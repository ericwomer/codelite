//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: editor_options_misc.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "editorsettingsmiscbasepanel.h"

// Declare the bitmap loading function
extern void wxC38F8InitBitmapResources();

static bool bBitmapLoaded = false;

EditorSettingsMiscBasePanel::EditorSettingsMiscBasePanel(wxWindow* parent, wxWindowID id, const wxPoint& pos,
                                                         const wxSize& size, long style)
    : wxPanel(parent, id, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxC38F8InitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* bSizer1 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer1);

    m_notebook2 = new Notebook(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                               kNotebook_Default | wxBORDER_STATIC);
    m_notebook2->SetName(wxT("m_notebook2"));

    bSizer1->Add(m_notebook2, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_panel1 =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panel1, _("General"), true);

    wxBoxSizer* bSizer2 = new wxBoxSizer(wxVERTICAL);
    m_panel1->SetSizer(bSizer2);

    wxFlexGridSizer* fgSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer4->SetFlexibleDirection(wxBOTH);
    fgSizer4->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer4->AddGrowableCol(1);

    bSizer2->Add(fgSizer4, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText8 = new wxStaticText(m_panel1, wxID_ANY, _("Toolbar Icon Size:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);

    fgSizer4->Add(m_staticText8, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_toolbarIconSizeArr;
    m_toolbarIconSizeArr.Add(wxT("Small Icons (16x16)"));
    m_toolbarIconSizeArr.Add(wxT("Large Icons (24x24)"));
    m_toolbarIconSize = new wxChoice(m_panel1, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel1, wxSize(-1, -1)),
                                     m_toolbarIconSizeArr, 0);
    m_toolbarIconSize->SetSelection(1);

    fgSizer4->Add(m_toolbarIconSize, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer98 = new wxBoxSizer(wxVERTICAL);

    bSizer2->Add(boxSizer98, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_singleAppInstance = new wxCheckBox(m_panel1, wxID_ANY, _("Allow only single instance running"), wxDefaultPosition,
                                         wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);
    m_singleAppInstance->SetValue(false);
    m_singleAppInstance->SetToolTip(_("There can be only one"));

    boxSizer98->Add(m_singleAppInstance, 0, wxALL, WXC_FROM_DIP(5));

    m_versionCheckOnStartup = new wxCheckBox(m_panel1, wxID_ANY, _("Check for new version on startup"),
                                             wxDefaultPosition, wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);
    m_versionCheckOnStartup->SetValue(true);
    m_versionCheckOnStartup->SetToolTip(_("When codelite starts, it will connect to http://codelite.org to check if a "
                                          "new version of codelite was released"));

    boxSizer98->Add(m_versionCheckOnStartup, 0, wxALL, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer57 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer98->Add(boxSizer57, 1, wxEXPAND, WXC_FROM_DIP(5));

    boxSizer57->Add(15, -1, 0, wxALL, WXC_FROM_DIP(5));

    m_checkBoxPromptReleaseOnly = new wxCheckBox(m_panel1, wxID_ANY, _("Prompt for stable releases only"),
                                                 wxDefaultPosition, wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);
    m_checkBoxPromptReleaseOnly->SetValue(false);
    m_checkBoxPromptReleaseOnly->SetToolTip(
        _("When checked, prompt me for new stable releases\nDon't prompt me for weekly builds"));

    boxSizer57->Add(m_checkBoxPromptReleaseOnly, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_checkBoxRestoreSession = new wxCheckBox(m_panel1, wxID_ANY, _("Load last session on startup"), wxDefaultPosition,
                                              wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);
    m_checkBoxRestoreSession->SetValue(false);
    m_checkBoxRestoreSession->SetToolTip(
        _("When launched, codelite will restore the last opened workspace + all open editors"));

    boxSizer98->Add(m_checkBoxRestoreSession, 0, wxALL, WXC_FROM_DIP(5));

    wxFlexGridSizer* flexGridSizer77 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer77->SetFlexibleDirection(wxBOTH);
    flexGridSizer77->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer77->AddGrowableCol(1);

    boxSizer98->Add(flexGridSizer77, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText79 = new wxStaticText(m_panel1, wxID_ANY, _("Web search prefix:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);

    flexGridSizer77->Add(m_staticText79, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_webSearchPrefix = new wxTextCtrl(m_panel1, wxID_ANY, wxT("https://www.google.com/search?q="), wxDefaultPosition,
                                       wxDLG_UNIT(m_panel1, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_webSearchPrefix->SetHint(wxT(""));
#endif

    flexGridSizer77->Add(m_webSearchPrefix, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_panel23 =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panel23, _("Frame Title"), false);

    wxBoxSizer* boxSizer25 = new wxBoxSizer(wxVERTICAL);
    m_panel23->SetSizer(boxSizer25);

    m_banner27 = new wxBannerWindow(m_panel23, wxID_ANY, wxTOP, wxDefaultPosition,
                                    wxDLG_UNIT(m_panel23, wxSize(-1, -1)), wxBORDER_THEME);
    m_banner27->SetBitmap(wxNullBitmap);
    m_banner27->SetText(_("Set CodeLite frame's title"), _("Set custom title to codelite's main frame"));
    m_banner27->SetGradient(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION),
                            wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
    m_banner27->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT));

    boxSizer25->Add(m_banner27, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText31 =
        new wxStaticText(m_panel23, wxID_ANY, _("You can use the following macros to construct your own frame title:"),
                         wxDefaultPosition, wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);

    boxSizer25->Add(m_staticText31, 0, wxALL, WXC_FROM_DIP(5));

    wxFlexGridSizer* flexGridSizer29 = new wxFlexGridSizer(0, 2, 0, 0);
    flexGridSizer29->SetFlexibleDirection(wxBOTH);
    flexGridSizer29->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer29->AddGrowableCol(1);

    boxSizer25->Add(flexGridSizer29, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText33 =
        new wxStaticText(m_panel23, wxID_ANY, _("$user"), wxDefaultPosition, wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);
    wxFont m_staticText33Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText33Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText33->SetFont(m_staticText33Font);

    flexGridSizer29->Add(m_staticText33, 0, wxALL | wxALIGN_RIGHT, WXC_FROM_DIP(5));

    m_staticText35 = new wxStaticText(m_panel23, wxID_ANY, _("the current user name inside square brackets"),
                                      wxDefaultPosition, wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);

    flexGridSizer29->Add(m_staticText35, 0, wxALL, WXC_FROM_DIP(5));

    m_staticText37 = new wxStaticText(m_panel23, wxID_ANY, _("$filename"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);
    wxFont m_staticText37Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText37Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText37->SetFont(m_staticText37Font);

    flexGridSizer29->Add(m_staticText37, 0, wxALL | wxALIGN_RIGHT, WXC_FROM_DIP(5));

    m_staticText39 = new wxStaticText(m_panel23, wxID_ANY, _("the current file name"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);

    flexGridSizer29->Add(m_staticText39, 0, wxALL, WXC_FROM_DIP(5));

    m_staticText41 = new wxStaticText(m_panel23, wxID_ANY, _("$fullpath"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);
    wxFont m_staticText41Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText41Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText41->SetFont(m_staticText41Font);

    flexGridSizer29->Add(m_staticText41, 0, wxALL | wxALIGN_RIGHT, WXC_FROM_DIP(5));

    m_staticText43 = new wxStaticText(m_panel23, wxID_ANY, _("the current file fullpath"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);

    flexGridSizer29->Add(m_staticText43, 0, wxALL, WXC_FROM_DIP(5));

    m_staticText45 = new wxStaticText(m_panel23, wxID_ANY, _("$workspace"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);
    wxFont m_staticText45Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    m_staticText45Font.SetWeight(wxFONTWEIGHT_BOLD);
    m_staticText45->SetFont(m_staticText45Font);

    flexGridSizer29->Add(m_staticText45, 0, wxALL | wxALIGN_RIGHT, WXC_FROM_DIP(5));

    m_staticText47 = new wxStaticText(m_panel23, wxID_ANY, _("the current workspace name inside square brackets"),
                                      wxDefaultPosition, wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);

    flexGridSizer29->Add(m_staticText47, 0, wxALL, WXC_FROM_DIP(5));

    m_staticText49 = new wxStaticText(m_panel23, wxID_ANY, _("Frame title:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);

    flexGridSizer29->Add(m_staticText49, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_textCtrlPattern = new wxTextCtrl(m_panel23, wxID_ANY, wxT("$workspace $fullpath"), wxDefaultPosition,
                                       wxDLG_UNIT(m_panel23, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_textCtrlPattern->SetHint(wxT(""));
#endif

    flexGridSizer29->Add(m_textCtrlPattern, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_panel44 =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panel44, _("Status Bar"), false);

    wxBoxSizer* boxSizer115 = new wxBoxSizer(wxVERTICAL);
    m_panel44->SetSizer(boxSizer115);

    m_staticText70 =
        new wxStaticText(m_panel44, wxID_ANY, _("What statistics to show in the status bar about an editor's text:"),
                         wxDefaultPosition, wxDLG_UNIT(m_panel44, wxSize(-1, -1)), 0);

    boxSizer115->Add(m_staticText70, 0, wxALL, WXC_FROM_DIP(5));

    m_statusbarShowLine = new wxCheckBox(m_panel44, wxID_ANY, _("Show current line"), wxDefaultPosition,
                                         wxDLG_UNIT(m_panel44, wxSize(-1, -1)), 0);
    m_statusbarShowLine->SetValue(true);

    boxSizer115->Add(m_statusbarShowLine, 0, wxALL, WXC_FROM_DIP(5));

    m_statusbarShowCol = new wxCheckBox(m_panel44, wxID_ANY, _("Show current column"), wxDefaultPosition,
                                        wxDLG_UNIT(m_panel44, wxSize(-1, -1)), 0);
    m_statusbarShowCol->SetValue(true);

    boxSizer115->Add(m_statusbarShowCol, 0, wxALL, WXC_FROM_DIP(5));

    m_statusbarShowPos = new wxCheckBox(m_panel44, wxID_ANY, _("Show current position within the file"),
                                        wxDefaultPosition, wxDLG_UNIT(m_panel44, wxSize(-1, -1)), 0);
    m_statusbarShowPos->SetValue(false);
    m_statusbarShowPos->SetToolTip(_("e.g. character 1234 in the file"));

    boxSizer115->Add(m_statusbarShowPos, 0, wxALL, WXC_FROM_DIP(5));

    m_statusbarShowFileLength = new wxCheckBox(m_panel44, wxID_ANY, _("Show total length of the file"),
                                               wxDefaultPosition, wxDLG_UNIT(m_panel44, wxSize(-1, -1)), 0);
    m_statusbarShowFileLength->SetValue(false);

    boxSizer115->Add(m_statusbarShowFileLength, 0, wxALL, WXC_FROM_DIP(5));

    m_statusBarShowSelChars = new wxCheckBox(m_panel44, wxID_ANY, _("Show number of selected chars"), wxDefaultPosition,
                                             wxDLG_UNIT(m_panel44, wxSize(-1, -1)), 0);
    m_statusBarShowSelChars->SetValue(false);
    m_statusBarShowSelChars->SetToolTip(_("Show the number of selected chars in the editor"));

    boxSizer115->Add(m_statusBarShowSelChars, 0, wxALL, WXC_FROM_DIP(5));

    m_panelTBar =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panelTBar, _("Tool Bar"), false);

    wxBoxSizer* boxSizer1152 = new wxBoxSizer(wxVERTICAL);
    m_panelTBar->SetSizer(boxSizer1152);

    wxBoxSizer* boxSizer95 = new wxBoxSizer(wxHORIZONTAL);

    boxSizer1152->Add(boxSizer95, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText94 = new wxStaticText(m_panelTBar, wxID_ANY, _("Separate adjacent tool groups by:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panelTBar, wxSize(-1, -1)), 0);

    boxSizer95->Add(m_staticText94, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_textCtrlSeparation =
        new wxTextCtrl(m_panelTBar, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(m_panelTBar, wxSize(-1, -1)), 0);
    m_textCtrlSeparation->SetToolTip(
        _("The tools on the toolbar are grouped by their function e.g. Edit, Build. By default those groups are "
          "separated by little more than a vertical line. Here you can adjust the amount of separation."));
#if wxVERSION_NUMBER >= 3000
    m_textCtrlSeparation->SetHint(wxT(""));
#endif

    boxSizer95->Add(m_textCtrlSeparation, 1, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticText97 = new wxStaticText(m_panelTBar, wxID_ANY, _("pixels"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panelTBar, wxSize(-1, -1)), 0);

    boxSizer95->Add(m_staticText97, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_panel2 =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panel2, _("Encoding & Locale"), false);

    wxBoxSizer* bSizer4 = new wxBoxSizer(wxVERTICAL);
    m_panel2->SetSizer(bSizer4);

    wxFlexGridSizer* fgSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer1->SetFlexibleDirection(wxBOTH);
    fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer1->AddGrowableCol(1);

    bSizer4->Add(fgSizer1, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText1 = new wxStaticText(m_panel2, wxID_ANY, _("File font encoding:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panel2, wxSize(-1, -1)), 0);

    fgSizer1->Add(m_staticText1, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_fileEncodingArr;
    m_fileEncoding =
        new wxChoice(m_panel2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel2, wxSize(-1, -1)), m_fileEncodingArr, 0);

    fgSizer1->Add(m_fileEncoding, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    fgSizer1->Add(0, 0, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_SetLocale = new wxCheckBox(m_panel2, wxID_ANY, _("Enable localization"), wxDefaultPosition,
                                 wxDLG_UNIT(m_panel2, wxSize(-1, -1)), 0);
    m_SetLocale->SetValue(true);
    m_SetLocale->SetToolTip(_("View CodeLite's strings translated into a different language, if available.  This will "
                              "also make CodeLite use other aspects of the locale."));

    fgSizer1->Add(m_SetLocale, 0, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_staticTextLocale = new wxStaticText(m_panel2, wxID_ANY, _("Locale to use:"), wxDefaultPosition,
                                          wxDLG_UNIT(m_panel2, wxSize(-1, -1)), 0);

    fgSizer1->Add(m_staticTextLocale, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_AvailableLocalesArr;
    m_AvailableLocales = new wxChoice(m_panel2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel2, wxSize(-1, -1)),
                                      m_AvailableLocalesArr, 0);
    m_AvailableLocales->SetToolTip(_("These are the locales that are available on your system. There won't necessarily "
                                     "be CodeLite translations for all of them."));

    fgSizer1->Add(m_AvailableLocales, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_panel3 =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panel3, _("History"), false);

    wxFlexGridSizer* fgSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
    fgSizer2->SetFlexibleDirection(wxBOTH);
    fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    fgSizer2->AddGrowableCol(1);
    m_panel3->SetSizer(fgSizer2);

    m_staticText2 = new wxStaticText(m_panel3, wxID_ANY, _("Clear recent workspace / files history"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText2, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_clearButton =
        new wxButton(m_panel3, wxID_CLEAR, _("&Clear"), wxDefaultPosition, wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);
    m_clearButton->SetDefault();

    fgSizer2->Add(m_clearButton, 0, wxALL | wxEXPAND | wxALIGN_LEFT, WXC_FROM_DIP(5));

    m_staticText3 = new wxStaticText(m_panel3, wxID_ANY, _("Max items kept in find / replace dialog:"),
                                     wxDefaultPosition, wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText3, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_maxItemsFindReplace =
        new wxTextCtrl(m_panel3, wxID_ANY, wxT("15"), wxDefaultPosition, wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_maxItemsFindReplace->SetHint(wxT(""));
#endif

    fgSizer2->Add(m_maxItemsFindReplace, 0, wxALL | wxEXPAND | wxALIGN_LEFT, WXC_FROM_DIP(5));

    m_staticText4 = new wxStaticText(m_panel3, wxID_ANY, _("Maximum number of tabs opened in the editor:"),
                                     wxDefaultPosition, wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText4, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_spinCtrlMaxOpenTabs =
        new wxTextCtrl(m_panel3, wxID_ANY, wxT("10"), wxDefaultPosition, wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);
#if wxVERSION_NUMBER >= 3000
    m_spinCtrlMaxOpenTabs->SetHint(wxT(""));
#endif

    fgSizer2->Add(m_spinCtrlMaxOpenTabs, 0, wxALL | wxEXPAND | wxALIGN_LEFT, WXC_FROM_DIP(5));

    m_staticText53 = new wxStaticText(m_panel3, wxID_ANY, _("Reset annoying dialogs answers:"), wxDefaultPosition,
                                      wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_staticText53, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_buttonAnnoyingDialogs =
        new wxButton(m_panel3, wxID_ANY, _("&Reset"), wxDefaultPosition, wxDLG_UNIT(m_panel3, wxSize(-1, -1)), 0);

    fgSizer2->Add(m_buttonAnnoyingDialogs, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_panel4 =
        new wxPanel(m_notebook2, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_notebook2, wxSize(-1, -1)), wxTAB_TRAVERSAL);
    m_notebook2->AddPage(m_panel4, _("Log"), false);

    wxBoxSizer* boxSizer11 = new wxBoxSizer(wxVERTICAL);
    m_panel4->SetSizer(boxSizer11);

    wxFlexGridSizer* flexGridSizer13 = new wxFlexGridSizer(0, 3, 0, 0);
    flexGridSizer13->SetFlexibleDirection(wxBOTH);
    flexGridSizer13->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);
    flexGridSizer13->AddGrowableCol(1);
    flexGridSizer13->AddGrowableCol(2);

    boxSizer11->Add(flexGridSizer13, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText6 = new wxStaticText(m_panel4, wxID_ANY, _("CodeLite's Log-file verbosity:"), wxDefaultPosition,
                                     wxDLG_UNIT(m_panel4, wxSize(-1, -1)), 0);

    flexGridSizer13->Add(m_staticText6, 0, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    wxArrayString m_choice4Arr;
    m_choice4Arr.Add(wxT("Error"));
    m_choice4Arr.Add(wxT("Warning"));
    m_choice4Arr.Add(wxT("Debug"));
    m_choice4Arr.Add(wxT("Developer"));
    m_choice4 =
        new wxChoice(m_panel4, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(m_panel4, wxSize(-1, -1)), m_choice4Arr, 0);
    m_choice4->SetToolTip(_("codelite logs to file various events, this option controls the logging verbosity"));
    m_choice4->SetSelection(0);

    flexGridSizer13->Add(m_choice4, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_buttonOpenLog =
        new wxButton(m_panel4, wxID_ANY, _("Open.."), wxDefaultPosition, wxDLG_UNIT(m_panel4, wxSize(-1, -1)), 0);
    m_buttonOpenLog->SetToolTip(_("Open the log file into an editor"));

    flexGridSizer13->Add(m_buttonOpenLog, 0, wxALL | wxEXPAND | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_redirectLogOutput = new wxCheckBox(m_panel4, wxID_ANY, _("GTK only: Redirect stdout/stderr output to a log file"),
                                         wxDefaultPosition, wxDLG_UNIT(m_panel4, wxSize(-1, -1)), 0);
    m_redirectLogOutput->SetValue(true);
    m_redirectLogOutput->SetToolTip(_("If ticked, all output from e.g. cout or wxLogDebug will be redirected to the "
                                      "file .codelite/codelite-stdout-stderr.log"));

    boxSizer11->Add(m_redirectLogOutput, 0, wxALL, WXC_FROM_DIP(10));

    SetName(wxT("EditorSettingsMiscBasePanel"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) { GetSizer()->Fit(this); }
    // Connect events
    m_checkBoxPromptReleaseOnly->Connect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::OnPromptStableReleaseUI), NULL, this);
    m_SetLocale->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::LocaleChkUpdateUI), NULL,
                         this);
    m_staticTextLocale->Connect(wxEVT_UPDATE_UI,
                                wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::LocaleStaticUpdateUI), NULL, this);
    m_AvailableLocales->Connect(wxEVT_UPDATE_UI,
                                wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::LocaleChoiceUpdateUI), NULL, this);
    m_clearButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                           wxCommandEventHandler(EditorSettingsMiscBasePanel::OnClearButtonClick), NULL, this);
    m_clearButton->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::OnClearUI), NULL, this);
    m_buttonAnnoyingDialogs->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                                     wxCommandEventHandler(EditorSettingsMiscBasePanel::OnResetAnnoyingDialogsAnswers),
                                     NULL, this);
    m_choice4->Connect(wxEVT_COMMAND_CHOICE_SELECTED,
                       wxCommandEventHandler(EditorSettingsMiscBasePanel::OnLogVerbosityChanged), NULL, this);
    m_buttonOpenLog->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                             wxCommandEventHandler(EditorSettingsMiscBasePanel::OnShowLogFile), NULL, this);
    m_redirectLogOutput->Connect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::OnLogoutputCheckUpdateUI), NULL, this);
}

EditorSettingsMiscBasePanel::~EditorSettingsMiscBasePanel()
{
    m_checkBoxPromptReleaseOnly->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::OnPromptStableReleaseUI), NULL, this);
    m_SetLocale->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::LocaleChkUpdateUI),
                            NULL, this);
    m_staticTextLocale->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::LocaleStaticUpdateUI), NULL, this);
    m_AvailableLocales->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::LocaleChoiceUpdateUI), NULL, this);
    m_clearButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                              wxCommandEventHandler(EditorSettingsMiscBasePanel::OnClearButtonClick), NULL, this);
    m_clearButton->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::OnClearUI), NULL,
                              this);
    m_buttonAnnoyingDialogs->Disconnect(
        wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(EditorSettingsMiscBasePanel::OnResetAnnoyingDialogsAnswers),
        NULL, this);
    m_choice4->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED,
                          wxCommandEventHandler(EditorSettingsMiscBasePanel::OnLogVerbosityChanged), NULL, this);
    m_buttonOpenLog->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                                wxCommandEventHandler(EditorSettingsMiscBasePanel::OnShowLogFile), NULL, this);
    m_redirectLogOutput->Disconnect(
        wxEVT_UPDATE_UI, wxUpdateUIEventHandler(EditorSettingsMiscBasePanel::OnLogoutputCheckUpdateUI), NULL, this);
}
