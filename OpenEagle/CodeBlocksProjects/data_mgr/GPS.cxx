/***************************************************************
 * Name:      GPS.cxx
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

#include "data_mgr.hxx"
#include "../3rdparty/constants.h"

 /// GPS, arduino UNO device with adafruit "ultimate GPS" 10 hz capable GPS device (6 meter accuracy)

void data_mgr::GPS_init()
{
/// init GPS
  GPS_send_GPS_protocol                           = false;
  GPS_send_GPSwAlt_protocol                       = false;
  GPS_socket_open                                 = false;
  head_field                                      = NULL;
  current_field                                   = NULL;
  free_field_list                                 = NULL;

  /// initialization OpenEagleAdafruitGPS
  OpenEagleAdafruitGPS.GPS_latitude               = -1.0;
  OpenEagleAdafruitGPS.GPS_longitude              = -1.0;
  OpenEagleAdafruitGPS.GPS_groundspeed_kt         = -1.0;
  OpenEagleAdafruitGPS.GPS_true_heading_deg       = -1.0;

  /// initialization OpenEagleAdafruitGPSAlt
  OpenEagleAdafruitGPSAlt.GPS_latitude            = -1.0;
  OpenEagleAdafruitGPSAlt.GPS_longitude           = -1.0;
  OpenEagleAdafruitGPSAlt.GPS_groundspeed_kt      = -1.0;
  OpenEagleAdafruitGPSAlt.GPS_true_heading_deg    = -1.0;
  OpenEagleAdafruitGPSAlt.GPS_altitude_ft         = -1.0;
}

void data_mgr::GPS_console()
{
 GPS_send_GPS_protocol = true;
 GPS_opened = GPS_open();
 if (!GPS_opened) exit(1);  /// device is not available for reading.
 while (true) {
   GPS_read();
 }
}

void data_mgr::GPSwAlt_console()
{
 GPS_send_GPSwAlt_protocol = true;
 GPS_opened = GPS_open();
 if (!GPS_opened) exit(1);  /// device is not available for reading.
 while (true) {
   GPS_read();
 }
}

void data_mgr::GPS_open_socket()
{
  GPS_socket_open = open_socket(GPS_PORT,&GPS_socket_fd);
  if (!GPS_socket_open) {
    printf("could not open socket to flightgear for GPS protocol\n");
  }
  else {
    printf("GPSsockfd %d for port %d\n",GPS_socket_fd,GPS_PORT);
    fprintf(GPS_sentence_log_fp,"GPSsockfd %d for port %d\n",GPS_socket_fd,GPS_PORT);
  }
}

bool data_mgr::GPS_open()
{
  ///printf("GPS_open():\n");
  GPS_fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);
  if (GPS_fd == -1)
  {
    printf("GPS_open() :: FATAL: unable to open serial GPS arduino uno device\n");
    perror("open_port: Unable to open /dev/ttyACM0");
    return false;
  }
  printf("GPS_open(): GPS_fd %d\n",GPS_fd);
  fcntl(GPS_fd, F_SETFL, 0);
  fcntl(GPS_fd, F_SETFL, FNDELAY);
/// baud rate
  struct termios optionsGPS;

///   * Get the current options for the port...
  tcgetattr(GPS_fd, &optionsGPS);

///   * Set the baud rates ...
/// B0,  B50,  B75,  B110,  B134,  B150,  B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800
  cfsetospeed(&optionsGPS, B115200);

///   * Enable the receiver and set local mode...
  optionsGPS.c_cflag |= (CLOCAL | CREAD);

///   * Set the new options for the port...
  tcsetattr(GPS_fd, TCSANOW, &optionsGPS);

  sleep(3);

  tcflush(GPS_fd,TCIOFLUSH);

/// Now to open log files
  GPS_sentence_log_fp = fopen("GPS_sentence_log.txt","w");
  if (GPS_sentence_log_fp == NULL) {
    printf("FATAL: Could not open GPS_sentence_log.txt\n");
    exit(1);
  }
  return true;
}

void data_mgr::GPS_read()
{
  printf("GPS_read():\n");
  for (int i = 0; i<GPS_BUFFER_SIZE; i++) {
    GPS_buffer[i] = '\0';
    GPS_sentance_buffer[i] = '\0';
  }
  GPS_i = 0;
  cycles = 0;
  do {
    if (GPS_read_sentence() == false) {
      /// 10 hz update rate
      struct timespec ts;
      ts.tv_sec = 0;
      //// tv_nesec range: 0 to
      ///           999999999
      ts.tv_nsec =   11111111;
      nanosleep(&ts, NULL);
    }
  } while (true);
}

bool data_mgr::GPS_read_sentence()
{
  int n = read(GPS_fd,GPS_buffer,1);
  cycles++;
  if (n>0) {
  //  if (GPSbuffer[0] ==0xA) printf(" 0xA ");  GPS seams to emit two 0xA's for "\n"
  //  if (GPSbuffer[0] ==0xD) printf(" 0xD ");  /// Garmin G5 end of record is 0xA .. 0xD
    if (GPS_buffer[0] != 0xA) {
      if (GPS_buffer[0] != 0xD) {
        printf("%c",GPS_buffer[0]);
        GPS_sentance_buffer[GPS_i] = GPS_buffer[0];
        GPS_i++;
        GPS_sentance_buffer[GPS_i] = '\0';
      }
    }
    if (GPS_buffer[0] == 0xA) {
      if (strlen(GPS_sentance_buffer) > 0) {
        printf("\n     Cycles %6d sentence size %3lu ",cycles,strlen(GPS_sentance_buffer));
        GPS_parse_sentence((char *)&GPS_sentance_buffer,strlen(GPS_sentance_buffer));
        GPS_i = 0;
        cycles = 0;
      }
      for (int i = 0; i<GPS_BUFFER_SIZE; i++) {  /// re-initialize GPSsentanceBuffer
        GPS_buffer[i] = '\0';
        GPS_sentance_buffer[i] = '\0';
      }
    }
    return true;
  }
  return false;
}

void data_mgr::GPS_parse_sentence(char * buffer, int l)
{
  fprintf(GPS_sentence_log_fp,"%s\n",buffer);
  ///printf("GPS_parse_sentence(%s, %d)\n",buffer,l);
  bool have_dollar    = false;
  bool have_asterick  = false;
  for (int i = 0; i<l; i++) {
    if (buffer[i] == '$') have_dollar = true;
    if (buffer[i] == '*') have_asterick = true;
  }
  bool valid_sentence = true;
  if (!have_dollar) valid_sentence = false;
  if (!have_asterick) valid_sentence = false;
  if (l <=0) valid_sentence = false;
  if (!valid_sentence) {
    printf("Not a valid sentence: have_dollar %b have_asterick %b l %d\n", have_dollar, have_asterick, l);
    return;
  }

  bool test = GPS_checksumTest(buffer,l);
  if (!test) {
      printf("checksum failed\n");
      return;
  }
  int n = 0;
  head_field = get_field();
  current_field = head_field;
  current_field->n_field = n;
  int length = 0;
  for (int i = 0; i <l; i++ ) {
    if ( (buffer[i] != ',') && (buffer[i] != '*') ) {
      current_field ->field += buffer[i];
      length ++;
      current_field->nullflag = false;
    }
    else {
      struct field* newfield = get_field();
      n++;
      current_field->next_field = newfield;
      current_field = newfield;
      length = 0;
      current_field->n_field=n;
    }
  }
  current_field = head_field;
  current_field = head_field;
  bool parsed = false;
  for (int i = 0; i<5; i++) {
    if ( strcmp(current_field->field.c_str(), GPS_sentences[i].c_str()) == 0) {
      switch (i) {
        case GGA: GPS_parse_GGA();   parsed = true;
        break;
        case GSA: GPS_parse_GSA();   parsed = true;
        break;
        case GSV: GPS_parse_GSV();   parsed = true;
        break;
        case RMC: GPS_parse_RMC();   parsed = true;
        break;
        case VTG: GPS_parse_VTG();   parsed = true;
        break;
        case TOP: parsed = true;
        free_fields();
        break;
        default: printf("unkown GPS sentence\n");
      }
    }
  }
  if (parsed) {
    if (GPS_send_GPSwAlt_protocol) {
      GPS_bind_GPSwAlt_protocol();
      if (GPS_socket_open) {
        int io_ret = write(GPS_socket_fd,&OpenEagleAdafruitGPSAlt,sizeof(OpenEagleAdafruitGPSAlt) );
        if (io_ret <0) {
           printf(" flightgear session ended: socket failure io_ret %d\n",io_ret);
           close(GPS_fd);
           fclose(GPS_sentence_log_fp);
           exit(1);
        } else printf(" write GPS_send_GPSwAlt_protocol to socket successful io_ret %d\n",io_ret);
      }
      else {
        printf("call GPS_open_socket()\n");
        GPS_open_socket(); /// attempt to open socket
        printf("GPS_socket_open  %b\n",GPS_socket_open);
      }
    }
    else {
      if (GPS_send_GPS_protocol) {
        GPS_bind_GPS_protocol();
        if (GPS_socket_open) {
          int io_ret = write(GPS_socket_fd,&OpenEagleAdafruitGPS,sizeof(OpenEagleAdafruitGPS) );
          if (io_ret <0) {
             printf(" flightgear session ended: socket failure io_ret %d\n",io_ret);
             close(GPS_fd);
             fclose(GPS_sentence_log_fp);
             exit(1);
          } else printf(" write GPS_send_GPS_protocol to socket successful io_ret %d\n",io_ret);
        }
        else {
          printf("call GPS_open_socket()\n");
          GPS_open_socket(); /// attempt to open socket
          printf("GPS_socket_open  %b\n",GPS_socket_open);
        }
      }
    }
  }
  else {
    printf("sentance %s is not a valid GPS sentence\n",current_field->field.c_str());
  }
  free_fields();
  for (int i = 0; i<GPS_BUFFER_SIZE; i++) {
    GPS_buffer[i] = '\0';
    GPS_sentance_buffer[i] = '\0';
  }
}

char data_mgr::GPS_get_checksum(char *buffer,int limit)
{
  char checksum = buffer[1]; //$
  for (int i =2; i< limit; i++) {
    if (buffer[i] == '*') break;
    checksum = checksum^buffer[i];
  }
  return checksum;
}

bool data_mgr::GPS_checksumTest(char *buffer,int l)
{
  char checksum = GPS_get_checksum(buffer,l);
  bool found = false;
  int index = l;
  while (!found) {
    if (buffer[index] =='*') found = true;
    else index--;
  }
  char cs[3];
  cs[0] = buffer[ index+1 ];
  cs[1] = buffer[ index+2 ];
  cs[2] = '\0';
  int num = (int)strtoul(cs, NULL, 16);
  if (num==checksum) {
      return true;
  }
  return false;
}

void data_mgr::GPS_parse_GGA()
{
 /// printf("\nGPS_parse_GGA Global Positioning System fixed Data\n");
  current_field = current_field->next_field; ///move to UTC time field
  GPS_set_UTC_TIME();
  current_field = current_field->next_field; ///move to latitude field
  GPS_set_latitude();
  current_field = current_field->next_field; ///move to longitude field
  GPS_set_longitude();
  current_field = current_field->next_field; ///move to Fix position code field
  GPS_fix_position_code = std::stoi(current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to satellites used field
  GPS_n_satellites_used = std::stoi(current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to HDOP used field
  GPS_HDOP = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to altitude meters used field
  GPS_altitude_meters = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to altitude units used field
  current_field = current_field->next_field; ///move to Geoidal Seperation Meters meters used field
  GPS_geoidal_separation_meters = strtod( current_field->field.c_str(),NULL);
  return;
}
void data_mgr::GPS_parse_GSA()
{
///  printf("\nGPS_parse_GSA GNSS DOP and Active Satellites\n");
  current_field = current_field->next_field; ///move to mode 1 field
  char charGpsMode1Code = current_field->field.c_str()[0];
  if (charGpsMode1Code == 'M') GPS_mode_1_code = 1.0;
  else
  if (charGpsMode1Code == 'A') GPS_mode_1_code = 2.0;
  else GPS_mode_1_code = -1.0;
  current_field = current_field->next_field; ///move to mode 2 field
  GPS_mode_2_code = std::stoi(current_field->field.c_str(),NULL);
  for (int i = 0; i<14; i++) {
    current_field = current_field->next_field; ///move to satellite used field
    GPS_satellites_used[i] = std::stoi(current_field->field.c_str(),NULL);
  }
  current_field = current_field->next_field; ///move to PDOP field
  GPS_PDOP = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to HDOP field
  GPS_HDOP = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to VDOP field
  GPS_VDOP = strtod( current_field->field.c_str(),NULL);
}
void data_mgr::GPS_parse_GSV()
{
///  printf("\nGPS_parse_GSV Satellites in view\n");
  while (current_field != NULL) {
    printf("field [%s]\n",current_field->field.c_str());
    current_field = current_field->next_field; ///move to number of messages field
  }
}
void data_mgr::GPS_parse_RMC()
{
///  printf("\nGPS_parse_RMC Recommended Minimum Navigation Information\n");
  current_field = current_field->next_field; ///move to UTC time field
  GPS_set_UTC_TIME();
  current_field = current_field->next_field; ///move to RMC status field
  char charRMCStatus = current_field->field.c_str()[0];
  if (charRMCStatus == 'A') GPS_RMC_status = 1.0;
  else
  if (charRMCStatus == 'V') GPS_RMC_status = 2.0;
  else  GPS_RMC_status = -1.0;
  current_field = current_field->next_field; ///move to latitude field
  GPS_set_latitude();
  current_field = current_field->next_field; ///move to longitude field
  GPS_set_longitude();
  current_field = current_field->next_field; ///move to speed over ground field
  GPS_RMC_speed_over_ground_knots = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to course over ground field
  GPS_RMC_course_over_ground_true = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///move to date field
  if (current_field->next_field != NULL)
    current_field = current_field->next_field; ///move to skip mag var field
  else return;
  if (current_field->next_field != NULL)
    current_field = current_field->next_field; ///move to mode code field
  else return;
  char charRMCMode = current_field->field.c_str()[0];
  if (charRMCMode == 'A') GPS_RMC_mode = 1.0;
  else
  if (charRMCMode == 'D') GPS_RMC_mode = 2.0;
  else
  if (charRMCMode == 'E') GPS_RMC_mode = 1.0;
  else GPS_RMC_mode = -1.0;
}

void data_mgr::GPS_parse_VTG()
{
 // printf("\nGPS_parse_VTG Course and speed relative to ground\n");
  current_field = current_field->next_field; ///move to course field
  GPS_VTG_course_true = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///skip over Reference T field
  current_field = current_field->next_field; ///skip over Reference M field
  GPS_VTG_speed_knots = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field; ///skip over Reference N field
  GPS_VTG_speed_kmph = strtod( current_field->field.c_str(),NULL);
}

void data_mgr::GPS_set_UTC_TIME()
{
/// current_field->field has string in hhmmss.sss format
  char buffer[200];
  strcpy((char*)&buffer,current_field->field.c_str());
  std::string hr = "";
  hr += buffer[0];
  hr += buffer[1];
  std::string mn = "";
  mn += buffer[2];
  mn += buffer[3];
  std::string sc = "";
  sc += buffer[4];
  sc += buffer[5];
  std::string ssc = "0.";
  ssc+= buffer[7];
  ssc+= buffer[8];
  ssc+= buffer[9];
}

void data_mgr::GPS_set_latitude()
{
/// current_field->field has latitude in  ddmm.mmmm format
  char buffer[200];
  strcpy((char*)&buffer,current_field->field.c_str());
  std::string dg = "";
  dg += buffer[0];
  dg += buffer[1];
  std::string mn = "";
  for (int i = 2; i<9; i++) mn += buffer[i];
  current_field = current_field->next_field;
/// current_field->field now is for N/S
  double sign = 0;
  if ( strcmp(current_field->field.c_str(),"N") == 0) sign =  1.0;
  if ( strcmp(current_field->field.c_str(),"S") == 0) sign = -1.0;
  double degree = strtod( dg.c_str(),NULL);
  double minute = strtod( mn.c_str(),NULL);
  minute /= 60.0;
  degree += minute;
  degree *= sign;
  GPS_latitude = degree;
}

void data_mgr::GPS_set_longitude()
{
/// current_field->field has latitude in  dddmm.mmmm format
  char buffer[200];
  strcpy((char*)&buffer,current_field->field.c_str());
  std::string dg = "";
  dg += buffer[0];
  dg += buffer[1];
  dg += buffer[2];
  std::string mn = "";
  for (int i = 3; i<10; i++) mn += buffer[i];
  current_field = current_field->next_field;
/// current_field->field now is for E/W
  double sign = 0;
  if ( strcmp(current_field->field.c_str(),"E") == 0) sign =  1.0;
  if ( strcmp(current_field->field.c_str(),"W") == 0) sign = -1.0;
  double degree = strtod( dg.c_str(),NULL);
  double minute = strtod( mn.c_str(),NULL);
  minute /= 60.0;
  degree += minute;
  degree *= sign;
  GPS_longitude = degree;
}

void data_mgr::GPS_bind_GPS_protocol()
{
///  printf("GPS_bind_GPS_protocol(): ");
  OpenEagleAdafruitGPS.GPS_latitude = GPS_latitude;
  OpenEagleAdafruitGPS.GPS_longitude = GPS_longitude;
  OpenEagleAdafruitGPS.GPS_groundspeed_kt = GPS_RMC_speed_over_ground_knots;
  OpenEagleAdafruitGPS.GPS_true_heading_deg = GPS_RMC_course_over_ground_true;
  if (GPS_RMC_speed_over_ground_knots < 5) OpenEagleAdafruitGPS.GPS_true_heading_deg = 0.0;
  printf(" lat %12.6f", OpenEagleAdafruitGPS.GPS_latitude);
  printf(" lon %12.6f", OpenEagleAdafruitGPS.GPS_longitude);
  printf(" gs_kt %7.2f", OpenEagleAdafruitGPS.GPS_groundspeed_kt);
  printf(" th_deg %7.2f", OpenEagleAdafruitGPS.GPS_true_heading_deg);
}

void data_mgr::GPS_bind_GPSwAlt_protocol()
{
///  printf("GPS_bind_GPSwAlt_protocol()" );
  OpenEagleAdafruitGPSAlt.GPS_latitude = GPS_latitude;
  OpenEagleAdafruitGPSAlt.GPS_longitude = GPS_longitude;
  OpenEagleAdafruitGPSAlt.GPS_groundspeed_kt = GPS_RMC_speed_over_ground_knots;
  OpenEagleAdafruitGPSAlt.GPS_true_heading_deg = GPS_RMC_course_over_ground_true;
  if (GPS_RMC_speed_over_ground_knots < 5) OpenEagleAdafruitGPSAlt.GPS_true_heading_deg = 0.0;
  OpenEagleAdafruitGPSAlt.GPS_altitude_ft = GPS_altitude_meters*SG_METER_TO_FEET;
  printf(" lat %12.6f", OpenEagleAdafruitGPSAlt.GPS_latitude);
  printf(" lon %12.6f", OpenEagleAdafruitGPSAlt.GPS_longitude);
  printf(" gs_kt %7.2f", OpenEagleAdafruitGPSAlt.GPS_groundspeed_kt);
  printf(" th_deg %7.2f", OpenEagleAdafruitGPSAlt.GPS_true_heading_deg);
  printf(" alt_ft %7.0f", OpenEagleAdafruitGPSAlt.GPS_altitude_ft);
}



