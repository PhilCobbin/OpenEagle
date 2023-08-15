/***************************************************************
 * Name:      fix.cxx
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
#include "fix.hxx"
//#include "term_io.hxx"
#include <cstddef>
#include "../read_data/read_data.hxx"
//#include <simgear/misc/sg_path.hxx>
#include "../subpath/subpath.hxx"
#include "../paths/paths.hxx"
#include "../avl_tree/avl_tree.hxx"
//#include "options.hxx"
#include "../data_conversion/data_conversion.hxx"
#include <math.h>

void fix:: update_ils_fix_mm_information (char * ils_mm_name, char * ils_mm_type, char * ils_apt_site_id, char * ils_rwy_id)
{
  struct avl_tree_node *avl_ptr;
  avl_ptr = search_avl_tree ((char *)&ils_mm_name, false, head_avl_fix);
  if (avl_ptr !=NULL) {
    fix_record*  test_ptr;
    test_ptr = (fix_record*)avl_ptr->data_ptr;
    ils_fix_mm_record * ils_mm_list;
    ils_mm_list = test_ptr->ils_mm_list;
    if (ils_mm_list == NULL) {
      ils_mm_list = new(ils_fix_mm_record);
      test_ptr->ils_mm_list = ils_mm_list;
    }
    else {
      while (ils_mm_list->ils_mm_next != NULL) {
        ils_mm_list = ils_mm_list->ils_mm_next;
      }
      ils_mm_list->ils_mm_next = new(ils_fix_mm_record);
      ils_mm_list = ils_mm_list->ils_mm_next;
    }
    ils_mm_list->ils_mm_next = NULL;
    strcpy((char *)&ils_mm_list->fix_ils_mm_type,ils_mm_type);
    strcpy((char *)&ils_mm_list->fix_ils_mm_apt_site_id,ils_apt_site_id);
    strcpy((char *)&ils_mm_list->fix_ils_mm_rwy_id,ils_rwy_id);
  }
}


void fix:: update_ils_fix_om_information (char * ils_om_name, char * ils_om_type, char * ils_apt_site_id, char * ils_rwy_id)
{
  struct avl_tree_node *avl_ptr;
  avl_ptr = search_avl_tree (ils_om_name, false, head_avl_fix);
  if (avl_ptr !=NULL) {
    fix_record *  test_ptr;
    test_ptr = (fix_record *)avl_ptr->data_ptr;
    ils_fix_om_record * ils_om_list;
    ils_om_list = test_ptr->ils_om_list;
    if (ils_om_list == NULL) {
      ils_om_list = new(ils_fix_om_record);
      test_ptr->ils_om_list = ils_om_list;
    }
    else {
      while (ils_om_list->ils_om_next != NULL) {
        ils_om_list = ils_om_list->ils_om_next;
      }
      ils_om_list->ils_om_next = new(ils_fix_om_record);
      ils_om_list = ils_om_list->ils_om_next;
    }
    ils_om_list->ils_om_next = NULL;
    strcpy((char *)&ils_om_list->fix_ils_om_type,ils_om_type);
    strcpy((char *)&ils_om_list->fix_ils_om_apt_site_id,ils_apt_site_id);
    strcpy((char *)&ils_om_list->fix_ils_om_rwy_id,ils_rwy_id);
  }
}

void fix::add_awy_fix(char * awy, char * awy_id, char * awy_mea)
{
  struct avl_tree_node *avl_ptr;
  avl_ptr = search_avl_tree ((char *)&awy, false, head_avl_fix);
  if (avl_ptr !=NULL) {
    test_ptr = (fix::fix_record*)avl_ptr->data_ptr;
    fix::awy_fix_record * awy_list;
    awy_list = test_ptr->awy_list;
    if (awy_list == NULL) {
      awy_list = new(awy_fix_record);
      test_ptr->awy_list = awy_list;
    }
    else {
      while (awy_list->awy_next != NULL) awy_list = awy_list->awy_next;
      awy_list->awy_next = new(awy_fix_record);
      awy_list = awy_list->awy_next;
    }
    awy_list->awy_next = NULL;
    strcpy((char *)&awy_list->fix_on_awy,awy_id);  //  V1234
    strcpy((char *)&awy_list->fix_awy_alt,awy_mea);
  }

}



void fix::read_fix1_data()
{
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->fix_id,30,4);                           //AN0030 00005  NONE    RECORD IDENTIFIER (FIX ID)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->fix_state_name,30,34);                  //AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->icao_region_code,2,64);                 //AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->latitude,14,66);                        //AN0014 00067  FX4     GEOGRAPHICAL LATITUDE OF THE FIX.
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->longitude,14,80);                       //AN0014 00081  FX5     GEOGRAPHICAL LONGITUDE OF THE FIX.
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->catagory,3,94);                         //AN0003 00095  FX20    CATEGORIZES THE FIX AS A MILITARY (MIL),
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->ident_facility_course_component,22,97); //AN0022 00098  FX27    3 OR 4 LETTER IDENT*FACILITY TYPE*DIRECTION OR
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->ident_apt_runway,22,119);               //AN0022 00120  FX27    AIRPORT ID*APPROACH-END-RWY*DISTANCE OF RADAR COMPONENT
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->previous_name,33,141);                  //AN0033 00142  FX33    PREVIOUS NAME OF THE FIX BEFORE IT WAS RENAMED
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->charting_info,38,174);                  //AN0038 00175  FX31    CHARTING INFORMATION.
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->published,1,212);                       //AN0001 00213  FX34    FIX TO BE PUBLISHED (Y = YES OR N = NO)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->use,15,213);                            //AN0015 00214  FX36    FIX USE
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->natl_id,5,228);                         //AN0005 00229  FX37    NATIONAL AIRSPACE SYSTEM(NAS) IDENTIFIER FOR
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->high_jurisdiction,4,233);               //AN0004 00234  FX91    DENOTES HIGH ARTCC AREA OF JURISDICTION.
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->low_jurisdiction,4,237);                //AN0004 00238  NONE    DENOTES LOW ARTCC AREA OF JURISDICTION.
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->fix_ctry,30,241);                       //AN0030 00242  NONE    FIX COUNTRY NAME (OUTSIDE CONUS)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->pitch,1,271);                           //AN0001 00272  NONE    PITCH (Y = YES OR N = NO)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->_catch,1,272);                          //AN0001 00273  NONE    CATCH (Y = YES OR N = NO)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix1->sua_atcaa,1,273);                       //AN0001 00274  NONE    SUA/ATCAA (Y = YES OR N = NO)
}


void write_FGlat(FILE *fp,double lat)
{
  int sign=1;
  if (lat < 0.0) sign =-1;
  lat *=sign;
  int ilat = lat;
  double dlat = lat - ilat;
  int i6dlat = dlat*1000000;
  if (sign < 0) fprintf(fp,"-"); else fprintf(fp," ");
  if (lat<10.0) fprintf(fp,"%09.6f ",lat); else fprintf(fp,"%9.6f ",lat);
 // fprintf(fp,"%d%.6f ",ilat,dlat);


}
void write_FGlon(FILE *fp,double lon)
{
  int sign=1;
  if (lon < 0.0) sign =-1;
  lon *=sign;
  int ilon = lon;
  double dlon = lon - ilon;
  int i6dlon = dlon*1000000;
  if (sign < 0) fprintf(fp,"-"); else fprintf(fp," ");
  if (lon>=100.0) {
    fprintf(fp,"%10.6f ",lon);
  }
  else {
     if (lon<100.0) fprintf(fp,"%010.6f ",lon); else  fprintf(fp,"%009.6f ",lon);
  }
  //fprintf(fp,"%d%.6f",ilon,dlon);
}

void fix::generate_FlightGear_fix_dat()
{
  std::string fn = "fix.dat";
  FILE * fp;

  std::string d_FlightGear_fix;
  d_FlightGear_fix = output_base;
  d_FlightGear_fix += "/fix.dat";
  fp  = fopen( d_FlightGear_fix.c_str(), "w++" );
  if (fp == NULL) {
    printf("could not open fix.dat at [%s]\n",d_FlightGear_fix.c_str());
    exit(1);
  }

  std::string d_NASR_README;
  d_NASR_README = NASR_base;
  d_NASR_README += "/NASR/current/README.txt";
  FILE * fpr;
  fpr = fopen(d_NASR_README.c_str(),"r");

  read_field(fpr,(char *)&NASRfixbuffer,sizeof(NASRfixbuffer),tc2);
  //set_field((char *)&NASRfixbuffer,(char *)&current_fix5->fix_name,30,4);

  fprintf(fp,"I\napt.dat file replacement for FlightGear for use with OpenEagle:  Produced from %s\n\n",NASRfixbuffer);
  current_fix1 = head_fix1;
  while (current_fix1!=NULL) {
    //summarize_fix1();
    current_fix5 = current_fix1->fix5_list;
    double lat = NASR_f_coord_to_d((char *) current_fix1->latitude);
    double lon = NASR_f_coord_to_d((char *)current_fix1->longitude);
    if (current_fix5!=NULL) {
      std::string fix_id = remove_trailing_spaces((char *)current_fix1->fix_id);
      if (strlen(fix_id.c_str())<=5) {
        write_FGlat(fp,lat);
        write_FGlon(fp,lon);
        fprintf(fp,"%s\n",current_fix1->fix_id);
      }
    }
    current_fix1 = current_fix1->next_fix1;
  }
  fprintf(fp,"99\n");
  fclose(fp);


}

void fix:: summarize_fix1()
{
//  if (strncmp(current_fix1->published,"Y",1)==0) {
    printf("FIX1: id[%s] st[%s] lat[%10.6f] lon[%11.6f] cat[%s] course[%s] rwy[%s] chart[%s] pub[%s] use[%s] ctry[%s] sua[%s]\n",
         current_fix1->fix_id,
         current_fix1->fix_state_name,
         NASR_f_coord_to_d((char *) current_fix1->latitude),
         NASR_f_coord_to_d((char *)current_fix1->longitude),
         current_fix1->catagory,
         current_fix1->ident_facility_course_component,
         current_fix1->ident_apt_runway,
         current_fix1->charting_info,
         current_fix1->published,
         current_fix1->use,
         current_fix1->fix_ctry,
         current_fix1->sua_atcaa);
  //}


}




void fix::read_fix2_data()
{
  set_field((char *)&NASRfixbuffer,(char *)&current_fix2->fix_name,30,4);         //AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix2->fix_st_name,30,34);     //AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix2->icao_region_code,2,64); //AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRfixbuffer,(char *)&current_fix2->loc_id,23,66);          //AN0023 00067  FX22    LOCATION-IDENTIFIER, FACILITY TYPE, AND RADIAL
}
void fix:: summarize_fix2()
{
  printf("  FIX2: name[%s] st[%s] loc_id[%s]\n",current_fix2->fix_name, current_fix2->fix_st_name,current_fix2->loc_id);

}


void fix::read_fix3_data()
{
  set_field((char *)&NASRfixbuffer,(char *)&current_fix3->fix_name,30,4);         //AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix3->fix_st_name,30,34);     //AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix3->icao_region_code,2,64); //AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRfixbuffer,(char *)&current_fix3->loc_id,23,66);          //AN0023 00067  FX26    3 OR 4 LETTER IDENT*FACILITY TYPE*DIRECTION OR COURSE
}

void fix:: summarize_fix3()
{
  printf("  FIX3: name[%s] st[%s] loc_id[%s]\n",current_fix3->fix_name, current_fix3->fix_st_name,current_fix3->loc_id);
}

void fix::read_fix4_data()
{
    /**
      struct fix4_record {
      fix4_record * next_fix4;
      char fix_name[31];
      char fix_st_name[31];
      char icao_region_code[3];
      char field_label[101];
      char remarks[301];
    };

    **/
  set_field((char *)&NASRfixbuffer,(char *)&current_fix4->fix_name,30,4);         //AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix4->fix_st_name,30,34);     //AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix4->icao_region_code,2,64); //AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRfixbuffer,(char *)&current_fix4->field_label,100,66);    //AN0100 00067  NONE    FIELD LABEL
  set_field((char *)&NASRfixbuffer,(char *)&current_fix4->remarks,300,66);         //AN0300 00167  NONE    REMARK TEXT
}

void fix:: summarize_fix4()
{
  printf("  FIX4: name[%s] st[%s] field[%s] remark[%s]\n",current_fix4->fix_name, current_fix4->fix_st_name,current_fix4->field_label,current_fix4->remarks);

}


void fix::read_fix5_data()
{
    /**
    struct fix5_record {
      fix5_record * next_fix5;
      char fix_name[31];
      char fix_st_name[31];
      char icao_region_code[3];
      char charting[23];
    };
    **/
  set_field((char *)&NASRfixbuffer,(char *)&current_fix5->fix_name,30,4);         //AN0030 00005  NONE    RECORD IDENTIFIER (FIX NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix5->fix_st_name,30,34);     //AN0030 00035  NONE    RECORD IDENTIFIER (FIX STATE NAME)
  set_field((char *)&NASRfixbuffer,(char *)&current_fix5->icao_region_code,2,64); //AN0002 00065  NONE    ICAO REGION CODE
  set_field((char *)&NASRfixbuffer,(char *)&current_fix5->charting,22,66);        //AN0022 00067  FX21    CHART ON WHICH FIX IS TO BE DEPICTED
}

void fix:: summarize_fix5()
{
  printf("  FIX5: name[%s] st[%s] charting[%s]\n",current_fix5->fix_name, current_fix5->fix_st_name,current_fix5->charting);


}

void fix::read_fix_data()
{
  FILE * fp_fix;
  FILE * fp_fix_dat;
  char fix_rtype[5];
  bool done=false;
  int last_space;
  int nfix=0;
  int nfixpublished=0;
  std::string d_NASR_fix;
  d_NASR_fix = NASR_base;
  d_NASR_fix += "/NASR/current/FIX.txt";

//  SGPath d_NASR_fix(NASR_base);
//  d_NASR_fix.append("./FIX.txt");
  fp_fix  = fopen( d_NASR_fix.c_str(), "r" );
  if (fp_fix == NULL) {
    printf("could not open FIX.txt at [%s]\n",d_NASR_fix.c_str());
    exit(1);
  }
//  head_fix = new(fix_record);
//  last_fix = head_fix;

  printf("Reading fix Records  :                          Published:\n");

  while (!done) {
      /**
    current_fix = new(fix_record);
    current_fix->awy_list = NULL;
    current_fix->ils_mm_list = NULL;
    current_fix->ils_om_list = NULL;
    current_fix->next_fix=NULL;
    last_fix->next_fix = current_fix;
    last_fix = current_fix;
**/
    read_field(fp_fix,(char *)&NASRfixbuffer,sizeof(NASRfixbuffer),tc2);
    set_field((char *)&NASRfixbuffer,(char *)&fix_rtype,4,0);
    if (strncmp(fix_rtype,"FIX1",4)==0) {
      head_fix2 = last_fix2 = NULL;
      head_fix3 = last_fix3 = NULL;
      head_fix4 = last_fix4 = NULL;
      head_fix5 = last_fix5 = NULL;

      current_fix1 = new(fix1_record);
      if (head_fix1 == NULL) {
        head_fix1=last_fix1 = current_fix1;
      }
      else {
          last_fix1->next_fix1 = current_fix1;
          last_fix1 = current_fix1;
      }
      current_fix1-> next_fix1 = NULL;
      current_fix1-> fix2_list = NULL;
      current_fix1-> fix3_list = NULL;
      current_fix1-> fix4_list = NULL;
      current_fix1-> fix5_list = NULL;
      read_fix1_data();
    }
    else {
      if  (strncmp(fix_rtype,"FIX2",4)==0) {
        current_fix2 = new(fix2_record);
        if (head_fix2 == NULL) {
          head_fix2=last_fix2 = current_fix2;
          current_fix1->fix2_list = current_fix2;
        }
        else {
          last_fix2->next_fix2 = current_fix2;
          last_fix2 = current_fix2;
        }
        current_fix2-> next_fix2 = NULL;
        read_fix2_data();
      }
      else {
        if  (strncmp(fix_rtype,"FIX3",4)==0) {
          current_fix3 = new(fix3_record);
          if (head_fix3 == NULL) {
            head_fix3=last_fix3 = current_fix3;
            current_fix1->fix3_list = current_fix3;
          }
          else {
            last_fix3->next_fix3 = current_fix3;
            last_fix3 = current_fix3;
          }
          current_fix3-> next_fix3 = NULL;
          read_fix3_data();
        }
        else {
          if  (strncmp(fix_rtype,"FIX4",4)==0) {
            current_fix4 = new(fix4_record);
            if (head_fix4 == NULL) {
              head_fix4=last_fix4 = current_fix4;
              current_fix1->fix4_list = current_fix4;
            }
            else {
              last_fix4->next_fix4 = current_fix4;
              last_fix4 = current_fix4;
            }
            current_fix4-> next_fix4 = NULL;
            read_fix4_data();
          }
          else {
            if  (strncmp(fix_rtype,"FIX5",4)==0) {
              current_fix5 = new(fix5_record);
              if (head_fix5 == NULL) {
                head_fix5=last_fix5 = current_fix5;
                current_fix1->fix5_list = current_fix5;
              }
              else {
                last_fix5->next_fix5 = current_fix5;
                last_fix5 = current_fix5;
              }
              current_fix5-> next_fix5 = NULL;
              read_fix5_data();
            }
          }
        }
      }
    }
  /**

    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_name,30,0);             //0
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_stname,20,30);             //0
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_f_lat,14,50);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_f_long,14,64);           //64

    set_field((char *)&NASRfixbuffer,(char *)&current_fix->c_lat_deg,2,50);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->c_lat_min,2,53);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->c_lat_sec,6,56);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->ns,1,62);            //50

    set_field((char *)&NASRfixbuffer,(char *)&current_fix->c_long_deg,3,64);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->c_long_min,2,68);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->c_long_sec,6,71);            //50
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->ew,1,77);            //50

    current_fix->latitude  = strtod(current_fix->c_lat_deg,NULL ) + strtod(current_fix->c_lat_min,NULL )/60.0 + strtod(current_fix->c_lat_sec,NULL )/3600.0;
    current_fix->longitude = strtod(current_fix->c_long_deg,NULL) + strtod(current_fix->c_long_min,NULL)/60.0 + strtod(current_fix->c_long_sec,NULL)/3600.0;

    if (strncmp(current_fix->ns,"S",1)==0) current_fix->latitude = -current_fix->latitude;
    if (strncmp(current_fix->ew,"W",1)==0) current_fix->longitude = -current_fix->longitude;

    int dx=81;
    for (int i=0; i<10; i++) {
      set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_chart[i],22,dx);        //81  dx=22  10 possible
      dx+=22;
    }
    dx=301;
    for (int i=0; i<4; i++) {
      set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_id_tp_rad_nav[i],22,dx); //301 dx=22  4 possible sets..
      dx+=22;
    }
    dx=389;
    for (int i=0; i<2; i++) {
      set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_id_tp_rad_ils[i],22,dx); //389 dx=22  2 possible sets..
      dx+=22;
    }

    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_charting_info,38,546);    //546
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_published,1,584);         //584
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_use,15,585);              //585
    set_field((char *)&NASRfixbuffer,(char *)&current_fix->fix_nas_id,5,600);            //600

    if (current_fix->fix_published[0]=='Y') {
      nfixpublished++;
      struct avl_tree_node *avl_ptr;
      avl_ptr = search_avl_tree ((char *)&current_fix->fix_nas_id, false, head_avl_fix);
      if (avl_ptr==NULL) {
        avl_ptr = search_avl_tree ((char *)&current_fix->fix_nas_id, true, head_avl_fix);
        avl_ptr->data_ptr = (void *) current_fix;
      }
      else {
         printf("ERROR! double fix_nas_id\n");
         exit(1);
      }

    }
    **/
    nfix++;
    if (!nextok(fp_fix)) done=true;
  }
  fclose(fp_fix);

  printf("nfix %d\n",nfix);
  printf("nfixpublished %d\n",nfixpublished);
  printf("finished reading data\n");
}

void fix::summarize_fix()
{
  FILE * fp_ds;
  fp_ds  = fopen("summary_fix.txt", "w+" );
  current_fix = head_fix->next_fix;
  while (current_fix!=NULL) {
    if (strncmp(current_fix->fix_published,"Y",1)==0) {
      fprintf(fp_ds,"name[%31s] stname[%21s] nas_id[%6s] latitude[%12.8f] longitude[%12.8f]",//  charting info [%s]\n",
        current_fix->fix_name,
        current_fix->fix_stname,
        current_fix->fix_nas_id,
        current_fix->latitude,
        current_fix->longitude
      );
      for (int i = 0; i<10; i++ ) if (strncmp(current_fix->fix_chart[i]," ",1) != 0) fprintf(fp_ds,"chart[%s] ",current_fix->fix_chart[i]);
      fprintf(fp_ds,"\n");
      awy_fix_record * awy_list;
      awy_list = current_fix->awy_list;
      while (awy_list !=NULL) {
        fprintf(fp_ds,"     awy[%6s] alt[%5s]\n",awy_list->fix_on_awy,awy_list->fix_awy_alt);
        awy_list = awy_list->awy_next;
      }
      ils_fix_mm_record * ils_mm_list;
      ils_mm_list = current_fix->ils_mm_list;
      while (ils_mm_list !=NULL) {
        fprintf(fp_ds,"     ils_mm_type[%s] ils_apt_site_id[%5s] fix_ils_rwy_id[%s]\n",
          ils_mm_list->fix_ils_mm_type,
          ils_mm_list->fix_ils_mm_apt_site_id,
          ils_mm_list->fix_ils_mm_rwy_id);
        ils_mm_list = ils_mm_list->ils_mm_next;
      }
      ils_fix_om_record * ils_om_list;
      ils_om_list = current_fix->ils_om_list;
      while (ils_om_list !=NULL) {
        fprintf(fp_ds,"     ils_om_type[%s] ils_apt_site_id[%5s] fix_ils_rwy_id[%s]\n",
          ils_om_list->fix_ils_om_type,
          ils_om_list->fix_ils_om_apt_site_id,
          ils_om_list->fix_ils_om_rwy_id);
        ils_om_list = ils_om_list->ils_om_next;
      }
    }
    current_fix=current_fix->next_fix;
  }
  fclose (fp_ds);
}
void fix::generate_fix_files()
{
}



void fix:: summarize_FADDS_fix()
{
  current_fix1 = head_fix1;
  while (current_fix1!=NULL) {
    summarize_fix1();

    current_fix2 = current_fix1->fix2_list;
    while (current_fix2!=NULL) {
      summarize_fix2();
      current_fix2 = current_fix2->next_fix2;
    }

    current_fix3 = current_fix1->fix3_list;
    while (current_fix3!=NULL) {
      summarize_fix3();
      current_fix3 = current_fix3->next_fix3;
    }

    current_fix4 = current_fix1->fix4_list;
    while (current_fix4!=NULL) {
      summarize_fix4();
      current_fix4 = current_fix4->next_fix4;
    }

    current_fix5 = current_fix1->fix5_list;
    while (current_fix5!=NULL) {
      summarize_fix5();
      current_fix5 = current_fix5->next_fix5;
    }

    current_fix1 = current_fix1->next_fix1;
  }

}

void fix::free_fix_data()
{
  current_fix1 = head_fix1;
  while (head_fix1!=NULL) {
    current_fix1=head_fix1;
    head_fix1 = head_fix1->next_fix1;

    current_fix2 = head_fix2;
    while (head_fix2!=NULL) {
      current_fix2=head_fix2;
      head_fix2 = head_fix2->next_fix2;
      delete current_fix2;
    }


    current_fix3 = head_fix3;
    while (head_fix3!=NULL) {
      current_fix3=head_fix3;
      head_fix3 = head_fix3->next_fix3;
      delete current_fix3;
    }

    current_fix4 = head_fix4;
    while (head_fix4!=NULL) {
      current_fix4=head_fix4;
      head_fix4 = head_fix4->next_fix4;
      delete current_fix4;
    }

    current_fix5 = head_fix5;
    while (head_fix5!=NULL) {
      current_fix5=head_fix5;
      head_fix5 = head_fix5->next_fix5;
      delete current_fix5;
    }
    delete current_fix1;
  }

  current_fix = head_fix;
  while (head_fix!=NULL) {
    current_fix=head_fix;
    head_fix = head_fix->next_fix;
    head_awy_fix = current_fix->awy_list;
    while (head_awy_fix !=NULL) {
      current_awy_fix = head_awy_fix;
      head_awy_fix = head_awy_fix->awy_next;
      delete current_awy_fix;
    }
    head_ils_mm_fix = current_fix->ils_mm_list;
    while (head_ils_mm_fix!=NULL) {
      current_ils_mm_fix = head_ils_mm_fix;
      head_ils_mm_fix = head_ils_mm_fix->ils_mm_next;
      delete current_ils_mm_fix;
    }
    head_ils_om_fix = current_fix->ils_om_list;
    while (head_ils_om_fix!=NULL) {
      current_ils_om_fix = head_ils_om_fix;
      head_ils_om_fix = head_ils_om_fix->ils_om_next;
      delete current_ils_om_fix;
    }
    delete current_fix;
  }
}


