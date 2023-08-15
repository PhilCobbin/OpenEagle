/***************************************************************
 * Name:      maps.h
 * Purpose:   Code for generation of leaflet tiled maps for OpenEagle maps in FlightGear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
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
#ifndef MAPS_HXX_INCLUDED
#define MAPS_HXX_INCLUDED
#include <string>
#include "../avl_tree/avl_tree.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
class maps
{

  public:

  OpenEaglePaths path;
  bool valid_sectionals_zip;
  bool valid_grand_canyon_zip;

  bool lookup_map(char * tiff_file);
  char * map_directory();
  std::string map_base_path;
  void generate_files();
  void generate_maps_script();
  void generate_map();
  void generate_map_complete_set(char * sectional_zip_file, char * grand_canyon_zip_file);
  int map_index;
  #define DATELINE_INDEX 56
  struct map_update {
    int index;
    std::string tif_file;
    std::string python_file;
    std::string map_dir;
    std::string map_ext;
    std::string latlon;
  };
  struct map_update * map_update_ptr;
#define MAP_LIST_SIZE 60
struct map_update map_list[MAP_LIST_SIZE];

  struct avl_tree_node * head_avl_tif;
  struct avl_tree_node * avl_ptr;
  maps()
  {
map_list[ 0].tif_file ="Albuquerque SEC.tif";                              map_list[ 0].python_file="Albuquerque_Sectional.py";
map_list[ 1].tif_file ="Anchorage SEC.tif";                                map_list[ 1].python_file="Anchorage_Sectional.py";
map_list[ 2].tif_file ="Atlanta SEC.tif";                                  map_list[ 2].python_file="Atlanta_Sectional.py";
map_list[ 3].tif_file ="Bethel SEC.tif";                                   map_list[ 3].python_file="Bethel_Sectional.py";
map_list[ 4].tif_file ="Billings SEC.tif";                                 map_list[ 4].python_file="Billings_Sectional.py";
map_list[ 5].tif_file ="Brownsville SEC.tif";                              map_list[ 5].python_file="Brownsville_Sectional.py";
map_list[ 6].tif_file ="Cape Lisburne SEC.tif";                            map_list[ 6].python_file="Cape_Lisburne_Sectional.py";
map_list[ 7].tif_file ="Charlotte SEC.tif";                                map_list[ 7].python_file="Charlotte_Sectional.py";
map_list[ 8].tif_file ="Cheyenne SEC.tif";                                 map_list[ 8].python_file="Cheyenne_Sectional.py";
map_list[ 9].tif_file ="Chicago SEC.tif";                                  map_list[ 9].python_file="Chicago_Sectional.py";
map_list[10].tif_file ="Cincinnati SEC.tif";                               map_list[10].python_file="Cincinnati_Sectional.py";
map_list[11].tif_file ="Cold Bay SEC.tif";                                 map_list[11].python_file="Cold_Bay_Sectional.py";
map_list[12].tif_file ="Dallas-Ft Worth SEC.tif";                          map_list[12].python_file="Dallas-Ft_Worth_Sectional.py";
map_list[13].tif_file ="Dawson SEC.tif";                                   map_list[13].python_file="Dawson_Sectional.py";
map_list[14].tif_file ="Denver SEC.tif";                                   map_list[14].python_file="Denver_Sectional.py";
map_list[15].tif_file ="Detroit SEC.tif";                                  map_list[15].python_file="Detroit_Sectional.py";
map_list[16].tif_file ="Dutch Harbor SEC.tif";                             map_list[16].python_file="Dutch_Harbor_Sectional.py";
map_list[17].tif_file ="El Paso SEC.tif";                                  map_list[17].python_file="El_Paso_Sectional.py";
map_list[18].tif_file ="Fairbanks SEC.tif";                                map_list[18].python_file="Fairbanks_Sectional.py";
map_list[19].tif_file ="Grand Canyon Air Tour Operators.tif";              map_list[19].python_file="Grand_Canyon_Air_Tour_Operators.py";
map_list[20].tif_file ="Grand Canyon General Aviation.tif";                map_list[20].python_file="Grand_Canyon_General_Aviation.py";
map_list[21].tif_file ="Great Falls SEC.tif";                              map_list[21].python_file="Great_Falls_Sectional.py";
map_list[22].tif_file ="Green Bay SEC.tif";                                map_list[22].python_file="Green_Bay_Sectional.py";
map_list[23].tif_file ="Halifax SEC.tif";                                  map_list[23].python_file="Halifax_Sectional.py";
map_list[24].tif_file ="Hawaiian Islands SEC.tif";                         map_list[24].python_file="Hawaiian_Islands_Sectional.py";
map_list[25].tif_file ="Honolulu Inset SEC.tif";                           map_list[25].python_file="Honolulu_Inset_Sectional.py";
map_list[26].tif_file ="Houston SEC.tif";                                  map_list[26].python_file="Houston_Sectional.py";
map_list[27].tif_file ="Jacksonville SEC.tif";                             map_list[27].python_file="Jacksonville_Sectional.py";
map_list[28].tif_file ="Juneau SEC.tif";                                   map_list[28].python_file="Juneau_Sectional.py";
map_list[29].tif_file ="Kansas City SEC.tif";                              map_list[29].python_file="Kansas_City_Sectional.py";
map_list[30].tif_file ="Ketchikan SEC.tif";                                map_list[30].python_file="Ketchikan_Sectional.py";
map_list[31].tif_file ="Klamath Falls SEC.tif";                            map_list[31].python_file="Klamath_Falls_Sectional.py";
map_list[32].tif_file ="Kodiak SEC.tif";                                   map_list[32].python_file="Kodiak_Sectional.py";
map_list[33].tif_file ="Lake Huron SEC.tif";                               map_list[33].python_file="Lake_Huron_Sectional.py";
map_list[34].tif_file ="Las Vegas SEC.tif";                                map_list[34].python_file="Las_Vegas_Sectional.py";
map_list[35].tif_file ="Los Angeles SEC.tif";                              map_list[35].python_file="Los_Angeles_Sectional.py";
map_list[36].tif_file ="Mariana Islands Inset SEC.tif";                    map_list[36].python_file="Mariana_Islands_Inset_Sectional.py";
map_list[37].tif_file ="McGrath SEC.tif";                                  map_list[37].python_file="McGrath_Sectional.py";
map_list[38].tif_file ="Memphis SEC.tif";                                  map_list[38].python_file="Memphis_Sectional.py";
map_list[39].tif_file ="Miami SEC.tif";                                    map_list[39].python_file="Miami_Sectional.py";
map_list[40].tif_file ="Montreal SEC.tif";                                 map_list[40].python_file="Montreal_Sectional.py";
map_list[41].tif_file ="New Orleans SEC.tif";                              map_list[41].python_file="New_Orleans_Sectional.py";
map_list[42].tif_file ="New York SEC.tif";                                 map_list[42].python_file="New_York_Sectional.py";
map_list[43].tif_file ="Nome SEC.tif";                                     map_list[43].python_file="Nome_Sectional.py";
map_list[44].tif_file ="Omaha SEC.tif";                                    map_list[44].python_file="Omaha_Sectional.py";
map_list[45].tif_file ="Phoenix SEC.tif";                                  map_list[45].python_file="Phoenix_Sectional.py";
map_list[46].tif_file ="Point Barrow SEC.tif";                             map_list[46].python_file="Point_Barrow_Sectional.py";
map_list[47].tif_file ="Salt Lake City SEC.tif";                           map_list[47].python_file="Salt_Lake_City_Sectional.py";
map_list[48].tif_file ="Samoan Islands Inset SEC.tif";                     map_list[48].python_file="Samoan_Islands_Inset_Sectional.py";
map_list[49].tif_file ="San Antonio SEC.tif";                              map_list[49].python_file="San_Antonio_Sectional.py";
map_list[50].tif_file ="San Francisco SEC.tif";                            map_list[50].python_file="San_Francisco_Sectional.py";
map_list[51].tif_file ="Seattle SEC.tif";                                  map_list[51].python_file="Seattle_Sectional.py";
map_list[52].tif_file ="Seward SEC.tif";                                   map_list[52].python_file="Seward_Sectional.py";
map_list[53].tif_file ="St Louis SEC.tif";                                 map_list[53].python_file="St_Louis_Sectional.py";
map_list[54].tif_file ="Twin Cities SEC.tif";                              map_list[54].python_file="Twin_Cities_Sectional.py";
map_list[55].tif_file ="Washington SEC.tif";                               map_list[55].python_file="Washington_Sectional.py";
map_list[56].tif_file ="Western Aleutian Islands East SEC.tif";            map_list[56].python_file="Western_Aleutian_Islands_East_Sectional_WEST.py";  ///dateline (180 degrees) split
map_list[57].tif_file ="Western Aleutian Islands East SEC.tif";            map_list[57].python_file="Western_Aleutian_Islands_East_Sectional_EAST.py";  ///dateline (180 degrees) split
map_list[58].tif_file ="Western Aleutian Islands West SEC.tif";            map_list[58].python_file="Western_Aleutian_Islands_West_Sectional.py";
map_list[59].tif_file ="Wichita SEC.tif";                                  map_list[59].python_file="Wichita_Sectional.py";


  map_list[ 0].map_dir="Albuquerque_Sectional";                     map_list[ 0].map_ext="'-110.436260932,-101.552246553,31.217888105,36.571239668 [EPSG:4326]'";   map_list[ 0].latlon=" 33.8945638865,-105.9942537425";
  map_list[ 1].map_dir="Anchorage_Sectional";                       map_list[ 1].map_ext="'-154.201534387,-138.983410740,57.273851253,66.444026190 [EPSG:4326]'";   map_list[ 1].latlon=" 61.8589387215,-146.5924725635";
  map_list[ 2].map_dir="Atlanta_Sectional";                         map_list[ 2].map_ext="'-89.456950464,-80.533427545,31.530872591,36.908031308 [EPSG:4326]'";     map_list[ 2].latlon=" 34.2194519495, -84.9951890045";
  map_list[ 3].map_dir="Bethel_Sectional";                          map_list[ 3].map_ext="'-175.162053631,-159.953074081,57.303924640,66.468589506 [EPSG:4326]'";   map_list[ 3].latlon=" 61.8862570730,-167.5575638560";
  map_list[ 4].map_dir="Billings_Sectional";                        map_list[ 4].map_ext="'-110.846549822,-100.009085508,43.430176657,49.960642958 [EPSG:4326]'";   map_list[ 4].latlon=" 46.6954098075,-105.4278176650";
  map_list[ 5].map_dir="Brownsville_Sectional";                     map_list[ 5].map_ext="'-104.309481166,-96.017751625,23.397420685,28.393871771 [EPSG:4326]'";    map_list[ 5].latlon=" 25.8956462280,-100.1636163955";
  map_list[ 6].map_dir="Cape_Lisburne_Sectional";                   map_list[ 6].map_ext="'-175.886244034,-154.418956963,63.385583287,76.321394721 [EPSG:4326]'";   map_list[ 6].latlon=" 69.8534890040,-165.1526004985";
  map_list[ 7].map_dir="Charlotte_Sectional";                       map_list[ 7].map_ext="'-83.014210663,-74.664076094,31.379893632,36.411538566 [EPSG:4326]'";     map_list[ 7].latlon=" 33.8957160990, -78.8391433785";
  map_list[ 8].map_dir="Cheyenne_Sectional";                        map_list[ 8].map_ext="'-110.412189803,-100.378593545,39.177464971,45.223534452 [EPSG:4326]'";   map_list[ 8].latlon=" 42.2004997115,-105.3953916740";
  map_list[ 9].map_dir="Chicago_Sectional";                         map_list[ 9].map_ext="'-94.417548626,-84.379640362,39.155678348,45.204346168 [EPSG:4326]'";     map_list[ 9].latlon=" 42.1800122580, -89.3985944940";
  map_list[10].map_dir="Cincinnati_Sectional";                      map_list[10].map_ext="'-86.835430477,-77.489561185,35.079310094,40.710967344 [EPSG:4326]'";     map_list[10].latlon=" 37.8951387190, -82.1624958310";
  map_list[11].map_dir="Cold_Bay_Sectional";                        map_list[11].map_ext="'-165.640468050,-153.800561831,51.435855546,58.570375794 [EPSG:4326]'";   map_list[11].latlon=" 55.0031156700,-159.7205149405";
  map_list[12].map_dir="Dallas-Ft_Worth_Sectional";                 map_list[12].map_ext="'-103.442188585,-94.553891163,31.222545980,36.578478429 [EPSG:4326]'";    map_list[12].latlon=" 33.9005122045, -98.9980398740";
  map_list[13].map_dir="Dawson_Sectional";                          map_list[13].map_ext="'-148.080316088,-130.289974713,60.505909142,71.226057459 [EPSG:4326]'";   map_list[13].latlon=" 65.8659833005,-139.1851454005";
  map_list[14].map_dir="Denver_Sectional";                          map_list[14].map_ext="'-112.160426190,-103.503793274,35.116580818,40.332916292 [EPSG:4326]'";   map_list[14].latlon=" 37.7247485550,-107.8321097320";
  map_list[15].map_dir="Detroit_Sectional";                         map_list[15].map_ext="'-86.382007341,-76.401019988,38.859340735,44.873709011 [EPSG:4326]'";     map_list[15].latlon=" 41.8665248730, -81.3915136645";
  map_list[16].map_dir="Dutch_Harbor_Sectional";                    map_list[16].map_ext="'-174.654605248,-162.794051850,50.275421519,57.422383394 [EPSG:4326]'";   map_list[16].latlon=" 53.8489024565,-168.7243285490";
  map_list[17].map_dir="El_Paso_Sectional";                         map_list[17].map_ext="'-110.290448077,-102.020886684,27.407785948,32.390878896 [EPSG:4326]'";   map_list[17].latlon=" 29.8993324220,-106.1556673805";
  map_list[18].map_dir="Fairbanks_Sectional";                       map_list[18].map_ext="'-161.133198079,-143.274380794,60.497334291,71.258744994 [EPSG:4326]'";   map_list[18].latlon=" 65.8780396425,-152.2037894365";
  map_list[19].map_dir="Grand_Canyon_Air_Tour_Operators";           map_list[19].map_ext="'-114.601595003,-111.197838334,35.145294363,37.196338554 [EPSG:4326]'";   map_list[19].latlon=" 36.1708164585,-112.8997166685";
  map_list[20].map_dir="Grand_Canyon_General_Aviation";             map_list[20].map_ext="'-114.958733499,-111.191893704,35.033671802,37.303503529 [EPSG:4326]'";   map_list[20].latlon=" 36.1685876655,-113.0753136015";
  map_list[21].map_dir="Great_Falls_Sectional";                     map_list[21].map_ext="'-118.846904679,-108.008541389,43.409551447,49.940559455 [EPSG:4326]'";   map_list[21].latlon=" 46.6750554510,-113.4277230340";
  map_list[22].map_dir="Green_Bay_Sectional";                       map_list[22].map_ext="'-94.780086624,-84.058907534,42.786683290,49.247078150 [EPSG:4326]'";     map_list[22].latlon=" 46.0168807200, -89.4194970790";
  map_list[23].map_dir="Halifax_Sectional";                         map_list[23].map_ext="'-70.299897758,-60.385370560,42.906328943,48.880649492 [EPSG:4326]'";     map_list[23].latlon=" 45.8934892175, -65.3426341590";
  map_list[24].map_dir="Hawaiian_Islands_Sectional";                map_list[24].map_ext="'-163.056602029,-152.062006189,17.551916671,24.177067679 [EPSG:4326]'";   map_list[24].latlon=" 20.8644921750,-157.5593041090";
  map_list[25].map_dir="Honolulu_Inset_Sectional";                  map_list[25].map_ext="'-158.697318015,-157.154987678,20.712523881,21.641905146 [EPSG:4326]'";   map_list[25].latlon=" 21.1772145135,-157.9261528465";
  map_list[26].map_dir="Houston_Sectional";                         map_list[26].map_ext="'-98.266810467,-90.046872383,27.439409023,32.392599834 [EPSG:4326]'";     map_list[26].latlon=" 29.9160044285, -94.1568414250";
  map_list[27].map_dir="Jacksonville_Sectional";                    map_list[27].map_ext="'-86.332455815,-77.982970205,27.365493069,32.396746952 [EPSG:4326]'";     map_list[27].latlon=" 29.8811200105, -82.1577130100";
  map_list[28].map_dir="Juneau_Sectional";                          map_list[28].map_ext="'-142.677219059,-129.386133532,53.859467672,61.868443169 [EPSG:4326]'";   map_list[28].latlon=" 57.8639554205,-136.0316762955";
  map_list[29].map_dir="Kansas_City_Sectional";                     map_list[29].map_ext="'-98.162375911,-89.504784190,35.285053197,40.501966430 [EPSG:4326]'";     map_list[29].latlon=" 37.8935098135, -93.8335800505";
  map_list[30].map_dir="Ketchikan_Sectional";                       map_list[30].map_ext="'-140.775390811,-128.958259806,50.302077173,57.422873474 [EPSG:4326]'";   map_list[30].latlon=" 53.8624753235,-134.8668253085";
  map_list[31].map_dir="Klamath_Falls_Sectional";                   map_list[31].map_ext="'-126.413869153,-116.385585621,39.171790513,45.214658639 [EPSG:4326]'";   map_list[31].latlon=" 42.1932245760,-121.3997273870";
  map_list[32].map_dir="Kodiak_Sectional";                          map_list[32].map_ext="'-163.699334961,-150.378926620,53.862195233,61.888840144 [EPSG:4326]'";   map_list[32].latlon=" 57.8755176885,-157.0391307905";
  map_list[33].map_dir="Lake_Huron_Sectional";                      map_list[33].map_ext="'-86.763824639,-76.073096376,42.683408005,49.125453729 [EPSG:4326]'";     map_list[33].latlon=" 45.9044308670, -81.4184605075";
  map_list[34].map_dir="Las_Vegas_Sectional";                       map_list[34].map_ext="'-119.765120218,-110.478547403,34.932641364,40.528567594 [EPSG:4326]'";   map_list[34].latlon=" 37.7306044790,-115.1218338105";
  map_list[35].map_dir="Los_Angeles_Sectional";                     map_list[35].map_ext="'-122.612884797,-114.291094285,31.777183365,36.791748667 [EPSG:4326]'";   map_list[35].latlon=" 34.2844660160,-118.4519895410";
  map_list[36].map_dir="Mariana_Islands_Inset_Sectional";           map_list[36].map_ext="'142.729220122,146.885222413,12.986068858,15.490403093 [EPSG:4326]'";     map_list[36].latlon=" 14.2382359755, 144.8072212675";
  map_list[37].map_dir="McGrath_Sectional";                         map_list[37].map_ext="'-164.581230065,-149.534383483,57.321045069,66.388011446 [EPSG:4326]'";   map_list[37].latlon=" 61.8545282575,-157.0578067740";
  map_list[38].map_dir="Memphis_Sectional";                         map_list[38].map_ext="'-96.427153377,-87.551078173,31.219147955,36.567715510 [EPSG:4326]'";     map_list[38].latlon=" 33.8934317325, -91.9891157750";
  map_list[39].map_dir="Miami_Sectional";                           map_list[39].map_ext="'-84.200814725,-75.909925462,23.672194735,28.668139485 [EPSG:4326]'";     map_list[39].latlon=" 26.1701671100, -80.0553700935";
  map_list[40].map_dir="Montreal_Sectional";                        map_list[40].map_ext="'-78.757857683,-68.057112303,42.680687050,49.128768915 [EPSG:4326]'";     map_list[40].latlon=" 45.9047279825, -73.4074849930";
  map_list[41].map_dir="New_Orleans_Sectional";                     map_list[41].map_ext="'-92.318320954,-84.013361641,27.382893921,32.387317036 [EPSG:4326]'";     map_list[41].latlon=" 29.8851054785, -88.1658412975";
  map_list[42].map_dir="New_York_Sectional";                        map_list[42].map_ext="'-78.373816073,-68.413120267,38.880053079,44.882194024 [EPSG:4326]'";     map_list[42].latlon=" 41.8811235515, -73.3934681700";
  map_list[43].map_dir="Nome_Sectional";                            map_list[43].map_ext="'-174.029419383,-156.214075608,60.516898845,71.252113172 [EPSG:4326]'";   map_list[43].latlon=" 65.8845060085,-165.1217474955";
  map_list[44].map_dir="Omaha_Sectional";                           map_list[44].map_ext="'-102.417746159,-92.382293713,39.182626473,45.229814461 [EPSG:4326]'";    map_list[44].latlon=" 42.2062204670, -97.4000199360";
  map_list[45].map_dir="Phoenix_Sectional";                         map_list[45].map_ext="'-117.347150584,-108.514309503,30.949684596,36.272200025 [EPSG:4326]'";   map_list[45].latlon=" 33.6109423105,-112.9307300435";
  map_list[46].map_dir="Point_Barrow_Sectional";                    map_list[46].map_ext="'-160.127631343,-138.614007659,63.401942489,76.365675555 [EPSG:4326]'";   map_list[46].latlon=" 69.8838090220,-149.3708195010";
  map_list[47].map_dir="Salt_Lake_City_Sectional";                  map_list[47].map_ext="'-118.400325211,-108.379883307,39.175849253,45.213992150 [EPSG:4326]'";   map_list[47].latlon=" 42.1949207015,-113.3901042590";
  map_list[48].map_dir="Samoan_Islands_Inset_Sectional";            map_list[48].map_ext="'-172.963236533,-169.257658283,-15.089602031,-12.856685439 [EPSG:4326]'"; map_list[48].latlon="-13.9731437350,-171.1104474080";
  map_list[49].map_dir="San_Antonio_Sectional";                     map_list[49].map_ext="'-104.238908185,-96.008018993,27.433124648,32.392914405 [EPSG:4326]'";    map_list[49].latlon=" 29.9130195265,-100.1234635890";
  map_list[50].map_dir="San_Francisco_Sectional";                   map_list[50].map_ext="'-126.154329563,-117.425450963,35.618308466,40.878177924 [EPSG:4326]'";   map_list[50].latlon=" 38.2482431950,-121.7898902630";
  map_list[51].map_dir="Seattle_Sectional";                         map_list[51].map_ext="'-126.838093389,-116.008667973,43.426615961,49.952238163 [EPSG:4326]'";   map_list[51].latlon=" 46.6894270620,-121.4233806810";
  map_list[52].map_dir="Seward_Sectional";                          map_list[52].map_ext="'-154.523857893,-139.593974180,55.817142425,64.813629024 [EPSG:4326]'";   map_list[52].latlon=" 60.3153857245,-147.0589160365";
  map_list[53].map_dir="St_Louis_Sectional";                        map_list[53].map_ext="'-92.871575308,-83.517909918,35.081192662,40.717547704 [EPSG:4326]'";     map_list[53].latlon=" 37.8993701830, -88.1947426130";
  map_list[54].map_dir="Twin_Cities_Sectional";                     map_list[54].map_ext="'-102.866635389,-92.005004626,43.422682407,49.967710988 [EPSG:4326]'";    map_list[54].latlon=" 46.6951966975, -97.4358200075";
  map_list[55].map_dir="Washington_Sectional";                      map_list[55].map_ext="'-80.155649839,-71.443739682,35.263821649,40.513466219 [EPSG:4326]'";     map_list[55].latlon=" 37.8886439340, -75.7996947605";
  map_list[56].map_dir="Western_Aleutian_Islands_East_Sectional_WEST";   map_list[56].map_ext="'177.000000000,179.9999999999,48.700810508,55.334960064 [EPSG:4326]'";    map_list[56].latlon=" 52.0178852860, 178.4999999995";
  map_list[57].map_dir="Western_Aleutian_Islands_East_Sectional_EAST";   map_list[57].map_ext="'-179.99999999,-172.000000000,48.700810508,55.334960064 [EPSG:4326]'";    map_list[57].latlon=" 52.0178852860,-175.9999999950";
  map_list[58].map_dir="Western_Aleutian_Islands_West_Sectional";   map_list[58].map_ext="'167.905661264,178.915190407,48.700810508,55.334960064 [EPSG:4326]'";     map_list[58].latlon=" 52.0178852860, 173.4104258355";
  map_list[59].map_dir="Wichita_Sectional";                         map_list[59].map_ext="'-105.118535098,-96.418424813,35.282865640,40.525399815 [EPSG:4326]'";    map_list[59].latlon=" 37.9041327275,-100.7684799555";
  for (int i = 0; i< MAP_LIST_SIZE; i++) map_list[i].index = i;
  head_avl_tif       = initialize_avl_tree();
  bool got_path = path.setupOpenEaglePaths("OpenEagleMapUpdate","");
  if (!got_path) {
    printf("unable to get paths for OpenEagle and FlighGear installation!\n");
    exit(1);
  }

  map_base_path  = path.OpenEagle_FlightGear_Path.c_str();
  map_base_path += "/Phi/OpenEagleMaps/";

///  map_base_path = "/OpenEagleMaps";

  for (int i = 0; i< MAP_LIST_SIZE; i++)
  {
    avl_ptr = search_avl_tree ((char *)map_list[i].tif_file.c_str(), false, head_avl_tif);
    if (avl_ptr==NULL) {
      avl_ptr = search_avl_tree ((char *)map_list[i].tif_file.c_str(), true, head_avl_tif);
      avl_ptr->data_ptr = (void *) &map_list[i];
    }
    else {
      printf("double entry in tif file list [%s] ignoring\n",map_list[i].tif_file.c_str());
    }
  }
  printf("generate_files(): \n");
  generate_files();
  printf("completed\n");

  valid_sectionals_zip = false;
  valid_grand_canyon_zip = false;

  }
  ~maps()
  {
    erase_avl_tree(head_avl_tif);
  }
};
#endif

