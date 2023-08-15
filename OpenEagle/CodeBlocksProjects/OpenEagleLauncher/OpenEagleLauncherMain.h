/***************************************************************
 * Name:      OpenEagleLauncherMain.h
 * Purpose:   Defines Application Frame
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

#ifndef SYNTHETIC_VISION_LAUNCHERMAIN_H
#define SYNTHETIC_VISION_LAUNCHERMAIN_H

//(*Headers(OpenEagleLauncherFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

#include "../OpenEaglePaths/OpenEaglePaths.hxx"
#include "../TimeStrings/TimeStrings.hxx"

class OpenEagleLauncherFrame: public wxFrame
{
    public:
        OpenEaglePaths paths;
        TimeStrings time_strings;
        OpenEagleLauncherFrame(wxWindow* parent,wxWindowID id = -1);
        double elevation;
        double latitude;
        double longitude;

        virtual ~OpenEagleLauncherFrame();

        std::string commandline;
        void initialize_commandline();
        void switches_to_commandline();
        void fixed_switches_to_commandline();

    private:

        //(*Handlers(OpenEagleLauncherFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnTextCtrlFgsceneryText(wxCommandEvent& event);
        void OnButtonStartCoordinatesClick(wxCommandEvent& event);
        void OnButton1ClickStartAirport(wxCommandEvent& event);
        void OnButtonStartCoordinatesElevationClick(wxCommandEvent& event);
        void OnButtonHaltClick(wxCommandEvent& event);
        void OnButtonStartAirportClick(wxCommandEvent& event);
        void OnCheckBoxFdmNullClick(wxCommandEvent& event);
        void OnButton_Lookup_FlightClick(wxCommandEvent& event);
        void OnButtonSelectFlightPlanClick(wxCommandEvent& event);
        void OnButtonCheckCGClick(wxCommandEvent& event);
        void OnButtonCheckCGClick1(wxCommandEvent& event);
        void OnButtonCheckCGClick2(wxCommandEvent& event);
        void OnTextCtrlWtCrewTextEnter(wxCommandEvent& event);
        void OnTextCtrlWtBaggageText(wxCommandEvent& event);
        void OnTextCtrlGalFuelText(wxCommandEvent& event);
        void OnCheckBoxData1Click(wxCommandEvent& event);
        void OnCheckBoxData2Click(wxCommandEvent& event);
        void OnCheckBoxWriteOpenEagleExtClick(wxCommandEvent& event);
        void OnCheckBoxWriteFGFSfileClick(wxCommandEvent& event);
        void OnCheckBoxWriteFGFSfileClick1(wxCommandEvent& event);
        void OnCheckBoxWriteFGFSfileClick2(wxCommandEvent& event);
        void OnCheckBoxWriteOpenEagleExtClick1(wxCommandEvent& event);
        void OnCheckBoxWriteFGFSfileClick3(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnTextCtrlData1Text(wxCommandEvent& event);
        void OnTextCtrl1Text1(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnTextCtrl3Text(wxCommandEvent& event);
        void OnTextCtrl4Text(wxCommandEvent& event);
        void OnTextCtrlData1Text1(wxCommandEvent& event);
        void OnCheckBox10Click(wxCommandEvent& event);
        void OnTextCtrlOpenEagleGPSText(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagleLauncherFrame)
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL4;
        static const long ID_TEXTCTRL_OPEN_EAGLE_G5;
        static const long ID_CHECKBOX_OPENEAGLE_G5;
        static const long ID_TEXTCTRL8;
        static const long ID_TEXTCTRL_FLIGHT_PLAN;
        static const long ID_STATICTEXT_FLIGHT_PLAN;
        static const long ID_BUTTON_START_AIRPORT;
        static const long ID_BUTTON2;
        static const long ID_TEXTCTRL_METAR;
        static const long ID_TEXTCTRL12;
        static const long ID_CHECKBOX3;
        static const long ID_TEXTCTRL13;
        static const long ID_TEXTCTRL16;
        static const long ID_BUTTON_START_COORDINATES_ELEVATION;
        static const long ID_TEXTCTRL17;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX10;
        static const long ID_CHECKBOX16;
        static const long ID_CHECKBOX17;
        static const long ID_CHECKBOX18;
        static const long ID_CHECKBOX19;
        static const long ID_CHECKBOX20;
        static const long ID_TEXTCTRL5;
        static const long ID_CHECKBOX23;
        static const long ID_CHECKBOX24;
        static const long ID_CHECKBOX27;
        static const long ID_TEXTCTRL10;
        static const long ID_CHOICE1;
        static const long ID_CHOICE2;
        static const long ID_CHECKBOX31;
        static const long ID_CHECKBOX12;
        static const long ID_TEXTCTRLCeiling;
        static const long ID_TEXTCTRL3;
        static const long ID_CHECKBOX_FDM_NULL;
        static const long ID_CHECKBOX2;
        static const long ID_TEXTCTRL7;
        static const long ID_BUTTON_LOOKUP_FLIGHT;
        static const long ID_BUTTON_SELECT_FLIGHT_PLAN;
        static const long ID_CHECKBOX_DISABLE_AI_TRAFFIC;
        static const long ID_STATICTEXT_AIRPORT;
        static const long ID_STATICTEXT_AIRCRAFT;
        static const long ID_STATICTEXT_LON;
        static const long ID_STATICTEXT_ALT;
        static const long ID_STATICTEXT_LAT;
        static const long ID_CHECKBOX_WRITE_OPEN_EAGLE_EXT;
        static const long ID_CHECKBOXWRITE_FGFS_FILE;
        static const long ID_CHECKBOX_DATA_OPEN_EAGLE_GPS_W_ALT;
        static const long ID_CHECKBOX5;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX9;
        static const long ID_CHECKBOX11;
        static const long ID_CHECKBOX_DATA_OPEN_EAGLE_GPS;
        static const long ID_CHECKBOX_DATA_OPEN_EAGLE_MANUAL;
        static const long ID_TEXTCTRL_OpenEagleGPS_W_ALT;
        static const long ID_CHECKBOX_DATA_OPEN_EAGLE_EM;
        static const long ID_CHECKBOX_DATA_OPEN_EAGLE_FC;
        static const long ID_TEXTCTRL_DATA_OPEN_EAGLE_GPS;
        static const long ID_TEXTCTROpenEagleManual;
        static const long ID_TEXTCTRL_OPEN_EAGLE_EM;
        static const long ID_TEXTCTRL_OPEN_EAGLE_FC;
        static const long ID_PANEL_LAUNCH_PANEL;
        //*)

        //(*Declarations(OpenEagleLauncherFrame)
        wxButton* ButtonQuit;
        wxButton* ButtonSelectFlightPlan;
        wxButton* ButtonStartAirport;
        wxButton* ButtonStartCoordinatesElevation;
        wxButton* Button_Lookup_Flight;
        wxCheckBox* CheckBox2;
        wxCheckBox* CheckBox3;
        wxCheckBox* CheckBox4;
        wxCheckBox* CheckBox5;
        wxCheckBox* CheckBox6;
        wxCheckBox* CheckBoxCeiling;
        wxCheckBox* CheckBoxData2;
        wxCheckBox* CheckBoxDataOpenEagleEM;
        wxCheckBox* CheckBoxDataOpenEagleFC;
        wxCheckBox* CheckBoxDataOpenEagleG5;
        wxCheckBox* CheckBoxDataOpenEagleGPS;
        wxCheckBox* CheckBoxDataOpenEagleGPSwAlt;
        wxCheckBox* CheckBoxDataOpenEagleManual;
        wxCheckBox* CheckBoxDisableAITraffic;
        wxCheckBox* CheckBoxDisableFullscreen;
        wxCheckBox* CheckBoxDisableHud3D;
        wxCheckBox* CheckBoxDisableRealWeatherFetch;
        wxCheckBox* CheckBoxDisableSound;
        wxCheckBox* CheckBoxEnableFullscreen;
        wxCheckBox* CheckBoxFdmNull;
        wxCheckBox* CheckBoxFgroot;
        wxCheckBox* CheckBoxGeometry;
        wxCheckBox* CheckBoxHttp;
        wxCheckBox* CheckBoxMetar;
        wxCheckBox* CheckBoxSeason;
        wxCheckBox* CheckBoxTimeOfDay;
        wxCheckBox* CheckBoxVisibilityMiles;
        wxCheckBox* CheckBoxWriteFGFSfile;
        wxCheckBox* CheckBoxWriteOpenEagleExt;
        wxChoice* ChoiceSeason;
        wxChoice* ChoiceTimeOfDay;
        wxFileDialog* FileDialogSelectFlightHistory;
        wxFileDialog* FileDialogSelectFlightPlan;
        wxPanel* PanelLaunchPanel;
        wxStaticText* Lon;
        wxStaticText* StaticTextAircraft;
        wxStaticText* StaticTextAirport;
        wxStaticText* StaticTextAlt;
        wxStaticText* StaticTextFlightPlan;
        wxStaticText* StaticTextLat;
        wxTextCtrl* TextCtrlAircraft;
        wxTextCtrl* TextCtrlAirport;
        wxTextCtrl* TextCtrlAltitude;
        wxTextCtrl* TextCtrlCeiling;
        wxTextCtrl* TextCtrlData2;
        wxTextCtrl* TextCtrlDataOpenEagleEM;
        wxTextCtrl* TextCtrlDataOpenEagleFC;
        wxTextCtrl* TextCtrlDataOpenEagleG5;
        wxTextCtrl* TextCtrlDataOpenEagleGPS;
        wxTextCtrl* TextCtrlDataOpenEagleGPSwAlt;
        wxTextCtrl* TextCtrlDataOpenEagleManual;
        wxTextCtrl* TextCtrlDisable2;
        wxTextCtrl* TextCtrlDisable;
        wxTextCtrl* TextCtrlFgroot;
        wxTextCtrl* TextCtrlFlightPlan;
        wxTextCtrl* TextCtrlGeometry;
        wxTextCtrl* TextCtrlHttpd;
        wxTextCtrl* TextCtrlLat;
        wxTextCtrl* TextCtrlLon;
        wxTextCtrl* TextCtrlMetar;
        wxTextCtrl* TextCtrlVisibilityMiles;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SYNTHETIC_VISION_LAUNCHERMAIN_H
