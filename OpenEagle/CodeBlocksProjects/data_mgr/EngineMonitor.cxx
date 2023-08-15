/***************************************************************
 * Name:      EngineMonitor.cxx
 * Purpose:   read, engine instrument data from Arduino Mega with custom daughter board
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

/// Arduino Mega Engine Monitor
#include "data_mgr.hxx"
#include "EngineMonitor.hxx"

void data_mgr::EM_init()
{
 /// initialization OpenEagleEngineMonitor
   OpenEagleEngineMonitor.EMfuel_psi                                 = -1.0;
   OpenEagleEngineMonitor.EMoil_psi                                  = -1.0;
   OpenEagleEngineMonitor.EMoil_f                                    = -1.0;
   OpenEagleEngineMonitor.EMcht                                      = -1.0;
   OpenEagleEngineMonitor.EMegt                                      = -1.0;
}

void data_mgr::EM_console()
{
 EM_opened = EM_open();
 if (!EM_opened) exit(1);  /// device is not available for reading.
 while (true) {
   EM_read();
 }
}

void data_mgr::EM_open_socket()
{
  EM_socket_open = open_socket(EM_PORT,&EM_socket_fd);
  if (!EM_socket_open) {
    printf("could not open socket to flightgear for EM protocol\n");
  }
  else {
    printf("EM_socket_fd %d\n",EM_socket_fd);
  }
}

bool data_mgr::EM_open()
{
  EM_fd = open("/dev/ttyACM1", O_RDWR | O_NOCTTY | O_NDELAY);
  if (EM_fd == -1)
  {
    printf("FATAL: unable to open serial EM arduino mega device\n");
    perror("open_port: Unable to open /dev/ttyACM1");
    return false;
  }

  fcntl(EM_fd, F_SETFL, 0);
  fcntl(EM_fd, F_SETFL, FNDELAY);

/// baud rate
  struct termios optionsEM;

///   * Get the current options for the port...
  tcgetattr(EM_fd, &optionsEM);

///   * Set the baud rates ...
/// B0,  B50,  B75,  B110,  B134,  B150,  B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800
  cfsetospeed(&optionsEM, B115200);

///   * Enable the receiver and set local mode...
  optionsEM.c_cflag |= (CLOCAL | CREAD);

///   * Set the new options for the port...
  tcsetattr(EM_fd, TCSANOW, &optionsEM);

  sleep(5);

  tcflush(EM_fd,TCIOFLUSH);

/// Now to open log files
  EM_sentence_log_fp = fopen("EM_sentence_log.txt","w");
  if (EM_sentence_log_fp == NULL) {
    printf("FATAL: Could not open EM_sentence_log.txt\n");
    exit(1);
  }

  return true;
}

void data_mgr::EM_read()
{
  printf("EM_read()\n");
  for (int i = 0; i<EM_BUFFER_SIZE; i++) {
    EM_buffer[i] = '\0';
    EM_sentance_buffer[i] = '\0';
  }
  EM_i = 0;
  cycles = 0;
  do {
    if (EM_read_sentence() == false) {
      /// 10 hz update rate
      struct timespec ts;
      ts.tv_sec = 0;
      //// tv_nsec range 0 to
      ////         999999999
      ts.tv_nsec =  11111111;
      nanosleep(&ts,NULL);
    }
  } while (true);
}

bool data_mgr::EM_read_sentence()
{
  int n = read(EM_fd,EM_buffer,1);
  cycles++;
  if (n>0) {
    if (EM_buffer[0] != 0xA) {
      if (EM_buffer[0] != 0xD) {
        printf("%c",EM_buffer[0]);
        EM_sentance_buffer[EM_i] = EM_buffer[0];
        EM_i++;
        EM_sentance_buffer[EM_i] = '\0';
      }
    }
    if (EM_buffer[0] == 0xA) {
      if (strlen(EM_sentance_buffer) > 0) {
        printf("\n     Cycles %6d sentence size %3lu ",cycles,strlen(EM_sentance_buffer));
        EM_parse_sentence((char *)&EM_sentance_buffer,strlen(EM_sentance_buffer));
        EM_i = 0;
        cycles = 0;
      }
      for (int i = 0; i<EM_BUFFER_SIZE; i++) {  /// re-initialize EMsentanceBuffer
        EM_buffer[i] = '\0';
        EM_sentance_buffer[i] = '\0';
      }
    }
    return true;
  }
  return false;
}

void data_mgr::EM_parse_sentence(char * buffer, int l)
{
  fprintf(EM_sentence_log_fp,"%s/n",buffer);
  /// comma delimeted.
  int n = 0;
  head_field = get_field();
  current_field = head_field;
  current_field->n_field = n;
  int length = 0;
  for (int i = 0; i <l; i++ ) {
    if ( (buffer[i] != ',') && (buffer[i] != '\n') ) {  /// no checksum on engine monitor data, line ends on \n
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
  if (n==8) {
    EM_parse_EM();
    EM_bind_protocol();
    if (EM_socket_open) {
      int io_ret = 0;
      io_ret = write(EM_socket_fd,&OpenEagleEngineMonitor,sizeof(OpenEagleEngineMonitor) );
      if (io_ret <0) {
         printf("socket failure io_ret %d\n",io_ret);
         printf("flightgear appears to have exited\n");
         close(EM_fd);
         fclose(EM_sentence_log_fp);
         free_fields();
         exit(1);
      } else printf("\nwrite to socket successful\n");
    }
    else {
      printf("call EM_open_socket()\n");
      EM_open_socket(); /// attempt to open socket
      printf("EM_socket_open  %b\n",EM_socket_open);
    }
  }
  free_fields();
}

void data_mgr::EM_parse_EM()
{
  printf("\nEM_parse()\n");
  EMhour = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMminute = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMsecond = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMsubSecond = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMFuelPsi = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMOilPsi = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMOilF = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMCHT = strtod( current_field->field.c_str(),NULL);
  current_field = current_field->next_field;

  EMEGT = strtod( current_field->field.c_str(),NULL);

}

void data_mgr::EM_bind_protocol()
{
  OpenEagleEngineMonitor.EMfuel_psi = EMFuelPsi;
  OpenEagleEngineMonitor.EMoil_psi = EMOilPsi;
  OpenEagleEngineMonitor.EMoil_f = EMOilF;
  OpenEagleEngineMonitor.EMcht = EMCHT;
  OpenEagleEngineMonitor.EMegt = EMEGT;
  printf("EM_bind_protocol(): ");
  printf(" EMFuelPsi %f",EMFuelPsi);
  printf(" EMOilPsi %f",EMOilPsi);
  printf(" EMOilF %f",EMOilF);
  printf(" EMCHT %f",EMCHT);
  printf(" EMEGT %f\n",EMEGT);
}





