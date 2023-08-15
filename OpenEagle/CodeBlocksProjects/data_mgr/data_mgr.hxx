/***************************************************************
 * Name:      data_mgr.h
 * Purpose:   Code for managing communication from sensors to FlightGear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2021-05-03
 * Copyright: Philip Cobbin (cobbin.com)
 * License:   GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
 * 2023-05-11 add in fuel computer data collection for fuel on board and fuel flow rate
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
#ifndef DATA_MGR_HXX_INCLUDED
#define DATA_MGR_HXX_INCLUDED
#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
///#include <pthread.h>
#include <signal.h>
#include <sys/utsname.h>
#include <time.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../TimeStrings/TimeStrings.hxx"
#include "../airport/airport.hxx"

class data_mgr
{
  public:

    /// data fields from parsing
    struct field {
      struct field * next_field;
      std::string field;
      bool nullflag;
      int n_field;
    };
    struct field * head_field;
    struct field * current_field;
    struct field * free_field_list;

    void free_fields();
    struct field * get_field();
    void destroy_fields();

#define ONE_NANOSECOND 1000000000.0

    /// Flight Time variables passed to OpenEagleExt (from data source) (values will be -1 on simulated data
    double FLTseconds;
    double FLTsecondstenths;

    std::string OpenEagleDataFile;
    std::string OpenEagleDataPath;
/// time
    bool ReportUTCyear;
    bool ReportUTCmonth;
    bool ReportUTCday;
    bool ReportUTChour;
    bool ReportUTCminute;
    bool ReportUTCsecond;
    bool ReportUTCsecondfraction;
/// G5 Att/Air
    bool ReportG5pitch_deg;
    bool ReportG5roll_deg;
    bool ReportG5airspeed_kt;
    bool ReportG5pressure_alt_ft;
    bool ReportG5rate_of_turn_dps;
    bool ReportG5lateral_acceleration_g;
    bool ReportG5vertical_acceleration_g;
    bool ReportG5vertical_speed_fpm;
    bool ReportG5setting_inhg;
/// G5 GPS
    bool ReportG5GPSlatitude;
    bool ReportG5GPSlongitude;
    bool ReportG5GPSposition_status;
    bool ReportG5GPShoriz_position_error_meter;
    bool ReportG5GPSaltitude_meter;
    bool ReportG5GPSeast_west_velocity_mps;
    bool ReportG5GPSnorth_south_velocity_mps;
    bool ReportG5GPSvertical_velocity_mps;
/// Adafruit GPS
    bool Reportlatitude_deg;
    bool Reportlongitude_deg;
    bool Reportgroundspeed_kt;
    bool Reporttrue_heading_deg;
/// Engine Monitor
    bool ReportEMfuel_pressure;
    bool ReportEMoil_pressure;
    bool ReportEMoil_temperature;
    bool ReportEMCHT;
    bool ReportEMEGT;
/// Computed
    bool ReportCOMPaltitude_ft;
    bool ReportCOMPspeed_down_fps;
    bool ReportCOMPspeed_east_fps;
    bool ReportCOMPspeed_north_fps;
    bool ReportCOMPdensity_altitude;
    bool reportCOMPtrue_airspeed;
/// FC-10 Fuel Computer
    bool ReportFCfuel_gallons;
    bool ReportFCfuel_flow;
/// Manual Data Entry
    bool ReportManualfirst_prefix;
    bool ReportManualsecond_prefix;
    bool ReportManualthird_prefix;
    bool ReportManualcrew_weight;
    bool ReportManualbaggage_weight;
    bool ReportManualRPM;
    bool ReportManualmanifold_pressure;
    bool ReportManualoutside_air_temp_degf;
    bool ReportManualflap_setting;
    bool ReportManualcowl_flap_in;

    void writeHeader(FILE * fp);
    void writeBody(FILE * fp);
    void writeReport(char * DataPath, char * DataFile, char * Reportfile);


    bool open_socket(int portno,int *socketfd);

    /// read cycle counter, used to experimentally set nanosleep intervals to start repetitive read attempts before device(s) write
    int cycles;

#include "../data_mgr/EngineMonitor.hxx"
#include "../data_mgr/FC10FuelComputer.hxx"
#include "../data_mgr/GPS.hxx"
#include "../data_mgr/Garmin_G5.hxx"
#include "../data_mgr/Manual.hxx"
#include "../data_mgr/OpenEagleExt.hxx"

/// CRM 114 codebook
#define TAKEOFF 1
#define CLIMB 2
#define CRUISE 3
#define DIVE 4
#define LAND 5
#define SPEED 6
#define STALL 7
#define TURN 8
#define OPE 9
#define UNKNOWN 10

    std::string CodeBook[UNKNOWN+1];
    int code_cnt[UNKNOWN+1];

    struct decodedData {
      decodedData * next_data;
      decodedData * last_data;
      OpenEagleExtData data;
      unsigned long int record_nbr;
    };
    decodedData * first_data;
    decodedData * current_data;
    decodedData * last_data;
    decodedData * get_new_data();
    void destroy_data();

    struct decodedFileList {
      decodedFileList * next_decoded_file;
      int code_index;
      int code_index_cnt;
      std::string path;
      std::string Full_Decoded_File_Name;
    };
    decodedFileList * first_decoded_file;
    decodedFileList * current_decoded_file;
    decodedFileList * last_decoded_file;
    decodedFileList * get_new_decoded_file();
    void destroy_decoded_file_list();
    void add_decoded_file_to_list(int code_index,int code_index_cnt,std::string path, std::string fn_ext);

    int DecodeCRM114files(std::string path, std::string fn);
      void extractTakeoff(FILE * fp);
      void extractClimb(FILE * fp);
      void extractCruise(FILE * fp);
      void extractDive(FILE * fp);
      void extractSpeed(FILE * fp);
      void extractLand(FILE * fp);
      void extractStall(FILE * fp);
      void extractTurn(FILE * fp);
      void extractOPE(FILE * fp);
      void extractUnkown(FILE * fp);

    void extractDecodedFileData(int file_nbr, int code_index, int code_index_cnt, std::string path, std::string Full_Decoded_File_Name);

    void extractDecodedFileData();

    void playbackHistory(std::string path, std::string fn);

    data_mgr(void)
    {
      printf("data_mgr(void):\n");
      printf("sizeof(struct OpenEagleExtData) [%lu]\n",sizeof( struct OpenEagleExtData));
      printf("sizeof(OpenEagleGarminG5) [%lu]\n",sizeof(OpenEagleGarminG5));
      printf("sizeof(OpenEagleGarminG5Data) [%lu]\n",sizeof(OpenEagleGarminG5Data));

      EM_init();
      FC_init();
      GPS_init();
      G5_init();

     /// OpenEagleExt initializations
      OpenEagleExt.G5UTCyear                          = -1.0;
      OpenEagleExt.G5UTCmonth                         = -1.0;
      OpenEagleExt.G5UTCday                           = -1.0;
      OpenEagleExt.G5UTChour                          = -1.0;
      OpenEagleExt.G5UTCminute                        = -1.0;
      OpenEagleExt.G5UTCsecond                        = -1.0;
      OpenEagleExt.G5UTCsecondFraction                = -1.0;
      OpenEagleExt.G5pitch_deg                        = -1.0;
      OpenEagleExt.G5roll_deg                         = -1.0;
      OpenEagleExt.G5airspeed_kt                      = -1.0;
      OpenEagleExt.G5pressure_alt_ft                  = -1.0;
      OpenEagleExt.G5rate_of_turn_dps                 = -1.0;
      OpenEagleExt.G5lateral_acceleration_g           = -1.0;
      OpenEagleExt.G5vertical_acceleration_g          = -1.0;
      OpenEagleExt.G5vertical_speed_fpm               = -1.0;
      OpenEagleExt.G5altimeter_setting_inhg           = -1.0;
      OpenEagleExt.G5GPSlatitude                      = -1.0;
      OpenEagleExt.G5GPSlongitude                     = -1.0;
      OpenEagleExt.G5GPSposition_status               = -1.0;
      OpenEagleExt.G5GPShoriz_pos_error_m             = -1.0;
      OpenEagleExt.G5GPSaltitude_m                    = -1.0;
      OpenEagleExt.G5GPSeast_west_velocity_mps        = -1.0;
      OpenEagleExt.G5GPSnorth_south_velocity_mps      = -1.0;
      OpenEagleExt.G5GPSvertical_velocity_mps         = -1.0;
      OpenEagleExt.GPSlatitude                        = -1.0;
      OpenEagleExt.GPSlongitude                       = -1.0;
      OpenEagleExt.GPSgroundspeed_kt                  = -1.0;
      OpenEagleExt.GPStrue_heading_deg                = -1.0;
      OpenEagleExt.EMfuel_psi                         = -1.0;
      OpenEagleExt.EMoil_psi                          = -1.0;
      OpenEagleExt.EMoil_f                            = -1.0;
      OpenEagleExt.EMcht                              = -1.0;
      OpenEagleExt.EMegt                              = -1.0;
      FLTseconds                                      = -1.0;
      FLTsecondstenths                                = -1.0;
      /// Computed
      OpenEagleExt.COMPaltitude_ft                    = -1.0;
      OpenEagleExt.COMPspeed_down_fps                 = -1.0;
      OpenEagleExt.COMPspeed_east_fps                 = -1.0;
      OpenEagleExt.COMPspeed_north_fps                = -1.0;
      OpenEagleExt.COMPdensity_altitude               = -1.0;
      OpenEagleExt.COMPtrue_airspeed                  = -1.0;
      OpenEagleExt.first_prefix                       = -1.0;
      OpenEagleExt.second_prefix                      = -1.0;
      OpenEagleExt.third_prefix                       = -1.0;
      OpenEagleExt.crew_wt                            = -1.0;
      OpenEagleExt.baggage_wt                         = -1.0;
      OpenEagleExt.fuel_gallons                       = -1.0;
      OpenEagleExt.RPM                                = -1.0;
      OpenEagleExt.manifold_pressure_inhg             = -1.0;
      OpenEagleExt.fuel_flow_gph                      = -1.0;
      OpenEagleExt.outside_air_temp_degf              = -1.0;
      OpenEagleExt.flap_setting                       = -1.0;

      /// initialization OpenEagleManual
      OpenEagleManual.first_prefix                               = -1.0;
      OpenEagleManual.second_prefix                              = -1.0;
      OpenEagleManual.third_prefix                               = -1.0;
      OpenEagleManual.crew_wt                                    = -1.0;
      OpenEagleManual.baggage_wt                                 = -1.0;
      OpenEagleManual.RPM                                        = -1.0;
      OpenEagleManual.manifold_pressure_inhg                     = -1.0;
      OpenEagleManual.outside_air_temp_degf                      = -1.0;
      OpenEagleManual.flap_setting                               = -1.0;
      OpenEagleManual.cowl_flap_in                               = -1.0;

      CodeBook[0]                                     = "NOT USED";
      CodeBook[TAKEOFF]                               = "Takeoff";
      CodeBook[CLIMB]                                 = "Climb";
      CodeBook[CRUISE]                                = "Cruise";
      CodeBook[DIVE]                                  = "Dive";
      CodeBook[SPEED]                                 = "Speed";
      CodeBook[LAND]                                  = "Land";
      CodeBook[STALL]                                 = "Stall";
      CodeBook[TURN]                                  = "Turn";
      CodeBook[OPE]                                   = "OPE";
      CodeBook[UNKNOWN]                               = "OPE";

    first_decoded_file                              = NULL;
    current_decoded_file                            = NULL;


    }
    inline ~data_mgr()
    {

    }

};

#endif // SYSTEM_IO_HXX_INCLUDED
