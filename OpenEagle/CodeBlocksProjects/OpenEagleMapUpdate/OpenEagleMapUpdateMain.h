/***************************************************************
 * Name:      OpenEagleMapUpdateMain.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-18
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

#ifndef OPENEAGLEMAPUPDATEMAIN_H
#define OPENEAGLEMAPUPDATEMAIN_H

//(*Headers(OpenEagleMapUpdateFrame)
#include <wx/button.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/msgdlg.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

#include "../maps/maps.hxx"

class OpenEagleMapUpdateFrame: public wxFrame
{
    public:
        maps update_map;
        OpenEagleMapUpdateFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagleMapUpdateFrame();


    private:

        //(*Handlers(OpenEagleMapUpdateFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonSelectClick(wxCommandEvent& event);
        void OnButton_GENERATE_NEW_MAPClick(wxCommandEvent& event);
        void OnButtonSelectSectionalsZipClick(wxCommandEvent& event);
        void OnButtonSelectGrandCanyonZipClick(wxCommandEvent& event);
        void OnButtonHelpClick(wxCommandEvent& event);
        void OnButtonBulkHelpClick(wxCommandEvent& event);
        void OnButtonBulkGenerateMapsClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagleMapUpdateFrame)
        static const long ID_STATIC_TEXT_SELECT_TIF;
        static const long ID_TEXTCTRL_TIF_FILE;
        static const long ID_BUTTON_SELECT;
        static const long ID_BUTTON_HELP;
        static const long ID_BUTTON_GENERATE;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL_SECTIONALS_ZIP;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRL_GRAND_CANYON_ZIP;
        static const long ID_BUTTON_SELECT_SECTIONALS_ZIP;
        static const long ID_BUTTON_SELECT_GRAND_CANYON_ZIP;
        static const long ID_BUTTON_BULK_GENERATE_MAPS;
        static const long ID_BUTTON_BULK_HELP;
        static const long ID_PANELOpenEagleMapUpdate;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR_OPEN_EAGLE_MAP_UPDATE;
        static const long ID_MESSAGEDIALOGHelpTifUpdate;
        static const long ID_MESSAGEDIALOG_HELP_UPDATE_BULK;
        //*)

        //(*Declarations(OpenEagleMapUpdateFrame)
        wxButton* ButtonBulkGenerateMaps;
        wxButton* ButtonBulkHelp;
        wxButton* ButtonHelp;
        wxButton* ButtonSelect;
        wxButton* ButtonSelectGrandCanyonZip;
        wxButton* ButtonSelectSectionalsZip;
        wxButton* Button_GENERATE_NEW_MAP;
        wxFileDialog* FileDialogZipFiles;
        wxFileDialog* FileDialog_FILE_SELECT;
        wxMessageDialog* MessageDialogHelpTifUpdate;
        wxMessageDialog* MessageDialogHelpUpdateAllMaps;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticTextSelectTiff;
        wxStatusBar* StatusBarOpenEagleMapUpdate;
        wxTextCtrl* TextCtrlGrandCanyonZip;
        wxTextCtrl* TextCtrlSectionalsZip;
        wxTextCtrl* TextCtrlTifFile;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLEMAPUPDATEMAIN_H
