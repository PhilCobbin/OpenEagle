/***************************************************************
 * Name:      OpenEagleDataMgrMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-05-03
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
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include "../data_mgr/data_mgr.hxx"
#include "../TimeStrings/TimeStrings.hxx"
#include "OpenEagleDataMgrMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEagleDataMgrFrame)
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

//(*IdInit(OpenEagleDataMgrFrame)
const long OpenEagleDataMgrFrame::ID_STATICTEXT_OPEN_EAGLE_CRM114 = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_CREW = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_BAGGAGE = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_RPM = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_MP = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_FLAPS = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_OAT = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_STALL_7 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_TURN_8 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_OPE9 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_DIVE_4 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_LAND_5 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_SPEED_6 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_TAKEOFF_1 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_CLIMB_2 = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_CRUISE_3 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_OAT = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_CURRENT = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_STANDBY_FIRST_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_CURRENT_FIRST_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_STANDBY_SECOND_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_STANDBY_THIRD_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_CURRENT_SECOND_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_CURRENT_THIRD_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_FIRST_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_SECOND_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_THIRD_CODE_PREFIX = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_SET = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_RESET = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_CRM114 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_CREW = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_BAGGAGE = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_RPM = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_MP = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_FLAPS = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_CRM114CodeBook = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT_CURRENT_MANUAL = wxNewId();
const long OpenEagleDataMgrFrame::ID_BUTTON_SET_MANUAL = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_CREW_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_BAGGAGE_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_RPM_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_MP_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_FLAPS_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_OAT_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT1 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT2 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT4 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT5 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT6 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT7 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT8 = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATICTEXT12 = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_COWL_FLAP = wxNewId();
const long OpenEagleDataMgrFrame::ID_TEXTCTRL_COWL_FLAP_STANDBY = wxNewId();
const long OpenEagleDataMgrFrame::ID_PANEL_DATA_MGR = wxNewId();
const long OpenEagleDataMgrFrame::idMenuQuit = wxNewId();
const long OpenEagleDataMgrFrame::idMenuAbout = wxNewId();
const long OpenEagleDataMgrFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagleDataMgrFrame,wxFrame)
    //(*EventTable(OpenEagleDataMgrFrame)
    //*)
END_EVENT_TABLE()

OpenEagleDataMgrFrame::OpenEagleDataMgrFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagleDataMgrFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("Open Eagle CRM114 Data Manager"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1200,600));
    PanelDataMgr = new wxPanel(this, ID_PANEL_DATA_MGR, wxPoint(0,0), wxSize(1200,800), wxTAB_TRAVERSAL, _T("ID_PANEL_DATA_MGR"));
    StaticText_OpenEagleCRM114 = new wxStaticText(PanelDataMgr, ID_STATICTEXT_OPEN_EAGLE_CRM114, _("OpenEagle Data Manager"), wxPoint(20,15), wxSize(500,50), 0, _T("ID_STATICTEXT_OPEN_EAGLE_CRM114"));
    wxFont StaticText_OpenEagleCRM114Font(24,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText_OpenEagleCRM114->SetFont(StaticText_OpenEagleCRM114Font);
    TextCtrlCrew = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_CREW, _("180"), wxPoint(120,130), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CREW"));
    wxFont TextCtrlCrewFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCrew->SetFont(TextCtrlCrewFont);
    TextCtrlBaggage = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_BAGGAGE, _("0"), wxPoint(230,130), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_BAGGAGE"));
    wxFont TextCtrlBaggageFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlBaggage->SetFont(TextCtrlBaggageFont);
    TextCtrlRPM = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_RPM, _("0"), wxPoint(340,130), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_RPM"));
    wxFont TextCtrlRPMFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlRPM->SetFont(TextCtrlRPMFont);
    TextCtrlMP = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_MP, _("0"), wxPoint(450,130), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_MP"));
    wxFont TextCtrlMPFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlMP->SetFont(TextCtrlMPFont);
    TextCtrlFlaps = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_FLAPS, _("0"), wxPoint(670,130), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_FLAPS"));
    wxFont TextCtrlFlapsFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFlaps->SetFont(TextCtrlFlapsFont);
    TextCtrlOAT = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_OAT, _("68"), wxPoint(780,130), wxSize(100,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_OAT"));
    wxFont TextCtrlOATFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlOAT->SetFont(TextCtrlOATFont);
    ButtonStall7 = new wxButton(PanelDataMgr, ID_BUTTON_STALL_7, _("Stall (7)"), wxPoint(810,330), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_STALL_7"));
    wxFont ButtonStall7Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonStall7->SetFont(ButtonStall7Font);
    ButtonTurn8 = new wxButton(PanelDataMgr, ID_BUTTON_TURN_8, _("Turn (8)"), wxPoint(810,380), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_TURN_8"));
    wxFont ButtonTurn8Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonTurn8->SetFont(ButtonTurn8Font);
    ButtonOPE9 = new wxButton(PanelDataMgr, ID_BUTTON_OPE9, _("OPE (9)"), wxPoint(810,430), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_OPE9"));
    wxFont ButtonOPE9Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonOPE9->SetFont(ButtonOPE9Font);
    ButtonDive4 = new wxButton(PanelDataMgr, ID_BUTTON_DIVE_4, _("Dive (4)"), wxPoint(660,330), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_DIVE_4"));
    wxFont ButtonDive4Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonDive4->SetFont(ButtonDive4Font);
    ButtonLand5 = new wxButton(PanelDataMgr, ID_BUTTON_LAND_5, _("Land (5)"), wxPoint(660,380), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_LAND_5"));
    wxFont ButtonLand5Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonLand5->SetFont(ButtonLand5Font);
    ButtonSpeed6 = new wxButton(PanelDataMgr, ID_BUTTON_SPEED_6, _("Speed (6)"), wxPoint(660,430), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_SPEED_6"));
    wxFont ButtonSpeed6Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSpeed6->SetFont(ButtonSpeed6Font);
    ButtonTakeoff1 = new wxButton(PanelDataMgr, ID_BUTTON_TAKEOFF_1, _("Takeoff (1)"), wxPoint(510,330), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_TAKEOFF_1"));
    wxFont ButtonTakeoff1Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonTakeoff1->SetFont(ButtonTakeoff1Font);
    ButtonClimb2 = new wxButton(PanelDataMgr, ID_BUTTON_CLIMB_2, _("Climb (2)"), wxPoint(510,380), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_CLIMB_2"));
    wxFont ButtonClimb2Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonClimb2->SetFont(ButtonClimb2Font);
    ButtonCruise3 = new wxButton(PanelDataMgr, ID_BUTTON_CRUISE_3, _("Cruise (3)"), wxPoint(510,430), wxSize(130,40), 0, wxDefaultValidator, _T("ID_BUTTON_CRUISE_3"));
    wxFont ButtonCruise3Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonCruise3->SetFont(ButtonCruise3Font);
    StaticTextOAT = new wxStaticText(PanelDataMgr, ID_STATICTEXT_OAT, _("OAT"), wxPoint(795,100), wxDefaultSize, 0, _T("ID_STATICTEXT_OAT"));
    StaticTextOAT->SetMinSize(wxSize(55,25));
    wxFont StaticTextOATFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextOAT->SetFont(StaticTextOATFont);
    StaticTextStandby = new wxStaticText(PanelDataMgr, ID_STATICTEXT_STANDBY, _("Standby"), wxPoint(385,290), wxDefaultSize, 0, _T("ID_STATICTEXT_STANDBY"));
    StaticTextStandby->SetMinSize(wxSize(90,25));
    wxFont StaticTextStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextStandby->SetFont(StaticTextStandbyFont);
    StaticTextCurrent = new wxStaticText(PanelDataMgr, ID_STATICTEXT_CURRENT, _("Current"), wxPoint(235,290), wxSize(80,20), 0, _T("ID_STATICTEXT_CURRENT"));
    wxFont StaticTextCurrentFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextCurrent->SetFont(StaticTextCurrentFont);
    TextCtrlStandbyFirstCodePrefix = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_STANDBY_FIRST_CODE_PREFIX, _("0"), wxPoint(370,330), wxSize(120,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_STANDBY_FIRST_CODE_PREFIX"));
    wxFont TextCtrlStandbyFirstCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlStandbyFirstCodePrefix->SetFont(TextCtrlStandbyFirstCodePrefixFont);
    TextCtrlCurrentFirstCodePrefix = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_CURRENT_FIRST_CODE_PREFIX, _("0"), wxPoint(220,330), wxSize(120,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CURRENT_FIRST_CODE_PREFIX"));
    wxFont TextCtrlCurrentFirstCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCurrentFirstCodePrefix->SetFont(TextCtrlCurrentFirstCodePrefixFont);
    TextCtrlStandbySecondCodePrefix = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_STANDBY_SECOND_CODE_PREFIX, _("0"), wxPoint(370,380), wxSize(120,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_STANDBY_SECOND_CODE_PREFIX"));
    wxFont TextCtrlStandbySecondCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlStandbySecondCodePrefix->SetFont(TextCtrlStandbySecondCodePrefixFont);
    TextCtrlStandbyThirdCodePrefix = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_STANDBY_THIRD_CODE_PREFIX, _("0"), wxPoint(370,430), wxSize(120,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_STANDBY_THIRD_CODE_PREFIX"));
    wxFont TextCtrlStandbyThirdCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlStandbyThirdCodePrefix->SetFont(TextCtrlStandbyThirdCodePrefixFont);
    TextCtrlCurrentSecondCodePrefix = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_CURRENT_SECOND_CODE_PREFIX, _("0"), wxPoint(220,380), wxSize(120,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CURRENT_SECOND_CODE_PREFIX"));
    wxFont TextCtrlCurrentSecondCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCurrentSecondCodePrefix->SetFont(TextCtrlCurrentSecondCodePrefixFont);
    TextCtrlCurrentThirdCodePrefix = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_CURRENT_THIRD_CODE_PREFIX, _("0"), wxPoint(220,430), wxSize(120,40), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CURRENT_THIRD_CODE_PREFIX"));
    wxFont TextCtrlCurrentThirdCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCurrentThirdCodePrefix->SetFont(TextCtrlCurrentThirdCodePrefixFont);
    StaticTextFirstCodePrefix = new wxStaticText(PanelDataMgr, ID_STATICTEXT_FIRST_CODE_PREFIX, _("First Code Prefix"), wxPoint(20,335), wxSize(180,30), 0, _T("ID_STATICTEXT_FIRST_CODE_PREFIX"));
    wxFont StaticTextFirstCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextFirstCodePrefix->SetFont(StaticTextFirstCodePrefixFont);
    StaticTextSecondCodePrefix = new wxStaticText(PanelDataMgr, ID_STATICTEXT_SECOND_CODE_PREFIX, _("Second Code Prefix"), wxPoint(20,385), wxSize(220,30), 0, _T("ID_STATICTEXT_SECOND_CODE_PREFIX"));
    wxFont StaticTextSecondCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextSecondCodePrefix->SetFont(StaticTextSecondCodePrefixFont);
    StaticTextThirdCodePrefix = new wxStaticText(PanelDataMgr, ID_STATICTEXT_THIRD_CODE_PREFIX, _("Third Code Prefix"), wxPoint(20,435), wxSize(190,30), 0, _T("ID_STATICTEXT_THIRD_CODE_PREFIX"));
    wxFont StaticTextThirdCodePrefixFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextThirdCodePrefix->SetFont(StaticTextThirdCodePrefixFont);
    ButtonSet = new wxButton(PanelDataMgr, ID_BUTTON_SET, _("Set"), wxPoint(220,480), wxSize(120,40), 0, wxDefaultValidator, _T("ID_BUTTON_SET"));
    wxFont ButtonSetFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSet->SetFont(ButtonSetFont);
    ButtonReset = new wxButton(PanelDataMgr, ID_BUTTON_RESET, _("Reset"), wxPoint(370,480), wxSize(120,40), 0, wxDefaultValidator, _T("ID_BUTTON_RESET"));
    wxFont ButtonResetFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonReset->SetFont(ButtonResetFont);
    StaticTextCRM114 = new wxStaticText(PanelDataMgr, ID_STATICTEXT_CRM114, _("CRM114"), wxPoint(20,270), wxSize(150,60), 0, _T("ID_STATICTEXT_CRM114"));
    wxFont StaticTextCRM114Font(24,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextCRM114->SetFont(StaticTextCRM114Font);
    StaticTextCrew = new wxStaticText(PanelDataMgr, ID_STATICTEXT_CREW, _("Crew"), wxPoint(135,100), wxDefaultSize, 0, _T("ID_STATICTEXT_CREW"));
    StaticTextCrew->SetMinSize(wxSize(60,25));
    wxFont StaticTextCrewFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextCrew->SetFont(StaticTextCrewFont);
    StaticTextBaggage = new wxStaticText(PanelDataMgr, ID_STATICTEXT_BAGGAGE, _("Baggage"), wxPoint(235,100), wxDefaultSize, 0, _T("ID_STATICTEXT_BAGGAGE"));
    StaticTextBaggage->SetMinSize(wxSize(95,30));
    wxFont StaticTextBaggageFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextBaggage->SetFont(StaticTextBaggageFont);
    StaticTextRPM = new wxStaticText(PanelDataMgr, ID_STATICTEXT_RPM, _("RPM"), wxPoint(365,100), wxDefaultSize, 0, _T("ID_STATICTEXT_RPM"));
    StaticTextRPM->SetMinSize(wxSize(50,25));
    wxFont StaticTextRPMFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextRPM->SetFont(StaticTextRPMFont);
    StaticTextMP = new wxStaticText(PanelDataMgr, ID_STATICTEXT_MP, _("MP"), wxPoint(480,100), wxDefaultSize, 0, _T("ID_STATICTEXT_MP"));
    StaticTextMP->SetMinSize(wxSize(45,25));
    wxFont StaticTextMPFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextMP->SetFont(StaticTextMPFont);
    StaticTextFlaps = new wxStaticText(PanelDataMgr, ID_STATICTEXT_FLAPS, _("Flaps"), wxPoint(690,100), wxDefaultSize, 0, _T("ID_STATICTEXT_FLAPS"));
    StaticTextFlaps->SetMinSize(wxSize(65,25));
    wxFont StaticTextFlapsFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextFlaps->SetFont(StaticTextFlapsFont);
    StaticTextCRM114CodeBook = new wxStaticText(PanelDataMgr, ID_STATICTEXT_CRM114CodeBook, _("<---------------- CRM114 Code Book ----------------->"), wxPoint(510,290), wxSize(430,30), 0, _T("ID_STATICTEXT_CRM114CodeBook"));
    wxFont StaticTextCRM114CodeBookFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextCRM114CodeBook->SetFont(StaticTextCRM114CodeBookFont);
    StaticTextCurrentManual = new wxStaticText(PanelDataMgr, ID_STATICTEXT_CURRENT_MANUAL, _("Current"), wxPoint(1000,140), wxSize(80,20), 0, _T("ID_STATICTEXT_CURRENT_MANUAL"));
    wxFont StaticTextCurrentManualFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticTextCurrentManual->SetFont(StaticTextCurrentManualFont);
    ButtonSetManual = new wxButton(PanelDataMgr, ID_BUTTON_SET_MANUAL, _("Set"), wxPoint(1090,130), wxSize(100,40), 0, wxDefaultValidator, _T("ID_BUTTON_SET_MANUAL"));
    wxFont ButtonSetManualFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    ButtonSetManual->SetFont(ButtonSetManualFont);
    TextCtrlCrewStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_CREW_STANDBY, _("180"), wxPoint(120,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_CREW_STANDBY"));
    wxFont TextCtrlCrewStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCrewStandby->SetFont(TextCtrlCrewStandbyFont);
    TextCtrlBaggageStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_BAGGAGE_STANDBY, _("0"), wxPoint(230,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_BAGGAGE_STANDBY"));
    wxFont TextCtrlBaggageStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlBaggageStandby->SetFont(TextCtrlBaggageStandbyFont);
    TextCtrlRPMStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_RPM_STANDBY, _("0"), wxPoint(340,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_RPM_STANDBY"));
    wxFont TextCtrlRPMStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlRPMStandby->SetFont(TextCtrlRPMStandbyFont);
    TextCtrlMPStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_MP_STANDBY, _("0"), wxPoint(450,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_MP_STANDBY"));
    wxFont TextCtrlMPStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlMPStandby->SetFont(TextCtrlMPStandbyFont);
    TextCtrlFlapsStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_FLAPS_STANDBY, _("0"), wxPoint(670,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_FLAPS_STANDBY"));
    wxFont TextCtrlFlapsStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlFlapsStandby->SetFont(TextCtrlFlapsStandbyFont);
    TextCtrlOATStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_OAT_STANDBY, _("68"), wxPoint(780,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_OAT_STANDBY"));
    wxFont TextCtrlOATStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlOATStandby->SetFont(TextCtrlOATStandbyFont);
    StaticText2 = new wxStaticText(PanelDataMgr, ID_STATICTEXT1, _("Standby"), wxPoint(1000,185), wxSize(95,30), 0, _T("ID_STATICTEXT1"));
    wxFont StaticText2Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText2->SetFont(StaticText2Font);
    StaticText3 = new wxStaticText(PanelDataMgr, ID_STATICTEXT2, _("<------------------------------------------------------------------------ Manual Data Entry ------------------------------------------------------------------------>"), wxPoint(10,70), wxSize(1070,20), 0, _T("ID_STATICTEXT2"));
    wxFont StaticText3Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText3->SetFont(StaticText3Font);
    StaticText4 = new wxStaticText(PanelDataMgr, ID_STATICTEXT4, _("<------------------------------------------------------------------- Flight Testing ------------------------------------------------------------------->"), wxPoint(16,240), wxSize(1168,40), 0, _T("ID_STATICTEXT4"));
    wxFont StaticText4Font(16,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText4->SetFont(StaticText4Font);
    StaticText5 = new wxStaticText(PanelDataMgr, ID_STATICTEXT5, _("First\n1        \n2  \n3 \n4   \n5       \n6     \n7    \n8     \n9\n10 ...     "), wxPoint(950,290), wxSize(50,260), 0, _T("ID_STATICTEXT5"));
    wxFont StaticText5Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText5->SetFont(StaticText5Font);
    StaticText6 = new wxStaticText(PanelDataMgr, ID_STATICTEXT6, _("Second\nDensity Alt\nAirspeed\nAirspeed\nAirspeed\nAirspeed\nAirspeed\nDensity Alt\nAirspeed\nmanual"), wxPoint(995,290), wxSize(95,260), 0, _T("ID_STATICTEXT6"));
    wxFont StaticText6Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText6->SetFont(StaticText6Font);
    StaticText7 = new wxStaticText(PanelDataMgr, ID_STATICTEXT7, _("Third\nFlaps\nFlaps\nDensity Alt\nFlaps\nFlaps\nDensity Alt\n\nDensity Alt\nmanual"), wxPoint(1090,290), wxSize(95,260), 0, _T("ID_STATICTEXT7"));
    wxFont StaticText7Font(12,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText7->SetFont(StaticText7Font);
    StaticText8 = new wxStaticText(PanelDataMgr, ID_STATICTEXT8, _("<----- Code Prefixes ----->"), wxPoint(952,264), wxSize(240,25), 0, _T("ID_STATICTEXT8"));
    wxFont StaticText8Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText8->SetFont(StaticText8Font);
    StaticText12 = new wxStaticText(PanelDataMgr, ID_STATICTEXT12, _("Cowl Flap"), wxPoint(565,104), wxSize(100,22), 0, _T("ID_STATICTEXT12"));
    wxFont StaticText12Font(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    StaticText12->SetFont(StaticText12Font);
    TextCtrlCowlFlap = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_COWL_FLAP, _("0"), wxPoint(560,130), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_COWL_FLAP"));
    wxFont TextCtrlCowlFlapFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCowlFlap->SetFont(TextCtrlCowlFlapFont);
    TextCtrlCowlFlapStandby = new wxTextCtrl(PanelDataMgr, ID_TEXTCTRL_COWL_FLAP_STANDBY, _("0"), wxPoint(560,180), wxSize(100,40), 0, wxDefaultValidator, _T("ID_TEXTCTRL_COWL_FLAP_STANDBY"));
    wxFont TextCtrlCowlFlapStandbyFont(14,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    TextCtrlCowlFlapStandby->SetFont(TextCtrlCowlFlapStandbyFont);
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

    Connect(ID_BUTTON_STALL_7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonStall7Click);
    Connect(ID_BUTTON_TURN_8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonTurn8Click);
    Connect(ID_BUTTON_OPE9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonOPE9Click);
    Connect(ID_BUTTON_DIVE_4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonDive4Click);
    Connect(ID_BUTTON_LAND_5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonLand5Click);
    Connect(ID_BUTTON_SPEED_6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonSpeed6Click);
    Connect(ID_BUTTON_TAKEOFF_1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonTakeoff1Click);
    Connect(ID_BUTTON_CLIMB_2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonClimb2Click);
    Connect(ID_BUTTON_CRUISE_3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonCruise3Click);
    Connect(ID_BUTTON_SET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonSetClick);
    Connect(ID_BUTTON_RESET,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonResetClick);
    Connect(ID_BUTTON_SET_MANUAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnButtonSetManualClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleDataMgrFrame::OnAbout);
    //*)

  bool ret = ManualData.open_socket(PORT_MANUAL,&ManualData.MANUALsockfd);
  if (ret!=true) {
    printf("Unable to open_socket bye!\n");
    manual_port_opened = false;
  }
  else manual_port_opened = true;

}

OpenEagleDataMgrFrame::~OpenEagleDataMgrFrame()
{
    //(*Destroy(OpenEagleDataMgrFrame)
    //*)
}

void OpenEagleDataMgrFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagleDataMgrFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}


void OpenEagleDataMgrFrame::OnButtonData2SocketClick(wxCommandEvent& event)
{
  PanelDataMgr->Enable(false);
  PanelDataMgr->Enable(true);
 // ButtonOpenEagleGarminG5Protocol2Socket->Hide(true);
// ButtonOpenEagleGarminG5Protocol2Socket->Hide();
}




void OpenEagleDataMgrFrame::OnButtonTakeoff1Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("1");
//  TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.COMPdensity_altitude));
//  TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.flap_setting));
}

void OpenEagleDataMgrFrame::OnButtonClimb2Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("2");
//  TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.G5airspeed_kt));
//  TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.flap_setting));
}

void OpenEagleDataMgrFrame::OnButtonCruise3Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("3");
//  TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.G5airspeed_kt));
//  TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.COMPdensity_altitude));
}

void OpenEagleDataMgrFrame::OnButtonDive4Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("4");
 // TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.G5airspeed_kt));
 // TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.flap_setting));
}

void OpenEagleDataMgrFrame::OnButtonLand5Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("5");
 // TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.G5airspeed_kt));
 // TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.flap_setting));
}

void OpenEagleDataMgrFrame::OnButtonSpeed6Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("6");
 // TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.G5airspeed_kt));
 // TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.COMPdensity_altitude));
}

void OpenEagleDataMgrFrame::OnButtonStall7Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("7");
 // TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.COMPdensity_altitude));
}

void OpenEagleDataMgrFrame::OnButtonTurn8Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("8");
 // TextCtrlStandbySecondCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.G5airspeed_kt));
 // TextCtrlStandbyThirdCodePrefix->SetValue(wxString::Format(wxT("%f"), (double)GPSdata.OpenEagleExt.COMPdensity_altitude));
}

void OpenEagleDataMgrFrame::OnButtonOPE9Click(wxCommandEvent& event)
{
  TextCtrlStandbyFirstCodePrefix->SetValue("9");
}

void OpenEagleDataMgrFrame::OnButtonSetClick(wxCommandEvent& event)
{
  ///OpenEagleManual
  this->ManualData.OpenEagleManual.first_prefix = std::stod(TextCtrlStandbyFirstCodePrefix->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.second_prefix = std::stod(TextCtrlStandbySecondCodePrefix->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.third_prefix = std::stod(TextCtrlStandbyThirdCodePrefix->GetValue().ToStdString());
  if (manual_port_opened) {
    bool io_ret = write(ManualData.MANUALsockfd,
                        &ManualData.OpenEagleManual,
                        sizeof(ManualData.OpenEagleManual) );
    if (io_ret <0) {
       printf(" socket failure io_ret %d\n",io_ret);
       printf("likely fgfs exited\n");
       exit(1);
    } else printf("\nwrite to socket successful\n");
  }
  else {
    bool ret = ManualData.open_socket(PORT_MANUAL,&ManualData.MANUALsockfd);
    if (ret!=true) {
      printf("Unable to open_socket bye!\n");
      manual_port_opened = false;
    }
    else manual_port_opened = true;
    if (manual_port_opened) {
      bool io_ret = write(ManualData.MANUALsockfd,
                          &ManualData.OpenEagleManual,
                          sizeof(ManualData.OpenEagleManual) );
      if (io_ret <0) {
         printf(" socket failure io_ret %d\n",io_ret);
         printf("likely fgfs exited\n");
         exit(1);
      } else printf("\nwrite to socket successful\n");
    }
  }
  TextCtrlCurrentFirstCodePrefix->SetValue(TextCtrlStandbyFirstCodePrefix->GetValue());
  TextCtrlCurrentSecondCodePrefix->SetValue(TextCtrlStandbySecondCodePrefix->GetValue());
  TextCtrlCurrentThirdCodePrefix->SetValue(TextCtrlStandbyThirdCodePrefix->GetValue());
}

void OpenEagleDataMgrFrame::OnButtonResetClick(wxCommandEvent& event)
{

  TextCtrlStandbyFirstCodePrefix->SetValue("0");
  TextCtrlStandbySecondCodePrefix->SetValue("0");
  TextCtrlStandbyThirdCodePrefix->SetValue("0");

  TextCtrlCurrentFirstCodePrefix->SetValue("0");
  TextCtrlCurrentSecondCodePrefix->SetValue("0");
  TextCtrlCurrentThirdCodePrefix->SetValue("0");

  /// OpenEagleManual
  this->ManualData.OpenEagleManual.first_prefix = 0;
  this->ManualData.OpenEagleManual.second_prefix = 0;
  this->ManualData.OpenEagleManual.third_prefix = 0;

  bool io_ret = write(ManualData.MANUALsockfd,
                      &ManualData.OpenEagleManual,
                      sizeof(ManualData.OpenEagleManual) );
  if (io_ret <0) {
     printf(" socket failure io_ret %d\n",io_ret);
     printf("likely fgfs exited\n");
     exit(1);
  } else printf("\nwrite to socket successful\n");

}

void OpenEagleDataMgrFrame::OnButtonSetManualClick(wxCommandEvent& event)
{
  ///OpenEagleManual
  this->ManualData.OpenEagleManual.crew_wt = std::stod(TextCtrlCrewStandby->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.baggage_wt = std::stod(TextCtrlBaggageStandby->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.RPM = std::stod(TextCtrlRPMStandby->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.manifold_pressure_inhg = std::stod(TextCtrlMPStandby->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.cowl_flap_in = std::stod(TextCtrlCowlFlapStandby->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.flap_setting = std::stod(TextCtrlFlapsStandby->GetValue().ToStdString());
  this->ManualData.OpenEagleManual.outside_air_temp_degf = std::stod(TextCtrlOATStandby->GetValue().ToStdString());

  TextCtrlCrew->SetValue(TextCtrlCrewStandby->GetValue());
  TextCtrlBaggage->SetValue(TextCtrlBaggageStandby->GetValue());
  TextCtrlRPM->SetValue(TextCtrlRPMStandby->GetValue());
  TextCtrlMP->SetValue(TextCtrlMPStandby->GetValue());
  TextCtrlCowlFlap->SetValue(TextCtrlCowlFlapStandby->GetValue());
  TextCtrlFlaps->SetValue(TextCtrlFlapsStandby->GetValue());
  TextCtrlOAT->SetValue(TextCtrlOATStandby->GetValue());

  /// OpenEagleManualData
  this->ManualData.OpenEagleManual.crew_wt = std::stod(TextCtrlCrewStandby->GetValue().ToStdString());

  TextCtrlCrew->SetValue(TextCtrlCrewStandby->GetValue());

  this->ManualData.OpenEagleManual.baggage_wt = std::stod(TextCtrlBaggageStandby->GetValue().ToStdString());
  TextCtrlBaggage->SetValue(TextCtrlBaggageStandby->GetValue());

  this->ManualData.OpenEagleManual.RPM = std::stod(TextCtrlRPMStandby->GetValue().ToStdString());
  TextCtrlRPM->SetValue(TextCtrlRPMStandby->GetValue());

  this->ManualData.OpenEagleManual.manifold_pressure_inhg = std::stod(TextCtrlMPStandby->GetValue().ToStdString());
  TextCtrlMP->SetValue(TextCtrlMPStandby->GetValue());

  this->ManualData.OpenEagleManual.cowl_flap_in = std::stod(TextCtrlCowlFlapStandby->GetValue().ToStdString());
  TextCtrlCowlFlap->SetValue(TextCtrlCowlFlapStandby->GetValue());

  this->ManualData.OpenEagleManual.flap_setting = std::stod(TextCtrlFlapsStandby->GetValue().ToStdString());
  TextCtrlFlaps->SetValue(TextCtrlFlapsStandby->GetValue());

  this->ManualData.OpenEagleManual.outside_air_temp_degf = std::stod(TextCtrlOATStandby->GetValue().ToStdString());
  TextCtrlOAT->SetValue(TextCtrlOATStandby->GetValue());

  if (manual_port_opened) {
    bool io_ret = write(ManualData.MANUALsockfd,
                        &ManualData.OpenEagleManual,
                        sizeof(ManualData.OpenEagleManual) );
    if (io_ret <0) {
       printf(" socket failure io_ret %d\n",io_ret);
       printf("likely fgfs exited\n");
       exit(1);
    } else printf("\nwrite to socket successful\n");
  }
  else {
    bool ret = ManualData.open_socket(PORT_MANUAL,&ManualData.MANUALsockfd);
    if (ret!=true) {
      printf("Unable to open_socket bye!\n");
      manual_port_opened = false;
    }
    else manual_port_opened = true;
    if (manual_port_opened) {
      bool io_ret = write(ManualData.MANUALsockfd,
                          &ManualData.OpenEagleManual,
                          sizeof(ManualData.OpenEagleManual) );
      if (io_ret <0) {
         printf(" socket failure io_ret %d\n",io_ret);
         printf("likely fgfs exited\n");
         exit(1);
      } else printf("\nwrite to socket successful\n");
    }
  }
}

