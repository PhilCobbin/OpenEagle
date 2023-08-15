/***************************************************************
 * Name:      OpenEagle_flightgear_fixMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-07-11
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

#include "OpenEagle_flightgear_fixMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEagle_flightgear_fixFrame)
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

//(*IdInit(OpenEagle_flightgear_fixFrame)
const long OpenEagle_flightgear_fixFrame::ID_STATICTEXT_OPENEAGLE_FLIGHTGEAR_FIX = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_TEXTCTRL_NASR_FIX_TXT = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_BUTTON_SELECT_NASR_FIX_TXT = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_STATICTEXT_NASR_FIX_TXT = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_STATICTEXT_FLIGHTGEAR_FIX_PATH = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_TEXTCTRL_FLIGHTGEAR_FIX_PATH = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_BUTTON_SELECT_FLIGHTGEAR_FIX_PATH = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_BUTTON_GENERATE_FLIGHTGEAR_FIX_FILE = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_PANEL_OPENEAGLE_FLIGHTGEAR_FIX = wxNewId();
const long OpenEagle_flightgear_fixFrame::idMenuQuit = wxNewId();
const long OpenEagle_flightgear_fixFrame::idMenuAbout = wxNewId();
const long OpenEagle_flightgear_fixFrame::ID_STATUSBAR_OPEN_EAGLE_FLIGHTGEAR_STATUS_BAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagle_flightgear_fixFrame,wxFrame)
    //(*EventTable(OpenEagle_flightgear_fixFrame)
    //*)
END_EVENT_TABLE()

OpenEagle_flightgear_fixFrame::OpenEagle_flightgear_fixFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagle_flightgear_fixFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar_OpenEagle_flightgear_fix;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("OpenEagle_flightgear_fix"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(950,350));
    Panel_OpenEagle_flightgear_fix = new wxPanel(this, ID_PANEL_OPENEAGLE_FLIGHTGEAR_FIX, wxPoint(0,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_OPENEAGLE_FLIGHTGEAR_FIX"));
    StaticText_OpenEagle_flightgear_fix = new wxStaticText(Panel_OpenEagle_flightgear_fix, ID_STATICTEXT_OPENEAGLE_FLIGHTGEAR_FIX, _("            OpenEagle_flightgear_fix\n(generate replacement using NASR data)"), wxPoint(300,20), wxSize(500,70), 0, _T("ID_STATICTEXT_OPENEAGLE_FLIGHTGEAR_FIX"));
    wxFont StaticText_OpenEagle_flightgear_fixFont(18,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText_OpenEagle_flightgear_fix->SetFont(StaticText_OpenEagle_flightgear_fixFont);
    TextCtrl_NASR_fix_txt = new wxTextCtrl(Panel_OpenEagle_flightgear_fix, ID_TEXTCTRL_NASR_FIX_TXT, _("Text"), wxPoint(140,100), wxSize(700,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_NASR_FIX_TXT"));
    wxFont TextCtrl_NASR_fix_txtFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrl_NASR_fix_txt->SetFont(TextCtrl_NASR_fix_txtFont);
    Button_NASR_fix_txt = new wxButton(Panel_OpenEagle_flightgear_fix, ID_BUTTON_SELECT_NASR_FIX_TXT, _("Select"), wxPoint(850,100), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SELECT_NASR_FIX_TXT"));
    wxFont Button_NASR_fix_txtFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_NASR_fix_txt->SetFont(Button_NASR_fix_txtFont);
    StaticText_NASR_fix_txt = new wxStaticText(Panel_OpenEagle_flightgear_fix, ID_STATICTEXT_NASR_FIX_TXT, _("NASR\nfix.txt"), wxPoint(10,95), wxSize(60,50), 0, _T("ID_STATICTEXT_NASR_FIX_TXT"));
    wxFont StaticText_NASR_fix_txtFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText_NASR_fix_txt->SetFont(StaticText_NASR_fix_txtFont);
    StaticText_flightgear_fix_path = new wxStaticText(Panel_OpenEagle_flightgear_fix, ID_STATICTEXT_FLIGHTGEAR_FIX_PATH, _("flightgear\nfix path"), wxPoint(10,170), wxSize(100,50), 0, _T("ID_STATICTEXT_FLIGHTGEAR_FIX_PATH"));
    wxFont StaticText_flightgear_fix_pathFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText_flightgear_fix_path->SetFont(StaticText_flightgear_fix_pathFont);
    TextCtrl_flightgear_fix_path = new wxTextCtrl(Panel_OpenEagle_flightgear_fix, ID_TEXTCTRL_FLIGHTGEAR_FIX_PATH, _("Text"), wxPoint(140,180), wxSize(700,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FLIGHTGEAR_FIX_PATH"));
    wxFont TextCtrl_flightgear_fix_pathFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrl_flightgear_fix_path->SetFont(TextCtrl_flightgear_fix_pathFont);
    Button_Select_flightgear_fix_path = new wxButton(Panel_OpenEagle_flightgear_fix, ID_BUTTON_SELECT_FLIGHTGEAR_FIX_PATH, _("Select"), wxPoint(850,180), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SELECT_FLIGHTGEAR_FIX_PATH"));
    wxFont Button_Select_flightgear_fix_pathFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_Select_flightgear_fix_path->SetFont(Button_Select_flightgear_fix_pathFont);
    Button_Generate_flightgear_fix_file = new wxButton(Panel_OpenEagle_flightgear_fix, ID_BUTTON_GENERATE_FLIGHTGEAR_FIX_FILE, _("Generate flightgear fix file (existing will be renamed with retirement date prefix)"), wxPoint(140,240), wxSize(760,40), 0, wxDefaultValidator, _T("ID_BUTTON_GENERATE_FLIGHTGEAR_FIX_FILE"));
    wxFont Button_Generate_flightgear_fix_fileFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_Generate_flightgear_fix_file->SetFont(Button_Generate_flightgear_fix_fileFont);
    MenuBar_OpenEagle_flightgear_fix = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar_OpenEagle_flightgear_fix->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar_OpenEagle_flightgear_fix->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar_OpenEagle_flightgear_fix);
    StatusBar_OpenEagle_flightgear_fix = new wxStatusBar(this, ID_STATUSBAR_OPEN_EAGLE_FLIGHTGEAR_STATUS_BAR, 0, _T("ID_STATUSBAR_OPEN_EAGLE_FLIGHTGEAR_STATUS_BAR"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar_OpenEagle_flightgear_fix->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar_OpenEagle_flightgear_fix->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar_OpenEagle_flightgear_fix);
    FileDialog_File_Select = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    DirDialog_Select_Path = new wxDirDialog(this, _("Select path"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));

    Connect(ID_BUTTON_SELECT_NASR_FIX_TXT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_flightgear_fixFrame::OnButton_NASR_fix_txtClick);
    Connect(ID_BUTTON_SELECT_FLIGHTGEAR_FIX_PATH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_flightgear_fixFrame::OnButton_Select_flightgear_fix_pathClick);
    Connect(ID_BUTTON_GENERATE_FLIGHTGEAR_FIX_FILE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_flightgear_fixFrame::OnButton_Generate_flightgear_fix_fileClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagle_flightgear_fixFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagle_flightgear_fixFrame::OnAbout);
    //*)
}

OpenEagle_flightgear_fixFrame::~OpenEagle_flightgear_fixFrame()
{
    //(*Destroy(OpenEagle_flightgear_fixFrame)
    //*)
}

void OpenEagle_flightgear_fixFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagle_flightgear_fixFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagle_flightgear_fixFrame::OnButton_NASR_fix_txtClick(wxCommandEvent& event)
{
  if (FileDialog_File_Select->ShowModal() == wxID_CANCEL) return;
  TextCtrl_NASR_fix_txt->SetValue(FileDialog_File_Select->GetPath());//              ->GetFilename());
}

void OpenEagle_flightgear_fixFrame::OnButton_Select_flightgear_fix_pathClick(wxCommandEvent& event)
{
  if (DirDialog_Select_Path->ShowModal() == wxID_CANCEL) return;
  TextCtrl_flightgear_fix_path->SetValue(DirDialog_Select_Path->GetPath());
}

void OpenEagle_flightgear_fixFrame::OnButton_Generate_flightgear_fix_fileClick(wxCommandEvent& event)
{
  read_NASR_fix_data();
  generate_flightgear_fix_data();

}

void OpenEagle_flightgear_fixFrame::read_NASR_fix_data()
{
  printf("read_NASR_fix_data()\n");

  APT.read_NASR_fix_data((char *)TextCtrl_NASR_fix_txt->GetValue().ToStdString().c_str());
}

void OpenEagle_flightgear_fixFrame::generate_flightgear_fix_data()
{
  printf("generate_flightgear_fix_data");
  APT.generate_flightgear_fix_dat((char *)TextCtrl_flightgear_fix_path->GetValue().ToStdString().c_str());

}
