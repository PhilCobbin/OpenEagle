/***************************************************************
 * Name:      OpenEagleMapUpdateMain.cpp
 * Purpose:   Code for Application Frame
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

#include "OpenEagleMapUpdateMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(OpenEagleMapUpdateFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(OpenEagleMapUpdateFrame)
const long OpenEagleMapUpdateFrame::ID_STATIC_TEXT_SELECT_TIF = wxNewId();
const long OpenEagleMapUpdateFrame::ID_TEXTCTRL_TIF_FILE = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_SELECT = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_HELP = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_GENERATE = wxNewId();
const long OpenEagleMapUpdateFrame::ID_STATICTEXT1 = wxNewId();
const long OpenEagleMapUpdateFrame::ID_TEXTCTRL_SECTIONALS_ZIP = wxNewId();
const long OpenEagleMapUpdateFrame::ID_STATICTEXT2 = wxNewId();
const long OpenEagleMapUpdateFrame::ID_TEXTCTRL_GRAND_CANYON_ZIP = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_SELECT_SECTIONALS_ZIP = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_SELECT_GRAND_CANYON_ZIP = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_BULK_GENERATE_MAPS = wxNewId();
const long OpenEagleMapUpdateFrame::ID_BUTTON_BULK_HELP = wxNewId();
const long OpenEagleMapUpdateFrame::ID_PANELOpenEagleMapUpdate = wxNewId();
const long OpenEagleMapUpdateFrame::idMenuQuit = wxNewId();
const long OpenEagleMapUpdateFrame::idMenuAbout = wxNewId();
const long OpenEagleMapUpdateFrame::ID_STATUSBAR_OPEN_EAGLE_MAP_UPDATE = wxNewId();
const long OpenEagleMapUpdateFrame::ID_MESSAGEDIALOGHelpTifUpdate = wxNewId();
const long OpenEagleMapUpdateFrame::ID_MESSAGEDIALOG_HELP_UPDATE_BULK = wxNewId();
//*)

BEGIN_EVENT_TABLE(OpenEagleMapUpdateFrame,wxFrame)
    //(*EventTable(OpenEagleMapUpdateFrame)
    //*)
END_EVENT_TABLE()

OpenEagleMapUpdateFrame::OpenEagleMapUpdateFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(OpenEagleMapUpdateFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBarOpenEagleMapUpdate;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, _("OpenEagleUpdateMap"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(1152,354));
    Panel1 = new wxPanel(this, ID_PANELOpenEagleMapUpdate, wxPoint(120,64), wxSize(1048,450), wxTAB_TRAVERSAL, _T("ID_PANELOpenEagleMapUpdate"));
    StaticTextSelectTiff = new wxStaticText(Panel1, ID_STATIC_TEXT_SELECT_TIF, _("Select Tif File to update Map"), wxPoint(10,40), wxDefaultSize, 0, _T("ID_STATIC_TEXT_SELECT_TIF"));
    TextCtrlTifFile = new wxTextCtrl(Panel1, ID_TEXTCTRL_TIF_FILE, wxEmptyString, wxPoint(208,40), wxSize(712,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL_TIF_FILE"));
    ButtonSelect = new wxButton(Panel1, ID_BUTTON_SELECT, _("Select"), wxPoint(936,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SELECT"));
    ButtonHelp = new wxButton(Panel1, ID_BUTTON_HELP, _("Help"), wxPoint(1032,40), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_HELP"));
    Button_GENERATE_NEW_MAP = new wxButton(Panel1, ID_BUTTON_GENERATE, _("Generate New Map"), wxPoint(496,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_GENERATE"));
    Button_GENERATE_NEW_MAP->Disable();
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Select Sectionals.zip for bulk processing"), wxPoint(10,136), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    TextCtrlSectionalsZip = new wxTextCtrl(Panel1, ID_TEXTCTRL_SECTIONALS_ZIP, wxEmptyString, wxPoint(312,130), wxSize(624,34), 0, wxDefaultValidator, _T("ID_TEXTCTRL_SECTIONALS_ZIP"));
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Select GrandCanyon.zip for bulk processing"), wxPoint(10,192), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    TextCtrlGrandCanyonZip = new wxTextCtrl(Panel1, ID_TEXTCTRL_GRAND_CANYON_ZIP, wxEmptyString, wxPoint(312,190), wxSize(624,34), 0, wxDefaultValidator, _T("ID_TEXTCTRL_GRAND_CANYON_ZIP"));
    ButtonSelectSectionalsZip = new wxButton(Panel1, ID_BUTTON_SELECT_SECTIONALS_ZIP, _("Select"), wxPoint(952,130), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SELECT_SECTIONALS_ZIP"));
    ButtonSelectGrandCanyonZip = new wxButton(Panel1, ID_BUTTON_SELECT_GRAND_CANYON_ZIP, _("Select"), wxPoint(952,190), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SELECT_GRAND_CANYON_ZIP"));
    ButtonBulkGenerateMaps = new wxButton(Panel1, ID_BUTTON_BULK_GENERATE_MAPS, _("Generate Sectionals and Grand Canyon from zip files"), wxPoint(408,248), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_BULK_GENERATE_MAPS"));
    ButtonBulkGenerateMaps->Disable();
    ButtonBulkHelp = new wxButton(Panel1, ID_BUTTON_BULK_HELP, _("Help"), wxPoint(1048,160), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_BULK_HELP"));
    MenuBarOpenEagleMapUpdate = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBarOpenEagleMapUpdate->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBarOpenEagleMapUpdate->Append(Menu2, _("Help"));
    SetMenuBar(MenuBarOpenEagleMapUpdate);
    StatusBarOpenEagleMapUpdate = new wxStatusBar(this, ID_STATUSBAR_OPEN_EAGLE_MAP_UPDATE, 0, _T("ID_STATUSBAR_OPEN_EAGLE_MAP_UPDATE"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBarOpenEagleMapUpdate->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBarOpenEagleMapUpdate->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBarOpenEagleMapUpdate);
    FileDialog_FILE_SELECT = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("*.tif"), wxFD_DEFAULT_STYLE|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    FileDialogZipFiles = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("*.zip"), wxFD_DEFAULT_STYLE|wxFD_FILE_MUST_EXIST, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));
    MessageDialogHelpTifUpdate = new wxMessageDialog(this, wxEmptyString, _("Help on Generating Map from a single Tif file"), wxOK, wxDefaultPosition);
    MessageDialogHelpUpdateAllMaps = new wxMessageDialog(this, wxEmptyString, _("Help on updating full set of maps in bulk"), wxOK|wxCANCEL, wxDefaultPosition);
    Center();

    Connect(ID_BUTTON_SELECT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButtonSelectClick);
    Connect(ID_BUTTON_HELP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButtonHelpClick);
    Connect(ID_BUTTON_GENERATE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButton_GENERATE_NEW_MAPClick);
    Connect(ID_BUTTON_SELECT_SECTIONALS_ZIP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButtonSelectSectionalsZipClick);
    Connect(ID_BUTTON_SELECT_GRAND_CANYON_ZIP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButtonSelectGrandCanyonZipClick);
    Connect(ID_BUTTON_BULK_GENERATE_MAPS,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButtonBulkGenerateMapsClick);
    Connect(ID_BUTTON_BULK_HELP,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnButtonBulkHelpClick);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&OpenEagleMapUpdateFrame::OnAbout);
    //*)
  //  init_tif_list();
}
/**
void OpenEagleMapUpdateFrame::init_tif_list()
{
  maps[0].tif_file = "Albuquerque SEC.tif";
  maps[ 0].tif_file ="Albuquerque SEC.tif";
  maps[ 1].tif_file ="Anchorage SEC.tif";
  maps[ 2].tif_file ="Atlanta SEC.tif";
  maps[ 3].tif_file ="Bethel SEC.tif";
  maps[ 4].tif_file ="Billings SEC.tif";
  maps[ 5].tif_file ="Brownsville SEC.tif";
  maps[ 6].tif_file ="Cape Lisburne SEC.tif";
  maps[ 7].tif_file ="Charlotte SEC.tif";
  maps[ 8].tif_file ="Cheyenne SEC.tif";
  maps[ 9].tif_file ="Chicago SEC.tif";
  maps[10].tif_file ="Cincinnati SEC.tif";
  maps[11].tif_file ="Cold Bay SEC.tif";
  maps[12].tif_file ="Dallas-Ft Worth SEC.tif";
  maps[13].tif_file ="Dawson SEC.tif";
  maps[14].tif_file ="Denver SEC.tif";
  maps[15].tif_file ="Detroit SEC.tif";
  maps[16].tif_file ="Dutch Harbor SEC.tif";
  maps[17].tif_file ="El Paso SEC.tif";
  maps[18].tif_file ="Fairbanks SEC.tif";
  maps[19].tif_file ="Grand Canyon Air Tour Operators.tif";
  maps[20].tif_file ="Grand Canyon General Aviation.tif";
  maps[21].tif_file ="Great Falls SEC.tif";
  maps[22].tif_file ="Green Bay SEC.tif";
  maps[23].tif_file ="Halifax SEC.tif";
  maps[24].tif_file ="Hawaiian Islands SEC.tif";
  maps[25].tif_file ="Honolulu Inset SEC.tif";
  maps[26].tif_file ="Houston SEC.tif";
  maps[27].tif_file ="Jacksonville SEC.tif";
  maps[28].tif_file ="Juneau SEC.tif";
  maps[29].tif_file ="Kansas City SEC.tif";
  maps[30].tif_file ="Ketchikan SEC.tif";
  maps[31].tif_file ="Klamath Falls SEC.tif";
  maps[32].tif_file ="Kodiak SEC.tif";
  maps[33].tif_file ="Lake Huron SEC.tif";
  maps[34].tif_file ="Las Vegas SEC.tif";
  maps[35].tif_file ="Los Angeles SEC.tif";
  maps[36].tif_file ="Mariana Islands Inset SEC.tif";
  maps[37].tif_file ="McGrath SEC.tif";
  maps[38].tif_file ="Memphis SEC.tif";
  maps[39].tif_file ="Miami SEC.tif";
  maps[40].tif_file ="Montreal SEC.tif";
  maps[41].tif_file ="New Orleans SEC.tif";
  maps[42].tif_file ="New York SEC.tif";
  maps[43].tif_file ="Nome SEC.tif";
  maps[44].tif_file ="Omaha SEC.tif";
  maps[45].tif_file ="Phoenix SEC.tif";
  maps[46].tif_file ="Point Barrow SEC.tif";
  maps[47].tif_file ="Salt Lake City SEC.tif";
  maps[48].tif_file ="Samoan Islands Inset SEC.tif";
  maps[49].tif_file ="San Antonio SEC.tif";
  maps[50].tif_file ="San Francisco SEC.tif";
  maps[51].tif_file ="Seattle SEC.tif";
  maps[52].tif_file ="Seward SEC.tif";
  maps[53].tif_file ="St Louis SEC.tif";
  maps[54].tif_file ="Twin Cities SEC.tif";
  maps[55].tif_file ="Washington SEC.tif";
  maps[56].tif_file ="Western Aleutian Islands East SEC.tif";
  maps[57].tif_file ="Western Aleutian Islands West SEC.tif";
  maps[58].tif_file ="Wichita SEC.tif";

  maps[ 0].map_dir="Albuquerque_Sectional";                     maps[ 0].map_ext="'-110.436260932,-101.552246553,31.217888105,36.571239668 [EPSG:4326]'";
  maps[ 1].map_dir="Anchorage_Sectional";                       maps[ 1].map_ext="'-154.201534387,-138.983410740,57.273851253,66.444026190 [EPSG:4326]'";
  maps[ 2].map_dir="Atlanta_Sectional";                         maps[ 2].map_ext="'-89.456950464,-80.533427545,31.530872591,36.908031308 [EPSG:4326]'";
  maps[ 3].map_dir="Bethel_Sectional";                          maps[ 3].map_ext="'-175.162053631,-159.953074081,57.303924640,66.468589506 [EPSG:4326]'";
  maps[ 4].map_dir="Billings_Sectional";                        maps[ 4].map_ext="'-110.846549822,-100.009085508,43.430176657,49.960642958 [EPSG:4326]'";
  maps[ 5].map_dir="Brownsville_Sectional";                     maps[ 5].map_ext="'-104.309481166,-96.017751625,23.397420685,28.393871771 [EPSG:4326]'";
  maps[ 6].map_dir="Cape_Lisburne_Sectional";                   maps[ 6].map_ext="'-175.886244034,-154.418956963,63.385583287,76.321394721 [EPSG:4326]'";
  maps[ 7].map_dir="Charlotte_Sectional";                       maps[ 7].map_ext="'-83.014210663,-74.664076094,31.379893632,36.411538566 [EPSG:4326]'";
  maps[ 8].map_dir="Cheyenne_Sectional";                        maps[ 8].map_ext="'-110.412189803,-100.378593545,39.177464971,45.223534452 [EPSG:4326]'";
  maps[ 9].map_dir="Chicago_Sectional";                         maps[ 9].map_ext="'-94.417548626,-84.379640362,39.155678348,45.204346168 [EPSG:4326]'";
  maps[10].map_dir="Cincinnati_Sectional";                      maps[10].map_ext="'-86.835430477,-77.489561185,35.079310094,40.710967344 [EPSG:4326]'";
  maps[11].map_dir="Cold_Bay_Sectional";                        maps[11].map_ext="'-165.640468050,-153.800561831,51.435855546,58.570375794 [EPSG:4326]'";
  maps[12].map_dir="Dallas-Ft_Worth_Sectional";                 maps[12].map_ext="'-103.442188585,-94.553891163,31.222545980,36.578478429 [EPSG:4326]'";
  maps[13].map_dir="Dawson_Sectional";                          maps[13].map_ext="'-148.080316088,-130.289974713,60.505909142,71.226057459 [EPSG:4326]'";
  maps[14].map_dir="Denver_Sectional";                          maps[14].map_ext="'-112.160426190,-103.503793274,35.116580818,40.332916292 [EPSG:4326]'";
  maps[15].map_dir="Detroit_Sectional";                         maps[15].map_ext="'-86.382007341,-76.401019988,38.859340735,44.873709011 [EPSG:4326]'";
  maps[16].map_dir="Dutch_Harbor_Sectional";                    maps[16].map_ext="'-174.654605248,-162.794051850,50.275421519,57.422383394 [EPSG:4326]'";
  maps[17].map_dir="El_Paso_Sectional";                         maps[17].map_ext="'-110.290448077,-102.020886684,27.407785948,32.390878896 [EPSG:4326]'";
  maps[18].map_dir="Fairbanks_Sectional";                       maps[18].map_ext="'-161.133198079,-143.274380794,60.497334291,71.258744994 [EPSG:4326]'";
  maps[19].map_dir="Grand_Canyon_Air_Tour_Operators";           maps[19].map_ext="'-114.601595003,-111.197838334,35.145294363,37.196338554 [EPSG:4326]'";
  maps[20].map_dir="Grand_Canyon_General_Aviation";             maps[20].map_ext="'-114.958733499,-111.191893704,35.033671802,37.303503529 [EPSG:4326]'";
  maps[21].map_dir="Great_Falls_Sectional";                     maps[21].map_ext="'-118.846904679,-108.008541389,43.409551447,49.940559455 [EPSG:4326]'";
  maps[22].map_dir="Green_Bay_Sectional";                       maps[22].map_ext="'-94.780086624,-84.058907534,42.786683290,49.247078150 [EPSG:4326]'";
  maps[23].map_dir="Halifax_Sectional";                         maps[23].map_ext="'-70.299897758,-60.385370560,42.906328943,48.880649492 [EPSG:4326]'";
  maps[24].map_dir="Hawaiian_Islands_Sectional";                maps[24].map_ext="'-163.056602029,-152.062006189,17.551916671,24.177067679 [EPSG:4326]'";
  maps[25].map_dir="Honolulu_Inset_Sectional";                  maps[25].map_ext="'-158.697318015,-157.154987678,20.712523881,21.641905146 [EPSG:4326]'";
  maps[26].map_dir="Houston_Sectional";                         maps[26].map_ext="'-98.266810467,-90.046872383,27.439409023,32.392599834 [EPSG:4326]'";
  maps[27].map_dir="Jacksonville_Sectional";                    maps[27].map_ext="'-86.332455815,-77.982970205,27.365493069,32.396746952 [EPSG:4326]'";
  maps[28].map_dir="Juneau_Sectional";                          maps[28].map_ext="'-142.677219059,-129.386133532,53.859467672,61.868443169 [EPSG:4326]'";
  maps[29].map_dir="Kansas_City_Sectional";                     maps[29].map_ext="'-98.162375911,-89.504784190,35.285053197,40.501966430 [EPSG:4326]'";
  maps[30].map_dir="Ketchikan_Sectional";                       maps[30].map_ext="'-140.775390811,-128.958259806,50.302077173,57.422873474 [EPSG:4326]'";
  maps[31].map_dir="Klamath_Falls_Sectional";                   maps[31].map_ext="'-126.413869153,-116.385585621,39.171790513,45.214658639 [EPSG:4326]'";
  maps[32].map_dir="Kodiak_Sectional";                          maps[32].map_ext="'-163.699334961,-150.378926620,53.862195233,61.888840144 [EPSG:4326]'";
  maps[33].map_dir="Lake_Huron_Sectional";                      maps[33].map_ext="'-86.763824639,-76.073096376,42.683408005,49.125453729 [EPSG:4326]'";
  maps[34].map_dir="Las_Vegas_Sectional";                       maps[34].map_ext="'-119.765120218,-110.478547403,34.932641364,40.528567594 [EPSG:4326]'";
  maps[35].map_dir="Los_Angeles_Sectional";                     maps[35].map_ext="'-122.612884797,-114.291094285,31.777183365,36.791748667 [EPSG:4326]'";
  maps[36].map_dir="Mariana_Islands_Inset_Sectional";           maps[36].map_ext="'142.729220122,146.885222413,12.986068858,15.490403093 [EPSG:4326]'";
  maps[37].map_dir="McGrath_Sectional";                         maps[37].map_ext="'-164.581230065,-149.534383483,57.321045069,66.388011446 [EPSG:4326]'";
  maps[38].map_dir="Memphis_Sectional";                         maps[38].map_ext="'-96.427153377,-87.551078173,31.219147955,36.567715510 [EPSG:4326]'";
  maps[39].map_dir="Miami_Sectional";                           maps[39].map_ext="'-84.200814725,-75.909925462,23.672194735,28.668139485 [EPSG:4326]'";
  maps[40].map_dir="Montreal_Sectional";                        maps[40].map_ext="'-78.757857683,-68.057112303,42.680687050,49.128768915 [EPSG:4326]'";
  maps[41].map_dir="New_Orleans_Sectional";                     maps[41].map_ext="'-92.318320954,-84.013361641,27.382893921,32.387317036 [EPSG:4326]'";
  maps[42].map_dir="New_York_Sectional";                        maps[42].map_ext="'-78.373816073,-68.413120267,38.880053079,44.882194024 [EPSG:4326]'";
  maps[43].map_dir="Nome_Sectional";                            maps[43].map_ext="'-174.029419383,-156.214075608,60.516898845,71.252113172 [EPSG:4326]'";
  maps[44].map_dir="Omaha_Sectional";                           maps[44].map_ext="'-102.417746159,-92.382293713,39.182626473,45.229814461 [EPSG:4326]'";
  maps[45].map_dir="Phoenix_Sectional";                         maps[45].map_ext="'-117.347150584,-108.514309503,30.949684596,36.272200025 [EPSG:4326]'";
  maps[46].map_dir="Point_Barrow_Sectional";                    maps[46].map_ext="'-160.127631343,-138.614007659,63.401942489,76.365675555 [EPSG:4326]'";
  maps[47].map_dir="Salt_Lake_City_Sectional";                  maps[47].map_ext="'-118.400325211,-108.379883307,39.175849253,45.213992150 [EPSG:4326]'";
  maps[48].map_dir="Samoan_Islands_Inset_Sectional";            maps[48].map_ext="'-172.963236533,-169.257658283,-15.089602031,-12.856685439 [EPSG:4326]'";
  maps[49].map_dir="San_Antonio_Sectional";                     maps[49].map_ext="'-104.238908185,-96.008018993,27.433124648,32.392914405 [EPSG:4326]'";
  maps[50].map_dir="San_Francisco_Sectional";                   maps[50].map_ext="'-126.154329563,-117.425450963,35.618308466,40.878177924 [EPSG:4326]'";
  maps[51].map_dir="Seattle_Sectional";                         maps[51].map_ext="'-126.838093389,-116.008667973,43.426615961,49.952238163 [EPSG:4326]'";
  maps[52].map_dir="Seward_Sectional";                          maps[52].map_ext="'-154.523857893,-139.593974180,55.817142425,64.813629024 [EPSG:4326]'";
  maps[53].map_dir="St_Louis_Sectional";                        maps[53].map_ext="'-92.871575308,-83.517909918,35.081192662,40.717547704 [EPSG:4326]'";
  maps[54].map_dir="Twin_Cities_Sectional";                     maps[54].map_ext="'-102.866635389,-92.005004626,43.422682407,49.967710988 [EPSG:4326]'";
  maps[55].map_dir="Washington_Sectional";                      maps[55].map_ext="'-80.155649839,-71.443739682,35.263821649,40.513466219 [EPSG:4326]'";
  maps[56].map_dir="Western_Aleutian_Islands_East_Sectional";   maps[56].map_ext="'-188.993034505,188.999657493,-61.864971037,165.906808933 [EPSG:4326]'";  /// fails
  maps[57].map_dir="Western_Aleutian_Islands_West_Sectional";   maps[57].map_ext="'167.905661264,178.915190407,48.700810508,55.334960064 [EPSG:4326]'";
  maps[58].map_dir="Wichita_Sectional";                         maps[58].map_ext="'-105.118535098,-96.418424813,35.282865640,40.525399815 [EPSG:4326]'";
}
**/

OpenEagleMapUpdateFrame::~OpenEagleMapUpdateFrame()
{
    //(*Destroy(OpenEagleMapUpdateFrame)
    FileDialog_FILE_SELECT->Destroy();
    FileDialogZipFiles->Destroy();
    MessageDialogHelpTifUpdate->Destroy();
    MessageDialogHelpUpdateAllMaps->Destroy();
    //*)
}

void OpenEagleMapUpdateFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void OpenEagleMapUpdateFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    msg+=  "\nPart of the OpenEagle Synthetic Vision Project";
    wxMessageBox(msg, _("Welcome to OpenEagleMapUpdate"));
}

void OpenEagleMapUpdateFrame::OnButtonSelectClick(wxCommandEvent& event)
{
  if (FileDialog_FILE_SELECT->ShowModal() == wxID_CANCEL) return;
  std::string filename = FileDialog_FILE_SELECT->GetFilename().ToStdString().c_str();
  printf("filename? [%s]\n",filename.c_str());
  TextCtrlTifFile->SetValue( FileDialog_FILE_SELECT->GetPath().c_str() );
  bool valid_map = update_map.lookup_map((char *)filename.c_str());
  if (valid_map) {
    printf("valid_map\n");
    printf("map_directory [%s]\n",update_map.map_directory());
    Button_GENERATE_NEW_MAP->Enable(true);
  }
  else {
    printf("not a valid or recognized map\n");
    Button_GENERATE_NEW_MAP->Enable(false);
  }
}

void OpenEagleMapUpdateFrame::OnButton_GENERATE_NEW_MAPClick(wxCommandEvent& event)
{
  std::string filename = FileDialog_FILE_SELECT->GetFilename().ToStdString().c_str();
  printf("filename? [%s]\n",filename.c_str());
  printf("path? [%s]\n",TextCtrlTifFile->GetValue().ToStdString().c_str());

  update_map.generate_map();
  printf("map generated....\n");
  exit(1);
}

void OpenEagleMapUpdateFrame::OnButtonSelectSectionalsZipClick(wxCommandEvent& event)
{
  if (FileDialogZipFiles->ShowModal() == wxID_CANCEL) return;
  std::string filename = FileDialogZipFiles->GetFilename().ToStdString().c_str();
  printf("filename? [%s]\n",filename.c_str());
  TextCtrlSectionalsZip->SetValue( FileDialogZipFiles->GetPath().c_str() );
  if (strcmp(filename.c_str(),"Sectional.zip") == 0) {
    printf("Sectional.zip [%s]\n",filename.c_str());
    update_map.valid_sectionals_zip = true;
  }
  else {
    printf("not a valid or recognized map\n");
     update_map.valid_sectionals_zip = false;
  }
  if ( update_map.valid_sectionals_zip &&  update_map.valid_grand_canyon_zip) ButtonBulkGenerateMaps->Enable(true); else  ButtonBulkGenerateMaps->Enable(false);
}

void OpenEagleMapUpdateFrame::OnButtonSelectGrandCanyonZipClick(wxCommandEvent& event)
{
  if (FileDialogZipFiles->ShowModal() == wxID_CANCEL) return;
  std::string filename = FileDialogZipFiles->GetFilename().ToStdString().c_str();
  printf("filename? [%s]\n",filename.c_str());
  TextCtrlGrandCanyonZip->SetValue( FileDialogZipFiles->GetPath().c_str() );
  if (strcmp(filename.c_str(),"Grand_Canyon.zip") == 0) {
    printf("Grand_Canyon.zip [%s]\n",filename.c_str());
    update_map.valid_grand_canyon_zip = true;
  }
  else {
    printf("not a valid or recognized map\n");
     update_map.valid_grand_canyon_zip = false;
  }
 /**
  if ( update_map.valid_sectionals_zip == true) {
    printf("valid_sectionals_zip::");
    if (update_map.valid_grand_canyon_zip == true) {
      printf("valid_grand_canyon_zip::");
      ButtonBulkGenerateMaps->Enable(true);
    }
    else ButtonBulkGenerateMaps->Enable(false);
  }
**/
  if ( (update_map.valid_sectionals_zip == true) &&  (update_map.valid_grand_canyon_zip == true) ) ButtonBulkGenerateMaps->Enable(true); else  ButtonBulkGenerateMaps->Enable(false);

}

void OpenEagleMapUpdateFrame::OnButtonHelpClick(wxCommandEvent& event)
{
  MessageDialogHelpTifUpdate->SetMessage("Use Select button to bring up file selection dialog for Tif files and select for a single map update");
  MessageDialogHelpTifUpdate->ShowModal();
}

void OpenEagleMapUpdateFrame::OnButtonBulkHelpClick(wxCommandEvent& event)
{
   MessageDialogHelpUpdateAllMaps->SetMessage("Use Select buttons to bring up file selection Dialogs for Sectionals.zip and Grand_Canyon.zip files download from the FAA's website");
   MessageDialogHelpUpdateAllMaps->SetExtendedMessage("Reminder: The FAA recommends that the current version of Sectionals.zip be downloaded at off peak hours\n");
   MessageDialogHelpUpdateAllMaps->ShowModal();
}

void OpenEagleMapUpdateFrame::OnButtonBulkGenerateMapsClick(wxCommandEvent& event)
{

// std::string sectional_filename = TextCtrlSectionalsZip->GetFilename().ToStdString().c_str();

//  std::string grand_canyon_filename = TextCtrlGrandCanyonZip->GetFilename().ToStdString().c_str();

  update_map.generate_map_complete_set(
                                       (char *) TextCtrlSectionalsZip->GetValue().ToStdString().c_str(),
                                       (char *) TextCtrlGrandCanyonZip->GetValue().ToStdString().c_str()
                                        );
  printf("complete set of maps generated....\n");
  exit(1);

}
