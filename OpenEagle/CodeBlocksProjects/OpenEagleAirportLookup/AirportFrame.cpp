/***************************************************************
 * Name:      AirportFrame.cpp
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
#include "AirportFrame.h"

//(*InternalHeaders(AirportFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(AirportFrame)
const long AirportFrame::ID_TEXTCTRL_AIRPORT = wxNewId();
const long AirportFrame::ID_PANEL_AIRPORT = wxNewId();
const long AirportFrame::ID_TEXTCTRL_ATTENDENCE = wxNewId();
const long AirportFrame::ID_PANEL_ATT = wxNewId();
const long AirportFrame::ID_TEXTCTRL_RUNWAY = wxNewId();
const long AirportFrame::ID_PANEL_RWY = wxNewId();
const long AirportFrame::ID_TEXTCTRL_ARRESTING_SYSTEMS = wxNewId();
const long AirportFrame::ID_PANEL_ArrSys = wxNewId();
const long AirportFrame::ID_TEXTCTRL_REMARKS = wxNewId();
const long AirportFrame::ID_PANEL_Remarks = wxNewId();
const long AirportFrame::ID_TEXTCTRL_TOWER = wxNewId();
const long AirportFrame::ID_PANEL_TOWER = wxNewId();
const long AirportFrame::ID_TEXTCTRL_HOURS = wxNewId();
const long AirportFrame::ID_PANEL_HOURS = wxNewId();
const long AirportFrame::ID_TEXTCTRL_FREQUENCIES = wxNewId();
const long AirportFrame::ID_PANEL_FREQUENCIES = wxNewId();
const long AirportFrame::ID_TEXTCTRL_SERVICES = wxNewId();
const long AirportFrame::ID_PANEL_SERVICES = wxNewId();
const long AirportFrame::ID_TEXTCTRL_RADAR = wxNewId();
const long AirportFrame::ID_PANEL_RADAR = wxNewId();
const long AirportFrame::ID_TEXTCTRL_TWR_REMARKS = wxNewId();
const long AirportFrame::ID_PANEL_REMARKS = wxNewId();
const long AirportFrame::ID_TEXTCTRL_SATELLITE = wxNewId();
const long AirportFrame::ID_PANEL_SATELLITE = wxNewId();
const long AirportFrame::ID_TEXTCTRL_CLASS_BCDE = wxNewId();
const long AirportFrame::ID_PANEL_CLASS_BCDE = wxNewId();
const long AirportFrame::ID_TEXTCTRL_ATIS = wxNewId();
const long AirportFrame::ID_PANEL_ATIS = wxNewId();
const long AirportFrame::ID_TEXTCTRL_AWOS = wxNewId();
const long AirportFrame::ID_PANEL_AWOS = wxNewId();
const long AirportFrame::ID_TEXTCTRL_ILS = wxNewId();
const long AirportFrame::ID_PANEL_ILS = wxNewId();
const long AirportFrame::ID_TEXTCTRL_LOCALIZER = wxNewId();
const long AirportFrame::ID_PANEL_LOCALIZER = wxNewId();
const long AirportFrame::ID_TEXTCTRL_GLIDE_SLOPE = wxNewId();
const long AirportFrame::ID_PANEL_GLIDE_SLOPE = wxNewId();
const long AirportFrame::ID_TEXTCTRL_DME = wxNewId();
const long AirportFrame::ID_PANEL_DMD = wxNewId();
const long AirportFrame::ID_TEXTCTRL_MARKER_BEACON = wxNewId();
const long AirportFrame::ID_PANEL_MARKER_BEACON = wxNewId();
const long AirportFrame::ID_TEXTCTRL_ILS_REMARKS = wxNewId();
const long AirportFrame::ID_PANEL_ILS_REMARKS = wxNewId();
const long AirportFrame::ID_NOTEBOOK_AIRPORT = wxNewId();
const long AirportFrame::ID_PANEL_AIRPORT_FRAME = wxNewId();
//*)

BEGIN_EVENT_TABLE(AirportFrame,wxFrame)
	//(*EventTable(AirportFrame)
	//*)
END_EVENT_TABLE()

AirportFrame::AirportFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(AirportFrame)
	Create(parent, id, _("Airport Data"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(600,650));
	Move(wxDefaultPosition);
	Panel_AirportFrame = new wxPanel(this, ID_PANEL_AIRPORT_FRAME, wxPoint(104,56), wxSize(580,500), wxTAB_TRAVERSAL, _T("ID_PANEL_AIRPORT_FRAME"));
	Notebook_Airport = new wxNotebook(Panel_AirportFrame, ID_NOTEBOOK_AIRPORT, wxPoint(16,16), wxSize(570,620), 0, _T("ID_NOTEBOOK_AIRPORT"));
	Panel_Airport = new wxPanel(Notebook_Airport, ID_PANEL_AIRPORT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_AIRPORT"));
	TextCtrl_Airport = new wxTextCtrl(Panel_Airport, ID_TEXTCTRL_AIRPORT, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_AIRPORT"));
	wxFont TextCtrl_AirportFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Airport->SetFont(TextCtrl_AirportFont);
	Panel_Att = new wxPanel(Notebook_Airport, ID_PANEL_ATT, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_ATT"));
	wxFont Panel_AttFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	Panel_Att->SetFont(Panel_AttFont);
	TextCtrl_Attendance = new wxTextCtrl(Panel_Att, ID_TEXTCTRL_ATTENDENCE, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_ATTENDENCE"));
	wxFont TextCtrl_AttendanceFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Attendance->SetFont(TextCtrl_AttendanceFont);
	Panel_Rwy = new wxPanel(Notebook_Airport, ID_PANEL_RWY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_RWY"));
	wxFont Panel_RwyFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	Panel_Rwy->SetFont(Panel_RwyFont);
	TextCtrl_Runway = new wxTextCtrl(Panel_Rwy, ID_TEXTCTRL_RUNWAY, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_RUNWAY"));
	wxFont TextCtrl_RunwayFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Runway->SetFont(TextCtrl_RunwayFont);
	PanelArrSys = new wxPanel(Notebook_Airport, ID_PANEL_ArrSys, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_ArrSys"));
	wxFont PanelArrSysFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	PanelArrSys->SetFont(PanelArrSysFont);
	TextCtrl_ArrestingSystems = new wxTextCtrl(PanelArrSys, ID_TEXTCTRL_ARRESTING_SYSTEMS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_ARRESTING_SYSTEMS"));
	wxFont TextCtrl_ArrestingSystemsFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_ArrestingSystems->SetFont(TextCtrl_ArrestingSystemsFont);
	PanelRemarks = new wxPanel(Notebook_Airport, ID_PANEL_Remarks, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_Remarks"));
	TextCtrlRemarks = new wxTextCtrl(PanelRemarks, ID_TEXTCTRL_REMARKS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_REMARKS"));
	wxFont TextCtrlRemarksFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrlRemarks->SetFont(TextCtrlRemarksFont);
	PanelTower = new wxPanel(Notebook_Airport, ID_PANEL_TOWER, wxDefaultPosition, wxSize(550,570), wxTAB_TRAVERSAL, _T("ID_PANEL_TOWER"));
	TextCtrlTower = new wxTextCtrl(PanelTower, ID_TEXTCTRL_TOWER, _("Text"), wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_TOWER"));
	wxFont TextCtrlTowerFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrlTower->SetFont(TextCtrlTowerFont);
	Panel_Hours = new wxPanel(Notebook_Airport, ID_PANEL_HOURS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_HOURS"));
	TextCtrl_Hours = new wxTextCtrl(Panel_Hours, ID_TEXTCTRL_HOURS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_HOURS"));
	wxFont TextCtrl_HoursFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Hours->SetFont(TextCtrl_HoursFont);
	Panel_Frequencies = new wxPanel(Notebook_Airport, ID_PANEL_FREQUENCIES, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_FREQUENCIES"));
	TextCtrl_Frequencies = new wxTextCtrl(Panel_Frequencies, ID_TEXTCTRL_FREQUENCIES, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_FREQUENCIES"));
	wxFont TextCtrl_FrequenciesFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Frequencies->SetFont(TextCtrl_FrequenciesFont);
	Panel_Services = new wxPanel(Notebook_Airport, ID_PANEL_SERVICES, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_SERVICES"));
	TextCtrl_Services = new wxTextCtrl(Panel_Services, ID_TEXTCTRL_SERVICES, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_SERVICES"));
	wxFont TextCtrl_ServicesFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Services->SetFont(TextCtrl_ServicesFont);
	Panel_Radar = new wxPanel(Notebook_Airport, ID_PANEL_RADAR, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_RADAR"));
	TextCtrl_Radar = new wxTextCtrl(Panel_Radar, ID_TEXTCTRL_RADAR, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_RADAR"));
	wxFont TextCtrl_RadarFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Radar->SetFont(TextCtrl_RadarFont);
	Panel_Remarks = new wxPanel(Notebook_Airport, ID_PANEL_REMARKS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_REMARKS"));
	TextCtrl_Remarks = new wxTextCtrl(Panel_Remarks, ID_TEXTCTRL_TWR_REMARKS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxTE_CHARWRAP|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_TWR_REMARKS"));
	wxFont TextCtrl_RemarksFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Remarks->SetFont(TextCtrl_RemarksFont);
	Panel_Satellite = new wxPanel(Notebook_Airport, ID_PANEL_SATELLITE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_SATELLITE"));
	TextCtrlSatellite = new wxTextCtrl(Panel_Satellite, ID_TEXTCTRL_SATELLITE, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_SATELLITE"));
	wxFont TextCtrlSatelliteFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrlSatellite->SetFont(TextCtrlSatelliteFont);
	Panel_Class_BCDE = new wxPanel(Notebook_Airport, ID_PANEL_CLASS_BCDE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_CLASS_BCDE"));
	TextCtrl_Class_BCDE = new wxTextCtrl(Panel_Class_BCDE, ID_TEXTCTRL_CLASS_BCDE, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_CLASS_BCDE"));
	wxFont TextCtrl_Class_BCDEFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Class_BCDE->SetFont(TextCtrl_Class_BCDEFont);
	Panel_ATIS = new wxPanel(Notebook_Airport, ID_PANEL_ATIS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_ATIS"));
	TextCtrl_ATIS = new wxTextCtrl(Panel_ATIS, ID_TEXTCTRL_ATIS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_ATIS"));
	wxFont TextCtrl_ATISFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_ATIS->SetFont(TextCtrl_ATISFont);
	Panel_AWOS = new wxPanel(Notebook_Airport, ID_PANEL_AWOS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_AWOS"));
	TextCtrl_AWOS = new wxTextCtrl(Panel_AWOS, ID_TEXTCTRL_AWOS, _("Text"), wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_AWOS"));
	wxFont TextCtrl_AWOSFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_AWOS->SetFont(TextCtrl_AWOSFont);
	Panel_ILS = new wxPanel(Notebook_Airport, ID_PANEL_ILS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_ILS"));
	TextCtrl_ILS = new wxTextCtrl(Panel_ILS, ID_TEXTCTRL_ILS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_ILS"));
	wxFont TextCtrl_ILSFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_ILS->SetFont(TextCtrl_ILSFont);
	Panel_Localizer = new wxPanel(Notebook_Airport, ID_PANEL_LOCALIZER, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_LOCALIZER"));
	TextCtrl_Localizer = new wxTextCtrl(Panel_Localizer, ID_TEXTCTRL_LOCALIZER, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_LOCALIZER"));
	wxFont TextCtrl_LocalizerFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_Localizer->SetFont(TextCtrl_LocalizerFont);
	Panel_GlideSlope = new wxPanel(Notebook_Airport, ID_PANEL_GLIDE_SLOPE, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_GLIDE_SLOPE"));
	TextCtrl_GlideSlope = new wxTextCtrl(Panel_GlideSlope, ID_TEXTCTRL_GLIDE_SLOPE, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_GLIDE_SLOPE"));
	wxFont TextCtrl_GlideSlopeFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_GlideSlope->SetFont(TextCtrl_GlideSlopeFont);
	Panel_DME = new wxPanel(Notebook_Airport, ID_PANEL_DMD, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_DMD"));
	TextCtrl_DME = new wxTextCtrl(Panel_DME, ID_TEXTCTRL_DME, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_DME"));
	wxFont TextCtrl_DMEFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_DME->SetFont(TextCtrl_DMEFont);
	PanelMarkerBeacon = new wxPanel(Notebook_Airport, ID_PANEL_MARKER_BEACON, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_MARKER_BEACON"));
	TextCtrl_MarkerBeacon = new wxTextCtrl(PanelMarkerBeacon, ID_TEXTCTRL_MARKER_BEACON, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_MARKER_BEACON"));
	wxFont TextCtrl_MarkerBeaconFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_MarkerBeacon->SetFont(TextCtrl_MarkerBeaconFont);
	Panel_ILS_Remarks = new wxPanel(Notebook_Airport, ID_PANEL_ILS_REMARKS, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_ILS_REMARKS"));
	TextCtrl_ILS_Remarks = new wxTextCtrl(Panel_ILS_Remarks, ID_TEXTCTRL_ILS_REMARKS, wxEmptyString, wxPoint(5,5), wxSize(555,570), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL|wxHSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_ILS_REMARKS"));
	wxFont TextCtrl_ILS_RemarksFont(10,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrl_ILS_Remarks->SetFont(TextCtrl_ILS_RemarksFont);
	Notebook_Airport->AddPage(Panel_Airport, _("Airport"), false);
	Notebook_Airport->AddPage(Panel_Att, _("Attendance"), false);
	Notebook_Airport->AddPage(Panel_Rwy, _("Runway"), false);
	Notebook_Airport->AddPage(PanelArrSys, _("Arresting System(s)"), false);
	Notebook_Airport->AddPage(PanelRemarks, _("Remarks"), false);
	Notebook_Airport->AddPage(PanelTower, _("Tower"), false);
	Notebook_Airport->AddPage(Panel_Hours, _("Hours"), false);
	Notebook_Airport->AddPage(Panel_Frequencies, _("Frequencies"), false);
	Notebook_Airport->AddPage(Panel_Services, _("Services"), false);
	Notebook_Airport->AddPage(Panel_Radar, _("Radar"), false);
	Notebook_Airport->AddPage(Panel_Remarks, _("Remarks"), false);
	Notebook_Airport->AddPage(Panel_Satellite, _("Satellite"), false);
	Notebook_Airport->AddPage(Panel_Class_BCDE, _("Class BCDE"), false);
	Notebook_Airport->AddPage(Panel_ATIS, _("ATIS"), false);
	Notebook_Airport->AddPage(Panel_AWOS, _("AWOS"), false);
	Notebook_Airport->AddPage(Panel_ILS, _("ILS"), false);
	Notebook_Airport->AddPage(Panel_Localizer, _("Localizer"), false);
	Notebook_Airport->AddPage(Panel_GlideSlope, _("Glide Slope"), false);
	Notebook_Airport->AddPage(Panel_DME, _("DME"), false);
	Notebook_Airport->AddPage(PanelMarkerBeacon, _("Marker Beacon"), false);
	Notebook_Airport->AddPage(Panel_ILS_Remarks, _("ILS Remarks"), false);
	Center();

	Connect(ID_NOTEBOOK_AIRPORT,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&AirportFrame::OnNotebook_AirportPageChanged);
	//*)
}

AirportFrame::~AirportFrame()
{
	//(*Destroy(AirportFrame)
	//*)
}


void AirportFrame::OnNotebook_AirportPageChanged(wxNotebookEvent& event)
{
}
