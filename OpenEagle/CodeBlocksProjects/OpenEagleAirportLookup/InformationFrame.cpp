/***************************************************************
 * Name:      InformationFrame.cpp
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

#include "InformationFrame.h"

//(*InternalHeaders(InformationFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(InformationFrame)
const long InformationFrame::ID_TEXTCTRL_BODY = wxNewId();
const long InformationFrame::ID_PANEL_INFORMATION = wxNewId();
//*)

BEGIN_EVENT_TABLE(InformationFrame,wxFrame)
	//(*EventTable(InformationFrame)
	//*)
END_EVENT_TABLE()

InformationFrame::InformationFrame(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(InformationFrame)
	Create(parent, id, _("Information"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
	SetClientSize(wxSize(700,700));
	Move(wxDefaultPosition);
	wxFont thisFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	PanelInformation = new wxPanel(this, ID_PANEL_INFORMATION, wxPoint(112,104), wxSize(700,700), wxTAB_TRAVERSAL, _T("ID_PANEL_INFORMATION"));
	TextCtrlBody = new wxTextCtrl(PanelInformation, ID_TEXTCTRL_BODY, wxEmptyString, wxPoint(10,10), wxSize(680,680), wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL_BODY"));
	wxFont TextCtrlBodyFont(20,wxFONTFAMILY_TELETYPE,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Miriam Mono CLM"),wxFONTENCODING_DEFAULT);
	TextCtrlBody->SetFont(TextCtrlBodyFont);
	Center();
	//*)
}

InformationFrame::~InformationFrame()
{
	//(*Destroy(InformationFrame)
	//*)
}

