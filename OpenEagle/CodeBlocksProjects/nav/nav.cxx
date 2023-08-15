/***************************************************************
 * Name:      fix.cxx
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


//****************************************************************************************************
//  Notes on FlightGear nav.dat file format (from xplane format?)
// + type code: 2:NDB 3:VOR 4:ILS case 5:LOC 6:GS 7:OM 8:MM 9:IM 12:13:DME 99:end-of-file code
//
// general form
// type code lat long elev_ft freq range multiuse ident
//
// + type code: 2:NDB
// |    +----latitude/longted
// |    |                           +---elevation feet (elev is in the FAA database...)
// |    |                           |    + -------nav_freq
// |    |                           |    |    +----range but FAA DOES STATE A RANGE
// |    |                           |    |    |         +---------unknown ALWAYS 0.0
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[NDB]
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |
// 2  31.58566667 -110.34425000      0   410  50       0.0   DAO  DRAGOO      NDB

// + type code: 3:VOR
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------freq no FAA fied?
// |    |                           |    |    +--------range no FAA field
// |    |                           |    |    |         +---------multiuse  no FAA Field
// |    |                           |    |    |         |     <--------------"ident" in navdb.cxx --->
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME]
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |
// 3  35.14719444 -111.67416667   7026 11385 130      14.0   FLG  FLAGSTAFF   VOR-DME
// 3  35.06161111 -110.79502778   4913 11260 130      14.0   INW  WINSLOW     VORTAC

// + type code: 4:ILS
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |
// 4  35.13792800 -111.67336100   7011 11050  18     226.050 IFLG KFLG 21     ILS-cat-I

// + type code: 5:LOC
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |



// + type code: 6:GS
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |
// 6  35.14408600 -111.66591900   6982 11050  10  300221.039 IFLG KFLG 21     GS


// + type code: 7:OM
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |
// 7  33.43161400 -112.10655000   1135     0   0      90.040 ---- KPHX 07L    OM

// + type code: 8:MM
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |


// + type code: 9:IM
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |

// + type code: 12/13:DME
// |    +----latitude/longted
// |    |                           +---elevation feet
// |    |                           |    + -------unknown
// |    |                           |    |    +--------unkown
// |    |                           |    |    |         +---------unknown
// |    |                           |    |    |         |     +-----ofc_nav_id
// |    |                           |    |    |         |     |       +----- nav_name
// |    |                           |    |    |         |     |       |        +------nav_type[VOR/DME
// |    |                           |    |    |         |     |       |        |
// |  --+----------------------     |    |    |         |     |       |        |

//12  35.06160000 -110.79501944   4913 11260 130       0.0   INW  WINSLOW     VORTAC
//
//****************************************************************************************************
#include "nav.hxx"
#include <cstddef>
#include "../read_data/read_data.hxx"
#include "../subpath/subpath.hxx"
#include "../paths/paths.hxx"
#include "../avl_tree/avl_tree.hxx"
#include "../data_conversion/data_conversion.hxx"
#include "../sghybrid/sghybrid.hxx"
#include "../generate/generate.hxx"


#define VORTAC 3
#define VOR_DME 3
#define FAN_MARKER -1
#define CONSOLANE -1
#define MARINE_NDB 2
#define MARINE_NDB_DME 2
#define VOT 0
#define NDB 2
#define NDB_DME 2
#define TACAN 2
#define UHF_NDB 2
#define VOR 3
#define TYPE_UNKNOWN 0

char NASRnavbuffer[700];

void nav ::read_nav1_data()
{
  current_nav  = new(nav_record);

  last_nav->next_nav = current_nav;
  last_nav = current_nav;

  current_nav1 = new(nav1_record);
  current_nav->nav1_list = current_nav1;
  current_nav->nav3_list = NULL;
  current_nav->nav4_list = NULL;
  current_nav->nav5_list = NULL;
  current_nav->next_nav=NULL;

  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_id,4,4);              // 0004 00005
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_type,20,8);           // 0020 00009
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->ofc_nav_id,4,28);         // 0004 00029
                                                                                    // 0010 00033  N/A     EFFECTIVE DATE; THIS DATE COINCIDES WITH
                                                                                    //
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_name,30,42);          // 0030 00043
  //now a city reference name also                                                     0040 00073  N1      CITY ASSOCIATED WITH THE NAVAID.
                                                                                    // 0030 00113  N2      STATE NAME WHERE ASSOCIATED CITY IS LOCATED
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_st,2,142);            // 0002 00143
                                                                                    // 0003 00145  N20     FAA REGION RESPONSIBLE FOR NAVAID (CODE)
                                                                                    // 0030 00148  N3      COUNTRY NAVAID LOCATED IF OTHER THAN U.S
                                                                                    // 0002 00178  N3S     COUNTRY POST OFFICE CODE NAVAID
                                                                                    // 0050 00180  N10     NAVAID OWNER NAME  (EX: U.S. NAVY)
                                                                                    // 00230  N12     NAVAID OPERATOR NAME (EX: U.S. NAVY)
                                                                                    // 0001 00280  N47     COMMON SYSTEM USAGE (Y OR N)
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_public,1,280);        // 0001 00281  N48     NAVAID PUBLIC USE (Y OR N)
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_class,11,281);        // 0011 00282
                                                                                    // 0011 00293  N52     HOURS OF OPERATION OF NAVAID
                                                                                    // 0004 00304  N91     IDENTIFIER OF ARTCC WITH HIGH ALTITUDE BOUNDARY THAT THE NAVAID
                                                                                    // 0030 00308  N91     NAME OF ARTCC WITH HIGH ALTITUDE BOUNDARY THAT THE NAVAID
                                                                                    // 0004 00338  N94     IDENTIFIER OF ARTCC WITH LOW ALTITUDE BOUNDARY THAT THE NAVAID
                                                                                    // 0030 00342  N94     NAME OF ARTCC WITH LOW ALTITUDE BOUNDARY THAT THE NAVAID
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_artcc,30,341);        // 0030 00342
                                                                                    // 0014 00372  N4      NAVAID LATITUDE (FORMATTED)
                                                                                    // 0011 00386  N4S     NAVAID LATITUDE (ALL SECONDS)
                                                                                    // 0014 00397  N5      NAVAID LONGITUDE (FORMATTED)
                                                                                    // 0011 00411  N5S     NAVAID LONGITUDE (ALL SECONDS)
                                                                                    // 0001 00422  N38     LATITUDE/LONGITUDE SURVERY ACCURACY (CODE)
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_lat_sec,11,385);      // 386
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_long_sec,11,410);     // 411
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_accuracy,1,421);      // 422
                                                                                    // 0014 00423  N21     LATITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
                                                                                    // 0011 00437  N21S    LATITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
                                                                                    // 0014 00448  N22     LONGITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
                                                                                    // 0011 00462  N22S    LONGITUDE OF TACAN PORTION OF VORTAC WHEN TACAN
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->tacan_lat_sec,11,436);    // 437
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->tacan_long_sec,11,461);   // 462
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_elev,7,472);          // 0007 00473  N37     ELEVATION IN TENTH OF A FOOT (MSL)
                                                                                    // 0005 00480  N45      MAGNETIC VARIATION DEGREES   (00-99)
                                                                                    // 0004 00485  N45S     MAGNETIC VARIATION EPOCH YEAR  (00-99)
                                                                                    //
                                                                                    // 0003 00489 N33     SIMULTANEOUS VOICE FEATURE (Y,N, OR NULL)
                                                                                    // 0004 00492 N34     POWER OUTPUT (IN WATTS)
                                                                                    // 0003 00496 N35     AUTOMATIC VOICE IDENTIFICATION FEATURE
                                                                                    // 0001 00499  N36     MONITORING CATEGORY
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->radio_call,30,499);       // 0030 00500 N23     RADIO VOICE CALL (NAME)
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_channel,4,529);       // 0004 00530 N24     CHANNEL (TACAN)  NAVAID TRANSMITS ON
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_freq,6,533);          // 0006 00534 N25     FREQUENCY THE NAVAID TRANSMITS ON
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_fan,24,539);          // 0024 00540 N75     TRANSMITTED FAN MARKER/MARINE RADIO BEACON
                                                                                    // 0010 00564 N76     FAN MARKER TYPE (BONE OR ELLIPTICAL)
                                                                                    // 0003 00574 N77     TRUE BEARING OF MAJOR AXIS OF FAN MARKER
                                                                                    // 0001 00577 N29     PROTECTED FREQUENCY ALTITUDE
                                                                                    // 0003 00578 N30     LOW ALTITUDE FACILITY USED IN HIGH STRUCTURE
                                                                                    // 0003 00581 N31     NAVAID Z MARKER AVAILABLE (Y, N, OR NULL)
                                                                                    // 0009 00584 N32     TRANSCRIBED WEATHER BROADCAST HOURS (TWEB)
                                                                                    // 0020 00593 N95     TRANSCRIBED WEATHER BROADCAST PHONE NUMBER
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_fss_id,4,612);        // 0004 00613 N49S    ASSOCIATED/CONTROLLING FSS (IDENT)
  set_field((char *)&NASRnavbuffer,(char *)&current_nav1->nav_fss_name,30,616);     // 0030 00617 N49     ASSOCIATED/CONTROLLING FSS (NAME)
                                                                                    // 0100 00647 F15     HOURS OF OPERATION OF CONTROLLING FSS
                                                                                    // 0004 00747 N49B    NOTAM ACCOUNTABILITY CODE (IDENT)
                                                                                    // 0016 00751 N80     QUADRANT IDENTIFICATION AND RANGE LEG BEARING
                                                                                    // 0030 00767  N41,    NAVIGATION AID STATUS
                                                                                    // 0001 00797  N/A    PITCH FLAG (Y OR N)
                                                                                    // 0001 00798  N/A    CATCH FLAG (Y OR N)
                                                                                    // 0001 00799  N/A    SUA/ATCAA FLAG (Y OR N)
                                                                                    // 0001 00800  N/A    NAVAID RESTRICTION FLAG
                                                                                    // 0001 00801  N/A    HIWAS FLAG
                                                                                    // 0001 00802  N/A    TRANSCRIBED WEATHER BROADCAST (TWEB) RESTRICTION
  printf("read_nav1_data(): nav_id[%s] nav_type[%s] ofc_nav_id[%s] nav_name[%s] nav_st[%s] nav_public[%s] nav_class[%s] nav_artcc[%s] nav_lat_sec[%s] nav_long_sec[%s] nav_accuracy[%s] tacan_lat_sec[%s] tacan_long_sec[%s] nav_elev[%s] radio_call[%s] nav_channel[%s] nav_freq[%s] nav_fan[%s]\n",
         current_nav1->nav_id,
         current_nav1->nav_type,
         current_nav1->ofc_nav_id,
         current_nav1->nav_name,
         current_nav1->nav_st,
         current_nav1->nav_public,
         current_nav1->nav_class,
         current_nav1->nav_artcc,
         current_nav1->nav_lat_sec,
         current_nav1->nav_long_sec,
         current_nav1->nav_accuracy,
         current_nav1->tacan_lat_sec,
         current_nav1->tacan_long_sec,
         current_nav1->nav_elev,
         current_nav1->radio_call,
         current_nav1->nav_channel,
         current_nav1->nav_freq,
         current_nav1->nav_fan
        );
  int nav_type_code=0;

  if (strncmp(current_nav1->nav_type,"VORTAC",6)==0) nav_type_code = VORTAC;
  else
  if (strncmp(current_nav1->nav_type,"VOR/DME",7)==0) nav_type_code = VOR_DME;
  else
  if (strncmp(current_nav1->nav_type,"FAN MARKER",10)==0) nav_type_code = FAN_MARKER;
  else
  if (strncmp(current_nav1->nav_type,"CONSOLANE",9)==0) nav_type_code = CONSOLANE;
  else
  if (strncmp(current_nav1->nav_type,"MARINE NDB",10)==0) nav_type_code = MARINE_NDB;
  else
  if (strncmp(current_nav1->nav_type,"MARINE NDB/DME",14)==0) nav_type_code = MARINE_NDB_DME;
  else
  if (strncmp(current_nav1->nav_type,"VOT",3)==0) nav_type_code = VOT;
  else
  if (strncmp(current_nav1->nav_type,"NDB",3)==0) nav_type_code = NDB;
  else
  if (strncmp(current_nav1->nav_type,"NDB/DME",7)==0) nav_type_code = NDB_DME;
  else
  if (strncmp(current_nav1->nav_type,"TACAN",5)==0) nav_type_code = TACAN;
  else
  if (strncmp(current_nav1->nav_type,"UHF/NDB",7)==0) nav_type_code = UHF_NDB;
  else
  if (strncmp(current_nav1->nav_type,"VOR",3)==0) nav_type_code = VOR;
  else
  nav_type_code = TYPE_UNKNOWN;
  current_nav1->nav_type_code = nav_type_code;
  double d_nav_freq;
  d_nav_freq = strtod(current_nav1->nav_freq,NULL);
  int i_nav_freq;
  i_nav_freq = (int) d_nav_freq;
  if (d_nav_freq > (double) i_nav_freq) i_nav_freq*=10;
  current_nav1->i_nav_freq = i_nav_freq;
}

void nav ::read_nav3_data()
{
  current_nav3 = new(nav3_record);
  current_nav3->next_nav3=NULL;
  if (current_nav->nav3_list==NULL) current_nav->nav3_list=current_nav3;
  else {
    a_nav3 = current_nav->nav3_list;
    while (a_nav3->next_nav3 !=NULL) a_nav3 = a_nav3->next_nav3;
    a_nav3->next_nav3 = current_nav3;
  }
  int i;
  int dx;
  int max_fix=-1;
  char lookup_fix[6];
  int lf;
  dx=28;
  for (i=0; i<19; i++) {
    set_field((char *)&NASRnavbuffer,(char *)&current_nav3->nav_fix[i],18,dx);            //4
    if (!isspace(current_nav3->nav_fix[i][0])) max_fix=i;
    dx+=33;
  }
  if (max_fix>=0) {
    for (i=0; i<max_fix+1; i++) {
      lf=0;
      while (current_nav3->nav_fix[i][lf]!='*') {
        lookup_fix[lf]=current_nav3->nav_fix[i][lf];
        lf++;
        if (lf>6) {
          current_nav3->nav_fix[i][lf]='*';
        }
      }
      lookup_fix[lf]='\0';
    }
  }
}

void nav ::read_nav4_data()
{
  current_nav4 = new(nav4_record);
  current_nav4->next_nav4=NULL;
  if (current_nav->nav4_list==NULL) current_nav->nav4_list=current_nav4;
  else {
    a_nav4 = current_nav->nav4_list;
    while (a_nav4->next_nav4 !=NULL) a_nav4 = a_nav4->next_nav4;
    a_nav4->next_nav4 = current_nav4;
  }
  int i;
  int dx;
  dx=28;
  for (i=0; i<19; i++) {
    set_field((char *)&NASRnavbuffer,(char *)&current_nav4->nav_hold_pat[i],18,dx);
    dx+=33;
  }
}

void nav ::read_nav5_data()
{
  current_nav5 = new(nav5_record);
  current_nav5->next_nav5=NULL;
  if (current_nav->nav5_list==NULL) current_nav->nav5_list=current_nav5;
  else {
    a_nav5 = current_nav->nav5_list;
    while (a_nav5->next_nav5 !=NULL) a_nav5 = a_nav5->next_nav5;
    a_nav5->next_nav5 = current_nav5;
  }
  int i;
  int dx;
  dx=28;
  for (i=0; i<19; i++) {
    set_field((char *)&NASRnavbuffer,(char *)&current_nav5->nav_fan_mkr[i],26,dx);
   dx+=26;
  }
}


int npubnav=0;
void  nav :: read_nav_data()
{
  FILE * fp_nav;
  FILE * fp_nav_dat;
  bool done=false;
  int last_space;
  int nnav=0;
  std::string d_NASR_nav;

  d_NASR_nav = NASR_base;
  d_NASR_nav += "/NASR/current/NAV.txt";
  fp_nav  = fopen( d_NASR_nav.c_str(), "r" );

  head_nav = new(nav_record); //empty first node
  head_nav->next_nav = NULL;
  head_nav->nav1_list = NULL;
  head_nav->nav3_list = NULL;
  head_nav->nav4_list = NULL;
  head_nav->nav5_list = NULL;

  last_nav = head_nav;

  printf("Reading nav Records\n");

  while (!done) {
    read_field(fp_nav,(char *)&NASRnavbuffer,sizeof(NASRnavbuffer),tc2);

    char nav_rtype[5];

    set_field((char *)&NASRnavbuffer,(char *)&nav_rtype,4,0);
    if (strncmp((const char *)&nav_rtype,"NAV1",4)==0) {
      read_nav1_data();
      if (strncmp(current_nav1->nav_public,"Y",1)==0) npubnav++;
    }
    else {
      if (strncmp((const char *)&nav_rtype,"NAV2",4)==0) {
      }
      else {
        if (strncmp((const char *)&nav_rtype,"NAV3",4)==0) {
          read_nav3_data();
        }
        else {
          if (strncmp((const char *)&nav_rtype,"NAV4",4)==0) {
            read_nav4_data();
          }
          else {
            if (strncmp((const char *)&nav_rtype,"NAV5",4)==0) {
              //read_nav5_data();
            }
            else {
              if (strncmp((const char *)&nav_rtype,"NAV6",4)==0) {
                read_nav5_data();
              }
              else {
                 printf("ERROR! unkown record type in database %s\n",(const char *)&nav_rtype);
                 exit(1);
              }
            }
          }
        }
      }
    }
    nnav++;
    if (!nextok(fp_nav)) done=true;
  }
  printf("nnav %d\n",nnav);
  printf("finished reading data\n");
  fclose(fp_nav);
}

void nav :: summarize_nav()
{
  FILE * fp_ds;
  fp_ds  = fopen("summary_nav.txt", "w+" );
  current_nav = head_nav->next_nav;
  while (current_nav!=NULL) {
    current_nav1 = current_nav->nav1_list;
    if (current_nav1==NULL) {
      printf("\n\n\n\n\n\n current_nav1 NULL\n");
      exit(1);
    }
    if (strncmp(current_nav1->nav_public,"Y",1)==0) {
      fprintf(fp_ds,"Type [%s] official id [%s] name[%s]",current_nav1->nav_type,current_nav1->ofc_nav_id,current_nav1->nav_name);
      fprintf(fp_ds," class [%s] artcc [%s]",current_nav1->nav_class,current_nav1->nav_artcc);
      fprintf(fp_ds," lat [%11.6f] long [%11.6f] accuracy code [%s] elevation [%s]",NASR_coord_to_d(current_nav1->nav_lat_sec),
        NASR_coord_to_d(current_nav1->nav_long_sec),current_nav1->nav_accuracy,current_nav1->nav_elev);
      fprintf(fp_ds," radio call [%s] nav channel [%s] freq [%s]",current_nav1->radio_call,current_nav1->nav_channel,current_nav1->nav_freq);
      fprintf(fp_ds," fss id [%s]  name [%s]\n",current_nav1->nav_fss_id,current_nav1->nav_fss_name);
      current_nav3 = current_nav->nav3_list;
      if (current_nav3!=NULL) {
        fprintf(fp_ds,"  Fixes\n");
        while (current_nav3!=NULL) {
          for (int i=0; i<19; i++) if (current_nav3->nav_fix[i][0]!=' ') fprintf(fp_ds,"    [%s]\n",current_nav3->nav_fix[i]);
          current_nav3 =current_nav3->next_nav3;
        }
      }
      current_nav4 = current_nav->nav4_list;
      if (current_nav4!=NULL) {
        fprintf(fp_ds,"  Holding Patterns\n");
        while (current_nav4!=NULL) {
          for (int i=0; i<19; i++) if (current_nav4->nav_hold_pat[i][0]!=' ')  fprintf(fp_ds,"    [%s]\n",current_nav4->nav_hold_pat[i]);
          current_nav4 =current_nav4->next_nav4;
        }
      }
      current_nav5 = current_nav->nav5_list;
      if (current_nav5!=NULL) {
        fprintf(fp_ds,"  Fan Markers\n");
        while (current_nav5!=NULL) {
          for (int i=0; i<24; i++) if (current_nav5->nav_fan_mkr[i][0]!=0)
                                   if (current_nav5->nav_fan_mkr[i][0]!=' ') fprintf(fp_ds,"    [%s]\n",current_nav5->nav_fan_mkr[i]);
          current_nav5 =current_nav5->next_nav5;
        }
      }
    }
    current_nav=current_nav->next_nav;
  }
  fclose (fp_ds);
}

void nav :: generate_nav_files()
{

  generate g;
  printf("generage nav files\n");
  FILE * fp;
  FILE * fp_g;
  char tile_addline[1000];
  char tile_filename[1000];
  char tile_path[1000];
  char xml_filename[1000];
  char ac_filename[1000];
  char png_filename[1000];
  char nav_line_1[1000];
  char nav_line_2[1000];
  int nnav=1;
  fp  = fopen("summary_generate_nav.txt", "w+" );
  current_nav = head_nav->next_nav;

  g.set_pillar_height(10300.00);
  g.set_sign_scale(20.0);
  g.add_condition((char *)"      <property>/open-eagle/airway/enabled</property>");
  g.add_condition((char *)"      <property>/open-eagle/airway/navaid/enabled</property>");

  while (current_nav!=NULL) {
    printf("nnav %d\n",nnav);
    printf("npubnav %d\n",npubnav);
    current_nav1 = current_nav->nav1_list;
    if (current_nav1==NULL) {
      printf("\n\n\n\n\n\n current_nav1 NULL\n");
      exit(1);
    }
    if (strncmp(current_nav1->nav_public,"Y",1)==0) {

      double dlat, dlong;

      dlat  = NASR_coord_to_d(current_nav1->nav_lat_sec);
      dlong = NASR_coord_to_d(current_nav1->nav_long_sec);
      set_subpath_for(dlat,dlong);
      hset_bucket(dlong,dlat);

      int tilenum;

      tilenum = hgen_index();

      double elevation;

      elevation = strtod(current_nav->nav1_list->nav_elev,NULL);
#define SIGN_HEIGHT_ABOVE_NAVAID 10300.00
      sprintf(tile_path,  "%s/Objects/%s",output_base.c_str(), subpath);
      sprintf(tile_filename,  "%d.stg",tilenum );

      //sprintf(tile_filename, "%s/Objects/%s%d.stg",output_base.c_str(), subpath, tilenum );
      sprintf(tile_addline,"OBJECT_STATIC N_%s.xml %f %f %6.1f 0.0\n",remove_trailing_spaces((char *)&current_nav1->ofc_nav_id),dlong,dlat, (elevation+SIGN_HEIGHT_ABOVE_NAVAID)*SG_FEET_TO_METER);
      sprintf(xml_filename, "%s/Objects/%s/N_%s.xml",output_base.c_str(), subpath,remove_trailing_spaces((char *)&current_nav1->ofc_nav_id));
      sprintf(ac_filename, "%s/Objects/%s/N_%s.ac",output_base.c_str(), subpath, remove_trailing_spaces((char *)&current_nav1->ofc_nav_id));
      sprintf(png_filename, "%s/Objects/%s/N_%s.png",output_base.c_str(), subpath, remove_trailing_spaces((char *)&current_nav1->ofc_nav_id));

      fprintf(fp,"Navaid: [%s]\n",current_nav1->ofc_nav_id);
      fprintf(fp,"  tile_filename  : [%s]\n",tile_filename);
      fprintf(fp,"    tile_addline : %s",tile_addline);  // has /n in it
      fprintf(fp,"  xml_filename   : [%s]\n",xml_filename);
      fprintf(fp,"  ac_filename    : [%s]\n",ac_filename);
      fprintf(fp,"  png_filename   : [%s]\n",png_filename);

     // g.write_tile_addline((char * )&tile_filename,( char *)&tile_addline);
      g.write_tile_addline((char *)&tile_path,(char * )&tile_filename,( char *)&tile_addline);

      char line[128];
      sprintf(line,"%s/",remove_trailing_spaces((char *)&current_nav1->ofc_nav_id));
      sprintf(line,"%s%s",line,remove_trailing_spaces((char *)&current_nav1->nav_type));
      g.add_line((char *)&line, 50,(char *) "blue",(char *)"Center");
      sprintf(line,"%s",remove_trailing_spaces((char *)&current_nav1->nav_freq));
      if (  strlen((const char *) remove_trailing_spaces((char *)&current_nav1->nav_channel)) > 0)
        sprintf(line,"%s, %s",line,remove_trailing_spaces((char *)&current_nav1->nav_channel));
      g.add_line((char *)&line, 40, (char *)"black",(char *)"Center");
      g.write_sign_png_file(fp,(char *)&png_filename);
      g.generate_sign_ac_file((char *)&ac_filename,(char *)&png_filename);
      g.generate_sign_xml_file((char *)&xml_filename,(char *)&ac_filename);
      nnav++;
    }
    current_nav=current_nav->next_nav;
  }
  g.erase_conditions();
  fclose(fp);

}
void nav :: free_nav_data()
{
  while (head_nav!=NULL) {
    current_nav=head_nav;
    head_nav = head_nav->next_nav;
    current_nav1 = current_nav->nav1_list;
    head_nav1 = current_nav1;
    delete head_nav1;
    current_nav3 = current_nav->nav3_list;
    while (current_nav3!=NULL) {
      head_nav3 = current_nav3;
      current_nav3 = current_nav3->next_nav3;
      delete head_nav3;
    }
    current_nav4 = current_nav->nav4_list;
    while (current_nav4!=NULL) {
      head_nav4 = current_nav4;
      current_nav4 = current_nav4->next_nav4;
      delete head_nav4;
    }
    current_nav5 = current_nav->nav5_list;
    while (current_nav5!=NULL) {
      head_nav5 = current_nav5;
      current_nav5 = current_nav5->next_nav5;
      delete head_nav5;
    }
    delete current_nav;
  }
}

