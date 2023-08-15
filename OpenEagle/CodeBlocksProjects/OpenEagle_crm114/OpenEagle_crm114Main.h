/***************************************************************
 * Name:      OpenEagle_crm114Main.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2022-01-30
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

#ifndef OPENEAGLE_CRM114MAIN_H
#define OPENEAGLE_CRM114MAIN_H

//(*Headers(OpenEagle_crm114Frame)
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
class OpenEagle_crm114Frame: public wxFrame, data_mgr
{
    public:
        data_mgr crm114;
        OpenEagle_crm114Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagle_crm114Frame();


    private:

        //(*Handlers(OpenEagle_crm114Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonSelectClick(wxCommandEvent& event);
        void OnTextCtrlOpenEagleExtFileText(wxCommandEvent& event);
        void OnButtonSearchClick(wxCommandEvent& event);
        void OnButtonExtractClick(wxCommandEvent& event);
        void OnButtonFirstPrefixClick(wxCommandEvent& event);
        void OnButtonRealTimeEditClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagle_crm114Frame)
        static const long ID_STATICTEXT_OPEN_EAGLE_CRM114;
        static const long ID_STATICTEXT_EXTRACT_NOTE;
        static const long ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE;
        static const long ID_BUTTON_SELECT;
        static const long ID_BUTTON_Extract;
        static const long ID_TEXTCTRL_PATH;
        static const long ID_STATICTEXT_PATH;
        static const long ID_PANEL_CRM114;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OpenEagle_crm114Frame)
        wxButton* ButtonExtract;
        wxButton* ButtonSelect;
        wxFileDialog* FileDialogSelectFlightHistory;
        wxPanel* PanelCRM114;
        wxStaticText* StaticText1;
        wxStaticText* StaticTextPath;
        wxStaticText* StaticText_OpenEagleCRM114;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlOpenEagleExtFile;
        wxTextCtrl* TextCtrlPath;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLE_CRM114MAIN_H
