/***************************************************************
 * Name:      OpenEaglePlayBackMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-06-20
 * Copyright: Philip Cobbin (www.cobbin.com)
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

#include "OpenEaglePlayBackMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEaglePlayBackFrame)
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

//(*IdInit(OpenEaglePlayBackFrame)
const long OpenEaglePlayBackFrame::ID_STATICTEXT_OPEN_EAGLE_PLAY_BACK = wxNewId();
const long OpenEaglePlayBackFrame::ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE = wxNewId();
const long OpenEaglePlayBackFrame::ID_BUTTON_SELECT = wxNewId();
const long OpenEaglePlayBackFrame::ID_STATICTEXT_PATH = wxNewId();
const long OpenEaglePlayBackFrame::ID_TEXTCTRL_PATH = wxNewId();
const long OpenEaglePlayBackFrame::ID_BUTTON_PLAY_BACK = wxNewId();
const long OpenEaglePlayBackFrame::ID_CHOICE_SPEED = wxNewId();
const long OpenEaglePlayBackFrame::ID_STATICTEXT_SPEED = wxNewId();
const long OpenEaglePlayBackFrame::ID_PANEL1 = wxNewId();
const long OpenEaglePlayBackFrame::idMenuQuit = wxNewId();
const long OpenEaglePlayBackFrame::idMenuAbout = wxNewId();
const long OpenEaglePlayBackFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEaglePlayBackFrame,wxFrame)
    //(*EventTable(OpenEaglePlayBackFrame)
    //*)
END_EVENT_TABLE()

OpenEaglePlayBackFrame::OpenEaglePlayBackFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEaglePlayBackFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("OpenEagle Playback"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1200,300));
    PanelOpenEaglePlayBack = new wxPanel(this, ID_PANEL1, wxPoint(240,160), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StaticTextOpenEaglePlayBack = new wxStaticText(PanelOpenEaglePlayBack, ID_STATICTEXT_OPEN_EAGLE_PLAY_BACK, _("OpenEagle PlayBack"), wxPoint(20,20), wxSize(330,50), 0, _T("ID_STATICTEXT_OPEN_EAGLE_PLAY_BACK"));
    wxFont StaticTextOpenEaglePlayBackFont(24,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextOpenEaglePlayBack->SetFont(StaticTextOpenEaglePlayBackFont);
    TextCtrlOpenEagleExtFile = new wxTextCtrl(PanelOpenEaglePlayBack, ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE, _("Text"), wxPoint(20,80), wxSize(1050,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE"));
    wxFont TextCtrlOpenEagleExtFileFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlOpenEagleExtFile->SetFont(TextCtrlOpenEagleExtFileFont);
    ButtonSelect = new wxButton(PanelOpenEaglePlayBack, ID_BUTTON_SELECT, _("Select"), wxPoint(1080,80), wxSize(100,40), 0, wxDefaultValidator, _T("ID_BUTTON_SELECT"));
    wxFont ButtonSelectFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSelect->SetFont(ButtonSelectFont);
    StaticTextPath = new wxStaticText(PanelOpenEaglePlayBack, ID_STATICTEXT_PATH, _("Path"), wxPoint(20,140), wxSize(60,30), 0, _T("ID_STATICTEXT_PATH"));
    wxFont StaticTextPathFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextPath->SetFont(StaticTextPathFont);
    TextCtrlPath = new wxTextCtrl(PanelOpenEaglePlayBack, ID_TEXTCTRL_PATH, _("Text"), wxPoint(80,130), wxSize(1050,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_PATH"));
    ButtonPlayBack = new wxButton(PanelOpenEaglePlayBack, ID_BUTTON_PLAY_BACK, _("Playback"), wxPoint(480,180), wxSize(120,40), 0, wxDefaultValidator, _T("ID_BUTTON_PLAY_BACK"));
    wxFont ButtonPlayBackFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonPlayBack->SetFont(ButtonPlayBackFont);
    ChoiceSpeed = new wxChoice(PanelOpenEaglePlayBack, ID_CHOICE_SPEED, wxPoint(720,180), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE_SPEED"));
    ChoiceSpeed->Append(_("1/10x"));
    ChoiceSpeed->Append(_("1/2x"));
    ChoiceSpeed->SetSelection( ChoiceSpeed->Append(_("1x")) );
    StaticTextSpeed = new wxStaticText(PanelOpenEaglePlayBack, ID_STATICTEXT_SPEED, _("Speed"), wxPoint(640,185), wxSize(60,30), 0, _T("ID_STATICTEXT_SPEED"));
    wxFont StaticTextSpeedFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextSpeed->SetFont(StaticTextSpeedFont);
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

//    Connect(ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEaglePlayBackFrame::OnTextCtrl1Text);
    Connect(ID_BUTTON_SELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEaglePlayBackFrame::OnButtonSelectClick);
    Connect(ID_BUTTON_PLAY_BACK,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEaglePlayBackFrame::OnButtonPlayBackClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEaglePlayBackFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEaglePlayBackFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&OpenEaglePlayBackFrame::OnClose);
    //*)
}

OpenEaglePlayBackFrame::~OpenEaglePlayBackFrame()
{
    //(*Destroy(OpenEaglePlayBackFrame)
    //*)
}

void OpenEaglePlayBackFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEaglePlayBackFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEaglePlayBackFrame::OnClose(wxCloseEvent& event)
{
}

void OpenEaglePlayBackFrame::OnButtonSelectClick(wxCommandEvent& event)
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

    ButtonPlayBack->Show(true);

  }
  else {
    if (ret != wxID_CANCEL ) {
      TextCtrlOpenEagleExtFile->SetValue("");
      TextCtrlPath->Show(false);
      StaticTextPath->Show(false);
      ButtonPlayBack->Show(false);
    }
  }
}

void OpenEaglePlayBackFrame::OnButtonPlayBackClick(wxCommandEvent& event)
{
  printf("Playback button...\n");
  std::string path = TextCtrlPath->GetValue().ToStdString();
  std::string fn = TextCtrlOpenEagleExtFile->GetValue().ToStdString();
  Playback.PlayBackSpeed = ChoiceSpeed->GetSelection();

  /// (1) open socket connection to flightgear, if success continue, otherwise message issue and return;
  bool socket_opened = Playback.open_socket(PORT_OPENEAGLEEXT,&Playback.OpenEagleExtsockfd);
  if (!socket_opened) {
    printf("could not open socket to flightgear for G5 protocol\n");
    return;
  }
  printf("Playback.OpenEagleExtsockfd %d\n",Playback.OpenEagleExtsockfd);
  Playback.sendOpenEagleExtProtocol = true;
  Playback.OpenOpenEagleExtFile(path,fn);
  Playback.SendOpenEagleExtProtocol();
}
