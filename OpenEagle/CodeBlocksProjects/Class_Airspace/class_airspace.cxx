/***************************************************************
 * Name:      class_airspace.cxx
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
#include "../Class_Airspace/class_airspace.hxx"
#include "stdlib.h"

void class_airspace::read_dbf(char * shape_file_path)
{
  printf("read_dbf(%s)\n",shape_file_path);
/************************************************************************/
/*                              read_dbf(...)                           */
/************************************************************************/
  std::string dbf_file = shape_file_path;
  dbf_file += "/Class_Airspace";
  printf("dbf_file [%s]\n",dbf_file.c_str());
  int ret;
  char file_bug[200];

  strcpy(file_bug,dbf_file.c_str());
  printf("file_bug [%s]\n",file_bug);
//  ret = SHPDBF->read_dbf((char *)dbf_file.c_str());
  ret = SHPDBF->read_dbf((char *)&file_bug);
  if (ret!=0) {
    printf("error while processing maindbf\n");
    exit(1);
  }

//  char dbf_file_summary[] ="dbf_file_summary";
//  SHPDBF->summarize_dbf(dbf_file_summary);
}

void class_airspace::read_dbf()
{
/************************************************************************/
/*                              read_dbf(...)                           */
/************************************************************************/
  std::string dbf_file = paths->OpenEaglePath.c_str();
  printf("dbf_file [%s]\n",dbf_file.c_str());
  int ret;
  char file_bug[200];

  strcpy(file_bug,dbf_file.c_str());
  printf("file_bug [%s]\n",file_bug);
//  ret = SHPDBF->read_dbf((char *)dbf_file.c_str());
  ret = SHPDBF->read_dbf((char *)&file_bug);
  if (ret!=0) {
    printf("error while processing maindbf\n");
    exit(1);
  }

//  char dbf_file_summary[] ="dbf_file_summary";
//  SHPDBF->summarize_dbf(dbf_file_summary);
}
void class_airspace::read_shp(char * shape_file_path)
{
/************************************************************************/
/*                              read_shp(...)                           */
/************************************************************************/
  printf("read_shp(%s)\n",shape_file_path);
  shp_file = shape_file_path;
  shp_file += "/Class_Airspace";
  printf("shp_file [%s]\n",shp_file.c_str());
  int ret;
  char file_bug[200];
  strcpy(file_bug,shp_file.c_str());
  printf("file_bug [%s]\n",file_bug);
//  ret = SHPDBF->read_shp((char *)shp_file.c_str());
  ret = SHPDBF->read_shp((char *)&file_bug);
  if (ret!=0) {
    printf("error while processing mainshp\n");
    exit(1);
  }

  SHPDBF->adjust_vertices_for_max_line_length();
  SHPDBF->set_segments();
  SHPDBF->reset_dbf_shp();

  n_dbf =  SHPDBF->get_dbf_num_records();
  n_shp =  SHPDBF->get_shp_nentities();
}

void class_airspace::write_NASR_class_airspace(bool do_terminal_io) //,OpenEaglePaths)
{

  terminal_io = do_terminal_io;
  class_b_cnt = 0;
  class_c_cnt = 0;
  class_d_cnt = 0;
  class_e2_cnt = 0;
  class_e3_cnt = 0;
  class_e4_cnt = 0;
//  printf("n_dbf %d\n",n_dbf);
//  return;

  for (int i = 0; i < n_dbf; i++) {
    int shape_nbr = SHPDBF->get_dbf_shape_shape_nbr();
    int n_vertices = SHPDBF->get_shape_n_vertices();
    int record_nbr = SHPDBF->get_dbf_shape_record_nbr();
    char * ident_field = SHPDBF->get_current_data_for_field(CA_IDENT_FIELD);

    double elevation = 0.0;
    bool have_apt_elevation = apt->lookup_airport_elevation(ident_field,&elevation);
    if (!have_apt_elevation) { /// class E
//        printf("apt.lookup_airport_elevation([%s]..) failed for shape %d\n",ident_field,i);
    }

    char * lower_val_field = SHPDBF->get_current_data_for_field(CA_LOWER_VAL_FIELD);
    char * lower_uom_field = SHPDBF->get_current_data_for_field(CA_LOWER_UOM_FIELD);
    char * lower_code_field = SHPDBF->get_current_data_for_field(CA_LOWER_CODE_FIELD);

    char * upper_val_field = SHPDBF->get_current_data_for_field(CA_UPPER_VAL_FIELD);
    char * upper_uom_field = SHPDBF->get_current_data_for_field(CA_UPPER_UOM_FIELD);
    char * upper_code_field = SHPDBF->get_current_data_for_field(CA_UPPER_CODE_FIELD);

    char * class_field = SHPDBF->get_current_data_for_field(CA_CLASS_FIELD);

    if ( strcmp(class_field, "CLASS_B") == 0 ) {
      class_b_cnt++;
    }
    if ( strcmp(class_field, "CLASS_C") == 0 ) {
      class_c_cnt++;
    }
    if ( strcmp(class_field, "CLASS_D") == 0) {
      class_d_cnt++;
    }
    if ( strcmp(class_field, "CLASS_E2") == 0 ) {
      class_e2_cnt++;
    }
    if ( strcmp(class_field, "CLASS_E3") == 0 ) {
      class_e3_cnt++;
    }
    if ( strcmp(class_field, "CLASS_E4") == 0 ) {
      class_e4_cnt++;
    }

    if ( (strcmp(class_field, "CLASS_B") == 0 ) ||
         (strcmp(class_field, "CLASS_C") == 0 ) ||
         (strcmp(class_field, "CLASS_D") == 0 ) ) {
//        (strcmp(class_field, "CLASS_E2") == 0) ||
//        (strcmp(class_field, "CLASS_E3") == 0) ||
//        (strcmp(class_field, "CLASS_E4") == 0) ) {
      double lower_altitude;
      bool lower_altitude_is_surface = false;
      double upper_altitude;
      printf("\n");
      printf("Record/Shape %5d is for [%s] airspace\n",i,class_field);
      printf("     Airport Identifier is [%s]\n",ident_field);
      printf("     lower limits %s %s %s\n", lower_val_field,lower_uom_field,lower_code_field);
      printf("     upper limits %s %s %s\n", upper_val_field,upper_uom_field,upper_code_field);
      if ( strcmp(lower_code_field,"SFC") == 0  ){
        printf("     lower limit is surface\n");
        lower_altitude_is_surface = true;
      }
      else {
        if ( strcmp(lower_code_field,"MSL" ) == 0 ) {
           lower_altitude = std::stod(lower_val_field);
           printf("    lower limit is %8.1f MSL\n",lower_altitude);
        }
      }
      if ( strcmp(upper_code_field,"MSL") == 0  ){
           upper_altitude = std::stod(upper_val_field);
           printf("    Upper limit is %8.1f MSL\n",upper_altitude);
      }
      else {
        printf("upper_code_field was not MSL\n");
        exit(1);
      }

/* -------------------------------------------------------------------- */
/*  Now to build directories, write files, and copy texture files       */
/*  into what will be /Scenery/Models/Airspace and /Scenery/Objects/... */
/* -------------------------------------------------------------------- */

      int n_segments = SHPDBF->get_shape_num_segments();
      SHPDBF->reset_segment_list();
      for (int sn = 0; sn < n_segments; sn++) {
        int current = sn;
        std::string models_and_objects_path = paths->OpenEagleWrite_ModelsAndObjectsPath;
        std::string short_ac_path = paths->class_airspace_subpath;
        short_ac_path += "/";
        short_ac_path += class_field;
        short_ac_path += "/";
        short_ac_path += ident_field;


        std::string full_ac_path  = paths->OpenEagleWrite_ModelsAndObjectsPath;
                    full_ac_path += "/Models/Class_Airspace";

        full_ac_path += "/";
        full_ac_path += class_field;
        full_ac_path += "/";
        full_ac_path += ident_field;

        std::string ac_filename = "SHAPE";
        ac_filename += "_";                                                      /// "SHAPE_"
        ac_filename += std::to_string(shape_nbr);                                /// "SHAPE_703"
        ac_filename += "_seg_";                                                  /// "SHAPE_703_"
        ac_filename += std::to_string(sn);                                       /// "SHAPE_703_0"
        std::string texture_path = paths->OpenEaglePath.c_str();
        texture_path += paths->OpenEagleMastersTextures_Path.c_str();     /// "/Masters/Airspace_Textures";
        std::string texture_name = class_field;

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
          printf("Error: nanbug\n");
          exit(1);
        }
        current = SHPDBF->next_segment();
        if (current < 0 ) SHPDBF->reset_segment_list();
      }
    }
    bool test = SHPDBF->can_advance_dbf_shp();
    if (test == true) SHPDBF->advance_dbf_shp();  //basically will run off list after processing last record, inhibits waltzing off list end(s)
  }
  printf("class_b_cnt %d\n",class_b_cnt);
  printf("class_c_cnt %d\n",class_c_cnt);
  printf("class_d_cnt %d\n",class_d_cnt);
  printf("class_e2_cnt %d\n",class_e2_cnt);
  printf("class_e3_cnt %d\n",class_e3_cnt);
  printf("class_e4_cnt %d\n",class_e4_cnt);


}

void class_airspace::update_class_airspace(bool do_terminal_io)
{
  terminal_io = do_terminal_io;
//  make_flightgear_path_addition();
  class_b_cnt = 0;
  class_c_cnt = 0;
  class_d_cnt = 0;
  class_e2_cnt = 0;
  class_e3_cnt = 0;
  class_e4_cnt = 0;
//  printf("n_dbf %d\n",n_dbf);
//  return;

  for (int i = 0; i < n_dbf; i++) {
    int shape_nbr = SHPDBF->get_dbf_shape_shape_nbr();
    int n_vertices = SHPDBF->get_shape_n_vertices();
    int record_nbr = SHPDBF->get_dbf_shape_record_nbr();
    char * ident_field = SHPDBF->get_current_data_for_field(CA_IDENT_FIELD);

    double elevation = 0.0;
    bool have_apt_elevation = apt->lookup_airport_elevation(ident_field,&elevation);
    if (!have_apt_elevation) { /// class E
//        printf("apt.lookup_airport_elevation([%s]..) failed for shape %d\n",ident_field,i);
    }

    char * lower_val_field = SHPDBF->get_current_data_for_field(CA_LOWER_VAL_FIELD);
    char * lower_uom_field = SHPDBF->get_current_data_for_field(CA_LOWER_UOM_FIELD);
    char * lower_code_field = SHPDBF->get_current_data_for_field(CA_LOWER_CODE_FIELD);

    char * upper_val_field = SHPDBF->get_current_data_for_field(CA_UPPER_VAL_FIELD);
    char * upper_uom_field = SHPDBF->get_current_data_for_field(CA_UPPER_UOM_FIELD);
    char * upper_code_field = SHPDBF->get_current_data_for_field(CA_UPPER_CODE_FIELD);

    char * class_field = SHPDBF->get_current_data_for_field(CA_CLASS_FIELD);

    if ( strcmp(class_field, "CLASS_B") == 0 ) {
      class_b_cnt++;
    }
    if ( strcmp(class_field, "CLASS_C") == 0 ) {
      class_c_cnt++;
    }
    if ( strcmp(class_field, "CLASS_D") == 0) {
      class_d_cnt++;
    }
    if ( strcmp(class_field, "CLASS_E2") == 0 ) {
      class_e2_cnt++;
    }
    if ( strcmp(class_field, "CLASS_E3") == 0 ) {
      class_e3_cnt++;
    }
    if ( strcmp(class_field, "CLASS_E4") == 0 ) {
      class_e4_cnt++;
    }

    if ( (strcmp(class_field, "CLASS_B") == 0 ) ||
         (strcmp(class_field, "CLASS_C") == 0 ) ||
         (strcmp(class_field, "CLASS_D") == 0 ) ) {
//        (strcmp(class_field, "CLASS_E2") == 0) ||
//        (strcmp(class_field, "CLASS_E3") == 0) ||
//        (strcmp(class_field, "CLASS_E4") == 0) ) {
      double lower_altitude;
      bool lower_altitude_is_surface = false;
      double upper_altitude;
      printf("\n");
      printf("Record/Shape %5d is for [%s] airspace\n",i,class_field);
      printf("     Airport Identifier is [%s]\n",ident_field);
      printf("     lower limits %s %s %s\n", lower_val_field,lower_uom_field,lower_code_field);
      printf("     upper limits %s %s %s\n", upper_val_field,upper_uom_field,upper_code_field);
      if ( strcmp(lower_code_field,"SFC") == 0  ){
        printf("     lower limit is surface\n");
        lower_altitude_is_surface = true;
      }
      else {
        if ( strcmp(lower_code_field,"MSL" ) == 0 ) {
           lower_altitude = std::stod(lower_val_field);
           printf("    lower limit is %8.1f MSL\n",lower_altitude);
        }
      }
      if ( strcmp(upper_code_field,"MSL") == 0  ){
           upper_altitude = std::stod(upper_val_field);
           printf("    Upper limit is %8.1f MSL\n",upper_altitude);
      }
      else {
        printf("upper_code_field was not MSL\n");
        exit(1);
      }

/* -------------------------------------------------------------------- */
/*  Now to build directories, write files, and copy texture files       */
/*  into what will be /Scenery/Models/Airspace and /Scenery/Objects/... */
/* -------------------------------------------------------------------- */

      int n_segments = SHPDBF->get_shape_num_segments();
      SHPDBF->reset_segment_list();
      for (int sn = 0; sn < n_segments; sn++) {
        int current = sn;
/// .OpenEagle/Update resource paths.
        std::string models_and_objects_path = paths->OpenEagleWrite_ModelsAndObjectsPath;
        std::string short_ac_path = paths->class_airspace_subpath.c_str();
        short_ac_path += "/";
        short_ac_path += class_field;
        short_ac_path += "/";
        short_ac_path += ident_field;

        std::string full_ac_path  = paths->OpenEagleWrite_ModelsAndObjectsPath;
                    full_ac_path += paths->class_airspace_subpath.c_str();

        full_ac_path += "/";
        full_ac_path += class_field;
        full_ac_path += "/";
        full_ac_path += ident_field;

        std::string ac_filename = "SHAPE";
        ac_filename += "_";
        ac_filename += std::to_string(shape_nbr);
        ac_filename += "_seg_";
        ac_filename += std::to_string(sn);
        std::string texture_path = paths->OpenEaglePath.c_str();
        texture_path += paths->OpenEagleMastersTextures_Path.c_str();
        std::string texture_name = class_field;

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
          printf("Error: nanbug\n");
          exit(1);
        }
        current = SHPDBF->next_segment();
        if (current < 0 ) SHPDBF->reset_segment_list();
      }
    }
    bool test = SHPDBF->can_advance_dbf_shp();
    if (test == true) SHPDBF->advance_dbf_shp();  //basically will run off list after processing last record, inhibits waltzing off list end(s)
  }
  printf("class_b_cnt %d\n",class_b_cnt);
  printf("class_c_cnt %d\n",class_c_cnt);
  printf("class_d_cnt %d\n",class_d_cnt);
  printf("class_e2_cnt %d\n",class_e2_cnt);
  printf("class_e3_cnt %d\n",class_e3_cnt);
  printf("class_e4_cnt %d\n",class_e4_cnt);
}
