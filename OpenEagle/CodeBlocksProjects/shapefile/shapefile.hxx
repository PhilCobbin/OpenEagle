/***************************************************************
 * Name:      shapefile.hxx
 * Purpose:   record structures for capturing both dbf and shp data and generating 3d models of Airspace elements into FlightGear Scenery database
 * Created:   2021-04-11
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
#ifndef _SHAPEFILE_HXX
#define _SHAPEFILE_HXX
#include <string.h>
#include <string>
#include "../system_io/system_io.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
/* ----------------------------------------------------------------------- */
/*      OpenEagle Hack: read_dbf and read_shape are hacked versions        */
/*      from shapelib-1.5.0                                                */
/*      from shapelib-1.5.0 uses                                           */
/*        shpopen.c  dbfopen.c  safileio.c  shptree.c  sbnsearch.c         */
/* ----------------------------------------------------------------------- */


#define MAX_LINE_LENGTH_FEET 5280

class shapefile
{
  public:
//    OpenEaglePaths paths;
    OpenEaglePaths *paths;
    void initialize_dbf();
    int read_limit;

    int read_dbf(char * file);
    int read_shp(char * file);


    void adjust_vertices_for_max_line_length();
    void set_segments();

    void summarize_dbf(char * fn);
    void summarize_shp(char * fn);
    void summarize_shp_vertices(char * fn);
    void summarize_shp_segments(char * fn);

    char * get_current_data_for_field(int n);

    void reset_dbf_shp();        // set both to head of lists
      int get_shp_nentities();
      int get_dbf_num_records();
      bool can_advance_dbf_shp();
    bool advance_dbf_shp();          // advance dbf and shp records, return false if one or both goto NULL;
      int get_dbf_shape_shape_nbr();
      int get_dbf_shape_record_nbr();
      int get_shape_n_vertices();    //
      int get_shape_num_segments();    //

    void reset_vertice_list();       // set vertice to head of list for current shape
    int next_vertice();              // traverse vertice list one node return return vertice_nbr will force an exit if previous went NULL.

      double get_vertice_x();        //
      double get_vertice_y();        //
      double get_vertice_long();     //  x as longitude
      double get_vertice_lat();      //  y as latitude

    void reset_segment_list();
      int get_n_segments();          //for current shape how many segments.

    int next_segment();              // traverse shape's segment list returning segment number
      int get_seg_n_vertices();      // how many vertices in current segment

   void reset_segments_vertice_list();       // set vertice to first vertice of segment

    // generation of ac xml and updating stg files
    // ac file needs
    //   path
    //   name
    //   texture path  i.e. where example of say class_d.png files etc are.
    //   texture name
    //   lower altitude
    //   upper altitude
/**
    bool generate_ac_xml_and_update_stg_files_current_segment(
                                                              std::string * ac_path,
                                                              std::string * ac_filename,
                                                              std::string * texture_path,
                                                              std::string * texture_name,
                                                              double low_alt,
                                                              double high_alt
                                                              );
**/
    bool generate_ac_xml_and_update_stg_files_current_segment(
                                                              int set_nbr,
                                                              std::string * models_and_objects_path,
                                                              std::string * short_ac_path,
                                                              std::string * full_ac_path,
                                                              std::string * ac_filename,
                                                              std::string * texture_path,
                                                              std::string * texture_name,
                                                              double low_alt,
                                                              double high_alt
                                                              );

  shapefile( class OpenEaglePaths * paths_ptr)
  {
    paths = paths_ptr;
  }
  private:

    std::string summaries_path;
    std::string OpenEagle_Airports_path;


// shapefile structures to retain dbf and shp information
    //dbf structures
    struct field_record {
      struct field_record * next_field;
      char field_name[200];    //names of fields: NAME, UPPER_VAL....SECTOR
    };

    struct field_record * field_list;
    struct field_record * temp_field_list;

    struct field_data {
      struct field_data * next_data;
      int field_nbr;
      char field_data_char[300];   //data list attached to specific recor #  values of NAME, UPPER_VAL...SECTOR
      // sua field  V 21 TIMESOFUSE,C,238
    };

    struct field_data * first_data_list;
    struct field_data * current_data_list;
    struct field_data * temp_data_list;

    struct record_data {
      int record_nbr;                   //  put records in a list and capture number for audit/cross referencing
      struct field_data * data;         //  because there are duplicates in NAME field will append record_nbr to open eagle files to handle dup's
      struct record_data * next_record;
    };

    struct record_data * first_record;
    struct record_data * current_record;
    struct record_data * temp_record;

    struct dbf_record {
      int num_records;
      int num_fields;
      struct field_record * field_list;      // list of fields
      struct record_data * record_list;           // list of records (with attached) field_data elements for each relevant field
    };

    struct dbf_record *dbf_data;  // head node of dbf file information

  //  shp structures
    struct vertice_record {
      struct vertice_record * next_vertice;
      int vertice_nbr;
      double x;  // x as longitude
      double y;  // y as latitude
    };
    struct vertice_record * first_vertice;
    struct vertice_record * last_vertice;
    struct vertice_record * current_vertice;
    struct vertice_record * temp_vertice;

// segment structures for dealing with FlightGear's tile system
    struct segment_record {
        segment_record * next_segment;
        int segment_n;
        long int tile_index;
        double tile_ctr_latitude;
        double tile_ctr_longitude;
        char tile_nbr_str[40];
        char tile_path_str[40];
        struct vertice_record * seg_vertice_start;
        struct vertice_record * seg_vertice_end;
        int seg_n_vertices;
    };

    struct segment_record * current_segment;  // null start null after free_segments();
    struct segment_record * temp_segment;
    int n_segment;
    //int seg_n_vertices;



    struct shape_record {
      struct shape_record * next_shape;
      int shape_nbr;
      int shape_nvertices;
      struct vertice_record * vertice_list;
      int num_segments;
      struct segment_record * segment_list;
    };

    struct shape_record * first_shape;
    struct shape_record * current_shape;
    struct shape_record * temp_shape;

    struct shp_record {
      int nentities;
      struct shape_record * shape_list;

    };

    struct shp_record * shp_data;

    public:

    shapefile() {
//      printf("shapefile() initializaton:\n");
      read_limit = -1;
/**
    ///  paths.setupOpenEaglePaths();
      summaries_path  = paths.OpenEaglePath.c_str();
      summaries_path += "/Update/Summaries";

      OpenEagle_Airports_path  = paths.OpenEagle_FlightGear_Path.c_str();
      OpenEagle_Airports_path += "/Scenery/Models/Airports/";

      std::string command = "mkdir -p ";
      command += summaries_path;
      bool shapefile_init_Summaries_path_ok = system_io(&command);
      if (!shapefile_init_Summaries_path_ok) {
        printf("shapefile() failed to make path [Summaries] for string [%s]\ncommand.c_str()\n",command.c_str());
        exit(1);
      }
      summaries_path += "/";
      **/

      field_list = NULL;
      temp_field_list = NULL;

      first_data_list = NULL;
      current_data_list = NULL;
      temp_data_list = NULL;

      first_record = NULL;
      current_record = NULL;
      temp_record = NULL;

      dbf_data=NULL;
      initialize_dbf();

      current_segment = NULL;
      temp_segment = NULL;
      n_segment = 0;
  //    printf("shapefile() finishes\n");

    }

    ~shapefile()
    {
      printf("~shapefile():\n");
      printf("freeing up dbf records\n");
      field_list = dbf_data->field_list;
      while (field_list != NULL) {
        temp_field_list = field_list;
        field_list = field_list->next_field;
        free ( temp_field_list );
      }
      current_record = dbf_data->record_list;
      while (current_record != NULL) {
        temp_record = current_record;
        current_data_list = current_record->data;
        while (current_data_list != NULL) {
          temp_data_list = current_data_list;
          current_data_list = current_data_list->next_data;
          free( temp_data_list );
        }
        current_record = current_record->next_record;
        free( temp_record );
      }
      free ( dbf_data );
      printf("freeing up shp records\n");
      current_shape = shp_data->shape_list;
      while (current_shape != NULL) {
        temp_shape = current_shape;
        current_vertice = current_shape->vertice_list;
        while (current_vertice != NULL) {
          temp_vertice = current_vertice;
          current_vertice = current_vertice->next_vertice;
          free( temp_vertice );
        }
        current_segment = current_shape->segment_list;
        while (current_segment != NULL) {
          temp_segment = current_segment;
          current_segment = current_segment->next_segment;
          free ( current_segment );
        }
        current_shape = current_shape->next_shape;
        free( temp_shape );
      }
      free ( shp_data );
    }
};

#endif
