/***************************************************************
 * Name:      OpenEaglePaths.h
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
#ifndef OPENEAGLEPATHS_H
#define OPENEAGLEPATHS_H
#include <string>
class OpenEaglePaths
{
  public:
    char * home;
    std::string OpenEagle_str;
    std::string OpenEaglePath;                       // "/home/phil/Desktop/OpenEagle"
    std::string OpenEagle_FlightGear_Path;           // "/home/phil/Desktop/FlightGear-OpenEagle

    std::string OpenEagleWrite_AirportFilename;
    std::string OpenEagleWrite_AirportPath;                 /// /Scenery/Models/Airports

    std::string OpenEagleWrite_Class_AirspaceFilename;
    std::string OpenEagleWrite_Class_AirspacePath;          /// /Scenery/Models/Airspace

    std::string OpenEagleWrite_Boundary_AirspaceFilename;
    std::string OpenEagleWrite_Boundary_AirspacePath;       /// /Scenery/Models/Boundary_Airspace

    std::string OpenEagleWrite_Special_Use_AirspaceFilename;
    std::string OpenEagleWrite_Special_Use_AirspacePath;    /// /Scenery/Models/Special_Use_Airspace

    std::string OpenEagleWrite_ModelsAndObjectsPath;        ///  from user input setupOpenEaglePaths(.....path)

    std::string OpenEagleMastersTextures_Path;       // "/Masters/Airspace_Textures"
    std::string OpenEagleSataMasters_Path;           // "/Masters/OpenEagle/Sata"
    std::string OpenEagleSuaMasters_Path;            // "/Masters/OpenEagle/Sua"
    std::string OpenEagleAirportACMaster;            // "/Masters/Airspace_Textures/airport.ac"
    std::string OpenEagleAirportXMLMaster;           // "/Masters/Airspace_Textures/"
    std::string OpenEagleMastersUpdateSua_Path;      // "/Masters/OpenEagle/Sua"

    std::string airport_sign_base_path;              // "/Scenery/Models/Airports"
    std::string class_airspace_subpath;              // "/Scenery/Models/Class_Airspace"
    std::string boundary_airspace_subpath;           // "/Scenery/Models/Boundary_Airspace"
    std::string SUA_airspace_subpath;                // "/Scenery/Models/Special_Use_Airspace"

    bool setupOpenEaglePaths(char * name,char * write_path);
    bool make_directory(char * path);
  private:
    void setupOpenEagleSubPaths();
    void setupOpenEagleMastersPaths();
    void setupOpenEagleWritePaths(char * path);
};
#endif
