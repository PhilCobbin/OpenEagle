/// protocol sent over socket: OpenEagleEM
/***************************************************************
 * Name:      EngineMonitor.hxx
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

 /// ******************** OpenEagleEngineMonitorData ******************** //
  struct OpenEagleEngineMonitorData {        /// data sources          FlightGear Property Tree
  /// Engine Monitor, Arduino Mega ard       ///                    ///
  /// Time variables not tracked             /// EMhour;            ///
                                             /// EMminute;          ///
                                             /// EMsecond;          ///
                                             /// EMsubSecond;       ///
    double EMfuel_psi;                       /// EMFuelPsi;         /// /OpenEagle/engine/fuel-pressure-ps
    double EMoil_psi;                        /// EMOilPsi;          /// /OpenEagle/engine/oil-pressure-psi
    double EMoil_f;                          /// EMOilF;            /// /OpenEagle/engine/oil-temperature-
    double EMcht;                            /// EMCHT;             /// /OpenEagle/engine/cht0-degf
    double EMegt;                            /// EMEGT;             /// /OpenEagle/engine/egt0-degf
  };
  /// ******************** OpenEagleEngineMonitorData ******************** //
  OpenEagleEngineMonitorData OpenEagleEngineMonitor;

  #define EM_BUFFER_SIZE 2000
  char EM_buffer[EM_BUFFER_SIZE];
  char EM_sentance_buffer[EM_BUFFER_SIZE];
  /// Engine Monitor variables for binding to OpenEagleExt structure
  double EMhour;       /// not passed to OpenEagleExt
  double EMminute;     /// not passed to OpenEagleExt
  double EMsecond;     /// not passed to OpenEagleExt
  double EMsubSecond;  /// not passed to OpenEagleExt
  double EMFuelPsi;
  double EMOilPsi;
  double EMOilF;
  double EMCHT;
  double EMEGT;
  int EM_i;

  void EM_init();

  void EM_console();
    // Socket I/O
    void EM_open_socket();
      bool EM_socket_open;
      int EM_socket_fd;     /// port 5555
      #define EM_PORT 5557

    // buffer log
    FILE *EM_sentence_log_fp;

    // Device I/O
    bool EM_open();
      int EM_fd;
      bool EM_opened;

    void EM_read();
      bool EM_read_sentence();
      void EM_parse_sentence(char * buffer, int l);
      void EM_parse_EM();
      void EM_bind_protocol();









