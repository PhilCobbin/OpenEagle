/***************************************************************
 * Name:      OpenEagle_crm114Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2022-01-30
 * Copyright: Philip Cobbin (cobbin.com)
 * License:   GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later versio
 *
 * This library is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public Lice
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 **************************************************************/

#include "OpenEagle_crm114Main.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEagle_crm114Frame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(OpenEagle_crm114Frame)
const long OpenEagle_crm114Frame::ID_STATICTEXT_OPEN_EAGLE_CRM114 = wxNewId();
const long OpenEagle_crm114Frame::ID_STATICTEXT_EXTRACT_NOTE = wxNewId();
const long OpenEagle_crm114Frame::ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE = wxNewId();
const long OpenEagle_crm114Frame::ID_BUTTON_SELECT = wxNewId();
const long OpenEagle_crm114Frame::ID_BUTTON_Extract = wxNewId();
const long OpenEagle_crm114Frame::ID_TEXTCTRL_PATH = wxNewId();
const long OpenEagle_crm114Frame::ID_STATICTEXT_PATH = wxNewId();
const long OpenEagle_crm114Frame::ID_PANEL_CRM114 = wxNewId();
const long OpenEagle_crm114Frame::idMenuQuit = wxNewId();
const long OpenEagle_crm114Frame::idMenuAbout = wxNewId();
const long OpenEagle_crm114Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagle_crm114Frame,wxFrame)
    //(*EventTable(OpenEagle_crm114Frame)
    //*)
END_EVENT_TABLE()

OpenEagle_crm114Frame::OpenEagle_crm114Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagle_crm114Frame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("OpenEagle CRM114"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1200,300));
    PanelCRM114 = new wxPanel(this, ID_PANEL_CRM114, wxPoint(1,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CRM114"));
    StaticText_OpenEagleCRM114 = new wxStaticText(PanelCRM114, ID_STATICTEXT_OPEN_EAGLE_CRM114, _("OpenEagle CRM114"), wxPoint(20,20), wxSize(370,50), 0, _T("ID_STATICTEXT_OPEN_EAGLE_CRM114"));
    wxFont StaticText_OpenEagleCRM114Font(24,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText_OpenEagleCRM114->SetFont(StaticText_OpenEagleCRM114Font);
    StaticText1 = new wxStaticText(PanelCRM114, ID_STATICTEXT_EXTRACT_NOTE, _("Extract OpenEagleExt files by code prefix(es)"), wxPoint(440,30), wxSize(510,30), 0, _T("ID_STATICTEXT_EXTRACT_NOTE"));
    wxFont StaticText1Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    TextCtrlOpenEagleExtFile = new wxTextCtrl(PanelCRM114, ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE, _("Text"), wxPoint(20,80), wxSize(1050,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE"));
    wxFont TextCtrlOpenEagleExtFileFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlOpenEagleExtFile->SetFont(TextCtrlOpenEagleExtFileFont);
    ButtonSelect = new wxButton(PanelCRM114, ID_BUTTON_SELECT, _("Select"), wxPoint(1080,80), wxSize(100,40), 0, wxDefaultValidator, _T("ID_BUTTON_SELECT"));
    wxFont ButtonSelectFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSelect->SetFont(ButtonSelectFont);
    ButtonExtract = new wxButton(PanelCRM114, ID_BUTTON_Extract, _("Extract"), wxPoint(20,200), wxSize(120,40), 0, wxDefaultValidator, _T("ID_BUTTON_Extract"));
    ButtonExtract->Hide();
    wxFont ButtonExtractFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonExtract->SetFont(ButtonExtractFont);
    TextCtrlPath = new wxTextCtrl(PanelCRM114, ID_TEXTCTRL_PATH, _("Text"), wxPoint(80,130), wxSize(1100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_PATH"));
    TextCtrlPath->Hide();
    wxFont TextCtrlPathFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlPath->SetFont(TextCtrlPathFont);
    StaticTextPath = new wxStaticText(PanelCRM114, ID_STATICTEXT_PATH, _("Path"), wxPoint(20,140), wxSize(60,30), 0, _T("ID_STATICTEXT_PATH"));
    StaticTextPath->Hide();
    wxFont StaticTextPathFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextPath->SetFont(StaticTextPathFont);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FileDialogSelectFlightHistory = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagle_crm114Frame::OnTextCtrlOpenEagleExtFileText);
    Connect(ID_BUTTON_SELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_crm114Frame::OnButtonSelectClick);
    Connect(ID_BUTTON_Extract,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_crm114Frame::OnButtonExtractClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagle_crm114Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagle_crm114Frame::OnAbout);
    //*)

}

OpenEagle_crm114Frame::~OpenEagle_crm114Frame()
{
    //(*Destroy(OpenEagle_crm114Frame)
    //*)
}

void OpenEagle_crm114Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagle_crm114Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagle_crm114Frame::OnButtonSelectClick(wxCommandEvent& event)
{
  FileDialogSelectFlightHistory->SetWildcard("*.OpenEagleExt");
  int ret = FileDialogSelectFlightHistory->ShowModal();
  if (ret == wxID_OK ) {
    std::string flight_history_file = "";
    std::string path;
    std::string full_path;
    flight_history_file = FileDialogSelectFlightHistory->GetFilename();
    full_path =FileDialogSelectFlightHistory->GetPath();
    long unsigned int i = full_path.rfind("/",full_path.length());
    if (i != std::string::npos) {
      path = full_path.substr(0,i+1);
    }
    else {
      printf("no path?");
    }

    TextCtrlOpenEagleExtFile->SetValue(flight_history_file.c_str());
    TextCtrlPath->SetValue(path.c_str());

    TextCtrlPath->Show(true);
    StaticTextPath->Show(true);

    ButtonExtract->Show(true);

  }
  else {
    if (ret != wxID_CANCEL ) {
      TextCtrlOpenEagleExtFile->SetValue("");
      TextCtrlPath->Show(false);
      StaticTextPath->Show(false);
      ButtonExtract->Show(false);
    }
  }
}

void OpenEagle_crm114Frame::OnTextCtrlOpenEagleExtFileText(wxCommandEvent& event)
{
}

void OpenEagle_crm114Frame::OnButtonExtractClick(wxCommandEvent& event)
{
  printf("Extract button...\n");
  std::string path = TextCtrlPath->GetValue().ToStdString();
  std::string fn = TextCtrlOpenEagleExtFile->GetValue().ToStdString();
  crm114.DecodeCRM114files(path, fn);  /// builds a file list
  printf("have DecodeCRM114file(...)\n");

  crm114.extractDecodedFileData();
//  printf("n = %d\n",n);
}
