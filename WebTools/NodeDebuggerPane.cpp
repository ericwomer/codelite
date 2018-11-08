#include "CallFrame.h"
#include "NodeDebugger.h"
#include "NodeDebuggerPane.h"
#include "NodeDebuggerTooltip.h"
#include "NodeFileManager.h"
#include "NodeJSDebuggerBreakpoint.h"
#include "NodeJSEvents.h"
#include "NoteJSWorkspace.h"
#include "PropertyDescriptor.h"
#include "event_notifier.h"
#include "wxterminal.h"
#include <wx/msgdlg.h>
#include <wx/wupdlock.h>

NodeDebuggerPane::NodeDebuggerPane(wxWindow* parent)
    : NodeJSCliDebuggerPaneBase(parent)
{
    m_dvListCtrlCallstack->SetSortFunction(nullptr);
    // Terminal for stdout/stdin with the running JS application
    m_terminal = new wxTerminal(m_panelOutput);
    m_terminal->SetInteractive(true);
    m_panelOutput->GetSizer()->Add(m_terminal, 1, wxEXPAND);

    // Console for real-time evaluating with Node.js
    m_node_console = new wxTerminal(m_panelConsole);
    m_node_console->SetInteractive(true);
    m_panelConsole->GetSizer()->Add(m_node_console, 1, wxEXPAND);

    m_terminal->Bind(wxEVT_TERMINAL_EXECUTE_COMMAND, &NodeDebuggerPane::OnRunTerminalCommand, this);
    m_node_console->Bind(wxEVT_TERMINAL_EXECUTE_COMMAND, &NodeDebuggerPane::OnEval, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_UPDATE_CONSOLE, &NodeDebuggerPane::OnConsoleOutput, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_UPDATE_CALLSTACK, &NodeDebuggerPane::OnUpdateBacktrace, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_STOPPED, &NodeDebuggerPane::OnDebuggerStopped, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_MARK_LINE, &NodeDebuggerPane::OnMarkLine, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_INTERACT, &NodeDebuggerPane::OnInteract, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_UPDATE_BREAKPOINTS_VIEW, &NodeDebuggerPane::OnUpdateBreakpoints,
                               this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_EVAL_RESULT, &NodeDebuggerPane::OnEvalResult, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_CREATE_OBJECT, &NodeDebuggerPane::OnCreateObject, this);
    EventNotifier::Get()->Bind(wxEVT_NODEJS_DEBUGGER_STARTED, &NodeDebuggerPane::OnDebugSessionStarted, this);
    EventNotifier::Get()->Bind(wxEVT_TOOLTIP_DESTROY, &NodeDebuggerPane::OnDestroyTip, this);
    m_dvListCtrlCallstack->SetSortFunction(nullptr);
    m_dvListCtrlBreakpoints->SetSortFunction(nullptr);

    DoPrintStartupMessages();
}

NodeDebuggerPane::~NodeDebuggerPane()
{
    DoDestroyTip();

    m_terminal->Unbind(wxEVT_TERMINAL_EXECUTE_COMMAND, &NodeDebuggerPane::OnRunTerminalCommand, this);
    m_node_console->Unbind(wxEVT_TERMINAL_EXECUTE_COMMAND, &NodeDebuggerPane::OnEval, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_UPDATE_CONSOLE, &NodeDebuggerPane::OnConsoleOutput, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_UPDATE_CALLSTACK, &NodeDebuggerPane::OnUpdateBacktrace,
                                 this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_STOPPED, &NodeDebuggerPane::OnDebuggerStopped, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_MARK_LINE, &NodeDebuggerPane::OnMarkLine, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_INTERACT, &NodeDebuggerPane::OnInteract, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_UPDATE_BREAKPOINTS_VIEW, &NodeDebuggerPane::OnUpdateBreakpoints,
                                 this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_EVAL_RESULT, &NodeDebuggerPane::OnEvalResult, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_CREATE_OBJECT, &NodeDebuggerPane::OnCreateObject, this);
    EventNotifier::Get()->Unbind(wxEVT_NODEJS_DEBUGGER_STARTED, &NodeDebuggerPane::OnDebugSessionStarted, this);
    EventNotifier::Get()->Unbind(wxEVT_TOOLTIP_DESTROY, &NodeDebuggerPane::OnDestroyTip, this);
}

void NodeDebuggerPane::OnUpdateBacktrace(clDebugCallFramesEvent& event)
{
    event.Skip();
    wxWindowUpdateLocker locker(m_dvListCtrlCallstack);
    const nSerializableObject::Vec_t& frames = event.GetCallFrames();
    m_dvListCtrlCallstack->DeleteAllItems();

    wxArrayString call_frame_ids;
    for(size_t i = 0; i < frames.size(); ++i) {
        CallFrame* frame = frames[i]->To<CallFrame>();

        wxVector<wxVariant> cols;
        wxString filename = NodeFileManager::Get().GetFilePath(frame->GetLocation().GetScriptId());
        cols.push_back(wxString() << "#" << i);
        cols.push_back(frame->GetFunctionName());
        cols.push_back(filename);
        cols.push_back(wxString() << (frame->GetLocation().GetLineNumber() + 1));
        m_dvListCtrlCallstack->AppendItem(cols, (wxUIntPtr) new wxStringClientData(frame->GetCallFrameId()));
        if(i == 0) {
            clDebugEvent event(wxEVT_NODEJS_DEBUGGER_MARK_LINE);
            event.SetLineNumber(frame->GetLocation().GetLineNumber() + 1);
            event.SetFileName(filename);
            EventNotifier::Get()->AddPendingEvent(event);
        }
        call_frame_ids.Add(frame->GetCallFrameId());
    }
    NodeJSWorkspace::Get()->GetDebugger()->SetFrames(call_frame_ids);
}

void NodeDebuggerPane::OnDebuggerStopped(clDebugEvent& event)
{
    event.Skip();
    m_dvListCtrlCallstack->DeleteAllItems([](wxUIntPtr data) {
        wxStringClientData* scd = reinterpret_cast<wxStringClientData*>(data);
        wxDELETE(scd);
    });
    m_dvListCtrlBreakpoints->DeleteAllItems([](wxUIntPtr data) {
        wxStringClientData* scd = reinterpret_cast<wxStringClientData*>(data);
        wxDELETE(scd);
    });
    NodeJSWorkspace::Get()->GetDebugger()->ClearDebuggerMarker();
    DoDestroyTip();
}

void NodeDebuggerPane::OnMarkLine(clDebugEvent& event)
{
    event.Skip();
    NodeJSWorkspace::Get()->GetDebugger()->ClearDebuggerMarker();
    NodeJSWorkspace::Get()->GetDebugger()->SetDebuggerMarker(event.GetFileName(), event.GetLineNumber());
}

void NodeDebuggerPane::OnUpdateBreakpoints(clDebugEvent& event)
{
    event.Skip();
    m_dvListCtrlBreakpoints->DeleteAllItems([](wxUIntPtr data) {
        wxStringClientData* scd = reinterpret_cast<wxStringClientData*>(data);
        wxDELETE(scd);
    });
    const NodeJSBreakpoint::Vec_t& bps = NodeJSWorkspace::Get()->GetDebugger()->GetBreakpointsMgr()->GetBreakpoints();
    for(size_t i = 0; i < bps.size(); ++i) {
        const NodeJSBreakpoint& bp = bps[i];
        wxVector<wxVariant> cols;
        cols.push_back(bp.GetFilename());
        cols.push_back(wxString() << bp.GetLine());
        m_dvListCtrlBreakpoints->AppendItem(cols, (wxUIntPtr) new wxStringClientData(bp.GetNodeBpID()));
    }
}

void NodeDebuggerPane::OnInteract(clDebugEvent& event)
{
    event.Skip();
    if(!event.IsAnswer()) {
        m_dvListCtrlCallstack->DeleteAllItems();
        NodeJSWorkspace::Get()->GetDebugger()->ClearDebuggerMarker();
    }
    if(event.GetString() == "exception") {
        // The debugger paused of an uncaught exception
        ::wxMessageBox(_("Node.js: uncaught exception!"), "Node.js", wxICON_ERROR | wxCENTRE,
                       EventNotifier::Get()->TopFrame());
    }
}

void NodeDebuggerPane::OnRunTerminalCommand(clCommandEvent& event)
{
    // Dont call event.Skip() here
    wxString command = event.GetString();
    NodeJSWorkspace::Get()->GetDebugger()->SendToDebuggee(command);
}

void NodeDebuggerPane::OnConsoleOutput(clDebugEvent& event)
{
    // Dont call event.Skip() here
    m_terminal->AddTextRaw(event.GetString());
}

void NodeDebuggerPane::OnEval(clCommandEvent& event)
{
    if(m_dvListCtrlCallstack->IsEmpty()) { return; }
    wxUIntPtr ptr = m_dvListCtrlCallstack->GetItemData(m_dvListCtrlCallstack->RowToItem(0));
    wxStringClientData* cd = reinterpret_cast<wxStringClientData*>(ptr);
    if(cd) { NodeJSWorkspace::Get()->GetDebugger()->Eval(event.GetString(), cd->GetData()); }
}

void NodeDebuggerPane::OnEvalResult(clDebugRemoteObjectEvent& event)
{
    RemoteObject* pro = event.GetRemoteObject()->To<RemoteObject>();
    m_node_console->AddTextRaw(pro->ToString() + "\n");
}

void NodeDebuggerPane::OnCreateObject(clDebugRemoteObjectEvent& event)
{
    nSerializableObject::Ptr_t o = event.GetRemoteObject();
    if(!m_debuggerTooltip) { m_debuggerTooltip = new NodeDebuggerTooltip(this); }
    m_debuggerTooltip->Show(o);
}

void NodeDebuggerPane::OnDestroyTip(clCommandEvent& event)
{
    event.Skip();
    DoDestroyTip();
}

void NodeDebuggerPane::DoDestroyTip()
{
    if(m_debuggerTooltip) {
        m_debuggerTooltip->Hide();
        m_debuggerTooltip->Destroy();
    }
    m_debuggerTooltip = nullptr;
}

void NodeDebuggerPane::OnDebugSessionStarted(clDebugEvent& event)
{
    event.Skip();
    DoPrintStartupMessages();
}

void NodeDebuggerPane::DoPrintStartupMessages()
{
    m_node_console->Clear();
    m_terminal->Clear();
    m_node_console->AddTextWithEOL("##==========================================================");
    m_node_console->AddTextWithEOL("## Node.js console");
    m_node_console->AddTextWithEOL("## use this console to send commands directly to node.js");
    m_node_console->AddTextWithEOL("##==========================================================");

    m_terminal->AddTextWithEOL("##==========================================================");
    m_terminal->AddTextWithEOL("## Node.js stdin/stdout console");
    m_terminal->AddTextWithEOL("## stdout messages (e.g. console.log(..) will appear here");
    m_terminal->AddTextWithEOL("##==========================================================");
}