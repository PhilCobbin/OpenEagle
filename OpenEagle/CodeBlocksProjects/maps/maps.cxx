/***************************************************************
 * Name:      maps.cxx
 * Purpose:   Code for generation of leaflet tiled maps for OpenEagle maps in FlightGear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2021-04-18
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
#include "../maps/maps.hxx"
#include "../OpenEaglePaths/OpenEaglePaths.hxx"
#include "../system_io/system_io.hxx"
#include <iostream>
#include <sys/stat.h>
//#include <time.h>
//#include <stdio.h>
bool maps::lookup_map(char * tiff_file)
{
  avl_ptr = search_avl_tree (tiff_file, false, head_avl_tif);
  if (avl_ptr != NULL) {
    map_update_ptr = (struct map_update*) avl_ptr->data_ptr;
    map_index = map_update_ptr->index;
    return true;
  }
  else return false;
}

char * maps::map_directory()
{
  if (avl_ptr == NULL) return NULL;
  return (char *)map_update_ptr->map_dir.c_str();
}

void maps::generate_maps_script()
{
/**
echo initial directory:
ls
echo "Albuquerque_Sectional:"
cd ..
cd Programs/OpenEagleMaps/Albuquerque_Sectional
./Albuquerque_Sectional.sh
echo post run
cd ..
cd ..
cd ..
cd Sectionals
echo final directory
ls
**/
  std::string maps_script = "";
  for (int i = 0; i< MAP_LIST_SIZE; i++) {
    maps_script += "echo ";
    maps_script += map_list[i].map_dir.c_str();
    maps_script += ":\n";
    maps_script += "cd ..\n";
    maps_script += "cd Programs/OpenEagleMaps/";
    maps_script += map_list[i].map_dir.c_str();
    maps_script += "\n";
    maps_script += "./";
    maps_script += map_list[i].map_dir.c_str();
    maps_script += ".sh\n";
    maps_script += "cd ..\n";
    maps_script += "cd ..\n";
    maps_script += "cd ..\n";
    maps_script += "cd Sectionals\n";
  }
  std::string fn = path.OpenEaglePath.c_str();
  fn+= "/Sectionals/generate_maps.sh";
  FILE * fp = fopen(fn.c_str(),"w");
  if (fp == NULL) {
    printf("could not open [%s]\n",fn.c_str());
    exit(1);
  }
  fprintf(fp,"%s\n)",maps_script.c_str());
  fclose(fp);
/// chmod +x filename.sh
  std::string command = "chmod +x ";
  command += fn.c_str();
  command += "\n";
  bool okay = system_io(&command);
  if (!okay) printf("unable to make script %s execuable\n",fn.c_str());
}

void maps::generate_files()
{
  printf("maps::generate_iles():\n");

  std::string update_destination = path.OpenEaglePath.c_str();
  update_destination += "/Update/";

  std::string destination = path.OpenEaglePath.c_str();
  destination += "/Programs/OpenEagleMaps/";


  FILE * fp;
  struct stat st;
  int fd;
  off_t size;
/** Index.html **/
  char index_buffer[500];
  std::string index = update_destination;
  index += "index.html";
  fp = fopen (index.c_str(), "r");
  if (fp == NULL)
  {
    printf("Cannot [%s].\n",index.c_str());
    exit(1);
  }
  fd = fileno(fp);    // get file descriptor
  fstat(fd, &st);
  size = st.st_size;
  fread(&index_buffer,1,size,fp);
  fclose(fp);
/** map_section-1.txt **/
  char map_section_1_buffer[1500];
  std::string map_section_1 = update_destination;
  map_section_1 += "/map-section-1.txt";
  fp = fopen (map_section_1.c_str(), "r");
  if (fp == NULL)
  {
    printf("Cannot map-section-1.txt.\n");
    exit(1);
  }
  fd = fileno(fp);    // get file descriptor
  fstat(fd, &st);
  size = st.st_size;
  fread(&map_section_1_buffer,1,size,fp);
  printf("map_section_1:\n%s\n",map_section_1_buffer);
  fclose(fp);
/** map_section-2.txt **/
  char map_section_2_buffer[1000];
  std::string map_section_2 = update_destination;
  map_section_2 += "/map-section-2.txt";
  fp = fopen (map_section_2.c_str(), "r");
  if (fp == NULL)
  {
    printf("Cannot map-section-2.txt.\n");
    exit(1);
  }
  fd = fileno(fp);    // get file descriptor
  fstat(fd, &st);
  size = st.st_size;
  fread(&map_section_2_buffer,1,size,fp);
  printf("map_section_2:\n%s\n",map_section_2_buffer);
  fclose(fp);
/** map_section-3.txt **/
  char map_section_3_buffer[5000];
  std::string map_section_3 = update_destination;
  map_section_3 += "/map-section-3.txt";
  fp = fopen (map_section_3.c_str(), "r");
  if (fp == NULL)
  {
    printf("Cannot map-section-3.txt.\n");
    exit(1);
  }
  fd = fileno(fp);    // get file descriptor
  fstat(fd, &st);
  size = st.st_size;
  fread(&map_section_3_buffer,1,size,fp);
  printf("map_section_3:\n%s\n",map_section_3_buffer);
  fclose(fp);

  for (int i = 0; i< MAP_LIST_SIZE; i++) {
    std::string map_directory = "mkdir -p ";
    map_directory += destination.c_str();
    map_directory += map_list[i].map_dir.c_str();
    map_directory += "/";
    map_directory += "\n";
    printf("mkdir? map_directory:[%s]\n",map_directory.c_str());
    bool okay = system_io(&map_directory);
    if (!okay) printf("failed to make directory [%s]\n",map_directory.c_str());
    std::string full_fn = destination.c_str();
    full_fn += map_list[i].map_dir.c_str();
    full_fn += "/";
    full_fn += map_list[i].python_file.c_str();
    FILE * fp = fopen(full_fn.c_str(),"w++");
    if (fp != NULL) {
      fprintf(fp,"import processing\n");
      fprintf(fp,"processing.run('qgis:tilesxyzdirectory', { 'DPI' : 96, 'EXTENT' : ");
      fprintf(fp,map_list[i].map_ext.c_str());
      fprintf(fp,", 'METATILESIZE' : 4, 'OUTPUT_DIRECTORY' : ");
      fprintf(fp,"'.'");
      fprintf(fp,", 'QUALITY' : 75, 'TILE_FORMAT' : 0, 'TILE_HEIGHT' : 256, 'TILE_WIDTH' : 256, 'TMS_CONVENTION' : False, 'ZOOM_MAX' : 13, 'ZOOM_MIN' : 8 })\n\n");
      fprintf(fp,"import os\n");
      fprintf(fp,"os._exit(0)\n");
      fclose(fp);
    }
    else {
      printf("unable to open for writing [%s]\n",full_fn.c_str());
      exit(1);
    }
/// next: write copy of index.html
    full_fn = destination.c_str();
    full_fn += map_list[i].map_dir.c_str();
    full_fn += "/";
    full_fn += "index.html";
    fp = fopen(full_fn.c_str(),"w++");
    fwrite(&index_buffer,1,strlen(index_buffer),fp);
    fclose(fp);
/// next:write map.html
/// map_section_1
    full_fn = destination.c_str();
    full_fn += map_list[i].map_dir.c_str();
    full_fn += "/";
    full_fn += "map.html";
    fp = fopen(full_fn.c_str(),"w++");
    fwrite(&map_section_1_buffer,1,strlen(map_section_1_buffer),fp);
/**
    var map = L.map('map').setView([33.872545423990864, -106.02212992067871], 10.5);
      L.tileLayer('../../../Programs/OpenEagleMaps/Albuquerque_Sectional/{z}/{x}/{y}.png', {
        minZoom: 8,
        maxZoom: 13,
        tms: false,
        attribution: 'Generated by TilesXYZ'
      }).addTo(map);
**/
    fprintf(fp,"    var map = L.map('map').setView([%s], 10.5);\n",map_list[i].latlon.c_str());
    fprintf(fp,"      L.tileLayer('../../../Programs/OpenEagleMaps/%s/{z}/{x}/{y}.png', {\n",map_list[i].map_dir.c_str());
    fprintf(fp,"        minZoom: 8,\n");
    fprintf(fp,"        maxZoom: 13,\n");
    fprintf(fp,"        tms: false,\n");
    fprintf(fp,"        attribution: 'Generated by TilesZYZ'\n");
    fprintf(fp,"      }).addTo(map);\n");

/// map_section_2
    fwrite(&map_section_2_buffer,1,strlen(map_section_2_buffer)-1,fp);
///    var point = L.orientedMarker([33.872545423990864, -106.02212992067871],{ icon: airplaneIcon, angle: heading}).addTo(map)
    fprintf(fp,"    var point = L.orientedMarker([%s],{ icon: airplaneIcon, angle: heading}).addTo(map)\n",map_list[i].latlon.c_str());
/// map_section_3
    fwrite(&map_section_3_buffer,1,strlen(map_section_3_buffer),fp);
    fclose(fp);
/// Phoenix_Sectional.sh
///qgis --code Phoenix_Sectional.py 'Phoenix SEC.tif'
    full_fn = destination.c_str();
    full_fn += map_list[i].map_dir.c_str();
    full_fn += "/";
    full_fn += map_list[i].map_dir.c_str();
    full_fn += ".sh";
    fp = fopen(full_fn.c_str(),"w++");
    fprintf(fp,"qgis --code %s '%s'\n", map_list[i].python_file.c_str(),map_list[i].tif_file.c_str());
    fclose(fp);
/// chmod +x filename.sh
    std::string command = "chmod +x ";
    command += full_fn.c_str();
    command += "\n";
    okay = system_io(&command);
    if (!okay) printf("unable to make script %s execuable\n",full_fn.c_str());
  }
  generate_maps_script();
}

void maps::generate_map()
{
  std::string PythonFile = path.OpenEaglePath.c_str();
  PythonFile += "/Update/Maps_Python_Code/";
  PythonFile += map_list[map_index].python_file.c_str();
//  PythonFile += ".py";

  std::string command = "qgis ";
  command += " --code ";
  command += PythonFile.c_str();
  command += " '";
  command += map_list[map_index].tif_file.c_str();
  command += "'\n";
  system_io(&command);
/// issue: dateline split for Western_Aleutian_Islands_East_Sectional full map is on both sides of 180 longitude
  if (map_index == DATELINE_INDEX) {
    map_index ++;
    generate_map();
  }


 // printf("test[%s]\n",command.c_str());
}

void maps::generate_map_complete_set(char * sectional_zip_file, char * grand_canyon_zip_file)
{
  std::string bulk_path = path.OpenEaglePath.c_str();
  bulk_path += "/Update/Maps_TIF_Files/";
  std::string command = " cp ";
              command += sectional_zip_file;
              command += " ";
              command += bulk_path.c_str();
              command += "Sectional.zip\n";
  system_io(&command);
              command = " cp ";
              command += grand_canyon_zip_file;
              command += " ";
              command += bulk_path.c_str();
              command += "Grand_Canyon.zip\n";
  system_io(&command);
  command  = "cd ";
  command +=  path.OpenEaglePath.c_str();
  command += "/Update/Maps_TIF_Files";
  command += "\n";
  command += "unzip ";
              command += grand_canyon_zip_file;
              command += "\n";
  system_io(&command);
    command  = "cd ";
  command +=  path.OpenEaglePath.c_str();
  command += "/Update/Maps_TIF_Files";
  command += "\n";
  command += "unzip ";
              command += grand_canyon_zip_file;
              command += "\n";
  command += "unzip ";
              command += sectional_zip_file;
              command += "\n";
  system_io(&command);

  std::string PythonFilePath = path.OpenEaglePath.c_str();
  PythonFilePath += "/Update/Maps_Python_Code/";

  for (int i = 0; i< MAP_LIST_SIZE; i++) {
    command = "qgis ";
    command += " --code ";
    command += PythonFilePath.c_str();
    command += map_list[i].python_file.c_str();
    command += " '";
    command += bulk_path.c_str();
    command += map_list[i].tif_file.c_str();
    command += "'\n";
    printf("%s",command.c_str());
   // system_io(&command);
  }
}
