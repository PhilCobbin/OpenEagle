/***************************************************************
 * Name:      time.cxx
 * Purpose:   Code for Application Frame
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2021-04-02
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
#include "../time/time.hxx"
#include <time.h>
#include <stdio.h>

time_t timer;

char fmt_time[100];

char * formatted_time()
{
  time(&timer);
  struct tm *t;
  t = localtime(&timer);
                        ///   yr   mn    dy  hr  min   sec
  sprintf((char *)&fmt_time,"%04d-%02d-%02d-%02d-%02d-%02d-",
          t->tm_year+1900,
          t->tm_mon+1,
          t->tm_mday,
          t->tm_hour,
          t->tm_min,
          t->tm_sec);
  return (char *)&fmt_time;
}

char * formatted_time_year_month_day()
{
  time(&timer);
  struct tm *t;
  t = localtime(&timer);
                        ///   yr   mn    dy
  sprintf((char *)&fmt_time,"%04d-%02d-%02d",
          t->tm_year+1900,
          t->tm_mon+1,
          t->tm_mday);
  return (char *)&fmt_time;

}

