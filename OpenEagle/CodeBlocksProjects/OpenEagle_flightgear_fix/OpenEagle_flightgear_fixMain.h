/***************************************************************
 * Name:      OpenEagle_flightgear_fixMain.h
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

#ifndef OPENEAGLE_FLIGHTGEAR_FIXMAIN_H
#define OPENEAGLE_FLIGHTGEAR_FIXMAIN_H

//(*Headers(OpenEagle_flightgear_fixFrame)
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
class OpenEagle_flightgear_fixFrame: public wxFrame
{
    public:

        OpenEagle_flightgear_fixFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagle_flightgear_fixFrame();

        void read_NASR_fix_data();
        void generate_flightgear_fix_data();

        airport APT;

    private:

        //(*Handlers(OpenEagle_flightgear_fixFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton_NASR_fix_txtClick(wxCommandEvent& event);
        void OnButton_Select_flightgear_fix_pathClick(wxCommandEvent& event);
        void OnButton_Generate_flightgear_fix_fileClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagle_flightgear_fixFrame)
        static const long ID_STATICTEXT_OPENEAGLE_FLIGHTGEAR_FIX;
        static const long ID_TEXTCTRL_NASR_FIX_TXT;
        static const long ID_BUTTON_SELECT_NASR_FIX_TXT;
        static const long ID_STATICTEXT_NASR_FIX_TXT;
        static const long ID_STATICTEXT_FLIGHTGEAR_FIX_PATH;
        static const long ID_TEXTCTRL_FLIGHTGEAR_FIX_PATH;
        static const long ID_BUTTON_SELECT_FLIGHTGEAR_FIX_PATH;
        static const long ID_BUTTON_GENERATE_FLIGHTGEAR_FIX_FILE;
        static const long ID_PANEL_OPENEAGLE_FLIGHTGEAR_FIX;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR_OPEN_EAGLE_FLIGHTGEAR_STATUS_BAR;
        //*)

        //(*Declarations(OpenEagle_flightgear_fixFrame)
        wxButton* Button_Generate_flightgear_fix_file;
        wxButton* Button_NASR_fix_txt;
        wxButton* Button_Select_flightgear_fix_path;
        wxDirDialog* DirDialog_Select_Path;
        wxFileDialog* FileDialog_File_Select;
        wxPanel* Panel_OpenEagle_flightgear_fix;
        wxStaticText* StaticText_NASR_fix_txt;
        wxStaticText* StaticText_OpenEagle_flightgear_fix;
        wxStaticText* StaticText_flightgear_fix_path;
        wxStatusBar* StatusBar_OpenEagle_flightgear_fix;
        wxTextCtrl* TextCtrl_NASR_fix_txt;
        wxTextCtrl* TextCtrl_flightgear_fix_path;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLE_FLIGHTGEAR_FIXMAIN_H
