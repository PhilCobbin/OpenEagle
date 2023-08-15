/***************************************************************
 * Name:      FC10FuelComputer.cxx
 * Purpose:   read, FC10 fuel computer serial out and
 * write to socket to interface with flightgear
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
// FC-10 Fuel Computer
#include "data_mgr.hxx"

void data_mgr::FC_init()
{
  FC_fd                                    = -1;
  FC_socket_open                           = false;
  FC_fuel_gallons                          = -1;
  FC_fuel_flow_gph                         = -1;

  OpenEagleFC10FuelComputer.fuel_gallons   = -1.0;
  OpenEagleFC10FuelComputer.fuel_flow_gph  = -1.0;
}

void data_mgr::FC_console()
{
 FC_opened = FC_open();
 if (!FC_opened) exit(1);  /// device is not available for reading.
 while (true) {
   FC_read();
 }
}

void data_mgr::FC_open_socket()
{
  FC_socket_open = open_socket(FC_PORT,&FC_socket_fd);
  if (!FC_socket_open) {
    printf("could not open socket to flightgear for FC protocol\n");
  }
  else {
    printf("FC_socket_fd %d\n",FC_socket_fd);
  }

}

bool data_mgr::FC_open()
{
  printf("FC_open():\n");
  FC_fd = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY | O_NDELAY);  /// on aircraft
  if (FC_fd == -1)
  {
    printf("FATAL: unable to open serial FC-10 fuel computer\n");
    perror("open_port: Unable to open /dev/ttyUSB1");
    return false;
  }
  bool error = false;

  printf("FC_fd = %d\n",FC_fd);
  int ret;

  ret = fcntl(FC_fd, F_SETFL, 0);
  if (ret == -1) {
    error = true;
    printf("first fcntl had error\n");
    perror("first fcntl: ");
    printf("\n");
  }
  ret =fcntl(FC_fd, F_SETFL, FNDELAY);
  if (ret == -1) {
    error = true;
    printf("second fcntl had error\n");
  }

/// baud rate
  struct termios optionsFC;

///   * Get the current options for the port...
  ret = tcgetattr(FC_fd, &optionsFC);
  if (ret == -1) {
    error = true;
    printf("tcgetattr() had error\n");
    perror("first fcntl: ");
    printf("\n");
  }
///   * Set the baud rates ...
/// B0,  B50,  B75,  B110,  B134,  B150,  B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800
  ret = cfsetospeed(&optionsFC, B9600);  // likely 9600
  if (ret == -1) {
    error = true;
    printf("cfsetospeed(...) had error\n");
    perror("first fcntl: ");
    printf("\n");
  }

///   * Enable the receiver and set local mode...
  optionsFC.c_cflag |= (CLOCAL | CREAD);

///   * Set the new options for the port...
  ret = tcsetattr(FC_fd, TCSANOW, &optionsFC);
  if (ret == -1) {
    error = true;
    printf("tcsetattr(...) had error\n");
    perror("first fcntl: ");
    printf("\n");
  }
///  sleep(3);

 ret = tcflush(FC_fd,TCIOFLUSH);
  if (ret == -1) {
    error = true;
    printf("tcflush(...) had error\n");
    perror("first fcntl: ");
    printf("\n");
  }

/// Now to open log files
  FC_sentence_log_fp = fopen("FC_sentence_log.txt","w");
  if (FC_sentence_log_fp == NULL) {
    printf("FATAL: Could not open FC_sentence_log.txt\n");
    exit(1);
  }
  if (error) return false;
  return true;
}

void data_mgr::FC_read()
{
  printf("\nFC_read():\n");
  for (int i = 0; i<FC_BUFFER_SIZE; i++) {
    FC_buffer[i] = '\0';
    FC_sentence_buffer[i] = '\0';
  }
  FCi = 0;
  cycles = 0;

  FC_init_read_to_END_OF_TEXT();
  /// 1 hz update rate
  struct timespec ts;
  ts.tv_sec = 0;
//// tv_nesec range: 0 to 999999999
            // 999999999
  ts.tv_nsec = 999100000;  /// 9/10th second
  ts.tv_nsec = 899900000;  /// 9/10th second
  ts.tv_nsec = 999999000;  /// 9/10th second
  ts.tv_nsec = 999999900;  /// 9/10th second
  nanosleep(&ts, NULL);

  /// now for the record read loop...

  while (true) {
    int n = readall(FC_fd,  &FC_buffer, 55);
    FC_buffer[55] = '\0';
    printf("n = %d,FC_buffer[%s]:  ",n,FC_buffer);
    FC_parse_sentence(FC_buffer,strlen(FC_buffer));
    /// 1 hz update rate
    struct timespec ts;
    ts.tv_sec = 0;
//// tv_nesec range: 0 to 999999999
              // 999999999
    ts.tv_nsec = 999100000;  /// 9/10th second
    ts.tv_nsec = 899900000;  /// 9/10th second
    ts.tv_nsec = 999999000;  /// 9/10th second
    ts.tv_nsec = 999999900;  /// 9/10th second
//      ts.tv_nsec = 999500000;  /// 9/10th second
      nanosleep(&ts, NULL);
  }
  int close_status = close(FC_fd);
  printf("close(FC_fd) returned %d",close_status);

}

void data_mgr::FC_init_read_to_END_OF_TEXT()
{
  printf("FC_init_read_to_END_OF_TEXT\n");
  bool done = false;
  while (!done) {
    char test_char;
//    printf("call read(...)\n");
    int bytesRead = read(FC_fd, &test_char, 1);
 //   printf("bytesRead (%d) char [%c]",bytesRead,test_char);
    if (bytesRead == -1) {
      printf("error:\n");
      perror("which error though? ");
      printf("\n");
    }
    if (bytesRead == 1) {
     /// printf("bytesRead (%d) char [%c]\n",bytesRead,test_char);
      if(test_char == END_OF_TEXT) done = true;
     /// printf("FC_init_read_to_END_OF_TEXT() done\n");
    }
    else {
      struct timespec ts;
      ts.tv_sec = 0;
      ts.tv_nsec = 011111111;  /// 1/10th second
   ///   printf("nanosleep: ");
      nanosleep(&ts, NULL);
   ///   printf(" woke up\n");
    }
  }
}

bool data_mgr::FC_read_sentence() //new
{
  return false;
}

ssize_t data_mgr::readall(int fd, void * data, size_t count) {
  ssize_t bytesRead;
  char * dataPtr =   (char * ) data;
  size_t total = 0;
  int cycles = 0;
  while (count) {
    bytesRead = read(fd, dataPtr, count);
    if(bytesRead <= 0) {
      ;
//      printf(".");
    }
    else {
      for (int i = 0; i<bytesRead; i++) {
       // printf("%c",dataPtr[i]);
        data+=dataPtr[i];
      }
    //  printf("%c",*dataPtr);
    //  data += bytesRead;
      count -= bytesRead;
      total += bytesRead;
      cycles++;
    }
  }
  printf("cycles %6d",cycles);
  return total;
}

///////////////////////// FUEL COMPUTER //////////////////////////////////
//
//  A                                                     A
//  S                                                     S
//  C                                                     C
//  I                                                     I
//  I                                                     I
//  ----+----1----+----2----+----3----+----4----+----5----+----6
//  2G0000.0 0000.0 ****** ****** 0000.0 ****** ****** NNN3
//    <GOB > < GPH>               <GUSD>                ?
//
// Strategy for reading:
// read char until ascii 2 (start)  (get start)
// read char's, if not ascii 3 ad to buffer
//
void data_mgr::FC_parse_sentence(char * buffer, int l)
{
  fprintf(FC_sentence_log_fp,"%s\n",buffer);
  printf("FC_parse_sentence...\n[%s]",buffer);
  if (l<55) {
    printf("FC_parse(...) short buffer: %d\n",l);
    return;
  }
  bool error = false;
  if (buffer[0]!= START_OF_TEXT) {
    printf(" bad start of text: %c %x::%x\n",buffer[0],buffer[0],START_OF_TEXT);
    error = true;
  }
  if (buffer[54]!= END_OF_TEXT) {
    printf(" bad end of text: %c %x::%x\n",buffer[54],buffer[54],END_OF_TEXT);
    error = true;
  }
  if (error) {
    printf(" error...\n");
    return;
  }
  char gallons_on_board[100];
  char fuel_flow_gph[100];
  ////not parsed fuel_remaining
  int i;

  for (i=0; i<6; i++) gallons_on_board[i] = buffer[i+2];
  gallons_on_board[i] = '\0';
  FC_fuel_gallons = strtod(gallons_on_board,NULL);

  for (i=0; i<6; i++) fuel_flow_gph[i] = buffer[i+9];
  fuel_flow_gph[i] = '\0';
  FC_fuel_flow_gph = strtod(fuel_flow_gph,NULL);;

  FC_bind_protocol();
  if (FC_socket_open) {
    int io_ret = 0;
    io_ret = write(FC_socket_fd,&OpenEagleFC10FuelComputer,sizeof(OpenEagleFC10FuelComputer) );
    if (io_ret <0) {
       printf("socket failure io_ret %d\n",io_ret);
       printf("flightgear likely exited\n");
       close(FC_fd);
       fclose(GPS_sentence_log_fp);
       exit(1);
    } else printf(" write to socket successful\n");
  }
  else {
    printf("call FC_open_socket()\n");
    FC_open_socket(); /// attempt to open socket
    printf("FC_socket_open  %b\n",FC_socket_open);
  }
}

void data_mgr::FC_bind_protocol()
{
  OpenEagleFC10FuelComputer.fuel_gallons = FC_fuel_gallons;
  OpenEagleFC10FuelComputer.fuel_flow_gph = FC_fuel_flow_gph;
  printf("FC_bind_protocol(): Fuel_gallons %8.1f  FCfuel_flow_gph  %8.1f ",FC_fuel_gallons,FC_fuel_flow_gph);
}



