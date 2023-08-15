/***************************************************************
 * Name:      OpenEaglePaths.cxx
 * Purpose:   Manage flightgear and OpenEagle paths
 * Author:    Philip Cobbin (phil@cobbin.com)
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
#include "OpenEaglePaths.hxx"
#include "../read_data/read_data.hxx"
#include "../system_io/system_io.hxx"

bool OpenEaglePaths::setupOpenEaglePaths(char * name,char * write_path)
{
  printf("setupOpenEaglePaths(%s)\n",name);
  home = getenv("HOME");
  OpenEagle_str = home;
  OpenEagle_str += "/.OpenEagle";
  FILE * fp;
  std::string fn;
  fn  = OpenEagle_str;
  fn += "/OpenEaglePath.txt";
  fp = fopen(fn.c_str(), "r");
  if (fp == NULL) {
    printf("could not open [%s]",fn.c_str());
    return false;
  }
  char buffer[2000];
  read_field(fp,(char *)&buffer,sizeof(buffer),tc2);
  int i = 0;
  bool done = false;
  OpenEaglePath = "";
  while (!done) {
    if (buffer[i] != '\n') {
      OpenEaglePath += buffer[i];
      i++;
    }
    else {
      done = true;
    }
  }
  fclose(fp);
  printf("OpenEaglePath[%s]\n",OpenEaglePath.c_str());


  fn  = OpenEagle_str;
  fn += "/OpenEagle-FlightGear-Path.txt";
  fp = fopen(fn.c_str(), "r");
  if (fp == NULL) {
    printf("could not open [%s]",fn.c_str());
    return false;
  }

  read_field(fp,(char *)&buffer,sizeof(buffer),tc2);
  i = 0;
  done = false;
  OpenEagle_FlightGear_Path = "";
  while (!done) {
    if (buffer[i] != '\n') {
      OpenEagle_FlightGear_Path += buffer[i];
      i++;
    }
    else {
      done = true;
    }
  }
  fclose(fp);
  printf("OpenEagle_FlightGear_Path[%s]\n",OpenEagle_FlightGear_Path.c_str());

  setupOpenEagleSubPaths();
  setupOpenEagleMastersPaths();
  setupOpenEagleWritePaths(write_path);
  printf("setupOpenEaglePaths()::finishes\n");
  return true;
}
void OpenEaglePaths::setupOpenEagleSubPaths()
{
  printf("setupOpenEagleSubPaths()\n");
  airport_sign_base_path         = "/Models/Airports";
  class_airspace_subpath         = "/Models/Class_Airspace";
  boundary_airspace_subpath      = "/Models/Boundary_Airspace";
  SUA_airspace_subpath           = "/Models/Special_Use_Airspace";

  printf("airport_sign_base_path         = %s\n",airport_sign_base_path.c_str());
  printf("class_airspace_subpath         = %s\n",class_airspace_subpath.c_str());
  printf("boundary_airspace_subpath      = %s\n",boundary_airspace_subpath.c_str());
  printf("SUA_airspace_subpath           = %s\n",SUA_airspace_subpath.c_str());

}
void OpenEaglePaths::setupOpenEagleMastersPaths()
{
  printf("setupOpeneagleWritePaths()\n");
  OpenEagleMastersTextures_Path         = "/Masters/Airspace_Textures";
  OpenEagleSataMasters_Path             = "/Masters/OpenEagle/Sata";
  OpenEagleSuaMasters_Path              = "/Masters/OpenEagle/Sua";
  OpenEagleAirportACMaster              = "/Masters/Airspace_Textures/airport.ac";
  OpenEagleAirportXMLMaster             = "/Masters/Airspace_Textures/";
  OpenEagleMastersUpdateSua_Path        = "/Masters/OpenEagle/Sua";

  printf("OpenEagleMastersTextures_Path         = %s\n",OpenEagleMastersTextures_Path.c_str());
  printf("OpenEagleSataMasters_Path             = %s\n",OpenEagleSataMasters_Path.c_str());
  printf("OpenEagleSuaMasters_Path              = %s\n",OpenEagleSuaMasters_Path.c_str());
  printf("OpenEagleAirportACMaster              = %s\n",OpenEagleAirportACMaster.c_str());
  printf("OpenEagleAirportXMLMaster             = %s\n",OpenEagleAirportXMLMaster.c_str());
  printf("OpenEagleMastersUpdateSua_Path        = %s\n",OpenEagleMastersUpdateSua_Path.c_str());
}

void OpenEaglePaths::setupOpenEagleWritePaths(char * write_path)
{
  OpenEagleWrite_ModelsAndObjectsPath = write_path;

  OpenEagleWrite_AirportPath = write_path;
    OpenEagleWrite_AirportPath += "/Models/Airports";
    make_directory((char *)OpenEagleWrite_AirportPath.c_str());
  OpenEagleWrite_Class_AirspacePath = write_path;
    OpenEagleWrite_Class_AirspacePath += "/Models/Class_Airspace";
    make_directory((char *)OpenEagleWrite_Class_AirspacePath.c_str());
  OpenEagleWrite_Boundary_AirspacePath = write_path;
    OpenEagleWrite_Boundary_AirspacePath += "/Models/Boundary_Airspace";
    make_directory((char *)OpenEagleWrite_Boundary_AirspacePath.c_str());
  OpenEagleWrite_Special_Use_AirspacePath = write_path;
    OpenEagleWrite_Special_Use_AirspacePath += "/Models/Special_Use_Airspace";
    make_directory((char *)OpenEagleWrite_Special_Use_AirspacePath.c_str());
}

bool OpenEaglePaths::make_directory(char * path)
{
  printf("make_directory(%s)\n",path);
  std::string command;
  command = "mkdir -p ";
  command += path;
  command += "\n";
  printf("system_io(%s)\n",command.c_str());
  bool path_ok = system_io(&command);
  if (!path_ok) {
    printf("could not make [%s] path\n",path);
///    exit(1);
  }
  return path_ok;
}
