/***************************************************************
 * Name:      OpenEagleProcessShapefilesMain.h
 * Purpose:   Defines Application Frame
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2022-07-02
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

#ifndef OPENEAGLEPROCESSSHAPEFILESMAIN_H
#define OPENEAGLEPROCESSSHAPEFILESMAIN_H

//(*Headers(OpenEagleProcessShapefilesFrame)
#include <wx/button.h>
#include <wx/dirdlg.h>
#include <wx/filedlg.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
//*)

#include "../OpenEaglePaths/OpenEaglePaths.hxx"
#include "../airport/airport.hxx"
#include "../Class_Airspace/class_airspace.hxx"
#include "../Airspace_Boundary/airspace_boundary.hxx"
#include "../U_S_Special_Use_Airspace/sua_airspace.hxx"
class OpenEagleProcessShapefilesFrame: public wxFrame
{

// update file structure:
// /Scenery
// /Scenery/Models
// /Scenery/Models/Airports     Subdirectories by state  i.e. /AZ/FLG/  with airport.ac airport.png airport.xml  SIGNAGE
// /Scenery/Models/Airspace/CLASS_B
// /Scenery/Models/Airspace/CLASS_C
// /Scenery/Models/Airspace/CLASS_D/FLG/ with CLASS_D.png shape segment .ac and .xml files for CLASS D fence boundary
// /Scenery/Models/Boundary_Airspace     SFRA, SPECIAL_USE_RULES  boundary segment .png, .ac and xml boundary files.
// /Scenery/Models/Special_Use_Airspace  MOA's et al
// /Scenery/Models/Special_Use_Airspace/A
// /Scenery/Models/Special_Use_Airspace/ADA
// /Scenery/Models/Special_Use_Airspace/MOA/ABLE_BRAVO_MOA/ .PNG .ac and .xml boundary files
// /Scenery/Models/Special_Use_Airspace/P
// /Scenery/Models/Special_Use_Airspace/R
// /Scenery/Models/Special_Use_Airspace/w
// /Scenery/Objects
// /Scenery/Terrain

    public:
        OpenEaglePaths paths;
      ///  airport apt;
   //     airspace_boundary boundary_airspace;
  //      sua_airspace Sua_airspace;
        OpenEagleProcessShapefilesFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~OpenEagleProcessShapefilesFrame();

    private:

        //(*Handlers(OpenEagleProcessShapefilesFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButtonLookupClassAirspaceClick(wxCommandEvent& event);
        void OnButtonLookupBoundaryAirspacePathClick(wxCommandEvent& event);
        void OnButtonLookupSpecialUseAirspacePathClick(wxCommandEvent& event);
        void OnButtonLookupModelsAndObjectsPathClick(wxCommandEvent& event);
        void OnButtonWriteModelsAndObjectsForFlightgearClick(wxCommandEvent& event);
        void OnButtonLookupAptPathClick(wxCommandEvent& event);
        void OnButtonProcessAptSignsClick(wxCommandEvent& event);
        void OnButtonProcessClassAirspaceClick(wxCommandEvent& event);
        void OnButtonProcessBoundaryAirspaceClick(wxCommandEvent& event);
        void OnButtonProcessSpecialUseAirspaceClick(wxCommandEvent& event);
        void OnButtonLookupUpdateProgramsPathClick(wxCommandEvent& event);
        void OnTextCtrlClassAirspacePathText(wxCommandEvent& event);
        void OnButtonLookupClassProgramClick(wxCommandEvent& event);
        void OnTextCtrlBoundaryAirspacePathText(wxCommandEvent& event);
        void OnButton_program_OpenEagleSataClick(wxCommandEvent& event);
        void OnButton_lookup_special_use_filenameClick(wxCommandEvent& event);
        void OnButton_lookup_OpenEagleAirportSignsClick(wxCommandEvent& event);
        void OnTextCtrl_models_and_objects_pathText(wxCommandEvent& event);
        void OnButtonLookupNASR_APT_txtClick(wxCommandEvent& event);
        void OnButton_lookup_airspace_texturesClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(OpenEagleProcessShapefilesFrame)
        static const long ID_TEXTCTRL_AIRPORT_FILENAME;
        static const long ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_FILENAME;
        static const long ID_TEXTCTRL_APT_TXT;
        static const long ID_TEXTCTRL_SPECIAL_USE_AIRSPACE_PATH;
        static const long ID_TEXTCTRL_BOUNDARY_AIRSPACE_PATH;
        static const long ID_STATICTEXT_CLASS_AIRSPACE_PATH;
        static const long ID_BUTTON_LOOKUP_CLASS_AIRSPACE;
        static const long ID_STATICTEXT_BOUNDARY_AIRSPACE_PATH;
        static const long ID_BUTTON_LOOKUP_BOUNDARY_AIRSPACE_PATH;
        static const long ID_STATICTEXT_SPECIAL_USE_AIRSPACE_PATH;
        static const long ID_BUTTON_LOOKUP_SPECIAL_USE_AIRSPACE_PATH;
        static const long ID_STATICTEXT_SPECIAL_USE_AIRSPACE_FILENAME;
        static const long ID_STATICTEXT_PATH_TO_MODELS_AND_OBJECTS;
        static const long ID_BUTTON_LOOKUP_MODELS_AND_OBJECTS_PATH;
        static const long ID_BUTTON_PROCESS_CLASS_AIRSPACE;
        static const long ID_BUTTON_PROCESS_BOUNDARY_AIRSPACE;
        static const long ID_BUTTON_PROCESS_SPECIAL_USE_AIRSPACE;
        static const long ID_STATICTEXT_AIRPORT_PATH;
        static const long ID_BUTTON_LOOKUP_APT_PATH;
        static const long ID_BUTTON_PROCESS_APT_SIGNS;
        static const long ID_STATICTEXT_AIRPORT_FILENAME;
        static const long ID_TEXTCTRL_NASR_APT_TXT;
        static const long ID_STATICTEXT_PROGRAM_OPENEAGLE_CLASS_AIRSPACE;
        static const long ID_TEXTCTRL_ClassAirspacePath;
        static const long ID_BUTTON_NASR_APT_TXT;
        static const long ID_STATICLINE1;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICLINE2;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_BUTTON_LOOKUP_SPECIAL_USE_FILENAME;
        static const long ID_STATICLINE3;
        static const long ID_STATICLINE4;
        static const long ID_BUTTON_LOOKUP_OPENEAGLEAIRPORTSIGNS;
        static const long ID_STATICLINE5;
        static const long ID_STATICTEXT7;
        static const long TextCtrlModelsAndObjectsPath;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(OpenEagleProcessShapefilesFrame)
        wxButton* ButtonLookupAptPath;
        wxButton* ButtonLookupBoundaryAirspacePath;
        wxButton* ButtonLookupClassAirspace;
        wxButton* ButtonLookupModelsAndObjectsPath;
        wxButton* ButtonLookupNASR_APT_txt;
        wxButton* ButtonLookupSpecialUseAirspacePath;
        wxButton* ButtonProcessAptSigns;
        wxButton* ButtonProcessBoundaryAirspace;
        wxButton* ButtonProcessClassAirspace;
        wxButton* ButtonProcessSpecialUseAirspace;
        wxButton* Button_lookup_OpenEagleAirportSigns;
        wxButton* Button_lookup_special_use_filename;
        wxDirDialog* DirDialogSelectDirectory;
        wxFileDialog* FileDialogSelectFile;
        wxPanel* Panel1;
        wxStaticLine* StaticLine1;
        wxStaticLine* StaticLine2;
        wxStaticLine* StaticLine3;
        wxStaticLine* StaticLine4;
        wxStaticLine* StaticLine5;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticTextAirportFilename;
        wxStaticText* StaticTextAirportPath;
        wxStaticText* StaticTextBoundaryAirspacePath;
        wxStaticText* StaticTextClassAirspacePath;
        wxStaticText* StaticTextPathToModelsAndObjects;
        wxStaticText* StaticTextSpecialUseAirspaceFilename;
        wxStaticText* StaticTextSpecialUseAirspacePath;
        wxStaticText* StaticText_program_OpenEagle_class_airspace;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrlAirportFilename;
        wxTextCtrl* TextCtrlBoundaryAirspacePath;
        wxTextCtrl* TextCtrlClassAirspacePath;
        wxTextCtrl* TextCtrlSpecialUseAirspaceFilename;
        wxTextCtrl* TextCtrlSpecialUseAirspacePath;
        wxTextCtrl* TextCtrl_APT_TXT;
        wxTextCtrl* TextCtrl_NASR_APT_txt;
        wxTextCtrl* TextCtrl_models_and_objects_path;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // OPENEAGLEPROCESSSHAPEFILESMAIN_H
