/***************************************************************
 * Name:      data_conversion.hxx
 * Purpose:   collection of data conversion routines.
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2005
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
#ifndef DATA_CONVERSION
#define DATA_CONVSION
#include <string.h>
#include <string>
char * add_eol_after_column_on_period(char * data, int n);
char * add_eol_after_column(char * data, int n);
char * remove_trailing_spaces(char * data);
//char * get_safe_line(char * tl);
//void   remove_space(char * data);
char *strip_period_and_asterick(char * tl, int limit);
void replace_space_with_under_score(char *tl);
void replace_forward_slash_with_under_score(char *tl);
void   safe_line(char * tl);  /** used by airport.cxx **/
double NASR_coord_to_d(char * coord);
double NASR_f_coord_to_d(char * coord);

int geo_inverse_wgs_84(
      double lat1,
      double lon1,
      double lat2,
			double lon2,
			double *az1,
			double *az2,
      double *s
      );
double ac_from_wgs_84(double dlatc, double dlongc, double dlatp, double dlongp,double *ac_x, double *ac_y);

double angle_to_360_to_720(double angle);

#endif

