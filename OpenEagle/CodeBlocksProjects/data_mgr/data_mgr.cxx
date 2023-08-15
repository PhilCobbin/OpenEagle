/***************** #in**********************************************
 * Name:      data_mgr.cxx
 * Purpose:   Code for managing communication from sensors to FlightGear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Started:   2021-05-03
 * Copyright: Philip Cobbin (cobbin.com)
 * License:   GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
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
#include "../data_mgr/data_mgr.hxx"
#include "../3rdparty/constants.h"
#include "../system_io/system_io.hxx"
#include "../data_conversion/data_conversion.hxx"
///#include <pthread.h>
#include <sched.h>
#include <string>
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//#include "wx/string.h"

void data_mgr::free_fields()
{
  if (head_field != NULL) {
    current_field = head_field;
    while (current_field->next_field != NULL) current_field = current_field->next_field;
    current_field->next_field = free_field_list;
    free_field_list = head_field;
    head_field = NULL;
    current_field = NULL;
  }
}

data_mgr::field * data_mgr::get_field()
{
  struct field * a_field;
  if (free_field_list != NULL) {
    a_field = free_field_list;
    free_field_list = free_field_list->next_field;
  }
  else {
    a_field = new(struct field);
  }
  a_field->next_field = NULL;
  a_field->field = "";
  a_field->nullflag = true;
  a_field->n_field = -1;
  return a_field;
}

void data_mgr::destroy_fields()
{
  while (head_field != NULL)
  {
    current_field = head_field;
    head_field = head_field->next_field;
    current_field->next_field = NULL;
    free(current_field);
  }
  while (free_field_list != NULL) {
    current_field = free_field_list;
    free_field_list = free_field_list->next_field;
    current_field->next_field = NULL;
    free(current_field);
  }
}

/**
void  data_mgr::BindOpenEagleExt()
{
  printf("BindOpenEagleExt()\n");
  /// G5 Att/Air
  OpenEagleExt.G5UTCyear                       = G5_GPS_UtcYear;
  OpenEagleExt.G5UTCmonth                      = G5_GPS_UtcMonth;
  OpenEagleExt.G5UTCday                        = G5_GPS_UtcDay;
  OpenEagleExt.G5UTChour                       = G5_GPS_UtcHour;
  OpenEagleExt.G5UTCminute                     = G5_GPS_UtcMinute;
  OpenEagleExt.G5UTCsecond                     = G5_GPS_UtcSecond;
  OpenEagleExt.G5UTCsecondFraction             = G5_ATT_AIR_UtcMsecond;
  OpenEagleExt.G5pitch_deg                     = G5_ATT_AIR_PitchDeg;
  OpenEagleExt.G5roll_deg                      = G5_ATT_AIR_RollDeg;
  OpenEagleExt.G5airspeed_kt                   = G5_ATT_AIR_AirspeedKnots;
  OpenEagleExt.G5pressure_alt_ft               = G5_ATT_AIR_PressureAltFt;
  OpenEagleExt.G5rate_of_turn_dps              = G5_ATT_AIR_RateOfTurnDPS;
  OpenEagleExt.G5lateral_acceleration_g        = G5_ATT_AIR_LateralAccG;
  OpenEagleExt.G5vertical_acceleration_g       = G5_ATT_AIR_VerticalAccG;
  OpenEagleExt.G5vertical_speed_fpm            = G5_ATT_AIR_VerticalSpeedFPM;
  OpenEagleExt.G5altimeter_setting_inhg        = G5_ATT_AIR_AltimeterInHg;

  /// G5GPS
  OpenEagleExt.G5GPSlatitude                   = G5_GPS_Latitude;
  OpenEagleExt.G5GPSlongitude                  = G5_GPS_Longitude;
  OpenEagleExt.G5GPSposition_status            = G5_GPS_PositionStatus;
  OpenEagleExt.G5GPShoriz_pos_error_m          = G5_GPS_HorizontalPosErrMeters;
  OpenEagleExt.G5GPSaltitude_m                 = G5_GPS_AltitudeMeters;
  OpenEagleExt.G5GPSeast_west_velocity_mps     = G5_GPS_EWvelocityMPS;
  OpenEagleExt.G5GPSnorth_south_velocity_mps   = G5_GPS_NSvelocityMPS;
  OpenEagleExt.G5GPSvertical_velocity_mps      = G5_GPS_VerticalVelocityMPS;

  /// GPS arduino with GPS daughter board.
  OpenEagleExt.GPSlatitude                     = GpsLatitude;
  OpenEagleExt.GPSlongitude                    = GpsLongitude;
  OpenEagleExt.GPSgroundspeed_kt               = RMCSpeedOverGroundKnots;
  if (RMCSpeedOverGroundKnots > 5.0)
    OpenEagleExt.GPStrue_heading_deg = RMCCourseOverGroundTrue;
  else OpenEagleExt.GPStrue_heading_deg = 0.0;

  /// EM arduino mega with daughter board to collect engine data
  OpenEagleExt.EMfuel_psi                      = EMFuelPsi;
  OpenEagleExt.EMoil_psi                       = EMOilPsi;
  OpenEagleExt.EMoil_f                         = EMOilF;
  OpenEagleExt.EMcht                           = EMCHT;
  OpenEagleExt.EMegt                           = EMEGT;

///  OpenEagle.COMPspeed_down_fps              = G5_GPS_VerticalVelocityMPS*SG_METER_TO_FEET;
  OpenEagleExt.COMPspeed_down_fps              = G5_ATT_AIR_VerticalSpeedFPM/60.0;  /// ATT_AIR Velocity used for VSI indicator (10 hz)

  OpenEagleExt.fuel_flow_gph                   = FC_fuel_flow_gph;

  /// Now for the computed values from manual data entries:
  /// COMP special handling to compute variables
  OpenEagleExt.COMPaltitude_ft                 = pressure_altitude_to_indicated(G5_ATT_AIR_PressureAltFt,G5_ATT_AIR_AltimeterInHg);
  OpenEagleExt.COMPspeed_east_fps              = G5_GPS_EWvelocityMPS*SG_METER_TO_FEET;
  OpenEagleExt.COMPspeed_north_fps             = G5_GPS_NSvelocityMPS*SG_METER_TO_FEET;


  /// for DA and TAS see U.S. Standard Atmosphere 1976

  ///Density Altitude
  double temp_C = (5.9/9.0)*(OpenEagleExt.outside_air_temp_degf-32.0);
  OpenEagleExt.COMPdensity_altitude = OpenEagleExt.G5pressure_alt_ft + 120.0*(temp_C - (15.0 -1.98*(OpenEagleExt.G5pressure_alt_ft/1000.00)));

  ///True Airspeed
  double pb = 1.2250;     /// density kg/m^3
  double hb = 0;          /// 0 meters
  double Tb = 288.15;     /// Std Temp. K
  double Lb = -0.0065;    /// Lapse Rate K/m
  double R  = 8.3144598;  /// Universal Gas Constant N.m/(mol.K)
  double g0 = 9.80665;    /// Gravitational Acceleration m/s^2
  double M  = 0.0289644;  /// Molar mass of Earth's air kg/mol


///  see: https://en.wikipedia.org/wiki/Barometric_formula
  pb = 1.2250;      /// density kg/m^3
  hb = 0;           /// 0 meters
  Tb = 288.15;      /// Std Temp. K
  Lb = -0.0065;     /// Lapse rate K/m
  R = 8.3144598;    /// Universal Gas Constant N.m/(mol.K)
  g0 = 9.80665;     /// gravitational acceleration m/s^2
  M = 0.0289644;    /// Molar mass of Earth's air kg/mol

  double hft = OpenEagleExt.COMPdensity_altitude;
  double h = hft*0.3048;                                      /// to meters
  double p = pb*pow( Tb/(Tb+Lb*(h-hb)), 1 + (g0*M)/R*Lb);
  hft = OpenEagleExt.COMPdensity_altitude;                        /// feet
  h = hft*0.3048;                                             /// meters
  p = pb*pow(  Tb / ( Tb+Lb*(h-hb) )  ,  1+(g0*M)/(R*Lb));
  OpenEagleExt.COMPtrue_airspeed = OpenEagleExt.G5airspeed_kt*sqrt(pb/p);

}
**/
bool data_mgr::open_socket(int portno,int *socketfd)
{
  printf("open_socket(int portno, int socketfd)\n");
  bool ret = true;
  *socketfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socketfd set to %d\n",*socketfd);
  if (*socketfd < 0) perror("ERROR opening socket");
  struct hostent *  server = gethostbyname("127.0.0.1");
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  struct sockaddr_in serv_addr;
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(*socketfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("ERROR connecting");
    ret = false;
  }
  return ret;
}

void data_mgr::extractTakeoff(FILE * fp)
{
  current_data = first_data;
  if (current_data == NULL) return;
  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Density_Altitude, Procedure\n");
  fprintf(fp,"%8.1f, %8.0f\n",current_data->data.second_prefix,current_data->data.third_prefix);
  fprintf(fp,"\n");

//  double time_offset = current_data->data.elapsed_sec;
  double start_lat   = current_data->data.GPSlatitude;
  double start_lon   = current_data->data.GPSlongitude;
  double starting_alt= current_data->data.COMPaltitude_ft;

  double distanceMeter;
  double distance_ft;
  double airspeed;
  double time_sec;
  double height;

  double lat2;
  double lon2;
  double az1;
  double az2;

  double pitch;
  double flap_setting;
  fprintf(fp,"Time        , Distance, Air_Speed, Height, Pitch, Flap\n");

  while (current_data != NULL) {
  ///  time_sec     = current_data->data.elapsed_sec - time_offset;
    height       = current_data->data.COMPaltitude_ft-starting_alt;
    airspeed     = current_data->data.G5airspeed_kt;
    lat2         = current_data->data.GPSlatitude;
    lon2         = current_data->data.GPSlongitude;
    geo_inverse_wgs_84( start_lat, start_lon, lat2, lon2, &az1, &az2, &distanceMeter);
    distance_ft  = distanceMeter * SG_METER_TO_FEET;
    pitch        = current_data->data.G5pitch_deg;
    flap_setting     = current_data->data.first_prefix;

    fprintf(fp,"%12.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.0f\n",time_sec,distance_ft,airspeed,height,pitch,flap_setting);
    current_data = current_data->next_data;
  }
}

void data_mgr::extractClimb(FILE * fp)
{
  current_data = first_data;
  if (current_data == NULL) return;
  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Indicated Airspeed (kt)\n");
  fprintf(fp,"%8.1f\n",current_data->data.second_prefix);
  fprintf(fp,"\n");

 // double time_offset = current_data->data.elapsed_sec;
  double start_lat   = current_data->data.GPSlatitude;
  double start_lon   = current_data->data.GPSlongitude;

  double distanceMeter;
  double distance_ft;
  double airspeed;
  double tas;
  double time_sec;
  double height;

  double lat2;
  double lon2;
  double az1;
  double az2;

  double pitch;
  double flap_setting;
  double oilt;

  fprintf(fp,"Time        , Distance, Air_Speed, TAS, Altitude, Pitch, Flap,OilT\n");

  while (current_data != NULL) {
  //  time_sec     = current_data->data.elapsed_sec - time_offset;
   // height       = current_data->data.density_altitude;
    airspeed     = current_data->data.G5airspeed_kt;
 //   tas          = current_data->data.true_airspeed;
    lat2         = current_data->data.GPSlatitude;
    lon2         = current_data->data.GPSlongitude;
    geo_inverse_wgs_84( start_lat, start_lon, lat2, lon2, &az1, &az2, &distanceMeter);
    distance_ft  = distanceMeter * SG_METER_TO_FEET;
    pitch        = current_data->data.G5pitch_deg;
    oilt         = current_data->data.EMoil_f;
    flap_setting  = current_data->data.flap_setting;
    fprintf(fp,"%12.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.2f,%8.0f,%8.2f\n",time_sec,distance_ft,airspeed,tas,height,pitch,flap_setting,oilt);
    current_data = current_data->next_data;
  }

}

void data_mgr::extractCruise(FILE * fp)
{
  current_data = first_data;
  if (current_data == NULL) return;
  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Density_Altitude, Indicated_Airspeed (kt)\n");
  fprintf(fp,"%8.1f, %8.0f\n",current_data->data.second_prefix,current_data->data.third_prefix);
  fprintf(fp,"\n");

 // double time_offset = current_data->data.elapsed_sec;
  double start_lat   = current_data->data.GPSlatitude;
  double start_lon   = current_data->data.GPSlongitude;

  double distanceMeter;
  double distance_ft;
  double airspeed;
  double tas;
  double time_sec;
  double height;

  double lat2;
  double lon2;
  double az1;
  double az2;

  double pitch;

  fprintf(fp,"Time        , Distance, Air_Speed, TAS, Altitude, Pitch\n");

  while (current_data != NULL) {
  //  time_sec     = current_data->data.elapsed_sec - time_offset;
//    height       = current_data->data.density_altitude;
    airspeed     = current_data->data.G5airspeed_kt;
 //   tas          = current_data->data.true_airspeed;
    lat2         = current_data->data.GPSlatitude;
    lon2         = current_data->data.GPSlongitude;
    geo_inverse_wgs_84( start_lat, start_lon, lat2, lon2, &az1, &az2, &distanceMeter);
    distance_ft  = distanceMeter * SG_METER_TO_FEET;
    pitch        = current_data->data.G5pitch_deg;
    fprintf(fp,"%12.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.2f\n",time_sec,distance_ft,airspeed,tas,height,pitch);
    current_data = current_data->next_data;
  }
}

void data_mgr::extractDive(FILE * fp)
{
  extractClimb(fp);
}

void data_mgr::extractLand(FILE * fp)
{
  current_data = first_data;
  if (current_data == NULL) return;
  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Indicated Airspeed (kt)\n");
  fprintf(fp,"%8.1f\n",current_data->data.second_prefix);
  fprintf(fp,"\n");

  while (current_data->next_data != NULL) current_data = current_data->next_data;
//  double time_offset = current_data->data.elapsed_sec;
  double start_lat   = current_data->data.GPSlatitude;
  double start_lon   = current_data->data.GPSlongitude;
  double starting_alt= current_data->data.COMPaltitude_ft;

  double distanceMeter;
  double distance_ft;
  double airspeed;
  double time_sec;
  double height;

  double lat2;
  double lon2;
  double az1;
  double az2;

  double pitch;
  double flap_setting;

  fprintf(fp,"Time        , Distance, Air_Speed, Height, Pitch, Flap\n");

  while (current_data != NULL) {
 //   time_sec     = current_data->data.elapsed_sec - time_offset;
    height       = current_data->data.COMPaltitude_ft-starting_alt;
    airspeed     = current_data->data.G5airspeed_kt;
    lat2         = current_data->data.GPSlatitude;
    lon2         = current_data->data.GPSlongitude;
    geo_inverse_wgs_84( start_lat, start_lon, lat2, lon2, &az1, &az2, &distanceMeter);
    distance_ft  = distanceMeter * SG_METER_TO_FEET;
    pitch        = current_data->data.G5pitch_deg;
    flap_setting     = current_data->data.first_prefix;

    fprintf(fp,"%12.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.0f\n",time_sec,distance_ft,airspeed,height,pitch,flap_setting);
    current_data = current_data->last_data;
  }

}

void data_mgr::extractSpeed(FILE * fp)
{
  current_data = first_data;
  if (current_data == NULL) return;
  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Density_Altitude\n");
  fprintf(fp,"%8.1f\n",current_data->data.second_prefix);
  fprintf(fp,"\n");

//  double time_offset = current_data->data.elapsed_sec;
  double start_lat   = current_data->data.GPSlatitude;
  double start_lon   = current_data->data.GPSlongitude;

  double distanceMeter;
  double distance_ft;
  double airspeed;
  double tas;
  double time_sec;
  double height;

  double lat2;
  double lon2;
  double az1;
  double az2;

  double pitch;
  double nsew;

  fprintf(fp,"Time        , Distance, Air_Speed, TAS, Altitude, Pitch NSEW\n");
  while (current_data != NULL) {
 ///   time_sec     = current_data->data.elapsed_sec - time_offset;
 //   height       = current_data->data.density_altitude;
    airspeed     = current_data->data.G5airspeed_kt;
 //   tas          = current_data->data.true_airspeed;
    lat2         = current_data->data.GPSlatitude;
    lon2         = current_data->data.GPSlongitude;
    geo_inverse_wgs_84( start_lat, start_lon, lat2, lon2, &az1, &az2, &distanceMeter);
    distance_ft  = distanceMeter * SG_METER_TO_FEET;
    pitch        = current_data->data.G5pitch_deg;
    nsew         = current_data->data.third_prefix;
    fprintf(fp,"%12.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.0f\n",time_sec,distance_ft,airspeed,tas,height,pitch,nsew);
    current_data = current_data->next_data;
  }

}

void data_mgr::extractStall(FILE * fp)
{
  current_data = first_data;
  if (current_data == NULL) return;
  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Aircraft Wt, Density_Altitude)\n");
  fprintf(fp,"%8.1f, %8.2f\n",current_data->data.second_prefix,current_data->data.third_prefix);
  fprintf(fp,"\n");
//  double time_offset = current_data->data.elapsed_sec;
  double start_lat   = current_data->data.GPSlatitude;
  double start_lon   = current_data->data.GPSlongitude;
  double starting_alt= current_data->data.COMPaltitude_ft;

  double distanceMeter;
  double distance_ft;
  double airspeed;
//  double tas;
  double time_sec;
  double height;

  double lat2;
  double lon2;
  double az1;
  double az2;

  double pitch;
  double flap_setting;
  //double oilt;

  fprintf(fp,"Time        , Distance, Air_Speed, TAS, Height, Pitch, Flap\n");
  time_sec = 0.0;
  while (current_data != NULL) {
 //   time_sec     = current_data->data.elapsed_sec - time_offset;
    height       = current_data->data.COMPaltitude_ft-starting_alt;
    airspeed     = current_data->data.G5airspeed_kt;
    lat2         = current_data->data.GPSlatitude;
    lon2         = current_data->data.GPSlongitude;
    geo_inverse_wgs_84( start_lat, start_lon, lat2, lon2, &az1, &az2, &distanceMeter);
    distance_ft  = distanceMeter * SG_METER_TO_FEET;
    pitch        = current_data->data.G5pitch_deg;
    flap_setting     = current_data->data.first_prefix;

    fprintf(fp,"%12.2f, %8.2f, %8.2f, %8.2f, %8.2f, %8.0f\n",time_sec,distance_ft,airspeed,height,pitch,flap_setting);
    current_data = current_data->next_data;
  }
}

void data_mgr::extractTurn(FILE * fp)
{
 // printf("extractTurn(...)\n");
 // return;
  current_data = first_data;
  if (current_data == NULL) return;

  double start_angle = current_data->data.GPStrue_heading_deg;
  decodedData * start_point = current_data;
  decodedData * end_point = NULL;
  bool done = false;
  double delta_angle;

/// cw or ccw?
#define CW  1
#define CCW 2
/// fencepost issue:
///    First Case example:: 359.5->0.2     CW turn
///    Second Case example   0.2 -> 359.5  CCW turn
  bool skip_over_north = true;
  while (skip_over_north) {
    delta_angle = start_angle - current_data->next_data->data.GPStrue_heading_deg;
    if (fabs(delta_angle) < 180.0) {
      skip_over_north = false;
    }
    else {
      current_data = current_data->next_data;
      start_point = current_data;
      start_angle = current_data->data.GPStrue_heading_deg;
    }
  }
  int clock_turn;
#define ANGLE_TEST 10.0
  if(delta_angle >0) { /// CCW turn
    clock_turn = CCW;
  }
  else {  /// CW turn
    clock_turn = CW;
  }

  bool valid_360_turn = false;

  double last_angle = start_angle;
  current_data = current_data->next_data;

///

  while (!done) {
    double angle = current_data->data.GPStrue_heading_deg;
    switch (clock_turn)
    {
    case CW: /// delta angle +
      if (last_angle < start_angle) {
        if (angle >= start_angle) {  /// crossed 360 degrees of turn, i.e. full circle
          end_point = current_data;
          valid_360_turn = true;
          done = true;
        }
      }
      break;
    case CCW:/// delta_angle -
      if (last_angle > start_angle) {
        if (angle <= start_angle) { /// crossed 360 degrees of turn
          end_point = current_data;
          valid_360_turn = true;
          done = true;
        }
      }
      break;
    }
    last_angle = angle;
    if (current_data->next_data != NULL)  current_data = current_data->next_data; else done = true;
  }
  if (!valid_360_turn) return;

  ///header information
  ///second prefix is density altitude
  ///            0----+----1----+----2----+----3
  fprintf(fp,    "Density_Altitude, Airspeed (kt)\n");  ///wt et al?
  fprintf(fp,"%8.1f, %8.2f\n",current_data->data.second_prefix,current_data->data.third_prefix);
  fprintf(fp,"\n");
///  fprintf(fp,"X_(long_ft)        , Y_(Lat_ft), Turn_Rate, R_ft, Airspeed, TAS, roll\n");

/// re read data, this time to get mean lon/lot for center of circle;
  current_data = start_point;
  done = false;
  double sum_lat = 0;
  double sum_lon = 0;
  int n_pts = 0;
  while (!done) {
    if (current_data != end_point) {
      sum_lat += current_data->data.GPSlatitude;
      sum_lon += current_data->data.GPSlongitude;
      n_pts++;
      current_data = current_data->next_data;
    } else done = true;
  }
  double ave_lat = sum_lat/(double)n_pts;
  double ave_lon = sum_lon/(double)n_pts;

  double start_lat = start_point->data.GPSlatitude;
  double start_lon = start_point->data.GPSlongitude;

  double end_lat = end_point->data.GPSlatitude;
  double end_lon = end_point->data.GPSlongitude;

  double apparent_wind_x;
  double apparent_wind_y;
  double apparent_wind = ac_from_wgs_84(start_lat, start_lon, end_lat, end_lon,&apparent_wind_x,&apparent_wind_y);

  double apparent_wind_x_ft = apparent_wind_x*SG_METER_TO_FEET;
  double apparent_wind_y_ft = apparent_wind_y*SG_METER_TO_FEET;
  double apparent_wind_ft = apparent_wind*SG_METER_TO_FEET;
//  double total_time_sec = end_point->data.elapsed_sec - start_point->data.elapsed_sec;
//  double apparent_wind_fps = apparent_wind_ft/total_time_sec;

  double apparent_wind_direction = atan2(apparent_wind_y,apparent_wind_x);
  apparent_wind_direction *= SG_RADIANS_TO_DEGREES;

//  double estimated_turn_rate_dps = total_time_sec/360.0;

//  fprintf(fp,"estimated turn rate accross turn %8.2f dps\n",estimated_turn_rate_dps);

  fprintf(fp,"start point lat %12.8f lon %12.8f\n",start_lat,start_lon);
  fprintf(fp,"end   point lat %12.8f lon %12.8f\n",end_lat,end_lon);
  fprintf(fp,"apparent_wind x %8.2f y %8.2f W %8.2f\n",apparent_wind_x_ft, apparent_wind_y_ft, apparent_wind_ft);
//  fprintf(fp,"apparent wind drift %8.2f fps, direction %8.2f degrees\n",apparent_wind_fps, apparent_wind_direction);



/// output coordinates of center of turn;
  fprintf(fp,"Average Latitude        , Average Longitude\n");
  fprintf(fp,"%12.8F,%12.8f\n",ave_lat,ave_lon);
  fprintf(fp,"heading x_ft       , y_ft     ,turn_rate (dps), r_ft, Airspeed, TAS, roll\n");

/// output x(longitude) y(latitude) of radius in feet for plotting and output the radius in feet.
  current_data = start_point;
  done = false;
  while (!done) {
    if (current_data != end_point) {
 //     double lat1 = ave_lat;
 //     double lon1 = ave_lon;
//      double lat2 = current_data->data.GPSlatitude;
  //    double lon2 = current_data->data.GPSlongitude;

 //     double x;
 //     double y;
//      double r = ac_from_wgs_84(lat1, lon1, lat2, lon2,&x,&y);
//      double x_ft = x*SG_METER_TO_FEET;
//      double y_ft = y*SG_METER_TO_FEET;
//      double r_ft = r*SG_METER_TO_FEET;
//      double airspeed = current_data->data.G5airspeed_kt;
 //     double tas = current_data->data.true_airspeed;
      double turn_rate = current_data->data.G5rate_of_turn_dps;
      turn_rate *= SG_RADIANS_TO_DEGREES;
 //     double roll = current_data->data.G5roll_deg;
 //     double heading = current_data->data.GPStrue_heading_deg;
   //   fprintf(fp,"%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.1f,%8.1f,%8.1f\n",heading,x_ft,y_ft,turn_rate,r_ft,airspeed,tas,roll);
      current_data = current_data->next_data;
    }
    else done = true;
  }
/// adjustment for apparent wind (or pilotage variation)
  double wind_adj_x = apparent_wind_x_ft;
  double wind_adj_y = apparent_wind_y_ft;
  fprintf(fp,"\n Apparent Wind adjusted turn, delta x %8.2f delta y %8.2f\n",wind_adj_x, wind_adj_y);
  fprintf(fp,"heading x_ft       , y_ft     ,turn_rate (dps), r_ft, Airspeed, TAS, roll\n");
  current_data = start_point;
  done = false;
  int i=0;
  while (!done) {
    if (current_data != end_point) {
//      double lat1 = ave_lat;
 //     double lon1 = ave_lon;
  //   double lat2 = current_data->data.GPSlatitude;
  //  double lon2 = current_data->data.GPSlongitude;

  //  double x;
  //  double y;
//      double r = ac_from_wgs_84(lat1, lon1, lat2, lon2,&x,&y);
   // double proportion = (double)i/(double)n_pts+1.0;
      //uble adjust x = wind_adj_x * proportion;

    //double x_ft = x*SG_METER_TO_FEET;  x_ft-=wind_adj_x*proportion;
    //double y_ft = y*SG_METER_TO_FEET;  y_ft-=wind_adj_y*proportion;

  //    double r_ft = r*SG_METER_TO_FEET;
  //    double airspeed = current_data->data.G5airspeed_kt;
   //   double tas = current_data->data.true_airspeed;
  //  double turn_rate = current_data->data.G5rate_of_turn_dps;
  //  turn_rate *= SG_RADIANS_TO_DEGREES;
  //    double roll = current_data->data.G5roll_deg;
//    double heading = current_data->data.GPStrue_heading_deg;
  //    fprintf(fp,"%8.2f,%8.2f,%8.2f,%8.2f,%8.2f,%8.1f,%8.1f,%8.1f\n",heading,x_ft,y_ft,turn_rate,r_ft,airspeed,tas,roll);
      current_data = current_data->next_data;
      i++;
    }
    else done = true;
  }


}

void data_mgr::extractOPE(FILE * fp)
{

}

void data_mgr::extractUnkown(FILE * fp)
{
  extractOPE(fp);
}

void data_mgr::destroy_data()
{
  current_data = first_data;
  while (current_data != NULL) {
    first_data = current_data;
    current_data = current_data->next_data;
    delete first_data;
  }
  first_data = NULL;
  current_data = NULL;
  last_data = NULL;
}

data_mgr::decodedData * data_mgr::get_new_data()
{
  decodedData * new_data = new decodedData;
  new_data->next_data = NULL;
  new_data->last_data = NULL;
  new_data->record_nbr = 0;
  return new_data;
}

void data_mgr::extractDecodedFileData(int file_nbr, int code_index, int code_index_cnt, std::string path, std::string Full_Decoded_File_Name)
{

  printf("extractDecodedFileData(\n");
  printf("                       code_index = %d,\n",code_index);
  printf("                       code_index_cnt = %d,\n",code_index_cnt);
  printf("                       path = [%s],\n",path.c_str());
  printf("                       Full_Decoded_File_Name = [%s]\n",Full_Decoded_File_Name.c_str());
  printf("                       );\n");

  /// Open
  /// Read to double linked list
  ///printf("  Open file\n");
  FILE * extract_fp;
  printf("extract_FP for [%s]\n",Full_Decoded_File_Name.c_str());
  extract_fp = fopen(Full_Decoded_File_Name.c_str(),"rb");
  if (extract_fp == NULL) {
    printf("failure to open file for extract [%s]\n",Full_Decoded_File_Name.c_str());
    perror("\nError");
  }
  else {
    printf("    Read data\n");
    first_data = NULL;
    current_data = NULL;
    last_data = NULL;
    int nread;
    int n = 0;
    OpenEagleExtData data;
    do {
      nread = fread(&data,sizeof( OpenEagleExtData ),1,extract_fp);
      printf("nread = %d\n",nread);
      if (nread == 1) {
        n++;
        printf("      read record %d\n",n);
        current_data = get_new_data();
        current_data->data = data;
        if (first_data == NULL) {
          printf("n==1, first\n");
          first_data = current_data;
          last_data = current_data;
          first_data = current_data;
          ///if (first_data != NULL) printf("first_data != NULL"); else printf("first_data == NULL?\n");
        }
        else {
          printf("n= %d, new end node\n",n);
          current_data->last_data = last_data;
          last_data ->next_data = current_data;
          last_data = current_data;
        }
      }
    } while ( (nread == 1) );
    printf("    Close file\n");
    /// read data in, close file
    fclose(extract_fp);

    /// set up filename for output data (txt)
    /// filename in form, ex: Takeoff_1_data.txt where 1 is the current_code_cnt
    std::string filename = "";
    filename += "flight_data/";
    if (file_nbr <10) filename += "0";
    filename += std::to_string(file_nbr);
    filename += "_";
    filename += CodeBook[code_index].c_str();
    filename += "_";
    filename += std::to_string(code_index_cnt);
    filename += "_data.txt";
    std::string full_filename = path;
    full_filename += filename;
    FILE * fp;
    fp = fopen(full_filename.c_str(),"w++");
    ///printf("  Open output file [%s]\n",full_filename.c_str());
    if (fp != NULL) {
      switch (code_index)
      {
        case TAKEOFF:
          extractTakeoff(fp);
          break;
        case CLIMB:
          extractClimb(fp);
          break;
        case CRUISE:
          extractCruise(fp);
          break;
        case DIVE:
          extractClimb(fp);
          break;
        case LAND:
          extractLand(fp);
          break;
        case SPEED:
          extractSpeed(fp);
          break;
        case STALL:
          extractStall(fp);
          break;
        case TURN:
          extractTurn(fp);
          break;
        case OPE:
          extractOPE(fp);
          break;
        case UNKNOWN:
          extractUnkown(fp);
          break;
          extractUnkown(fp);
        default:
          break;
      }
      fclose(fp);
    }
    else {
      printf("WARNING: failure to open data_file\n");
    }
  }
}

void data_mgr::extractDecodedFileData()
{
  current_decoded_file = first_decoded_file;
  int file_nbr = 1;
  while (current_decoded_file != NULL) {
    extractDecodedFileData(
                           file_nbr,
                           current_decoded_file->code_index,
                           current_decoded_file->code_index_cnt,
                           current_decoded_file->path,
                           current_decoded_file->Full_Decoded_File_Name
                           );
    current_decoded_file = current_decoded_file->next_decoded_file;
    file_nbr ++;
  }
  destroy_decoded_file_list();
}

void data_mgr::destroy_decoded_file_list()
{
  current_decoded_file = first_decoded_file;
  while (current_decoded_file != NULL) {
    first_decoded_file = current_decoded_file;
    current_decoded_file = current_decoded_file->next_decoded_file;
    delete first_decoded_file;
  }
  first_decoded_file = NULL;
  current_decoded_file = NULL;
  last_decoded_file = NULL;
}

data_mgr::decodedFileList * data_mgr::get_new_decoded_file()
{
  decodedFileList * new_file = new decodedFileList;
  new_file->next_decoded_file = NULL;
  new_file->code_index = -1;
  new_file->code_index_cnt = -1;
  new_file->path = "";
  new_file->Full_Decoded_File_Name = "";
  return new_file;
}

void data_mgr::add_decoded_file_to_list(int code_index,int code_index_cnt,std::string path, std::string decoded_fn)
{
///  printf("add_decoded_file_to_list(code_index %d, code_index_cnt %d, path [%s], decoded_fn [%s]\n",
///                                   code_index,code_index_cnt,path.c_str(),decoded_fn.c_str());
  decodedFileList * new_decoded_file_entry = get_new_decoded_file();
  new_decoded_file_entry->code_index = code_index;
  new_decoded_file_entry->code_index_cnt = code_index_cnt;
  new_decoded_file_entry->path = path;
  new_decoded_file_entry->Full_Decoded_File_Name = decoded_fn;
  if (first_decoded_file == NULL) {
    first_decoded_file = new_decoded_file_entry;
    last_decoded_file = first_decoded_file;
  }
  else {
    last_decoded_file->next_decoded_file = new_decoded_file_entry;
    last_decoded_file = new_decoded_file_entry;
  }
}

int data_mgr::DecodeCRM114files(std::string path, std::string fn)
{
  printf("DecodeCRM114files(%s, %s)\n",path.c_str(),fn.c_str());
  FILE * fp;
  FILE * fp_ext;

  size_t nread;
  int ret = 0;

//  int code_cnt[12] = {0,0,0,0,0,0,0,0,0,0,0,0};  /// mickey mouse fix it dodo!
  for (int i = 0; i<UNKNOWN; i++) code_cnt[i]=0;
  int code_index;
  bool write_file = false;

  std::string decoded_fn;

  std::string full_fn = path.c_str();
  full_fn += fn.c_str();
  printf("full_fn [%s]\n",full_fn.c_str());

  fp = fopen(full_fn.c_str(),"r");

  int test_flight_nbr = 0;

  nread = fread(&OpenEagleExt, sizeof(OpenEagleExtData), 1,fp);
  if ( nread == (long unsigned int)  EOF) {
    fclose(fp);
    return ret;
  }
  if (nread <1) {
    fclose(fp);
    return ret;
  }
  int last_prefix = OpenEagleExt.first_prefix;
  int current_prefix = -1;
  int data_prefix = last_prefix;
/// open file and write first out maybe
  if (data_prefix > 0) {
    if (current_prefix < UNKNOWN) {
      current_prefix = data_prefix;
    }
    else current_prefix = UNKNOWN;
  }
  code_index = current_prefix;
  if (code_index > 0) {
    test_flight_nbr++;
   /// printf("open on first record...\n");
   /// printf("open on first record:  file and write, on initial code_index %f\n",code_index);
   /// return ret;
    code_cnt[code_index]++;
    decoded_fn  = path;
    decoded_fn += "flight_tests/";
    if (test_flight_nbr < 10) decoded_fn += "0";
    decoded_fn += std::to_string(test_flight_nbr);
    decoded_fn += "_";
    decoded_fn += CodeBook[code_index];
    decoded_fn += "_";
    decoded_fn += std::to_string(code_cnt[code_index]);
    decoded_fn += ".OpenEagleExt";
    ///printf("open decoded file on first record record....[%s]\n",decoded_fn.c_str());
    fp_ext = fopen(decoded_fn.c_str(),"w++");
    add_decoded_file_to_list(code_index,code_cnt[code_index],path,decoded_fn);
    write_file = true;
    fwrite(&OpenEagleExt,sizeof(OpenEagleExt),1,fp_ext);
  }
  else decoded_fn = "";

  int i = 0;
  if (fp != NULL) {
    size_t nread;
    do {
      nread = fread(&OpenEagleExt, sizeof(OpenEagleExtData), 1,fp);
//      printf("i %d nread %d \n",i,nread);
      i++;
      if (nread == (long unsigned int) EOF) {
        printf("close on EOF\n");
        fclose(fp);
        fclose(fp_ext);
      //  if (write_file) {
      //    fclose(fp_ext);
      //  }
        return ret;
      }
      if (nread <1) {
        fclose(fp);
        if (write_file) {
          fclose(fp_ext);
        }
        return ret;
      }
      int test_prefix = OpenEagleExt.first_prefix;
     // printf("test_prefix %d, current_prefix %d\n elapsed_sec %10.2f",test_prefix,current_prefix,OpenEagleExt.elapsed_sec);
      if (test_prefix == current_prefix) {
        if (test_prefix > 0) {
          fwrite(&OpenEagleExt,sizeof(OpenEagleExt),1,fp_ext);
        }
      }
      else {
        if (write_file) {
          ///printf("close [%s]\n",decoded_fn.c_str());
          fclose(fp_ext);
          write_file = false;
        }
        current_prefix = test_prefix;
        last_prefix = OpenEagleExt.first_prefix;
        data_prefix = last_prefix;
        /// open file and write first out maybe
        printf("open file and write first out maybe: current_prefix %d, last_prefix %d, data_prefix %d\n",current_prefix,last_prefix,data_prefix);
        if (data_prefix > 0) {
          if (current_prefix < UNKNOWN) {
            current_prefix = data_prefix;
          }
          else current_prefix = UNKNOWN;
        }
        code_index = current_prefix;
        if (code_index > 0) {
          printf("open on code_index %d\n",code_index);
      ///    return ret;
          test_flight_nbr++;
          code_cnt[code_index]++;
          decoded_fn = path;
          decoded_fn += "flight_tests/";
          if (test_flight_nbr < 10) decoded_fn += "0";
          decoded_fn += std::to_string(test_flight_nbr);
          decoded_fn += "_";
          decoded_fn += CodeBook[code_index];
          decoded_fn += "_";
          decoded_fn += std::to_string(code_cnt[code_index]);
          decoded_fn += ".OpenEagleExt";
          printf("open and do first record for file [%s]\n",decoded_fn.c_str());
          fp_ext = fopen(decoded_fn.c_str(),"w++");
          if (fp_ext != NULL) {
            add_decoded_file_to_list(code_index,code_cnt[code_index],path,decoded_fn);
            write_file = true;
            fwrite(&OpenEagleExt,sizeof(OpenEagleExt),1,fp_ext);
          }
          else {
            printf("fp_ext NULL, failure to open file\n");
            fclose(fp);
            return -1;
          }
        }
        else decoded_fn = "";
      }
    } while (nread != (long unsigned int) EOF);
    fclose(fp);
  }
  else {
    printf("unable to open file\n");
  }
  return ret;
}

void data_mgr::writeHeader(FILE * fp)
{
/// time
  if (ReportUTCyear)                           fprintf(fp,"year ");  // " 4.0f "
  if (ReportUTCmonth)                          fprintf(fp,"mn ");  // " 2.0f  "
  if (ReportUTCday)                            fprintf(fp,"day ");
  if (ReportUTChour)                           fprintf(fp,"hr ");
  if (ReportUTCminute)                         fprintf(fp,"min ");
  if (ReportUTCsecond)                         fprintf(fp,"sec ");
  if (ReportUTCsecondfraction)                 fprintf(fp,"tnth ");
/// G5 Att/Air
  if (ReportG5pitch_deg)                       fprintf(fp," pitch ");
  if (ReportG5roll_deg)                        fprintf(fp,"  roll ");
  if (ReportG5airspeed_kt)                     fprintf(fp," ASkn ");
  if (ReportG5pressure_alt_ft)                 fprintf(fp,"  PA ");
  if (ReportG5rate_of_turn_dps)                fprintf(fp,"  ROT ");
  if (ReportG5lateral_acceleration_g)          fprintf(fp,"  LAg ");
  if (ReportG5vertical_acceleration_g)         fprintf(fp,"  VAg ");
  if (ReportG5vertical_speed_fpm)              fprintf(fp,"  VSfpm");
  if (ReportG5setting_inhg)                    fprintf(fp," InHg ");

/// G5 GPS                                               //----+----1----+
  if (ReportG5GPSlatitude)                    fprintf(fp," G5 Latitude ");
  if (ReportG5GPSlongitude)                   fprintf(fp,"    Longitude ");
  if (ReportG5GPSposition_status)             fprintf(fp," PS ");
  if (ReportG5GPShoriz_position_error_meter)  fprintf(fp," HPEm");
  if (ReportG5GPSaltitude_meter)                 fprintf(fp," Altm");
  if (ReportG5GPSeast_west_velocity_mps)      fprintf(fp,"EW mps");
  if (ReportG5GPSnorth_south_velocity_mps)    fprintf(fp," NSmps");
  if (ReportG5GPSvertical_velocity_mps)       fprintf(fp," Vvmps");
/// Adafruit GPS
  if (Reportlatitude_deg)                     fprintf(fp,"  Latitude  ");
  if (Reportlongitude_deg)                    fprintf(fp,"     Longitude ");
  if (Reportgroundspeed_kt)                   fprintf(fp," Gr Sp  ");
  if (Reporttrue_heading_deg)                 fprintf(fp," THdg");
/// Engine Monitor
  if (ReportEMfuel_pressure)                  fprintf(fp," Fpsi ");
  if (ReportEMoil_pressure)                   fprintf(fp," Opsi ");
  if (ReportEMoil_temperature)                fprintf(fp," ODegF");
  if (ReportEMCHT)                            fprintf(fp,"  CHT");
  if (ReportEMEGT)                            fprintf(fp,"  EGT");
/// Computed
  if (ReportCOMPaltitude_ft)                  fprintf(fp," CAlt");
  if (ReportCOMPspeed_down_fps)               fprintf(fp," CspdD");
  if (ReportCOMPspeed_east_fps)               fprintf(fp," CspdE");
   if (ReportCOMPspeed_north_fps)             fprintf(fp," CspdN");
  if (ReportCOMPdensity_altitude)             fprintf(fp,"  CDalt");
  if (reportCOMPtrue_airspeed)                fprintf(fp,"  CTAS");
/// FC-10 Fuel Computer
  if (ReportFCfuel_gallons)                   fprintf(fp," Fuel G");
  if (ReportFCfuel_flow)                      fprintf(fp," Fuel GPH");
/// Manual Data Entry
  if (ReportManualfirst_prefix)               fprintf(fp," 1P ");
  if (ReportManualsecond_prefix)              fprintf(fp," 2P ");
  if (ReportManualthird_prefix)               fprintf(fp," 3P ");
  if (ReportManualcrew_weight)                fprintf(fp," Crew Wt ");
  if (ReportManualbaggage_weight)             fprintf(fp," Bag. Wt ");
  if (ReportManualRPM)                        fprintf(fp,"  RPM");
  if (ReportManualmanifold_pressure)          fprintf(fp,"  ManP");
  if (ReportManualoutside_air_temp_degf)      fprintf(fp," OAT ");
  if (ReportManualflap_setting)               fprintf(fp," Flap ");
  if (ReportManualcowl_flap_in)               fprintf(fp," Cowl ");

  fprintf(fp,"\n");

}

 void data_mgr::writeBody(FILE * fp)
 {
     /// time
  if (ReportUTCyear)                           fprintf(fp,"%4.0F ",OpenEagleExt.G5UTCyear);  // " 4.0f "
  if (ReportUTCmonth)                          fprintf(fp,"%2.0f  ",OpenEagleExt.G5UTCmonth);  // " 2.0f  "
  if (ReportUTCday)                            fprintf(fp,"%2.0f ",OpenEagleExt.G5UTCday);
  if (ReportUTChour)                           fprintf(fp,"%2.0f ",OpenEagleExt.G5UTChour); //"-hr-"
  if (ReportUTCminute)                         fprintf(fp," %2.0f ",OpenEagleExt.G5UTCminute);
  if (ReportUTCsecond)                         fprintf(fp," %2.0f ",OpenEagleExt.G5UTCsecond);
  if (ReportUTCsecondfraction)                 fprintf(fp,"%4.2f",OpenEagleExt.G5UTCsecondFraction);
/// G5 Att/Air
  if (ReportG5pitch_deg)                       fprintf(fp,"  %5.1f ",OpenEagleExt.G5pitch_deg);
  if (ReportG5roll_deg)                        fprintf(fp,"%6.1f ",OpenEagleExt.G5roll_deg);
  if (ReportG5airspeed_kt)                     fprintf(fp,"%5.1f ",OpenEagleExt.G5airspeed_kt);
  if (ReportG5pressure_alt_ft)                 fprintf(fp,"%5.0f ",OpenEagleExt.G5pressure_alt_ft);
  if (ReportG5rate_of_turn_dps)                fprintf(fp,"%5.2f ",OpenEagleExt.G5rate_of_turn_dps);
  if (ReportG5lateral_acceleration_g)          fprintf(fp,"%5.2f ",OpenEagleExt.G5lateral_acceleration_g);
  if (ReportG5vertical_acceleration_g)         fprintf(fp,"%5.2f ",OpenEagleExt.G5vertical_acceleration_g);
  if (ReportG5vertical_speed_fpm)              fprintf(fp,"%7.0f ",OpenEagleExt.G5vertical_speed_fpm);
  if (ReportG5setting_inhg)                    fprintf(fp,"%5.2f ",OpenEagleExt.G5altimeter_setting_inhg);

/// G5 GPS                                               //----+----1----+
  if (ReportG5GPSlatitude)                    fprintf(fp," %12.8f ",OpenEagleExt.G5GPSlatitude); //"--------------"
  if (ReportG5GPSlongitude)                   fprintf(fp," %12.8f ",OpenEagleExt.G5GPSlongitude);
  if (ReportG5GPSposition_status)             fprintf(fp,"%2.0f ",OpenEagleExt.G5GPSposition_status);
  if (ReportG5GPShoriz_position_error_meter)     fprintf(fp," %2.0f ",OpenEagleExt.G5GPShoriz_pos_error_m);
  if (ReportG5GPSaltitude_meter)                 fprintf(fp,"%5.0f ",OpenEagleExt.G5GPSaltitude_m);
  if (ReportG5GPSeast_west_velocity_mps)      fprintf(fp," %5.0f",OpenEagleExt.G5GPSeast_west_velocity_mps);
  if (ReportG5GPSnorth_south_velocity_mps)    fprintf(fp,"  %5.0f",OpenEagleExt.G5GPSnorth_south_velocity_mps);
  if (ReportG5GPSvertical_velocity_mps)       fprintf(fp,"%5.f  ",OpenEagleExt.G5GPSvertical_velocity_mps);
/// Adafruit GPS
  if (Reportlatitude_deg)                     fprintf(fp,"%12.8f ",OpenEagleExt.GPSlatitude);
  if (Reportlongitude_deg)                    fprintf(fp," %12.8f ",OpenEagleExt.GPSlongitude);
  if (Reportgroundspeed_kt)                   fprintf(fp,"  %5.2f ",OpenEagleExt.GPSgroundspeed_kt);
  if (Reporttrue_heading_deg)                 fprintf(fp,"%5.2f",OpenEagleExt.GPStrue_heading_deg);
/// Engine Monitor
  if (ReportEMfuel_pressure)                  fprintf(fp,"%6.2f ",OpenEagleExt.EMfuel_psi);
  if (ReportEMoil_pressure)                   fprintf(fp,"%6.2f",OpenEagleExt.EMoil_psi);
  if (ReportEMoil_temperature)                fprintf(fp,"%6.2f",OpenEagleExt.EMoil_f);
  if (ReportEMCHT)                            fprintf(fp,"%5.0f",OpenEagleExt.EMcht);
  if (ReportEMEGT)                            fprintf(fp,"%5.0f",OpenEagleExt.EMegt);
/// Computed
  if (ReportCOMPaltitude_ft)                  fprintf(fp," %5.0f",OpenEagleExt.COMPaltitude_ft);
  if (ReportCOMPspeed_down_fps)               fprintf(fp," %5.0f",OpenEagleExt.COMPspeed_down_fps);
  if (ReportCOMPspeed_east_fps)               fprintf(fp," %5.0f",OpenEagleExt.COMPspeed_east_fps);
   if (ReportCOMPspeed_north_fps)             fprintf(fp," %5.0f",OpenEagleExt.COMPspeed_north_fps);
  if (ReportCOMPdensity_altitude)             fprintf(fp," %6.0f",OpenEagleExt.COMPdensity_altitude);
  if (reportCOMPtrue_airspeed)                fprintf(fp," %5.0f",OpenEagleExt.COMPtrue_airspeed);
/// FC-10 Fuel Computer
  if (ReportFCfuel_gallons)                   fprintf(fp,"   %5.2f",OpenEagleExt.fuel_gallons);
  if (ReportFCfuel_flow)                      fprintf(fp,"    %5.2f",OpenEagleExt.fuel_flow_gph);
/// Manual Data Entry
  if (ReportManualfirst_prefix)               fprintf(fp," %2.0f ",OpenEagleExt.first_prefix);
  if (ReportManualsecond_prefix)              fprintf(fp," %2.0f ",OpenEagleExt.second_prefix);
  if (ReportManualthird_prefix)               fprintf(fp," %2.0f ",OpenEagleExt.third_prefix);
  if (ReportManualcrew_weight)                fprintf(fp,"    %5.1f ",OpenEagleExt.crew_wt);
  if (ReportManualbaggage_weight)             fprintf(fp,"   %5.1f ",OpenEagleExt.baggage_wt);
  if (ReportManualRPM)                        fprintf(fp," %4.0f",OpenEagleExt.RPM);
  if (ReportManualmanifold_pressure)          fprintf(fp," %5.1f",OpenEagleExt.manifold_pressure_inhg);
  if (ReportManualoutside_air_temp_degf)      fprintf(fp,"%4.0f ",OpenEagleExt.outside_air_temp_degf);
  if (ReportManualflap_setting)               fprintf(fp,"   %2.0f ",OpenEagleExt.flap_setting);
  if (ReportManualcowl_flap_in)               fprintf(fp,"   %2.0f ",OpenEagleExt.cowl_flap_in);

  fprintf(fp,"\n");

 }


void data_mgr::writeReport(char * DataPath, char * DataFile, char * ReportFile)
{
  printf("writeReport(...)\n");
  printf("  Datapath:[%s]\n",DataPath);
  printf("  DataFile:[%s]\n",DataFile);
  printf("  ReportFile[%s]\n",ReportFile);
  std::string FullDataFile = DataPath;
  FullDataFile += DataFile;
  printf("  FullDataFile:[%s]\n",FullDataFile.c_str());
  int fddata = open(FullDataFile.c_str(),O_RDONLY);
  if (fddata == -1) {
    printf("Unable to open DataFile\n");
    return;
  }
  std::string full_path_report_file = DataPath;
  full_path_report_file += ReportFile;
  FILE * fpReport = fopen(full_path_report_file.c_str(),"w");
  if (fpReport == NULL) {
    printf("unable to Open ReportFile [%s]\n",full_path_report_file.c_str());
  }
  bool done = false;
  writeHeader(fpReport);
  int n = 1;
  while (!done) {
    int ret = read(fddata,&OpenEagleExt,sizeof(OpenEagleExt));
    if (ret == sizeof(OpenEagleExt)) {
      if (OpenEagleExt.G5UTCyear>0) {
        writeBody(fpReport);
        printf("%d\n",n);
        n++;
      ///  if (n>1000) done = true;
      } else printf("no year\n");
    }
    else {
      printf("ret != sizeof(OpenEagleExt) assuming EOF on DataFile\n");
      done = true;
    }
  }
  printf("done at n=%d\n",n);
  fclose(fpReport);
  close(fddata);
}

void data_mgr::playbackHistory(std::string path, std::string fn)
{

}
