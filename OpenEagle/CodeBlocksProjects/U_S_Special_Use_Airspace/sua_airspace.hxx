#ifndef SUA_AIRSPACE_HXX_INCLUDED
#define SUA_AIRSPACE_HXX_INCLUDED
/***************************************************************
 * Name:      sua_airspace.hxx.cpp
 * Purpose:   read U_S_Special_Use_Airspace shapefile and generate 3D models into FlightGear scenery database
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-22
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
 #include "../shapefile/shapefile.hxx"
 #include "../tile/tile.hxx"
 #include "../OpenEaglePaths/OpenEaglePaths.hxx"
class sua_airspace
{
  public:
///#define SUA_NAME_FIELD 1
#define SUA_NAME_FIELD 2
///#define SUA_TYPE_CODE_FIELD 2
#define SUA_TYPE_CODE_FIELD 3

///#define SUA_UPPER_DESC_FIELD 4
#define SUA_UPPER_DESC_FIELD 5
///#define SUA_UPPER_VAL_FIELD 5
#define SUA_UPPER_VAL_FIELD 6
///#define SUA_UPPER_UOM_FIELD 6
#define SUA_UPPER_UOM_FIELD 7
///#define SUA_UPPER_CODE_FIELD 7
#define SUA_UPPER_CODE_FIELD 8

///#define SUA_LOWER_DESC 8
#define SUA_LOWER_DESC 9
///#define SUA_LOWER_VAL_FIELD 9
#define SUA_LOWER_VAL_FIELD 10
///#define SUA_LOWER_UOM_FIELD 10
#define SUA_LOWER_UOM_FIELD 11
///#define SUA_LOWER_CODE_FIELD 11
#define SUA_LOWER_CODE_FIELD 12

/// #define SUA_STATE_FIELD 14
#define SUA_STATE_FIELD 15

///#define SUA_SECTOR_FIELD 18
#define SUA_SECTOR_FIELD 19
      shapefile* SHPDBF;
      std::string command;
      void make_flightgear_path_addition();
      void initialize_sua_masters_path();
      void read_dbf();
      void read_shp();
      void update_sua_airspace(bool do_terminal_io);

      void read_dbf(char * filepath);
      void read_shp(char * filepath);
      void write_sua_airspace(bool do_terminal_io);//,char *filepath);

      bool terminal_io;
      std::string OpenEagleSua_path;
      std::string fn_sua;
      int n_dbf;
      int n_shp;
      tile T;
      int num_SFC;
      int num_AGL;

      OpenEaglePaths * paths;


  sua_airspace( class OpenEaglePaths * paths_ptr)
  {
    paths = paths_ptr;
    SHPDBF = (shapefile *)new shapefile();
    if (SHPDBF != NULL) {
    //  printf("not null\n");
    }
    else {
      printf("null grr\n");
      printf("error of some sort\n");
      exit(1);
    }
  }
};

#endif // SUA_AIRSPACE_HXX_INCLUDED
