/***************************************************************
 * Name:      GPS.hxx
 * Purpose:   read GPS data from an Arduino UNO with an Adafruit Ultimate GPS board
 * and write to socket to interface with flightgear
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
    /// ***************************************** hardware devices ********************************************
    /// GPS, arduino UNO device with adafruit "ultimate GPS" 10 hz capable GPS device (6 meter accuracy)
    /// protocol sent over socket: OpenEagleGPS

    /// console_GPS() approach where (1) open IO to device then write logs of input data
    /// if socket not open try open, if open write protocol out, if IO error on  socket write,
    /// flightgear has exited, so then orderly shutdown of consoleGPS();


     /// ******************** OpenEagleAdaFruitGPSData ******************** //
    struct OpenEagleAdafruitGPSData {                        /// data sources                 FlightGear Property Tree
    /// Arduinno with Adafruit board GPS 10 (hz)             ///                          ///
    /// Configured through Arduino Uno for 10 hz             ///                          ///
    /// output sentencs are GPGGA and GPRMC                  ///                          ///
    /// Examples:                                            ///                          ///
    /// 18:40:16.008 -> $GPRMC,014015.800,A,3439.1665,N,11146.4284,W,0.01,189.52,290523,,,D*79
    /// 18:40:16.107 -> $GPGGA,014016.000,3439.1665,N,11146.4284,W,2,09,0.88,1076.3,M,-24.0,M,0000,0000*6E
    /// 18:40:16.207 -> $GPRMC,014016.000,A,3439.1665,N,11146.4284,W,0.01,244.96,290523,,,D*78
    /// 18:40:16.307 -> $GPGGA,014016.200,3439.1665,N,11146.4284,W,2,09,0.88,1076.3,M,-24.0,M,0000,0000*6C
    /// 18:40:16.406 -> $GPRMC,014016.200,A,3439.1665,N,11146.4284,W,0.01,167.98,290523,,,D*76
    /// 18:40:16.505 -> $GPGGA,014016.400,3439.1665,N,11146.4284,W,2,09,0.88,1076.3,M,-24.0,M,0000,0000*6A
    /// GPGGA data: Time, Position, and fix related data     ///                          ///
    /// GPRMC data: Time, date, position, course and speed   ///                          ///
      double GPS_latitude;                                   /// GpsLatitude;             /// /position/latitude-deg
      double GPS_longitude;                                  /// GpsLongitude;            /// /position/longitude-deg
      double GPS_groundspeed_kt;                             /// RMCSpeedOverGroundKnots  /// /velocities/groundspeed-kt
      double GPS_true_heading_deg;                           /// RMCCourseOverGroundTrue  /// /orientation/true-heading-deg
    };
    /// ******************** OpenEagleAdaFruitGPSData ******************** //
    OpenEagleAdafruitGPSData OpenEagleAdafruitGPS;

    /// ******************** OpenEagleAdaFruitGPSAltData ******************** //
    struct OpenEagleAdafruitGPSAltData {                     /// data sources             FlightGear Property Tree
    /// Arduinno with Adafruit board GPS 10 (hz)             ///                          ///
    /// Configured through Arduino Uno for 10 hz             ///                          ///
    /// output sentencs are GPGGA and GPRMC                  ///                          ///
    /// Examples:                                            ///                          ///
    /// 18:40:16.008 -> $GPRMC,014015.800,A,3439.1665,N,11146.4284,W,0.01,189.52,290523,,,D*79
    /// 18:40:16.107 -> $GPGGA,014016.000,3439.1665,N,11146.4284,W,2,09,0.88,1076.3,M,-24.0,M,0000,0000*6E
    /// 18:40:16.207 -> $GPRMC,014016.000,A,3439.1665,N,11146.4284,W,0.01,244.96,290523,,,D*78
    /// 18:40:16.307 -> $GPGGA,014016.200,3439.1665,N,11146.4284,W,2,09,0.88,1076.3,M,-24.0,M,0000,0000*6C
    /// 18:40:16.406 -> $GPRMC,014016.200,A,3439.1665,N,11146.4284,W,0.01,167.98,290523,,,D*76
    /// 18:40:16.505 -> $GPGGA,014016.400,3439.1665,N,11146.4284,W,2,09,0.88,1076.3,M,-24.0,M,0000,0000*6A
    /// GPGGA data: Time, Position, and fix related data     ///                          ///
    /// GPRMC data: Time, date, position, course and speed   ///                          ///
      double GPS_latitude;                                  /// GpsLatitude;             /// /position/latitude-deg
      double GPS_longitude;                                  /// GpsLongitude;            /// /position/longitude-deg
      double GPS_groundspeed_kt;                             /// RMCSpeedOverGroundKnots  /// /velocities/groundspeed-kt
      double GPS_true_heading_deg;                           /// RMCCourseOverGroundTrue  /// /orientation/true-heading-deg
      double GPS_altitude_ft;                                /// GpsAltitudeMeters*       ///
                                                             ///         SG_METER_TO_FEET /// /position/altitude-ft
    };
    /// ******************** OpenEagleAdaFruitGPSAltData ******************** //
    OpenEagleAdafruitGPSAltData OpenEagleAdafruitGPSAlt;



    #define GPS_BUFFER_SIZE 2000
    char GPS_buffer[GPS_BUFFER_SIZE];
    char GPS_sentance_buffer[GPS_BUFFER_SIZE];
    const std::string GPS_sentences[7] = {"$GPGGA", "$GPGSA", "$GPGSV", "$GPRMC", "$GPVTG", "$PGTOP"};
    /// defines for GPS sentences for adafruit GPS board
    #define GGA 0
    #define GSA 1
    #define GSV 2
    #define RMC 3
    #define VTG 4
    #define TOP 5
    bool GPS_send_GPS_protocol;
    bool GPS_send_GPSwAlt_protocol;
    double GPS_UTC_time_hours;
    double GPS_UTC_time_minutes;
    double GPS_UTC_time_seconds;
    double GPS_UTC_timme_subseconds;
    double GPS_altitude_meters;
    double GPS_fix_position_code;  /// 0 (fix not available), 1 (GPS fix), 2 (Differential GPS fix)
    double GPS_n_satellites_used;   /// 0..14
    double GPS_HDOP;
    double GPS_PDOP;
    double GPS_VDOP;
    double GPS_geoidal_separation_meters;
    double GPS_age_of_diff_corr_seconds;
    double GPS_mode_1_code;  ///   M=1 (Manual—forced to operate in 2D or 3D mode) A=2 (2D Automatic—allowed to automatically switch 2D/3D)
    double GPS_mode_2_code;  ///   1 (Fix not available) 2 (2D (＜4 SVs used)) 3 (3D ( ≧ 4 SVs used))
    #define GPS_MAX_SATELLITES 14
    int GPS_satellites_used[GPS_MAX_SATELLITES];
    int GPS_satellites_in_view;
    struct GPS_in_view {
      int id;
      double elev_deg;
      double azimuth_true;
      int SNR;
    };
    double GPS_RMC_status;  /// A data valid(1) or V, data not valid(2)
    double GPS_RMC_mode;     /// A= 1, Autonomous mode  D=2, Differential mode  E=3, Estimated mode
    double GPS_GLL_status;      /// A (1) valid V (2) invalid
    double GPS_GLL_mode;
    double GPS_GSA_status;
    double GPS_GSA_mode;
    double GPS_GSA_num_satellites;
    double GPS_GSA_PDOP;
    double GPS_GSA_HDOP;
    double GPS_GSA_VDOP;
    double GPS_GSV_total_msgs;
    double GPS_GSV_msg_num;
    double GPS_GSV_total_sat_in_view;
    double GPS_GSV_satellite_id[4];
    double GPS_GSV_satellite_elevation[4];
    double GPS_GSV_satellite_azimuth_true[4];
    double GPS_GSV_signal_2_noise_ratio[4];
    double GPS_VTG_course_true;
    double GPS_VTG_speed_knots;
    double GPS_VTG_speed_kmph;
    double GPS_VTG_mode;   /// A valid (1); V data not valid (2)
    double GPS_TOP_state; /// External Antenna::  1=>Active Antenna Shorted 2=>Using Internal Antenna  3=>Using Active Antenna
   /// GPS variables for binding to GPS structures
    double GPS_latitude;
    double GPS_longitude;
    double GPS_RMC_speed_over_ground_knots;
    double GPS_RMC_course_over_ground_true;
    int GPS_i;

    void GPS_init();

    void GPS_console();
    void GPSwAlt_console();
      /// Socket I/O
      void GPS_open_socket();
        bool GPS_socket_open;
        int GPS_socket_fd;     /// port 5555
        #define GPS_PORT_ALT 5555
        #define GPS_PORT 5555

      /// buffer log
      FILE * GPS_sentence_log_fp;
      /// Device I/0
      bool GPS_open();
        int GPS_fd;
        bool GPS_opened;
      void GPS_read();
        bool GPS_read_sentence();
        void GPS_parse_sentence(char * buffer, int l);
          char GPS_get_checksum(char *buffer,int limit);
          bool GPS_checksumTest(char *buffer,int l);
            void GPS_parse_GGA();
            void GPS_parse_GSA();
            void GPS_parse_GSV();
            void GPS_parse_RMC();
            void GPS_parse_VTG();
            /// parser executive routines::setters for time and lon/lat
            void GPS_set_UTC_TIME();
            void GPS_set_longitude();
            void GPS_set_latitude();
          void GPS_bind_GPS_protocol();
          void GPS_bind_GPSwAlt_protocol();
