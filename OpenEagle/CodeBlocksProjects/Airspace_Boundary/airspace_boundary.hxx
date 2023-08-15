#ifndef AIRSPACE_BOUNDARY_HXX_INCLUDED
#define AIRSPACE_BOUNDARY_HXX_INCLUDED
/***************************************************************
 * Name:      airspace_boundary.hxx
 * Purpose:   read Airspace Boundary shapefile and generate 3D models into FlightGear scenery database
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
#include "../data_conversion/data_conversion.hxx"
#include "../3rdparty/constants.h"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
class airspace_boundary
{
  public:
    shapefile * SHPDBF;
    void make_flightgear_path_addition();
    OpenEaglePaths *paths;
    std::string command;
    void read_dbf();
    std::string fn_Sata;
    std::string OpenEagleSataMasters_path;
    std::string msl_str;
    void read_shp();
    int n_dbf;
    int n_shp;
    tile T;
    int num_SFC;
    int num_AGL;
    void initialize_sata_path();
    void update_airspace_boundary(bool do_terminal_io);
    void make_flightgear_path_addition(char * filepath);
    void read_dbf(char * filepath);
    void read_shp(char * filepath);
    void write_boundary_airspace(bool do_terminal_io); //, char * filepath);
    bool terminal_io;

#define AB_NAME_FIELD 3
//ANCHORAGE, ALASKA, TERMINAL AREA
//SPECIAL FLIGHT RULES IN THE VICINITY OF GRAND CANYON NATIONAL PARK, AZ
//KETCHIKAN INTL ARPT TRAFFIC RULE
//SPECIAL AIR TRAFFIC RULE IN THE VICINITY OF LUKE AFB, AZ
//SPECIAL AIR TRAFFIC RULES IN THE VICINITY OF NIAGARA FALLS, NEW YORK
//NEW YORK CLASS B AIRSPACE HUDSON RIVER AND EAST RIVER EXCLUSION SFRA
//VALPARAISO, FLORIDA TERMINAL AREA
//WASHINGTON, DC METROPOLITAN AREA SPECIAL FLIGHT RULES AREA
//SPECIAL FLIGHT RULES IN THE VICINITY OF PEARSON FIELD AIRPORT, VANCOUVER, WA
//
//
//
#define AB_TYPE_CODE_FIELD 4
//SATA
//if it's not SATA skip
#define AB_LOCAL_TYPE_FIELD 6
//SFRA
//SPEC_AT_RULES
#define AB_SECTOR_FIELD 8
//**************** note the use of / strip to blank or underscore
//INTERNATIONAL SEG
//INTERNATIONAL SEG
//MERRILL SEGMENT
//LAKE HOOD SEGMENT
//ELMENDORF SEGMENT
//BRYANT SEGMENT
//SEWARD HWY SEGMENT
//SUPAI SECTOR
//TORWP/SHINUMO FFZ
//TORWP/SHINUMO FFZ
//TORWP/SHINUMO FFZ
//BRIGHT ANGEL FFZ
//DESERT VIEW FFZ
//MARBLE CANYON SEC
//PEARCE FERRY SEC
//SANUP FFZ
//DIAMOND CREEK SEC
//SANUP FFZ EAST
//TORWP/SHINUMO FFZ
//TORWP/SHINUMO FFZ
//KTN TRAFFIC RULE
//EAST SECTOR - SOUTH
//EAST SEC SOUTH LOWER
//EAST SECTOR - CENTER
//EAST SECTOR - CENTER
//EAST SECTOR - NORTH
//WEST SECTOR - NORTH
//WEST SECTOR - SOUTH
//SATR NIAG FLS NY
//EAST RIVER EXCLUSION
//EAST RIVER EXCLUSION
//HUDSON RVR EXCLUSION
//NORTH-SOUTH CRDR
//EAST-WEST CRDR-WEST SECTION
//EAST-WEST CRDR-CNTR SECTION
//EAST-WEST CRDR-EAST SECTION
//DC SFRA
//DC FRZ
//PEARSON FIELD SFRA

#define AB_UPPER_VAL_FIELD 11
//numeric upper_val
#define AB_UPPER_UOM_FIELD 12
#define AB_UPPER_CODE_FIELD 13

#define AB_LOWER_VAL_FIELD 15
//numeric lower val
#define AB_LOWER_UOM_FIELD 16
#define AB_LOWER_CODE_FIELD 17

#define AB_STATE_FIELD 24

  airspace_boundary(class OpenEaglePaths * paths_ptr)
  {
    paths = paths_ptr;
    msl_str = "MSL";
    SHPDBF = (shapefile *)new shapefile();
    if (SHPDBF != NULL) {
      printf("not null\n");
    }
    else {
      printf("null grr\n");
      printf("error of some sort\n");
      exit(1);
    }
  }
};

#endif // AIRSPACE_BOUNDARY_HXX_INCLUDED
