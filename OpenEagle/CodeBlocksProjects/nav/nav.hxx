/***************************************************************
 * Name:      fix.hxx
 * Purpose:   read summarize and generate files related to faa nav.txt navaid data.
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2005
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
#ifndef NAV
#define NAV
#include <cstddef>
#define SG_FEET_TO_METER    0.3048
class nav 
{
  public:
    void read_nav_data(); 
    void summarize_nav();
    void generate_nav_files();
    void free_nav_data();

  private:
    void read_nav1_data();
    void read_nav3_data();  
    void read_nav4_data();
    void read_nav5_data();

    struct nav1_record{
//      nav1_record * next_nav1;
 
      int nav_type_code;  // decoded from fields
      int i_nav_freq;     // decoded

//     char nav_rtype[5];           //0
//     bool nav_1_record;
     // NAV 1 records
      char nav_id[5];        
      char nav_type[21]; 
      char ofc_nav_id[5];
      char nav_name[31]; 
      char nav_st[3];    
      char nav_public[2];
      char nav_class[12];
      char nav_artcc[31];
      char nav_lat_sec[12]; 
      char nav_long_sec[12];
      char nav_accuracy[2]; 
      char tacan_lat_sec[12];  
      char tacan_long_sec[12]; 
      char nav_elev[8];
      char radio_call[31]; 
      char nav_channel[5]; 
      char nav_freq[7];    
      char nav_fan[25];    
      char nav_fss_id[5];    
      char nav_fss_name[31]; 
    };
    struct nav3_record{
      nav3_record * next_nav3;
//     bool nav3_record;
      char nav_fix[19][34];    //28  dx = 33  19 records...
    };

    struct nav4_record{
      nav4_record * next_nav4;
//      bool nav4_record;
      char nav_hold_pat[19][34];  // 28 dx=33  19 records...
    };

    struct nav5_record{
      nav5_record * next_nav5;
//    bool nav5_record;
      char nav_fan_mkr[24][27];      //28   dx=26   24 fan markers
    };

    struct nav_record {
      nav_record * next_nav;
      nav1_record * nav1_list;
      nav3_record * nav3_list;
      nav4_record * nav4_list;
      nav5_record * nav5_list;
     };

    nav_record * a_nav;
    nav_record * head_nav;
    nav_record * current_nav;
    nav_record * last_nav;

    nav1_record * a_nav1;
    nav1_record * head_nav1;
    nav1_record * current_nav1;
    nav1_record * last_nav1;

    nav3_record * a_nav3;
    nav3_record * head_nav3;
    nav3_record * current_nav3;
    nav3_record * last_nav3;

    nav4_record * a_nav4;
    nav4_record * head_nav4;
    nav4_record * current_nav4;
    nav4_record * last_nav4;

    nav5_record * a_nav5;
    nav5_record * head_nav5;
    nav5_record * current_nav5;
    nav5_record * last_nav5;

  public: 
    inline nav(void)
    {
      head_nav      = NULL;
    } 
    inline ~nav(void)
    {
      free_nav_data();
    } 



};
#endif
