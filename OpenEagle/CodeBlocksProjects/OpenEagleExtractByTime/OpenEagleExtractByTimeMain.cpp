/***************************************************************
 * Name:      OpenEagleExtractByTimeMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-06-18
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

#include "OpenEagleExtractByTimeMain.h"
#include <wx/msgdlg.h>
#include "../data_mgr/data_mgr.hxx"

//(*InternalHeaders(OpenEagleExtractByTimeFrame)
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

//(*IdInit(OpenEagleExtractByTimeFrame)
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_OPEN_EAGLE_EXTRACT_BY_TIME = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_BUTTON_SELECT = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_Path = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_PATH = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_BUTTON_EXTRACT = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_FROM = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_FROM_HOUR = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_FROM_HOUR = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_FROM_MINUTE = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_FROM_MINUTE = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_FROM_SECOND = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_FROM_SECOND = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_TO = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_TO_HOUR = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_TO_MINUTE = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_TO_SECOND = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_TO_HOUR = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_TO_MINUTE = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_TO_SECOND = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_CHECKBOX_SET_PREFIX_1 = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATICTEXT_CRM114_PREFIX = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_TEXTCTRL_PREFIX_1 = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_PANEL_EXTRACT_BY_TIME = wxNewId();
const long OpenEagleExtractByTimeFrame::idMenuQuit = wxNewId();
const long OpenEagleExtractByTimeFrame::idMenuAbout = wxNewId();
const long OpenEagleExtractByTimeFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagleExtractByTimeFrame,wxFrame)
    //(*EventTable(OpenEagleExtractByTimeFrame)
    //*)
END_EVENT_TABLE()

OpenEagleExtractByTimeFrame::OpenEagleExtractByTimeFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagleExtractByTimeFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1200,300));
    PanelExtractByTime = new wxPanel(this, ID_PANEL_EXTRACT_BY_TIME, wxPoint(1,0), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_EXTRACT_BY_TIME"));
    StaticTextOpenEagleExtractByTime = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_OPEN_EAGLE_EXTRACT_BY_TIME, _("OpenEagle Extract by Time"), wxPoint(40,32), wxSize(470,50), 0, _T("ID_STATICTEXT_OPEN_EAGLE_EXTRACT_BY_TIME"));
    wxFont StaticTextOpenEagleExtractByTimeFont(24,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextOpenEagleExtractByTime->SetFont(StaticTextOpenEagleExtractByTimeFont);
    TextCtrlOpenEagleExtFile = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE, _("Text"), wxPoint(20,80), wxSize(1050,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE"));
    ButtonSelect = new wxButton(PanelExtractByTime, ID_BUTTON_SELECT, _("Select"), wxPoint(1080,80), wxSize(100,40), 0, wxDefaultValidator, _T("ID_BUTTON_SELECT"));
    wxFont ButtonSelectFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSelect->SetFont(ButtonSelectFont);
    StaticTextPath = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_Path, _("Path"), wxPoint(20,140), wxSize(60,30), 0, _T("ID_STATICTEXT_Path"));
    wxFont StaticTextPathFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextPath->SetFont(StaticTextPathFont);
    TextCtrlPath = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_PATH, _("Text"), wxPoint(80,130), wxSize(1100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_PATH"));
    ButtonExtract = new wxButton(PanelExtractByTime, ID_BUTTON_EXTRACT, _("Extract"), wxPoint(20,200), wxSize(120,40), 0, wxDefaultValidator, _T("ID_BUTTON_EXTRACT"));
    wxFont ButtonExtractFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonExtract->SetFont(ButtonExtractFont);
    StaticTextFrom = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_FROM, _("From"), wxPoint(200,205), wxSize(60,30), 0, _T("ID_STATICTEXT_FROM"));
    wxFont StaticTextFromFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextFrom->SetFont(StaticTextFromFont);
    TextCtrlFromHour = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_FROM_HOUR, _("Text"), wxPoint(260,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FROM_HOUR"));
    wxFont TextCtrlFromHourFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFromHour->SetFont(TextCtrlFromHourFont);
    StaticTextFromHour = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_FROM_HOUR, _("Hour"), wxPoint(280,175), wxDefaultSize, 0, _T("ID_STATICTEXT_FROM_HOUR"));
    TextCtrlFromMinute = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_FROM_MINUTE, _("Text"), wxPoint(360,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FROM_MINUTE"));
    wxFont TextCtrlFromMinuteFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFromMinute->SetFont(TextCtrlFromMinuteFont);
    StaticTextFromMinute = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_FROM_MINUTE, _("Minute"), wxPoint(370,175), wxDefaultSize, 0, _T("ID_STATICTEXT_FROM_MINUTE"));
    TextCtrlFromSecond = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_FROM_SECOND, _("Text"), wxPoint(460,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FROM_SECOND"));
    wxFont TextCtrlFromSecondFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFromSecond->SetFont(TextCtrlFromSecondFont);
    StaticTextFromSecond = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_FROM_SECOND, _("Second"), wxPoint(470,175), wxDefaultSize, 0, _T("ID_STATICTEXT_FROM_SECOND"));
    StaticTextTo = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_TO, _("To"), wxPoint(560,205), wxSize(30,30), 0, _T("ID_STATICTEXT_TO"));
    wxFont StaticTextToFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextTo->SetFont(StaticTextToFont);
    TextCtrlToHour = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_TO_HOUR, _("Text"), wxPoint(600,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_TO_HOUR"));
    wxFont TextCtrlToHourFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlToHour->SetFont(TextCtrlToHourFont);
    TextCtrlToMinute = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_TO_MINUTE, _("Text"), wxPoint(700,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_TO_MINUTE"));
    wxFont TextCtrlToMinuteFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlToMinute->SetFont(TextCtrlToMinuteFont);
    TextCtrlToSecond = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_TO_SECOND, _("Text"), wxPoint(800,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_TO_SECOND"));
    wxFont TextCtrlToSecondFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlToSecond->SetFont(TextCtrlToSecondFont);
    StaticTextToHour = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_TO_HOUR, _("Hour"), wxPoint(620,175), wxDefaultSize, 0, _T("ID_STATICTEXT_TO_HOUR"));
    StaticTextToMinute = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_TO_MINUTE, _("Minute"), wxPoint(710,175), wxDefaultSize, 0, _T("ID_STATICTEXT_TO_MINUTE"));
    StaticTextToSecond = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_TO_SECOND, _("Second"), wxPoint(810,175), wxDefaultSize, 0, _T("ID_STATICTEXT_TO_SECOND"));
    CheckBoxSetPrefix1 = new wxCheckBox(PanelExtractByTime, ID_CHECKBOX_SET_PREFIX_1, _("Set Prefix 1"), wxPoint(890,205), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_SET_PREFIX_1"));
    CheckBoxSetPrefix1->SetValue(false);
    StaticTextCRM114Prefix = new wxStaticText(PanelExtractByTime, ID_STATICTEXT_CRM114_PREFIX, _("CRM114 Prefix 1"), wxPoint(1000,176), wxDefaultSize, 0, _T("ID_STATICTEXT_CRM114_PREFIX"));
    TextCtrlPrefix1 = new wxTextCtrl(PanelExtractByTime, ID_TEXTCTRL_PREFIX_1, _("Text"), wxPoint(1000,200), wxSize(75,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_PREFIX_1"));
    wxFont TextCtrlPrefix1Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlPrefix1->SetFont(TextCtrlPrefix1Font);
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

    Connect(ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagleExtractByTimeFrame::OnTextCtrl1Text);
    Connect(ID_BUTTON_SELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleExtractByTimeFrame::OnButtonSelectClick);
    Connect(ID_BUTTON_EXTRACT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleExtractByTimeFrame::OnButtonExtractClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleExtractByTimeFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleExtractByTimeFrame::OnAbout);
    //*)
}

OpenEagleExtractByTimeFrame::~OpenEagleExtractByTimeFrame()
{
    //(*Destroy(OpenEagleExtractByTimeFrame)
    //*)
}

void OpenEagleExtractByTimeFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagleExtractByTimeFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagleExtractByTimeFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void OpenEagleExtractByTimeFrame::OnButton1Click(wxCommandEvent& event)
{
}

void OpenEagleExtractByTimeFrame::OnButtonExtractClick(wxCommandEvent& event)
{
  set_parameters();
  ExtractByTimeRange();
}

void OpenEagleExtractByTimeFrame::OnButtonSelectClick(wxCommandEvent& event)
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
//      TextCtrlOpenEagleExtFile->SetValue("");
      TextCtrlPath->Show(false);
      StaticTextPath->Show(false);
      ButtonExtract->Show(false);
    }
  }
}

void OpenEagleExtractByTimeFrame::set_parameters()
{
  start_hr =     std::strtod(TextCtrlFromHour->GetValue(),NULL);
  start_minute = std::strtod(TextCtrlFromMinute->GetValue(),NULL);
  start_second = std::strtod(TextCtrlFromSecond->GetValue(),NULL);
  end_hr =       std::strtod(TextCtrlToHour->GetValue(),NULL);
  end_minute =   std::strtod(TextCtrlToMinute->GetValue(),NULL);
  end_second =   std::strtod(TextCtrlToSecond->GetValue(),NULL);
  /// want all of last second so extract to first record after end_second
  int second = end_second;
  int minute = end_minute;
  second++;
  if (second > 59) {
    second = 0;
    minute++;
  }
  if (minute >59) {
    minute = 0;
  }
  end_second = second;
  end_minute = minute;
  if (CheckBoxSetPrefix1->IsChecked()) first_prefix = std::strtod(TextCtrlPrefix1->GetValue(),NULL);
}

unsigned long  OpenEagleExtractByTimeFrame::find_time_record(double hour, double minute, double second)
{
//  printf("find_time_record(hour %f, minute %f, second %f)\n",hour, minute, second);
  bool done = false;
  DM.current_data = DM.first_data;
  while (!done) {
  ///  printf("hour %d minute %d second %d\n",int(DM.current_data->data.G5UTChour),int(DM.current_data->data.G5UTCminute),int(DM.current_data->data.G5UTCsecond));
    if ( int(DM.current_data->data.G5UTChour) == int(hour) ) {
      if (int(DM.current_data->data.G5UTCminute) == int(minute) )  {
        if ( int(DM.current_data->data.G5UTCsecond) == int(second) ) {
         // printf("return record_nbr %lu\n",DM.current_data->record_nbr);
          return DM.current_data->record_nbr;
        }
      }
    }
    if (DM.current_data->next_data != NULL) DM.current_data = DM.current_data->next_data;
    else return 0;
  }
  return 0;
}

void OpenEagleExtractByTimeFrame::read_data_to_decoded_DataList(FILE * fp)
{
 /// printf("read_data_to_decoded_DataList(fp)\n");
  record_nbr = 0;

  DM.first_data = NULL;
  DM.current_data = NULL;
  DM.last_data = NULL;

  bool done = false;
  while (!done) {
    int nread = fread(&data,sizeof( data_mgr::OpenEagleExtData ),1,fp);
    if (nread == 1) {
      record_nbr++;
      DM.current_data = DM.get_new_data();
      DM.current_data->data = data;
      DM.current_data->record_nbr = record_nbr;
      if (DM.first_data == NULL) {
       // printf("n==1, first\n");
        DM.first_data = DM.current_data;
        DM.last_data = DM.current_data;
        DM.first_data = DM.current_data;
        ///if (first_data != NULL) printf("first_data != NULL"); else printf("first_data == NULL?\n");
      }
      else {
      ///  printf("record_nbr %lu, new end node\n",record_nbr);
        DM.current_data->last_data = DM.last_data;
        DM.last_data ->next_data = DM.current_data;
        DM.last_data = DM.current_data;
      }
    }
    else {
    //  printf("read to EOF? nread %d\n",nread);
      done = true;
      fclose(fp);
   ///   errorEOF = true;
    }
  }

}

void OpenEagleExtractByTimeFrame::writeExtractFile(FILE * fp)
{
 // printf("writeExtractFile(fp)\n");
  DM.current_data = DM.first_data;
 /// printf("first record_nbr %lu\n",DM.current_data->record_nbr);
  unsigned long int n = end_record_nbr - start_record_nbr;
///  printf("start_record_nbr %lu end_record_nbr %lu\n",start_record_nbr, end_record_nbr);
///  printf("unsigned long int n %lu\n",n);
  long unsigned int dataSize = sizeof (DM.OpenEagleExt);
///  printf("for loop to first record\n");
  for (unsigned long int i = 1; i < start_record_nbr; i++) {
 //   printf("skipping record_nbr %lu\n",DM.current_data->record_nbr);
    DM.current_data = DM.current_data->next_data;
  }
///  printf("for loop for n %lu records\n",n);
  for (unsigned long int i = 0; i<n; i++) {
   /// printf("write extract data: record_nbr %lu\n", DM.current_data->record_nbr);
    fwrite(&DM.current_data->data, dataSize,1,fp);
    if (DM.current_data->next_data != NULL) DM.current_data = DM.current_data->next_data;
  }
  DM.destroy_data();
  fclose (fp);
}

void OpenEagleExtractByTimeFrame::ExtractByTimeRange()
{
  std::string file_name = TextCtrlOpenEagleExtFile->GetValue().ToStdString();
  std::string path = TextCtrlPath->GetValue().ToStdString();

  std::string full_file_name = path;
  full_file_name += file_name.c_str();
 /// printf("full_file_name: [%s]\n",full_file_name.c_str());

  FILE * fp = fopen(full_file_name.c_str(),"rb");
  if (fp == NULL) {
    printf("unable to open [%s]\n",full_file_name.c_str());
    return;
  }

  read_data_to_decoded_DataList(fp);  // will fclose(fp);

  start_record_nbr = find_time_record(start_hr,start_minute, start_second);
  end_record_nbr   = find_time_record(end_hr,end_minute, end_second);
///  printf(" start record %lu end record %lu\n",start_record_nbr, end_record_nbr);
  unsigned long int sum = start_record_nbr * end_record_nbr;
  if (sum == 0) {
    printf(" could not find one or more records\n");
    return;
  }

  std::string ranged_file_name;
  ranged_file_name = TextCtrlFromHour->GetValue().ToStdString();
  ranged_file_name += "-";
  ranged_file_name += TextCtrlFromMinute->GetValue().ToStdString();
  ranged_file_name += "-";
  ranged_file_name += TextCtrlFromSecond->GetValue().ToStdString();
  ranged_file_name += "-to-";
  ranged_file_name += TextCtrlToHour->GetValue().ToStdString();
  ranged_file_name += "-";
  ranged_file_name += TextCtrlToMinute->GetValue().ToStdString();
  ranged_file_name += "-";
  ranged_file_name += TextCtrlToSecond->GetValue().ToStdString();
  ranged_file_name += "-";
  ranged_file_name += file_name.c_str();
  std::string full_ranged_file_name = path.c_str();
  full_ranged_file_name +=ranged_file_name.c_str();

 /// printf("full_ranged_file_name: [%s]\n",full_ranged_file_name.c_str());

  fp = fopen(full_ranged_file_name.c_str(),"w");
  if (fp == NULL) {
    printf("unable to open full_ranged_file_name:[%s]\n",full_ranged_file_name.c_str());
    return;
  }
  writeExtractFile(fp);
}

