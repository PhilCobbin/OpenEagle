/***************************************************************
 * Name:      airspace_boundary.cxx
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

#include "stdlib.h"
#include "../Airspace_Boundary/airspace_boundary.hxx"

void airspace_boundary::make_flightgear_path_addition(char * filepath)
{
 /// std::string base_path = SHPDBF->paths.OpenEagle_FlightGear_Path.c_str();  ///"/home/phil/Desktop/FlightGear-OpenEagle2
 ///             base_path += SHPDBF->paths.airspace_boundary_subpath.c_str(); /// "/Scenery/Models/Airspace_Boundary"

  std::string base_path = filepath;
              base_path += "/Scenery/Models/Airspace_Boundary";

  command = "mkdir -p ";
  command += base_path.c_str();
  command += "\n";
  printf("system_io(%s)\n",command.c_str());
  bool path_ok = system_io(&command);
  if (!path_ok) {
    printf("could not make [%s] in FlightGear path\n",base_path.c_str());
    exit(1);
  }
}

void airspace_boundary::make_flightgear_path_addition()
{
 /// std::string base_path = SHPDBF->paths.OpenEagle_FlightGear_Path.c_str();  ///"/home/phil/Desktop/FlightGear-OpenEagle2
 ///             base_path += SHPDBF->paths.airspace_boundary_subpath.c_str(); /// "/Scenery/Models/Airspace_Boundary"

  std::string base_path = "/home/phil/Desktop/OpenEagle/Programs/Scenery_Test";
              base_path += SHPDBF->paths->boundary_airspace_subpath.c_str(); /// "/Scenery/Models/Airspace_Boundary"

  command = "mkdir -p ";
  command += base_path.c_str();
  command += "\n";
  printf("system_io(%s)\n",command.c_str());
  bool path_ok = system_io(&command);
  if (!path_ok) {
    printf("could not make [%s] in FlightGear path\n",base_path.c_str());
    exit(1);
  }
}

void airspace_boundary::read_dbf(char * filepath)
{
  printf("read_dbf(%s)\n",filepath);

  fn_Sata =  filepath;
  fn_Sata += "/Airspace_Boundary.dbf";


  printf("read_dbf(%s)\n",fn_Sata.c_str());
  int ret = SHPDBF->read_dbf((char *) fn_Sata.c_str());
  if (ret!=0) {
    printf("error while processing maindbf\n");
    exit(1);
  }

//  std::string dbf_file_summary = SHPDBF->paths.OpenEaglePath.c_str();
//  dbf_file_summary += "/Update/Summaries";
//  SHPDBF->summarize_dbf((char *)dbf_file_summary.c_str());

//    SHPDBF->summarize_dbf("");

}

void airspace_boundary::read_dbf()
{
/************************************************************************/
/*                              read_dbf(...)                           */
/************************************************************************/
  printf("read_dbf()\n");
///  fn_Sata = SHPDBF->paths.OpenEaglePath.c_str();
///  fn_Sata += "/Update/Airspace_Boundary/Airspace_Boundary";

  fn_Sata =  "/Update/Airspace_Boundary/Airspace_Boundary";
  fn_Sata += "/";
  fn_Sata += "fix me"; //SHPDBF->paths.OpenEagleUpdate_Boundary_AirspaceFilename.c_str();


  printf("read_dbf(%s)\n",fn_Sata.c_str());
  int ret = SHPDBF->read_dbf((char *) fn_Sata.c_str());
  if (ret!=0) {
    printf("error while processing maindbf\n");
    exit(1);
  }

  std::string dbf_file_summary = SHPDBF->paths->OpenEaglePath.c_str();
  dbf_file_summary += "/Update/Summaries";
  SHPDBF->summarize_dbf((char *)dbf_file_summary.c_str());

}
void airspace_boundary::initialize_sata_path()
{

/************************************************************************/
/*                     initialize Sata path as needed                    */
/*                       this will be a lookup for sfc/agl              */
/*                       altitudes to base .ac files on                 */
/*                                                                      */
/************************************************************************/

  OpenEagleSataMasters_path = SHPDBF->paths->OpenEaglePath.c_str();
  OpenEagleSataMasters_path += SHPDBF->paths->OpenEagleSataMasters_Path.c_str();

  command = "mkdir -p ";
  command += OpenEagleSataMasters_path;
  bool Sata_path_ok = system_io(&command);

  if (!Sata_path_ok) {
    printf("system command failed to create Sata path [%s]\n",command.c_str());
    exit(1);
  }
}

void airspace_boundary::read_shp(char * filepath)
{
  printf("read_shp(%s)\n",filepath);
  std::string filename = filepath;
  filename += "/Airspace_Boundary.shp";
  printf("filename: [%s]\n",filename.c_str());
  int ret = SHPDBF->read_shp( (char *)filename.c_str() );
  if (ret!=0) {
    printf("error while processing mainshp\n");
    exit(1);
  }
  printf("read_shp() successful\n");

  printf("adjust_vertices_for_max_line_length()\n");
  SHPDBF->adjust_vertices_for_max_line_length();

  SHPDBF->set_segments();

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* -------------------------------------------------------------------- */

  SHPDBF->reset_dbf_shp();
  n_dbf =  SHPDBF->get_dbf_num_records();
  n_shp =  SHPDBF->get_shp_nentities();

}

void airspace_boundary::read_shp()
{

/************************************************************************/
/*                              read_shp(...)                           */
/************************************************************************/
  printf("read_shp(%s)\n",fn_Sata.c_str());
  SHPDBF->read_limit = 40;  /// First 40 only read and used for SATA and SFRA items, there are read problems later in the shapefile do to multiple rings on non-used types
  int ret = SHPDBF->read_shp( (char *) fn_Sata.c_str() );
  if (ret!=0) {
    printf("error while processing mainshp\n");
    exit(1);
  }
  printf("read_shp() successful\n");

  printf("adjust_vertices_for_max_line_length()\n");
  SHPDBF->adjust_vertices_for_max_line_length();

  SHPDBF->set_segments();

/* -------------------------------------------------------------------- */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/* -------------------------------------------------------------------- */

  SHPDBF->reset_dbf_shp();
  n_dbf =  SHPDBF->get_dbf_num_records();
  n_shp =  SHPDBF->get_shp_nentities();

}

void airspace_boundary::write_boundary_airspace(bool do_terminal_io) //,char * filepath)
{
//  printf("write_boundary_airspace(...) filepath [%s]\n",filepath);
  terminal_io = do_terminal_io;
//  printf("call make_flightgear_path_addition(%s)\n",filepath);
//  make_flightgear_path_addition(filepath);
  num_SFC = 0;
  num_AGL = 0;
  printf("main for loop:\n");
  for (int i = 0; i < n_dbf; i++) {
    double elevation = 0.0;
    int shape_nbr = SHPDBF->get_dbf_shape_shape_nbr();
    int n_segments = SHPDBF->get_shape_num_segments();

    char * type_code_field = SHPDBF->get_current_data_for_field(AB_TYPE_CODE_FIELD);

    if (strcmp(type_code_field,"SATA")== 0) {

      char * name_field = SHPDBF->get_current_data_for_field(AB_NAME_FIELD);
      char * local_type_field = SHPDBF->get_current_data_for_field(AB_LOCAL_TYPE_FIELD);

      char * sector_field = SHPDBF->get_current_data_for_field(AB_SECTOR_FIELD);

      char * lower_val_field = SHPDBF->get_current_data_for_field(AB_LOWER_VAL_FIELD);
      char * lower_uom_field = SHPDBF->get_current_data_for_field(AB_LOWER_UOM_FIELD);
      char * lower_code_field = SHPDBF->get_current_data_for_field(AB_LOWER_CODE_FIELD);

      char * upper_val_field = SHPDBF->get_current_data_for_field(AB_UPPER_VAL_FIELD);
      char * upper_uom_field = SHPDBF->get_current_data_for_field(AB_UPPER_UOM_FIELD);
      char * upper_code_field = SHPDBF->get_current_data_for_field(AB_UPPER_CODE_FIELD);

      char * state_field = SHPDBF->get_current_data_for_field(AB_STATE_FIELD);

      safe_line(name_field);  // kill of the O'Neills of the world
      replace_space_with_under_score(name_field);
      safe_line(sector_field);
      replace_space_with_under_score(sector_field);

      printf(" NAME [%28s]",name_field);
      printf(" type_code [%3s]",type_code_field);
      printf(" shape [%4d]",shape_nbr);
      //  printf(" vertices [%4d]",n_vertices);
      //  printf(" segments [%4d]",n_segments);
      printf(" lower fields [%6s]:[%3s]:[%3s]",lower_val_field,lower_uom_field,lower_code_field);
      printf(" upper fields [%6s]:[%3s]:[%5s]",upper_val_field,upper_uom_field,upper_code_field);
      printf(" st [%s]",state_field);
      //   printf("\n");

/* -------------------------------------------------------------------------------------------------- */
/*          generate/read elevation and location files                                                */
/*   index auxiliary information such as where to put signage and base elevation as follows           */
/*   Name_Path:                                                                                       */
/*     /Scenery/Models/Airspace_Boundary"/ST/NAME/                                                    */
/*       where blanks in comma in name are converted to underscore                                    */
/*     Files:                                                                                         */
/*       SATA_elevation.txt                                                                           */
/*       SATA_longitude.txt                                                                           */
/*       SATA_latitude.txt                                                                            */
/*                                                                                                    */
/*   Name_Sector_Path:                                                                                */
/*     OpenEagle/SATA/ST/NAME/SECTOR                                                                  */
/*       where SECTOR had blanks, comma and / character converted to underscores                      */
/*     Files:                                                                                         */
/*       SECTOR_elevation.txt                                                                         */
/*       SECTOR_longitude.txt                                                                         */
/*       SECTOR_latitude.txt                                                                          */
/*                                                                                                    */
/*                                                                                                    */
/*                                                                                                    */
/* -------------------------------------------------------------------------------------------------- */

      printf("workaround OpenEagleSataMasters_Path [%s] :\n",(char *)paths->OpenEagleSataMasters_Path.c_str());
      std::string NAME_path = paths->OpenEaglePath;
      NAME_path += paths->OpenEagleSataMasters_Path.c_str(); //OpenEagleSataMasters_path.c_str(); /// "/Masters/OpenEagle/Sata";
      NAME_path += "/";                                          /// "/Masters/OpenEagle/Sata/";
      NAME_path += state_field;                                  /// "/Masters/OpenEagle/Sata/AZ";
      NAME_path += "/";
      NAME_path += name_field;
      std::string SATA_elevation_str = "SATA_elevation";
      std::string SATA_latitude_str = "SATA_latitude";
      std::string SATA_longitude_str = "SATA_longitude";
      std::string SATA_ext_str = "txt";

      std::string NAME_Sector_path =  paths->OpenEagleWrite_Boundary_AirspacePath.c_str(); //         NAME_path.c_str();
      NAME_Sector_path += "/";
      NAME_Sector_path += sector_field;

      std::string SECTOR_elevation_str = "SECTOR_elevation";
      std::string SECTOR_latitude_str = "SECTOR_latitude";
      std::string SECTOR_longitude_str = "SECTOR_longitude";

      double SECTOR_elevation =   read_write_dbl_as_string( &NAME_Sector_path, &SECTOR_elevation_str, &SATA_ext_str );
  //    double SECTOR_elevation =   stod(SECTOR_elevation_str,NULL);
      printf("SECTOR_elevation %f\n",SECTOR_elevation);
/* ---------------------------------------------------------------------------------------- */
/*                                                                                          */
/*  lower_code_field:                                                                       */
/*    SFC    but if lower_val_field >0 change SFC to AGL[1]                                 */
/*    MSL                                                                                   */
/*    STD    flight level, change lower_val_file *=100    ie 310 -> 31000 recode STD->MSL   */
/*           uom field will be FL for flight level                                          */
/*                                                                                          */
/*   upper_code_field:                                                                      */
/*    MSL                                                                                   */
/*    STD    changer upper_val_field *= 100  recode STD->MSL                                */
/*    UNLTD  leave code but change upper_val field to "100000" 100,000 feet\                */
/*                                                                                          */
/*                                                                                          */
/* Notes [1] triggering setting up a sample elevation file with 0.0 feet                    */
/*   a hand edit                                                                            */
/* ---------------------------------------------------------------------------------------- */

      double lower_altitude;
      lower_altitude = strtod(lower_val_field,NULL);
      if ( strcmp(lower_code_field,"SFC") == 0) {
        num_SFC++;
        if (lower_altitude > 0.0) {
          num_AGL++;
          lower_altitude = lower_altitude + SECTOR_elevation;
        }
        else lower_altitude = elevation;
      }
      else {
        if ( strcmp(lower_code_field,"STD") == 0) {
          lower_altitude *= 100.0;
          lower_code_field = (char *)msl_str.c_str();//"MSL";
        }
      }

      double upper_altitude;

      if ( strcmp(upper_code_field,"UNLTD") == 0) {
        upper_altitude = 100000.0;
        upper_code_field = (char *)msl_str.c_str(); //"MSL";
      }
      else {
        upper_altitude = strtod(upper_val_field,NULL);
        if ( strcmp(upper_code_field,"STD") == 0) {
          upper_altitude *= 100.0;
          upper_code_field = (char *)msl_str.c_str(); //"MSL";
        }
      }

      printf(" altitudes: %7.0f - %7.0f\n",lower_altitude, upper_altitude);


/* -------------------------------------------------------------------- */
/*  Now to build directories, write files, and copy texture files       */
/*  into what will be Models/Airspace and /Scenery/Objects/...          */
/* -------------------------------------------------------------------- */

      SHPDBF->reset_segment_list();

      for (int sn = 0; sn < n_segments; sn++) {
        printf("          seg %d",sn);
        int current = sn;
        ///std::string short_ac_path = SHPDBF->paths.boundary_airspace_subpath.c_str();     /// "/Scenery/Models/Boundary_Boundary"
        std::string models_and_objects_path = paths->OpenEagleWrite_ModelsAndObjectsPath; //;
        std::string short_ac_path = "/Scenery/Models/Boundary_Airspace/";                /// "/Scenery/Models/Boundary_Airspace/"
        short_ac_path += local_type_field;                                               /// "/Scenery/Models/Booundary_Airspace/SFRA"
        short_ac_path += "/";                                                            /// "/Scenery/Models/Boundary_Airspace/SFRA/"
        short_ac_path += name_field;                                                     /// /..../SPECIAL_FLIGHT_RULES_IN_THE_VICINITY_OF_GRAND_CANYON_NATIONAL_PARK__AZ"

        std::string full_ac_path = paths->OpenEagleWrite_ModelsAndObjectsPath; //SHPDBF->paths.OpenEagleUpdate_ModelsAndObjectsPath.c_str(); /// "/home/phil/Desktop/OpenEagle/Programs/Scenery_Test"
                    full_ac_path += paths->boundary_airspace_subpath.c_str();     /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary"
        full_ac_path += "/";                                                             /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary/"
        full_ac_path += local_type_field;                                                /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary/SFRA"
        full_ac_path += "/";                                                             /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary/SFRA/"
        full_ac_path += name_field;                                                      /// /..../SPECIAL_FLIGHT_RULES_IN_THE_VICINITY_OF_GRAND_CANYON_NATIONAL_PARK__AZ"
        std::string ac_filename = "SHAPE";                                          // "SHAPE"
        ac_filename += "_";                                                         // "SHAPE_"
        ac_filename += std::to_string(shape_nbr);                                   // "SHAPE_703"
        ac_filename += "_seg_";                                                     // "SHAPE_703_seg_"
        ac_filename += std::to_string(sn);                                          // "SHAPE_703_seg_0"

        std::string texture_path = paths->OpenEaglePath.c_str();
                    texture_path += paths->OpenEagleMastersTextures_Path.c_str();

        std::string texture_name = "unknown texture";
        if ( strcmp(local_type_field,"SFRA") == 0) texture_name = "SATA_SFRA";
        if ( strcmp(local_type_field,"SPEC_AT_RULES") == 0) texture_name = "SATA_SPEC_AT_RULES";

        bool nanbug = SHPDBF->generate_ac_xml_and_update_stg_files_current_segment(
          sn,
          &models_and_objects_path,
          &short_ac_path,
          &full_ac_path,
          &ac_filename,
          &texture_path,
          &texture_name,
          lower_altitude,
          upper_altitude
          );
        if (nanbug) {
          printf("warning nanbug on the prowle\n");
          exit(1);
        }
        current = SHPDBF->next_segment();
        if (current < 0 ) SHPDBF->reset_segment_list();
      }
    }
    bool test = SHPDBF->can_advance_dbf_shp();
    if (test == true) SHPDBF->advance_dbf_shp();  //basically will run off list after processing last record, inhibits waltzing off list end(s)
  }
  printf("num_SFC %d\n",num_SFC);
  printf("num_AGL %d\n",num_AGL);

}

void airspace_boundary::update_airspace_boundary(bool do_terminal_io)
{
  terminal_io = do_terminal_io;
  make_flightgear_path_addition();
  num_SFC = 0;
  num_AGL = 0;
  for (int i = 0; i < n_dbf; i++) {
    double elevation = 0.0;
    int shape_nbr = SHPDBF->get_dbf_shape_shape_nbr();
    int n_segments = SHPDBF->get_shape_num_segments();

    char * type_code_field = SHPDBF->get_current_data_for_field(AB_TYPE_CODE_FIELD);

    if (strcmp(type_code_field,"SATA")== 0) {

      char * name_field = SHPDBF->get_current_data_for_field(AB_NAME_FIELD);
      char * local_type_field = SHPDBF->get_current_data_for_field(AB_LOCAL_TYPE_FIELD);

      char * sector_field = SHPDBF->get_current_data_for_field(AB_SECTOR_FIELD);

      char * lower_val_field = SHPDBF->get_current_data_for_field(AB_LOWER_VAL_FIELD);
      char * lower_uom_field = SHPDBF->get_current_data_for_field(AB_LOWER_UOM_FIELD);
      char * lower_code_field = SHPDBF->get_current_data_for_field(AB_LOWER_CODE_FIELD);

      char * upper_val_field = SHPDBF->get_current_data_for_field(AB_UPPER_VAL_FIELD);
      char * upper_uom_field = SHPDBF->get_current_data_for_field(AB_UPPER_UOM_FIELD);
      char * upper_code_field = SHPDBF->get_current_data_for_field(AB_UPPER_CODE_FIELD);

      char * state_field = SHPDBF->get_current_data_for_field(AB_STATE_FIELD);

      safe_line(name_field);  // kill of the O'Neills of the world
      replace_space_with_under_score(name_field);
      safe_line(sector_field);
      replace_space_with_under_score(sector_field);

      printf(" NAME [%28s]",name_field);
      printf(" type_code [%3s]",type_code_field);
      printf(" shape [%4d]",shape_nbr);
      //  printf(" vertices [%4d]",n_vertices);
      //  printf(" segments [%4d]",n_segments);
      printf(" lower fields [%6s]:[%3s]:[%3s]",lower_val_field,lower_uom_field,lower_code_field);
      printf(" upper fields [%6s]:[%3s]:[%5s]",upper_val_field,upper_uom_field,upper_code_field);
      printf(" st [%s]",state_field);
      //   printf("\n");

/* -------------------------------------------------------------------------------------------------- */
/*          generate/read elevation and location files                                                */
/*   index auxiliary information such as where to put signage and base elevation as follows           */
/*   Name_Path:                                                                                       */
/*     /Scenery/Models/Airspace_Boundary"/ST/NAME/                                                    */
/*       where blanks in comma in name are converted to underscore                                    */
/*     Files:                                                                                         */
/*       SATA_elevation.txt                                                                           */
/*       SATA_longitude.txt                                                                           */
/*       SATA_latitude.txt                                                                            */
/*                                                                                                    */
/*   Name_Sector_Path:                                                                                */
/*     OpenEagle/SATA/ST/NAME/SECTOR                                                                  */
/*       where SECTOR had blanks, comma and / character converted to underscores                      */
/*     Files:                                                                                         */
/*       SECTOR_elevation.txt                                                                         */
/*       SECTOR_longitude.txt                                                                         */
/*       SECTOR_latitude.txt                                                                          */
/*                                                                                                    */
/*                                                                                                    */
/*                                                                                                    */
/* -------------------------------------------------------------------------------------------------- */
      std::string NAME_path = OpenEagleSataMasters_path.c_str(); /// "/Masters/OpenEagle/Sata";
      NAME_path += "/";                                          /// "/Masters/OpenEagle/Sata/";
      NAME_path += state_field;                                  /// "/Masters/OpenEagle/Sata/AZ";
      NAME_path += "/";
      NAME_path += name_field;
      std::string SATA_elevation_str = "SATA_elevation";
      std::string SATA_latitude_str = "SATA_latitude";
      std::string SATA_longitude_str = "SATA_longitude";
      std::string SATA_ext_str = "txt";

      std::string NAME_Sector_path = NAME_path.c_str();
      NAME_Sector_path += "/";
      NAME_Sector_path += sector_field;

      std::string SECTOR_elevation_str = "SECTOR_elevation";
      std::string SECTOR_latitude_str = "SECTOR_latitude";
      std::string SECTOR_longitude_str = "SECTOR_longitude";

      double SECTOR_elevation =  read_write_dbl_as_string( &NAME_Sector_path, &SECTOR_elevation_str, &SATA_ext_str );
     // double SECTOR_elevation =  stod(SECTOR_elevation_str);



/* ---------------------------------------------------------------------------------------- */
/*                                                                                          */
/*  lower_code_field:                                                                       */
/*    SFC    but if lower_val_field >0 change SFC to AGL[1]                                 */
/*    MSL                                                                                   */
/*    STD    flight level, change lower_val_file *=100    ie 310 -> 31000 recode STD->MSL   */
/*           uom field will be FL for flight level                                          */
/*                                                                                          */
/*   upper_code_field:                                                                      */
/*    MSL                                                                                   */
/*    STD    changer upper_val_field *= 100  recode STD->MSL                                */
/*    UNLTD  leave code but change upper_val field to "100000" 100,000 feet\                */
/*                                                                                          */
/*                                                                                          */
/* Notes [1] triggering setting up a sample elevation file with 0.0 feet                    */
/*   a hand edit                                                                            */
/* ---------------------------------------------------------------------------------------- */

      double lower_altitude;
      lower_altitude = strtod(lower_val_field,NULL);
      if ( strcmp(lower_code_field,"SFC") == 0) {
        num_SFC++;
        if (lower_altitude > 0.0) {
          num_AGL++;
          lower_altitude = lower_altitude + SECTOR_elevation;
        }
        else lower_altitude = elevation;
      }
      else {
        if ( strcmp(lower_code_field,"STD") == 0) {
          lower_altitude *= 100.0;
          lower_code_field = (char *)msl_str.c_str();//"MSL";
        }
      }

      double upper_altitude;

      if ( strcmp(upper_code_field,"UNLTD") == 0) {
        upper_altitude = 100000.0;
        upper_code_field = (char *)msl_str.c_str(); //"MSL";
      }
      else {
        upper_altitude = strtod(upper_val_field,NULL);
        if ( strcmp(upper_code_field,"STD") == 0) {
          upper_altitude *= 100.0;
          upper_code_field = (char *)msl_str.c_str(); //"MSL";
        }
      }

      printf(" altitudes: %7.0f - %7.0f\n",lower_altitude, upper_altitude);


/* -------------------------------------------------------------------- */
/*  Now to build directories, write files, and copy texture files       */
/*  into what will be Models/Airspace and /Scenery/Objects/...          */
/* -------------------------------------------------------------------- */

      SHPDBF->reset_segment_list();

      for (int sn = 0; sn < n_segments; sn++) {
        printf("          seg %d",sn);
        int current = sn;
        ///std::string short_ac_path = SHPDBF->paths.boundary_airspace_subpath.c_str();     /// "/Scenery/Models/Boundary_Boundary"
        std::string models_and_objects_path = "????";
        std::string short_ac_path = "/Scenery/Models/Boundary_Airspace/";                /// "/Scenery/Models/Boundary_Airspace/"
        short_ac_path += local_type_field;                                               /// "/Scenery/Models/Booundary_Airspace/SFRA"
        short_ac_path += "/";                                                            /// "/Scenery/Models/Boundary_Airspace/SFRA/"
        short_ac_path += name_field;                                                     /// /..../SPECIAL_FLIGHT_RULES_IN_THE_VICINITY_OF_GRAND_CANYON_NATIONAL_PARK__AZ"

        std::string full_ac_path = "/home/phil/Desktop/OpenEagle/Programs/Scenery_Test";
                    full_ac_path += SHPDBF->paths->boundary_airspace_subpath.c_str();     /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary"
        full_ac_path += "/";                                                             /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary/"
        full_ac_path += local_type_field;                                                /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary/SFRA"
        full_ac_path += "/";                                                             /// "/home/phil/Desktop/FlightGear-OpenEagle2/Scenery/Models/Airspace_Boundary/SFRA/"
        full_ac_path += name_field;                                                      /// /..../SPECIAL_FLIGHT_RULES_IN_THE_VICINITY_OF_GRAND_CANYON_NATIONAL_PARK__AZ"
        std::string ac_filename = "SHAPE";                                          // "SHAPE"
        ac_filename += "_";                                                         // "SHAPE_"
        ac_filename += std::to_string(shape_nbr);                                   // "SHAPE_703"
        ac_filename += "_seg_";                                                     // "SHAPE_703_seg_"
        ac_filename += std::to_string(sn);                                          // "SHAPE_703_seg_0"

        std::string texture_path  = SHPDBF->paths->OpenEaglePath.c_str();
                    texture_path += SHPDBF->paths->OpenEagleMastersTextures_Path.c_str();

        std::string texture_name = "unknown texture";
        if ( strcmp(local_type_field,"SFRA") == 0) texture_name = "SATA_SFRA";
        if ( strcmp(local_type_field,"SPEC_AT_RULES") == 0) texture_name = "SATA_SPEC_AT_RULES";

        bool nanbug = SHPDBF->generate_ac_xml_and_update_stg_files_current_segment(
          sn,
          &models_and_objects_path,
          &short_ac_path,
          &full_ac_path,
          &ac_filename,
          &texture_path,
          &texture_name,
          lower_altitude,
          upper_altitude
          );
        if (nanbug) {
          printf("warning nanbug on the prowle\n");
          exit(1);
        }
        current = SHPDBF->next_segment();
        if (current < 0 ) SHPDBF->reset_segment_list();
      }
    }
    bool test = SHPDBF->can_advance_dbf_shp();
    if (test == true) SHPDBF->advance_dbf_shp();  //basically will run off list after processing last record, inhibits waltzing off list end(s)
  }
  printf("num_SFC %d\n",num_SFC);
  printf("num_AGL %d\n",num_AGL);
}

