/***************************************************************
 * Name:      FC10FuelComputer.hxx
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

#define START_OF_TEXT 0x2
#define END_OF_TEXT 0x3

  /// ******************** OpenEagleFC10FuelComputerData ******************** //
  struct OpenEagleFC10FuelComputerData {        /// data sources          FlightGear Property Tree
  /// FC10 Fuel Computer, rs232, 9600 baud      ///                    ///
  double fuel_gallons;                          /// FC_fuel_gallons;   ///  /OpenEagle/weight_and_balance/fuel_gallons
  double fuel_flow_gph;                         /// FC_fuel_flow_gph;  ///  /OpenEagle/engine/fuel-flow-gph
  };
  /// ******************** OpenEagleFC10FuelComputerData ******************** //
  /// FC-10 Fuel Computer, yields (1) fuel on board GAL, (2) fuel flow rate GPH and (3) Fuel Used (gal)
  /// Note: (3) not used in OpenEagleExt structure nor inside OpenEagle property tree in FlightGear
  OpenEagleFC10FuelComputerData OpenEagleFC10FuelComputer;

  #define FC_BUFFER_SIZE 2000
  char FC_buffer[FC_BUFFER_SIZE];
  char FC_sentence_buffer[FC_BUFFER_SIZE];
  int FCi;

//  #define START_OF_TEXT 02
//  #define END_OF_TEXT 03

  double FC_fuel_gallons;
  double FC_fuel_flow_gph;

  void FC_init();
  void FC_console();

    void FC_open_socket();
      bool FC_socket_open;
      int FC_socket_fd;
      #define FC_PORT 5558

    bool FC_open();
      int FC_fd;
      bool FC_opened;

  FILE * FC_sentence_log_fp;
  void FC_read();
    void FC_init_read_to_END_OF_TEXT();
    bool FC_read_sentence(); //new
    ssize_t readall(int fd, void * data, size_t count);
    void FC_parse_sentence(char * buffer, int l);
///    void FC_parse(char * buffer, int l);
    void FC_bind_protocol();


