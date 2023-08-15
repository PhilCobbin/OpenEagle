/***************************************************************
 * Name:      TimeStrings.h
 * Purpose:   Manage flightgear and OpenEagle time strings for setting path elements and file name elements
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2022-02-01
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
#ifndef TIMESTRINGS_H
#define TIMESTRINGS_H
#include <string>
class TimeStrings
{
  public:
    std::string time_yr_mn_day_hr_min_path_str;
    std::string time_full_dashed_str;
    void set_time_strings();
};
#endif
