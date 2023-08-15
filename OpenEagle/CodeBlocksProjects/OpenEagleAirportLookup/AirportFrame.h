/***************************************************************
 * Name:      AirportFrame.h
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
#ifndef AIRPORTFRAME_H
#define AIRPORTFRAME_H

//(*Headers(AirportFrame)
#include <wx/frame.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
//*)
#include "../airport/airport.hxx"
class AirportFrame: public wxFrame
{
	public:

		AirportFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~AirportFrame();

		//(*Declarations(AirportFrame)
		wxNotebook* Notebook_Airport;
		wxPanel* PanelArrSys;
		wxPanel* PanelMarkerBeacon;
		wxPanel* PanelRemarks;
		wxPanel* PanelTower;
		wxPanel* Panel_ATIS;
		wxPanel* Panel_AWOS;
		wxPanel* Panel_Airport;
		wxPanel* Panel_AirportFrame;
		wxPanel* Panel_Att;
		wxPanel* Panel_Class_BCDE;
		wxPanel* Panel_DME;
		wxPanel* Panel_Frequencies;
		wxPanel* Panel_GlideSlope;
		wxPanel* Panel_Hours;
		wxPanel* Panel_ILS;
		wxPanel* Panel_ILS_Remarks;
		wxPanel* Panel_Localizer;
		wxPanel* Panel_Radar;
		wxPanel* Panel_Remarks;
		wxPanel* Panel_Rwy;
		wxPanel* Panel_Satellite;
		wxPanel* Panel_Services;
		wxTextCtrl* TextCtrlRemarks;
		wxTextCtrl* TextCtrlSatellite;
		wxTextCtrl* TextCtrlTower;
		wxTextCtrl* TextCtrl_ATIS;
		wxTextCtrl* TextCtrl_AWOS;
		wxTextCtrl* TextCtrl_Airport;
		wxTextCtrl* TextCtrl_ArrestingSystems;
		wxTextCtrl* TextCtrl_Attendance;
		wxTextCtrl* TextCtrl_Class_BCDE;
		wxTextCtrl* TextCtrl_DME;
		wxTextCtrl* TextCtrl_Frequencies;
		wxTextCtrl* TextCtrl_GlideSlope;
		wxTextCtrl* TextCtrl_Hours;
		wxTextCtrl* TextCtrl_ILS;
		wxTextCtrl* TextCtrl_ILS_Remarks;
		wxTextCtrl* TextCtrl_Localizer;
		wxTextCtrl* TextCtrl_MarkerBeacon;
		wxTextCtrl* TextCtrl_Radar;
		wxTextCtrl* TextCtrl_Remarks;
		wxTextCtrl* TextCtrl_Runway;
		wxTextCtrl* TextCtrl_Services;
		//*)

	protected:

		//(*Identifiers(AirportFrame)
		static const long ID_TEXTCTRL_AIRPORT;
		static const long ID_PANEL_AIRPORT;
		static const long ID_TEXTCTRL_ATTENDENCE;
		static const long ID_PANEL_ATT;
		static const long ID_TEXTCTRL_RUNWAY;
		static const long ID_PANEL_RWY;
		static const long ID_TEXTCTRL_ARRESTING_SYSTEMS;
		static const long ID_PANEL_ArrSys;
		static const long ID_TEXTCTRL_REMARKS;
		static const long ID_PANEL_Remarks;
		static const long ID_TEXTCTRL_TOWER;
		static const long ID_PANEL_TOWER;
		static const long ID_TEXTCTRL_HOURS;
		static const long ID_PANEL_HOURS;
		static const long ID_TEXTCTRL_FREQUENCIES;
		static const long ID_PANEL_FREQUENCIES;
		static const long ID_TEXTCTRL_SERVICES;
		static const long ID_PANEL_SERVICES;
		static const long ID_TEXTCTRL_RADAR;
		static const long ID_PANEL_RADAR;
		static const long ID_TEXTCTRL_TWR_REMARKS;
		static const long ID_PANEL_REMARKS;
		static const long ID_TEXTCTRL_SATELLITE;
		static const long ID_PANEL_SATELLITE;
		static const long ID_TEXTCTRL_CLASS_BCDE;
		static const long ID_PANEL_CLASS_BCDE;
		static const long ID_TEXTCTRL_ATIS;
		static const long ID_PANEL_ATIS;
		static const long ID_TEXTCTRL_AWOS;
		static const long ID_PANEL_AWOS;
		static const long ID_TEXTCTRL_ILS;
		static const long ID_PANEL_ILS;
		static const long ID_TEXTCTRL_LOCALIZER;
		static const long ID_PANEL_LOCALIZER;
		static const long ID_TEXTCTRL_GLIDE_SLOPE;
		static const long ID_PANEL_GLIDE_SLOPE;
		static const long ID_TEXTCTRL_DME;
		static const long ID_PANEL_DMD;
		static const long ID_TEXTCTRL_MARKER_BEACON;
		static const long ID_PANEL_MARKER_BEACON;
		static const long ID_TEXTCTRL_ILS_REMARKS;
		static const long ID_PANEL_ILS_REMARKS;
		static const long ID_NOTEBOOK_AIRPORT;
		static const long ID_PANEL_AIRPORT_FRAME;
		//*)

	private:

		//(*Handlers(AirportFrame)
		void OnNotebook_AirportPageChanged(wxNotebookEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
