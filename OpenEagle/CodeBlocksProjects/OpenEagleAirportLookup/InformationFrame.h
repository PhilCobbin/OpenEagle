/***************************************************************
 * Name:      InformationFrame.h
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
#ifndef INFORMATIONFRAME_H
#define INFORMATIONFRAME_H

//(*Headers(InformationFrame)
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
//*)
#include "../airport/airport.hxx"
class InformationFrame: public wxFrame ,airport
{
	public:

		InformationFrame(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~InformationFrame();

		//(*Declarations(InformationFrame)
		wxPanel* PanelInformation;
		wxTextCtrl* TextCtrlBody;
		//*)

	protected:

		//(*Identifiers(InformationFrame)
		static const long ID_TEXTCTRL_BODY;
		static const long ID_PANEL_INFORMATION;
		//*)

	private:

		//(*Handlers(InformationFrame)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
