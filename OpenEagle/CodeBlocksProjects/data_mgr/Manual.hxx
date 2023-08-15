/***************************************************************
 * Name:      Manual.h
 * Purpose:   Manually set flight data and write using a socket to Flightgear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2023-05-11
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
/// ******************** OpenEagleManualData ******************** //
    struct OpenEagleManualData {                       /// FlightGear Property Tree
      /// CRM114 prefix system for coding flight data  ///
      /// See the Movie Dr. Strangelove                ///
      double first_prefix;                             /// /OpenEagle/crm114/first_prefix
      double second_prefix;                            /// /OpenEagle/crm114/second_prefix
      double third_prefix;                             /// /OpenEagle/crm114/third_prefix
      double crew_wt;                                  /// /OpenEagle/weight_and_balance/crew_wt
      double baggage_wt;                               /// /OpenEagle/weight_and_balance/baggage_wt
      double RPM;                                      /// /OpenEagle/engine/RPM
      double manifold_pressure_inhg;                   /// /OpenEagle/engine/manifold-pressure-inhg
      double outside_air_temp_degf;                    /// /OpenEagle/temperature/outside-air-temp-degf
      double flap_setting;                             /// /OpenEagle/flaps/flap_setting
      double cowl_flap_in;                             /// /OpenEagle/cowl_flap/opening
    };
/// ******************** OpenEagleManualData ******************** //
    OpenEagleManualData OpenEagleManual;

    int MANUALsockfd;  /// port 5559
#define PORT_MANUAL 5559




