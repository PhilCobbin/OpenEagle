/***************************************************************
 * Name:      Garmin_G5.hxx
 * Purpose:   read, Garmin G5 RS-232 Text Output Format
 * and write to socket to interface with flightgear
 * Reference: Section 11.4 G5 Installation Mannual for non-certificated
 * instalations.  Rev. 9
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-07-19
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

    double pressure_altitude_to_indicated(double pressure_altitude, double altimeter_setting);

 /// ******************** OpenEagleGarminG5Data ******************** //
    struct OpenEagleGarminG5Data {        /// data sources                            FlightGear Property Tree
    /// ////////////////////////////////////////////// BindOpenEagleGarminG5() call assigns
    /// Garming G5                           ///                                  /// OpenEagleData to the related parser variable(s)
      double G5UTCyear;                      /// G5_ATT_AI_UtcYear;               /// /OpenEagle/time/G5/utc-year
      double G5UTCmonth;                     /// G5_ATT_AI_UtcMonth;              /// /OpenEagle/time/G5/utc-month
      double G5UTCday;                       /// G5_ATT_AI_UtcDay;                /// /OpenEagle/time/G5/utc-day
      double G5UTChour;                      /// G5_ATT_AIR_UtcHour;              /// /OpenEagle/time/G5/utc-hour
      double G5UTCminute;                    /// G5_ATT_AIR_UtcMinute;            /// /OpenEagle/time/G5/utc-minute
      double G5UTCsecond;                    /// G5_ATT_AIR_UtcSecond;            /// /OpenEagle/time/G5/utc-second
      double G5UTCsecondFraction;            /// G5_ATT_AIR_UtcMsecond;           /// /OpenEagle/time/G5/utc-second-fraction
      double G5pitch_deg;                    /// G5_ATT_AIR_PitchDeg;             /// /orientation/pitch-deg
      double G5roll_deg;                     /// G5_ATT_AIR_RollDeg;              /// /orientation/roll-deg
      double G5airspeed_kt;                  /// G5_ATT_AIR_AirspeedKnots;        /// /velocities/airspeed-kt
      double G5pressure_alt_ft;              /// G5_ATT_AIR_PressureAltFt;        /// /instrumentation/altimeter/pressure-alt-ft
      double G5rate_of_turn_dps;             /// G5_ATT_AIR_RateOfTurnDPS;        /// /orientation/yaw-rate-dps
      double G5lateral_acceleration_g;       /// G5_ATT_AIR_LateralAccG;          /// /OpenEagle/acceleration/lateral_acc_g
      double G5vertical_acceleration_g;      /// G5_ATT_AIR_VerticalAccG;         /// /OpenEagle/acceleration/vertical_acc_g
      double G5vertical_speed_fpm;           /// G5_ATT_AIR_VerticalSpeedFPM;     /// /OpenEagle/vertical_speed_fpm
      double G5altimeter_setting_inhg;       /// G5_ATT_AIR_AltimeterInHg;        /// /instrumentation/altimeter/setting-inhg
      double G5GPSlatitude;                  /// G5_GPS_Latitude;                 /// /OpenEagle/G5GPS/latitude
      double G5GPSlongitude;                 /// G5_GPS_Longitude;                /// /OpenEagle/G5GPS/longitude
    /// G5 GPS position status:              ///                                  ///
    ///   0 = 'g' 2D GPS position            ///                                  ///
    ///   1 = 'G' 3d GPS position            ///                                  ///
    ///   2 = 'd' 2d diff GPS position       ///                                  ///
    ///   3 = 'D' 3d diff GPS position       ///                                  ///
    ///   4 = 'S' simulated position ???     ///                                  ///
    ///  -1 - invalid position               ///                                  ///
      double G5GPSposition_status;           /// G5_GPS_PositionStatus            /// /OpenEagle/G5GPS/position_status
      double G5GPShoriz_pos_error_m;         /// G5_GPS_HorizontalPosErrMeters    /// /OpenEagle/G5GPS/horizontal_position_error_ft
      double G5GPSaltitude_m;                /// G5_GPS_AltitudeMeters            /// /OpenEagle/G5GPS/altitude_ft
      double G5GPSeast_west_velocity_mps;    /// G5_GPS_EWvelocityMPS             /// /OpenEagle/G5GPS/east_west_velocity_ft
      double G5GPSnorth_south_velocity_mps;  /// G5_GPS_NSvelocityMPS             /// /OpenEagle/G5GPS/north_south_velocity_fps
      double G5GPSvertical_velocity_mps;     /// G5_GPS_VerticalVelocityMPS       /// /OpenEagle/G5GPS/vertical_velocity_fps
      double COMPaltitude_ft;                /// pressure_altitude_to_indicated(  /// /position/altitude-ft
                                             ///    G5_ATT_AIR_PressureAltFt,     ///
                                             ///    G5_ATT_AIR_AltimeterInHg      ///
                                             /// );                               ///
      double COMPspeed_down_fps;             /// G5_ATT_AIR_VerticalSpeedFPM      /// /velocities/speed-down-fps
      double COMPspeed_east_fps;             /// G5_GPS_EWvelocityMPS             /// /velocities/speed-east-fps
      double COMPspeed_north_fps;            /// G5_GPS_NSvelocity                /// /velocities/speed-north-fps
    };
/// ******************** OpenEagleGarminG5Data ******************** //
    OpenEagleGarminG5Data OpenEagleGarminG5;

    #define G5_BUFFER_SIZE 2000
    char G5_buffer[GPS_BUFFER_SIZE];
    char G5_sentance_buffer[GPS_BUFFER_SIZE];

    /// Garmin G5 Attitude/Air Data (UTC time variables same as G5 GPS with one extra
    double G5_ATT_AIR_UtcHour;
    double G5_ATT_AIR_UtcMinute;
    double G5_ATT_AIR_UtcSecond;
    double G5_ATT_AIR_UtcMsecond;
    double G5_ATT_AIR_PitchDeg;
    double G5_ATT_AIR_RollDeg;
    double G5_ATT_AIR_HeadingDeg;
    double G5_ATT_AIR_AirspeedKnots;
    double G5_ATT_AIR_PressureAltFt;
    double G5_ATT_AIR_RateOfTurnDPS;
    double G5_ATT_AIR_LateralAccG;
    double G5_ATT_AIR_VerticalAccG;
    double G5_ATT_AIR_VerticalSpeedFPM;
    double G5_ATT_AIR_AltimeterInHg;

    /// Garmin G5 GPS variables for binding to OpenEagleExt structure
    double G5_GPS_UtcYear;
    double G5_GPS_UtcMonth;
    double G5_GPS_UtcDay;
    double G5_GPS_UtcHour;
    double G5_GPS_UtcMinute;
    double G5_GPS_UtcSecond;
    double G5_GPS_Latitude;
    double G5_GPS_Longitude;
    double G5_GPS_PositionStatus;
    double G5_GPS_HorizontalPosErrMeters;
    double G5_GPS_AltitudeMeters;
    double G5_GPS_EWvelocityMPS;
    double G5_GPS_NSvelocityMPS;
    double G5_GPS_VerticalVelocityMPS;


    int G5_i;

    void G5_init();

    void G5_console();

      void G5_open_socket();
        bool G5_socket_open;
        int G5_socket_fd;
        #define G5_PORT 5556

      /// buffer log
      FILE *G5_sentence_log_fp;

      /// Device I/O
      bool G5_open();
        bool G5_opened;
        int G5_fd;

      void G5_read();
        bool G5_read_sentence();
        void G5_parse(char * buffer, int l);
          void G5_parse_AttAir(char * buffer, int l);
          void G5_parse_GPS(char * buffer, int l);

        void G5_bind_OpenEagleG5();
