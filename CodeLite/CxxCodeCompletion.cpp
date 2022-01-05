#include "CxxCodeCompletion.hpp"

#include "CxxExpression.hpp"
#include "CxxScannerTokens.h"
#include "CxxVariableScanner.h"
#include "ctags_manager.h"
#include "file_logger.h"
#include "function.h"
#include "language.h"

#include <algorithm>
#include <deque>

#define RECURSE_GUARD_RETURN_NULLPTR() \
    m_recurse_protector++;             \
    if(m_recurse_protector > 150) {    \
        return nullptr;                \
    }

#define RECURSE_GUARD_RETURN()      \
    m_recurse_protector++;          \
    if(m_recurse_protector > 150) { \
        return;                     \
    }

CxxCodeCompletion::CxxCodeCompletion(ITagsStoragePtr lookup)
    : m_lookup(lookup)
{
    m_template_manager.reset(new TemplateManager(this));
}

CxxCodeCompletion::~CxxCodeCompletion() {}

void CxxCodeCompletion::determine_current_scope()
{
    if(!m_current_scope_name.empty() || m_filename.empty() || m_line_number == wxNOT_FOUND) {
        return;
    }

    CHECK_PTR_RET(m_lookup);
    m_current_scope_name = m_lookup->GetScope(m_filename, m_line_number);
}

TagEntryPtr CxxCodeCompletion::code_complete(const wxString& expression, const vector<wxString>& visible_scopes,
                                             CxxExpression* remainder)
{
    // build expression from the expression
    m_recurse_protector = 0;
    m_template_manager.reset(new TemplateManager(this));

    vector<wxString> scopes = { visible_scopes.begin(), visible_scopes.end() };
    vector<CxxExpression> expr_arr = CxxExpression::from_expression(expression, remainder);
    auto where =
        find_if(visible_scopes.begin(), visible_scopes.end(), [](const wxString& scope) { return scope.empty(); });

    if(where == visible_scopes.end()) {
        // add the global scope
        scopes.push_back(wxEmptyString);
    }

    // Check the current scope
    if(!m_current_scope_name.empty()) {
        prepend_scope(scopes, m_current_scope_name);
    }

    clDEBUG() << "code_complete() called with scopes:" << scopes << endl;

    // handle global scope
    if(expr_arr.empty() ||
       (expr_arr.size() == 1 && expr_arr[0].type_name().empty() && expr_arr[0].operand_string() == "::")) {
        // return a dummy entry representing the global scope
        TagEntryPtr global_scope(new TagEntry());
        global_scope->SetName("<global>");
        global_scope->SetPath("<global>");
        return global_scope;
    } else if(expr_arr.size() >= 2 && expr_arr[0].type_name().empty() && expr_arr[0].operand_string() == "::") {
        // explicity requesting for the global namespace
        // clear the `scopes` and use only the global namespace (empty string)
        scopes.clear();
        scopes.push_back(wxEmptyString);
        // in addition, we can remove the first expression from the array
        expr_arr.erase(expr_arr.begin());
    }
    return resolve_compound_expression(expr_arr, scopes);
}

TagEntryPtr CxxCodeCompletion::resolve_compound_expression(vector<CxxExpression>& expression,
                                                           const vector<wxString>& visible_scopes)
{
    RECURSE_GUARD_RETURN_NULLPTR();

    // resolve each expression
    if(expression.empty()) {
        return nullptr;
    }

    TagEntryPtr resolved;
    for(CxxExpression& curexpr : expression) {
        resolved = resolve_expression(curexpr, resolved, visible_scopes);
        CHECK_PTR_RET_NULL(resolved);
    }
    return resolved;
}

size_t CxxCodeCompletion::parse_locals(const wxString& text, unordered_map<wxString, __local>* locals) const
{
    shrink_scope(text, locals);
    return locals->size();
}

wxString CxxCodeCompletion::shrink_scope(const wxString& text, unordered_map<wxString, __local>* locals) const
{
    CxxVariableScanner scanner(text, eCxxStandard::kCxx11, get_tokens_map(), false);
    const wxString& trimmed_text = scanner.GetOptimizeBuffer();

    CxxVariable::Vec_t variables = scanner.GetVariables(false);
    locals->reserve(variables.size());

    for(auto var : variables) {
        __local local;
        local.set_assignment(var->GetDefaultValue());
        local.set_type_name(var->GetTypeAsString());
        local.set_is_auto(var->IsAuto());
        local.set_name(var->GetName());
        local.set_pattern(var->ToString(CxxVariable::kToString_Name | CxxVariable::kToString_DefaultValue));
        locals->insert({ var->GetName(), local });
    }
    return trimmed_text;
}

TagEntryPtr CxxCodeCompletion::lookup_operator_arrow(TagEntryPtr parent, const vector<wxString>& visible_scopes)
{
    return lookup_child_symbol(parent, "operator->", visible_scopes, { "function", "prototype" });
}

TagEntryPtr CxxCodeCompletion::lookup_child_symbol(TagEntryPtr parent, const wxString& child_symbol,
                                                   const vector<wxString>& visible_scopes,
                                                   const vector<wxString>& kinds)
{
    CHECK_PTR_RET_NULL(m_lookup);
    auto resolved = lookup_symbol_by_kind(child_symbol, visible_scopes, kinds);
    if(resolved) {
        return resolved;
    }

    // try with the parent
    CHECK_PTR_RET_NULL(parent);

    // to avoid spaces and other stuff that depends on the user typing
    // we tokenize the symbol name
    vector<wxString> requested_symbol_tokens;
    {
        CxxLexerToken tok;
        CxxTokenizer tokenizer;
        tokenizer.Reset(child_symbol);
        while(tokenizer.NextToken(tok)) {
            requested_symbol_tokens.push_back(tok.GetWXString());
        }
    }

    auto compare_tokens_func = [&requested_symbol_tokens](const wxString& symbol_name) -> bool {
        CxxLexerToken tok;
        CxxTokenizer tokenizer;
        tokenizer.Reset(symbol_name);
        for(const wxString& token : requested_symbol_tokens) {
            if(!tokenizer.NextToken(tok)) {
                return false;
            }

            if(tok.GetWXString() != token)
                return false;
        }

        // if we can read more tokens from the tokenizer, it means that
        // the comparison is not complete, it "contains" the requested name
        if(tokenizer.NextToken(tok)) {
            return false;
        }
        return true;
    };

    deque<TagEntryPtr> q;
    q.push_front(parent);
    wxStringSet_t visited;
    while(!q.empty()) {
        auto t = q.front();
        q.pop_front();

        // avoid visiting the same tag twice
        if(!visited.insert(t->GetPath()).second)
            continue;

        vector<TagEntryPtr> tags;
        m_lookup->GetTagsByScope(t->GetPath(), tags);
        for(TagEntryPtr child : tags) {
            if(compare_tokens_func(child->GetName())) {
                return child;
            }
        }

        // if we got here, no match
        wxArrayString inherits = t->GetInheritsAsArrayNoTemplates();
        for(const wxString& inherit : inherits) {
            auto match = lookup_symbol_by_kind(inherit, visible_scopes, { "class", "struct" });
            if(match) {
                q.push_back(match);
            }
        }
    }
    return nullptr;
}

TagEntryPtr CxxCodeCompletion::lookup_symbol_by_kind(const wxString& name, const vector<wxString>& visible_scopes,
                                                     const vector<wxString>& kinds)
{
    vector<TagEntryPtr> tags;
    for(const wxString& scope : visible_scopes) {
        wxString path;
        if(!scope.empty()) {
            path << scope << "::";
        }
        path << name;
        m_lookup->GetTagsByPathAndKind(path, tags, kinds);
        if(tags.size() == 1) {
            // we got a match
            return tags[0];
        }
    }
    return tags.empty() ? nullptr : tags[0];
}

void CxxCodeCompletion::update_template_table(TagEntryPtr resolved, CxxExpression& curexpr,
                                              const vector<wxString>& visible_scopes, wxStringSet_t& visited)
{
    CHECK_PTR_RET(resolved);
    if(!visited.insert(resolved->GetPath()).second) {
        // already visited this node
        return;
    }

    // simple template instantiaion line
    wxString pattern = resolved->GetPatternClean();
    if(curexpr.is_template()) {
        curexpr.parse_template_placeholders(pattern);
        wxStringMap_t M = curexpr.get_template_placeholders_map();
        m_template_manager->add_placeholders(M, visible_scopes);
    }

    // Check if one of the parents is a template class
    vector<wxString> inhertiance_expressions = CxxExpression::split_subclass_expression(resolved->GetPatternClean());
    for(const wxString& inherit : inhertiance_expressions) {
        vector<CxxExpression> more_expressions = CxxExpression::from_expression(inherit + ".", nullptr);
        if(more_expressions.empty())
            continue;

        auto match = lookup_symbol_by_kind(more_expressions[0].type_name(), visible_scopes, { "class", "struct" });
        if(match) {
            update_template_table(match, more_expressions[0], visible_scopes, visited);
        }
    }
}

TagEntryPtr CxxCodeCompletion::lookup_symbol(CxxExpression& curexpr, const vector<wxString>& visible_scopes,
                                             TagEntryPtr parent)
{
    wxString name_to_find = curexpr.type_name();
    auto resolved_name = m_template_manager->resolve(name_to_find, visible_scopes);
    if(resolved_name != name_to_find) {
        name_to_find = resolved_name;
    }

    // try classes first
    auto resolved = lookup_child_symbol(parent, name_to_find, visible_scopes,
                                        { "typedef", "class", "struct", "namespace", "enum", "union" });
    if(!resolved) {
        // try methods
        // `lookup_child_symbol` takes inheritance into consideration
        resolved = lookup_child_symbol(parent, name_to_find, visible_scopes, { "function", "prototype", "member" });
    }

    if(resolved) {
        // update the template table
        wxStringSet_t visited;
        update_template_table(resolved, curexpr, visible_scopes, visited);

        // Check for operator-> overloading
        if(curexpr.operand_string() == "->") {
            // search for operator-> overloading
            TagEntryPtr arrow_tag = lookup_operator_arrow(resolved, visible_scopes);
            if(arrow_tag) {
                resolved = arrow_tag;
            }
        }
    }
    return resolved;
}

vector<wxString> CxxCodeCompletion::update_visible_scope(const vector<wxString>& curscopes, TagEntryPtr tag)
{
    vector<wxString> scopes;
    scopes.insert(scopes.end(), curscopes.begin(), curscopes.end());

    if(tag && (tag->IsClass() || tag->IsStruct() || tag->IsNamespace() || tag->GetKind() == "union")) {
        prepend_scope(scopes, tag->GetPath());
    } else if(tag && tag->IsMethod()) {
        prepend_scope(scopes, tag->GetScope());
    }
    return scopes;
}

TagEntryPtr CxxCodeCompletion::resolve_expression(CxxExpression& curexp, TagEntryPtr parent,
                                                  const vector<wxString>& visible_scopes)
{
    // test locals first, if its empty, its the first time we are entering here
    if(!parent) {
        if(curexp.is_this()) {
            // this can only work with ->
            if(curexp.operand_string() != "->") {
                return nullptr;
            }

            // replace "this" with the current scope name
            determine_current_scope();
            wxString exprstr = m_current_scope_name + curexp.operand_string();
            vector<CxxExpression> expr_arr = CxxExpression::from_expression(exprstr, nullptr);
            return resolve_compound_expression(expr_arr, visible_scopes);

        } else if(curexp.operand_string() == "." || curexp.operand_string() == "->") {
            if(m_locals.count(curexp.type_name())) {
                wxString exprstr = m_locals.find(curexp.type_name())->second.type_name() + curexp.operand_string();
                vector<CxxExpression> expr_arr = CxxExpression::from_expression(exprstr, nullptr);
                return resolve_compound_expression(expr_arr, visible_scopes);
            } else {
                determine_current_scope();
                auto scope_tag =
                    lookup_symbol_by_kind(m_current_scope_name, visible_scopes, { "class", "struct", "union" });
                if(scope_tag) {
                    // we are inside a scope, use the scope as the parent
                    // and call resolve_expression() again
                    return resolve_expression(curexp, scope_tag, visible_scopes);
                }
            }
        }
    }

    // update the visible scopes
    vector<wxString> scopes = update_visible_scope(visible_scopes, parent);

    auto resolved = lookup_symbol(curexp, scopes, parent);
    CHECK_PTR_RET_NULL(resolved);

    if(resolved->IsContainer()) {
        // nothing more to be done here
        return resolved;
    }

    // continue only if one of 3: member, method or typedef
    if(!resolved->IsMethod() && !resolved->IsMember() && !resolved->IsTypedef()) {
        return nullptr;
    }

    // after we resolved the expression, update the scope
    scopes = update_visible_scope(scopes, resolved);

    if(resolved->IsMethod()) {
        // parse the return value
        wxString new_expr = get_return_value(resolved) + curexp.operand_string();
        vector<CxxExpression> expr_arr = CxxExpression::from_expression(new_expr, nullptr);
        return resolve_compound_expression(expr_arr, scopes);
    } else if(resolved->IsTypedef()) {
        // substitude the type with the typeref
        wxString new_expr;
        if(!resolve_user_type(resolved->GetPath(), visible_scopes, &new_expr)) {
            new_expr = typedef_from_pattern(resolved->GetPatternClean());
        }
        new_expr += curexp.operand_string();
        vector<CxxExpression> expr_arr = CxxExpression::from_expression(new_expr, nullptr);
        return resolve_compound_expression(expr_arr, scopes);
    } else if(resolved->IsMember()) {
        // replace the member variable by its type
        unordered_map<wxString, __local> locals_variables;
        if((parse_locals(resolved->GetPatternClean(), &locals_variables) == 0) ||
           (locals_variables.count(resolved->GetName()) == 0)) {
            return nullptr;
        }

        wxString new_expr = locals_variables[resolved->GetName()].type_name() + curexp.operand_string();
        vector<CxxExpression> expr_arr = CxxExpression::from_expression(new_expr, nullptr);
        return resolve_compound_expression(expr_arr, scopes);
    }
    return nullptr;
}

const wxStringMap_t& CxxCodeCompletion::get_tokens_map() const { return m_macros_table_map; }

wxString CxxCodeCompletion::get_return_value(TagEntryPtr tag) const
{
    clFunction f;
    if(LanguageST::Get()->FunctionFromPattern(tag, f)) {
        wxString return_value;
        if(!f.m_returnValue.m_typeScope.empty()) {
            return_value << f.m_returnValue.m_typeScope << "::";
        }
        return_value << f.m_returnValue.m_type;
        return return_value;
    }
    return wxEmptyString;
}

void CxxCodeCompletion::prepend_scope(vector<wxString>& scopes, const wxString& scope) const
{
    auto where = find_if(scopes.begin(), scopes.end(), [=](const wxString& s) { return s == scope; });

    if(where != scopes.end()) {
        scopes.erase(where);
    }

    scopes.insert(scopes.begin(), scope);
}

void CxxCodeCompletion::reset()
{
    m_locals.clear();
    m_optimized_scope.clear();
    m_template_manager->clear();
    m_recurse_protector = 0;
    m_current_scope_name.clear();
}

wxString CxxCodeCompletion::typedef_from_pattern(const wxString& pattern) const
{
    CxxTokenizer tkzr;
    CxxLexerToken tk;

    tkzr.Reset(pattern);

    wxString typedef_str;
    vector<wxString> V;
    wxString last_identifier;
    if(!tkzr.NextToken(tk)) {
        return wxEmptyString;
    }

    if(tk.GetType() == T_USING) {
        // "using" syntax:
        // using element_type = _Tp;
        // read until the "=";

        // consume everything until we find the "="
        while(tkzr.NextToken(tk)) {
            if(tk.GetType() == '=')
                break;
        }

        // read until the ";"
        while(tkzr.NextToken(tk)) {
            if(tk.GetType() == ';') {
                break;
            }
            if(tk.is_keyword()) {
                // dont pick keywords
                continue;
            }
            if(tk.is_builtin_type()) {
                V.push_back((V.empty() ? "" : " ") + tk.GetWXString() + " ");
            } else {
                V.push_back(tk.GetWXString());
            }
        }

    } else if(tk.GetType() == T_TYPEDEF) {
        // standard "typedef" syntax:
        // typedef wxString MyString;
        while(tkzr.NextToken(tk)) {
            if(tk.is_keyword()) {
                continue;
            }
            if(tk.GetType() == ';') {
                // end of typedef
                if(!V.empty()) {
                    V.pop_back();
                }
                break;
            } else {
                if(tk.is_builtin_type()) {
                    V.push_back((V.empty() ? "" : " ") + tk.GetWXString() + " ");
                } else {
                    V.push_back(tk.GetWXString());
                }
            }
        }
    }

    if(V.empty()) {
        return wxEmptyString;
    }

    for(const wxString& s : V) {
        typedef_str << s;
    }
    return typedef_str.Trim();
}

vector<TagEntryPtr> CxxCodeCompletion::get_locals()
{
    vector<TagEntryPtr> locals;
    locals.reserve(m_locals.size());

    for(const auto& vt : m_locals) {
        const auto& local = vt.second;
        TagEntryPtr tag(new TagEntry());
        tag->SetName(local.name());
        tag->SetKind("variable");
        tag->SetParent("<local>");
        tag->SetScope(local.type_name());
        tag->SetAccess("public");
        tag->SetPattern("/^ " + local.pattern() + " $/");
        locals.push_back(tag);
    }
    return locals;
}

size_t CxxCodeCompletion::get_completions(TagEntryPtr parent, const wxString& filter, vector<TagEntryPtr>& candidates,
                                          const vector<wxString>& visible_scopes, size_t limit)
{
    if(!parent) {
        return 0;
    }
    vector<TagEntryPtr> scopes = get_scopes(parent, visible_scopes);
    for(TagEntryPtr scope : scopes) {
        vector<TagEntryPtr> children =
            get_children_of_scope(scope, { "function", "prototype", "member", "enum", "enumerator" });
        candidates.insert(candidates.end(), children.begin(), children.end());
    }

    // sort the matches
    vector<TagEntryPtr> sorted_tags;
    sort_tags(candidates, sorted_tags, ".");
    candidates.swap(sorted_tags);

    // filter the results
    return candidates.size();
}

vector<TagEntryPtr> CxxCodeCompletion::get_scopes(TagEntryPtr parent, const vector<wxString>& visible_scopes)
{
    vector<TagEntryPtr> scopes;
    scopes.reserve(100);

    deque<TagEntryPtr> q;
    q.push_front(parent);
    wxStringSet_t visited;
    while(!q.empty()) {
        auto t = q.front();
        q.pop_front();

        // avoid visiting the same tag twice
        if(!visited.insert(t->GetPath()).second)
            continue;

        scopes.push_back(t);

        // if we got here, no match
        wxArrayString inherits = t->GetInheritsAsArrayNoTemplates();
        for(const wxString& inherit : inherits) {
            auto match = lookup_symbol_by_kind(inherit, visible_scopes, { "class", "struct" });
            if(match) {
                q.push_back(match);
            }
        }
    }
    return scopes;
}

vector<TagEntryPtr> CxxCodeCompletion::get_children_of_scope(TagEntryPtr parent, const vector<wxString>& kinds)
{
    if(!m_lookup) {
        return {};
    }

    vector<TagEntryPtr> tags;
    wxArrayString wx_kinds;
    wx_kinds.reserve(kinds.size());
    for(const wxString& kind : kinds) {
        wx_kinds.Add(kind);
    }
    m_lookup->GetTagsByScopeAndKind(parent->GetPath(), wx_kinds, tags);
    return tags;
}

void CxxCodeCompletion::set_text(const wxString& text, const wxString& filename, int current_line)
{
    m_optimized_scope.clear();
    m_locals.clear();
    m_optimized_scope = shrink_scope(text, &m_locals);
    m_filename = filename;
    m_line_number = current_line;
    m_current_scope_name.clear();

    if(!m_filename.empty() && m_line_number != wxNOT_FOUND) {
        determine_current_scope();
    }
}

namespace
{

bool find_wild_match(const vector<pair<wxString, wxString>>& table, const wxString& find_what, wxString* match)
{
    for(const auto& p : table) {
        // we support wildcard matching
        if(::wxMatchWild(p.first, find_what)) {
            *match = p.second;
            return true;
        }
    }
    return false;
}

bool try_resovle_user_type_with_scopes(const vector<pair<wxString, wxString>>& table, const wxString& type,
                                       const vector<wxString>& visible_scopes, wxString* resolved)
{
    for(const wxString& scope : visible_scopes) {
        wxString user_type = scope;
        if(!user_type.empty()) {
            user_type << "::";
        }
        user_type << type;
        if(find_wild_match(table, type, resolved)) {
            return true;
        }
    }
    return false;
}
}; // namespace

bool CxxCodeCompletion::resolve_user_type(const wxString& type, const vector<wxString>& visible_scopes,
                                          wxString* resolved) const
{
    bool match_found = false;
    wxStringSet_t visited;
    *resolved = type;
    while(true) {
        if(!visited.insert(*resolved).second) {
            // already tried this type
            break;
        }

        if(!try_resovle_user_type_with_scopes(m_types_table, *resolved, visible_scopes, resolved)) {
            break;
        }
        match_found = true;
    }

    if(match_found) {
        return true;
    }
    return false;
}

void TemplateManager::clear() { m_table.clear(); }

void TemplateManager::add_placeholders(const wxStringMap_t& table, const vector<wxString>& visible_scopes)
{
    // try to resolve any of the template before we insert them
    // its important to do it now so we use the correct scope
    wxStringMap_t M;
    for(const auto& vt : table) {
        wxString name = vt.first;
        wxString value;

        auto resolved = m_completer->lookup_child_symbol(
            nullptr, vt.second, visible_scopes,
            { "class", "struct", "typedef", "union", "namespace", "enum", "enumerator" });
        if(resolved) {
            // use the path found in the db
            value = resolved->GetPath();
        } else {
            value = vt.second;
        }
        M.insert({ name, value });
    }
    m_table.insert(m_table.begin(), M);
}

#define STRIP_PLACEHOLDER(__ph)                        \
    stripped_placeholder.Replace("*", wxEmptyString);  \
    stripped_placeholder.Replace("->", wxEmptyString); \
    stripped_placeholder.Replace("&&", wxEmptyString);

namespace
{
bool try_resolve_placeholder(const wxStringMap_t& table, const wxString& name, wxString* resolved)
{
    // strip operands from `s`
    wxString stripped_placeholder = name;
    STRIP_PLACEHOLDER(stripped_placeholder);

    if(table.count(name)) {
        *resolved = table.find(name)->second;
        return true;
    }
    return false;
}
}; // namespace

wxString TemplateManager::resolve(const wxString& name, const vector<wxString>& visible_scopes) const
{
    wxStringSet_t visited;
    wxString resolved = name;
    for(const wxStringMap_t& table : m_table) {
        try_resolve_placeholder(table, resolved, &resolved);
    }
    return resolved;
}

void CxxCodeCompletion::set_macros_table(const vector<pair<wxString, wxString>>& t)
{
    m_macros_table = t;

    m_macros_table_map.reserve(m_macros_table.size());
    for(const auto& d : m_macros_table) {
        m_macros_table_map.insert(d);
    }
}

void CxxCodeCompletion::sort_tags(const vector<TagEntryPtr>& tags, vector<TagEntryPtr>& sorted_tags,
                                  const wxString& operand)
{
    TagEntryPtrVector_t publicTags;
    TagEntryPtrVector_t protectedTags;
    TagEntryPtrVector_t privateTags;
    TagEntryPtrVector_t locals;
    TagEntryPtrVector_t members;

    bool skip_tor = operand == "." || operand == "->";

    // first: remove duplicates
    unordered_set<int> visited_by_id;
    unordered_set<wxString> visited_by_name;

    for(size_t i = 0; i < tags.size(); ++i) {
        TagEntryPtr tag = tags.at(i);
        if(skip_tor && (tag->IsConstructor() || tag->IsDestructor()))
            continue;

        bool is_local = tag->IsLocalVariable() || tag->GetScope() == "<local>";
        // we filter local tags by name
        if(is_local && !visited_by_name.insert(tag->GetName()).second) {
            continue;
        }

        // other tags (loaded from the db) are filtered by their ID
        if(!is_local && !visited_by_id.insert(tag->GetId()).second) {
            continue;
        }

        // filter by type/access
        wxString access = tag->GetAccess();
        wxString kind = tag->GetKind();

        if(kind == "variable") {
            locals.push_back(tag);

        } else if(kind == "member") {
            members.push_back(tag);

        } else if(access == "private") {
            privateTags.push_back(tag);

        } else if(access == "protected") {
            protectedTags.push_back(tag);

        } else if(access == "public") {
            if(tag->GetName().StartsWith("_") || tag->GetName().Contains("operator")) {
                // methods starting with _ usually are meant to be private
                // and also, put the "operator" methdos at the bottom
                privateTags.push_back(tag);
            } else {
                publicTags.push_back(tag);
            }
        } else {
            // assume private
            privateTags.push_back(tag);
        }
    }

    auto sort_func = [=](TagEntryPtr a, TagEntryPtr b) { return a->GetName().CmpNoCase(b->GetName()) < 0; };

    sort(privateTags.begin(), privateTags.end(), sort_func);
    sort(publicTags.begin(), publicTags.end(), sort_func);
    sort(protectedTags.begin(), protectedTags.end(), sort_func);
    sort(members.begin(), members.end(), sort_func);
    sort(locals.begin(), locals.end(), sort_func);

    sorted_tags.clear();
    sorted_tags.insert(sorted_tags.end(), locals.begin(), locals.end());
    sorted_tags.insert(sorted_tags.end(), publicTags.begin(), publicTags.end());
    sorted_tags.insert(sorted_tags.end(), protectedTags.begin(), protectedTags.end());
    sorted_tags.insert(sorted_tags.end(), privateTags.begin(), privateTags.end());
    sorted_tags.insert(sorted_tags.end(), members.begin(), members.end());
}