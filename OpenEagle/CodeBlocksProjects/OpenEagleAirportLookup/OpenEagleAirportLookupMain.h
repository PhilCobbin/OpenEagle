/***************************************************************
 * Name:      OpenEagleAirportLookupMain.h
 * Purpose:   Defines Application Frame
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

#ifndef OPENEAGLEAIRPORTLOOKUPMAIN_H
#define OPENEAGLEAIRPORTLOOKUPMAIN_H

//(*Headers(OpenEagleAirportLookupFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dirdlg.h>
#include <wx/frame.h>
#include <wx/listbox.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)
#include "../airport/airport.hxx"
#include "AirportFrame.h"
#include "InformationFrame.h"
class OpenEagleAirportLookupFrame: public wxFrame
{
    airport apt;
    public:

        OpenEagleAirportLookupFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagleAirportLookupFrame();

    private:

        //(*Handlers(OpenEagleAirportLookupFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonLookupAirportClick(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnTextCtrlAirport_IDTextEnter(wxCommandEvent& event);
        void OnTextCtrlAirport_IDText(wxCommandEvent& event);
        void OnTextCtrlAirport_IDText1(wxCommandEvent& event);
        void OnPanel1Paint(wxPaintEvent& event);
        void OnButton_AirportClick(wxCommandEvent& event);
        void OnTextCtrlAirport_IDText2(wxCommandEvent& event);
        void OnButtonAptInformationClick(wxCommandEvent& event);
        void OnButtonAptFrequenciesClick(wxCommandEvent& event);
        void OnListBoxAptRunwayDClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagleAirportLookupFrame)
        static const long ID_TEXTCTRL_AIRPORT_ID;
        static const long ID_BUTTON_LOOKUP_BY_STATE;
        static const long ID_STATICTEXT_AIRPORT;
        static const long ID_STATICTEXT_SEE_FAA_DOT_GOV;
        static const long ID_STATICTEXT_28_DAY_NASR;
        static const long ID_TEXTCTRL_ICAO_ID;
        static const long ID_STATICTEXT_ICAO_ID;
        static const long ID_TEXTCTRL_APT_NAME;
        static const long ID_TEXTCTRL_APT_CITY_STATE;
        static const long ID_TEXTCTRL_APT_ELEVATION;
        static const long ID_STATICTEXT_ELEVATION;
        static const long ID_STATICTEXT_TP_ALTITUDE;
        static const long ID_TEXTCTRL_TP_ALT;
        static const long ID_BUTTON_APT_INFORMATION;
        static const long ID_BUTTON_APT_FREQUENCIES;
        static const long ID_LISTBOX_APT_RUNWAY;
        static const long ID_STATICTEXT_RUNWAYS;
        static const long ID_CHECKBOX_DO_FULL_NASR;
        static const long ID_PANEL1;
        //*)

        //(*Declarations(OpenEagleAirportLookupFrame)
        wxButton* ButtonAptFrequencies;
        wxButton* ButtonAptInformation;
        wxButton* Button_LookupByState;
        wxCheckBox* CheckBox_DoFullNASR;
        wxDirDialog* DirDialogLookupAirport;
        wxListBox* ListBoxAptRunway;
        wxPanel* Panel1;
        wxStaticText* StaticTextAirport;
        wxStaticText* StaticTextRunways;
        wxStaticText* StaticText_22_Day_NASR;
        wxStaticText* StaticText_Elevation;
        wxStaticText* StaticText_ICAO_ID;
        wxStaticText* StaticText_Note_SeeFAA_Dot_Gov;
        wxStaticText* StaticText_TP_Altitude;
        wxTextCtrl* TextCtrlAirport_ID;
        wxTextCtrl* TextCtrl_AptCitySt;
        wxTextCtrl* TextCtrl_Apt_Elevation;
        wxTextCtrl* TextCtrl_Apt_Name;
        wxTextCtrl* TextCtrl_ICAO_ID;
        wxTextCtrl* TextCtrl_TP_Alt;
        //*)

        DECLARE_EVENT_TABLE()

        void OpenEagleBriefNASR(wxString airport_id);

        void OpenEagleFullNASR(wxString airport_id);

        /// NASR Airport records
        void OpenEagleAirportNASR(AirportFrame* frm);
        void OpenEagleAttendanceNASR(AirportFrame* frm);
        void OpenEagleArrestNASR(AirportFrame* frm);
        void OpenEagleRemarksNASR(AirportFrame* frm);
        void OpenEagleRunwayNASR(AirportFrame* frm);

        /// NASR Tower records
        void OpenEagleTowerNASR(AirportFrame* frm);
        void OpenEagleTwr1NASR(AirportFrame* frm);
        void OpenEagleTwr2NASR(AirportFrame* frm);
        void OpenEagleTwr3NASR(AirportFrame* frm);
        void OpenEagleTwr4NASR(AirportFrame* frm);
        void OpenEagleTwr5NASR(AirportFrame* frm);
        void OpenEagleTwr6NASR(AirportFrame* frm);
        void OpenEagleTwr7NASR(AirportFrame* frm);
        void OpenEagleTwr8NASR(AirportFrame* frm);
        void OpenEagleTwr9NASR(AirportFrame* frm);


        /// NASR Awos records
        void OpenEagleAwosNASR(AirportFrame* frm);
        void OpenEagleAwos1NASR(AirportFrame* frm);
        void OpenEagleAwos2NASR(AirportFrame* frm);

        /// NASR Ils records
        void OpenEagleIlsNASR(AirportFrame * frm);
        void OpenEagleIls1NASR(AirportFrame* frm);
        void OpenEagleIls2NASR(AirportFrame* frm);
        void OpenEagleIls3NASR(AirportFrame* frm);
        void OpenEagleIls4NASR(AirportFrame* frm);
        void OpenEagleIls5NASR(AirportFrame* frm);
        void OpenEagleIls6NASR(AirportFrame* frm);


};

#endif // OPENEAGLEAIRPORTLOOKUPMAIN_H
