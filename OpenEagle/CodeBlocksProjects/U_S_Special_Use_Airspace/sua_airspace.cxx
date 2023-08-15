/***************************************************************
 * Name:      sua_Airspace.cxx.cpp
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

#include "stdlib.h"
#include "../U_S_Special_Use_Airspace/sua_airspace.hxx"
#include "../data_conversion/data_conversion.hxx"

void sua_airspace::initialize_sua_masters_path()
{

printf("initialize_sua_masters_path()::\n");
/************************************************************************/
/*                     initialize Sua path as needed                    */
/*                       this will be a lookup for sfc/agl              */
/*                       altitudes to base .ac files on                 */
/*                                                                      */
/************************************************************************/
//  std::string str_elevation_;

  OpenEagleSua_path = paths->OpenEaglePath.c_str();
  OpenEagleSua_path +=paths->OpenEagleMastersUpdateSua_Path.c_str(); //

  std::string command = "mkdir -p ";
  command += OpenEagleSua_path;
  printf("mkdir - p call: [%s]\n",command.c_str());
  bool sua_path_ok = system_io(&command);
  if (!sua_path_ok) {
    printf("system command failed to create Sua path [%s]\n",command.c_str());
    exit(1);
  }
  printf("...fini\n");
}

void sua_airspace::read_dbf(char * filepath)
{
/************************************************************************/
/*                              read_dbf(...)                           */
/************************************************************************/
  printf("read_dbf(%s)\n",filepath);
  fn_sua = filepath;
  fn_sua += "/Special_Use_Airspace.dbf";
  printf("fn_sua [%s]\n",fn_sua.c_str());
  int ret = SHPDBF->read_dbf((char *) fn_sua.c_str());
  if (ret!=0) {
    printf("error while processing maindbf\n");
    exit(1);
  }
  SHPDBF->summarize_dbf("summarize_SUA_dbf");
}

void sua_airspace::read_shp(char * filepath)
{
/************************************************************************/
/*                              read_shp(...)                           */
/************************************************************************/
  printf("read_shp(%s)\n",filepath);
  fn_sua = filepath;
  fn_sua += "/Special_Use_Airspace.shp";
  printf("fn_sua [%s]\n",fn_sua.c_str());
  int ret = SHPDBF->read_shp((char *) fn_sua.c_str());
  if (ret!=0) {
    printf("error while processing mainshp\n");
    exit(1);
  }
  SHPDBF->summarize_shp_vertices("SUA_shp_summary");

  SHPDBF->adjust_vertices_for_max_line_length();

  SHPDBF->set_segments();

/* -------------------------------------------------------------------- */
/*  Some SUA's will have a lower boundary of surface                    */
/*  (1) note in summary log and use 0 msl as the surface                */
/*                                                                      */
/*  ideally use unique identifier for SFC to visit in flightgear and    */
/*  get relevant surface altitude and put that in                       */
/*        /SUA/'name'/elevation.txt in string form                      */
/* -------------------------------------------------------------------- */

/**  2021-01 fields in U-S-_Special_Use_Airspac shapefile
 A 0 GLOBAL_ID,C,36
 B 1 NAME,C,27                 ABEL EAST MOA  (issue...convert "ABEL EAST MOA" to "ABEL_EAST_MOA" as filename. but add also shape number
 C 2 TYPE_CODE,C,3             A (ALERT), D(DANGER) MOA, P(PROHIBITED) R(RESTRICTED) W(WARNING) ADA
 D 3 CLASS,C,1
 E 4 UPPER_DESC,C,3
 F 5 UPPER_VAL,C,6             -9999, 0, 1000
 G 6 UPPER_UOM,C,2             FL FT
 H 7 UPPER_CODE,C,7            STD MSL  UNLTD
 I 8 LOWER_DESC,C,5            ANI OTHER
 J 9 LOWER_VAL,C,5              0, 9000
 K 10 LOWER_UOM,C,2            FT FL
 L 11 LOWER_CODE,C,3           SFC, STD, MSL
 M 12 LEVEL_CODE,C,1           B,U,L
 N 13 CITY,C,59
 O 14 STATE,C,2
 P 15 COUNTRY,C,13
 Q 16 CONT_AGENT,C,66
 R 17 COMM_NAME,C,36
 S 18 SECTOR,C,60              EXCLUSION NOTES
 T 19 ONSHORE,C,1
 U 20 EXCLUSION,C,1
 V 21 TIMESOFUSE,C,238
 W 22 GMTOFFSET,C,3
 X 23 DST_CODE,C,1
 Y 24 REMARKS,C,200
 Z 25 AK_LOW,N,1,0        numeric
AA 26 AK_HIGH,N,1,0       numeric
AB 27 US_LOW,N,1,0        numeric
AC 28 US_HIGH,N,1,0       numeric
AD 29 OBJECTID,N,4,0           CORRESPONDS TO SHAPE NUMBER but note numbering starts at 1
AE 30 US_AREA,N,1,0       numeric
AF 31 PACIFIC,N,1,0       numeric
AG 32 Shape__Are,N,24,15  numeric
AH 33 Shape__Len,N,24,15  numeric

**/
}

void sua_airspace::write_sua_airspace(bool do_terminal_io)
{
  terminal_io = do_terminal_io;
  SHPDBF->reset_dbf_shp();

  n_dbf =  SHPDBF->get_dbf_num_records();
  n_shp =  SHPDBF->get_shp_nentities();

  printf("n_dbf %d n_shp %d\n",n_dbf,n_shp);
  num_SFC = 0;
  num_AGL = 0;
  for (int i = 0; i < n_dbf; i++) {
    printf("%d of n_dbf %d\n",i,n_dbf);
    double elevation = 0.0;
    bool have_elevation = false;
    int shape_nbr = SHPDBF->get_dbf_shape_shape_nbr();
    int n_vertices = SHPDBF->get_shape_n_vertices();
    int n_segments = SHPDBF->get_shape_num_segments();
    int record_nbr = SHPDBF->get_dbf_shape_record_nbr();

    printf("  shape_nbr %d n_vertices %d n_segments %d record_nbr %d\n",shape_nbr,n_vertices,n_segments,record_nbr);
    char * name_field = SHPDBF->get_current_data_for_field(SUA_NAME_FIELD);
    char * type_code_field = SHPDBF->get_current_data_for_field(SUA_TYPE_CODE_FIELD);

     printf(" name_field [%s] type_code_field [%s]\n",name_field,type_code_field);

    char * lower_val_field = SHPDBF->get_current_data_for_field(SUA_LOWER_VAL_FIELD);
    char * lower_uom_field = SHPDBF->get_current_data_for_field(SUA_LOWER_UOM_FIELD);
    char * lower_code_field = SHPDBF->get_current_data_for_field(SUA_LOWER_CODE_FIELD);

    printf(" lower_val_field [%s] lower_uom_field [%s] lower_code_field [%s]\n",lower_val_field,lower_uom_field,lower_code_field);

    char * upper_val_field = SHPDBF->get_current_data_for_field(SUA_UPPER_VAL_FIELD);
    char * upper_uom_field = SHPDBF->get_current_data_for_field(SUA_UPPER_UOM_FIELD);
    char * upper_code_field = SHPDBF->get_current_data_for_field(SUA_UPPER_CODE_FIELD);

    printf(" upper_val_field [%s] upper_uom_field [%s] upper_code_field [%s]\n",upper_val_field,upper_uom_field,upper_code_field);

    char * state_field = SHPDBF->get_current_data_for_field(SUA_STATE_FIELD);
    printf(" state_field [%s]\n",state_field);
    bool state_field_null = false;
    if ( strcmp(state_field,"(NULL)") == 0) {
       printf("warning: state_field was (NULL) possibly CANADA\n");
       state_field_null = true;
    }

    char * sector_field = SHPDBF->get_current_data_for_field(SUA_SECTOR_FIELD);

    printf(" sector_field [%s]\n",sector_field);
    safe_line(name_field);  // kill of the O'Neills of the world
    printf("got past safe_line(name_field)\n");
    replace_space_with_under_score(name_field);
    printf("got past replace_space_with_under_score(name_field)\n");

    printf(" NAME [%28s]",name_field);
    printf(" type_code [%3s]",type_code_field);
    printf(" shape [%4d]",shape_nbr);
    printf(" lower fields [%6s]:[%3s]:[%3s]",lower_val_field,lower_uom_field,lower_code_field);
    printf(" upper fields [%6s]:[%3s]:[%5s]",upper_val_field,upper_uom_field,upper_code_field);
    printf(" st [%s]\n",state_field);
/**
    if (!state_field_null) {
      printf("!state_field_null\n");
      std::string elevation_file = paths->OpenEagleWrite_ModelsAndObjectsPath; //filepath; //OpenEagleSua_path;
      elevation_file += "/Special_Use_Airspace/";
      elevation_file += type_code_field;
      elevation_file += "/";
      elevation_file += state_field;
      elevation_file += "/";
      elevation_file += name_field;
      elevation_file += "/";
      elevation_file += std::to_string(i); // shape number

      command = "mkdir -p ";  /// make sua_path if needed
      command += elevation_file.c_str();
      printf("mkdir - p call: [%s]\n",command.c_str());
      bool sua_path_ok = system_io(&command);
      if (!sua_path_ok) {
        printf("system command failed for sua_path string [%s]\n",command.c_str());
        exit(1);
      }
      elevation_file += "/";
      elevation_file += "elevation.txt";
      FILE * fp_elevation = fopen(elevation_file.c_str(),"r");
      if (fp_elevation == NULL) {
        printf("write elevation file to [%s]\n",elevation_file.c_str());
        fp_elevation = fopen(elevation_file.c_str(),"w++");
        fprintf(fp_elevation,"0.0\n"); /// write one with 0.0 of elevation
        fclose(fp_elevation);
      }
      else {
        have_elevation = true;
        printf("     elevation file [%s] exists",elevation_file.c_str());
        printf("     opened it\n");
        std:: string double_string = "";
        bool eol=false;
        while (!eol) {
          char test = fgetc(fp_elevation);
          if (test != '\n') double_string += test;
          else eol=true;
       //   printf("        double_string [%s]\n",double_string.c_str());
        }
        elevation = stod(double_string,NULL);
        printf(" elevation %0.1f\n",elevation);
        printf("\n");
//        if (lower_altitude_is_surface) lower_altitude = elevation;
          fclose(fp_elevation);
      }
    }
    else {
      printf("state field is NULL\n");
    }
**/

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
    printf("lower_code_field\n");
    double lower_altitude;
    lower_altitude = strtod(lower_val_field,NULL);
    if ( strcmp(lower_code_field,"SFC") == 0) {
        num_SFC++;
        if (lower_altitude > 0.0) {
            num_AGL++;
            printf(" add elevation %f to lower_altitude %f", elevation,lower_altitude);
            lower_altitude = lower_altitude + elevation;
            printf("lower_altitude -> %f",lower_altitude);
            printf(" AGL:");
        }
        else lower_altitude = elevation;
    }
    else {
        if ( strcmp(lower_code_field,"STD") == 0) {
          lower_altitude *= 100.0;
          lower_code_field = "MSL";
        }
    }

    double upper_altitude;
    printf("upper_code_field\n");
    if ( strcmp(upper_code_field,"UNLTD") == 0) {
       upper_altitude = 100000.0;
       upper_code_field = "MSL";
    }
    else {
        upper_altitude = strtod(upper_val_field,NULL);
        if ( strcmp(upper_code_field,"STD") == 0) {
          upper_altitude *= 100.0;
          upper_code_field = "MSL";
        }
    }

    printf(" altitudes: %7.0f - %7.0f\n",lower_altitude, upper_altitude);

/* -------------------------------------------------------------------- */
/*  Now to build directories, write files, and copy texture files       */
/*  into what will be /Scenery/Models/Airspace and /Scenery/Objects/... */
/* -------------------------------------------------------------------- */
    printf("now to build directories\n");

    SHPDBF->reset_segment_list();

    printf("survived SHPDBF->reset_segment_list()\n");
    if (!state_field_null) {
      for (int sn = 0; sn < n_segments; sn++) {
        printf("          seg %d\n",sn);
        int current = sn;
        std::string models_and_objects_path = paths->OpenEagleWrite_ModelsAndObjectsPath;
        std::string short_ac_path = paths->SUA_airspace_subpath.c_str();
        short_ac_path += "/";
        short_ac_path += type_code_field;
        short_ac_path += "/";
        short_ac_path += name_field;

        printf("  short_ac_path [%s]\n",short_ac_path.c_str());

        std::string full_ac_path  = paths->OpenEagleWrite_ModelsAndObjectsPath.c_str();
                    full_ac_path += paths->SUA_airspace_subpath.c_str();
        full_ac_path += "/";
        full_ac_path += type_code_field;
        full_ac_path += "/";
        full_ac_path += name_field;
        printf("  full_ac_path [%s]\n",full_ac_path.c_str());

        std::string ac_filename = "SHAPE";                                  // "SHAPE"
        ac_filename += "_";                                                 // "SHAPE_"
        ac_filename += std::to_string(shape_nbr);                           // "SHAPE_703"
        ac_filename += "_seg_";                                             // "SHAPE_703_seg_"
        ac_filename += std::to_string(sn);                                  // "SHAPE_703_seg_0"
        std::string texture_path  = paths->OpenEaglePath.c_str();
                    texture_path += paths->OpenEagleMastersTextures_Path.c_str();
        std::string texture_name = "unknown texture";
        if ( strcmp(type_code_field,"A") == 0) texture_name = "SUA_ALERT";
        if ( strcmp(type_code_field,"ADA") == 0) texture_name = "SUA_ADA";
        if ( strcmp(type_code_field,"MOA") == 0) texture_name = "SUA_MOA";
        if ( strcmp(type_code_field,"P") == 0) texture_name = "SUA_PROHIBITED";
        if ( strcmp(type_code_field,"R") == 0) texture_name = "SUA_RESTRICTED";
        if ( strcmp(type_code_field,"W") == 0) texture_name = "SUA_WARNING";

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

void sua_airspace::update_sua_airspace(bool do_terminal_io)
{
  printf("update_sua_airspace(...)\n");
  terminal_io = do_terminal_io;

  SHPDBF->reset_dbf_shp();

  printf("got past reset_dbf_shp()\n");

  n_dbf =  SHPDBF->get_dbf_num_records();
  n_shp =  SHPDBF->get_shp_nentities();

  printf("n_dbf %d n_shp %d\n",n_dbf,n_shp);
  num_SFC = 0;
  num_AGL = 0;
  for (int i = 0; i < n_dbf; i++) {
    printf("%d of n_dbf %d\n",i,n_dbf);
    double elevation = 0.0;
    bool have_elevation = false;
    int shape_nbr = SHPDBF->get_dbf_shape_shape_nbr();
    int n_vertices = SHPDBF->get_shape_n_vertices();
    int n_segments = SHPDBF->get_shape_num_segments();
    int record_nbr = SHPDBF->get_dbf_shape_record_nbr();

    printf("  shape_nbr %d n_vertices %d n_segments %d record_nbr %d\n",shape_nbr,n_vertices,n_segments,record_nbr);
    char * name_field = SHPDBF->get_current_data_for_field(SUA_NAME_FIELD);
    char * type_code_field = SHPDBF->get_current_data_for_field(SUA_TYPE_CODE_FIELD);

     printf(" name_field [%s] type_code_field [%s]\n",name_field,type_code_field);

    char * lower_val_field = SHPDBF->get_current_data_for_field(SUA_LOWER_VAL_FIELD);
    char * lower_uom_field = SHPDBF->get_current_data_for_field(SUA_LOWER_UOM_FIELD);
    char * lower_code_field = SHPDBF->get_current_data_for_field(SUA_LOWER_CODE_FIELD);

    printf(" lower_val_field [%s] lower_uom_field [%s] lower_code_field [%s]\n",lower_val_field,lower_uom_field,lower_code_field);

    char * upper_val_field = SHPDBF->get_current_data_for_field(SUA_UPPER_VAL_FIELD);
    char * upper_uom_field = SHPDBF->get_current_data_for_field(SUA_UPPER_UOM_FIELD);
    char * upper_code_field = SHPDBF->get_current_data_for_field(SUA_UPPER_CODE_FIELD);

    printf(" upper_val_field [%s] upper_uom_field [%s] upper_code_field [%s]\n",upper_val_field,upper_uom_field,upper_code_field);

    char * state_field = SHPDBF->get_current_data_for_field(SUA_STATE_FIELD);
    printf(" state_field [%s]\n",state_field);
    bool state_field_null = false;
    if ( strcmp(state_field,"(NULL)") == 0) {
        printf("warning: state_field was (NULL) possibly CANADA\n");
       state_field_null = true;
    }

    char * sector_field = SHPDBF->get_current_data_for_field(SUA_SECTOR_FIELD);

    printf(" sector_field [%s]\n",sector_field);
    safe_line(name_field);  // kill of the O'Neills of the world
    printf("got past safe_line(name_field)\n");
    replace_space_with_under_score(name_field);
    printf("got past replace_space_with_under_score(name_field)\n");

    printf(" NAME [%28s]",name_field);
    printf(" type_code [%3s]",type_code_field);
    printf(" shape [%4d]",shape_nbr);
    printf(" lower fields [%6s]:[%3s]:[%3s]",lower_val_field,lower_uom_field,lower_code_field);
    printf(" upper fields [%6s]:[%3s]:[%5s]",upper_val_field,upper_uom_field,upper_code_field);
    printf(" st [%s]\n",state_field);

    if (!state_field_null) {
      printf("!state_field_null\n");
      std::string elevation_file = OpenEagleSua_path;
      elevation_file += "/";
      elevation_file += type_code_field;
      elevation_file += "/";
      elevation_file += state_field;
      elevation_file += "/";
      elevation_file += name_field;
      elevation_file += "/";
      elevation_file += std::to_string(i); // shape number

      command = "mkdir -p ";  /// make sua_path if needed
      command += elevation_file.c_str();
      printf("mkdir - p call: [%s]\n",command.c_str());
      bool sua_path_ok = system_io(&command);
      if (!sua_path_ok) {
        printf("system command failed for sua_path string [%s]\n",command.c_str());
        exit(1);
      }
      elevation_file += "/";
      elevation_file += "elevation.txt";
      FILE * fp_elevation = fopen(elevation_file.c_str(),"r");
      if (fp_elevation == NULL) {
        printf("write elevation file to [%s]\n",elevation_file.c_str());
        fp_elevation = fopen(elevation_file.c_str(),"w++");
        fprintf(fp_elevation,"0.0\n"); /// write one with 0.0 of elevation
        fclose(fp_elevation);
      }
      else {
        have_elevation = true;
        printf("     elevation file [%s] exists",elevation_file.c_str());
        printf("     opened it\n");
        std:: string double_string = "";
        bool eol=false;
        while (!eol) {
          char test = fgetc(fp_elevation);
          if (test != '\n') double_string += test;
          else eol=true;
       //   printf("        double_string [%s]\n",double_string.c_str());
        }
        elevation = stod(double_string,NULL);
        printf(" elevation %0.1f\n",elevation);
        printf("\n");
//        if (lower_altitude_is_surface) lower_altitude = elevation;
          fclose(fp_elevation);
      }
    }
    else {
      printf("state field is NULL\n");
    }


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
    printf("lower_code_field\n");
    double lower_altitude;
    lower_altitude = strtod(lower_val_field,NULL);
    if ( strcmp(lower_code_field,"SFC") == 0) {
        num_SFC++;
        if (lower_altitude > 0.0) {
            num_AGL++;
            printf(" add elevation %f to lower_altitude %f", elevation,lower_altitude);
            lower_altitude = lower_altitude + elevation;
            printf("lower_altitude -> %f",lower_altitude);
            printf(" AGL:");
        }
        else lower_altitude = elevation;
    }
    else {
        if ( strcmp(lower_code_field,"STD") == 0) {
          lower_altitude *= 100.0;
          lower_code_field = "MSL";
        }
    }

    double upper_altitude;
    printf("upper_code_field\n");
    if ( strcmp(upper_code_field,"UNLTD") == 0) {
       upper_altitude = 100000.0;
       upper_code_field = "MSL";
    }
    else {
        upper_altitude = strtod(upper_val_field,NULL);
        if ( strcmp(upper_code_field,"STD") == 0) {
          upper_altitude *= 100.0;
          upper_code_field = "MSL";
        }
    }

    printf(" altitudes: %7.0f - %7.0f\n",lower_altitude, upper_altitude);

/* -------------------------------------------------------------------- */
/*  Now to build directories, write files, and copy texture files       */
/*  into what will be /Scenery/Models/Airspace and /Scenery/Objects/... */
/* -------------------------------------------------------------------- */
    printf("now to build directories\n");

    SHPDBF->reset_segment_list();

    if (!state_field_null) {
      for (int sn = 0; sn < n_segments; sn++) {
        printf("          seg %d",sn);
        int current = sn;
        std::string models_and_objects_path = paths->OpenEagleWrite_ModelsAndObjectsPath.c_str();
        std::string short_ac_path = SHPDBF->paths->SUA_airspace_subpath.c_str();
        short_ac_path += "/";
        short_ac_path += type_code_field;
        short_ac_path += "/";
        short_ac_path += name_field;
        printf("sn %d short_ac_path [%s]\n",sn,(char *)short_ac_path.c_str());

        std::string full_ac_path  = paths->OpenEagleWrite_ModelsAndObjectsPath.c_str();
                    full_ac_path += paths->SUA_airspace_subpath.c_str();
        full_ac_path += "/";
        full_ac_path += type_code_field;
        full_ac_path += "/";
        full_ac_path += name_field;
        printf("sn %d full_ac_path [%s]\n",sn,(char *)full_ac_path.c_str());

        std::string ac_filename = "SHAPE";                                  // "SHAPE"
        ac_filename += "_";                                                 // "SHAPE_"
        ac_filename += std::to_string(shape_nbr);                           // "SHAPE_703"
        ac_filename += "_seg_";                                             // "SHAPE_703_seg_"
        ac_filename += std::to_string(sn);                                  // "SHAPE_703_seg_0"
        std::string texture_path  = SHPDBF->paths->OpenEaglePath.c_str();
                    texture_path += SHPDBF->paths->OpenEagleMastersTextures_Path.c_str();
        std::string texture_name = "unknown texture";
        if ( strcmp(type_code_field,"A") == 0) texture_name = "SUA_ALERT";
        if ( strcmp(type_code_field,"ADA") == 0) texture_name = "SUA_ADA";
        if ( strcmp(type_code_field,"MOA") == 0) texture_name = "SUA_MOA";
        if ( strcmp(type_code_field,"P") == 0) texture_name = "SUA_PROHIBITED";
        if ( strcmp(type_code_field,"R") == 0) texture_name = "SUA_RESTRICTED";
        if ( strcmp(type_code_field,"W") == 0) texture_name = "SUA_WARNING";

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
