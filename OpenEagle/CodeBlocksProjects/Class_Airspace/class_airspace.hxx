#ifndef CLASS_AIRSPACE_HXX_INCLUDED
#define CLASS_AIRSPACE_HXX_INCLUDED
/***************************************************************
 * Name:      class_airspace.hxx.cpp
 * Purpose:   read Class_Airspace shapefile and generate 3D models into FlightGear scenery database
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-22
 * Copyright: Philip Cobbin (cobbin.com)
 * License    GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
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
#include "../shapefile/shapefile.hxx"
#include "../tile/tile.hxx"
#include "../airport/airport.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
#include <string>
class class_airspace
{
  public:
    bool terminal_io;
    class_airspace(airport apt, OpenEaglePaths path);
    void make_flightgear_path_addition();
    std::string command;
    airport *apt;
    OpenEaglePaths *paths;
    shapefile* SHPDBF;
    std::string shp_file;
    void read_dbf();
    void read_shp();
    int n_dbf;
    int n_shp;
    void update_class_airspace(bool do_terminal_io);

    void read_dbf(char * shape_files_path);
    void read_shp(char * shape_files_path);
    void write_NASR_class_airspace(bool do_terminal_io);//,OpenEaglePaths paths);
#define CA_IDENT_FIELD 0
#define CA_UPPER_VAL_FIELD 3
#define CA_UPPER_UOM_FIELD 4
#define CA_UPPER_CODE_FIELD 5
#define CA_LOWER_VAL_FIELD 7
#define CA_LOWER_UOM_FIELD 8
#define CA_LOWER_CODE_FIELD 9
#define CA_CLASS_FIELD 11
#define CA_SECTOR_FIELD 16

    int class_b_cnt;
    int class_c_cnt;
    int class_d_cnt;
    int class_e2_cnt;
    int class_e3_cnt;
    int class_e4_cnt;
    tile T;



  class_airspace(airport* apt_ptr, class OpenEaglePaths * paths_ptr)
  {
    printf("class_airspace(airport * apt_ptr) class init call\n");
    apt = apt_ptr;
    paths = paths_ptr;
    SHPDBF = (shapefile *)new shapefile();
    if (SHPDBF != NULL) {
      printf("have SHPDBF point on shapefile()\n");
     // printf("not null\n");
    }
    else {
      printf("null grr\n");
      printf("error of some sort\n");
      exit(1);
    }
    printf("init of class_airspace done\n");
  }


};

#endif // CLASS_AIRSPACE_HXX_INCLUDED
