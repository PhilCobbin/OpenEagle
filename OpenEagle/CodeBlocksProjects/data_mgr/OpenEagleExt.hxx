/***************************************************************
 * Name:      OpenEagleExt.hxx
 * Purpose:   read/write extended data integrated from data sources by flightgear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2023-06-21
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

/// OpenEagleExt protocol structure(s) for I/O with flightgear
/// OpenEagleExtData: from device data augmented with manual and calculated dat
/// *************************************** OpenEagleExtData *************************************** //
    struct OpenEagleExtData {                                ///    FlightGear Property Tree
      double G5UTCyear;                                      /// /OpenEagle/time/G5/utc-year
      double G5UTCmonth;                                     /// /OpenEagle/time/G5/utc-month
      double G5UTCday;                                       /// /OpenEagle/time/G5/utc-day
      double G5UTChour;                                      /// /OpenEagle/time/G5/utc-hour
      double G5UTCminute;                                    /// /OpenEagle/time/G5/utc-minute
      double G5UTCsecond;                                    /// /OpenEagle/time/G5/utc-second
      double G5UTCsecondFraction;                            /// /OpenEagle/time/G5/utc-second-fraction
      double G5pitch_deg;                                    /// /orientation/pitch-deg
      double G5roll_deg;                                     /// /orientation/roll-deg
      double G5airspeed_kt;                                  /// /velocities/airspeed-kt
      double G5pressure_alt_ft;                              /// /instrumentation/altimeter/pressure-alt-ft
      double G5rate_of_turn_dps;                             /// /orientation/yaw-rate-dps
      double G5lateral_acceleration_g;                       /// /OpenEagle/acceleration/lateral_acc_g
      double G5vertical_acceleration_g;                      /// /OpenEagle/acceleration/vertical_acc_g
      double G5vertical_speed_fpm;                           /// /OpenEagle/vertical_speed_fpm
      double G5altimeter_setting_inhg;                       /// /instrumentation/altimeter/setting-inhg
      double G5GPSlatitude;                                  /// /OpenEagle/G5GPS/latitude
      double G5GPSlongitude;                                 /// /OpenEagle/G5GPS/longitude
      /// G5 GPS position status:
      ///   0 = 'g' 2D GPS position
      ///   1 = 'G' 3d GPS position
      ///   2 = 'd' 2d diff GPS position
      ///   3 = 'D' 3d diff GPS position
      ///   4 = 'S' simulated position ???
      ///  -1 - invalid position
      double G5GPSposition_status;                           /// /OpenEagle/G5GPS/position_status
      double G5GPShoriz_pos_error_m;                         /// /OpenEagle/G5GPS/horizontal_position_error_ft
      double G5GPSaltitude_m;                                /// /OpenEagle/G5GPS/altitude_ft
      /// G5 GPS East West velocity E = + W = - (meters/sec)
      double G5GPSeast_west_velocity_mps;                    /// /OpenEagle/G5GPS/east_west_velocity_ft
      /// G5 GPS North South velocity N = + S = - (meters/sec)
      double G5GPSnorth_south_velocity_mps;                  /// /OpenEagle/G5GPS/north_south_velocity_fps
      double G5GPSvertical_velocity_mps;                     /// /OpenEagle/G5GPS/vertical_velocity_fps
      double GPSlatitude;                                    /// /position/latitude-deg
      double GPSlongitude;                                   /// /position/longitude-deg
      double GPSgroundspeed_kt;                              /// /velocities/groundspeed-kt
      double GPStrue_heading_deg;                            /// /orientation/true-heading-deg
      double EMfuel_psi;                                     /// /OpenEagle/engine/fuel-pressure-ps
      double EMoil_psi;                                      /// /OpenEagle/engine/oil-pressure-psi
      double EMoil_f;                                        /// /OpenEagle/engine/oil-temperature-degf
      double EMcht;                                          /// /OpenEagle/engine/cht0-degf
      double EMegt;                                          /// /OpenEagle/engine/egt0-degf
      double COMPaltitude_ft;                                /// /position/altitude-ft
      double COMPspeed_down_fps;                             /// /velocities/speed-down-fps
      double COMPspeed_east_fps;                             /// /velocities/speed-east-fps
      double COMPspeed_north_fps;                            /// /velocities/speed-north-fps
      double COMPdensity_altitude;                           /// /OpenEagle/altitude/density-altitude
      double COMPtrue_airspeed;                              /// /OpenEagle/airspeed/true-airspeed
      /// CRM114 code prefixes:
      ///       See Movie Dr. Strangelove, used to mark flight test data
      /// not to facilitate the end of the world
      double first_prefix;                                   /// /OpenEagle/crm114/first_prefix
      double second_prefix;                                  /// /OpenEagle/crm114/second_prefix
      double third_prefix;                                   /// /OpenEagle/crm114/third_prefix
      double crew_wt;                                        /// /OpenEagle/weight_and_balance/crew_wt
      double baggage_wt;                                     /// /OpenEagle/weight_and_balance/baggage_wt
      double fuel_gallons;                                   /// /OpenEagle/weight_and_balance/fuel_gallons
      double RPM;                                            /// /OpenEagle/engine/RPM
      double manifold_pressure_inhg;                         /// /OpenEagle/engine/manifold-pressure-inhg
      double fuel_flow_gph;                                  /// /OpenEagle/engine/fuel-flow-gph
      double outside_air_temp_degf;                          /// /OpenEagle/temperature/outside-air-temp-degf
      double flap_setting;                                   /// /OpenEagle/flaps/flap_setting
      double cowl_flap_in;                                   /// /OpenEagle/cowl_flap/opening
   };
/// *************************************** OpenEagleExtData *************************************** //
   OpenEagleExtData OpenEagleExt;
   bool sendOpenEagleExtProtocol;
   int OpenEagleExtsockfd;
#define PORT_OPENEAGLEEXT 5555
   FILE * OpenEagleExtfp;
   bool OpenOpenEagleExtFile(std::string path, std::string filename);
   void SendOpenEagleExtProtocol();
   void initOpenEagleExt();//   1/10       1/2     1
   int PlayBackSpeed;      // 12345678 123456789 123456789
   long int nsec_speeds[3] = {99999999,499999999, 99999999};
