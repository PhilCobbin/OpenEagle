/***************************************************************
 * Name:      OpenEagleLauncherMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2018-06-09
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

#include "OpenEagleLauncherMain.h"
#include <wx/msgdlg.h>
#include "InformationFrame.h"
#include "../system_io/system_io.hxx"

//(*InternalHeaders(OpenEagleLauncherFrame)
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

//(*IdInit(OpenEagleLauncherFrame)
const long OpenEagleLauncherFrame::ID_TEXTCTRL1 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL2 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL4 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_OPEN_EAGLE_G5 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_OPENEAGLE_G5 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL8 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_FLIGHT_PLAN = wxNewId();
const long OpenEagleLauncherFrame::ID_STATICTEXT_FLIGHT_PLAN = wxNewId();
const long OpenEagleLauncherFrame::ID_BUTTON_START_AIRPORT = wxNewId();
const long OpenEagleLauncherFrame::ID_BUTTON2 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_METAR = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL12 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX3 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL13 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL16 = wxNewId();
const long OpenEagleLauncherFrame::ID_BUTTON_START_COORDINATES_ELEVATION = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL17 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX6 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX10 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX16 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX17 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX18 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX19 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX20 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL5 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX23 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX24 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX27 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL10 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHOICE1 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHOICE2 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX31 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX12 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRLCeiling = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL3 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_FDM_NULL = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX2 = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL7 = wxNewId();
const long OpenEagleLauncherFrame::ID_BUTTON_LOOKUP_FLIGHT = wxNewId();
const long OpenEagleLauncherFrame::ID_BUTTON_SELECT_FLIGHT_PLAN = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_DISABLE_AI_TRAFFIC = wxNewId();
const long OpenEagleLauncherFrame::ID_STATICTEXT_AIRPORT = wxNewId();
const long OpenEagleLauncherFrame::ID_STATICTEXT_AIRCRAFT = wxNewId();
const long OpenEagleLauncherFrame::ID_STATICTEXT_LON = wxNewId();
const long OpenEagleLauncherFrame::ID_STATICTEXT_ALT = wxNewId();
const long OpenEagleLauncherFrame::ID_STATICTEXT_LAT = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_WRITE_OPEN_EAGLE_EXT = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOXWRITE_FGFS_FILE = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_DATA_OPEN_EAGLE_GPS_W_ALT = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX5 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX7 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX8 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX9 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX11 = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_DATA_OPEN_EAGLE_GPS = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_DATA_OPEN_EAGLE_MANUAL = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_OpenEagleGPS_W_ALT = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_DATA_OPEN_EAGLE_EM = wxNewId();
const long OpenEagleLauncherFrame::ID_CHECKBOX_DATA_OPEN_EAGLE_FC = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_DATA_OPEN_EAGLE_GPS = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTROpenEagleManual = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_OPEN_EAGLE_EM = wxNewId();
const long OpenEagleLauncherFrame::ID_TEXTCTRL_OPEN_EAGLE_FC = wxNewId();
const long OpenEagleLauncherFrame::ID_PANEL_LAUNCH_PANEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagleLauncherFrame,wxFrame)
    //(*EventTable(OpenEagleLauncherFrame)
    //*)
END_EVENT_TABLE()

OpenEagleLauncherFrame::OpenEagleLauncherFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagleLauncherFrame)
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1200,900));
    SetBackgroundColour(wxColour(169,169,169));
    PanelLaunchPanel = new wxPanel(this, ID_PANEL_LAUNCH_PANEL, wxPoint(191,222), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL_LAUNCH_PANEL"));
    TextCtrlAirport = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL1, _("KFLG"), wxPoint(100,60), wxSize(80,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    wxFont TextCtrlAirportFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlAirport->SetFont(TextCtrlAirportFont);
    TextCtrlDisable = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL2, _("--enable-fullscreen --disable-random-vegetation"), wxPoint(20,780), wxSize(800,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    wxFont TextCtrlDisableFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDisable->SetFont(TextCtrlDisableFont);
    TextCtrlHttpd = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL4, _("8080"), wxPoint(140,430), wxSize(100,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    wxFont TextCtrlHttpdFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlHttpd->SetFont(TextCtrlHttpdFont);
    TextCtrlDataOpenEagleG5 = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_OPEN_EAGLE_G5, _("--generic=socket,in,10,127.0.0.1,5556,tcp,OpenEagleG5"), wxPoint(300,215), wxSize(800,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPEN_EAGLE_G5"));
    wxFont TextCtrlDataOpenEagleG5Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDataOpenEagleG5->SetFont(TextCtrlDataOpenEagleG5Font);
    CheckBoxDataOpenEagleG5 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_OPENEAGLE_G5, _("DATA OpenEagleG5"), wxPoint(20,220), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_OPENEAGLE_G5"));
    CheckBoxDataOpenEagleG5->SetValue(false);
    wxFont CheckBoxDataOpenEagleG5Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDataOpenEagleG5->SetFont(CheckBoxDataOpenEagleG5Font);
    TextCtrlAircraft = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL8, _("OpenEagle"), wxPoint(280,60), wxSize(140,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    wxFont TextCtrlAircraftFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlAircraft->SetFont(TextCtrlAircraftFont);
    TextCtrlFlightPlan = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_FLIGHT_PLAN, _("--flight-plan=/home/phil/.fgfs/Export/testing-area"), wxPoint(140,15), wxSize(700,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FLIGHT_PLAN"));
    wxFont TextCtrlFlightPlanFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFlightPlan->SetFont(TextCtrlFlightPlanFont);
    StaticTextFlightPlan = new wxStaticText(PanelLaunchPanel, ID_STATICTEXT_FLIGHT_PLAN, _("Flight Plan"), wxPoint(20,20), wxSize(120,24), 0, _T("ID_STATICTEXT_FLIGHT_PLAN"));
    wxFont StaticTextFlightPlanFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextFlightPlan->SetFont(StaticTextFlightPlanFont);
    ButtonStartAirport = new wxButton(PanelLaunchPanel, ID_BUTTON_START_AIRPORT, _("Start Airport"), wxDLG_UNIT(PanelLaunchPanel,wxPoint(10,43)), wxSize(160,35), wxBORDER_DOUBLE, wxDefaultValidator, _T("ID_BUTTON_START_AIRPORT"));
    wxFont ButtonStartAirportFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonStartAirport->SetFont(ButtonStartAirportFont);
    ButtonQuit = new wxButton(PanelLaunchPanel, ID_BUTTON2, _("Quit"), wxPoint(1050,800), wxSize(120,60), wxBORDER_DOUBLE, wxDefaultValidator, _T("ID_BUTTON2"));
    wxFont ButtonQuitFont(36,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonQuit->SetFont(ButtonQuitFont);
    TextCtrlMetar = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_METAR, _("\'XXXX 012345Z 00000KT 99SM NOSIG\' "), wxPoint(160,520), wxSize(420,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_METAR"));
    wxFont TextCtrlMetarFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlMetar->SetFont(TextCtrlMetarFont);
    TextCtrlDisable2 = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL12, _("--disable-random-buildings --disable-ai-models --disable-ai-traffic --disable-terrasync"), wxPoint(24,840), wxSize(1000,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL12"));
    wxFont TextCtrlDisable2Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDisable2->SetFont(TextCtrlDisable2Font);
    CheckBoxFgroot = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX3, _("--fg-root=path"), wxPoint(20,475), wxSize(190,30), 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    CheckBoxFgroot->SetValue(true);
    wxFont CheckBoxFgrootFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxFgroot->SetFont(CheckBoxFgrootFont);
    TextCtrlFgroot = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL13, _("/home/phil/Desktop/FlightGearOpenEagle"), wxPoint(208,470), wxSize(950,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL13"));
    wxFont TextCtrlFgrootFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFgroot->SetFont(TextCtrlFgrootFont);
    TextCtrlLon = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL16, _("-110.384749"), wxPoint(700,60), wxSize(200,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL16"));
    wxFont TextCtrlLonFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlLon->SetFont(TextCtrlLonFont);
    ButtonStartCoordinatesElevation = new wxButton(PanelLaunchPanel, ID_BUTTON_START_COORDINATES_ELEVATION, _("Start  Lat/Lon/Altitude"), wxPoint(430,103), wxSize(650,35), 0, wxDefaultValidator, _T("ID_BUTTON_START_COORDINATES_ELEVATION"));
    wxFont ButtonStartCoordinatesElevationFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonStartCoordinatesElevation->SetFont(ButtonStartCoordinatesElevationFont);
    TextCtrlLat = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL17, _("36.58686"), wxPoint(480,64), wxSize(160,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL17"));
    wxFont TextCtrlLatFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlLat->SetFont(TextCtrlLatFont);
    CheckBoxDisableHud3D = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX6, _("--disable-hud-3d"), wxPoint(32,632), wxSize(220,30), 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBoxDisableHud3D->SetValue(true);
    wxFont CheckBoxDisableHud3DFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDisableHud3D->SetFont(CheckBoxDisableHud3DFont);
    CheckBoxDisableSound = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX10, _("--disable-sound"), wxPoint(32,560), wxSize(200,20), 0, wxDefaultValidator, _T("ID_CHECKBOX10"));
    CheckBoxDisableSound->SetValue(true);
    wxFont CheckBoxDisableSoundFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDisableSound->SetFont(CheckBoxDisableSoundFont);
    CheckBoxDisableFullscreen = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX16, _("--disable-fullscreen"), wxPoint(32,592), wxSize(250,20), 0, wxDefaultValidator, _T("ID_CHECKBOX16"));
    CheckBoxDisableFullscreen->SetValue(true);
    wxFont CheckBoxDisableFullscreenFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDisableFullscreen->SetFont(CheckBoxDisableFullscreenFont);
    CheckBoxEnableFullscreen = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX17, _("--enable-fullscreen"), wxPoint(32,616), wxSize(250,20), 0, wxDefaultValidator, _T("ID_CHECKBOX17"));
    CheckBoxEnableFullscreen->SetValue(false);
    wxFont CheckBoxEnableFullscreenFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxEnableFullscreen->SetFont(CheckBoxEnableFullscreenFont);
    CheckBoxGeometry = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX18, _("--geometry=WxH"), wxPoint(608,696), wxSize(220,-1), 0, wxDefaultValidator, _T("ID_CHECKBOX18"));
    CheckBoxGeometry->SetValue(false);
    wxFont CheckBoxGeometryFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxGeometry->SetFont(CheckBoxGeometryFont);
    CheckBoxTimeOfDay = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX19, _("--timeofday="), wxPoint(20,740), wxSize(170,30), 0, wxDefaultValidator, _T("ID_CHECKBOX19"));
    CheckBoxTimeOfDay->SetValue(true);
    wxFont CheckBoxTimeOfDayFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxTimeOfDay->SetFont(CheckBoxTimeOfDayFont);
    CheckBoxSeason = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX20, _("--season="), wxPoint(370,745), wxSize(140,20), 0, wxDefaultValidator, _T("ID_CHECKBOX20"));
    CheckBoxSeason->SetValue(true);
    wxFont CheckBoxSeasonFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxSeason->SetFont(CheckBoxSeasonFont);
    TextCtrlGeometry = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL5, _("640x480"), wxPoint(808,696), wxSize(200,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    wxFont TextCtrlGeometryFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlGeometry->SetFont(TextCtrlGeometryFont);
    CheckBoxMetar = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX23, _("--metar="), wxPoint(20,525), wxSize(130,20), 0, wxDefaultValidator, _T("ID_CHECKBOX23"));
    CheckBoxMetar->SetValue(true);
    wxFont CheckBoxMetarFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxMetar->SetFont(CheckBoxMetarFont);
    CheckBoxDisableRealWeatherFetch = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX24, _("--disable-real-weather-fetch"), wxPoint(24,672), wxSize(350,20), 0, wxDefaultValidator, _T("ID_CHECKBOX24"));
    CheckBoxDisableRealWeatherFetch->SetValue(false);
    wxFont CheckBoxDisableRealWeatherFetchFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDisableRealWeatherFetch->SetFont(CheckBoxDisableRealWeatherFetchFont);
    CheckBoxVisibilityMiles = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX27, _("--visibility-miles="), wxPoint(336,704), wxSize(220,20), 0, wxDefaultValidator, _T("ID_CHECKBOX27"));
    CheckBoxVisibilityMiles->SetValue(true);
    wxFont CheckBoxVisibilityMilesFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxVisibilityMiles->SetFont(CheckBoxVisibilityMilesFont);
    TextCtrlVisibilityMiles = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL10, _("75"), wxPoint(536,696), wxSize(50,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL10"));
    wxFont TextCtrlVisibilityMilesFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlVisibilityMiles->SetFont(TextCtrlVisibilityMilesFont);
    ChoiceSeason = new wxChoice(PanelLaunchPanel, ID_CHOICE1, wxPoint(510,735), wxSize(150,40), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    ChoiceSeason->SetSelection( ChoiceSeason->Append(_("summer")) );
    ChoiceSeason->Append(_("winter"));
    wxFont ChoiceSeasonFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ChoiceSeason->SetFont(ChoiceSeasonFont);
    ChoiceTimeOfDay = new wxChoice(PanelLaunchPanel, ID_CHOICE2, wxPoint(200,735), wxSize(150,40), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    ChoiceTimeOfDay->Append(_("real"));
    ChoiceTimeOfDay->Append(_("dawn"));
    ChoiceTimeOfDay->SetSelection( ChoiceTimeOfDay->Append(_("morning")) );
    ChoiceTimeOfDay->Append(_("noon"));
    ChoiceTimeOfDay->Append(_("afternoon"));
    ChoiceTimeOfDay->Append(_("dusk"));
    ChoiceTimeOfDay->Append(_("evening"));
    ChoiceTimeOfDay->Append(_("midnight"));
    wxFont ChoiceTimeOfDayFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ChoiceTimeOfDay->SetFont(ChoiceTimeOfDayFont);
    CheckBoxHttp = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX31, _("--httpd="), wxPoint(20,430), wxSize(120,30), 0, wxDefaultValidator, _T("ID_CHECKBOX31"));
    CheckBoxHttp->SetValue(true);
    wxFont CheckBoxHttpFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxHttp->SetFont(CheckBoxHttpFont);
    CheckBoxCeiling = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX12, _("--ceiling="), wxPoint(20,700), wxSize(130,20), 0, wxDefaultValidator, _T("ID_CHECKBOX12"));
    CheckBoxCeiling->SetValue(true);
    wxFont CheckBoxCeilingFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxCeiling->SetFont(CheckBoxCeilingFont);
    TextCtrlCeiling = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRLCeiling, _("100000:0"), wxPoint(160,695), wxSize(150,30), 0, wxDefaultValidator, _T("ID_TEXTCTRLCeiling"));
    wxFont TextCtrlCeilingFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCeiling->SetFont(TextCtrlCeilingFont);
    TextCtrlAltitude = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL3, _("8000"), wxPoint(960,60), wxSize(120,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    wxFont TextCtrlAltitudeFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlAltitude->SetFont(TextCtrlAltitudeFont);
    CheckBoxFdmNull = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_FDM_NULL, _("--fdm=null"), wxPoint(270,430), wxSize(160,20), 0, wxDefaultValidator, _T("ID_CHECKBOX_FDM_NULL"));
    CheckBoxFdmNull->SetValue(true);
    wxFont CheckBoxFdmNullFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxFdmNull->SetFont(CheckBoxFdmNullFont);
    CheckBoxData2 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX2, _("DATA2"), wxPoint(20,360), wxSize(100,30), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    CheckBoxData2->SetValue(false);
    wxFont CheckBoxData2Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxData2->SetFont(CheckBoxData2Font);
    TextCtrlData2 = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL7, _("--native=file,in,10,flight1.fgfs"), wxPoint(120,360), wxSize(860,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    wxFont TextCtrlData2Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlData2->SetFont(TextCtrlData2Font);
    Button_Lookup_Flight = new wxButton(PanelLaunchPanel, ID_BUTTON_LOOKUP_FLIGHT, _("Lookup Flight"), wxPoint(1000,360), wxSize(180,30), 0, wxDefaultValidator, _T("ID_BUTTON_LOOKUP_FLIGHT"));
    wxFont Button_Lookup_FlightFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Button_Lookup_Flight->SetFont(Button_Lookup_FlightFont);
    ButtonSelectFlightPlan = new wxButton(PanelLaunchPanel, ID_BUTTON_SELECT_FLIGHT_PLAN, _("Select Flight Plan"), wxPoint(850,15), wxSize(230,35), 0, wxDefaultValidator, _T("ID_BUTTON_SELECT_FLIGHT_PLAN"));
    wxFont ButtonSelectFlightPlanFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSelectFlightPlan->SetFont(ButtonSelectFlightPlanFont);
    CheckBoxDisableAITraffic = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_DISABLE_AI_TRAFFIC, _("--disable-ai-traffic"), wxPoint(460,430), wxSize(220,20), 0, wxDefaultValidator, _T("ID_CHECKBOX_DISABLE_AI_TRAFFIC"));
    CheckBoxDisableAITraffic->SetValue(true);
    wxFont CheckBoxDisableAITrafficFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDisableAITraffic->SetFont(CheckBoxDisableAITrafficFont);
    StaticTextAirport = new wxStaticText(PanelLaunchPanel, ID_STATICTEXT_AIRPORT, _("Airport"), wxPoint(20,60), wxSize(80,30), 0, _T("ID_STATICTEXT_AIRPORT"));
    wxFont StaticTextAirportFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextAirport->SetFont(StaticTextAirportFont);
    StaticTextAircraft = new wxStaticText(PanelLaunchPanel, ID_STATICTEXT_AIRCRAFT, _("Aircraft"), wxPoint(190,60), wxSize(80,30), 0, _T("ID_STATICTEXT_AIRCRAFT"));
    wxFont StaticTextAircraftFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextAircraft->SetFont(StaticTextAircraftFont);
    Lon = new wxStaticText(PanelLaunchPanel, ID_STATICTEXT_LON, _("Lon"), wxPoint(650,60), wxSize(60,30), 0, _T("ID_STATICTEXT_LON"));
    wxFont LonFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    Lon->SetFont(LonFont);
    StaticTextAlt = new wxStaticText(PanelLaunchPanel, ID_STATICTEXT_ALT, _("Alt"), wxPoint(920,60), wxSize(30,30), 0, _T("ID_STATICTEXT_ALT"));
    wxFont StaticTextAltFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextAlt->SetFont(StaticTextAltFont);
    StaticTextLat = new wxStaticText(PanelLaunchPanel, ID_STATICTEXT_LAT, _("Lat"), wxPoint(430,60), wxSize(40,30), 0, _T("ID_STATICTEXT_LAT"));
    wxFont StaticTextLatFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextLat->SetFont(StaticTextLatFont);
    CheckBoxWriteOpenEagleExt = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_WRITE_OPEN_EAGLE_EXT, _("Write OpenEagleExt File"), wxPoint(20,390), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_WRITE_OPEN_EAGLE_EXT"));
    CheckBoxWriteOpenEagleExt->SetValue(true);
    wxFont CheckBoxWriteOpenEagleExtFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxWriteOpenEagleExt->SetFont(CheckBoxWriteOpenEagleExtFont);
    CheckBoxWriteFGFSfile = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOXWRITE_FGFS_FILE, _("Write fgfs file"), wxPoint(300,390), wxSize(180,30), 0, wxDefaultValidator, _T("ID_CHECKBOXWRITE_FGFS_FILE"));
    CheckBoxWriteFGFSfile->SetValue(false);
    wxFont CheckBoxWriteFGFSfileFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxWriteFGFSfile->SetFont(CheckBoxWriteFGFSfileFont);
    CheckBoxDataOpenEagleGPSwAlt = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_DATA_OPEN_EAGLE_GPS_W_ALT, _("DATA OpenEagleGPSwAlt"), wxPoint(20,185), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_DATA_OPEN_EAGLE_GPS_W_ALT"));
    CheckBoxDataOpenEagleGPSwAlt->SetValue(false);
    wxFont CheckBoxDataOpenEagleGPSwAltFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDataOpenEagleGPSwAlt->SetFont(CheckBoxDataOpenEagleGPSwAltFont);
    CheckBox2 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX5, _("Write GPSwAlt"), wxPoint(480,390), wxSize(180,30), 0, wxDefaultValidator, _T("ID_CHECKBOX5"));
    CheckBox2->SetValue(false);
    wxFont CheckBox2Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBox2->SetFont(CheckBox2Font);
    CheckBox3 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX7, _("Write GPS"), wxPoint(660,390), wxSize(140,30), 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    CheckBox3->SetValue(false);
    wxFont CheckBox3Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBox3->SetFont(CheckBox3Font);
    CheckBox4 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX8, _("Write G5"), wxPoint(800,390), wxSize(120,30), 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox4->SetValue(false);
    wxFont CheckBox4Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBox4->SetFont(CheckBox4Font);
    CheckBox5 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX9, _("Write EM"), wxPoint(920,390), wxSize(120,30), 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    CheckBox5->SetValue(false);
    wxFont CheckBox5Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBox5->SetFont(CheckBox5Font);
    CheckBox6 = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX11, _("Write FC"), wxPoint(1050,390), wxSize(120,30), 0, wxDefaultValidator, _T("ID_CHECKBOX11"));
    CheckBox6->SetValue(false);
    wxFont CheckBox6Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBox6->SetFont(CheckBox6Font);
    CheckBoxDataOpenEagleGPS = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_DATA_OPEN_EAGLE_GPS, _("DATA OpenEagleGPS"), wxPoint(20,150), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_DATA_OPEN_EAGLE_GPS"));
    CheckBoxDataOpenEagleGPS->SetValue(false);
    wxFont CheckBoxDataOpenEagleGPSFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDataOpenEagleGPS->SetFont(CheckBoxDataOpenEagleGPSFont);
    CheckBoxDataOpenEagleManual = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_DATA_OPEN_EAGLE_MANUAL, _("DATA OpenEagleManual"), wxPoint(20,255), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_DATA_OPEN_EAGLE_MANUAL"));
    CheckBoxDataOpenEagleManual->SetValue(false);
    wxFont CheckBoxDataOpenEagleManualFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDataOpenEagleManual->SetFont(CheckBoxDataOpenEagleManualFont);
    TextCtrlDataOpenEagleGPSwAlt = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_OpenEagleGPS_W_ALT, _("--generic=socket,in,10,127.0.0.1,5555,tcp,OpenEagleGPSwALT"), wxPoint(300,180), wxSize(800,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OpenEagleGPS_W_ALT"));
    wxFont TextCtrlDataOpenEagleGPSwAltFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDataOpenEagleGPSwAlt->SetFont(TextCtrlDataOpenEagleGPSwAltFont);
    CheckBoxDataOpenEagleEM = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_DATA_OPEN_EAGLE_EM, _("DATA OpenEagleEM"), wxPoint(20,290), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_DATA_OPEN_EAGLE_EM"));
    CheckBoxDataOpenEagleEM->SetValue(false);
    wxFont CheckBoxDataOpenEagleEMFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDataOpenEagleEM->SetFont(CheckBoxDataOpenEagleEMFont);
    CheckBoxDataOpenEagleFC = new wxCheckBox(PanelLaunchPanel, ID_CHECKBOX_DATA_OPEN_EAGLE_FC, _("DATA OpenEagleFC"), wxPoint(20,325), wxSize(280,30), 0, wxDefaultValidator, _T("ID_CHECKBOX_DATA_OPEN_EAGLE_FC"));
    CheckBoxDataOpenEagleFC->SetValue(false);
    wxFont CheckBoxDataOpenEagleFCFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    CheckBoxDataOpenEagleFC->SetFont(CheckBoxDataOpenEagleFCFont);
    TextCtrlDataOpenEagleGPS = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_DATA_OPEN_EAGLE_GPS, _("--generic=socket,in,10,127.0.0.1,5555,tcp,OpenEagleGPS"), wxPoint(300,145), wxSize(800,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_DATA_OPEN_EAGLE_GPS"));
    wxFont TextCtrlDataOpenEagleGPSFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDataOpenEagleGPS->SetFont(TextCtrlDataOpenEagleGPSFont);
    TextCtrlDataOpenEagleManual = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTROpenEagleManual, _("--generic=socket,in,10,127.0.0.1,5559,tcp,OpenEagleManual"), wxPoint(300,250), wxSize(800,30), 0, wxDefaultValidator, _T("ID_TEXTCTROpenEagleManual"));
    wxFont TextCtrlDataOpenEagleManualFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDataOpenEagleManual->SetFont(TextCtrlDataOpenEagleManualFont);
    TextCtrlDataOpenEagleEM = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_OPEN_EAGLE_EM, _("--generic=socket,in,10,127.0.0.1,5557,tcp,OpenEagleEM"), wxPoint(300,285), wxSize(800,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPEN_EAGLE_EM"));
    wxFont TextCtrlDataOpenEagleEMFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDataOpenEagleEM->SetFont(TextCtrlDataOpenEagleEMFont);
    TextCtrlDataOpenEagleFC = new wxTextCtrl(PanelLaunchPanel, ID_TEXTCTRL_OPEN_EAGLE_FC, _("--generic=socket,in,10,127.0.0.1,5558,tcp,OpenEagleFC"), wxPoint(300,320), wxSize(800,30), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OPEN_EAGLE_FC"));
    wxFont TextCtrlDataOpenEagleFCFont(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlDataOpenEagleFC->SetFont(TextCtrlDataOpenEagleFCFont);
    FileDialogSelectFlightHistory = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, wxFD_DEFAULT_STYLE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FileDialogSelectFlightPlan = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, wxFileSelectorDefaultWildcardStr, 0, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_TEXTCTRL_OPEN_EAGLE_G5,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnTextCtrlData1Text1);
    Connect(ID_CHECKBOX_OPENEAGLE_G5,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnCheckBoxData1Click);
    Connect(ID_BUTTON_START_AIRPORT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnButtonStartAirportClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnQuit);
    Connect(ID_BUTTON_START_COORDINATES_ELEVATION,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnButtonStartCoordinatesElevationClick);
    Connect(ID_CHECKBOX_FDM_NULL,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnCheckBoxFdmNullClick);
    Connect(ID_CHECKBOX2,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnCheckBoxData2Click);
    Connect(ID_BUTTON_LOOKUP_FLIGHT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnButton_Lookup_FlightClick);
    Connect(ID_BUTTON_SELECT_FLIGHT_PLAN,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnButtonSelectFlightPlanClick);
    Connect(ID_CHECKBOX_WRITE_OPEN_EAGLE_EXT,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnCheckBoxWriteOpenEagleExtClick1);
    Connect(ID_CHECKBOXWRITE_FGFS_FILE,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnCheckBoxWriteFGFSfileClick3);
    Connect(ID_CHECKBOX_DATA_OPEN_EAGLE_FC,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnCheckBox10Click);
    Connect(ID_TEXTCTRL_DATA_OPEN_EAGLE_GPS,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&OpenEagleLauncherFrame::OnTextCtrlOpenEagleGPSText);
    //*)

    bool paths_ok = paths.setupOpenEaglePaths((char *)"OpenEagleLauncher",(char *)"duh");
    if (!paths_ok) {
      printf("Warning: could not locate a valid set of paths in home/.OpenEagle directory\n");
    }
    std::string OpenEagleFlightGearPath = paths.OpenEagle_FlightGear_Path.c_str();
    TextCtrlFgroot->SetValue(OpenEagleFlightGearPath.c_str());

    FILE * fp;
    char buffer[500];
    int n=20;
    fp = fopen("elevation.txt","r");
    if (fp != NULL) {
      fgets((char *)&buffer,n,fp);
      elevation = strtod((char *)&buffer,NULL);
      TextCtrlAltitude->SetValue(std::to_string(elevation));
      fclose(fp);
      fp = fopen("latitude.txt","r");
      if (fp != NULL) {
        fgets((char *)&buffer,n,fp);
        latitude = strtod((char *)&buffer,NULL);
        TextCtrlLat->SetValue(std::to_string(latitude));
        fclose(fp);
        fp = fopen("longitude.txt","r");
        if (fp != NULL) {
          fgets((char *)&buffer,n,fp);
          longitude = strtod((char *)&buffer,NULL);
          TextCtrlLon->SetValue(std::to_string(longitude));
          fclose(fp);

        }
      }
    }

}

OpenEagleLauncherFrame::~OpenEagleLauncherFrame()
{
    //(*Destroy(OpenEagleLauncherFrame)
    //*)
}

void OpenEagleLauncherFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagleLauncherFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void OpenEagleLauncherFrame::OnTextCtrlFgsceneryText(wxCommandEvent& event)
{
}

void OpenEagleLauncherFrame::OnButtonStartCoordinatesElevationClick(wxCommandEvent& event)
{
  initialize_commandline();

  commandline += "--aircraft=";
  commandline += TextCtrlAircraft->GetValue();
  commandline += " \\\n";

  commandline += "--altitude=";
  commandline += TextCtrlAltitude->GetValue();
  commandline += " \\\n";

  commandline += "--lat=";
  commandline += TextCtrlLat->GetValue();
  commandline += " \\\n";

  commandline += "--lon=";
  commandline += TextCtrlLon->GetValue();
  commandline += " \\\n";

  switches_to_commandline();

  commandline += TextCtrlFlightPlan->GetValue();
  commandline += " \\\n";

  commandline +='\n';

  printf("CommandLine[%s]",commandline.c_str());
  FILE * fp_latlon = fopen("latlon_commandline.txt","w++");
  fprintf(fp_latlon,"%s\n",commandline.c_str());
  fclose(fp_latlon);
  system(commandline.c_str());

  exit(1);
}

void OpenEagleLauncherFrame::initialize_commandline()
{
  commandline="fgfs \\\n";
  time_strings.set_time_strings();
  std::string command;
  std::string flight_history;

  if (CheckBoxData2->IsChecked()==false) {
    if (CheckBoxWriteFGFSfile->IsChecked() == true) {
      /// setup fgfs flight history file also...
      std::string fgfs_path = "flights_fgfs/";
      command = "mkdir -p ";
      command += fgfs_path.c_str();
      command += "/";
      command += time_strings.time_full_dashed_str.c_str();
      command += "\n";
      bool command_ok = system_io(&command);
      printf("make fgfs flight history directory....[%s]\n",command.c_str());
      if (!command_ok) {
        printf("failed to fgfs_path directory [%s]\n",command.c_str());
        exit(1);
      }

      flight_history = "--native=file,out,10,";
      flight_history += fgfs_path.c_str();
      flight_history += "/";
      flight_history += time_strings.time_full_dashed_str.c_str();
      flight_history += "/";
      flight_history += "flight";
      flight_history += ".fgfs";

      commandline += flight_history;
      commandline += " \\\n";
    }
    if (CheckBoxWriteOpenEagleExt->IsChecked() == true) {
      /// setup OpenEagleExt flight history file also...
      std::string OpenEagleExt_path = "flights_OpenEagleExt/";
      OpenEagleExt_path += "/";
      OpenEagleExt_path += time_strings.time_full_dashed_str.c_str();
      command = "mkdir -p ";
      command += OpenEagleExt_path.c_str();
      command += "\n";
      bool command_ok = system_io(&command);
      if (!command_ok) {
        printf("failed to OpenEagleExt_path directory [%s]\n",command.c_str());
        exit(1);
      }

      /// flight testing subpath
      std::string flight_test_analysis = OpenEagleExt_path;
      flight_test_analysis += "/flight_test_analysis";
      command = "mkdir -p ";
      command += flight_test_analysis.c_str();
//      command += "/";
//      command += time_strings.time_full_dashed_str.c_str();
      command += "\n";
      command_ok = system_io(&command);
      if (!command_ok) {
        printf("failed to OpenEagleExt_path flight test analysis subpath directory [%s]\n",command.c_str());
        exit(1);
      }
      /// flight data subpath
      std::string flight_test_data = OpenEagleExt_path;
      flight_test_data += "/flight_test_data";
      command = "mkdir -p ";
      command += flight_test_data.c_str();
 //     command += "/";
 //     command += time_strings.time_full_dashed_str.c_str();
      command += "\n";
      command_ok = system_io(&command);
      if (!command_ok) {
        printf("failed to OpenEagleExt_path flight test data subpath directory [%s]\n",command.c_str());
        exit(1);
      }

      flight_history = "--generic=file,out,10,";
      flight_history += OpenEagleExt_path.c_str();
      flight_history += "/";
 //     flight_history += time_strings.time_full_dashed_str.c_str();
  //    flight_history += "/";
      flight_history += "flight";
///      flight_history += time_strings.time_full_dashed_str.c_str();
      flight_history += ".OpenEagleExt,OpenEagleExt";

      commandline += flight_history;
      commandline += " \\\n";

    }
  }
  else {
    commandline += TextCtrlData2->GetValue().ToStdString().c_str();
    commandline += " \\\n";
  }
}

void OpenEagleLauncherFrame::fixed_switches_to_commandline()
{
 //  if (CheckBoxDisableRandomObjects->IsChecked() ){
    commandline += "--disable-random-objects";
    commandline += " \\\n";
  //  }

  //  if (CheckBoxDisableRandomVegetation->IsChecked() ){
      commandline += "--disable-random-vegetation";
      commandline += " \\\n";
  //  }

  //  if (CheckBoxDisableRandomBuildings->IsChecked() ){
      commandline += "--disable-random-buildings";
      commandline += " \\\n";
  //  }
  //  if (CheckBoxFogDisable->IsChecked() ){
      commandline += "--fog-disable";
      commandline += " \\\n";
  //  }
 //  if (CheckBoxDisableDistanceAttenuation->IsChecked() ){
      commandline += "--disable-distance-attenuation";
      commandline += " \\\n";
  //  }

 //   if (CheckBoxDisableHorizonEffect->IsChecked() ){
      commandline += "--disable-horizon-effect";
      commandline += " \\\n";
 //   }

 //   if (CheckBoxDisableSpecularHighlight->IsChecked() ){
      commandline += "--disable-specular-highlight";
      commandline += " \\\n";
 //   }

//    if (CheckBoxDisableClouds->IsChecked() ){
      commandline += "--disable-clouds";
      commandline += " \\\n";
 //   }

 //   if (CheckBoxDisableClouds3D->IsChecked() ){
      commandline += "--disable-clouds3d";
      commandline += " \\\n";
 //   }
  //  if (CheckBoxDisableTerrasync->IsChecked() ){
      commandline += "--disable-terrasync";
      commandline += " \\\n";
  //  }
}

void OpenEagleLauncherFrame::switches_to_commandline()
{
  fixed_switches_to_commandline();

  if ( CheckBoxDataOpenEagleG5->IsChecked() ) {
    printf("CheckBoxDataOpenEagleG5 is checked!\n");
    commandline += TextCtrlDataOpenEagleG5->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxDataOpenEagleGPSwAlt->IsChecked() ) {
    printf("CheckBoxDataOpenEagleGPSwAlt is checked!\n");
    commandline += TextCtrlDataOpenEagleGPSwAlt->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxDataOpenEagleGPS->IsChecked() ) {
    printf("CheckBoxDataOpenEagleGPS is checked!\n");
    commandline += TextCtrlDataOpenEagleGPS->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxDataOpenEagleManual->IsChecked() ) {
    printf("CheckBoxDataOpenEagleManual is checked!\n");
    commandline += TextCtrlDataOpenEagleManual->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxDataOpenEagleEM->IsChecked() ) {
    printf("CheckBoxDataOpenEagleEM is checked!\n");
    commandline += TextCtrlDataOpenEagleEM->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxDataOpenEagleFC->IsChecked() ) {
    printf("CheckBoxDataOpenEagleFC is checked!\n");
    commandline += TextCtrlDataOpenEagleFC->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxData2->IsChecked() ) {
    commandline += TextCtrlData2->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxHttp->IsChecked() ){
    commandline += "--httpd=";
    commandline += TextCtrlHttpd->GetValue();
    commandline += " \\\n";
  }

  if ( CheckBoxFdmNull->IsChecked() ) {
    commandline += "--fdm=null";
    commandline += " \\\n";
  }

  if ( CheckBoxFgroot->IsChecked() ){
    commandline += "--fg-root=";
    commandline += TextCtrlFgroot->GetValue();
    commandline += " \\\n";
  }

  if (CheckBoxDisableHud3D->IsChecked() ){
    commandline += "--disable-hud-3d";
    commandline += " \\\n";
  }


  if (CheckBoxDisableAITraffic->IsChecked() ) {
    commandline += "--disable-ai-traffic";
    commandline += " \\\n";
  }

    if (CheckBoxDisableSound->IsChecked() ){
      commandline += "--disable-sound";
      commandline += " \\\n";
    }


    if (CheckBoxCeiling->IsChecked() ){
      commandline += "--ceiling=";
      commandline+= TextCtrlCeiling->GetValue();
      commandline += " \\\n";
    }

    if (CheckBoxDisableFullscreen->IsChecked() ){
      commandline += "--disable-fullscreen";
      commandline += " \\\n";
    }
///// enable full screen flip/flop

    if (CheckBoxGeometry->IsChecked() ){
      commandline+= "--geometry=";
      commandline+= TextCtrlGeometry->GetValue();
      commandline += " \\\n";
    }

    if (CheckBoxTimeOfDay->IsChecked() ) {
      commandline+= "--timeofday=";
      int choice = ChoiceTimeOfDay->GetSelection();
      /// real,dawn,morning,noon,afternoon,dusk,evening,midnight
      switch (choice) {
        case 0: commandline+="real";
        break;
        case 1: commandline+="dawn";
        break;
        case 2: commandline+="morning";
        break;
        case 3: commandline+="noon";
        break;
        case 4: commandline+="afternoon";
        break;
        case 5: commandline+="dusk";
        break;
        case 6: commandline+="evening";
        break;
        case 7: commandline+="midnight";
        break;

      }
      commandline += " \\\n";
    }

    if (CheckBoxSeason->IsChecked() ) {
      commandline+= "--season=";
      int choice = ChoiceSeason->GetSelection();
      /// summer, winter
      switch (choice) {
        case 0: commandline+="summer";
        break;
        case 1: commandline+="winter";
        break;
        default: commandline+="summer";
      }
      commandline += " \\\n";
    }

  if (CheckBoxMetar->IsChecked() ) {
      commandline += "--metar=";
      commandline += TextCtrlMetar->GetValue();
      commandline += " \\\n";
   }

    if (CheckBoxDisableRealWeatherFetch->IsChecked() ){
      commandline += "--disable-real-weather-fetch";
      commandline += " \\\n";
    }


    if (CheckBoxVisibilityMiles->IsChecked() ){
      commandline += "--visibility-miles=";
      commandline += TextCtrlVisibilityMiles->GetValue();
      commandline += " \\\n";
    }

}

void OpenEagleLauncherFrame::OnButtonStartAirportClick(wxCommandEvent& event)
{

  initialize_commandline();

  commandline += "--airport=";
  commandline += TextCtrlAirport->GetValue();
  commandline += " \\\n";

  commandline += "--aircraft=";
  commandline += TextCtrlAircraft->GetValue();
  commandline += " \\\n";

  /// no worky properties_to_commandline();

  switches_to_commandline();

  commandline += TextCtrlFlightPlan->GetValue();
  commandline += " \\\n";

  commandline +='\n';

  printf("CommandLine[%s]",commandline.c_str());
  FILE * fp_airport = fopen("airport_commandline.txt","w++");
  fprintf(fp_airport,"%s\n",commandline.c_str());
  fclose(fp_airport);
  system(commandline.c_str());

  exit(1);
}

void OpenEagleLauncherFrame::OnCheckBoxFdmNullClick(wxCommandEvent& event)
{
}

void OpenEagleLauncherFrame::OnButton_Lookup_FlightClick(wxCommandEvent& event)
{
  int ret = FileDialogSelectFlightHistory->ShowModal();
  if (ret == wxID_OK ) {
    std::string flight_history_file = "";
    std::string file_ext = "";
    flight_history_file = FileDialogSelectFlightHistory->GetPath();  /// need full path
    long unsigned int i = flight_history_file.rfind(".",flight_history_file.length());
    if (i != std::string::npos) {
      file_ext = flight_history_file.substr(i+1,flight_history_file.length()-1);
    }
    else {
      printf("no file extenstion?");
    }

    printf("file_ext [%s]\n",file_ext.c_str());
    std::string fgfs = "fgfs";
    if (strcmp("fgfs",file_ext.c_str()) == 0) {
      std::string data2 = "--native=file,in,10,";
      data2 += flight_history_file.c_str();
      TextCtrlData2->SetValue(data2);
      CheckBoxData2->SetValue(true);
      CheckBoxFdmNull->SetValue(true);
      CheckBoxWriteFGFSfile->SetValue(false);
      CheckBoxWriteOpenEagleExt->SetValue(false);
    }
    else {
      if (strcmp("OpenEagle",file_ext.c_str())== 0) {
        std::string data2 = "--generic=file,in,10,";
        data2 += flight_history_file.c_str();
        data2 += ",OpenEagle";
        TextCtrlData2->SetValue(data2);
        CheckBoxData2->SetValue(true);
        CheckBoxFdmNull->SetValue(true);
        CheckBoxWriteFGFSfile->SetValue(false);
        CheckBoxWriteOpenEagleExt->SetValue(false);
      }
      else {
        if (strcmp("OpenEagleExt",file_ext.c_str())== 0) {
          std::string data2 = "--generic=file,in,10,";
          data2 += flight_history_file.c_str();
          data2 += ",OpenEagleExt";
          TextCtrlData2->SetValue(data2);
          CheckBoxData2->SetValue(true);
          CheckBoxFdmNull->SetValue(true);
          CheckBoxWriteFGFSfile->SetValue(false);
          CheckBoxWriteOpenEagleExt->SetValue(false);
        }
      }
    }
  }
}

void OpenEagleLauncherFrame::OnButtonSelectFlightPlanClick(wxCommandEvent& event)
{
  FileDialogSelectFlightPlan->SetDirectory("/home/phil/.fgfs/Export");
  int ret =FileDialogSelectFlightPlan->ShowModal();
  if (ret == wxID_OK) {
    std::string flightplan = "--flight-plan=";
    flightplan += FileDialogSelectFlightPlan->GetPath();
    TextCtrlFlightPlan->SetValue(flightplan);
  }
}

void OpenEagleLauncherFrame::OnCheckBoxData1Click(wxCommandEvent& event)
{
  if (CheckBoxData2->IsChecked()) CheckBoxData2->SetValue(false);
}


void OpenEagleLauncherFrame::OnCheckBoxData2Click(wxCommandEvent& event)
{
  if (CheckBoxDataOpenEagleG5->IsChecked()) CheckBoxDataOpenEagleG5->SetValue(false);
}

void OpenEagleLauncherFrame::OnCheckBoxWriteOpenEagleExtClick1(wxCommandEvent& event)
{
}

void OpenEagleLauncherFrame::OnCheckBoxWriteFGFSfileClick3(wxCommandEvent& event)
{
}

void OpenEagleLauncherFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}



void OpenEagleLauncherFrame::OnTextCtrlData1Text1(wxCommandEvent& event)
{
}

void OpenEagleLauncherFrame::OnCheckBox10Click(wxCommandEvent& event)
{
}

void OpenEagleLauncherFrame::OnTextCtrlOpenEagleGPSText(wxCommandEvent& event)
{
}
