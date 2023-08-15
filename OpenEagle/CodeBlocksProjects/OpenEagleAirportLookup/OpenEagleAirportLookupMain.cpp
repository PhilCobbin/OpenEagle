/***************************************************************
 * Name:      OpenEagleAirportLookupMain.cpp
 * Purpose:   Code for Application Frame for OpenEagleAirportLookup tool (NASR database related to airports)
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2021-02-05
 * Copyright: Philip Cobbin (cobbin.com)
 * License    GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
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

#include "OpenEagleAirportLookupMain.h"
#include "../data_conversion/data_conversion.hxx"

#include <wx/msgdlg.h>
//#include <wx/dirdlg.h>
//(*InternalHeaders(OpenEagleAirportLookupFrame)
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

//(*IdInit(OpenEagleAirportLookupFrame)
const long OpenEagleAirportLookupFrame::ID_TEXTCTRL_AIRPORT_ID = wxNewId();
const long OpenEagleAirportLookupFrame::ID_BUTTON_LOOKUP_BY_STATE = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_AIRPORT = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_SEE_FAA_DOT_GOV = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_28_DAY_NASR = wxNewId();
const long OpenEagleAirportLookupFrame::ID_TEXTCTRL_ICAO_ID = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_ICAO_ID = wxNewId();
const long OpenEagleAirportLookupFrame::ID_TEXTCTRL_APT_NAME = wxNewId();
const long OpenEagleAirportLookupFrame::ID_TEXTCTRL_APT_CITY_STATE = wxNewId();
const long OpenEagleAirportLookupFrame::ID_TEXTCTRL_APT_ELEVATION = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_ELEVATION = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_TP_ALTITUDE = wxNewId();
const long OpenEagleAirportLookupFrame::ID_TEXTCTRL_TP_ALT = wxNewId();
const long OpenEagleAirportLookupFrame::ID_BUTTON_APT_INFORMATION = wxNewId();
const long OpenEagleAirportLookupFrame::ID_BUTTON_APT_FREQUENCIES = wxNewId();
const long OpenEagleAirportLookupFrame::ID_LISTBOX_APT_RUNWAY = wxNewId();
const long OpenEagleAirportLookupFrame::ID_STATICTEXT_RUNWAYS = wxNewId();
const long OpenEagleAirportLookupFrame::ID_CHECKBOX_DO_FULL_NASR = wxNewId();
const long OpenEagleAirportLookupFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagleAirportLookupFrame,wxFrame)
    //(*EventTable(OpenEagleAirportLookupFrame)
    //*)
END_EVENT_TABLE()

OpenEagleAirportLookupFrame::OpenEagleAirportLookupFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagleAirportLookupFrame)
    Create(parent, wxID_ANY, _("Lookup Airport/Runway Information"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(670,360));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(136,8), wxSize(565,210), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    TextCtrlAirport_ID = new wxTextCtrl(Panel1, ID_TEXTCTRL_AIRPORT_ID, _("FLG"), wxPoint(128,30), wxSize(80,40), wxTE_PROCESS_ENTER, wxDefaultValidator, _T("ID_TEXTCTRL_AIRPORT_ID"));
    wxFont TextCtrlAirport_IDFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    TextCtrlAirport_ID->SetFont(TextCtrlAirport_IDFont);
    Button_LookupByState = new wxButton(Panel1, ID_BUTTON_LOOKUP_BY_STATE, _("Lookup by State"), wxPoint(230,30), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_BY_STATE"));
    Button_LookupByState->SetMinSize(wxSize(250,40));
    wxFont Button_LookupByStateFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    Button_LookupByState->SetFont(Button_LookupByStateFont);
    StaticTextAirport = new wxStaticText(Panel1, ID_STATICTEXT_AIRPORT, _("Airport"), wxPoint(10,30), wxDefaultSize, 0, _T("ID_STATICTEXT_AIRPORT"));
    StaticTextAirport->SetMinSize(wxSize(120,40));
    wxFont StaticTextAirportFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    StaticTextAirport->SetFont(StaticTextAirportFont);
    StaticText_Note_SeeFAA_Dot_Gov = new wxStaticText(Panel1, ID_STATICTEXT_SEE_FAA_DOT_GOV, _("https://www.faa.gov/air_traffic/flight_info/aeronav/aero_data/NASR_Subscription/\n"), wxPoint(8,8), wxSize(560,20), 0, _T("ID_STATICTEXT_SEE_FAA_DOT_GOV"));
    StaticText_22_Day_NASR = new wxStaticText(Panel1, ID_STATICTEXT_28_DAY_NASR, _("28 Day NASR Subscription"), wxPoint(488,40), wxDefaultSize, 0, _T("ID_STATICTEXT_28_DAY_NASR"));
    TextCtrl_ICAO_ID = new wxTextCtrl(Panel1, ID_TEXTCTRL_ICAO_ID, _("KFLG"), wxPoint(110,75), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_ICAO_ID"));
    TextCtrl_ICAO_ID->Disable();
    TextCtrl_ICAO_ID->Hide();
    wxFont TextCtrl_ICAO_IDFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    TextCtrl_ICAO_ID->SetFont(TextCtrl_ICAO_IDFont);
    StaticText_ICAO_ID = new wxStaticText(Panel1, ID_STATICTEXT_ICAO_ID, _("ICAO"), wxPoint(10,75), wxSize(70,40), 0, _T("ID_STATICTEXT_ICAO_ID"));
    StaticText_ICAO_ID->SetMinSize(wxSize(100,40));
    StaticText_ICAO_ID->Disable();
    StaticText_ICAO_ID->Hide();
    wxFont StaticText_ICAO_IDFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    StaticText_ICAO_ID->SetFont(StaticText_ICAO_IDFont);
    TextCtrl_Apt_Name = new wxTextCtrl(Panel1, ID_TEXTCTRL_APT_NAME, _("Flagstaff Pulliam"), wxPoint(10,130), wxSize(630,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_APT_NAME"));
    TextCtrl_Apt_Name->Disable();
    TextCtrl_Apt_Name->Hide();
    wxFont TextCtrl_Apt_NameFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    TextCtrl_Apt_Name->SetFont(TextCtrl_Apt_NameFont);
    TextCtrl_AptCitySt = new wxTextCtrl(Panel1, ID_TEXTCTRL_APT_CITY_STATE, _("Flagstaff, AZ"), wxPoint(10,180), wxSize(300,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_APT_CITY_STATE"));
    TextCtrl_AptCitySt->Disable();
    TextCtrl_AptCitySt->Hide();
    wxFont TextCtrl_AptCityStFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    TextCtrl_AptCitySt->SetFont(TextCtrl_AptCityStFont);
    TextCtrl_Apt_Elevation = new wxTextCtrl(Panel1, ID_TEXTCTRL_APT_ELEVATION, _("7015"), wxPoint(170,230), wxSize(120,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_APT_ELEVATION"));
    TextCtrl_Apt_Elevation->Disable();
    TextCtrl_Apt_Elevation->Hide();
    wxFont TextCtrl_Apt_ElevationFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    TextCtrl_Apt_Elevation->SetFont(TextCtrl_Apt_ElevationFont);
    StaticText_Elevation = new wxStaticText(Panel1, ID_STATICTEXT_ELEVATION, _("Elevation"), wxPoint(8,240), wxSize(150,40), 0, _T("ID_STATICTEXT_ELEVATION"));
    StaticText_Elevation->SetMinSize(wxSize(150,30));
    StaticText_Elevation->Disable();
    StaticText_Elevation->Hide();
    wxFont StaticText_ElevationFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    StaticText_Elevation->SetFont(StaticText_ElevationFont);
    StaticText_TP_Altitude = new wxStaticText(Panel1, ID_STATICTEXT_TP_ALTITUDE, _("T.P.\nAltitude"), wxPoint(10,280), wxSize(120,100), 0, _T("ID_STATICTEXT_TP_ALTITUDE"));
    StaticText_TP_Altitude->SetMinSize(wxSize(140,60));
    StaticText_TP_Altitude->Disable();
    StaticText_TP_Altitude->Hide();
    wxFont StaticText_TP_AltitudeFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    StaticText_TP_Altitude->SetFont(StaticText_TP_AltitudeFont);
    TextCtrl_TP_Alt = new wxTextCtrl(Panel1, ID_TEXTCTRL_TP_ALT, _("8000"), wxPoint(170,285), wxSize(120,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_TP_ALT"));
    TextCtrl_TP_Alt->Disable();
    TextCtrl_TP_Alt->Hide();
    wxFont TextCtrl_TP_AltFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    TextCtrl_TP_Alt->SetFont(TextCtrl_TP_AltFont);
    ButtonAptInformation = new wxButton(Panel1, ID_BUTTON_APT_INFORMATION, _("Information"), wxPoint(350,250), wxSize(200,40), 0, wxDefaultValidator, _T("ID_BUTTON_APT_INFORMATION"));
    ButtonAptInformation->Disable();
    ButtonAptInformation->Hide();
    wxFont ButtonAptInformationFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    ButtonAptInformation->SetFont(ButtonAptInformationFont);
    ButtonAptFrequencies = new wxButton(Panel1, ID_BUTTON_APT_FREQUENCIES, _("Frequencies"), wxPoint(350,300), wxSize(200,40), 0, wxDefaultValidator, _T("ID_BUTTON_APT_FREQUENCIES"));
    ButtonAptFrequencies->Disable();
    ButtonAptFrequencies->Hide();
    wxFont ButtonAptFrequenciesFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    ButtonAptFrequencies->SetFont(ButtonAptFrequenciesFont);
    ListBoxAptRunway = new wxListBox(Panel1, ID_LISTBOX_APT_RUNWAY, wxPoint(590,180), wxSize(70,160), 0, 0, wxLB_SINGLE|wxVSCROLL, wxDefaultValidator, _T("ID_LISTBOX_APT_RUNWAY"));
    ListBoxAptRunway->SetSelection( ListBoxAptRunway->Append(_("99X")) );
    ListBoxAptRunway->Disable();
    ListBoxAptRunway->Hide();
    wxFont ListBoxAptRunwayFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    ListBoxAptRunway->SetFont(ListBoxAptRunwayFont);
    StaticTextRunways = new wxStaticText(Panel1, ID_STATICTEXT_RUNWAYS, _("Runways ->"), wxPoint(420,180), wxDefaultSize, 0, _T("ID_STATICTEXT_RUNWAYS"));
    StaticTextRunways->SetMinSize(wxSize(160,30));
    StaticTextRunways->Disable();
    StaticTextRunways->Hide();
    wxFont StaticTextRunwaysFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
    StaticTextRunways->SetFont(StaticTextRunwaysFont);
    CheckBox_DoFullNASR = new wxCheckBox(Panel1, ID_CHECKBOX_DO_FULL_NASR, _("Full NASR Database"), wxPoint(240,88), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX_DO_FULL_NASR"));
    CheckBox_DoFullNASR->SetValue(false);
    DirDialogLookupAirport = new wxDirDialog(this, _("Select directory"), wxEmptyString, wxDD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxDirDialog"));
    Center();

    Connect(ID_TEXTCTRL_AIRPORT_ID,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagleAirportLookupFrame::OnTextCtrlAirport_IDText2);
    Connect(ID_TEXTCTRL_AIRPORT_ID,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&OpenEagleAirportLookupFrame::OnTextCtrlAirport_IDTextEnter);
    Connect(ID_BUTTON_LOOKUP_BY_STATE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleAirportLookupFrame::OnButtonLookupAirportClick);
    Connect(ID_BUTTON_APT_INFORMATION,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleAirportLookupFrame::OnButtonAptInformationClick);
    Connect(ID_BUTTON_APT_FREQUENCIES,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleAirportLookupFrame::OnButtonAptFrequenciesClick);
    Connect(ID_LISTBOX_APT_RUNWAY,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&OpenEagleAirportLookupFrame::OnListBoxAptRunwayDClick);
    //*)

    printf("reading airport, tower, awos and ils data\n");
    apt.read_airport_data();
    apt.read_tower_data();
    apt.read_awos_data();
    apt.read_ils_data();

}

OpenEagleAirportLookupFrame::~OpenEagleAirportLookupFrame()
{
    //(*Destroy(OpenEagleAirportLookupFrame)
    //*)
}

void OpenEagleAirportLookupFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagleAirportLookupFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagleAirportLookupFrame::OnButtonLookupAirportClick(wxCommandEvent& event)
{
  //DirDialogLookupAirport->ShowModal();

  if (DirDialogLookupAirport->ShowModal() == wxID_OK)
  {
    wxString path = DirDialogLookupAirport->GetPath();
    wxMessageBox(path);
  }

}

void OpenEagleAirportLookupFrame::OpenEagleBriefNASR(wxString airport_id)
{
  ButtonAptFrequencies->Enable(true);   ButtonAptFrequencies->Show(true);
  ButtonAptInformation->Enable(true);   ButtonAptInformation->Show(true);
  StaticTextRunways->Enable(true);      StaticTextRunways->Show(true);

  //bool have_runways =
  apt.have_runway_records();
  ListBoxAptRunway->Clear();
  do {
    ListBoxAptRunway->AppendAndEnsureVisible(apt.get_b_id());
    ListBoxAptRunway->AppendAndEnsureVisible(apt.get_r_id());
  } while (apt.next_runway_record());
  ListBoxAptRunway->Enable(true);  ListBoxAptRunway->Show(true);
  TextCtrl_Apt_Name->Clear();
  TextCtrl_Apt_Name->AppendText(apt.get_name());  TextCtrl_Apt_Name->Enable(true); TextCtrl_Apt_Name->Show(true);
  TextCtrl_AptCitySt->Clear();
  TextCtrl_AptCitySt->AppendText(apt.get_city());
  TextCtrl_AptCitySt->AppendText(", ");
  TextCtrl_AptCitySt->AppendText(apt.get_st());  TextCtrl_AptCitySt->Enable(true);  TextCtrl_AptCitySt->Show(true);
  TextCtrl_Apt_Elevation->Clear();
  TextCtrl_Apt_Elevation->AppendText(apt.get_airport_elevation());  TextCtrl_Apt_Elevation->Enable(true);TextCtrl_Apt_Elevation->Show(true);
  StaticText_Elevation->Enable(true);  StaticText_Elevation->Show(true);
  std::string ICAO = apt.get_airport_official_icao();
  if (ICAO.c_str()[0] != ' ') {
    ICAO.erase(4);
    printf("have ICAO [%s]\n",ICAO.c_str());
    TextCtrl_ICAO_ID->Clear();
    TextCtrl_ICAO_ID->AppendText(ICAO.c_str());     TextCtrl_ICAO_ID->Enable(true);    TextCtrl_ICAO_ID->Show(true);
    StaticText_ICAO_ID->Enable(true);     StaticText_ICAO_ID->Show(true);
  }
  else {
    TextCtrl_ICAO_ID->Show(false); TextCtrl_ICAO_ID->Enable(false);
  }
  if (apt.get_traffic_pattern_altitude()[0] != ' ') {
    printf("have traffic pattern alt\n");
    TextCtrl_TP_Alt->Clear();
    TextCtrl_TP_Alt->AppendText(apt.get_traffic_pattern_altitude());    TextCtrl_TP_Alt->Enable(true);    TextCtrl_TP_Alt->Show(true);
    StaticText_TP_Altitude->Enable(true);    StaticText_TP_Altitude->Show(true);
  }
  else {
    StaticText_TP_Altitude->Show(false);
    TextCtrl_TP_Alt->Show(false);
  }

}

void OpenEagleAirportLookupFrame::OpenEagleFullNASR(wxString airport_id)
{
  AirportFrame* frm = new AirportFrame(this);
  std::string caption = "Information for Airport: ";
  caption += airport_id;
  wxFont StaticText_AirportFrameFont(10,wxFIXED,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("NULL"),wxFONTENCODING_DEFAULT);

  frm->SetTitle(caption);

  OpenEagleAirportNASR(frm);
  OpenEagleAttendanceNASR(frm);
  OpenEagleArrestNASR(frm);
  OpenEagleRemarksNASR(frm);
  OpenEagleRunwayNASR(frm);
  OpenEagleTowerNASR(frm);
  OpenEagleAwosNASR(frm);

  frm->Show();

}

void OpenEagleAirportLookupFrame::OpenEagleAirportNASR(AirportFrame* frm)
{
   std::string apt_text = "Airport Information:\n";

   apt_text += "Landing Facility Site Number: ";   apt_text +=apt.get_lfsn(); apt_text +="\n";
   apt_text += "Location Identifier  : "; apt_text += apt.get_location_identifier(); apt_text += "\n";
   apt_text += "Type: ";   apt_text +=apt.get_airport_type(); apt_text +="\n";
   apt_text += "Cycle Date           : ";   apt_text +=apt.get_airport_effective_date(); apt_text +="\n";
   apt_text += "--------------------Demographic Data--------------------\n";
   apt_text += "FAA Region           : ";   apt_text +=apt.get_faa_region_code(); apt_text += "\n";
   apt_text += "FAA District         : ";   apt_text +=apt.get_faa_district_office(); apt_text += "\n";
   apt_text += "State                : ";   apt_text +=apt.get_st(); apt_text += "\n";
   apt_text += "State Name           : ";   apt_text +=apt.get_stname(); apt_text += "\n";
   apt_text += "County               : ";   apt_text +=apt.get_county(); apt_text += "\n";
   apt_text += "County St            : ";   apt_text +=apt.get_county_st(); apt_text += "\n";
   apt_text += "City                 : ";   apt_text +=apt.get_city(); apt_text += "\n";
   apt_text += "Name                 : ";   apt_text +=apt.get_name(); apt_text += "\n";
   apt_text += "--------------------Ownership Data--------------------\n";
   apt_text += "Type                 : ";   apt_text +=apt.get_ownership_type(); apt_text += "\n";
   apt_text += "Use                  : ";   apt_text +=apt.get_facility_use(); apt_text += "\n";
   apt_text += "Name                 : ";   apt_text +=apt.get_own_name(); apt_text += "\n";
   apt_text += "Address              : ";   apt_text +=apt.get_own_addr(); apt_text += "\n";
   apt_text += "City                 : ";   apt_text +=apt.get_own_city(); apt_text += "\n";
   apt_text += "Phone                : ";   apt_text +=apt.get_own_phone(); apt_text += "\n";
   apt_text += "Manager Name         : ";   apt_text +=apt.get_mgr_name(); apt_text += "\n";
   apt_text += "Manager Address      : ";   apt_text +=apt.get_mgr_addr(); apt_text += "\n";
   apt_text += "Manager City         : ";   apt_text +=apt.get_mgr_city(); apt_text += "\n";
   apt_text += "Manager Phone        : ";   apt_text +=apt.get_mgr_phone(); apt_text += "\n";
   apt_text += "--------------------Geographic Data--------------------\n";
   apt_text += "Latitude (formatted) : ";  apt_text +=apt.get_airport_latitude_formatted();  apt_text += "\n";
   apt_text += "Latitude (seconds)   : ";  apt_text +=apt.get_airport_latitude_seconds();    apt_text += "\n";
   apt_text += "Longitude (formatted): ";  apt_text +=apt.get_airport_longitude_formatted(); apt_text += "\n";
   apt_text += "Longitude (seconds)  : ";  apt_text +=apt.get_airport_longitude_seconds();   apt_text += "\n";
   apt_text += "Determination Method : ";  apt_text +=apt.get_airport_ref_determ_method();    apt_text += "\n";
   apt_text += "Elevation            : ";  apt_text +=apt.get_airport_elevation();            apt_text += "\n";
   apt_text += "Elevation Method     : ";  apt_text +=apt.get_airport_elevation_method();   apt_text += "\n";
   apt_text += "Magnetic Variation   : ";  apt_text +=apt.get_airport_mag_var();             apt_text += "\n";
   apt_text += "Variation Epoch Year : ";  apt_text +=apt.get_airport_mag_var_epoch_yr();    apt_text += "\n";
   apt_text += "Traf. Pat. Alt.      : ";  apt_text +=apt.get_traffic_pattern_altitude();    apt_text += "\n";
   apt_text += "Section Chart        : ";  apt_text +=apt.get_section_chart();              apt_text += "\n";
   apt_text += "Dist. from Bus. Dist.: ";  apt_text +=apt.get_dist_from_business();          apt_text += "\n";
   apt_text += "Dir. from Bus. Dist. : ";  apt_text +=apt.get_dir_from_business();           apt_text += "\n";
   apt_text += "Land Area            : ";  apt_text +=apt.get_land_area();                   apt_text += "\n";
   apt_text += "--------------------FAA SERVICES---------------------";apt_text += "\n";
   apt_text += "Boundary ARTCC       : "; apt_text +=apt.get_boundary_artcc();         apt_text += "\n";
   apt_text += "ARTCC FAA            : "; apt_text +=apt.get_boundary_artcc_faa();     apt_text += "\n";
   apt_text += "ARTCC Name           : "; apt_text +=apt.get_boundary_artcc_name();   apt_text += "\n";
   apt_text += "ARTCC Rep ID         : "; apt_text +=apt.get_resp_artcc_rep_id();      apt_text += "\n";
   apt_text += "ARTCC_FAA            : "; apt_text +=apt.get_resp_artcc_faa();         apt_text += "\n";
   apt_text += "ARTCC Name           : "; apt_text +=apt.get_resp_artcc_name();       apt_text += "\n";
   apt_text += "Tie In Physical      : "; apt_text +=apt.get_tie_in_phys();            apt_text += "\n";
   apt_text += "Tie In ID            : "; apt_text +=apt.get_tie_in_id();              apt_text += "\n";
   apt_text += "Tie In Name          : "; apt_text +=apt.get_tie_in_name();           apt_text += "\n";
   apt_text += "Local Phone          : "; apt_text +=apt.get_local_phone();           apt_text += "\n";
   apt_text += "Toll Free Phone      : "; apt_text +=apt.get_toll_free_phone();       apt_text += "\n";
   apt_text += "Alt FSS ID           : "; apt_text +=apt.get_alt_fss_id();             apt_text += "\n";
   apt_text += "Alt FSS Name         : "; apt_text +=apt.get_alt_fss_name();          apt_text += "\n";
   apt_text += "Alt FSS Toll Free    : "; apt_text +=apt.get_alt_fss_toll_free();     apt_text += "\n";
   apt_text += "Notam ID             : "; apt_text +=apt.get_notam_id();               apt_text += "\n";
   apt_text += "Notam Available      : "; apt_text +=apt.get_notam_available();        apt_text += "\n";
   apt_text += "--------------------FEDERAL STATUS--------------------";  apt_text += "\n";
   apt_text += "Active Date          : "; apt_text +=apt.get_airport_activ_data();     apt_text += "\n";
   apt_text += "Airport Status Code  : "; apt_text +=apt.get_airport_status_code();    apt_text += "\n";
   apt_text += "ARF Cert             : "; apt_text +=apt.get_airport_arf_cert();      apt_text += "\n";
   apt_text += "NPIAS Fed Code       : "; apt_text +=apt.get_NPIAS_FEDERAL_code();     apt_text += "\n";
   apt_text += "Airspace Analysis    : "; apt_text +=apt.get_airport_airspace_analysis();apt_text += "\n";
   apt_text += "Customs POE          : "; apt_text +=apt.get_airport_customs_poe();    apt_text += "\n";
   apt_text += "Customs Landing      : "; apt_text +=apt.get_airport_customs_landing();apt_text += "\n";
   apt_text += "MIL CIVIL joint use  : "; apt_text +=apt.get_military_civil_joint_use();apt_text += "\n";
   apt_text += "MIL Landing Rights   : "; apt_text +=apt.get_military_landing_rights();apt_text += "\n";
   apt_text += "--------------------AIRPORT INSPECTION DATA--------------------";  apt_text += "\n";
   apt_text += "Inspect Method       : "; apt_text +=apt.get_airport_insp_method();    apt_text += "\n";
   apt_text += "Agency               : "; apt_text +=apt.get_airport_insp_agency();    apt_text += "\n";
   apt_text += "Last Inspection      : "; apt_text +=apt.get_airport_last_inspect();   apt_text += "\n";
   apt_text += "Last Info Req        : "; apt_text +=apt.get_airport_last_info_req();  apt_text += "\n";
   apt_text += "--------------------AIRPORT SERVICES--------------------";  apt_text += "\n";
   apt_text += "Fuel Types           : "; apt_text +=apt.get_fuel_types();            apt_text += "\n";
   apt_text += "Airframe Repair      : "; apt_text +=apt.get_airframe_repair();        apt_text += "\n";
   apt_text += "Powerplant Repair    : "; apt_text +=apt.get_powerplant_repair();      apt_text += "\n";
   apt_text += "Bottled Oxygen       : "; apt_text +=apt.get_bottled_oxy();            apt_text += "\n";
   apt_text += "Bulk Oxygen          : "; apt_text +=apt.get_bulk_oxy();               apt_text += "\n";
   apt_text += "--------------------AIRPORT FACILITIES--------------------";  apt_text += "\n";
   apt_text += "Light Sched          : "; apt_text +=apt.get_light_sched();            apt_text += "\n";
   apt_text += "Beacon Light Sched   : "; apt_text +=apt.get_beacon_light_sched();     apt_text += "\n";
   apt_text += "Has Tower            : "; apt_text +=apt.get_airport_has_tower();      apt_text += "\n";
   apt_text += "UNICOM               : "; apt_text +=apt.get_unicom();                 apt_text += "\n";
   apt_text += "CTAF                 : "; apt_text +=apt.get_ctaf();                   apt_text += "\n";
   apt_text += "Segment Circle Marker: "; apt_text +=apt.get_segment_circle_marker();  apt_text += "\n";
   apt_text += "Lense Color          : "; apt_text +=apt.get_lens_color();             apt_text += "\n";
   apt_text += "Landing Fee          : "; apt_text +=apt.get_landing_fee();            apt_text += "\n";
   apt_text += "Medical Use          : "; apt_text +=apt.get_medical_use();            apt_text += "\n";
   apt_text += "--------------------BASED AIRCRAFT--------------------";  apt_text += "\n";
   apt_text += "Singe Engine GA      : "; apt_text +=apt.get_sega();                   apt_text += "\n";
   apt_text += "Multi Engine GA      : "; apt_text +=apt.get_mega();                   apt_text += "\n";
   apt_text += "Jet GA               : "; apt_text +=apt.get_jetga();                  apt_text += "\n";
   apt_text += "GA Helicopter        : "; apt_text +=apt.get_gaheli();                 apt_text += "\n";
   apt_text += "Glider               : "; apt_text +=apt.get_glider();                 apt_text += "\n";
   apt_text += "Military             : "; apt_text +=apt.get_military();               apt_text += "\n";
   apt_text += "Ultralight           : "; apt_text +=apt.get_ultralight();             apt_text += "\n";
   apt_text += "--------------------ANNUAL OPERATIONS--------------------";  apt_text += "\n";
   apt_text += "Cab Carriers         : "; apt_text +=apt.get_cab_carriers();           apt_text += "\n";
   apt_text += "Commuter             : "; apt_text +=apt.get_commuter();               apt_text += "\n";
   apt_text += "Air Taxi             : "; apt_text +=apt.get_air_taxi();               apt_text += "\n";
   apt_text += "GA Ops               : "; apt_text +=apt.get_ga_ops();                 apt_text += "\n";
   apt_text += "GA Itinerant         : "; apt_text +=apt.get_ga_itinerant();           apt_text += "\n";
   apt_text += "MIL Ops              : "; apt_text +=apt.get_mil_ops();                apt_text += "\n";
   apt_text += "Ending Date          : "; apt_text +=apt.get_ending_date();           apt_text += "\n";
   apt_text += "--------------------ADDITIONAL AIRPORT DATA--------------------"; apt_text += "\n";
   apt_text += "Pos Source           : "; apt_text +=apt.get_pos_source();            apt_text += "\n";
   apt_text += "Pos Source Date      : "; apt_text +=apt.get_pos_source_date();       apt_text += "\n";
   apt_text += "Elevation Source     : "; apt_text +=apt.get_apt_elev_source();       apt_text += "\n";
   apt_text += "Elevation Source Date: "; apt_text +=apt.get_apt_elev_source_date();  apt_text += "\n";
   apt_text += "Contract Fuel        : "; apt_text +=apt.get_contract_fuel();          apt_text += "\n";
   apt_text += "Transient Storage    : "; apt_text +=apt.get_transient_store();       apt_text += "\n";
   apt_text += "Other Services       : "; apt_text +=apt.get_other_ac_services();     apt_text += "\n";
   apt_text += "Wind Indicator       : "; apt_text +=apt.get_wind_indicator();         apt_text += "\n";
   apt_text += "ICAO designation     : "; apt_text +=apt.get_airport_official_icao();  apt_text += "\n";
   apt_text += "MIN OP Network       : "; apt_text +=apt.get_min_op_network();         apt_text += "\n";

   frm->TextCtrl_Airport->AppendText(apt_text.c_str());
}

void OpenEagleAirportLookupFrame::OpenEagleAttendanceNASR(AirportFrame* frm)
{

  std::string att_text = "Attendance Information:\n";
  bool attendance_records = apt.have_attendance_records();
  if (attendance_records) {
    do {
  att_text += "Facility Site No.    : "; att_text += apt.get_att_lfsn(); att_text += "\n";
  att_text += "State                : "; att_text += apt.get_att_st(); att_text += "\n";
  att_text += "Attendance sched No. : "; att_text += apt.get_att_sn(); att_text += "\n";
  att_text += "Attendance Schedule  : "; att_text += apt.get_att_sched(); att_text += "\n";

    } while (apt.next_attendance_record());
    frm->TextCtrl_Attendance->AppendText(att_text.c_str());
  }
  else {
    frm->Panel_Att->Show(false);
  }
}

void OpenEagleAirportLookupFrame::OpenEagleArrestNASR(AirportFrame* frm)
{
  std::string ars_text = "Arresting System Information:\n";
  bool arrest_records = apt.have_arrest_records();
  if (arrest_records) {
    do {
  ars_text += "Facility Site No.    : "; ars_text += apt.get_ars_lfsn();  ars_text += "\n";
  ars_text += "State                : "; ars_text += apt.get_ars_lfst();  ars_text += "\n";  //L AN 0002 00015  N/A     LANDING FACILITY STATE POST OFFICE CODE
  ars_text += "Runway               : "; ars_text += apt.get_ars_runway();  ars_text += "\n"; //L AN 0007 00017  A30     RUNWAY IDENTIFICATION
  ars_text += "Runway End           : "; ars_text += apt.get_ars_runway_end();  ars_text += "\n";//L AN 0003 00024  A30A    RUNWAY END IDENTIFIER THE RUNWAY END DESCRIBED BY THE ARRESTING SYSTEM INFORMATION.
  ars_text += "Arresting System Type: "; ars_text += apt.get_ars_type();  ars_text += "\n"; //L AN 0009 00027  E60     TYPE OF AIRCRAFT ARRESTING DEVICE INDICATES TYPE OF JET ARRESTING BARRIER INSTALLED AT THE FAR END.
   } while (apt.next_arrest_record());
    frm->TextCtrl_ArrestingSystems->AppendText(ars_text.c_str());
  }
  else {
    frm->PanelArrSys->Show(false);
  }

}

void OpenEagleAirportLookupFrame::OpenEagleRemarksNASR(AirportFrame* frm)
{
   std::string rmk_text = "Remarks:\n";
   bool remark_records = apt.have_remark_records();
   if (remark_records) {
     do {
   rmk_text += "--------------------Remarks Information--------------------\n";
   rmk_text += "Facility Site No.    : "; rmk_text += apt.get_rmk_lfsn();  rmk_text += "\n";
   rmk_text += "State                : "; rmk_text += apt.get_rmk_lfst();  rmk_text += "\n";
   rmk_text += "Name                 : "; rmk_text += apt.get_name();  rmk_text += "\n";
   char * text = apt.get_rmk_text();
   remove_trailing_spaces(text);
   add_eol_after_column(text, 40);
   add_eol_after_column_on_period(text, 10);
   rmk_text += "Text                 :\n"; rmk_text += text; //apt.get_rmk_text();
        rmk_text += "\n";
     } while (apt.next_remark_record());
     frm->TextCtrlRemarks->AppendText(rmk_text.c_str());
   }
   else {
     frm->PanelRemarks->Show(false);
   }

}

void OpenEagleAirportLookupFrame::OpenEagleRunwayNASR(AirportFrame* frm)
{
   std::string rwy_text = "Runways:\n";
   bool runway_records = apt.have_runway_records();
   char * test;
   if (runway_records) {
     do {
   rwy_text += "Landing Site        : "; rwy_text += apt.get_rwlanding_facility_site_number(); rwy_text += "\n"; //L AN 0011 00004  DLID    LANDING FACILITY SITE NUMBER
   rwy_text += "State               : "; rwy_text += apt.get_rw_st(); rwy_text += "\n";//L AN 0002 00015  DLID    RUNWAY STATE POST OFFICE CODE
   rwy_text += "ID                  : "; rwy_text += apt.get_runway_id(); rwy_text += "\n"; //L AN 0007 00017  A30     RUNWAY IDENTIFICATION
   rwy_text += "--------------------Common Runway Data--------------------\n";
   rwy_text += "length              : "; rwy_text += apt.get_runway_length(); rwy_text += "\n"; //R AN 0005 00024  A31     PHYSICAL RUNWAY LENGTH (NEAREST FOOT)
   rwy_text += "width               : "; rwy_text += apt.get_runway_width(); rwy_text += "\n"; //R AN 0004 00029  A32     PHYSICAL RUNWAY WIDTH (NEAREST FOOT)
   rwy_text += "surface type cond   : "; rwy_text += apt.get_runway_surface_type_cond(); rwy_text += "\n"; //L AN 0012 00033  A33     RUNWAY SURFACE TYPE AND CONDITION
   test = apt.get_runway_surface_treatment();
   if (test[0]!= ' ') {
   rwy_text += "surface treatment   : "; rwy_text += apt.get_runway_surface_treatment(); rwy_text += "\n"; //L AN 0005 00045  A34     RUNWAY SURFACE TREATMENT
   }
   rwy_text += "runway PCN          : "; rwy_text += apt.get_runway_pcn(); rwy_text += "\n"; //L AN 0011 00050  A39     PAVEMENT CLASSIFICATION NUMBER (PCN)
   rwy_text += "Light Edge Intensity: "; rwy_text += apt.get_runway_light_edge_intensity(); rwy_text += "\n"; //L AN 0005 00061  A40     RUNWAY LIGHTS EDGE INTENSITY
   rwy_text += "--------------------ADDITIONAL COMMON RUNWAY DATA--------------------\n";
   rwy_text += "Runway Length Source: "; rwy_text += apt.get_length_src(); rwy_text += "\n";//L AN 0016 00510  NONE    RUNWAY LENGTH SOURCE
   rwy_text += "Date                : "; rwy_text += apt.get_length_date(); rwy_text += "\n";//L AN 0010 00526  NONE    RUNWAY LENGTH SOURCE DATE (MM/DD/YYYY)
   rwy_text += "Single Wheel Wt Cap : "; rwy_text += apt.get_single_wheel_cap(); rwy_text += "\n";//R AN 0006 00536  A35     RUNWAY WEIGHT-BEARING CAPACITY FOR Single wheel type landing gear (DC3), (C47), (F15), etc.
   rwy_text += "Duel Wheel Wt Cap   : "; rwy_text += apt.get_dual_wheel_cap(); rwy_text += "\n"; //R AN 0006 00542  A36  RUNWAY WEIGHT-BEARING CAPACITY FOR Dual wheel type landing gear (BE1900), (B737), (A319), etc.
   rwy_text += "Duel Whl Tndm Cap   : "; rwy_text += apt.get_dual_wheel_tandem_cap(); rwy_text += "\n"; //R AN 0006 00548  A37     RUNWAY WEIGHT-BEARING CAPACITY FOR Two dual wheels in tandem type landing gear (B707), etc.
   rwy_text += "2x Duel Whl Tndm Cap: "; rwy_text += apt.get_two_duel_wheel_tandem_cap(); rwy_text += "\n";  //R AN 0006 00554  A38     RUNWAY WEIGHT-BEARING CAPACITY FOR Two dual wheels in tandem/two dual wheels in double tandem body gear type landing gear (B747, E4).
   rwy_text += "--------------------+------Base End-------+------Reciprocal End---+\n";
   rwy_text += "End Identifier      :                  "; rwy_text += apt.get_b_id(); rwy_text += " :";
   rwy_text += "                    "; rwy_text += apt.get_r_id(); rwy_text += " :\n";
   rwy_text += "True Alignment      :                 "; rwy_text += apt.get_b_true_alignment(); rwy_text += " :";
   rwy_text += "                   "; rwy_text += apt.get_r_true_alignment(); rwy_text += " :\n";
   rwy_text += "ILS Type            :          "; rwy_text += apt.get_b_ils_type(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_ils_type(); rwy_text += " :\n";
   rwy_text += "RH traffic          :                   "; rwy_text += apt.get_b_rh_traffic(); rwy_text += " :";
   rwy_text += "                     "; rwy_text += apt.get_r_rh_traffic(); rwy_text += " :\n";
   rwy_text += "Runway Markings     :               "; rwy_text += apt.get_b_rwy_markings(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_rwy_markings(); rwy_text += " :\n";
   rwy_text += "Runway Condition    :                   "; rwy_text += apt.get_b_rwy_condition(); rwy_text += " :";
   rwy_text += "                     "; rwy_text += apt.get_r_rwy_condition(); rwy_text += " :\n";
   rwy_text += "---Geographic Data--+------Base End-------+------Reciprocal End---+\n";
   rwy_text += "Latitude            :     "; rwy_text += apt.get_b_latitude(); rwy_text += " :";
   rwy_text += "       "; rwy_text += apt.get_r_latitude(); rwy_text += " :\n";
   rwy_text += "Latitude (seconds)  :     "; rwy_text += apt.get_b_latitude_seconds(); rwy_text += "    :";
   rwy_text += "          "; rwy_text += apt.get_r_latitude_seconds(); rwy_text += " :\n";
   rwy_text += "Longitude           :     "; rwy_text += apt.get_b_longitude(); rwy_text += " :";
   rwy_text += "       "; rwy_text += apt.get_r_longitude(); rwy_text += " :\n";
   rwy_text += "Longitude (seconds) :     "; rwy_text += apt.get_b_longitude_seconds(); rwy_text += "    :";
   rwy_text += "          "; rwy_text += apt.get_r_longitude_seconds(); rwy_text += " :\n";
   rwy_text += "Elevation           :             "; rwy_text += apt.get_b_elevation(); rwy_text += " :";
   rwy_text += "               "; rwy_text += apt.get_r_elevation(); rwy_text += " :\n";
   rwy_text += "Threshold Cross Hgt :                 "; rwy_text += apt.get_b_threshold_xheight(); rwy_text += " :";
   rwy_text += "                   "; rwy_text += apt.get_r_threshold_xheight(); rwy_text += " :\n";
   rwy_text += "Glide Slope         :                "; rwy_text += apt.get_b_glide_slope(); rwy_text += " :";
   rwy_text += "                  "; rwy_text += apt.get_r_glide_slope(); rwy_text += " :\n";
   rwy_text += "-Displace Threshold-+------Base End-------+------Reciprocal End---+\n";
   rwy_text += "Latitude            :     "; rwy_text += apt.get_b_dt_latitude(); rwy_text += " :";
   rwy_text += "       "; rwy_text += apt.get_r_dt_latitude(); rwy_text += " :\n";
   rwy_text += "Latitude (seconds)  :     "; rwy_text += apt.get_b_dt_latitude_seconds(); rwy_text += "    :";
   rwy_text += "          "; rwy_text += apt.get_r_dt_latitude_seconds(); rwy_text += " :\n";
   rwy_text += "Longitude           :     "; rwy_text += apt.get_b_dt_longitude(); rwy_text += "    :";
   rwy_text += "       "; rwy_text += apt.get_r_dt_longitude(); rwy_text += " :\n";
   rwy_text += "Longitude (seconds) :     "; rwy_text += apt.get_b_dt_longitude_seconds(); rwy_text += "    :";
   rwy_text += "          "; rwy_text += apt.get_r_dt_longitude_seconds(); rwy_text += " :\n";
   rwy_text += "Elevation           :             "; rwy_text += apt.get_b_dt_elevation(); rwy_text += " :";
   rwy_text += "               "; rwy_text += apt.get_r_dt_elevation(); rwy_text += " :\n";
   rwy_text += "Length              :                "; rwy_text += apt.get_b_dt_length(); rwy_text += " :";
   rwy_text += "                  "; rwy_text += apt.get_r_dt_length(); rwy_text += " :\n";
   rwy_text += "Elevation at TD     :             "; rwy_text += apt.get_b_dt_elev_at_td(); rwy_text += " :";
   rwy_text += "               "; rwy_text += apt.get_r_dt_elev_at_td(); rwy_text += " :\n";
   rwy_text += "---Lighting Data----+------Base End-------+------Reciprocal End---+\n";
   rwy_text += "Glide Slope         :               "; rwy_text += apt.get_b_glide_slope_ind(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_glide_slope_ind(); rwy_text += " :\n";
   rwy_text += "Visual Range Eq.    :                 "; rwy_text += apt.get_b_rvr(); rwy_text += " :";
   rwy_text += "                   "; rwy_text += apt.get_r_rvr(); rwy_text += " :\n";
   rwy_text += "Visual Value Eq.    :                   "; rwy_text += apt.get_b_rvv(); rwy_text += " :";
   rwy_text += "             "; rwy_text += apt.get_r_rvv(); rwy_text += " :\n";
   rwy_text += "Approach            :            "; rwy_text += apt.get_b_approach_lights(); rwy_text += " :";
   rwy_text += "              "; rwy_text += apt.get_r_approach_lights(); rwy_text += " :\n";
   rwy_text += "Runway End Lgts REIL:                   "; rwy_text += apt.get_b_reil(); rwy_text += " :";
   rwy_text += "                     "; rwy_text += apt.get_r_reil(); rwy_text += " :\n";
   rwy_text += "Center Line         :                   "; rwy_text += apt.get_b_ctr_ln_lights(); rwy_text += " :";
   rwy_text += "                     "; rwy_text += apt.get_r_ctr_ln_lights(); rwy_text += " :\n";
   rwy_text += "Touch Down          :                   "; rwy_text += apt.get_b_td_lights(); rwy_text += " :";
   rwy_text += "                     "; rwy_text += apt.get_r_td_lights(); rwy_text += " :\n";
   rwy_text += "-----Object Data----+------Base End-------+------Reciprocal End---+\n";
   rwy_text += "Object Description  :         "; rwy_text += apt.get_b_object(); rwy_text += " :";
   rwy_text += "           "; rwy_text += apt.get_r_object(); rwy_text += " :\n";
   rwy_text += "Marked - Lighted    :                "; rwy_text += apt.get_b_marked_lighted(); rwy_text += " :";
   rwy_text += "                  "; rwy_text += apt.get_r_marked_lighted(); rwy_text += " :\n";
   rwy_text += "FAA CFR 77          :               "; rwy_text += apt.get_b_faa_cfr_77(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_faa_cfr_77(); rwy_text += " :\n";
   rwy_text += "Clearance Slope     :                  "; rwy_text += apt.get_b_clearance_slope(); rwy_text += " :";
   rwy_text += "                    "; rwy_text += apt.get_r_clearance_slope(); rwy_text += " :\n";
   rwy_text += "Height Above Runway :               "; rwy_text += apt.get_b_height_above_rwy(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_height_above_rwy(); rwy_text += " :\n";
   rwy_text += "Distance from Runway:               "; rwy_text += apt.get_b_dist_from_rwy(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_dist_from_rwy(); rwy_text += " :\n";
   rwy_text += "Center Line Offset  :             "; rwy_text += apt.get_b_center_line_offset(); rwy_text += " :";
   rwy_text += "               "; rwy_text += apt.get_r_center_line_offset(); rwy_text += " :\n";
   rwy_text += "--Additional Data---+------Base End-------+------Reciprocal End---+\n";
   rwy_text += "Runway End Gradient :               "; rwy_text += apt.get_b_runway_end_gradient(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_runway_end_gradient(); rwy_text += " :\n";
   rwy_text += "Runway End Grad Dir :                "; rwy_text += apt.get_b_runway_end_gradient_dir(); rwy_text += " :";
   rwy_text += "                  "; rwy_text += apt.get_r_runway_end_gradient_dir(); rwy_text += " :\n";
   rwy_text += "Runway End Pos Src  :    "; rwy_text += apt.get_b_runway_end_pos_src(); rwy_text += " :";
   rwy_text += "      "; rwy_text += apt.get_r_runway_end_pos_src(); rwy_text += " :\n";
   rwy_text += "Runway End Pos Date :          "; rwy_text += apt.get_b_runway_end_pos_date(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_runway_end_pos_date(); rwy_text += " :\n";
   rwy_text += "Runway End Elev Src :    "; rwy_text += apt.get_b_runway_end_elev_src(); rwy_text += " :";
   rwy_text += "      "; rwy_text += apt.get_r_runway_end_elev_src(); rwy_text += " :\n";
   rwy_text += "Runway End Elev Date:          "; rwy_text += apt.get_b_runway_end_elev_src_date(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_runway_end_elev_src_date(); rwy_text += " :\n";
   rwy_text += "Disp Thld Pos Src   :    "; rwy_text += apt.get_b_dt_pos_src(); rwy_text += " :";
   rwy_text += "      "; rwy_text += apt.get_r_dt_pos_src(); rwy_text += " :\n";
   rwy_text += "Disp Thld Pos Src Dt:          "; rwy_text += apt.get_b_dt_pos_src_date(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_dt_pos_src_date(); rwy_text += " :\n";
   rwy_text += "Disp Thld Elev Src  :    "; rwy_text += apt.get_b_dt_elev_src(); rwy_text += " :";
   rwy_text += "      "; rwy_text += apt.get_r_dt_elev_src(); rwy_text += " :\n";
   rwy_text += "Disp Thld Elev Src D:          "; rwy_text += apt.get_b_dt_elev_src_date(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_dt_elev_src_date(); rwy_text += " :\n";
   rwy_text += "TD Elev Src         :    "; rwy_text += apt.get_b_td_elev_src(); rwy_text += " :";
   rwy_text += "      "; rwy_text += apt.get_r_td_elev_src(); rwy_text += " :\n";
   rwy_text += "TD Elev Src  Date   :          "; rwy_text += apt.get_b_td_elev_src_date(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_td_elev_src_date(); rwy_text += " :\n";
   rwy_text += "TORA                :               "; rwy_text += apt.get_b_tora(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_tora(); rwy_text += " :\n";
   rwy_text += "TODA                :               "; rwy_text += apt.get_b_toda(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_toda(); rwy_text += " :\n";
   rwy_text += "ASDA                :               "; rwy_text += apt.get_b_asda(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_asda(); rwy_text += " :\n";
   rwy_text += "LDA                 :               "; rwy_text += apt.get_b_lda(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_lda(); rwy_text += " :\n";
   rwy_text += "LAHSO Landing Dist  :               "; rwy_text += apt.get_b_lahso(); rwy_text += " :";
   rwy_text += "                 "; rwy_text += apt.get_r_lahso(); rwy_text += " :\n";
   rwy_text += "LAHSO ID Int RWY    :             "; rwy_text += apt.get_b_id_int_rw(); rwy_text += " :";
   rwy_text += "               "; rwy_text += apt.get_r_id_int_rw(); rwy_text += " :\n";
   rwy_text += "LAHSO Ent Def Pt B  :"; rwy_text += apt.get_b_id_desc_ent(); rwy_text += "\n";
   rwy_text += "LAHSO Ent Def Pt R  :"; rwy_text += apt.get_r_id_desc_ent(); rwy_text += "\n";
   rwy_text += "LAHSO Lat.          :     "; rwy_text += apt.get_b_lat_lahso(); rwy_text += " :";
   rwy_text += "       "; rwy_text += apt.get_r_lat_lahso(); rwy_text += " :\n";
   rwy_text += "LAHSO Lat. (Seconds):        "; rwy_text += apt.get_b_lat_lahso_seconds(); rwy_text += " :";
   rwy_text += "          "; rwy_text += apt.get_r_lat_lahso_seconds(); rwy_text += " :\n";
   rwy_text += "LAHSO Long.         :     "; rwy_text += apt.get_b_lon_lahso(); rwy_text += " :";
   rwy_text += "       "; rwy_text += apt.get_r_lon_lahso(); rwy_text += " :\n";
   rwy_text += "LAHSO Long. (Secnds):        "; rwy_text += apt.get_b_lon_lahso_seconds(); rwy_text += " :";
   rwy_text += "          "; rwy_text += apt.get_r_lon_lahso_seconds(); rwy_text += " :\n";
   rwy_text += "LAHSO Source        :    "; rwy_text += apt.get_b_latlon_lahso_src(); rwy_text += " :";
   rwy_text += "      "; rwy_text += apt.get_r_latlon_lahso_src(); rwy_text += " :\n";
   rwy_text += "LAHSO Date          :          "; rwy_text += apt.get_b_latlon_lahso_src_date(); rwy_text += " :";
   rwy_text += "            "; rwy_text += apt.get_r_latlon_lahso_src_date(); rwy_text += " :\n";

   } while (apt.next_runway_record());
     frm->TextCtrl_Runway->AppendText(rwy_text.c_str());
   }
   else {
     frm->Panel_Rwy->Show(false);
   }

}

/// NASR Tower records
void OpenEagleAirportLookupFrame::OpenEagleTowerNASR(AirportFrame* frm)
{
  bool twr1_record = apt.have_twr1_record();
  if (twr1_record) {
    OpenEagleTwr1NASR(frm);
    bool have_twr2 = apt.have_twr2_record();
    if (have_twr2) {
      printf("have twr2\n");
      OpenEagleTwr2NASR(frm);
    }
    else {
      frm->Panel_Hours->Show(false);
    }
    bool have_twr3 = apt.have_twr3_records();
    if (have_twr3) {
      printf("have twr3\n");
      do {
        OpenEagleTwr3NASR(frm);
      } while (apt.next_twr3_record());
    }
    else {
      frm->Panel_Frequencies->Show(false);
    }
    bool have_twr4 = apt.have_twr4_records();
    if (have_twr4) {
      printf("have twr4\n");
      do {
        OpenEagleTwr4NASR(frm);
      } while (apt.next_twr4_record());
    }
    else {
      frm->Panel_Services->Show(false);
    }
    bool have_twr5 = apt.have_twr5_record();
    if (have_twr5) {
      printf("have twr5\n");
      OpenEagleTwr5NASR(frm);
    }
    else {
      frm->Panel_Radar->Show(false);
    }
    bool have_twr6 = apt.have_twr6_records();
    if (have_twr6) {
      printf("have twr6\n");
      do {
        OpenEagleTwr6NASR(frm);
      } while (apt.next_twr6_record());
    }
    else {
      frm->Panel_Remarks->Show(false);
    }
    bool have_twr7 = apt.have_twr7_records();
    if (have_twr7) {
      printf("have twr7\n");
      do {
        OpenEagleTwr7NASR(frm);
      } while (apt.next_twr7_record());
    }
    else {
      frm->Panel_Satellite->Show(false);
    }
    bool have_twr8 = apt.have_twr8_record();
    if (have_twr8) {
      printf("have twr8\n");
      OpenEagleTwr8NASR(frm);
    }
    else {
      frm->Panel_Class_BCDE->Show(false);
    }
    bool have_twr9 = apt.have_twr9_records();
    if (have_twr9) {
      printf("have twr9\n");
      do {
        OpenEagleTwr9NASR(frm);
      } while (apt.next_twr9_record());
    }
    else {
      frm->Panel_ATIS->Show(false);
    }
  }
  else {
    frm->PanelTower->Show(false);
  }
}
void OpenEagleAirportLookupFrame::OpenEagleTwr1NASR(AirportFrame* frm)
{
   std::string twr_text = "Tower:\n";

   twr_text += "--------------------Tower Information--------------------\n";
   twr_text += "TERMINAL COMMUNICATIONS FACILITY IDENTIFIER :"    ;   twr_text += apt.get_term_com_fac_id(); twr_text += "\n";
   twr_text += "INFORMATION EFFECTIVE DATE (MM/DD/YYYY)           :";   twr_text += apt.get_info_effect_date(); twr_text += "\n";
   twr_text += "--------------------Landing Facility(Airport) Data--------------------\n";
   twr_text += "LANDING FACILITY SITE NUMBER                      : "; twr_text += apt.get_lfsn();   twr_text += "\n";
   twr_text += "FAA REGION CODE                                   : "; twr_text += apt.get_faa_reg_code();     twr_text += "\n";
   twr_text += "ASSOCIATED STATE NAME                             : "; twr_text += apt.get_assoc_st_name(); twr_text += "\n";
   twr_text += "ASSOCIATED STATE POST OFFICE  CODE                : "; twr_text += apt.get_assoc_st();   twr_text += "\n";
   twr_text += "ASSOCIATED CITY NAME                              : "; twr_text +=  apt.get_assoc_city_name();  twr_text += "\n";
   twr_text += "OFFICIAL AIRPORT NAME                             : "; twr_text += apt.get_offic_apt_name();   twr_text += "\n";
   twr_text += "AIRPORT REFERENCE POINT LATITUDE (FORMATTED)      : "; twr_text += apt.get_latitude();   twr_text += "\n";
   twr_text += "AIRPORT REFERENCE POINT LATITUDE (SECONDS)        : "; twr_text +=  apt.get_latitude_seconds();  twr_text += "\n";
   twr_text += "AIRPORT REFERENCE POINT LONGITUDE (FORMATTED)     : "; twr_text += apt.get_longitude();   twr_text += "\n";
   twr_text += "AIRPORT REFERENCE POINT LONGITUDE (SECONDS)       : "; twr_text +=  apt.get_longitude_seconds();  twr_text += "\n";
   twr_text += "TIE-IN FLIGHT SERVICE STATION (FSS) IDENTIFIER    : "; twr_text +=  apt.get_tie_in_fss();  twr_text += "\n";
   twr_text += "TIE-IN FLIGHT SERVICE STATION (FSS) NAME          : "; twr_text +=  apt.get_tie_in_fss_name();  twr_text += "\n";
   twr_text += "--------------------Terminal Communications Facility Data--------------------\n";
   twr_text += "FACILITY TYPE                                     : "; twr_text += apt.get_fac_type();     twr_text += "\n";
   twr_text += "NUMBER OF HOURS OF DAILY OPERATION                : "; twr_text += apt.get_num_hours();      twr_text += "\n";
   twr_text += "NUMBER OF HOURS OF DAILY OPERATION  CODE          : "; twr_text += apt.get_num_hours_code();      twr_text += "\n";
   twr_text += "MASTER AIRPORT LOCATION IDENTIFIER (EX: LAX)      : "; twr_text += apt.get_master_apt_id();     twr_text += "\n";
   twr_text += "NAME OF MASTER AIRPORT FURNISHING SERVICES        : "; twr_text += apt.get_master_apt_name();        twr_text += "\n";
   twr_text += "DIRECTION FINDING EQUIPMENT (TYPE)                : "; twr_text += apt.get_dir_find_eq();    twr_text += "\n";
   twr_text += "----------Terminal Communications Facility Off Airport----------\n";
   twr_text += "NAME OF ASSOCIATED LANDING FACILITY WHEN THE      : "; twr_text += apt.get_assoc_land_fac();      twr_text += "\n";
   twr_text += "NAME OF THE ASSOCIATED CITY WHEN THE FACILITY     : "; twr_text += apt.get_accoc_city();      twr_text += "\n";
   twr_text += "NAME OF THE STATE OR PROVINCE WHEN THE FACILITY   : "; twr_text += apt.get_st_prov();      twr_text += "\n";
   twr_text += "NAME OF STATE/COUNTRY WHEN FACILITY NOT LOCATED   : "; twr_text += apt.get_st_county();      twr_text += "\n";
   twr_text += "COUNTRY/STATE  POST OFFICE CODE WHEN FACILITY     : "; twr_text += apt.get_country_st();      twr_text += "\n";
   twr_text += "FAA REGION CODE WHEN THE FACILITY NOT LOCATED     : "; twr_text += apt.get_faa_reg_code_off_apt();      twr_text += "\n";
   twr_text += "----------Latitude-Longitude data----------\n";
   twr_text += "AIRPORT SURVEILLANCE RADAR LATITUDE(FORMATTED)    : "; twr_text +=apt.get_as_rad_lat();               twr_text += "\n";
   twr_text += "AIRPORT SURVEILLANCE RADAR LATITUDE (SECONDS)     : "; twr_text +=apt.get_as_rad_lat_seconds();       twr_text += "\n";
   twr_text += "AIRPORT SURVEILLANCE RADAR LONGITUDE (FORMATTED)  : "; twr_text +=apt.get_as_rad_lon();               twr_text += "\n";
   twr_text += "AIRPORT SURVEILLANCE RADAR LONGITUDE (SECONDS)    : "; twr_text +=apt.get_as_rad_lon_seconds();       twr_text += "\n";
   twr_text += "LATITUDE OF DIRECTION FINDING ANTENNA (FORMATTED) : "; twr_text += apt.get_dfa_rad_lat();                twr_text += "\n";
   twr_text += "LATITUDE OF DIRECTION FINDING ANTENNA (SECONDS)   : "; twr_text += apt.get_dfa_rad_lat_seconds();        twr_text += "\n";
   twr_text += "LONGITUDE OF DIRECTION FINDING ANTENNA(FORMATTED) : "; twr_text += apt.get_dfa_rad_lon();                twr_text += "\n";
   twr_text += "LONGITUDE OF DIRECTION FINDING ANTENNA (SECONDS)  : "; twr_text += apt.get_dfa_rad_lon_seconds();        twr_text += "\n";
   twr_text += "--------------------Operator Data--------------------\n";
   twr_text += "NAME OF THE AGENCY THAT OPERATES THE TOWER        : "; twr_text += apt.get_twr();               twr_text += "\n";
   twr_text += "NAME OF THE AGENCY THAT OPERATES MILITARY         : "; twr_text += apt.get_mil_ops_data();           twr_text += "\n";
   twr_text += "NAME OF THE AGENCY THAT OPERATES THE PRIMARY      : "; twr_text += apt.get_p_app_cntrl();       twr_text += "\n";
   twr_text += "NAME OF THE AGENCY OPERATING THE SECONDARY        : "; twr_text += apt.get_s_app_cntrl();       twr_text += "\n";
   twr_text += "NAME OF THE AGENCY OPERATING THE PRIMARY          : "; twr_text += apt.get_p_dep_cntrl();       twr_text += "\n";
   twr_text += "NAME OF THE AGENCY OPERATING THE SECONDARY        : "; twr_text += apt.get_s_dep_cntrl();       twr_text += "\n";
   twr_text += "--------------------Radio Call Data--------------------\n";
   twr_text += "RADIO CALL USED BY PILOT TO CONTACT TOWER         : "; twr_text +=apt.get_pilot_to_twr();                   twr_text += "\n";
   twr_text += "RADIO CALL NAME FOR MILITARY OPERATIONS AT        : "; twr_text +=apt.get_mill_ops_call();                       twr_text += "\n";
   twr_text += "RADIO CALL OF FACILITY THAT FURNISHES PRIMARY     : "; twr_text +=apt.get_p_app_cntr_call();                twr_text += "\n";
   twr_text += "RADIO CALL OF FACILITY THAT TAKES OVER APPROACH   : "; twr_text +=apt.get_p_take_over_cntrl_call();         twr_text += "\n";
   twr_text += "RADIO CALL OF FACILITY THAT FURNISHES PRIMARY     : "; twr_text +=apt.get_p_dep_cntr();                     twr_text += "\n";

     /**
   twr_text += "                                               : "; twr_text +=       twr_text += "\n";
     **/
   frm->TextCtrlTower->AppendText(twr_text.c_str());


}

void OpenEagleAirportLookupFrame::OpenEagleTwr2NASR(AirportFrame* frm)
{
   std::string twr_text = "";

   twr_text += "-----------------Operating Hours------------------+\n";
   twr_text += "FACILITY IDENTIFIER : "; twr_text += apt.get_ident(); twr_text += "\n";
   twr_text += "MILITARY (PMSV)     : "; twr_text += apt.get_pmsv(); twr_text += "\n";
   twr_text += "MILITARY (MACP)     : "; twr_text += apt.get_macp();  twr_text += "\n";
   twr_text += "MIL OPS DAILY       : "; twr_text += apt.get_dyly();  twr_text += "\n";
   twr_text += "PRIMARY APPROACH    : "; twr_text += apt.get_p_app(); twr_text += "\n";
   twr_text += "SECONDARY APPROACH  : "; twr_text += apt.get_s_app(); twr_text += "\n";
   twr_text += "PRIMARY DEPARTURE   : "; twr_text += apt.get_p_dep(); twr_text += "\n";
   twr_text += "SECONDARY DEPARTURE : "; twr_text += apt.get_s_dep(); twr_text += "\n";
   twr_text += "TOWER (LOCAL TIME)  : "; twr_text += apt.get_twr2_twr(); twr_text += "the end\n";

  // twr_text += "                                                  : "; twr_text += apt.      twr_text += "\n";

   frm->TextCtrl_Hours->AppendText( twr_text.c_str() );
  // printf("hours[%s]\n",twr_text.c_str());
}

void OpenEagleAirportLookupFrame::OpenEagleTwr3NASR(AirportFrame* frm)
{
   std::string twr_text = "";
   twr_text += "-----------------Frequencies------------------+\n";
   twr_text += "FACILITY IDENTIFIER: "; twr_text += apt.get_ident(); twr_text += "\n";
   for (int i = 0; i<9; i++) {
   twr_text += "Frequency (";  twr_text += std::to_string(i+1); twr_text +=") : "; twr_text += apt.get_twr3_freq(i); twr_text += "\n";
   twr_text += " Use      : "; twr_text += apt.get_twr3_use(i);      twr_text += "\n";
   }
   for (int i = 0; i<9; i++) {
   twr_text += "Freq ("; twr_text += std::to_string(i); twr_text +=") : "; twr_text += apt.get_freq_not_trunc(i);      twr_text += "\n";
   }
   frm->TextCtrl_Frequencies->AppendText( twr_text.c_str() );

}

void OpenEagleAirportLookupFrame::OpenEagleTwr4NASR(AirportFrame* frm)
{
   std::string twr_text = "";
   twr_text += "-----------------Services------------------+\n";
   twr_text += "FACILITY IDENTIFIER: "; twr_text += apt.get_twr4_ident(); twr_text += "\n";
   twr_text += "AIRPORT SERVICES   : "; twr_text += apt.get_service();      twr_text += "\n";
   frm->TextCtrl_Services->AppendText( twr_text.c_str() );

}

void OpenEagleAirportLookupFrame::OpenEagleTwr5NASR(AirportFrame* frm)
{
   std::string twr_text = "";
   twr_text += "-----------------Radar------------------+\n";
   twr_text += "FACILITY IDENTIFIER       : "; twr_text += apt.get_twr5_ident(); twr_text += "\n";
   twr_text += "PRIMARY APPROACH CALL     : "; twr_text += apt.get_p_apr_call();      twr_text += "\n";
   twr_text += "SECONDARY APPROACH CALL   : "; twr_text += apt.get_s_apr_call();      twr_text += "\n";
   twr_text += "PRIMARY DEPARTURE CALL    : "; twr_text += apt.get_p_dep_call();      twr_text += "\n";
   twr_text += "SECONDARY DEPARTURE CALL  : "; twr_text += apt.get_s_dep_call();      twr_text += "\n";
   for (int i = 0; i<4; i++) {
   twr_text += "TYPE OF RADAR AT TOWER    : "; twr_text += apt.get_radar_type(i);      twr_text += "\n";
   twr_text += "RADAR HOURS OF OPERATION  : "; twr_text += apt.get_radar_hrs(i);      twr_text += "\n";
   }
   frm->TextCtrl_Radar->AppendText( twr_text.c_str() );
}

void OpenEagleAirportLookupFrame::OpenEagleTwr6NASR(AirportFrame* frm)
{
   std::string twr_text = "";
   twr_text += "-----------------Remarks------------------+\n";
   twr_text += "FACILITY IDENTIFIER: "; twr_text += apt.get_twr6_ident(); twr_text += "\n";
   twr_text += "ELEMENT NUMBER     : "; twr_text += apt.get_twr6_elem_nbr();      twr_text += "\n";
   twr_text += "---------------------------Remark-----------------------------\n";
   twr_text += apt.get_twr6_remark(); twr_text += "\n";
   frm->TextCtrl_Remarks->AppendText( twr_text.c_str() );
}

void OpenEagleAirportLookupFrame::OpenEagleTwr7NASR(AirportFrame* frm)
{
   std::string twr_text = "";
   twr_text += "-----------------Satellite Information------------------+\n";
   twr_text += "FACILITY IDENTIFIER                            : "; twr_text += apt.get_twr7_ident(); twr_text += "\n";
   twr_text += "FREQUENCY (EX: 126.1)                          : "; twr_text += apt.get_twr7_sat_freq();      twr_text += "\n";
   twr_text += "USE (EX: APCH/P DEP/P)                         : "; twr_text += apt.get_twr7_sat_use();      twr_text += "\n";
   twr_text += "SATELLITE AIRPORT SITE NUMBER                  : "; twr_text += apt.get_twr7_apt_site_nbr();      twr_text += "\n";
   twr_text += "SATELLITE AIRPORT LOCATION IDENTIFIER          : "; twr_text += apt.get_twr7_apt_id();      twr_text += "\n";
   twr_text += "SATELLITE FAA REGION CODE (EX: AWP)            : "; twr_text += apt.get_twr7_faa_reg();      twr_text += "\n";
   twr_text += "SATELLITE ASSOCIATED STATE NAME                : "; twr_text += apt.get_twr7_st_name();      twr_text += "\n";
   twr_text += "SATELLITE ASSOCIATED STATE POST OFFICE CODE    : "; twr_text += apt.get_twr7_st();      twr_text += "\n";
   twr_text += "SATELLITE ASSOCIATED CITY (EX: PALMDALE)       : "; twr_text += apt.get_twr7_city();      twr_text += "\n";
   twr_text += "SATELLITE ARPT NAME                            : "; twr_text += apt.get_twr7_arpt_name();      twr_text += "\n";
   twr_text += "AIRPORT LATITUDE(FORMATTED)                    : "; twr_text += apt.get_twr7_lat();      twr_text += "\n";
   twr_text += "AIRPORT LATITUDE (SECONDS)                     : "; twr_text += apt.get_twr7_lat_seconds();      twr_text += "\n";
   twr_text += "AIRPORT LONGITUDE (FORMATTED)                  : "; twr_text += apt.get_twr7_lon();      twr_text += "\n";
   twr_text += "AIRPORT LONGITUDE (SECONDS)                    : "; twr_text += apt.get_twr7_lon_seconds();      twr_text += "\n";
   twr_text += "FLIGHT SERVICE STATION IDENTIFIER (EX: WJF)    : "; twr_text += apt.get_twr7_fss_id();      twr_text += "\n";
   twr_text += "FLIGHT SERVICE STATION NAME                    : "; twr_text += apt.get_twr7_fss_name();      twr_text += "\n";
   twr_text += "-----------------Master Airport Information-------------+\n";
   twr_text += "MASTER AIRPORT INFORMATION (EX: 01526.8*A)     : "; twr_text += apt.get_twr7_m_arpt_id();      twr_text += "\n";
   twr_text += "MASTER AIRPORT FAA REGION CODE (EX: ACE)       : "; twr_text += apt.get_twr7_m_faa_reg();      twr_text += "\n";
   twr_text += "MASTER AIRPORT ASSOCIATED STATE NAME           : "; twr_text += apt.get_twr7_m_st_name();      twr_text += "\n";
   twr_text += "MASTER AIRPORT ASSOCIATED STATE POST OFFICE    : "; twr_text += apt.get_twr7_m_st();      twr_text += "\n";
   twr_text += "MASTER AIRPORT ASSOCIATED CITY (EX: EWARDS)    : "; twr_text += apt.get_twr7_m_city();      twr_text += "\n";
   twr_text += "MASTER AIRPORT NAME  (EX: EDWARDS AFB)         : "; twr_text += apt.get_twr7_m_arpt_name();      twr_text += "\n";
   twr_text += "SATELLITE FREQUENCY (EX: 126.1) (NOT TRUNCATED): "; twr_text += apt.get_twr7_m_sat_freq();      twr_text += "\n";

   frm->TextCtrlSatellite->AppendText( twr_text.c_str() );

}

void OpenEagleAirportLookupFrame::OpenEagleTwr8NASR(AirportFrame* frm)
{
   std::string twr_text = "";
   twr_text += "-----------------Class Airpace------------------+\n";
   twr_text += "FACILITY IDENTIFIER        : "; twr_text += apt.get_twr8_ident(); twr_text += "\n";
   twr_text += "CLASS B AIRSPACE (EX: Y)   : "; twr_text += apt.get_twr8_class_b();      twr_text += "\n";
   twr_text += "CLASS C AIRSPACE           : "; twr_text += apt.get_twr8_class_b();      twr_text += "\n";
   twr_text += "CLASS D AIRSPACE           : "; twr_text += apt.get_twr8_class_b();      twr_text += "\n";
   twr_text += "CLASS E AIRSPACE           : "; twr_text += apt.get_twr8_class_b();      twr_text += "\n";
   twr_text += "AIRSPACE HOURS             : "; twr_text += apt.get_twr8_hours();      twr_text += "\n";
   frm->TextCtrl_Class_BCDE->AppendText( twr_text.c_str() );
}

void OpenEagleAirportLookupFrame::OpenEagleTwr9NASR(AirportFrame* frm)
{
  std::string twr_text = "";
   twr_text += "-----------------Class Airpace------------------+\n";
   twr_text += "FACILITY IDENTIFIER                     : "; twr_text += apt.get_twr9_ident(); twr_text += "\n";
   twr_text += "ATIS SERIAL NUMBER                      : "; twr_text += apt.get_twr9_sn();      twr_text += "\n";
   twr_text += "ATIS HOURS OF OPERATION LOCAL TIME      : "; twr_text += apt.get_twr9_hours();      twr_text += "\n";
   twr_text += "OPTIONAL DESCRIPTION OR PURPOSE OF ATIS : "; twr_text += apt.get_twr9_purpose();      twr_text += "\n";
   twr_text += "PHONE NUMBER                            : "; twr_text += apt.get_twr9_phone();      twr_text += "\n";

  frm->TextCtrl_ATIS->AppendText( twr_text.c_str() );
}

/// AWOS records
void OpenEagleAirportLookupFrame::OpenEagleAwosNASR(AirportFrame* frm)
{
  bool awos1_record = apt.have_awos1_record();
  if (awos1_record) {
    printf("have awos1 record\n");
    OpenEagleAwos1NASR(frm);
    bool awos2_records = apt.have_awos2_records();
    if (awos2_records) {
      do {
        printf("have awos2 record with id[%s]\n",apt.get_awos2_wx_sensor_ident());
        OpenEagleAwos2NASR(frm);
      }  while (apt.next_awos2_record());
    }
  }
  else {
    frm->Panel_AWOS->Show(false);
  }
}
void OpenEagleAirportLookupFrame::OpenEagleAwos1NASR(AirportFrame* frm)
{
   std::string awos_text = "";
   awos_text += "-----------------AWOS------------------+\n";
   awos_text += "WX_SENSOR_IDENT         : "; awos_text += apt.get_awos1_wx_sensor_ident(); awos_text += "\n";
   awos_text += "WX_SENSOR_TYPE          : "; awos_text += apt.get_awos1_wx_sensor_type(); awos_text += "\n";
   awos_text += "COMMISSIONING_STATUS    : "; awos_text += apt.get_awos1_commisioning_status(); awos_text += "\n";
   awos_text += "COMMISSIONING DATE      : "; awos_text += apt.get_awos1_commisioning_date(); awos_text += "\n";
   awos_text += "NAVAID FLAG             : "; awos_text += apt.get_awos1_navaid_flag(); awos_text += "\n";
   awos_text += "STATION LATITUDE        : "; awos_text += apt.get_awos1_lat(); awos_text += "\n";
   awos_text += "STATION LONGITUDE       : "; awos_text += apt.get_awos1_lon(); awos_text += "\n";
   awos_text += "ELEVATION               : "; awos_text += apt.get_awos1_elevation(); awos_text += "\n";
   awos_text += "SURVEY METHOG           : "; awos_text += apt.get_awos1_survey_method(); awos_text += "\n";
   awos_text += "FREQUENCY               : "; awos_text += apt.get_awos1_frequency(); awos_text += "\n";
   awos_text += "FREQUENCY (2)           : "; awos_text += apt.get_awos1_frequency2(); awos_text += "\n";
   awos_text += "PHONE                   : "; awos_text += apt.get_awos1_phone(); awos_text += "\n";
   awos_text += "PHONE (2)               : "; awos_text += apt.get_awos1_phone2(); awos_text += "\n";
   awos_text += "LFSN                    : "; awos_text += apt.get_awos1_lfsn(); awos_text += "\n";
   awos_text += "CITY                    : "; awos_text += apt.get_awos1_city(); awos_text += "\n";
   awos_text += "STATE                   : "; awos_text += apt.get_awos1_st(); awos_text += "\n";
   awos_text += "INFORMATION EFF. DATE   : "; awos_text += apt.get_awos1_info_eff_date(); awos_text += "\n";
   frm->TextCtrl_AWOS->AppendText( awos_text.c_str() );
}
void OpenEagleAirportLookupFrame::OpenEagleAwos2NASR(AirportFrame* frm)
{
   std::string awos_text = "";
   awos_text += "-----------------AWOS REMARKS----------+\n";
   awos_text += "WX_SENSOR_IDENT         : "; awos_text += apt.get_awos2_wx_sensor_ident(); awos_text += "\n";
   awos_text += "WX_SENSOR_TYPE          : "; awos_text += apt.get_awos2_wx_sensor_type(); awos_text += "\n";
   awos_text += "-----------------REMARKS---------------:\n";
   awos_text += apt.get_awos2_remarks(); awos_text += "\n";
   frm->TextCtrl_AWOS->AppendText( awos_text.c_str() );
}

void OpenEagleAirportLookupFrame::OpenEagleIlsNASR(AirportFrame * frm)
{
  bool ils_records = apt.have_apt_ils_records();
  if (ils_records) {
    do {
      printf("have ils1 record\n");
      OpenEagleIls1NASR(frm);
      bool ils2_record = apt.have_ils2_record();
      if (ils2_record) {
        printf("have ils2_record\n");
        OpenEagleIls2NASR(frm);
         if (apt.have_ils3_record()){
          printf("have_ils3_record\n");
          OpenEagleIls3NASR(frm);
          if (apt.have_ils4_record()) {
            printf("have_ils4_record()\n");
            OpenEagleIls4NASR(frm);
            if (apt.have_ils5_records()) {
              do {
                OpenEagleIls5NASR(frm);
                if (apt.have_ils6_records()){
                  do {
                    OpenEagleIls6NASR(frm);
                  } while (apt.next_ils6_record());
                } else frm->Panel_ILS_Remarks->Show(false);
              } while (apt.next_ils5_record());
            }
            else frm->PanelMarkerBeacon->Show(false);
          }
          else frm->Panel_DME->Show(false);
        }
        else frm->Panel_GlideSlope->Show(false);
      }
      else {
        frm->Panel_Localizer->Show(false);
      }
    } while (apt.next_apt_ils_record());
  }
  else {
    frm->Panel_ILS->Show(false);
    frm->Panel_Localizer->Show(false);
    frm->Panel_GlideSlope->Show(false);
    frm->Panel_DME->Show(false);
    frm->PanelMarkerBeacon->Show(false);
    frm->Panel_ILS_Remarks->Show(false);
  }
}
void OpenEagleAirportLookupFrame::OpenEagleIls1NASR(AirportFrame* frm)
{
  std::string ils_text = "";
  ils_text += "--------------------ILS Information--------------------\n";
  ils_text += "LANDING FACILITY SITE NUMBER                      : ";ils_text += apt.get_ils1_lfsn();   ils_text += "\n";
  ils_text += "RUNWAY END IDENTIFIER                             : ";ils_text += apt.get_ils1_rwy_end();   ils_text += "\n";
  ils_text += "SYSTEM TYPE                                       : ";ils_text += apt.get_ils1_type();   ils_text += "\n";
  ils_text += "IDENTIFICATION CODE OF ILS                        : ";ils_text += apt.get_ils1_id_code();   ils_text += "\n";
  ils_text += "INFORMATION EFFECTIVE DATE                        : ";ils_text += apt.get_ils1_eff_date();   ils_text += "\n";
  ils_text += "AIRPORT NAME                                      : ";ils_text += apt.get_ils1_apt_name();   ils_text += "\n";
  ils_text += "CITY                                              : ";ils_text += apt.get_ils1_city();   ils_text += "\n";
  ils_text += "ST                                                : ";ils_text += apt.get_ils1_st();   ils_text += "\n";
  ils_text += "STATE NAME                                        : ";ils_text += apt.get_ils1_state_name();   ils_text += "\n";
  ils_text += "FAA REGION CODE                                   : ";ils_text += apt.get_ils1_faa_reg();   ils_text += "\n";
  ils_text += "AIRPORT IDENTIFIER                                : ";ils_text += apt.get_ils1_apt_id();   ils_text += "\n";
  ils_text += "ILS RUNWAY LENGTH                                 : ";ils_text += apt.get_ils1_length();   ils_text += "\n";
  ils_text += "ILS RUNWAY WIDTH                                  : ";ils_text += apt.get_ils1_width();   ils_text += "\n";
  ils_text += "--------------------ILS SYSTEM INFORMATION-------------\n";
  ils_text += "CATEGORY                                          : ";ils_text += apt.get_ils1_cat();   ils_text += "\n";
  ils_text += "NAME OF OWNER                                     : ";ils_text += apt.get_ils1_own_name();   ils_text += "\n";
  ils_text += "FACILITY OPERATOR                                 : ";ils_text += apt.get_ils1_fac_oper();   ils_text += "\n";
  ils_text += "APPROACH BEARING (DEG. MAGNETIC)                  : ";ils_text += apt.get_ils1_app_bearing_mag();   ils_text += "\n";
  ils_text += "MAGNETIC VARIATION                                : ";ils_text += apt.get_ils1_mag_var();   ils_text += "\n";
  frm->TextCtrl_ILS->AppendText( ils_text.c_str() );
}
void OpenEagleAirportLookupFrame::OpenEagleIls2NASR(AirportFrame* frm)
{
  std::string ils_text = "";
  ils_text += "--------------------LOCALIZER --------------------\n";
  ils_text += "LANDING FACILITY SITE NUMBER                      : ";ils_text += apt.get_ils2_lfsn();   ils_text += "\n";
  ils_text += "RUNWAY END IDENTIFIER                             : ";ils_text += apt.get_ils2_rwy_end();   ils_text += "\n";
  ils_text += "SYSTEM TYPE                                       : ";ils_text += apt.get_ils2_type();   ils_text += "\n";
  ils_text += "STATUS                                            : ";ils_text += apt.get_ils2_status();   ils_text += "\n";
  ils_text += "INFORMATION EFFECTIVE DATE                        : ";ils_text += apt.get_ils2_eff_date();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA                               : ";ils_text += apt.get_ils2_lat_ant();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA (SECONDS)                     : ";ils_text += apt.get_ils2_lat_ant_seconds();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA                              : ";ils_text += apt.get_ils2_lon_ant();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA (SECONDS)                    : ";ils_text += apt.get_ils2_lon_ant_seconds();   ils_text += "\n";
  ils_text += "LATITUDE LONGITUDE SOURCE INFORMAITON             : ";ils_text += apt.get_ils2_lat_lon_code();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM APPROACH END OF RUNWAY   : ";ils_text += apt.get_ils2_dist_frm_app_end();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM RUNWAY CENTER LINE       : ";ils_text += apt.get_ils2_dist_frm_rnwy_cl();   ils_text += "\n";
  ils_text += "DIRECTION OF ANTENNA FROM RUNWAY                  : ";ils_text += apt.get_ils2_dir_of_ant_frm_rnwy();   ils_text += "\n";
  ils_text += "CODE INDIATING SOURCE OF DISTANCE INFO            : ";ils_text += apt.get_ils2_src_dist_info();   ils_text += "\n";
  ils_text += "ELEVATION OF ANTENNA                              : ";ils_text += apt.get_ils2_elev();   ils_text += "\n";
  ils_text += "FREQUENCY OF ANTENNA                              : ";ils_text += apt.get_ils2_freq_mhz();   ils_text += "\n";
  ils_text += "BACK COURSE STATUS                                : ";ils_text += apt.get_ils2_back_crs_status();   ils_text += "\n";
  ils_text += "COURSE WIDTH                                      : ";ils_text += apt.get_ils2_course_width();   ils_text += "\n";
  ils_text += "WIDTH AT THRESHOLD                                : ";ils_text += apt.get_ils2_width_at_threshold();   ils_text += "\n";
  ils_text += "DISTANCE FROM STOP END OF RUNWAY                  : ";ils_text += apt.get_ils2_dist_from_stop();   ils_text += "\n";
  ils_text += "DIRECTION FROM STOP END OF RUNWAY                 : ";ils_text += apt.get_ils2_dir_from_stop();   ils_text += "\n";
  ils_text += "SERVICE CODE                                      : ";ils_text += apt.get_ils2_serv_code();   ils_text += "\n";
  frm->TextCtrl_Localizer->AppendText( ils_text.c_str() );
}
void OpenEagleAirportLookupFrame::OpenEagleIls3NASR(AirportFrame* frm)
{
  std::string ils_text = "";
  ils_text += "--------------------GLIDE SLOPE INFORMATION-------\n";
  ils_text += "LANDING FACILITY SITE NUMBER                      : ";ils_text += apt.get_ils3_lfsn();   ils_text += "\n";
  ils_text += "RUNWAY END IDENTIFIER                             : ";ils_text += apt.get_ils3_rwy_end();   ils_text += "\n";
  ils_text += "SYSTEM TYPE                                       : ";ils_text += apt.get_ils3_type();   ils_text += "\n";
  ils_text += "STATUS                                            : ";ils_text += apt.get_ils3_status();   ils_text += "\n";
  ils_text += "INFORMATION EFFECTIVE DATE                        : ";ils_text += apt.get_ils3_eff_date();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA                               : ";ils_text += apt.get_ils3_lat_ant();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA (SECONDS)                     : ";ils_text += apt.get_ils3_lat_ant_seconds();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA                              : ";ils_text += apt.get_ils3_lon_ant();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA (SECONDS)                    : ";ils_text += apt.get_ils3_lon_ant_seconds();   ils_text += "\n";
  ils_text += "LATITUDE LONGITUDE SOURCE INFORMAITON             : ";ils_text += apt.get_ils3_lat_lon_code();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM APPROACH END OF RUNWAY   : ";ils_text += apt.get_ils3_dist_frm_app_end();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM RUNWAY CENTER LINE       : ";ils_text += apt.get_ils3_dist_frm_rnwy_cl();   ils_text += "\n";
  ils_text += "DIRECTION OF ANTENNA FROM RUNWAY                  : ";ils_text += apt.get_ils3_dir_of_ant_frm_rnwy();   ils_text += "\n";
  ils_text += "CODE INDIATING SOURCE OF DISTANCE INFO            : ";ils_text += apt.get_ils3_src_dist_info();   ils_text += "\n";
  ils_text += "ELEVATION OF ANTENNA                              : ";ils_text += apt.get_ils3_elev();   ils_text += "\n";
  ils_text += "CLASS TYPE                                        : ";ils_text += apt.get_ils3_gsclass();   ils_text += "\n";
  ils_text += "ANGLE                                             : ";ils_text += apt.get_ils3_angle();   ils_text += "\n";
  ils_text += "FREQUENCY                                         : ";ils_text += apt.get_ils3_freq();   ils_text += "\n";
  ils_text += "ADJACENT ELEVATION                                : ";ils_text += apt.get_ils3_adj_elev();   ils_text += "\n";
  frm->TextCtrl_GlideSlope->AppendText( ils_text.c_str() );
}
void OpenEagleAirportLookupFrame::OpenEagleIls4NASR(AirportFrame* frm)
{
  std::string ils_text = "";
  ils_text += "--------------------DME---------------------------\n";
  ils_text += "LANDING FACILITY SITE NUMBER                      : ";ils_text += apt.get_ils4_lfsn();   ils_text += "\n";
  ils_text += "RUNWAY END IDENTIFIER                             : ";ils_text += apt.get_ils4_rwy_end();   ils_text += "\n";
  ils_text += "SYSTEM TYPE                                       : ";ils_text += apt.get_ils4_type();   ils_text += "\n";
  ils_text += "STATUS                                            : ";ils_text += apt.get_ils4_status();   ils_text += "\n";
  ils_text += "INFORMATION EFFECTIVE DATE                        : ";ils_text += apt.get_ils4_eff_date();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA                               : ";ils_text += apt.get_ils4_lat_ant();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA (SECONDS)                     : ";ils_text += apt.get_ils4_lat_ant_seconds();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA                              : ";ils_text += apt.get_ils4_lon_ant();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA (SECONDS)                    : ";ils_text += apt.get_ils4_lon_ant_seconds();   ils_text += "\n";
  ils_text += "LATITUDE LONGITUDE SOURCE INFORMAITON             : ";ils_text += apt.get_ils4_lat_lon_code();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM APPROACH END OF RUNWAY   : ";ils_text += apt.get_ils4_dist_frm_app_end();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM RUNWAY CENTER LINE       : ";ils_text += apt.get_ils4_dist_frm_rnwy_cl();   ils_text += "\n";
  ils_text += "DIRECTION OF ANTENNA FROM RUNWAY                  : ";ils_text += apt.get_ils4_dir_of_ant_frm_rnwy();   ils_text += "\n";
  ils_text += "CODE INDIATING SOURCE OF DISTANCE INFO            : ";ils_text += apt.get_ils4_src_dist_info();   ils_text += "\n";
  ils_text += "ELEVATION OF ANTENNA                              : ";ils_text += apt.get_ils4_elev();   ils_text += "\n";
  ils_text += "CHANNEL                                           : ";ils_text += apt.get_ils4_channel();   ils_text += "\n";
  ils_text += "DISTANCE OF DME FROM STOP END OF RUNWAY           : ";ils_text += apt.get_ils4_dist_frm_stop();   ils_text += "\n";
  frm->TextCtrl_DME->AppendText( ils_text.c_str() );
}
void OpenEagleAirportLookupFrame::OpenEagleIls5NASR(AirportFrame* frm)
{
  std::string ils_text = "";
  ils_text += "--------------------MARKER BEACON-----------------\n";
  ils_text += "LANDING FACILITY SITE NUMBER                      : ";ils_text += apt.get_ils5_lfsn();   ils_text += "\n";
  ils_text += "RUNWAY END IDENTIFIER                             : ";ils_text += apt.get_ils5_rwy_end();   ils_text += "\n";
  ils_text += "SYSTEM TYPE                                       : ";ils_text += apt.get_ils5_type();   ils_text += "\n";
  ils_text += "MARKER TYPE                                       : ";ils_text += apt.get_ils5_marker_type();   ils_text += "\n";
  ils_text += "STATUS                                            : ";ils_text += apt.get_ils5_status();   ils_text += "\n";
  ils_text += "INFORMATION EFFECTIVE DATE                        : ";ils_text += apt.get_ils5_eff_date();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA                               : ";ils_text += apt.get_ils5_lat_ant();   ils_text += "\n";
  ils_text += "LATITUDE OF ANTENNA (SECONDS)                     : ";ils_text += apt.get_ils5_lat_ant_seconds();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA                              : ";ils_text += apt.get_ils5_lon_ant();   ils_text += "\n";
  ils_text += "LONGITUDE OF ANTENNA (SECONDS)                    : ";ils_text += apt.get_ils5_lon_ant_seconds();   ils_text += "\n";
  ils_text += "LATITUDE LONGITUDE SOURCE INFORMAITON             : ";ils_text += apt.get_ils5_lat_lon_code();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM APPROACH END OF RUNWAY   : ";ils_text += apt.get_ils5_dist_frm_app_end();   ils_text += "\n";
  ils_text += "DISTANCE OF ANTENNA FROM RUNWAY CENTER LINE       : ";ils_text += apt.get_ils5_dist_frm_rnwy_cl();   ils_text += "\n";
  ils_text += "DIRECTION OF ANTENNA FROM RUNWAY                  : ";ils_text += apt.get_ils5_dir_of_ant_frm_rnwy();   ils_text += "\n";
  ils_text += "CODE INDIATING SOURCE OF DISTANCE INFO            : ";ils_text += apt.get_ils5_src_dist_info();   ils_text += "\n";
  ils_text += "ELEVATION OF ANTENNA                              : ";ils_text += apt.get_ils5_elev();   ils_text += "\n";
  ils_text += "FACILITY TYPE                                     : ";ils_text += apt.get_ils5_fac_type();   ils_text += "\n";
  ils_text += "LOCATION IDENTIFIER OF BEACON AT MARKER           : ";ils_text += apt.get_ils5_loc_id();   ils_text += "\n";
  ils_text += "NAME OF MARKER LOACTOR BEACON                     : ";ils_text += apt.get_ils5_name();   ils_text += "\n";
  ils_text += "FREQUENCY OF BEACON AT MIDDLE MARKER (KHZ)        : ";ils_text += apt.get_ils5_freq();   ils_text += "\n";
  ils_text += "LOCATION ID OF NAVAID TYPE                        : ";ils_text += apt.get_ils5_navaid_type();   ils_text += "\n";
  ils_text += "LOW POWERED NDB STATUS                            : ";ils_text += apt.get_ils5_low_ndb_status();   ils_text += "\n";
  ils_text += "SERVICE PROVED BY MARKER                          : ";ils_text += apt.get_ils5_serv_provided();   ils_text += "\n";
  frm->TextCtrl_MarkerBeacon->AppendText( ils_text.c_str() );
}
void OpenEagleAirportLookupFrame::OpenEagleIls6NASR(AirportFrame* frm)
{
  std::string ils_text = "";
  ils_text += "--------------------ILS SYSTEM REMARKS------------\n";
  ils_text += "LANDING FACILITY SITE NUMBER                      : ";ils_text += apt.get_ils6_lfsn();   ils_text += "\n";
  ils_text += "RUNWAY END IDENTIFIER                             : ";ils_text += apt.get_ils6_rwy_end();   ils_text += "\n";
  ils_text += "SYSTEM TYPE                                       : ";ils_text += apt.get_ils6_type();   ils_text += "\n";
  ils_text += "--------------------REMARK:-----------------------\n";
  ils_text += apt.get_ils6_remarks();   ils_text += "\n";
  frm->TextCtrl_Remarks->AppendText( ils_text.c_str() );
}


void OpenEagleAirportLookupFrame::OnTextCtrlAirport_IDTextEnter(wxCommandEvent& event)
{
    wxString airport_id = TextCtrlAirport_ID->GetLineText(0);
    std::string airport_id_str = std::string(airport_id.mb_str());
    printf("airport_id [%s]\n",airport_id_str.c_str());
    bool apt_exists = apt.lookup_airport_and_set_current((char *)airport_id_str.c_str());
    if (!apt_exists) {
      wxMessageBox("No Joy!");
      StaticText_ICAO_ID->Show(false);
      TextCtrl_ICAO_ID->Show(false);
      TextCtrl_Apt_Name->Show(false);
      TextCtrl_AptCitySt->Show(false);
      StaticText_Elevation->Show(false);
      TextCtrl_Apt_Elevation->Show(false);
      StaticText_TP_Altitude->Show(false);
      TextCtrl_TP_Alt->Show(false);
      StaticTextRunways->Show(false);
      ListBoxAptRunway->Show(false);
      ButtonAptInformation->Show(false);
      ButtonAptFrequencies->Show(false);

    }
    else {
      if (CheckBox_DoFullNASR->GetValue()) {
        StaticText_ICAO_ID->Show(false);
        TextCtrl_ICAO_ID->Show(false);
        TextCtrl_Apt_Name->Show(false);
        TextCtrl_AptCitySt->Show(false);
        StaticText_Elevation->Show(false);
        TextCtrl_Apt_Elevation->Show(false);
        StaticText_TP_Altitude->Show(false);
        TextCtrl_TP_Alt->Show(false);
        StaticTextRunways->Show(false);
        ListBoxAptRunway->Show(false);
        ButtonAptInformation->Show(false);
        ButtonAptFrequencies->Show(false);
        OpenEagleFullNASR(airport_id);
      }
      else OpenEagleBriefNASR(airport_id);

    }
}



void OpenEagleAirportLookupFrame::OnTextCtrlAirport_IDText2(wxCommandEvent& event)
{
}

void OpenEagleAirportLookupFrame::OnButtonAptInformationClick(wxCommandEvent& event)
{
   InformationFrame * frm = new InformationFrame(this);

 	wxFont TextCtrlBodyFont(14,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	frm->TextCtrlBody->SetFont(TextCtrlBodyFont);

   std::string caption = "Information for Airport: ";
   caption += apt.get_location_identifier();


   frm->TextCtrlBody->Clear();
   std::string apt_text = "";
   apt_text += "Type: ";   apt_text +=apt.get_airport_type(); apt_text +="\n";
   apt_text += "Cycle Date           : ";   apt_text +=apt.get_airport_effective_date(); apt_text +="\n";
   apt_text += "--------------------Demographic Data--------------------\n";
   apt_text += "FAA Region           : ";   apt_text +=apt.get_faa_region_code(); apt_text += "\n";
   apt_text += "FAA District         : ";   apt_text +=apt.get_faa_district_office(); apt_text += "\n";
    apt_text += "--------------------Ownership Data--------------------\n";
   apt_text += "Type                 : ";   apt_text +=apt.get_ownership_type(); apt_text += "\n";
   apt_text += "Use                  : ";   apt_text +=apt.get_facility_use(); apt_text += "\n";
   apt_text += "Name                 : ";   apt_text +=remove_trailing_spaces(apt.get_own_name()); apt_text += "\n";
   apt_text += "Address              : ";   apt_text +=remove_trailing_spaces(apt.get_own_addr()); apt_text += "\n";
   apt_text += "City                 : ";   apt_text +=remove_trailing_spaces(apt.get_own_city()); apt_text += "\n";
   apt_text += "Phone                : ";   apt_text +=apt.get_own_phone(); apt_text += "\n";
   apt_text += "Manager Name         : ";   apt_text +=apt.get_mgr_name(); apt_text += "\n";
   apt_text += "Manager Address      : ";   apt_text +=remove_trailing_spaces(apt.get_mgr_addr()); apt_text += "\n";
   apt_text += "Manager City         : ";   apt_text +=remove_trailing_spaces(apt.get_mgr_city()); apt_text += "\n";
   apt_text += "Manager Phone        : ";   apt_text +=apt.get_mgr_phone(); apt_text += "\n";
   apt_text += "--------------------Geographic Data--------------------\n";
   apt_text += "Latitude (formatted) : ";  apt_text +=apt.get_airport_latitude_formatted();  apt_text += "\n";
   apt_text += "Longitude (formatted): ";  apt_text +=apt.get_airport_longitude_formatted(); apt_text += "\n";
   apt_text += "Magnetic Variation   : ";  apt_text +=apt.get_airport_mag_var();             apt_text += "\n";
   apt_text += "Variation Epoch Year : ";  apt_text +=apt.get_airport_mag_var_epoch_yr();    apt_text += "\n";
   apt_text += "Section Chart        : ";  apt_text +=apt.get_section_chart();              apt_text += "\n";
   apt_text += "--------------------FAA SERVICES---------------------";apt_text += "\n";
   apt_text += "Boundary ARTCC       : "; apt_text +=apt.get_boundary_artcc();         apt_text += "\n";
   apt_text += "ARTCC FAA            : "; apt_text +=apt.get_boundary_artcc_faa();     apt_text += "\n";
   apt_text += "ARTCC Name           : "; apt_text +=apt.get_boundary_artcc_name();   apt_text += "\n";
   apt_text += "ARTCC Rep ID         : "; apt_text +=apt.get_resp_artcc_rep_id();      apt_text += "\n";
   apt_text += "ARTCC_FAA            : "; apt_text +=apt.get_resp_artcc_faa();         apt_text += "\n";
   apt_text += "ARTCC Name           : "; apt_text +=apt.get_resp_artcc_name();       apt_text += "\n";
   apt_text += "Tie In Physical      : "; apt_text +=apt.get_tie_in_phys();            apt_text += "\n";
   apt_text += "Tie In ID            : "; apt_text +=apt.get_tie_in_id();              apt_text += "\n";
   apt_text += "Tie In Name          : "; apt_text +=apt.get_tie_in_name();           apt_text += "\n";
   apt_text += "Local Phone          : "; apt_text +=apt.get_local_phone();           apt_text += "\n";
   apt_text += "Toll Free Phone      : "; apt_text +=apt.get_toll_free_phone();       apt_text += "\n";
   apt_text += "Alt FSS ID           : "; apt_text +=apt.get_alt_fss_id();             apt_text += "\n";
   apt_text += "Alt FSS Name         : "; apt_text +=apt.get_alt_fss_name();          apt_text += "\n";
   apt_text += "Alt FSS Toll Free    : "; apt_text +=apt.get_alt_fss_toll_free();     apt_text += "\n";
   apt_text += "Notam ID             : "; apt_text +=apt.get_notam_id();               apt_text += "\n";
   apt_text += "Notam Available      : "; apt_text +=apt.get_notam_available();        apt_text += "\n";
   apt_text += "--------------------FEDERAL STATUS-----------------";  apt_text += "\n";
   apt_text += "Airport Status Code  : "; apt_text +=apt.get_airport_status_code();    apt_text += "\n";
   apt_text += "Customs POE          : "; apt_text +=apt.get_airport_customs_poe();    apt_text += "\n";
   apt_text += "Customs Landing      : "; apt_text +=apt.get_airport_customs_landing();apt_text += "\n";
   apt_text += "--------------------AIRPORT SERVICES-----------------";  apt_text += "\n";
   apt_text += "Fuel Types           : "; apt_text +=apt.get_fuel_types();            apt_text += "\n";
   apt_text += "Airframe Repair      : "; apt_text +=apt.get_airframe_repair();        apt_text += "\n";
   apt_text += "Powerplant Repair    : "; apt_text +=apt.get_powerplant_repair();      apt_text += "\n";
   apt_text += "Bottled Oxygen       : "; apt_text +=apt.get_bottled_oxy();            apt_text += "\n";
   apt_text += "Bulk Oxygen          : "; apt_text +=apt.get_bulk_oxy();               apt_text += "\n";
   apt_text += "--------------------AIRPORT FACILITIES-----------------";  apt_text += "\n";
   apt_text += "Light Sched          : "; apt_text +=apt.get_light_sched();            apt_text += "\n";
   apt_text += "Beacon Light Sched   : "; apt_text +=apt.get_beacon_light_sched();     apt_text += "\n";
   apt_text += "Has Tower            : "; apt_text +=apt.get_airport_has_tower();      apt_text += "\n";
   apt_text += "Segment Circle Marker: "; apt_text +=apt.get_segment_circle_marker();  apt_text += "\n";
   apt_text += "Lense Color          : "; apt_text +=apt.get_lens_color();             apt_text += "\n";
   apt_text += "Landing Fee          : "; apt_text +=apt.get_landing_fee();            apt_text += "\n";
///  attendance records
  bool attendance_records = apt.have_attendance_records();
  if (attendance_records) {
  apt_text += "--------------------ATTENDANCE--------------------"; apt_text += "\n";
    do {
  apt_text += "Attendance Schedule  : "; apt_text += apt.get_att_sched(); apt_text += "\n";

    } while (apt.next_attendance_record());
  }

  bool remark_records = apt.have_remark_records();
   if (remark_records) {
   apt_text += "--------------------REMARKS--------------------"; apt_text += "\n";

     do {
   char * text = apt.get_rmk_text();
   //printf("remarks text start  [%s]\n",text);
   remove_trailing_spaces(text);
   //printf("remarks text space  [%s]\n",text);
   add_eol_after_column_on_period(text, 10);
   //printf("remarks text .      [%s]\n",text);
   add_eol_after_column(text, 55);
   //printf("remarks text final  [%s]\n",text);
   apt_text += text;
   apt_text += "\n";
     } while (apt.next_remark_record());
   }
   frm->TextCtrlBody->AppendText(apt_text.c_str());
   frm->Show(true);

}

void OpenEagleAirportLookupFrame::OnButtonAptFrequenciesClick(wxCommandEvent& event)
{
  InformationFrame * frm = new InformationFrame(this);
 	wxFont TextCtrlBodyFont(14,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	frm->TextCtrlBody->SetFont(TextCtrlBodyFont);

   std::string caption = "Frequencies for Airport: ";
   caption += apt.get_location_identifier();
   frm->SetTitle(caption);


  frm->TextCtrlBody->Clear();
  std::string apt_text = "";
  apt_text += apt.get_unicom(); apt_text +=" : UNICOM\n";
  apt_text += apt.get_ctaf();   apt_text +=" : CTAF\n";

  bool twr1_record = apt.have_twr1_record();
  if (twr1_record) {
    bool have_twr3 = apt.have_twr3_records();
    if (have_twr3) {
      printf("have twr3\n");
      do {
   for (int i = 0; i<9; i++) {
     if (apt.get_twr3_use(i)[0] != ' ') {
       apt_text += remove_trailing_spaces(apt.get_twr3_freq(i));
       apt_text += " : "; apt_text += remove_trailing_spaces(apt.get_twr3_use(i));  apt_text += "\n";
     }
   }

      } while (apt.next_twr3_record());
    }

    bool have_twr6 = apt.have_twr6_records();
    if (have_twr6) {
      apt_text += "-----------------Remarks------------------+\n";
      printf("have twr6\n");
      do {

   char * text = apt.get_twr6_remark();
   remove_trailing_spaces(text);
   add_eol_after_column(text, 40);
   add_eol_after_column_on_period(text, 10);
   apt_text += text; apt_text += "\n";

      } while (apt.next_twr6_record());
    }

    bool have_twr9 = apt.have_twr9_records();
    if (have_twr9) {
      printf("have twr9\n");
      do {
 //  apt_text += "ATIS SERIAL NUMBER                      : "; apt_text += apt->get_twr9_sn();      apt_text += "\n";
   apt_text += "ATIS HOURS : "; apt_text += apt.get_twr9_hours();      apt_text += "\n";
   if (apt.get_twr9_purpose()[0] != ' ') {
   apt_text += "ATIS PURPOSE : "; apt_text += apt.get_twr9_purpose();      apt_text += "\n";
   }
   if (apt.get_twr9_phone()[0]!= ' ') {
   apt_text += "PHONE NUMBER                            : "; apt_text += apt.get_twr9_phone();      apt_text += "\n";
   }
      } while (apt.next_twr9_record());
    }
  }


  frm->TextCtrlBody->AppendText(apt_text.c_str());
  frm->Show(true);
}

void OpenEagleAirportLookupFrame::OnListBoxAptRunwayDClick(wxCommandEvent& event)
{
  printf("double click on ListBoxAptRunway....\n");
  int i = ListBoxAptRunway->GetSelection();
  printf("selection is [%d]\n",i);
  //bool have_runways =
  apt.have_runway_records();
  int j = 0;

  bool b = true;
//  bool r = false;
  while (i != j) {
    j++;
    if (b) {
      b = false;
  //    r = true;
    }
    else {
    //  r = false;
      b=true;
      apt.next_runway_record();
    }
  }

  if (b) {
    printf("selected b [%s]\n",apt.get_b_id());
  }
  else {
    printf("selected r [%s]\n",apt.get_r_id());
  }

  InformationFrame * frm = new InformationFrame(this);

   std::string caption = "Information for Airport: ";
   caption += apt.get_location_identifier();
   caption += " Runway: ";
   if (b) caption += apt.get_b_id(); else caption += apt.get_r_id();
   frm->SetTitle(caption);
   frm->TextCtrlBody->Clear();
  std::string apt_text = "";

  if (b) {

   apt_text += "length              : "; apt_text += apt.get_runway_length(); apt_text += "\n"; //R AN 0005 00024  A31     PHYSICAL RUNWAY LENGTH (NEAREST FOOT)
   apt_text += "width               : "; apt_text += apt.get_runway_width(); apt_text += "\n"; //R AN 0004 00029  A32     PHYSICAL RUNWAY WIDTH (NEAREST FOOT)
   apt_text += "surface type cond   : "; apt_text += apt.get_runway_surface_type_cond(); apt_text += "\n"; //L AN 0012 00033  A33     RUNWAY SURFACE TYPE AND CONDITION
   char* test = apt.get_runway_surface_treatment();
   if (test[0]!= ' ') {
   apt_text += "surface treatment   : "; apt_text += apt.get_runway_surface_treatment(); apt_text += "\n"; //L AN 0005 00045  A34     RUNWAY SURFACE TREATMENT
   }
   if (apt.get_runway_pcn()[0] != ' ') {
   apt_text += "runway PCN          : "; apt_text += apt.get_runway_pcn();                  apt_text += "\n"; //L AN 0011 00050  A39     PAVEMENT CLASSIFICATION NUMBER (PCN)
   }
   apt_text += "Light Edge Intensity: "; apt_text += apt.get_runway_light_edge_intensity(); apt_text += "\n"; //L AN 0005 00061  A40     RUNWAY LIGHTS EDGE INTENSITY
   apt_text += "End Identifier      : "; apt.get_b_id();                                    apt_text += " :\n";
   apt_text += "True Alignment      : "; apt.get_b_true_alignment();                        apt_text += " :\n";
   apt_text += "ILS Type            : "; apt.get_b_ils_type();                              apt_text += " :\n";
   if (apt.get_b_rh_traffic()[0]!= ' ') {
   apt_text += "RH traffic          : "; apt_text += apt.get_b_rh_traffic();                apt_text += " :\n";
   }
   apt_text += "Runway Markings     : "; apt_text += apt.get_b_rwy_markings();              apt_text += " :\n";
   apt_text += "Runway Condition    : "; apt_text += apt.get_b_rwy_condition();             apt_text += " :\n";
   apt_text += "Latitude            : "; apt_text += apt.get_b_latitude();                  apt_text += " :\n";
   apt_text += "Longitude           : "; apt_text += apt.get_b_longitude();                 apt_text += " :\n";
   apt_text += "Elevation           : "; apt_text += apt.get_b_elevation();                 apt_text += " :\n";
   if (apt.get_b_threshold_xheight()[0] != ' '){
   apt_text += "Threshold Cross Hgt : "; apt_text += apt.get_b_threshold_xheight();         apt_text += " :\n";
   }
   if (apt.get_b_glide_slope()[0] != ' ') {
   apt_text += "Glide Slope         : "; apt_text += apt.get_b_glide_slope();               apt_text += " :\n";
   }
   if (apt.get_b_dt_latitude()[0]!= ' ') {
   apt_text += "-Displace Threshold-+\n";
   apt_text += "Latitude            : "; apt_text += apt.get_b_dt_latitude();               apt_text += " :\n";
   apt_text += "Latitude (seconds)  : "; apt_text += apt.get_b_dt_latitude_seconds();       apt_text += " :\n";
   apt_text += "Longitude           : "; apt_text += apt.get_b_dt_longitude();              apt_text += " :\n";
   apt_text += "Longitude (seconds) : "; apt_text += apt.get_b_dt_longitude_seconds();      apt_text += " :\n";
   apt_text += "Elevation           : "; apt_text += apt.get_b_dt_elevation();              apt_text += " :\n";
   apt_text += "Length              : "; apt_text += apt.get_b_dt_length();                 apt_text += " :\n";
   apt_text += "Elevation at TD     : "; apt_text += apt.get_b_dt_elev_at_td();             apt_text += " :\n";
   apt_text += "-Displace Threshold-+\n";
   }
   apt_text += "---Lighting Data----+\n";
   apt_text += "Glide Slope         : "; apt_text += apt.get_b_glide_slope_ind();           apt_text += " :\n";
   apt_text += "Visual Value Eq.    : "; apt_text += apt.get_b_rvv();                       apt_text += " :\n";
   apt_text += "Approach            : "; apt_text += apt.get_b_approach_lights();           apt_text += " :\n";
   apt_text += "Runway End Lgts REIL: "; apt_text += apt.get_b_reil();                      apt_text += " :\n";
   apt_text += "Center Line         : "; apt_text += apt.get_b_ctr_ln_lights();             apt_text += " :\n";
   apt_text += "Touch Down          : "; apt_text += apt.get_b_td_lights();                 apt_text += " :\n";
   apt_text += "---Lighting Data----+\n";
   if (apt.get_b_object()[0] != ' ') {
   apt_text += "-----Object Data----+\n";
   apt_text += "Object Description  : "; apt_text += apt.get_b_object();                    apt_text += " :\n";
   apt_text += "Marked - Lighted    : "; apt_text += apt.get_b_marked_lighted();            apt_text += " :\n";
   apt_text += "FAA CFR 77          : "; apt_text += apt.get_b_faa_cfr_77();                apt_text += " :\n";
   apt_text += "Clearance Slope     : "; apt_text += apt.get_b_clearance_slope();           apt_text += " :\n";
   apt_text += "Height Above Runway : "; apt_text += apt.get_b_height_above_rwy();          apt_text += " :\n";
   apt_text += "Distance from Runway: "; apt_text += apt.get_b_dist_from_rwy();             apt_text += " :\n";
   apt_text += "Center Line Offset  : "; apt_text += apt.get_b_center_line_offset();        apt_text += " :\n";
   apt_text += "-----Object Data----+\n";
   }
   if (apt.get_b_runway_end_gradient()[0] != ' ') {
   apt_text += "Runway End Gradient : "; apt_text += apt.get_b_runway_end_gradient();       apt_text += " :\n";
   apt_text += "Runway End Grad Dir : "; apt_text += apt.get_b_runway_end_gradient_dir();   apt_text += " :\n";
   }
   if (apt.get_b_tora()[0] != ' ') {
   apt_text += "TORA                : "; apt_text += apt.get_b_tora();                      apt_text += " :\n";
   apt_text += "TODA                : "; apt_text += apt.get_b_toda();                      apt_text += " :\n";
   apt_text += "ASDA                : "; apt_text += apt.get_b_asda();                      apt_text += " :\n";
   apt_text += "LDA                 : "; apt_text += apt.get_b_lda();                       apt_text += " :\n";
   }
   if (apt.get_b_lahso()[0] != ' ') {
   apt_text += "LAHSO Landing Dist  : "; apt_text += apt.get_b_lahso();                     apt_text += " :\n";
   apt_text += "LAHSO ID Int RWY    : "; apt_text += apt.get_b_id_int_rw();                 apt_text += " :\n";
   apt_text += "LAHSO Ent Def Pt B  : "; apt_text += apt.get_b_id_desc_ent();                apt_text += "\n";
   apt_text += "LAHSO Lat.          : "; apt_text += apt.get_b_lat_lahso();             apt_text += " :\n";
   apt_text += "LAHSO Long.         : "; apt_text += apt.get_b_lon_lahso();             apt_text += " :\n";
   }

  }
  else { // r

   apt_text += "length              : "; apt_text += apt.get_runway_length(); apt_text += "\n"; //R AN 0005 00024  A31     PHYSICAL RUNWAY LENGTH (NEAREST FOOT)
   apt_text += "width               : "; apt_text += apt.get_runway_width(); apt_text += "\n"; //R AN 0004 00029  A32     PHYSICAL RUNWAY WIDTH (NEAREST FOOT)
   apt_text += "surface type cond   : "; apt_text += apt.get_runway_surface_type_cond(); apt_text += "\n"; //L AN 0012 00033  A33     RUNWAY SURFACE TYPE AND CONDITION
   char* test = apt.get_runway_surface_treatment();
   if (test[0]!= ' ') {
   apt_text += "surface treatment   : "; apt_text += apt.get_runway_surface_treatment(); apt_text += "\n"; //L AN 0005 00045  A34     RUNWAY SURFACE TREATMENT
   }
   if (apt.get_runway_pcn()[0] != ' ') {
   apt_text += "runway PCN          : "; apt_text += apt.get_runway_pcn();                  apt_text += "\n"; //L AN 0011 00050  A39     PAVEMENT CLASSIFICATION NUMBER (PCN)
   }
   apt_text += "Light Edge Intensity: "; apt_text += apt.get_runway_light_edge_intensity(); apt_text += "\n"; //L AN 0005 00061  A40     RUNWAY LIGHTS EDGE INTENSITY
   apt_text += "End Identifier      : "; apt.get_r_id();                                    apt_text += " :\n";
   apt_text += "True Alignment      : "; apt.get_r_true_alignment();                        apt_text += " :\n";
   apt_text += "ILS Type            : "; apt.get_r_ils_type();                              apt_text += " :\n";
   if (apt.get_r_rh_traffic()[0]!= ' ') {
   apt_text += "RH traffic          : "; apt_text += apt.get_r_rh_traffic();                apt_text += " :\n";
   }
   apt_text += "Runway Markings     : "; apt_text += apt.get_r_rwy_markings();              apt_text += " :\n";
   apt_text += "Runway Condition    : "; apt_text += apt.get_r_rwy_condition();             apt_text += " :\n";
   apt_text += "Latitude            : "; apt_text += apt.get_r_latitude();                  apt_text += " :\n";
   apt_text += "Longitude           : "; apt_text += apt.get_r_longitude();                 apt_text += " :\n";
   apt_text += "Elevation           : "; apt_text += apt.get_r_elevation();                 apt_text += " :\n";
   if (apt.get_r_threshold_xheight()[0] != ' '){
   apt_text += "Threshold Cross Hgt : "; apt_text += apt.get_r_threshold_xheight();         apt_text += " :\n";
   }
   if (apt.get_r_glide_slope()[0] != ' ') {
   apt_text += "Glide Slope         : "; apt_text += apt.get_r_glide_slope();               apt_text += " :\n";
   }
   if (apt.get_r_dt_latitude()[0]!= ' ') {
   apt_text += "-Displace Threshold-+\n";
   apt_text += "Latitude            : "; apt_text += apt.get_r_dt_latitude();               apt_text += " :\n";
   apt_text += "Latitude (seconds)  : "; apt_text += apt.get_r_dt_latitude_seconds();       apt_text += " :\n";
   apt_text += "Longitude           : "; apt_text += apt.get_r_dt_longitude();              apt_text += " :\n";
   apt_text += "Longitude (seconds) : "; apt_text += apt.get_r_dt_longitude_seconds();      apt_text += " :\n";
   apt_text += "Elevation           : "; apt_text += apt.get_r_dt_elevation();              apt_text += " :\n";
   apt_text += "Length              : "; apt_text += apt.get_r_dt_length();                 apt_text += " :\n";
   apt_text += "Elevation at TD     : "; apt_text += apt.get_r_dt_elev_at_td();             apt_text += " :\n";
   apt_text += "-Displace Threshold-+\n";
   }
   apt_text += "---Lighting Data----+\n";
   apt_text += "Glide Slope         : "; apt_text += apt.get_r_glide_slope_ind();           apt_text += " :\n";
   apt_text += "Visual Value Eq.    : "; apt_text += apt.get_r_rvv();                       apt_text += " :\n";
   apt_text += "Approach            : "; apt_text += apt.get_r_approach_lights();           apt_text += " :\n";
   apt_text += "Runway End Lgts REIL: "; apt_text += apt.get_r_reil();                      apt_text += " :\n";
   apt_text += "Center Line         : "; apt_text += apt.get_r_ctr_ln_lights();             apt_text += " :\n";
   apt_text += "Touch Down          : "; apt_text += apt.get_r_td_lights();                 apt_text += " :\n";
   apt_text += "---Lighting Data----+\n";
   if (apt.get_r_object()[0] != ' ') {
   apt_text += "-----Object Data----+\n";
   apt_text += "Object Description  : "; apt_text += apt.get_r_object();                    apt_text += " :\n";
   apt_text += "Marked - Lighted    : "; apt_text += apt.get_r_marked_lighted();            apt_text += " :\n";
   apt_text += "FAA CFR 77          : "; apt_text += apt.get_r_faa_cfr_77();                apt_text += " :\n";
   apt_text += "Clearance Slope     : "; apt_text += apt.get_r_clearance_slope();           apt_text += " :\n";
   apt_text += "Height Above Runway : "; apt_text += apt.get_r_height_above_rwy();          apt_text += " :\n";
   apt_text += "Distance from Runway: "; apt_text += apt.get_r_dist_from_rwy();             apt_text += " :\n";
   apt_text += "Center Line Offset  : "; apt_text += apt.get_r_center_line_offset();        apt_text += " :\n";
   apt_text += "-----Object Data----+\n";
   }
   if (apt.get_r_runway_end_gradient()[0] != ' ') {
   apt_text += "Runway End Gradient : "; apt_text += apt.get_r_runway_end_gradient();       apt_text += " :\n";
   apt_text += "Runway End Grad Dir : "; apt_text += apt.get_r_runway_end_gradient_dir();   apt_text += " :\n";
   }
   if (apt.get_r_tora()[0] != ' ') {
   apt_text += "TORA                : "; apt_text += apt.get_r_tora();                      apt_text += " :\n";
   apt_text += "TODA                : "; apt_text += apt.get_r_toda();                      apt_text += " :\n";
   apt_text += "ASDA                : "; apt_text += apt.get_r_asda();                      apt_text += " :\n";
   apt_text += "LDA                 : "; apt_text += apt.get_r_lda();                       apt_text += " :\n";
   }
   if (apt.get_r_lahso()[0] != ' ') {
   apt_text += "LAHSO Landing Dist  : "; apt_text += apt.get_r_lahso();                     apt_text += " :\n";
   apt_text += "LAHSO ID Int RWY    : "; apt_text += apt.get_r_id_int_rw();                 apt_text += " :\n";
   apt_text += "LAHSO Ent Def Pt B  : "; apt_text += apt.get_r_id_desc_ent();                apt_text += "\n";
   apt_text += "LAHSO Lat.          : "; apt_text += apt.get_r_lat_lahso();             apt_text += " :\n";
   apt_text += "LAHSO Long.         : "; apt_text += apt.get_r_lon_lahso();             apt_text += " :\n";
   }

  }

  frm->TextCtrlBody->AppendText(apt_text.c_str());
  frm->Show(true);

}
