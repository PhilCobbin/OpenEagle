/***************************************************************
 * Name:      fix.hxx
 * Purpose:   read summarize and generate files related to faa fix.txt fix data.
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-11
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
#ifndef FIX
#define FIX
#include <cstddef>
#include "../avl_tree/avl_tree.hxx"
//#include <stdio.h>
#include <stdlib.h>

class fix 
{
  public:
    
    void read_fix_data(); 
    void read_fix1_data();
    void read_fix2_data();
    void read_fix3_data();
    void read_fix4_data();
    void read_fix5_data();

    void summarize_FADDS_fix();
    void summarize_fix1();
    void summarize_fix2();
    void summarize_fix3();
    void summarize_fix4();
    void summarize_fix5();
    void generate_FlightGear_fix_dat();
    
    void summarize_fix();
    void generate_fix_files();
    void free_fix_data();  

    void add_awy_fix(char * awy, char * awy_id, char * awy_mea);
    void update_ils_fix_mm_information (char * ils_mm_name, char * ils_mm_type, char * ils_apt_site_id, char * ils_rwy_id);
    void update_ils_fix_om_information (char * ils_om_name, char * ils_om_type, char * ils_apt_site_id, char * ils_rwy_id); 


  private:

    struct awy_fix_record {
      awy_fix_record * awy_next;
      char fix_on_awy[6];  //  V1234
      char fix_awy_alt[5];
    };

    struct ils_fix_mm_record {
      ils_fix_mm_record * ils_mm_next;
      char fix_ils_mm_type[16];
      char fix_ils_mm_apt_site_id[12];
      char fix_ils_mm_rwy_id[4];  
    };

    struct ils_fix_om_record {
      ils_fix_om_record * ils_om_next;
      char fix_ils_om_type[16];
      char fix_ils_om_apt_site_id[12];
      char fix_ils_om_rwy_id[4];  
    };

    struct fix5_record {
      fix5_record * next_fix5;
      char fix_name[31];
      char fix_st_name[31];
      char icao_region_code[3];
      char charting[23];      
    };
    struct fix4_record {
      fix4_record * next_fix4;
      char fix_name[31];
      char fix_st_name[31];
      char icao_region_code[3];
      char field_label[101];
      char remarks[301];      
    };
    struct fix3_record {
      fix3_record * next_fix3;
      char fix_name[31];
      char fix_st_name[31];
      char icao_region_code[3];
      char loc_id[24];
    };
    struct fix2_record {
      fix2_record * next_fix2;
      char fix_name[31];
      char fix_st_name[31];
      char icao_region_code[3];
      char loc_id[24];
    };

    struct fix1_record {
      fix1_record * next_fix1;
      fix2_record * fix2_list;
      fix3_record * fix3_list;
      fix4_record * fix4_list;
      fix5_record * fix5_list;
      char fix_id[31];
      char fix_state_name[31];
      char icao_region_code[3];
      char latitude[15];
      char longitude[15];
      char catagory[4];
      char ident_facility_course_component[23];
      char ident_apt_runway[23];
      char previous_name[34];
      char charting_info[39];
      char published[2];
      char use[16];
      char natl_id[6];
      char high_jurisdiction[5];
      char low_jurisdiction[5];
      char fix_ctry[31];
      char pitch[2];
      char _catch[2];
      char sua_atcaa[2];
    };    

     struct fix_record {
      fix_record     * next_fix;
      awy_fix_record * awy_list;                            
      ils_fix_mm_record * ils_mm_list;
      ils_fix_om_record * ils_om_list;
      char fix_name[31];             //0
      char fix_stname[21];          //30
      char fix_f_lat[15];            //50
      char fix_f_long[15];           //64

      char c_lat_deg[3];
      char c_lat_min[3];
      char c_lat_sec[7];
      char ns[2];

      char c_long_deg[4]; 
      char c_long_min[3];
      char c_long_sec[7];
      char ew[2];

      double latitude;
      double longitude;

      char fix_chart[10][23];        //81  dx=22  10 possible
      char fix_id_tp_rad_nav[4][23]; //301 dx=2  4 possible sets..
      char fix_id_tp_rad_ils[2][23]; //389 dx=2  2 possible sets..
      char fix_charting_info[39];    //546
      char fix_published[2];         //584
      char fix_use[16];              //585
      char fix_nas_id[6];            //600
    };

    fix_record * test_ptr;


    char NASRfixbuffer[1431];
    fix_record * head_fix;
    fix_record * current_fix;
    fix_record * last_fix;

    
    fix1_record * head_fix1;
    fix1_record * current_fix1;
    fix1_record * last_fix1;

    fix2_record * head_fix2;
    fix2_record * current_fix2;
    fix2_record * last_fix2;
    
    fix3_record * head_fix3;
    fix3_record * current_fix3;
    fix3_record * last_fix3;
    
    fix4_record * head_fix4;
    fix4_record * current_fix4;
    fix4_record * last_fix4;
    
    fix5_record * head_fix5;
    fix5_record * current_fix5;
    fix5_record * last_fix5;
   
    
    awy_fix_record * head_awy_fix;
    awy_fix_record * current_awy_fix;

    ils_fix_mm_record * head_ils_mm_fix;
    ils_fix_mm_record * current_ils_mm_fix;

    ils_fix_om_record * head_ils_om_fix;
    ils_fix_om_record * current_ils_om_fix;
    struct avl_tree_node *head_avl_fix;
  public: 
    inline fix(void)
    {
      head_avl_fix  = initialize_avl_tree();
      head_fix      = NULL;
      last_fix      = NULL;

      head_fix1     = NULL;
      last_fix1     = NULL;

      head_fix2     = NULL;
      last_fix2     = NULL;

      head_fix3     = NULL;
      last_fix3     = NULL;

      head_fix4     = NULL;
      last_fix4     = NULL;

      head_fix5     = NULL;
      last_fix5     = NULL;
      
    } 
    inline ~fix(void)
    {
      erase_avl_tree(head_avl_fix); 
      free_fix_data();
    } 

    
};
#endif
