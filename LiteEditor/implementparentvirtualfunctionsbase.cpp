//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: implementparentvirtualfunctionsbase.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#include "implementparentvirtualfunctionsbase.h"

// Declare the bitmap loading function
extern void wxCA6AAInitBitmapResources();

static bool bBitmapLoaded = false;

ImplementParentVirtualFunctionsBase::ImplementParentVirtualFunctionsBase(wxWindow* parent, wxWindowID id,
                                                                         const wxString& title, const wxPoint& pos,
                                                                         const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style)
{
    if(!bBitmapLoaded) {
        // We need to initialise the default bitmap handler
        wxXmlResource::Get()->AddHandler(new wxBitmapXmlHandler);
        wxCA6AAInitBitmapResources();
        bBitmapLoaded = true;
    }

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(mainSizer);

    m_banner4 = new wxBannerWindow(this, wxID_ANY, wxBOTTOM, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                                   wxBORDER_THEME);
    m_banner4->SetBitmap(wxNullBitmap);
    m_banner4->SetText(_("Implement inherited virtual functions"),
                       _("Select from the list below the functions that you want to override in your class"));
    m_banner4->SetGradient(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION),
                           wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));
    m_banner4->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT));

    mainSizer->Add(m_banner4, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* bSizer4 = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(bSizer4, 0, wxTOP | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    m_staticText2 =
        new wxStaticText(this, wxID_ANY, _("File:"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    bSizer4->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_VERTICAL, WXC_FROM_DIP(5));

    m_textCtrlImplFile =
        new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_textCtrlImplFile->SetToolTip(_("Generate the functions in this filename"));
#if wxVERSION_NUMBER >= 3000
    m_textCtrlImplFile->SetHint(wxT(""));
#endif

    bSizer4->Add(m_textCtrlImplFile, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxBoxSizer* boxSizer6 = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(boxSizer6, 1, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_dvListCtrl = new clThemedListCtrl(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)),
                                        wxDV_ROW_LINES | wxDV_SINGLE);

    boxSizer6->Add(m_dvListCtrl, 1, wxEXPAND, WXC_FROM_DIP(5));

    m_dvListCtrl->AppendTextColumn(_("Function"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                   wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrl->AppendTextColumn(_("Visibility"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                   wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrl->AppendTextColumn(_("Virtual"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                   wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrl->AppendTextColumn(_("Override"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                   wxDATAVIEW_COL_RESIZABLE);
    m_dvListCtrl->AppendTextColumn(_("Document"), wxDATAVIEW_CELL_INERT, WXC_FROM_DIP(-2), wxALIGN_LEFT,
                                   wxDATAVIEW_COL_RESIZABLE);
    wxBoxSizer* boxSizer8 = new wxBoxSizer(wxVERTICAL);

    boxSizer6->Add(boxSizer8, 0, wxEXPAND, WXC_FROM_DIP(5));

    m_button10 = new wxButton(this, wxID_ANY, _("Check all"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizer8->Add(m_button10, 0, wxLEFT | wxRIGHT | wxBOTTOM | wxEXPAND, WXC_FROM_DIP(5));

    m_button12 = new wxButton(this, wxID_ANY, _("Uncheck all"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    boxSizer8->Add(m_button12, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    wxStaticBoxSizer* sbSizer1 = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, _("Options:")), wxVERTICAL);

    mainSizer->Add(sbSizer1, 0, wxALL | wxEXPAND, WXC_FROM_DIP(5));

    m_checkBoxFormat = new wxCheckBox(this, wxID_ANY, _("Format text after insertion"), wxDefaultPosition,
                                      wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_checkBoxFormat->SetValue(false);

    sbSizer1->Add(m_checkBoxFormat, 0, wxALL, WXC_FROM_DIP(5));

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(buttonSizer, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, WXC_FROM_DIP(5));

    m_buttonOk = new wxButton(this, wxID_OK, _("&OK"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);
    m_buttonOk->SetDefault();

    buttonSizer->Add(m_buttonOk, 0, wxALL, WXC_FROM_DIP(5));

    m_buttonCancel =
        new wxButton(this, wxID_CANCEL, _("&Cancel"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    buttonSizer->Add(m_buttonCancel, 0, wxALL, WXC_FROM_DIP(5));

    SetName(wxT("ImplementParentVirtualFunctionsBase"));
    SetSize(wxDLG_UNIT(this, wxSize(-1, -1)));
    if(GetSizer()) {
        GetSizer()->Fit(this);
    }
    if(GetParent()) {
        CentreOnParent(wxBOTH);
    } else {
        CentreOnScreen(wxBOTH);
    }
#if wxVERSION_NUMBER >= 2900
    if(!wxPersistenceManager::Get().Find(this)) {
        wxPersistenceManager::Get().RegisterAndRestore(this);
    } else {
        wxPersistenceManager::Get().Restore(this);
    }
#endif
    // Connect events
    m_button10->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                        wxCommandEventHandler(ImplementParentVirtualFunctionsBase::OnCheckAll), NULL, this);
    m_button12->Connect(wxEVT_COMMAND_BUTTON_CLICKED,
                        wxCommandEventHandler(ImplementParentVirtualFunctionsBase::OnUnCheckAll), NULL, this);
}

ImplementParentVirtualFunctionsBase::~ImplementParentVirtualFunctionsBase()
{
    m_button10->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                           wxCommandEventHandler(ImplementParentVirtualFunctionsBase::OnCheckAll), NULL, this);
    m_button12->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,
                           wxCommandEventHandler(ImplementParentVirtualFunctionsBase::OnUnCheckAll), NULL, this);
}
