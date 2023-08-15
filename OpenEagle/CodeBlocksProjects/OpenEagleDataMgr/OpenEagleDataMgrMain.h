/***************************************************************
 * Name:      OpenEagleDataMgrMain.h
 * Purpose:   Defines Application Frame
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

#ifndef OPENEAGLEDATAMGRMAIN_H
#define OPENEAGLEDATAMGRMAIN_H

//(*Headers(OpenEagleDataMgrFrame)
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
#include "../data_mgr/data_mgr.hxx"

class OpenEagleDataMgrFrame: public wxFrame
{
    public:
        data_mgr ManualData;
        OpenEagleDataMgrFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagleDataMgrFrame();
    bool manual_port_opened;
    private:

        //(*Handlers(OpenEagleDataMgrFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonGPS_ArduinnoClick(wxCommandEvent& event);
        void OnButtonDebugClick(wxCommandEvent& event);
        void OnButtonIndicatedAltitudeClick(wxCommandEvent& event);
        void OnButtonData2SocketClick(wxCommandEvent& event);
        void OnButtonSelectClick(wxCommandEvent& event);
        void OnButtonRealTimeEditClick(wxCommandEvent& event);
        void OnButtonTakeoff1Click(wxCommandEvent& event);
        void OnButtonClimb2Click(wxCommandEvent& event);
        void OnButtonCruise3Click(wxCommandEvent& event);
        void OnButtonDive4Click(wxCommandEvent& event);
        void OnButtonLand5Click(wxCommandEvent& event);
        void OnButtonSpeed6Click(wxCommandEvent& event);
        void OnButtonStall7Click(wxCommandEvent& event);
        void OnButtonTurn8Click(wxCommandEvent& event);
        void OnButtonOPE9Click(wxCommandEvent& event);
        void OnButtonSetClick(wxCommandEvent& event);
        void OnButtonResetClick(wxCommandEvent& event);
        void OnButtonSetManualClick(wxCommandEvent& event);
        void OnButtonUbloxGPSClick(wxCommandEvent& event);
        void OnButtonTestGPSExemplarClick(wxCommandEvent& event);
        void OnButtonRealTimeEditClick1(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButtonGPStestClick(wxCommandEvent& event);
        void OnButtonFuelComputerTestClick(wxCommandEvent& event);
        void OnButtonEngineMonitorTestClick(wxCommandEvent& event);
        void OnButton1ClickMultipleProtocolWrite(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagleDataMgrFrame)
        static const long ID_STATICTEXT_OPEN_EAGLE_CRM114;
        static const long ID_TEXTCTRL_CREW;
        static const long ID_TEXTCTRL_BAGGAGE;
        static const long ID_TEXTCTRL_RPM;
        static const long ID_TEXTCTRL_MP;
        static const long ID_TEXTCTRL_FLAPS;
        static const long ID_TEXTCTRL_OAT;
        static const long ID_BUTTON_STALL_7;
        static const long ID_BUTTON_TURN_8;
        static const long ID_BUTTON_OPE9;
        static const long ID_BUTTON_DIVE_4;
        static const long ID_BUTTON_LAND_5;
        static const long ID_BUTTON_SPEED_6;
        static const long ID_BUTTON_TAKEOFF_1;
        static const long ID_BUTTON_CLIMB_2;
        static const long ID_BUTTON_CRUISE_3;
        static const long ID_STATICTEXT_OAT;
        static const long ID_STATICTEXT_STANDBY;
        static const long ID_STATICTEXT_CURRENT;
        static const long ID_TEXTCTRL_STANDBY_FIRST_CODE_PREFIX;
        static const long ID_TEXTCTRL_CURRENT_FIRST_CODE_PREFIX;
        static const long ID_TEXTCTRL_STANDBY_SECOND_CODE_PREFIX;
        static const long ID_TEXTCTRL_STANDBY_THIRD_CODE_PREFIX;
        static const long ID_TEXTCTRL_CURRENT_SECOND_CODE_PREFIX;
        static const long ID_TEXTCTRL_CURRENT_THIRD_CODE_PREFIX;
        static const long ID_STATICTEXT_FIRST_CODE_PREFIX;
        static const long ID_STATICTEXT_SECOND_CODE_PREFIX;
        static const long ID_STATICTEXT_THIRD_CODE_PREFIX;
        static const long ID_BUTTON_SET;
        static const long ID_BUTTON_RESET;
        static const long ID_STATICTEXT_CRM114;
        static const long ID_STATICTEXT_CREW;
        static const long ID_STATICTEXT_BAGGAGE;
        static const long ID_STATICTEXT_RPM;
        static const long ID_STATICTEXT_MP;
        static const long ID_STATICTEXT_FLAPS;
        static const long ID_STATICTEXT_CRM114CodeBook;
        static const long ID_STATICTEXT_CURRENT_MANUAL;
        static const long ID_BUTTON_SET_MANUAL;
        static const long ID_TEXTCTRL_CREW_STANDBY;
        static const long ID_TEXTCTRL_BAGGAGE_STANDBY;
        static const long ID_TEXTCTRL_RPM_STANDBY;
        static const long ID_TEXTCTRL_MP_STANDBY;
        static const long ID_TEXTCTRL_FLAPS_STANDBY;
        static const long ID_TEXTCTRL_OAT_STANDBY;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT12;
        static const long ID_TEXTCTRL_COWL_FLAP;
        static const long ID_TEXTCTRL_COWL_FLAP_STANDBY;
        static const long ID_PANEL_DATA_MGR;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OpenEagleDataMgrFrame)
        wxButton* ButtonClimb2;
        wxButton* ButtonCruise3;
        wxButton* ButtonDive4;
        wxButton* ButtonLand5;
        wxButton* ButtonOPE9;
        wxButton* ButtonReset;
        wxButton* ButtonSet;
        wxButton* ButtonSetManual;
        wxButton* ButtonSpeed6;
        wxButton* ButtonStall7;
        wxButton* ButtonTakeoff1;
        wxButton* ButtonTurn8;
        wxFileDialog* FileDialogSelectFlightHistory;
        wxPanel* PanelDataMgr;
        wxStaticText* StaticText12;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticTextBaggage;
        wxStaticText* StaticTextCRM114;
        wxStaticText* StaticTextCRM114CodeBook;
        wxStaticText* StaticTextCrew;
        wxStaticText* StaticTextCurrent;
        wxStaticText* StaticTextCurrentManual;
        wxStaticText* StaticTextFirstCodePrefix;
        wxStaticText* StaticTextFlaps;
        wxStaticText* StaticTextMP;
        wxStaticText* StaticTextOAT;
        wxStaticText* StaticTextRPM;
        wxStaticText* StaticTextSecondCodePrefix;
        wxStaticText* StaticTextStandby;
        wxStaticText* StaticTextThirdCodePrefix;
        wxStaticText* StaticText_OpenEagleCRM114;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlBaggage;
        wxTextCtrl* TextCtrlBaggageStandby;
        wxTextCtrl* TextCtrlCowlFlap;
        wxTextCtrl* TextCtrlCowlFlapStandby;
        wxTextCtrl* TextCtrlCrew;
        wxTextCtrl* TextCtrlCrewStandby;
        wxTextCtrl* TextCtrlCurrentFirstCodePrefix;
        wxTextCtrl* TextCtrlCurrentSecondCodePrefix;
        wxTextCtrl* TextCtrlCurrentThirdCodePrefix;
        wxTextCtrl* TextCtrlFlaps;
        wxTextCtrl* TextCtrlFlapsStandby;
        wxTextCtrl* TextCtrlMP;
        wxTextCtrl* TextCtrlMPStandby;
        wxTextCtrl* TextCtrlOAT;
        wxTextCtrl* TextCtrlOATStandby;
        wxTextCtrl* TextCtrlRPM;
        wxTextCtrl* TextCtrlRPMStandby;
        wxTextCtrl* TextCtrlStandbyFirstCodePrefix;
        wxTextCtrl* TextCtrlStandbySecondCodePrefix;
        wxTextCtrl* TextCtrlStandbyThirdCodePrefix;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLEDATAMGRMAIN_H
