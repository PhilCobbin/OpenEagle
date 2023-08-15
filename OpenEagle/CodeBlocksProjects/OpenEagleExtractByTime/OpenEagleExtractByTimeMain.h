/***************************************************************
 * Name:      OpenEagleExtractByTimeMain.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-06-18
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

#ifndef OPENEAGLEEXTRACTBYTIMEMAIN_H
#define OPENEAGLEEXTRACTBYTIMEMAIN_H

//(*Headers(OpenEagleExtractByTimeFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)
#include "../data_mgr/data_mgr.hxx"
class OpenEagleExtractByTimeFrame: public wxFrame
{

    public:

      data_mgr DM;

      OpenEagleExtractByTimeFrame(wxWindow* parent,wxWindowID id = -1);
      virtual ~OpenEagleExtractByTimeFrame();


      double start_hr;
      double start_minute;
      double start_second;
      double end_hr;
      double end_minute;
      double end_second;
      bool change_first_prefix;
      double first_prefix;

      void set_parameters();

      data_mgr::OpenEagleExtData data;

      void read_data_to_decoded_DataList(FILE * fp);
      unsigned long int record_nbr;
      unsigned long int start_record_nbr;
      unsigned long int end_record_nbr;
      unsigned long find_time_record(double hour, double minute, double second);
      void writeExtractFile(FILE * fp);

      void ExtractByTimeRange();



    private:

        //(*Handlers(OpenEagleExtractByTimeFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButtonExtractClick(wxCommandEvent& event);
        void OnButtonSelectClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagleExtractByTimeFrame)
        static const long ID_STATICTEXT_OPEN_EAGLE_EXTRACT_BY_TIME;
        static const long ID_TEXTCTRL_OPEN_EAGLE_EXT_FILE;
        static const long ID_BUTTON_SELECT;
        static const long ID_STATICTEXT_Path;
        static const long ID_TEXTCTRL_PATH;
        static const long ID_BUTTON_EXTRACT;
        static const long ID_STATICTEXT_FROM;
        static const long ID_TEXTCTRL_FROM_HOUR;
        static const long ID_STATICTEXT_FROM_HOUR;
        static const long ID_TEXTCTRL_FROM_MINUTE;
        static const long ID_STATICTEXT_FROM_MINUTE;
        static const long ID_TEXTCTRL_FROM_SECOND;
        static const long ID_STATICTEXT_FROM_SECOND;
        static const long ID_STATICTEXT_TO;
        static const long ID_TEXTCTRL_TO_HOUR;
        static const long ID_TEXTCTRL_TO_MINUTE;
        static const long ID_TEXTCTRL_TO_SECOND;
        static const long ID_STATICTEXT_TO_HOUR;
        static const long ID_STATICTEXT_TO_MINUTE;
        static const long ID_STATICTEXT_TO_SECOND;
        static const long ID_CHECKBOX_SET_PREFIX_1;
        static const long ID_STATICTEXT_CRM114_PREFIX;
        static const long ID_TEXTCTRL_PREFIX_1;
        static const long ID_PANEL_EXTRACT_BY_TIME;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OpenEagleExtractByTimeFrame)
        wxButton* ButtonExtract;
        wxButton* ButtonSelect;
        wxCheckBox* CheckBoxSetPrefix1;
        wxFileDialog* FileDialogSelectFlightHistory;
        wxPanel* PanelExtractByTime;
        wxStaticText* StaticTextCRM114Prefix;
        wxStaticText* StaticTextFrom;
        wxStaticText* StaticTextFromHour;
        wxStaticText* StaticTextFromMinute;
        wxStaticText* StaticTextFromSecond;
        wxStaticText* StaticTextOpenEagleExtractByTime;
        wxStaticText* StaticTextPath;
        wxStaticText* StaticTextTo;
        wxStaticText* StaticTextToHour;
        wxStaticText* StaticTextToMinute;
        wxStaticText* StaticTextToSecond;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlFromHour;
        wxTextCtrl* TextCtrlFromMinute;
        wxTextCtrl* TextCtrlFromSecond;
        wxTextCtrl* TextCtrlOpenEagleExtFile;
        wxTextCtrl* TextCtrlPath;
        wxTextCtrl* TextCtrlPrefix1;
        wxTextCtrl* TextCtrlToHour;
        wxTextCtrl* TextCtrlToMinute;
        wxTextCtrl* TextCtrlToSecond;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLEEXTRACTBYTIMEMAIN_H
