/***************************************************************
 * Name:      TimeStrings.cxx
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
#include "../TimeStrings/TimeStrings.hxx"
#include <time.h>
#include <stdio.h>

void TimeStrings::set_time_strings()
{
  time_t now;
  struct tm *t;
  now = time((time_t *)NULL);
  t = localtime(&now);

  int year = t->tm_year;
  year += 1900;
  int month = t->tm_mon+1;
  int day = t->tm_mday;
  int second = t->tm_sec;
  int minute = t->tm_min;
  int hour = t->tm_hour;

  time_yr_mn_day_hr_min_path_str += std::to_string(year);
  ///time_yr_mn_day_hr_min_path_str  += "/";
  time_yr_mn_day_hr_min_path_str  += "-";

  if (month < 10) time_yr_mn_day_hr_min_path_str  += "0";
  time_yr_mn_day_hr_min_path_str  += std::to_string(month);
//  time_yr_mn_day_hr_min_path_str  += "/";
  time_yr_mn_day_hr_min_path_str  += "-";

  if (day < 10) time_yr_mn_day_hr_min_path_str  += "0";
  time_yr_mn_day_hr_min_path_str  += std::to_string(day);
///  time_yr_mn_day_hr_min_path_str  += "/";
  time_yr_mn_day_hr_min_path_str  += "-";

  if (hour < 10) time_yr_mn_day_hr_min_path_str  += "0";
  time_yr_mn_day_hr_min_path_str  += std::to_string(hour);
  ///time_yr_mn_day_hr_min_path_str  += "/";
  time_yr_mn_day_hr_min_path_str  += "-";

  if (minute < 10) time_yr_mn_day_hr_min_path_str  += "0";
  time_yr_mn_day_hr_min_path_str  += std::to_string(minute);
 /// time_yr_mn_day_hr_min_path_str  += "/";
  time_yr_mn_day_hr_min_path_str  += "-";

  time_full_dashed_str += std::to_string(year);
  time_full_dashed_str  += "-";

  time_full_dashed_str  += std::to_string(month);
  time_full_dashed_str  += "-";

  time_full_dashed_str  += std::to_string(day);
  time_full_dashed_str  += "-";

  time_full_dashed_str  += std::to_string(hour);
  time_full_dashed_str  += "-";

  time_full_dashed_str  += std::to_string(minute);
  time_full_dashed_str  += "-";

  time_full_dashed_str += std::to_string(second);
}
