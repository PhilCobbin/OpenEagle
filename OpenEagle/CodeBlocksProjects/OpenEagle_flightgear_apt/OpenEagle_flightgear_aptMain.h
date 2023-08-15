/***************************************************************
 * Name:      OpenEagle_flightgear_aptMain.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-07-12
 * Copyright: Philip Cobbin (www.cobbin.com)
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

#ifndef OPENEAGLE_FLIGHTGEAR_APTMAIN_H
#define OPENEAGLE_FLIGHTGEAR_APTMAIN_H

//(*Headers(OpenEagle_flightgear_aptFrame)
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

#include "../airport/airport.hxx"
class OpenEagle_flightgear_aptFrame: public wxFrame
{
    public:

        OpenEagle_flightgear_aptFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagle_flightgear_aptFrame();

        void read_NASR_apt_dat();
        void generate_flightgear_apt_dat();

        airport APT;
    private:

        //(*Handlers(OpenEagle_flightgear_aptFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton_NASR_apt_txtClick(wxCommandEvent& event);
        void OnButton_Select_flightgear_apt_pathClick(wxCommandEvent& event);
        void OnButton_generate_flightgear_apt_fileClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagle_flightgear_aptFrame)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL_NASR_APT_TXT;
        static const long ID_TEXTCTRL_FLIGHTGEAR_APT_PATH;
        static const long ID_BUTTON_NASR_APT_TXT;
        static const long ID_BUTTON_SELECT_FLIGHTGEAR_APT_PATH;
        static const long ID_BUTTON_GENERATE_FLIGHTHGEAR_APT_FILE;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OpenEagle_flightgear_aptFrame)
        wxButton* Button_NASR_apt_txt;
        wxButton* Button_Select_flightgear_apt_path;
        wxButton* Button_generate_flightgear_apt_file;
        wxDirDialog* DirDialog_select_path;
        wxFileDialog* FileDialog_select_file;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStatusBar* StatusBar_OpenEagle_flighgear_apt;
        wxTextCtrl* TextCtrl_NASR_apt_txt;
        wxTextCtrl* TextCtrl_flightgear_apt_path;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLE_FLIGHTGEAR_APTMAIN_H
