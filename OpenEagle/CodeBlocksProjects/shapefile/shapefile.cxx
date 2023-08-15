/***************************************************************
 * Name:      shapefile.cxx
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
#include "shapefile.hxx"
#include <stdlib.h>
#include <string.h>
#include "../tile/tile.hxx"
#include "../data_conversion/data_conversion.hxx"
#include "../3rdparty/constants.h"
#include "../system_io/system_io.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
#include "../3rdparty/shapelib-1.5.0/shapefil.h"
void shapefile::initialize_dbf()
{
  dbf_data = new struct dbf_record;
  dbf_data->field_list = NULL;
  dbf_data->record_list = NULL;
}

char * shapefile::get_current_data_for_field(int n)
{
  if (n<0) return NULL;
  if (n < dbf_data->num_fields) {
    struct record_data * a_record = current_record;
    if (a_record != NULL) {
      struct field_data * data = a_record->data;
      for (int i=0; i<=n; i++){
        if (data != NULL) {
          if (data->field_nbr != n) {
            data = data->next_data;
          }
          else return data->field_data_char;
        }
        else return NULL;
      }
    }
    else return NULL;
  }
  return NULL;
}

void shapefile::reset_dbf_shp()
{
  current_record = dbf_data->record_list;
  current_shape  = shp_data->shape_list;
}

int shapefile::get_shp_nentities()
{
  return shp_data->nentities;
}

int shapefile::get_dbf_num_records()
{
  return dbf_data->num_records;
}

bool shapefile::can_advance_dbf_shp()
{
  bool can_advance = true;
  if (current_record->next_record == NULL) can_advance = false;
  if (current_shape->next_shape == NULL) can_advance = false;
  return can_advance;
}

bool shapefile::advance_dbf_shp()          // advance dbf and shp records, return false if one or both goto NULL;
{
  current_record = current_record->next_record;
  current_shape = current_shape->next_shape;
  bool ret = true;
  if (current_record == NULL) ret = false;
  if (current_shape == NULL) ret = false;
  return ret;
}

int shapefile::get_dbf_shape_shape_nbr()
{
  if (current_shape!=NULL) return current_shape->shape_nbr;
  return -1;
}

int shapefile::get_dbf_shape_record_nbr()
{
  if (current_record!=NULL) return current_record->record_nbr;
  return -1;
}

void shapefile::reset_vertice_list()       // set vertice to head of list for current shape
{
  current_vertice = current_shape->vertice_list;
}

void shapefile::reset_segment_list()       // set segment to head of list for current shape
{
  current_segment = current_shape->segment_list;
}

void shapefile::reset_segments_vertice_list()
{
  current_vertice = current_segment->seg_vertice_start;
}

int shapefile::get_shape_n_vertices()      //
{
  return current_shape->shape_nvertices;
}

int shapefile::get_shape_num_segments()
{
  return current_shape->num_segments;
}

int shapefile::next_segment()      // traverse segment list will return -1 if current_segment -> NULL.
{
  current_segment = current_segment->next_segment;
  if (current_segment != NULL) return current_segment->segment_n; else return -1;
}

int shapefile::get_seg_n_vertices()
{
  return current_segment->seg_n_vertices;
}



bool shapefile::generate_ac_xml_and_update_stg_files_current_segment(
       int seg_nbr,
       std::string * models_and_objects_path,
       std::string * short_ac_path,
       std::string * full_ac_path,
       std::string * ac_filename,
       std::string * texture_path,
       std::string * texture_name,
       double low_alt,
       double high_alt
                                                              )
{
  printf("shapefile::generate_ac_xml_and_update_stg_files_current_segment(\n");
  printf("     models_and_objects_path, [%s]\n",models_and_objects_path->c_str());
  printf("     short_ac_path [%s]\n",short_ac_path->c_str());
  printf("     full_ac_path [%s]\n",full_ac_path->c_str());
  printf("     ac_filename [%s]\n",ac_filename->c_str());
  printf("     texture_path [%s]\n",texture_path->c_str());
  printf("     texture_name [%s]\n",texture_name->c_str());
  printf("     low_alt %10.1f high_alt %10.1f\n",low_alt,high_alt);
  printf("     )\n");


  bool nanbug = false;
  std::string command_ac_path = "mkdir -p ";
  command_ac_path += full_ac_path->c_str();
  command_ac_path += "\n";
  printf("command_ac_path: [%s]\n",command_ac_path.c_str());
  bool ac_path_ok = system_io(&command_ac_path);
  if (!ac_path_ok) {
    printf("could not build ac_path [%s]\n",command_ac_path.c_str());
    exit(1);
  }
  FILE * fp;
  std::string full_filename = full_ac_path->c_str();
  full_filename += "/";
  full_filename += ac_filename->c_str();
  full_filename += ".ac";

  std::string short_filename = "/";
  short_filename += ac_filename->c_str();
  short_filename += ".ac";
/************************************************************************/
/*                              write .ac file                         */
/************************************************************************/
  fp = fopen(full_filename.c_str(),"w+");
  printf("full_filename [%s]\n",full_filename.c_str());
  if (fp == NULL) {
    printf("file [%s] could not be opened for writting\n",full_filename.c_str());
    return false;//    exit(1);
  }
  fprintf(fp,"AC3Db\nMATERIAL \"Material.001\" rgb 1 1 1 amb 0 0 0 emis 1 1 1 spec 0 0 0 shi 0 trans 0.3\nOBJECT world\nkids 1\n");
  int n_vertices = current_segment->seg_n_vertices;
  struct vertice_record* ac_start_vertice = current_segment->seg_vertice_start;
  struct vertice_record* ac_end_vertice = current_segment->seg_vertice_end;
  struct vertice_record* ac_current_vertice = ac_start_vertice;

  fprintf(fp,"OBJECT poly\nname \"airspace-%d\"\n",current_segment->segment_n);
  fprintf(fp,"texture \"%s.png\"\n",texture_name->c_str());
  fprintf(fp,"texoff 1.0 1.0\n");
  fprintf(fp,"texrep 1.0 3.15\n");
  fprintf(fp,"crease 45.000000\n");
  fprintf(fp,"numvert %d\n",n_vertices*2);
  double ac_long;
  double ac_lat;
  double _R;
  for (int i = 0; i < n_vertices; i++) {
     _R = ac_from_wgs_84(current_segment->tile_ctr_latitude,
                   current_segment->tile_ctr_longitude,
                   ac_current_vertice->y,
                   ac_current_vertice->x,
                   &ac_long,
                   &ac_lat);
    fprintf(fp,"  %12.2f  %12.2f  %12.2f\n", ac_long, low_alt*SG_FEET_TO_METER, ac_lat);
    ac_current_vertice = ac_current_vertice->next_vertice;
  }
  ac_current_vertice = ac_start_vertice;
  for (int i = 0; i < n_vertices; i++) {
  nanbug = ac_from_wgs_84(current_segment->tile_ctr_latitude,
                   current_segment->tile_ctr_longitude,
                   ac_current_vertice->y,
                   ac_current_vertice->x,
                   &ac_long,
                   &ac_lat);
    fprintf(fp,"  %12.2f  %12.2f  %12.2f\n", ac_long, high_alt*SG_FEET_TO_METER, ac_lat);
    ac_current_vertice = ac_current_vertice->next_vertice;
  }
  fprintf(fp,"numsurf %d\n",n_vertices-1);
  for (int isurf=0; isurf< n_vertices-1; isurf++) {
    int numvert;
    numvert = n_vertices*2;
    fprintf(fp,"SURF 0x20\nmat 0\nrefs 4\n");
    fprintf(fp,"%5d 0.003906 0.640625\n",isurf);
    fprintf(fp,"%5d 0.972656 0.644531\n",numvert/2+isurf);
    fprintf(fp,"%5d 0.972656 0.992188\n",numvert/2+isurf+1);
    fprintf(fp,"%5d 0.003906 0.988281\n",isurf+1);
  }
  fprintf(fp,"kids 0\n");
  fclose(fp);
/************************************************************************/
/*                              NOW to copy the Texture                 */
/************************************************************************/
  std::string temp_name = texture_name->c_str();
  temp_name += ".png";
  std::string full_texture_name = texture_path->c_str();
  full_texture_name += "/";
  full_texture_name += temp_name.c_str();
  std::string command_cp_texture = "cp ";
  command_cp_texture += full_texture_name.c_str();
  command_cp_texture += " ";
  command_cp_texture += full_ac_path->c_str();
  command_cp_texture += "/";
  command_cp_texture += temp_name.c_str();
  command_cp_texture += "\n";
  printf("copy texture command_cp_texture string [%s]\n",command_cp_texture.c_str());
  bool full_texture_path = system_io(&command_cp_texture);
  if (!full_texture_path) {
    printf("system command_str failed for string [%s]\n",command_cp_texture.c_str());
    exit(1);
  }
/************************************************************************/
/*                              NOW write xml file                      */
/************************************************************************/
  std::string xml_filename = ac_filename->c_str();
  xml_filename += ".xml";
  ///std::string models_and_objects_path = OpenEagleWrite_ModelsAndObjectsPath;
  std::string short_xml_filename = short_ac_path->c_str();
  short_xml_filename += "/";
  short_xml_filename += xml_filename.c_str();
  printf("short xml file [%s]\n",short_xml_filename.c_str());


  std::string full_xml_filename = full_ac_path->c_str();
  full_xml_filename += "/";
  full_xml_filename += xml_filename.c_str();
  printf("full xml file [%s]\n",full_xml_filename.c_str());


  fp = fopen(full_xml_filename.c_str(),"w+");
  if (fp != NULL) {
    fprintf(fp,"<?xml version=\"1.0\"?>\n");
    fprintf(fp,"<PropertyList>\n");
    fprintf(fp,"  <path>%s.ac</path>\n",ac_filename->c_str());
    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>none</type>\n");
    /**
    for (int segment = 0; segment < current_shape->num_segments; segment++) {
      fprintf(fp,"    <object-name>airspace-%d</object-name>\n",segment);
    }
    **/
    fprintf(fp,"    <object-name>airspace-%d</object-name>\n",seg_nbr);
///    fprintf(fp,"    <condition>\n");
///    fprintf(fp,"      <property>/open-eagle/airspace/enabled</property>\n");
///    fprintf(fp,"      <property>/open-eagle/%s/enabled</property>\n", texture_name->c_str());
///    fprintf(fp,"    </condition>\n");
    fprintf(fp,"  </animation>\n");
    fprintf(fp,"</PropertyList>\n");
    fclose(fp);
  }
  else {
    printf("failed to open xml file [%s]",full_xml_filename.c_str());
    exit(1);
  }
  printf("wrote full_xml_filename\n");
/************************************************************************/
/*               NOW (1) add line to .stg file                          */
/************************************************************************/
/*  segment record includes path for .stg file                          */
/*    but, it is not the complete path                                  */
/*                                                                      */
/*  In the FlightGear data terrain starts at                            */
/*  Scenery in fgdata there is a sub folder/directory:                  */
/*  Scenery/Objects                                                     */
/*  thus the true relative path to the .stg file(s) is                  */
/*  Objects/(path from the segment record)                              */
/*                                                                      */
/*  Thus working with data in a "Current" folder/directory              */
/*  Make an Objects folder and copy the FlighGear Object contents       */
/*  in. We will be appending lines into the .stg files                  */
/*                                                                      */
/*  With the .ac .xml and .stg additions to the Models and Objects      */
/*  copied to the FlightGear root data we're ready add translucent      */
/*  boundaries for the airspace into the scene.                         */
/*                                                                      */
/************************************************************************/
///  std::string stg_path = paths.OpenEagle_FlightGear_Path.c_str();
  std::string stg_path = models_and_objects_path->c_str();
  stg_path += "/Objects/";
//  std::string  stg_pathShort = "/Objects/";

  stg_path      += current_segment->tile_path_str;
//  stg_pathShort += current_segment->tile_path_str;
  printf("stg_path [%s]\n",stg_path.c_str());
  printf("tile string [%s]\n",current_segment->tile_nbr_str);
  std::string command_tile_path = "mkdir -p ";
  command_tile_path += stg_path.c_str();
  command_tile_path += "\n";
  printf("command_tile_path [%s]\n",command_tile_path.c_str());
  bool tile_path_ok = system_io(&command_tile_path);
  if (!tile_path_ok) {
    printf("okay why is system command failing for string [%s]\n",command_tile_path.c_str());
    exit(1);
  }
  std::string stg_full_filename = stg_path.c_str();
  stg_full_filename += "/";
  stg_full_filename += current_segment->tile_nbr_str;
  stg_full_filename += ".stg";
  printf(" write stg filename [%s]\n",stg_full_filename.c_str());
  fp = fopen(stg_full_filename.c_str(),"a+");
  if (fp != NULL) {
    ///now the line to add ex: OBJECT_SHARED Models/Airspace/Class_D/1122113/Class_D-497-1122113.xml -111.875000 35.062500 0.0 0.00
    std::string addline = "OBJECT_SHARED ";
    addline += short_xml_filename.c_str();
    addline += " ";
    addline += std::to_string(current_segment->tile_ctr_longitude);
    addline += " ";
    addline += std::to_string(current_segment->tile_ctr_latitude);
    addline += " 0.0 0.00\n";
    fprintf(fp,"%s",addline.c_str());
    printf(" add the line [%s]\n",addline.c_str());
    fclose(fp);
  }
  else {
    printf("not able to open for append [%s]\n",stg_full_filename.c_str());
    exit(1);
  }
  if (nanbug==true) return false;
  return true;
}

int shapefile::next_vertice()              // traverse vertice list one node return return vertice_nbr or -1 if current_vertice is then NULL.
{
  current_vertice = current_vertice->next_vertice;
  if (current_vertice != NULL) return current_vertice->vertice_nbr; else return -1;
}

double shapefile::get_vertice_x()
{
  return current_vertice->x;
}

double shapefile::get_vertice_y()
{
  return current_vertice->y;
}

double shapefile::get_vertice_long()
{
  return current_vertice->x;
}

double shapefile::get_vertice_lat()
{
  return current_vertice->y;
}

void shapefile::summarize_dbf(char * fn)
{
  FILE * fp;
  std::string ffn_header = summaries_path + fn;
  ffn_header +="_dbf_header.txt";
  fp = fopen(ffn_header.c_str(),"w++");
  printf("summarize_dbf opened file [%s]\n",ffn_header.c_str());
  if (fp != NULL) {
    int nfield = 0;
    fprintf(fp,"dbf file summary\n  header:\n");
    field_list = dbf_data->field_list;
    while (field_list != NULL) {
      fprintf(fp,"%5d Field name[%s]\n",nfield,field_list->field_name);
      field_list = field_list->next_field;
      nfield++;
    }
    fclose(fp);
  }
  else printf("unable to open [%s] to summarize .dbf file\n",ffn_header.c_str());
  std::string ffn_data = summaries_path + fn;
  ffn_data += "_dbf_data.txt";
  fp = fopen(ffn_data.c_str(),"w++");
  if (fp != NULL) {
    current_record = dbf_data->record_list;
    while (current_record != NULL) {
      fprintf(fp,"Record %d:",current_record->record_nbr);
      current_data_list = current_record->data;
      while (current_data_list != NULL) {
        fprintf(fp," %d:%s",current_data_list->field_nbr,current_data_list->field_data_char);
        current_data_list = current_data_list->next_data;
      }
      fprintf(fp,"\n");
      current_record = current_record->next_record;
    }
    fclose(fp);
  }
  else printf("unable to open [%s] to summarize .dbf file\n",ffn_data.c_str());
}

void shapefile::summarize_shp_vertices(char * fn)
{
  int nPrecision = 15;
  std::string ffn = summaries_path + fn;
  ffn +="_segment_vertice.txt";
  FILE * fp;
  fp = fopen(ffn.c_str(),"w++");
  if (fp != NULL) {
    fprintf(fp,"shp_segments and vertices file summary\n");
    current_shape = shp_data->shape_list;
    while (current_shape != NULL) {
      fprintf(fp,"shape_nbr %4d shape_nvertices %5d\n",current_shape->shape_nbr,current_shape->shape_nvertices);
      fprintf(fp,"vertice summary\n");
      current_vertice = current_shape->vertice_list;
      struct vertice_record * last_vertice = NULL;
      while (current_vertice != NULL) {
        double x;
        double y;
        double last_x;
        double last_y;
        double r;
        double az;
        double az2;
        fprintf(fp,"     vertice_nbr %d (%.*g,%.*g) ",
	      current_vertice->vertice_nbr,
	      nPrecision,current_vertice->x,
	      nPrecision,current_vertice->y);
  	    x = current_vertice->x;
	      y = current_vertice->y;
	      if (last_vertice != NULL) {
          geo_inverse_wgs_84(last_y,last_x, y,x, &az, &az2,&r);
          fprintf(fp," delta distance between vertices %f",r*SG_METER_TO_FEET);
        }
  	    last_vertice = current_vertice;
	      last_x = x;
	      last_y = y;
        current_vertice = current_vertice->next_vertice;
        fprintf(fp,"\n");
      }
      current_shape = current_shape->next_shape;
    }
    fclose(fp);
  }
  else printf("unable to open [%s] to summarize .shp file\n",fn);
}

void shapefile::summarize_shp_segments(char * fn)
{
 std::string ffn = summaries_path + fn;
  ffn +="_shp_data.txt";
  FILE * fp;
  fp = fopen(ffn.c_str(),"w++");
  if (fp != NULL) {
    fprintf(fp,"shp_segments file summary\n");
    current_shape = shp_data->shape_list;
    while (current_shape != NULL) {
      fprintf(fp,"shape_nbr %4d shape_nvertices %5d num_segments %3d\n",current_shape->shape_nbr,current_shape->shape_nvertices, current_shape->num_segments);
      current_segment = current_shape->segment_list;
      while (current_segment != NULL) {
        fprintf(fp," Segment %3d tile_index %ld str [%s] path [%s] vertices %5d start %d end %d\n",
               current_segment->segment_n,
               current_segment->tile_index,
               current_segment->tile_nbr_str,
               current_segment->tile_path_str,
               current_segment->seg_n_vertices,
               current_segment->seg_vertice_start->vertice_nbr,
               current_segment->seg_vertice_end->vertice_nbr
                );
        current_segment = current_segment->next_segment;
      }
      current_shape = current_shape->next_shape;
    }
    fclose(fp);
  }
  else printf("unable to open [%s] to summarize .shp file\n",fn);
}

void shapefile::summarize_shp(char * fn)
{
  std::string ffn = summaries_path + fn;
  ffn +="_shp_data.txt";
  FILE * fp;
  fp = fopen(ffn.c_str(),"w++");
  if (fp != NULL) {
    fprintf(fp,"shp file summary\n");
    int nPrecision = 15;                   // copied from mainshp()
    current_shape = shp_data->shape_list;
    while (current_shape != NULL) {
      fprintf(fp,"shape_nbr %d shape_nvertices %d\n",current_shape->shape_nbr,current_shape->shape_nvertices);
      current_vertice = current_shape->vertice_list;
      while (current_vertice != NULL) {
        fprintf(fp,"     vertice_nbr %d (%.*g,%.*g)\n",
	      current_vertice->vertice_nbr,
	      nPrecision,current_vertice->x,
	      nPrecision,current_vertice->y);
        current_vertice = current_vertice->next_vertice;
      }
      current_shape = current_shape->next_shape;
    }
    fclose(fp);
  }
  else printf("unable to open [%s] to summarize .shp file\n",fn);
}
int shapefile::read_dbf( char * file )
{
   DBFHandle	hDBF;
    int		*panWidth, i, iRecord;
    char	szFormat[32]; //, *pszFilename = NULL;
    int		nWidth, nDecimals;
    int		bHeader = 0;
    int		bRaw = 0;
    int		bMultiLine = 0;
    char	szTitle[400];         //   char	szTitle[12];  openeagle hack fadds dbf fields currently char 200 (2021-january)

/* -------------------------------------------------------------------- */
/*      Open the file.                                                  */
/* -------------------------------------------------------------------- */
    hDBF = DBFOpen( file, "rb" );

    if( hDBF == NULL )
    {
  	  printf( "DBFOpen(%s,\"r\") failed.\n", file );
  	  exit( 2 );
    }
/* -------------------------------------------------------------------- */
/*	If there is no data in this file let the user know.		*/
/* -------------------------------------------------------------------- */
    if( DBFGetFieldCount(hDBF) == 0 )
    {
	  printf( "There are no fields in this table!\n" );
	    exit( 3 );
    }
/* -------------------------------------------------------------------- */
/*	Dump header definitions.					*/
/* -------------------------------------------------------------------- */
    if( bHeader )
    {
        for( i = 0; i < DBFGetFieldCount(hDBF); i++ )
        {
            DBFFieldType	eType;
//              const char	 	*pszTypeName;
//              char chNativeType;
                                           //openeagle   chNativeType = DBFGetNativeFieldType( hDBF, i );
            eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );
/** openeagle
            if( eType == FTString )
                pszTypeName = "String";
            else if( eType == FTInteger )
                pszTypeName = "Integer";
            else if( eType == FTDouble )
                pszTypeName = "Double";
            else if( eType == FTInvalid )
                pszTypeName = "Invalid";

              printf( "Field %d: Type=%c/%s, Title=`%s', Width=%d, Decimals=%d\n",
                    i, chNativeType, pszTypeName, szTitle, nWidth, nDecimals );
**/
        }
    }
/* -------------------------------------------------------------------- */
/*	Compute offsets to use when printing each of the field 		*/
/*	values. We make each field as wide as the field title+1, or 	*/
/*	the field value + 1. 						*/
/* -------------------------------------------------------------------- */
    panWidth = (int *) malloc( DBFGetFieldCount( hDBF ) * sizeof(int) );
    dbf_data->num_fields = DBFGetFieldCount(hDBF);
    for( i = 0; i < DBFGetFieldCount(hDBF) && !bMultiLine; i++ )
    {
  	  DBFFieldType	eType;

	  eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );
	  if( (int) strlen(szTitle) > nWidth )
	      panWidth[i] = strlen(szTitle);
	  else
	      panWidth[i] = nWidth;

  	  if( eType == FTString )
	    sprintf( szFormat, "%%-%ds ", panWidth[i] );
	  else
	    sprintf( szFormat, "%%%ds ", panWidth[i] );

/* -------------------------------------------------------------------- */
/*	openeagle hack: build field list records                        */
/* -------------------------------------------------------------------- */
     // printf("build field list records\n");
      if (i ==0) {
        field_list = new struct field_record;
        field_list->next_field = NULL;
	    dbf_data->field_list = field_list;    // start dbf_data field list with first node
      }
	  else {
        temp_field_list = new struct field_record;
        temp_field_list->next_field = NULL;
	    field_list->next_field = temp_field_list;
	    field_list = temp_field_list;
      }
      strcpy(field_list->field_name,szTitle);
/*end	openeagle hack: build field list records                        */
    }
 /* -------------------------------------------------------------------- */
/*	Read all the records 						*/
/* -------------------------------------------------------------------- */
    dbf_data->num_records = DBFGetRecordCount(hDBF);
   // printf("read %d records\n",dbf_data->num_records);
    for( iRecord = 0; iRecord < DBFGetRecordCount(hDBF); iRecord++ )
    {
/* -------------------------------------------------------------------- */
/*	openeagle hack: initialize record_data                          */
/* -------------------------------------------------------------------- */
    //   printf(" record %d\n",iRecord);

        if (iRecord ==0) {
          first_record =  new struct record_data;
	      first_record->record_nbr = iRecord;
	      first_record->data = NULL;
	      first_record->next_record = NULL;
	      current_record= first_record;
	      dbf_data->record_list=first_record;
	    }
	    else {
          temp_record = new struct record_data;
	      temp_record->record_nbr = iRecord;
	      temp_record->next_record = NULL;
	      temp_record->next_record = NULL;
	      current_record->next_record = temp_record;
	      current_record = temp_record;
  	    }

/*end	openeagle hack: initialize record_data                          */
/** openeagle
        if( bMultiLine )
            printf( "Record: %d\n", iRecord );
**/
	for( i = 0; i < DBFGetFieldCount(hDBF); i++ )
	{
            DBFFieldType	eType;
            eType = DBFGetFieldInfo( hDBF, i, szTitle, &nWidth, &nDecimals );

/* -------------------------------------------------------------------- */
/*	openeagle hack: initialize field_data record                    */
/* -------------------------------------------------------------------- */
      //  printf("     field %d\n",i);
        if (i==0) {
           first_data_list = new struct field_data;
 	       first_data_list->next_data = NULL;
	       current_data_list = first_data_list;
	       current_record->data = first_data_list;
	     }
	     else {
           temp_data_list = new struct field_data;
	       temp_data_list->next_data = NULL;
	       current_data_list->next_data = temp_data_list;
	       current_data_list = temp_data_list;
  	     }
  	     current_data_list->field_nbr = i;
	                                          //  }
/*end	openeagle hack: initialize field_data record                    */

/** openeagle
            if( bMultiLine )
            {
                printf( "%s: ", szTitle );
            }
**/
/* -------------------------------------------------------------------- */
/*      Print the record according to the type and formatting           */
/*      information implicit in the DBF field description.              */
/* -------------------------------------------------------------------- */
            if( !bRaw )
            {
                if( DBFIsAttributeNULL( hDBF, iRecord, i ) )
                {
                    if( eType == FTString )
                        sprintf( szFormat, "%%-%ds", nWidth );
                    else
                        sprintf( szFormat, "%%%ds", nWidth );
/** openeagle
                    printf( szFormat, "(NULL)" );
**/
/* -------------------------------------------------------------------- */
/*	openeagle hack: copy file data for NULL entry                   */
/* -------------------------------------------------------------------- */
		      strcpy(current_data_list->field_data_char,"(NULL)");
/*end	openeagle hack: copy file data for NULL entry                   */
		        }
                else
                {
                    bool intFieldType = false;
                    int intfield;
                    bool doubleFieldType = false;
                    double doublefield;
                    std::string formatNumber;
                    switch( eType )
                    {
                      case FTString:
                     //   printf("FTString\n");
/** openeagle **/
                  //      sprintf( szFormat, "%%-%ds", nWidth );
                  //      printf( szFormat,
                  //             DBFReadStringAttribute( hDBF, iRecord, i ) );
/** **/
/* -------------------------------------------------------------------- */
/*	openeagle hack: copy field data currently fadds is all char     */
/* -------------------------------------------------------------------- */
               		    strcpy(current_data_list->field_data_char,DBFReadStringAttribute( hDBF, iRecord, i ));
                       // printf("strcpy survived\n");

/*end	openeagle hack: copy field data currently fadds is all char   but sua ain't!    */
                        break;
/** openeagle  **/
                      case FTInteger:
                         // printf("FTInteger\n");
                          /**  **/
                       // sprintf( szFormat, "%%%dd", nWidth );
                       // printf( szFormat,
                       //         DBFReadIntegerAttribute( hDBF, iRecord, i ) );
                            /**    **/
                        intfield = DBFReadIntegerAttribute( hDBF, iRecord, i );
                        intFieldType = true;
                        formatNumber = "";
                        formatNumber += std::to_string(intfield);
                        strcpy(current_data_list->field_data_char,formatNumber.c_str());
                       // printf("strcpy survived\n");
                        break;

                      case FTDouble:
                        //  printf("double\n");

                  //      sprintf( szFormat, "%%%d.%dlf", nWidth, nDecimals );
                    //    printf( szFormat,
                      //          DBFReadDoubleAttribute( hDBF, iRecord, i ) );
                        doublefield = DBFReadDoubleAttribute( hDBF, iRecord, i );
                        doubleFieldType = true;
                        formatNumber = "";
                        formatNumber += std::to_string(intfield);
                        strcpy(current_data_list->field_data_char,formatNumber.c_str());
                       // printf("strcpy survived\n");
                        break;
/**   **/
                      default:
                        break;
                    }
                }
            }

/* -------------------------------------------------------------------- */
/*      Just dump in raw form (as formatted in the file).               */
/* -------------------------------------------------------------------- */
            else
            {
/** openeagle
                sprintf( szFormat, "%%-%ds", nWidth );
                printf( szFormat,
                        DBFReadStringAttribute( hDBF, iRecord, i ) );
**/
            }

/* -------------------------------------------------------------------- */
/*      Write out any extra spaces required to pad out the field        */
/*      width.                                                          */
/* -------------------------------------------------------------------- */
/** openeagle
	    if( !bMultiLine )
	    {
		sprintf( szFormat, "%%%ds", panWidth[i] - nWidth + 1 );
		printf( szFormat, "" );
	    }

            if( bMultiLine )
                printf( "\n" );
**/
//	    fflush( stdout );

	}
/** openeagle
        if( DBFIsRecordDeleted(hDBF, iRecord) )
            printf( "(DELETED)" );

	printf( "\n" );
**/
    }

    DBFClose( hDBF );
    free( panWidth );
/** open eagle **/
printf("dbf processing completed\n");
    return( 0 );
}

int shapefile::read_shp( char * file)
{

    tile T;
    SHPHandle	hSHP;
    int		nShapeType, nEntities, i, iPart, bValidate = 0,nInvalidCount=0;
    int         bHeaderOnly = 0;
    const char 	*pszPlus;
    double 	adfMinBound[4], adfMaxBound[4];
  //  int nPrecision = 15;
//printf("read_shp( ... )\n");

/* ----------------------------------------------------------------------- */
/*      openeagle Hack: initialize shp_record                              */
/* ----------------------------------------------------------------------- */
    shp_data = (shp_record *)malloc(sizeof(struct shp_record));
    shp_data->shape_list = NULL;
/*end      openeagle Hack: initialize shp record                           */

/* -------------------------------------------------------------------- */
/*      Open the passed shapefile.                                      */
/* -------------------------------------------------------------------- */
    hSHP = SHPOpen( file, "rb" );

    if( hSHP == NULL )
    {
        printf( "Unable to open:%s\n", file ); //argv[1] );
        exit( 1 );
    }

/* -------------------------------------------------------------------- */
/*      Print out the file bounds.                                      */
/* -------------------------------------------------------------------- */
    SHPGetInfo( hSHP, &nEntities, &nShapeType, adfMinBound, adfMaxBound );
/** openeagle
    printf( "File Bounds: (%.*g,%.*g,%.*g,%.*g)\n"
            "         to  (%.*g,%.*g,%.*g,%.*g)\n",
            nPrecision, adfMinBound[0],
            nPrecision, adfMinBound[1],
            nPrecision, adfMinBound[2],
            nPrecision, adfMinBound[3],
            nPrecision, adfMaxBound[0],
            nPrecision, adfMaxBound[1],
            nPrecision, adfMaxBound[2],
            nPrecision, adfMaxBound[3] );
**/
/* -------------------------------------------------------------------- */
/*	Skim over the list of shapes, printing all the vertices.	*/
/* -------------------------------------------------------------------- */
    if (read_limit > 0) {  nEntities = read_limit;
      dbf_data->num_records = read_limit;
     // printf(" read_limit should control at %d\n",read_limit);
    }
    shp_data->nentities = nEntities;

    for( i = 0; i < nEntities && !bHeaderOnly; i++ )
    {
       // printf("shape %d of %d\n",i,nEntities);
       /* ----------------------------------------------------------------------- */
       /*      openeagle Hack: initialize shape record capture relevent fields/data */
       /* ----------------------------------------------------------------------- */
       if (i==0) {  // first
         first_shape = (shape_record *) malloc(sizeof(struct shape_record));
         first_shape->next_shape = NULL;
	     first_shape->vertice_list = NULL;
	     first_shape->num_segments = 0;
	     first_shape->segment_list = NULL;
  	     current_shape = first_shape;
  	     // bind shp_data for head of shape list
	     shp_data->shape_list = first_shape;
       }
       else {
         temp_shape = (shape_record *) malloc(sizeof(struct shape_record));
         temp_shape->next_shape = NULL;
	     current_shape->next_shape = temp_shape;
	     current_shape = current_shape->next_shape;
	     current_shape->num_segments = 0;
	     current_shape->segment_list = NULL;
       }
       current_shape->shape_nbr = i;
       /*end      openeagle Hack: initialize shape_record                         */

        int		j;
        SHPObject	*psShape;

        psShape = SHPReadObject( hSHP, i );

        if( psShape == NULL )
        {
            fprintf( stderr,
                     "Unable to read shape %d, terminating object reading.\n",
                    i );
            break;
        }
/** openeagle        if( psShape->bMeasureIsUsed ) printf("bMeasureIsUsed\n"); else printf("bMeasureIsUsed NOT\n"); exit(1);  **/
/* -------------------------------------------------------------------- */
/*	openeagle hack: trim i/o                                        */
/* -------------------------------------------------------------------- */

/*end	openeagle hack: trim i/o                                        */

        if( psShape->nParts > 0 && psShape->panPartStart[0] != 0 )
        {
            fprintf( stderr, "panPartStart[0] = %d, not zero as expected.\n",
                     psShape->panPartStart[0] );
        }

// openeagle set current_shape n vertices
        current_shape->shape_nvertices =psShape->nVertices;
// openeagle lon/lat variables to analyze tile #'s and tile path(s)
        double lon;
        double lat;
       // long int current_tile_index;
        for( j = 0, iPart = 1; j < psShape->nVertices; j++ )
        {
          // printf("     vertice %d\n",j);
        /* ----------------------------------------------------------------------- */
        /*      openeagle Hack: initialize vertice_record                          */
        /* ----------------------------------------------------------------------- */
        if (j==0) {
           // first vertice
           first_vertice = (vertice_record *)malloc(sizeof(struct vertice_record));
           last_vertice = NULL;
           first_vertice->next_vertice = NULL;
	       current_shape->vertice_list = first_vertice;
 	       current_vertice = first_vertice;

  	       current_vertice->vertice_nbr = j;
	       current_vertice->x = psShape->padfX[j];
	       current_vertice->y = psShape->padfY[j];

         }
         else {
           temp_vertice = (vertice_record *) malloc(sizeof(struct vertice_record));
           temp_vertice->next_vertice = NULL;
           last_vertice = current_vertice;
           current_vertice->next_vertice = temp_vertice;
           current_vertice = temp_vertice;

  	       current_vertice->vertice_nbr = j;
	       current_vertice->x = psShape->padfX[j];
	       current_vertice->y = psShape->padfY[j];

	         lon = get_vertice_long();
             lat = get_vertice_lat();

             T.set_tile(lon,lat);
             long int tile_index = T.gen_index();

         }
         //printf("vertex %d x %f y %f\n",j,current_vertice->x, current_vertice->y);
         /*end      openeagle Hack: initialize vertice_record                         */

	    const char	*pszPartType = "";

            if( j == 0 && psShape->nParts > 0 )
                pszPartType = SHPPartTypeName( psShape->panPartType[0] );

            if( iPart < psShape->nParts
                && psShape->panPartStart[iPart] == j )
            {
                pszPartType = SHPPartTypeName( psShape->panPartType[iPart] );
                iPart++;
                pszPlus = "+";
                printf(" warning part issue on shape %d\n",current_shape->shape_nbr);
              //  exit(1);
            }
            else
                pszPlus = " ";
            /* -------------------------------------------------------------------- */
            /*	openeagle hack: trim i/o on point and only show x, y                */
            /* -------------------------------------------------------------------- */
/**
            if( psShape->bMeasureIsUsed )
                printf("   %d %s (%.*g,%.*g) %s \n",
		       j,
                       pszPlus,
                       nPrecision, psShape->padfX[j],
                       nPrecision, psShape->padfY[j],
                                           //nPrecision, psShape->padfZ[j],
                                           //nPrecision, psShape->padfM[j],
                       pszPartType );
            else
                printf("   %d %s (%.*g,%.*g) %s \n",
		       j,
                       pszPlus,
                       nPrecision, psShape->padfX[j],
                       nPrecision, psShape->padfY[j],
                                           //   nPrecision, psShape->padfZ[j],
                       pszPartType );
**/

	}
/**
            if( psShape->bMeasureIsUsed )
                printf("   %s (%.*g,%.*g, %.*g, %.*g) %s \n",
                       pszPlus,
                       nPrecision, psShape->padfX[j],
                       nPrecision, psShape->padfY[j],
                       nPrecision, psShape->padfZ[j],
                       nPrecision, psShape->padfM[j],
                       pszPartType );
            else
                printf("   %s (%.*g,%.*g, %.*g) %s \n",
                       pszPlus,
                       nPrecision, psShape->padfX[j],
                       nPrecision, psShape->padfY[j],
                       nPrecision, psShape->padfZ[j],
                       pszPartType );
        }
**/
            /*end	openeagle hack: trim i/o on point and only show x, y            */

        if( bValidate )
        {
            int nAltered = SHPRewindObject( hSHP, psShape );

            if( nAltered > 0 )
            {
                printf( "  %d rings wound in the wrong direction.\n",
                        nAltered );
                nInvalidCount++;
                exit(1);
            }
        }

        SHPDestroyObject( psShape );
    }

    SHPClose( hSHP );

    if( bValidate )
    {
        printf( "%d object has invalid ring orderings.\n", nInvalidCount );
    }

#ifdef USE_DBMALLOC
    malloc_dump(2);
#endif

    return( 0 );                           //   exit( 0 );

}

void shapefile::adjust_vertices_for_max_line_length()
{
/* -------------------------------------------------------------------- */
/*	check distance between vertices and if longer than                  */
/*  MAX_LINE_LENGTH_FEET                                                */
/*  insert intermediate vertices and adjust shape record for n vertices */
/* -------------------------------------------------------------------- */
/*  segments are produced AFTER adjusting vertice lists for shapes      */
/* -------------------------------------------------------------------- */
  printf("adjust_vertices_for_max_line_length()\n");
  reset_dbf_shp();
  int shp_nentities =get_shp_nentities();
  for (int shp_n = 0; shp_n< shp_nentities; shp_n++) {
    printf("shp_n %d of %d\n",shp_n, shp_nentities);
    int shp_n_vertices = current_shape->shape_nvertices;
    printf("shp_n %d n vertices %d\n",shp_n,shp_n_vertices);
    current_vertice = current_shape->vertice_list;
    bool renumber=false;
    double x = 90;
    double y = 90;
    double last_x = 90;
    double last_y = 90;
    last_vertice = NULL;
    for (int seg_v = 0; seg_v < shp_n_vertices; seg_v++) {  // vertices within shape loop
//      int nPrecision = 15;
  ///    printf("          seg_v %d (%.*g,%.*g)",current_vertice->vertice_nbr, nPrecision,current_vertice->x, nPrecision,current_vertice->y);
      if (last_vertice != NULL) {  // check distance between vertices
        double r;
        double az;
        double az2;
        x = current_vertice->x;
	    y = current_vertice->y;

        geo_inverse_wgs_84(last_y,last_x, y,x, &az, &az2,&r);
   //     printf(" delta vertices %f",r*SG_METER_TO_FEET);
         //   printf(" lst_lat %.*g, lst_lon %.*g lat %.*g lon %.*g ",nPrecision,last_y, nPrecision,last_x, nPrecision,y, nPrecision,x);
        if (r*SG_METER_TO_FEET > MAX_LINE_LENGTH_FEET) {
//           printf("shp_n %d n vertices %d current v %d last %d\n",shp_n,shp_n_vertices,last_vertice->vertice_nbr,current_vertice->vertice_nbr);
//           printf("     last x %.*g last y %.*g\n",nPrecision,last_x,nPrecision,last_y);
//           printf("          x %.*g      y %.*g\n",nPrecision,x,nPrecision,y);
//           printf("     delta vertices %f feet\n",r*SG_METER_TO_FEET);
           renumber = true;
           double multiplier = r*SG_METER_TO_FEET/MAX_LINE_LENGTH_FEET;
           double multiplier2 = multiplier+1.0;
           int imult = multiplier;   // multipoer = 1.1
           int imult2 = multiplier2;
           if (imult != imult2) imult = imult2; //sloppy ceiling
           double dmult = imult;
//           printf("     need to add %f lines or %d\n",multiplier,imult);
/* -------------------------------------------------------------------- */
/*	                         7.1 miles imult = 7                        */
/*      Vl-------------------------------------------------V            */
/*                  imult                                               */
/*	                number of vertices added is imult-1                 */
/*      Vl-------vi------v2------v3-----v4-----v5----vi----V            */
/*                                                                      */
/*	                                                                    */
/*      Ri = R*(i/imult)                                                */
/*      R1 = R*(1/7)                                                    */
/*	    R2 = R*(2/7)                                                    */
/*      R3 = R*(3/7)                                                    */
/*      R4 = R*(4/7)                                                    */
/*	    R5 = R*(5/7)                                                    */
/*      R6 = R*(6/7)                                                    */
/*                                                                      */
/*	    (1) adjust shape record number of vertices by imult-1           */
/*      (2) record R6-> V                                               */
/*      (3) Vl-> R1                                                     */
/*      (4) clean up at end of shape by renumbering vertices as req'd   */
/* -------------------------------------------------------------------- */
          double delta_x = current_vertice->x - last_vertice->x;
          double delta_y = current_vertice->y - last_vertice->y;

//          printf("     delta_x %.*g  delta_y %.*g degrees\n",nPrecision,delta_x, nPrecision, delta_y);
          struct vertice_record * start_list;
          struct vertice_record * end_list;
          struct vertice_record * a_vertice;

          start_list = (vertice_record *) malloc(sizeof(struct vertice_record));
          start_list->vertice_nbr = 1;
          start_list->x = last_vertice->x+ delta_x*(1.0/dmult);
          start_list->y = last_vertice->y + delta_y*(1.0/dmult);
          start_list->next_vertice = NULL;

          end_list = start_list;

//          printf("          1.0/%f\n",dmult);
          if (imult >2) {
            for (int vi = 2; vi < imult; vi++ ) {
              double dvi = vi;
  //            printf("          %f/%f\n",dvi,dmult);
              a_vertice = (vertice_record *) malloc(sizeof(struct vertice_record));
              end_list->next_vertice = a_vertice;
              a_vertice->x = last_vertice->x+ delta_x*(dvi/dmult);
              a_vertice->y = last_vertice->y + delta_y*(dvi/dmult);

              a_vertice->vertice_nbr = end_list->vertice_nbr+1;
              a_vertice->next_vertice = NULL;
              end_list = a_vertice;
            }
          }
    //      printf("     insert list elements\n");
          a_vertice=start_list;
          /**
          int j=0;
          do {
            a_vertice = a_vertice->next_vertice;
            j++;
          } while (a_vertice != NULL);
          **/
          end_list->next_vertice = current_vertice;
          last_vertice->next_vertice = start_list;
        }

        //else printf("\n");
      }  // last_vertice != NULL;
     // printf("\n");
      last_x = current_vertice->x;
	  last_y = current_vertice->y;
      last_vertice = current_vertice;
      current_vertice = current_vertice->next_vertice;
    //  printf("\n");
    } // vertice within shape loop
 //   printf("*********************************fini adjusting vertice distances ************************************\n");
    if (renumber==true) {
   //   printf("renumber....\n");
      current_vertice = current_shape->vertice_list;
      int i = 0;
      while (current_vertice != NULL ){
        current_vertice->vertice_nbr = i;
        i++;
        current_vertice = current_vertice->next_vertice;
      }
      current_shape->shape_nvertices = i;


     // printf("renumberd to %d\n",i);
     // printf("recheck\n");
      current_vertice = current_shape->vertice_list;
      last_vertice = NULL;
      shp_n_vertices = current_shape->shape_nvertices;
    //  printf("shp_n %d n vertices %d\n",shp_n,shp_n_vertices);
      shp_n_vertices = current_shape->shape_nvertices;
      for (int seg_v = 0; seg_v < shp_n_vertices; seg_v++) {  // vertices within shape loop
//        int nPrecision = 15;
    //    printf("          seg_v %d (%.*g,%.*g)",current_vertice->vertice_nbr, nPrecision,current_vertice->x, nPrecision,current_vertice->y);
/**
        if (last_vertice != NULL) {  // check distance between vertices
          double r;
          double az;
          double az2;
          x = current_vertice->x;
	      y = current_vertice->y;

          geo_inverse_wgs_84(last_y,last_x, y,x, &az, &az2,&r);
      //    printf(" delta vertices %f",r*SG_METER_TO_FEET);
        }  // last_vertice != NULL;
        printf("\n");
        **/
        last_x = current_vertice->x;
	    last_y = current_vertice->y;
        last_vertice = current_vertice;
        current_vertice = current_vertice->next_vertice;
      }
    }
    current_shape = current_shape->next_shape;

  }  // shape loop
}


void shapefile::set_segments()
{
  tile T;
/* -------------------------------------------------------------------- */
/*  with vertices down to less than MAX_LINE_LENGTH_FEET can now do     */
/*  the segmentation of the vertex list with respect to FlighGear tiles */
/* -------------------------------------------------------------------- */
  reset_dbf_shp();
  int shp_nentitities =get_shp_nentities();
  for (int shp_n = 0; shp_n< shp_nentitities; shp_n++) {
    int shp_n_vertices = current_shape->shape_nvertices;
  //  printf("shape %d n vertices %d\n",shp_n,shp_n_vertices);
    current_vertice = current_shape->vertice_list;
    //double seg_j = 0;
    for (int vi = 0; vi < shp_n_vertices; vi++) {
      if (vi==0) {
    	temp_segment = (segment_record *) malloc(sizeof(struct segment_record)); // initialize first segment record;
  	    current_segment = temp_segment;
  	    current_shape->segment_list = current_segment; // bind segment list for current shape
  	    current_shape->num_segments++;
        current_segment->next_segment = NULL;
        current_segment->segment_n =  0;
        current_segment->seg_vertice_start = current_vertice;
        current_segment->seg_vertice_end = current_vertice;
        current_segment->seg_n_vertices = 1;
        double lon = get_vertice_long();
        double lat = get_vertice_lat();
        T.set_tile(lon,lat);
        current_segment->tile_index = T.gen_index();  // tile_index for current segment
        current_segment->tile_ctr_latitude = T.get_center_lat();
        current_segment->tile_ctr_longitude = T.get_center_lon();
        std::string tile_index_str = T.gen_index_str();
        strcpy(current_segment->tile_nbr_str , T.gen_index_str().c_str() );
        std::string tile_base_path = T.gen_base_path();
        strcpy(current_segment->tile_path_str , T.gen_base_path().c_str() );
      }
      else {
        double lon = get_vertice_long();
        double lat = get_vertice_lat();
        T.set_tile(lon,lat);
        long int tile_index = T.gen_index();
        if (tile_index != current_segment->tile_index) {  // new segment// change of tiles in FlightGear
  	      temp_segment = (segment_record *) malloc(sizeof(struct segment_record));
  	      temp_segment->segment_n = current_segment->segment_n +1;  // initialize next segment record;
  	      current_segment->next_segment = temp_segment;

  	      if (current_segment->seg_n_vertices ==1) { // check for short segment
           // printf("caution segment [%d] only had one vertice...fixed it ...maybe\n",current_segment->segment_n);
            // need at least 2 fence post issue with tile boundaries but they are only a mile away...
            current_segment->seg_n_vertices = 2;
            current_segment->seg_vertice_end = current_vertice;
  	      }
  	      //else {
          temp_segment->seg_vertice_start = current_segment->seg_vertice_end;
  	      //}

  	      current_segment = temp_segment;

  	      current_shape->num_segments++;
          current_segment->next_segment = NULL;
//          current_segment->seg_vertice_start = last_vertice;  // look back one first will be for previous segment (cross tile boundary)
          current_segment->seg_vertice_end   = current_vertice;
          current_segment->seg_n_vertices = 2; // start out with 2 vertices
          n_segment++;

  	      lon = get_vertice_long();  // current vertice set's the index as last likely on different tile...
          lat = get_vertice_lat();
          T.set_tile(lon,lat);
          current_segment->tile_index = T.gen_index();
          current_segment->tile_ctr_latitude = T.get_center_lat();
          current_segment->tile_ctr_longitude = T.get_center_lon();

          std::string tile_index_str = T.gen_index_str();
          std::string tile_base_path = T.gen_base_path();
          strcpy(current_segment->tile_nbr_str , tile_index_str.c_str());
          strcpy(current_segment->tile_path_str , tile_base_path.c_str());
        }
        else {
 	      current_segment->seg_n_vertices++;
          current_segment->seg_vertice_end = current_vertice;
        }
      }
      current_vertice = current_vertice->next_vertice;
    }
    current_shape = current_shape->next_shape;
  }
}
