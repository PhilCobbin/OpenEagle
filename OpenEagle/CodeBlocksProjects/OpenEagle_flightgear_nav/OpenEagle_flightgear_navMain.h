/***************************************************************
 * Name:      OpenEagle_flightgear_navMain.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-07-11
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

#ifndef OPENEAGLE_FLIGHTGEAR_NAVMAIN_H
#define OPENEAGLE_FLIGHTGEAR_NAVMAIN_H

//(*Headers(OpenEagle_flightgear_navFrame)
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
class OpenEagle_flightgear_navFrame: public wxFrame
{
    public:

        OpenEagle_flightgear_navFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagle_flightgear_navFrame();

        void read_NASR_NAV_data();
        void generate_flightgear_NAV_data();

        airport APT;


    private:

        //(*Handlers(OpenEagle_flightgear_navFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton_NASR_nav_txtClick(wxCommandEvent& event);
        void OnButton_Select_flightgear_nav_pathClick(wxCommandEvent& event);
        void OnButton_Generate_flightgear_nav_fileClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagle_flightgear_navFrame)
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL_NASR_NAV_TXT;
        static const long ID_TEXTCTRL_FLIGHTGEAR_NAV_PATH;
        static const long ID_BUTTON_NASR_NAV_TXT;
        static const long ID_BUTTON_SELECT_FLIGHTGEAR_NAV_PATH;
        static const long ID_BUTTON_GENERATE_FLIGHTGEAR_NAV_FILE;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR_OpenEagle_flightgear_nav;
        //*)

        //(*Declarations(OpenEagle_flightgear_navFrame)
        wxButton* Button_Generate_flightgear_nav_file;
        wxButton* Button_NASR_nav_txt;
        wxButton* Button_Select_flightgear_nav_path;
        wxDirDialog* DirDialog_Select_Path;
        wxFileDialog* FileDialog_File_Select;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStatusBar* StatusBar_OpenEagle_flightgear_nav;
        wxTextCtrl* TextCtrl_NASR_nav_txt;
        wxTextCtrl* TextCtrl_flightgear_nav_path;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLE_FLIGHTGEAR_NAVMAIN_H
