/***************************************************************
 * Name:      OpenEagle_flightgear_navMain.cpp
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

#include "OpenEagle_flightgear_navMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEagle_flightgear_navFrame)
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

//(*IdInit(OpenEagle_flightgear_navFrame)
const long OpenEagle_flightgear_navFrame::ID_STATICTEXT1 = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_STATICTEXT2 = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_STATICTEXT3 = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_TEXTCTRL_NASR_NAV_TXT = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_TEXTCTRL_FLIGHTGEAR_NAV_PATH = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_BUTTON_NASR_NAV_TXT = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_BUTTON_SELECT_FLIGHTGEAR_NAV_PATH = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_BUTTON_GENERATE_FLIGHTGEAR_NAV_FILE = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_PANEL1 = wxNewId();
const long OpenEagle_flightgear_navFrame::idMenuQuit = wxNewId();
const long OpenEagle_flightgear_navFrame::idMenuAbout = wxNewId();
const long OpenEagle_flightgear_navFrame::ID_STATUSBAR_OpenEagle_flightgear_nav = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagle_flightgear_navFrame,wxFrame)
    //(*EventTable(OpenEagle_flightgear_navFrame)
    //*)
END_EVENT_TABLE()

OpenEagle_flightgear_navFrame::OpenEagle_flightgear_navFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagle_flightgear_navFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar_OpenEagle_flightgear_nav;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(950,350));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(120,96), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("            OpenEagle_flightgear_nav\n(generate replacement using NASR data)"), wxPoint(300,20), wxSize(500,70), 0, _T("ID_STATICTEXT1"));
    wxFont StaticText1Font(18,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText1->SetFont(StaticText1Font);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("NASR\nnav.txt"), wxPoint(10,95), wxSize(65,50), 0, _T("ID_STATICTEXT2"));
    wxFont StaticText2Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("flightgear\nnav path"), wxPoint(10,170), wxSize(100,50), 0, _T("ID_STATICTEXT3"));
    wxFont StaticText3Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    TextCtrl_NASR_nav_txt = new wxTextCtrl(Panel1, ID_TEXTCTRL_NASR_NAV_TXT, _("Text"), wxPoint(140,100), wxSize(700,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_NASR_NAV_TXT"));
    wxFont TextCtrl_NASR_nav_txtFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrl_NASR_nav_txt->SetFont(TextCtrl_NASR_nav_txtFont);
    TextCtrl_flightgear_nav_path = new wxTextCtrl(Panel1, ID_TEXTCTRL_FLIGHTGEAR_NAV_PATH, _("Text"), wxPoint(140,180), wxSize(700,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FLIGHTGEAR_NAV_PATH"));
    wxFont TextCtrl_flightgear_nav_pathFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrl_flightgear_nav_path->SetFont(TextCtrl_flightgear_nav_pathFont);
    Button_NASR_nav_txt = new wxButton(Panel1, ID_BUTTON_NASR_NAV_TXT, _("Select"), wxPoint(850,100), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NASR_NAV_TXT"));
    wxFont Button_NASR_nav_txtFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_NASR_nav_txt->SetFont(Button_NASR_nav_txtFont);
    Button_Select_flightgear_nav_path = new wxButton(Panel1, ID_BUTTON_SELECT_FLIGHTGEAR_NAV_PATH, _("Select"), wxPoint(850,180), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SELECT_FLIGHTGEAR_NAV_PATH"));
    wxFont Button_Select_flightgear_nav_pathFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_Select_flightgear_nav_path->SetFont(Button_Select_flightgear_nav_pathFont);
    Button_Generate_flightgear_nav_file = new wxButton(Panel1, ID_BUTTON_GENERATE_FLIGHTGEAR_NAV_FILE, _("Generate flightgear nav file (existing will be renamed with retirement date prefix)"), wxPoint(140,240), wxSize(780,40), 0, wxDefaultValidator, _T("ID_BUTTON_GENERATE_FLIGHTGEAR_NAV_FILE"));
    wxFont Button_Generate_flightgear_nav_fileFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_Generate_flightgear_nav_file->SetFont(Button_Generate_flightgear_nav_fileFont);
    MenuBar_OpenEagle_flightgear_nav = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar_OpenEagle_flightgear_nav->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar_OpenEagle_flightgear_nav->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar_OpenEagle_flightgear_nav);
    StatusBar_OpenEagle_flightgear_nav = new wxStatusBar(this, ID_STATUSBAR_OpenEagle_flightgear_nav, 0, _T("ID_STATUSBAR_OpenEagle_flightgear_nav"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar_OpenEagle_flightgear_nav->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar_OpenEagle_flightgear_nav->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar_OpenEagle_flightgear_nav);
    FileDialog_File_Select = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    DirDialog_Select_Path = new wxDirDialog(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));

    Connect(ID_BUTTON_NASR_NAV_TXT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_flightgear_navFrame::OnButton_NASR_nav_txtClick);
    Connect(ID_BUTTON_SELECT_FLIGHTGEAR_NAV_PATH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_flightgear_navFrame::OnButton_Select_flightgear_nav_pathClick);
    Connect(ID_BUTTON_GENERATE_FLIGHTGEAR_NAV_FILE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagle_flightgear_navFrame::OnButton_Generate_flightgear_nav_fileClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagle_flightgear_navFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagle_flightgear_navFrame::OnAbout);
    //*)
}

OpenEagle_flightgear_navFrame::~OpenEagle_flightgear_navFrame()
{
    //(*Destroy(OpenEagle_flightgear_navFrame)
    //*)
}

void OpenEagle_flightgear_navFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagle_flightgear_navFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagle_flightgear_navFrame::OnButton_NASR_nav_txtClick(wxCommandEvent& event)
{
  if (FileDialog_File_Select->ShowModal() == wxID_CANCEL) return;
  TextCtrl_NASR_nav_txt->SetValue(FileDialog_File_Select->GetPath());//
}

void OpenEagle_flightgear_navFrame::OnButton_Select_flightgear_nav_pathClick(wxCommandEvent& event)
{
  if (DirDialog_Select_Path->ShowModal() == wxID_CANCEL) return;
  TextCtrl_flightgear_nav_path->SetValue(DirDialog_Select_Path->GetPath());
}

void OpenEagle_flightgear_navFrame::OnButton_Generate_flightgear_nav_fileClick(wxCommandEvent& event)
{
  read_NASR_NAV_data();
  generate_flightgear_NAV_data();
}

void OpenEagle_flightgear_navFrame::read_NASR_NAV_data()
{
  printf("read_NASR_NAV_data()\n");
  APT.read_NASR_nav_data((char *)TextCtrl_NASR_nav_txt->GetValue().ToStdString().c_str());
}

void OpenEagle_flightgear_navFrame::generate_flightgear_NAV_data()
{
  APT.generate_flightgear_nav_dat((char *)TextCtrl_flightgear_nav_path->GetValue().ToStdString().c_str());
}
