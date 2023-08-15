/***************************************************************
 * Name:      Garmin_G5.cxx
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
// Garmin G5, See Garmin G5 Install Manual & Pilot's Guide, Appendix A RS-232 Text Output Format

#include "data_mgr.hxx"
#include <math.h>
#include "../3rdparty/constants.h"

double data_mgr::pressure_altitude_to_indicated(double pressure_altitude, double altimeter_setting)
{
  double ret = pressure_altitude - (1.0 - pow((33.8639*altimeter_setting/1013.25),0.190284))*145366.45;
  return ret;
}

void data_mgr::G5_init()
{
  G5_i                                                         = 0;
  FLTseconds                                                   = 0.0;
  FLTsecondstenths                                             = 0.0;
  G5_socket_open                                               = false;
  /// initialization OpenEagleGarminG5
  OpenEagleGarminG5.G5UTCyear                                  = -1.0;
  OpenEagleGarminG5.G5UTCmonth                                 = -1.0;
  OpenEagleGarminG5.G5UTCday                                   = -1.0;
  OpenEagleGarminG5.G5UTChour                                  = -1.0;
  OpenEagleGarminG5.G5UTCminute                                = -1.0;
  OpenEagleGarminG5.G5UTCsecond                                = -1.0;
  OpenEagleGarminG5.G5UTCsecondFraction                        = -1.0;
  OpenEagleGarminG5.G5pitch_deg                                = -1.0;
  OpenEagleGarminG5.G5roll_deg                                 = -1.0;
  OpenEagleGarminG5.G5airspeed_kt                              = -1.0;
  OpenEagleGarminG5.G5pressure_alt_ft                          = -1.0;
  OpenEagleGarminG5.G5rate_of_turn_dps                         = -1.0;
  OpenEagleGarminG5.G5lateral_acceleration_g                   = -1.0;
  OpenEagleGarminG5.G5vertical_acceleration_g                  = -1.0;
  OpenEagleGarminG5.G5vertical_speed_fpm                       = -1.0;
  OpenEagleGarminG5.G5altimeter_setting_inhg                   = -1.0;
  OpenEagleGarminG5.G5GPSlatitude                              = -1.0;
  OpenEagleGarminG5.G5GPSlongitude                             = -1.0;
  OpenEagleGarminG5.G5GPSposition_status                       = -1.0;
  OpenEagleGarminG5.G5GPShoriz_pos_error_m                     = -1.0;
  OpenEagleGarminG5.G5GPSaltitude_m                            = -1.0;
  OpenEagleGarminG5.G5GPSeast_west_velocity_mps                = -1.0;
  OpenEagleGarminG5.G5GPSnorth_south_velocity_mps              = -1.0;
  OpenEagleGarminG5.G5GPSvertical_velocity_mps                 = -1.0;
  OpenEagleGarminG5.COMPaltitude_ft                            = -1.0;
  OpenEagleGarminG5.COMPspeed_down_fps                         = -1.0;
  OpenEagleGarminG5.COMPspeed_east_fps                         = -1.0;
  OpenEagleGarminG5.COMPspeed_north_fps                        = -1.0;
}

void data_mgr::G5_console()
{
  G5_opened = G5_open();
  if (!G5_opened) exit(1);  /// device is not available for reading.
  while (true) {
    G5_read();
  }
}

void data_mgr::G5_open_socket()
{
  G5_socket_open = open_socket(G5_PORT,&G5_socket_fd);
  if (!G5_socket_open) {
    printf("could not open socket to flightgear for G5 protocol\n");
  }
  else {
    printf("G5_socket_fd %d\n",G5_socket_fd);
  }
}

bool data_mgr::G5_open()
{
  printf("G5_open()\n");
  G5_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (G5_fd == -1)
  {
    printf("FATAL: unable to open serial G5\n");
    perror("open_port: Unable to open /dev/ttyUSB0");
    return false;
  }

  fcntl(G5_fd, F_SETFL, 0);
  fcntl(G5_fd, F_SETFL, FNDELAY);

/// baud rate

  struct termios optionsG5;

///   * Get the current options for the port...

  tcgetattr(G5_fd, &optionsG5);

///   * Set the baud rates ...
/// B0,  B50,  B75,  B110,  B134,  B150,  B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800

  cfsetospeed(&optionsG5, B115200);

///   * Enable the receiver and set local mode...

  optionsG5.c_cflag |= (CLOCAL | CREAD);

///   * Set the new options for the port...

  tcsetattr(G5_fd, TCSANOW, &optionsG5);

  sleep(5);

  tcflush(G5_fd,TCIOFLUSH);

/// Now to open log files
  G5_sentence_log_fp = fopen("G5_sentence_log.txt","w");
  if (G5_sentence_log_fp == NULL) {
    printf("FATAL: Could not open G5_sentence_log.txt\n");
    exit(1);
  }

  return true;
}

void data_mgr::G5_read()
{
  printf("G5_read()\n");
  for (int i = 0; i<GPS_BUFFER_SIZE; i++) {
    GPS_buffer[i] = '\0';
    GPS_sentance_buffer[i] = '\0';
  }
  do {
    if (G5_read_sentence() == false) {
      /// 10 hz update rate
      struct timespec ts;
      ts.tv_sec = 0;
      //// tv_nesec range: 0 to
      ///           999999999
      ts.tv_nsec =  011111111;
      nanosleep(&ts, NULL);
    }
  } while (true);
}

bool data_mgr::G5_read_sentence()
{
  int n = read(G5_fd,G5_buffer,1);
  if (n>0) {
    if (G5_buffer[0] != 0xA) {
      if (G5_buffer[0] != 0xD) {
        G5_sentance_buffer[G5_i] = G5_buffer[0];
        G5_i++;
        G5_sentance_buffer[G5_i] = '\0';  /// always pack a null for end of character string
      }
    }
    if (G5_buffer[0] == 0xD) { /// end of Message
      G5_parse((char *)&G5_sentance_buffer,strlen(G5_sentance_buffer));
      G5_i = 0;
    }
    return true;
  }
  else return false;
}

void data_mgr::G5_parse(char * buffer, int l)
{
  printf("\nG5_parse(...)\n[%s]\n",buffer);
  fprintf(  G5_sentence_log_fp,"%s\n",buffer);
  if (l == 57) return G5_parse_AttAir(buffer,l);
  if (l == 55) return G5_parse_GPS(buffer,l);

//  if (l == 59) return G5_parse_AttAir(buffer,l);
//  if (l == 57) return G5_parse_GPS(buffer,l);
  printf("ERROR: G5 length is %d, should be 55 or 57\n",l);
}

void data_mgr::G5_parse_AttAir(char * buffer, int l)
{
  printf("\nG5_parse_AttAir(...)\n");
///=1115583460-042+0004___0000+03370+001-01+10__+000___2480
///=11hhmmssmmpppprrrrrhhhsssspppppprrrrlllvvvxxvvvvxxxaaacc
  std::string hour;
  hour  = buffer[3];
  hour += buffer[4];
  G5_ATT_AIR_UtcHour = strtod(hour.c_str(),NULL);

  std::string minute;
  minute  = buffer[5];
  minute += buffer[6];
  G5_ATT_AIR_UtcMinute = strtod(minute.c_str(),NULL);

  std::string second;
  second  = buffer[7];
  second += buffer[8];
  G5_ATT_AIR_UtcSecond = strtod(second.c_str(),NULL);

  std::string msecond;
  msecond  = buffer[9];
  msecond += buffer[10];
  G5_ATT_AIR_UtcMsecond = strtod(msecond.c_str(),NULL);
  G5_ATT_AIR_UtcMsecond /= 100.0;

  std::string pitch;
 // pitch  = buffer[10];
  pitch  = buffer[11];
  pitch += buffer[12];
  pitch += buffer[13];
  pitch += buffer[14];
  printf("std::string pitch [%s]\n", pitch.c_str());
  G5_ATT_AIR_PitchDeg = strtod(pitch.c_str(),NULL);
  G5_ATT_AIR_PitchDeg /= 10.0;

  std::string roll;
  roll  = buffer[15];
  roll += buffer[16];
  roll += buffer[17];
  roll += buffer[18];
  roll += buffer[19];
  G5_ATT_AIR_RollDeg = strtod(roll.c_str(),NULL);
  G5_ATT_AIR_RollDeg /= 10.0;

  ///currently no heading information [20]--[22]
  std::string heading;
  heading  = buffer[20];
  heading += buffer[21];
  heading += buffer[22];
  if (buffer[20] != '_') {
    G5_ATT_AIR_HeadingDeg = strtod(heading.c_str(),NULL);
  }
  else G5_ATT_AIR_HeadingDeg = 0.0;

  std::string airspeed;
  airspeed  = buffer[23];
  airspeed += buffer[24];
  airspeed += buffer[25];
  airspeed += buffer[26];
  G5_ATT_AIR_AirspeedKnots = strtod(airspeed.c_str(),NULL);
  G5_ATT_AIR_AirspeedKnots /= 10.0;

  std::string pressalt;
  pressalt  = buffer[27];
  pressalt += buffer[28];
  pressalt += buffer[29];
  pressalt += buffer[30];
  pressalt += buffer[31];
  pressalt += buffer[32];
  G5_ATT_AIR_PressureAltFt = strtod(pressalt.c_str(),NULL);

  std::string turnrate;
  turnrate  = buffer[33];
  turnrate += buffer[34];
  turnrate += buffer[35];
  turnrate += buffer[36];
  G5_ATT_AIR_RateOfTurnDPS = strtod(turnrate.c_str(),NULL);
  G5_ATT_AIR_RateOfTurnDPS /=10.0;

  std::string lataccel;
  lataccel  = buffer[37];
  lataccel += buffer[38];
  lataccel += buffer[39];
  G5_ATT_AIR_LateralAccG = strtod(lataccel.c_str(),NULL);
  G5_ATT_AIR_LateralAccG /= 100.0;

  std::string vertaccel;
  vertaccel  = buffer[40];
  vertaccel += buffer[41];
  vertaccel += buffer[42];
  G5_ATT_AIR_VerticalAccG = strtod(vertaccel.c_str(),NULL);
  G5_ATT_AIR_VerticalAccG /= 10.0;

  /// two unused spaces
  std::string vertspeed;
  vertspeed  = buffer[45];
  vertspeed += buffer[46];
  vertspeed += buffer[47];
  vertspeed += buffer[48];
  G5_ATT_AIR_VerticalSpeedFPM = strtod(vertspeed.c_str(),NULL);
  G5_ATT_AIR_VerticalSpeedFPM *= 10.0;


  /// three unused spaces
  std::string altimeter;
  altimeter  = buffer[52];
  altimeter += buffer[53];
  altimeter += buffer[54];
  G5_ATT_AIR_AltimeterInHg = strtod(altimeter.c_str(),NULL);
  G5_ATT_AIR_AltimeterInHg /= 100.0;
  G5_ATT_AIR_AltimeterInHg += 27.50;

  ///skipping checksum for now

  FLTsecondstenths += 1.0;
  if (FLTsecondstenths>9.0) {
    FLTsecondstenths = 0.0;
    FLTseconds++;
  }

  G5_bind_OpenEagleG5();
  if (G5_socket_open) {
    int io_ret = write(G5_socket_fd, &OpenEagleGarminG5,sizeof(OpenEagleGarminG5) );
    if (io_ret <0) {
      printf("ReadOpenEagleG5(): socket failure io_ret %d\n",io_ret);
      printf("likely fgfs exited\n");
      close(G5_fd);
      fclose(G5_sentence_log_fp);
      exit(1);
    } else printf("\nwrite to socket successful\n");
  }
  else {
    printf("call G5_open_socket()\n");
    G5_open_socket(); /// attempt to open socket
    printf("G5_socket_open  %b\n",G5_socket_open);
  }
}

void data_mgr::G5_parse_GPS(char * buffer, int l)
{
  printf("\nG5_parse_GPS(...)\n");
/// @210523155834N3438916W11146695G017+00151W0001N0000U000 might be missing a char
///  yymmddhhmmss ddmmmmm dddmmmmmSeeeaaaaaa vvvv vvvv mmm
/// @211108195132N3444038W11202330G009+01098E0000N0001U0005
  std::string year;
  year  = buffer[1];
  year += buffer[2];
  G5_GPS_UtcYear = strtod(year.c_str(),NULL);

  std::string month;
  month  = buffer[3];
  month += buffer[4];
  G5_GPS_UtcMonth = strtod(month.c_str(),NULL);

  std::string day;
  day  = buffer[5];
  day += buffer[6];
  G5_GPS_UtcDay = strtod(day.c_str(),NULL);

  std::string hour;
  hour  = buffer[7];
  hour += buffer[8];
  G5_GPS_UtcHour = strtod(hour.c_str(),NULL);

  std::string minute;
  minute  = buffer[9];
  minute += buffer[10];
  G5_GPS_UtcMinute = strtod(minute.c_str(),NULL);

  std::string second;
  second  = buffer[11];
  second += buffer[12];
  G5_GPS_UtcSecond = strtod(second.c_str(),NULL);

  if (buffer[13] != ' ') {
    double sign;
    if (buffer[13] =='N') sign = 1.0; else sign = -1.0;
    std::string latitude;
    latitude  = buffer[14];
    latitude += buffer[15];
    G5_GPS_Latitude = strtod(latitude.c_str(),NULL);

    std::string latmin;
    latmin  = buffer[16];
    latmin += buffer[17];
    latmin += buffer[18];
    latmin += buffer[19];
    latmin += buffer[20];
    double x;
    x = strtod(latmin.c_str(),NULL);
    x /= 1000.0;
    x /= 60.0;
    G5_GPS_Latitude += x;
    G5_GPS_Latitude *= sign;

    std::string longitude;
    if (buffer[21] == 'E') sign = 1.0; else sign = -1.0;
    longitude  = buffer[22];
    longitude += buffer[23];
    longitude += buffer[24];
    G5_GPS_Longitude = strtod(longitude.c_str(),NULL);

    std::string longmin;
    longmin  = buffer[25];
    longmin += buffer[26];
    longmin += buffer[27];
    longmin += buffer[28];
    longmin += buffer[29];

    x = strtod(longmin.c_str(),NULL);
    x /= 1000.0;
    x /= 60.0;
    G5_GPS_Longitude += x;
    G5_GPS_Longitude *= sign;

    char charG5_GPS_PositionStatus = buffer[30];
    if (charG5_GPS_PositionStatus =='g') G5_GPS_PositionStatus = 1.0;
    else
    if (charG5_GPS_PositionStatus =='G') G5_GPS_PositionStatus = 2.0;
    else
    if (charG5_GPS_PositionStatus =='d') G5_GPS_PositionStatus = 3.0;
    else
    if (charG5_GPS_PositionStatus =='D') G5_GPS_PositionStatus = 4.0;
    else
    if (charG5_GPS_PositionStatus =='g') G5_GPS_PositionStatus = 5.0;
    else
    if (charG5_GPS_PositionStatus =='S') G5_GPS_PositionStatus = 7.0;
    else
    if (charG5_GPS_PositionStatus =='_') G5_GPS_PositionStatus = 8.0;
    else  G5_GPS_PositionStatus = 8.0;
    std::string perror;
    perror  = buffer[31];
    perror += buffer[32];
    perror += buffer[33];
    G5_GPS_HorizontalPosErrMeters = strtod(perror.c_str(),NULL);  /// OpenEagle not used

    if ( (buffer[34] == '+') || (buffer[34] == '+') ) {
      std::string altitude;
      altitude  = buffer[34];
      altitude += buffer[35];
      altitude += buffer[36];
      altitude += buffer[37];
      altitude += buffer[38];
      altitude += buffer[39];
      G5_GPS_AltitudeMeters = strtod(altitude.c_str(),NULL);
    }

    if (buffer[40] == 'E') sign = 1.0; else sign = -1.0;
    std::string EWvelocity;
    EWvelocity  = buffer[41];
    EWvelocity += buffer[42];
    EWvelocity += buffer[43];
    EWvelocity += buffer[44];
    G5_GPS_EWvelocityMPS = strtod(EWvelocity.c_str(),NULL);
    G5_GPS_EWvelocityMPS /= 10.0;
    G5_GPS_EWvelocityMPS *= sign;

    if (buffer[45] == 'N') sign = 1.0; else sign = -1.0;
    std::string NSvelocity;
    NSvelocity  = buffer[46];
    NSvelocity += buffer[47];
    NSvelocity += buffer[48];
    NSvelocity += buffer[49];
    G5_GPS_NSvelocityMPS = strtod(NSvelocity.c_str(),NULL);
    G5_GPS_NSvelocityMPS /= 10.0;
    G5_GPS_NSvelocityMPS *= sign;

    if (buffer[50] == 'U') sign = 1.0; else sign = -1.0;
    std::string vertvel;
    vertvel  = buffer[51];
    vertvel += buffer[52];
    vertvel += buffer[53];
    vertvel += buffer[54];
    G5_GPS_VerticalVelocityMPS = strtod(vertvel.c_str(),NULL);
    G5_GPS_VerticalVelocityMPS /= 100.0;
    G5_GPS_VerticalVelocityMPS *= sign;
  }
}

void data_mgr::G5_bind_OpenEagleG5()
{
 printf("G5_bind_OpenEagleG5():");
  /// G5 Att/Air
  OpenEagleGarminG5.G5UTCyear                       = G5_GPS_UtcYear;
  OpenEagleGarminG5.G5UTCmonth                      = G5_GPS_UtcMonth;
  OpenEagleGarminG5.G5UTCday                        = G5_GPS_UtcDay;
  OpenEagleGarminG5.G5UTChour                       = G5_GPS_UtcHour;
  OpenEagleGarminG5.G5UTCminute                     = G5_GPS_UtcMinute;
  OpenEagleGarminG5.G5UTCsecond                     = G5_GPS_UtcSecond;
  OpenEagleGarminG5.G5UTCsecondFraction             = G5_ATT_AIR_UtcMsecond;
  OpenEagleGarminG5.G5pitch_deg                     = G5_ATT_AIR_PitchDeg;
  OpenEagleGarminG5.G5roll_deg                      = G5_ATT_AIR_RollDeg;
  OpenEagleGarminG5.G5airspeed_kt                   = G5_ATT_AIR_AirspeedKnots;
  OpenEagleGarminG5.G5pressure_alt_ft               = G5_ATT_AIR_PressureAltFt;
  OpenEagleGarminG5.G5rate_of_turn_dps              = G5_ATT_AIR_RateOfTurnDPS;
  OpenEagleGarminG5.G5lateral_acceleration_g        = G5_ATT_AIR_LateralAccG;
  OpenEagleGarminG5.G5vertical_acceleration_g       = G5_ATT_AIR_VerticalAccG;
  OpenEagleGarminG5.G5vertical_speed_fpm            = G5_ATT_AIR_VerticalSpeedFPM;
  OpenEagleGarminG5.G5altimeter_setting_inhg        = G5_ATT_AIR_AltimeterInHg;

  /// G5GPS
  OpenEagleGarminG5.G5GPSlatitude                   = G5_GPS_Latitude;
  OpenEagleGarminG5.G5GPSlongitude                  = G5_GPS_Longitude;
  OpenEagleGarminG5.G5GPSposition_status            = G5_GPS_PositionStatus;
  OpenEagleGarminG5.G5GPShoriz_pos_error_m          = G5_GPS_HorizontalPosErrMeters;
  OpenEagleGarminG5.G5GPSaltitude_m                 = G5_GPS_AltitudeMeters;
  OpenEagleGarminG5.G5GPSeast_west_velocity_mps     = G5_GPS_EWvelocityMPS;
  OpenEagleGarminG5.G5GPSnorth_south_velocity_mps   = G5_GPS_NSvelocityMPS;
  OpenEagleGarminG5.G5GPSvertical_velocity_mps      = G5_GPS_VerticalVelocityMPS;
  OpenEagleGarminG5.COMPaltitude_ft                 = pressure_altitude_to_indicated(G5_ATT_AIR_PressureAltFt,G5_ATT_AIR_AltimeterInHg);
  OpenEagleGarminG5.COMPspeed_down_fps              = G5_ATT_AIR_VerticalSpeedFPM/60.0;  /// ATT_AIR Velocity used for VSI indicator (10 hz)
  OpenEagleGarminG5.COMPspeed_east_fps              = G5_GPS_EWvelocityMPS*SG_METER_TO_FEET;
  OpenEagleGarminG5.COMPspeed_north_fps             = G5_GPS_NSvelocityMPS*SG_METER_TO_FEET;

  printf("Altimeter Setting %f Pressure Altitude Ft %f Pitch %f Roll %f\n",
         OpenEagleGarminG5.G5altimeter_setting_inhg,
         OpenEagleGarminG5.G5pressure_alt_ft,
         OpenEagleGarminG5.G5pitch_deg,
         OpenEagleGarminG5.G5roll_deg );
  printf("pitch %f roll %f\n", OpenEagleGarminG5.G5pitch_deg, OpenEagleGarminG5.G5roll_deg);
  printf("Latitude %f Longitude %f COMPaltitude_ft%f\n",
         OpenEagleGarminG5.G5GPSlatitude,
         OpenEagleGarminG5.G5GPSlongitude,
         OpenEagleGarminG5.COMPaltitude_ft);
}
