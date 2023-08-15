/***************************************************************
 * Name:      OpenEagleProcessShapefilesMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2022-07-02
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

#include "OpenEagleProcessShapefilesMain.h"
#include "../system_io/system_io.hxx"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEagleProcessShapefilesFrame)
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

//(*IdInit(OpenEagleProcessShapefilesFrame)
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_AIRPORT_FILENAME = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_FILENAME = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_APT_TXT = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_BOUNDARY_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_CLASS_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_CLASS_AIRSPACE = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_BOUNDARY_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_BOUNDARY_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_SPECIAL_USE_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_SPECIAL_USE_AIRSPACE_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_SPECIAL_USE_AIRSPACE_FILENAME = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_PATH_TO_MODELS_AND_OBJECTS = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_MODELS_AND_OBJECTS_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_PROCESS_CLASS_AIRSPACE = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_PROCESS_BOUNDARY_AIRSPACE = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_PROCESS_SPECIAL_USE_AIRSPACE = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_AIRPORT_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_APT_PATH = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_PROCESS_APT_SIGNS = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_AIRPORT_FILENAME = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_NASR_APT_TXT = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT_PROGRAM_OPENEAGLE_CLASS_AIRSPACE = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_TEXTCTRL_ClassAirspacePath = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_NASR_APT_TXT = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICLINE1 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT1 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT3 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT4 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICLINE2 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT5 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT6 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_SPECIAL_USE_FILENAME = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICLINE3 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICLINE4 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_BUTTON_LOOKUP_OPENEAGLEAIRPORTSIGNS = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICLINE5 = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATICTEXT7 = wxNewId();
const long OpenEagleProcessShapefilesFrame::TextCtrlModelsAndObjectsPath = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_PANEL1 = wxNewId();
const long OpenEagleProcessShapefilesFrame::idMenuQuit = wxNewId();
const long OpenEagleProcessShapefilesFrame::idMenuAbout = wxNewId();
const long OpenEagleProcessShapefilesFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagleProcessShapefilesFrame,wxFrame)
    //(*EventTable(OpenEagleProcessShapefilesFrame)
    //*)
END_EVENT_TABLE()

OpenEagleProcessShapefilesFrame::OpenEagleProcessShapefilesFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagleProcessShapefilesFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("OpenEagleProcessShapefiles"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1200,900));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(80,30), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    TextCtrlAirportFilename = new wxTextCtrl(Panel1, ID_TEXTCTRL_AIRPORT_FILENAME, _("TEXT"), wxPoint(200,680), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_AIRPORT_FILENAME"));
    TextCtrlSpecialUseAirspaceFilename = new wxTextCtrl(Panel1, ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_FILENAME, _("Text"), wxPoint(200,540), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_FILENAME"));
    TextCtrl_APT_TXT = new wxTextCtrl(Panel1, ID_TEXTCTRL_APT_TXT, _("Text"), wxPoint(200,640), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_APT_TXT"));
    TextCtrlSpecialUseAirspacePath = new wxTextCtrl(Panel1, ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_PATH, _("Text"), wxPoint(200,500), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_PATH"));
    TextCtrlBoundaryAirspacePath = new wxTextCtrl(Panel1, ID_TEXTCTRL_BOUNDARY_AIRSPACE_PATH, _("Text"), wxPoint(200,360), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_BOUNDARY_AIRSPACE_PATH"));
    StaticTextClassAirspacePath = new wxStaticText(Panel1, ID_STATICTEXT_CLASS_AIRSPACE_PATH, _("Shape_Files path"), wxPoint(20,180), wxSize(120,20), 0, _T("ID_STATICTEXT_CLASS_AIRSPACE_PATH"));
    ButtonLookupClassAirspace = new wxButton(Panel1, ID_BUTTON_LOOKUP_CLASS_AIRSPACE, _("Lookup"), wxPoint(1105,170), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_CLASS_AIRSPACE"));
    StaticTextBoundaryAirspacePath = new wxStaticText(Panel1, ID_STATICTEXT_BOUNDARY_AIRSPACE_PATH, _("Boundary Airspace Path"), wxPoint(20,360), wxSize(180,20), 0, _T("ID_STATICTEXT_BOUNDARY_AIRSPACE_PATH"));
    ButtonLookupBoundaryAirspacePath = new wxButton(Panel1, ID_BUTTON_LOOKUP_BOUNDARY_AIRSPACE_PATH, _("lookup"), wxPoint(1105,360), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_BOUNDARY_AIRSPACE_PATH"));
    StaticTextSpecialUseAirspacePath = new wxStaticText(Panel1, ID_STATICTEXT_SPECIAL_USE_AIRSPACE_PATH, _("Special Use Airspace Path"), wxPoint(20,500), wxSize(180,20), 0, _T("ID_STATICTEXT_SPECIAL_USE_AIRSPACE_PATH"));
    ButtonLookupSpecialUseAirspacePath = new wxButton(Panel1, ID_BUTTON_LOOKUP_SPECIAL_USE_AIRSPACE_PATH, _("Lookup"), wxPoint(1105,500), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_SPECIAL_USE_AIRSPACE_PATH"));
    StaticTextSpecialUseAirspaceFilename = new wxStaticText(Panel1, ID_STATICTEXT_SPECIAL_USE_AIRSPACE_FILENAME, _("Program: OpenEagleSua"), wxPoint(20,550), wxSize(180,20), 0, _T("ID_STATICTEXT_SPECIAL_USE_AIRSPACE_FILENAME"));
    StaticTextPathToModelsAndObjects = new wxStaticText(Panel1, ID_STATICTEXT_PATH_TO_MODELS_AND_OBJECTS, _("Path to write \nMODELS and OBJECTS"), wxPoint(20,40), wxDefaultSize, 0, _T("ID_STATICTEXT_PATH_TO_MODELS_AND_OBJECTS"));
    ButtonLookupModelsAndObjectsPath = new wxButton(Panel1, ID_BUTTON_LOOKUP_MODELS_AND_OBJECTS_PATH, _("Lookup"), wxPoint(1105,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_MODELS_AND_OBJECTS_PATH"));
    ButtonProcessClassAirspace = new wxButton(Panel1, ID_BUTTON_PROCESS_CLASS_AIRSPACE, _("Process"), wxPoint(16,260), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_PROCESS_CLASS_AIRSPACE"));
    ButtonProcessBoundaryAirspace = new wxButton(Panel1, ID_BUTTON_PROCESS_BOUNDARY_AIRSPACE, _("Process"), wxPoint(20,390), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_PROCESS_BOUNDARY_AIRSPACE"));
    ButtonProcessSpecialUseAirspace = new wxButton(Panel1, ID_BUTTON_PROCESS_SPECIAL_USE_AIRSPACE, _("Process"), wxPoint(20,580), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_PROCESS_SPECIAL_USE_AIRSPACE"));
    StaticTextAirportPath = new wxStaticText(Panel1, ID_STATICTEXT_AIRPORT_PATH, _("Airport date: apt.txt"), wxPoint(20,640), wxDefaultSize, 0, _T("ID_STATICTEXT_AIRPORT_PATH"));
    ButtonLookupAptPath = new wxButton(Panel1, ID_BUTTON_LOOKUP_APT_PATH, _("Lookup"), wxPoint(1105,640), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_APT_PATH"));
    ButtonProcessAptSigns = new wxButton(Panel1, ID_BUTTON_PROCESS_APT_SIGNS, _("Process"), wxPoint(20,720), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_PROCESS_APT_SIGNS"));
    StaticTextAirportFilename = new wxStaticText(Panel1, ID_STATICTEXT_AIRPORT_FILENAME, _("Program:\nOpenEagleAirportSigns"), wxPoint(20,680), wxDefaultSize, 0, _T("ID_STATICTEXT_AIRPORT_FILENAME"));
    TextCtrl_NASR_APT_txt = new wxTextCtrl(Panel1, ID_TEXTCTRL_NASR_APT_TXT, _("Text"), wxPoint(200,210), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_NASR_APT_TXT"));
    StaticText_program_OpenEagle_class_airspace = new wxStaticText(Panel1, ID_STATICTEXT_PROGRAM_OPENEAGLE_CLASS_AIRSPACE, _("NASR:\nAPT.txt "), wxPoint(20,210), wxSize(180,40), 0, _T("ID_STATICTEXT_PROGRAM_OPENEAGLE_CLASS_AIRSPACE"));
    TextCtrlClassAirspacePath = new wxTextCtrl(Panel1, ID_TEXTCTRL_ClassAirspacePath, _("Text"), wxPoint(200,170), wxSize(900,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_ClassAirspacePath"));
    ButtonLookupNASR_APT_txt = new wxButton(Panel1, ID_BUTTON_NASR_APT_TXT, _("Lookup"), wxPoint(1105,210), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_NASR_APT_TXT"));
    StaticLine1 = new wxStaticLine(Panel1, ID_STATICLINE1, wxPoint(20,300), wxSize(1150,5), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Download from: https://www.faa.gov/air_traffic/flight_info/aeronav/Aero_Data/NASR_Subscription/"), wxPoint(200,150), wxSize(680,20), 0, _T("ID_STATICTEXT1"));
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Download: https://ais-faa.opendata.arcgis.com/datasets/67885972e4e940b2aa6d74024901c561_0\?geometry=99.844%2C-88.438%2C-99.844%2C88.438"), wxPoint(20,310), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("Download: https://adds-faa.opendata.arcgis.com/datasets/67885972e4e940b2aa6d74024901c561_0\?geometry=99.844%2C-88.438%2C-99.844%2C88.438"), wxPoint(20,330), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticLine2 = new wxStaticLine(Panel1, ID_STATICLINE2, wxPoint(20,430), wxSize(1150,5), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    StaticText5 = new wxStaticText(Panel1, ID_STATICTEXT5, _("Download: https://ais-faa.opendata.arcgis.com/datasets/dd0d1b726e504137ab3c41b21835d05b_0\?geometry=27.853%2C7.409%2C-22.069%2C78.288"), wxPoint(24,444), wxDefaultSize, 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(Panel1, ID_STATICTEXT6, _("Download: https://adds-faa.opendata.arcgis.com/datasets/dd0d1b726e504137ab3c41b21835d05b_0\?geometry=27.853%2C7.409%2C-22.069%2C78.288"), wxPoint(24,468), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    Button_lookup_special_use_filename = new wxButton(Panel1, ID_BUTTON_LOOKUP_SPECIAL_USE_FILENAME, _("Lookup"), wxPoint(1105,540), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_SPECIAL_USE_FILENAME"));
    StaticLine3 = new wxStaticLine(Panel1, ID_STATICLINE3, wxPoint(20,620), wxSize(1150,5), wxLI_HORIZONTAL, _T("ID_STATICLINE3"));
    StaticLine4 = new wxStaticLine(Panel1, ID_STATICLINE4, wxPoint(20,760), wxSize(1150,5), wxLI_HORIZONTAL, _T("ID_STATICLINE4"));
    Button_lookup_OpenEagleAirportSigns = new wxButton(Panel1, ID_BUTTON_LOOKUP_OPENEAGLEAIRPORTSIGNS, _("Lookup"), wxPoint(1105,680), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_OPENEAGLEAIRPORTSIGNS"));
    StaticLine5 = new wxStaticLine(Panel1, ID_STATICLINE5, wxPoint(20,140), wxSize(1150,5), wxLI_HORIZONTAL, _T("ID_STATICLINE5"));
    StaticText7 = new wxStaticText(Panel1, ID_STATICTEXT7, _("OpenEagleProcessShapefiles"), wxPoint(350,5), wxSize(350,30), 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    TextCtrl_models_and_objects_path = new wxTextCtrl(Panel1, TextCtrlModelsAndObjectsPath, _("Text"), wxPoint(200,40), wxSize(900,30), 0, wxDefaultValidator, _T("TextCtrlModelsAndObjectsPath"));
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
    DirDialogSelectDirectory = new wxDirDialog(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    FileDialogSelectFile = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_TEXTCTRL_BOUNDARY_AIRSPACE_PATH,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnTextCtrlBoundaryAirspacePathText);
    Connect(ID_BUTTON_LOOKUP_CLASS_AIRSPACE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonLookupClassAirspaceClick);
    Connect(ID_BUTTON_LOOKUP_BOUNDARY_AIRSPACE_PATH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonLookupBoundaryAirspacePathClick);
    Connect(ID_BUTTON_LOOKUP_SPECIAL_USE_AIRSPACE_PATH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonLookupSpecialUseAirspacePathClick);
    Connect(ID_BUTTON_LOOKUP_MODELS_AND_OBJECTS_PATH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonLookupModelsAndObjectsPathClick);
    Connect(ID_BUTTON_PROCESS_CLASS_AIRSPACE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonProcessClassAirspaceClick);
    Connect(ID_BUTTON_PROCESS_BOUNDARY_AIRSPACE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonProcessBoundaryAirspaceClick);
    Connect(ID_BUTTON_PROCESS_SPECIAL_USE_AIRSPACE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonProcessSpecialUseAirspaceClick);
    Connect(ID_BUTTON_LOOKUP_APT_PATH,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonLookupAptPathClick);
    Connect(ID_BUTTON_PROCESS_APT_SIGNS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonProcessAptSignsClick);
    Connect(ID_BUTTON_NASR_APT_TXT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButtonLookupNASR_APT_txtClick);
    Connect(ID_BUTTON_LOOKUP_SPECIAL_USE_FILENAME,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButton_lookup_special_use_filenameClick);
    Connect(ID_BUTTON_LOOKUP_OPENEAGLEAIRPORTSIGNS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnButton_lookup_OpenEagleAirportSignsClick);
    Connect(TextCtrlModelsAndObjectsPath,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnTextCtrl_models_and_objects_pathText);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleProcessShapefilesFrame::OnAbout);
    //*)

//    bool paths_ok = paths.setupOpenEaglePaths();
//    if (!paths_ok) {
//      printf("Warning: could not locate a valid set of paths in home/.OpenEagle directory\n");
//      exit(1);
//    }
//    else printf("paths.setupOpenEaglePaths() call successful");
}

OpenEagleProcessShapefilesFrame::~OpenEagleProcessShapefilesFrame()
{
    //(*Destroy(OpenEagleProcessShapefilesFrame)
    DirDialogSelectDirectory->Destroy();
    FileDialogSelectFile->Destroy();
    //*)
}

void OpenEagleProcessShapefilesFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagleProcessShapefilesFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagleProcessShapefilesFrame::OnButtonLookupClassAirspaceClick(wxCommandEvent& event)
{
  DirDialogSelectDirectory->ShowModal();
  TextCtrlClassAirspacePath->SetValue(DirDialogSelectDirectory->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnButtonLookupBoundaryAirspacePathClick(wxCommandEvent& event)
{
  DirDialogSelectDirectory->ShowModal();
  TextCtrlBoundaryAirspacePath->SetValue(DirDialogSelectDirectory->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnButtonLookupSpecialUseAirspacePathClick(wxCommandEvent& event)
{
  DirDialogSelectDirectory->ShowModal();
  TextCtrlSpecialUseAirspacePath->SetValue(DirDialogSelectDirectory->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnButtonLookupModelsAndObjectsPathClick(wxCommandEvent& event)
{
  DirDialogSelectDirectory->ShowModal();
  TextCtrl_models_and_objects_path->SetValue(DirDialogSelectDirectory->GetPath());

  paths.setupOpenEaglePaths("OpenEagleProcessShapefiles",(char *)DirDialogSelectDirectory->GetPath().ToStdString().c_str());
  //TextCtrlModelsAndObjectsPath
  //->SetValue(DirDialogSelectDirectory->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnButtonWriteModelsAndObjectsForFlightgearClick(wxCommandEvent& event)
{

}

void OpenEagleProcessShapefilesFrame::OnButtonLookupAptPathClick(wxCommandEvent& event)
{
  FileDialogSelectFile->ShowModal();
  TextCtrl_APT_TXT->SetValue(FileDialogSelectFile->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnButtonProcessAptSignsClick(wxCommandEvent& event)
{
    airport apt(&paths);
    apt.read_NASR_apt_dat((char *)TextCtrl_APT_TXT->GetValue().ToStdString().c_str());
    apt.generate_airport_files();
}

void OpenEagleProcessShapefilesFrame::OnButtonProcessClassAirspaceClick(wxCommandEvent& event)
{
  printf("OnButtonProcessClassAirspaceClick(   )\n");
  airport apt(&paths);
  apt.terminal_io = true;
  apt.read_NASR_apt_dat((char *)TextCtrl_NASR_APT_txt->GetValue().ToStdString().c_str());
 ///apt.read_airport_data();
  printf("OnButtonProcessClassAirspaceClick(...):: read)_NASR_apt_dat(...) completed\n");
  class_airspace airspace(&apt,&paths);  /// apt needed for lookup of field elevation.
  printf("OnButtonProcessClassAirspaceClick(...):: created airspace(&apt)\n");

  char * models_and_objects_path = (char *)TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str();
  char * shapefile_path          = (char *)TextCtrlBoundaryAirspacePath->GetValue().ToStdString().c_str();

  printf("OnButtonProcessClassAirspaceClick(...)\n     models_and_objects_path [%s]\n     shapefile_path [%s]\n",
         TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str(),
         TextCtrlClassAirspacePath->GetValue().ToStdString().c_str());
  airspace.read_dbf((char *)TextCtrlClassAirspacePath->GetValue().ToStdString().c_str());
  airspace.read_shp((char *)TextCtrlClassAirspacePath->GetValue().ToStdString().c_str());
  airspace.write_NASR_class_airspace(true);//,paths);

}

void OpenEagleProcessShapefilesFrame::OnButtonProcessBoundaryAirspaceClick(wxCommandEvent& event)
{
    /**
  std::string command = "";
  command += paths.OpenEagleUpdate_UpdateProgramsPath.c_str();
  command += "/OpenEagleSata\n";
  system_io(&command);
  **/
  printf("OnButtonProcessBoundaryAirspaceClick(...)\n");
  printf("OpenEagleSata built using the C shapelib version 1.5.0\n");

  class airspace_boundary boundary_airspace(&paths);

 /// airspace.initialize_sata_path();
  char * models_and_objects_path = (char *)TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str();
  char * shapefile_path          = (char *)TextCtrlBoundaryAirspacePath->GetValue().ToStdString().c_str();
  printf("OnButtonProcessBoundaryAirspaceClick(...)\n     models_and_objects_path [%s]\n     shapefile_path [%s]\n",
         TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str(),
         TextCtrlClassAirspacePath->GetValue().ToStdString().c_str());
 // return;
  boundary_airspace.read_dbf((char *)TextCtrlBoundaryAirspacePath->GetValue().ToStdString().c_str());
  boundary_airspace.read_shp((char *)TextCtrlBoundaryAirspacePath->GetValue().ToStdString().c_str());
  boundary_airspace.write_boundary_airspace(true); //,(char *)TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str());
}

void OpenEagleProcessShapefilesFrame::OnButtonProcessSpecialUseAirspaceClick(wxCommandEvent& event)
{
    /**
  std::string command = "";
  command += paths.OpenEagleUpdate_UpdateProgramsPath.c_str();
  command += "/OpenEagleSua\n";
  system_io(&command);
**/
  printf("OpenEagleSua built using the C shapelib version 1.5.0\n");
  sua_airspace Sua_airspace(&paths);

  char * models_and_objects_path = (char *)TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str();
  char * shapefile_path          = (char *)TextCtrlBoundaryAirspacePath->GetValue().ToStdString().c_str();
  printf("OnButtonProcessSpecialUseAirspaceClick(...)\n     models_and_objects_path [%s]\n     shapefile_path [%s]\n",
         TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str(),
         TextCtrlSpecialUseAirspacePath->GetValue().ToStdString().c_str());

  Sua_airspace.read_dbf((char *)TextCtrlSpecialUseAirspacePath->GetValue().ToStdString().c_str());
  Sua_airspace.read_shp((char *)TextCtrlSpecialUseAirspacePath->GetValue().ToStdString().c_str());

  Sua_airspace.write_sua_airspace(true); //,(char *)TextCtrl_models_and_objects_path->GetValue().ToStdString().c_str());



}


void OpenEagleProcessShapefilesFrame::OnButtonLookupUpdateProgramsPathClick(wxCommandEvent& event)
{
  DirDialogSelectDirectory->ShowModal();
//  TextCtrlPathToUpdatePrograms->SetValue(DirDialogSelectDirectory->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnTextCtrlClassAirspacePathText(wxCommandEvent& event)
{
}


void OpenEagleProcessShapefilesFrame::OnTextCtrlBoundaryAirspacePathText(wxCommandEvent& event)
{
}

void OpenEagleProcessShapefilesFrame::OnButton_lookup_special_use_filenameClick(wxCommandEvent& event)
{
  FileDialogSelectFile->ShowModal();
  TextCtrlSpecialUseAirspaceFilename->SetValue(FileDialogSelectFile->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnButton_lookup_OpenEagleAirportSignsClick(wxCommandEvent& event)
{
  FileDialogSelectFile->ShowModal();
  TextCtrlAirportFilename->SetValue(FileDialogSelectFile->GetPath());
}

void OpenEagleProcessShapefilesFrame::OnTextCtrl_models_and_objects_pathText(wxCommandEvent& event)
{
}

void OpenEagleProcessShapefilesFrame::OnButtonLookupNASR_APT_txtClick(wxCommandEvent& event)
{
    FileDialogSelectFile->ShowModal();
    TextCtrl_NASR_APT_txt->SetValue(FileDialogSelectFile->GetPath());
}


