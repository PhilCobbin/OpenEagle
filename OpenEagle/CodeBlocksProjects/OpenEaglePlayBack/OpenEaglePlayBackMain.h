/***************************************************************
 * Name:      OpenEaglePlayBackMain.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-06-20
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

#ifndef OPENEAGLEPLAYBACKMAIN_H
#define OPENEAGLEPLAYBACKMAIN_H

//(*Headers(OpenEaglePlayBackFrame)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
#include "../data_mgr/data_mgr.hxx"
class OpenEaglePlayBackFrame: public wxFrame
{
    public:
        data_mgr Playback;;
        OpenEaglePlayBackFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEaglePlayBackFrame();

    private:

        //(*Handlers(OpenEaglePlayBackFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButtonSelectClick(wxCommandEvent& event);
        void OnButtonPlayBackClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEaglePlayBackFrame)
        static const long ID_STATICTEXT_OPEN_EAGLE_PLAY_BACK;
        static const long ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE;
        static const long ID_BUTTON_SELECT;
        static const long ID_STATICTEXT_PATH;
        static const long ID_TEXTCTRL_PATH;
        static const long ID_BUTTON_PLAY_BACK;
        static const long ID_CHOICE_SPEED;
        static const long ID_STATICTEXT_SPEED;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OpenEaglePlayBackFrame)
        wxButton* ButtonPlayBack;
        wxButton* ButtonSelect;
        wxChoice* ChoiceSpeed;
        wxFileDialog* FileDialogSelectFlightHistory;
        wxPanel* PanelOpenEaglePlayBack;
        wxStaticText* StaticTextOpenEaglePlayBack;
        wxStaticText* StaticTextPath;
        wxStaticText* StaticTextSpeed;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlOpenEagleExtFile;
        wxTextCtrl* TextCtrlPath;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLEPLAYBACKMAIN_H
