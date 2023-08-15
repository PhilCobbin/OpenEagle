/***************************************************************
 * Name:      data_conversion.cxx
 * Purpose:   collection of data conversion routines, some from simgear
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2005
 * Copyright: Philip Cobbin (cobbin.com)
 * License    GPLv3 see: https://www.gnu.org/licenses/gpl-3.0.html
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
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "data_conversion.hxx"
#include "../3rdparty/constants.h"


char data_conversion[1000];
/**
void remove_space(char * data)
{
  int l;
  l= strlen(data);
  int i;
  for (i=l-1; i>=0; i--) {
    if (isalnum(data[i])) return;
    else data[i]='\0';
  }
}
**/
char * add_eol_after_column_on_period(char * data, int n)
{
  int i = 0;
  int column = 0;
  while (data[i] != '\0') {
     i++;
     column++;
     if (column > n) {
       if ( data[i] == '.') {
         if (data[i+1] == ' ') {
           data[i+1] = '\n';
           column = 0;
           int j = i+2;
           while (data[j] == ' ') j++;
           int k = i+2;
           while (data[j] != '\0') {
             data[k]=data[j];
              k++;
              j++;
           }
           data[k]=data[j];
         }
       }
     }
   }
   return data;
}



char * add_eol_after_column(char * data, int n)
{
  int i = 0;
  int column = 0;
  while (data[i] != '\0') {
     i++;
     column++;
     if (data[i] == '\n') column = 0;
     if (column > n) {
       if (data[i] == ' '){
         data[i] = '\n';
         column = 0;
       }
     }
   }
   return data;
}
char * remove_trailing_spaces(char * data)
{
   int l= strlen(data) - 2;
   if (l>0) {
     while (data[l] == ' ') {
      data[l]='\0';
      l--;
     }
   }
  return data;
}


char data_conversion2[1000];

char * get_safe_line(char * tl)
{
  strcpy((char *)&data_conversion2,tl);

  int i=0;
  while (data_conversion2[i]!='\0') {
    if ( data_conversion2[i]=='\'') data_conversion2[i]=' ';
    if ( data_conversion2[i]=='"') data_conversion2[i]=' ';
    if ( data_conversion2[i]=='(') data_conversion2[i]=' ';
    if ( data_conversion2[i]==')') data_conversion2[i]=' ';
    i++;
  }
  return (char *)&data_conversion2;
}

char * strip_period_and_asterick(char * tl, int limit)  ///note blank terminates  'if and when' will return 'if'
{
  int i = 0;
  int j = 0;
  bool done = false;
  do {
    if (tl[i] != '.') {
      if (tl[i] != '*') {
        data_conversion[j]=tl[i];
        j++;
        data_conversion[j]='\0';
      }
    }
    i++;
    if (tl[i] == '\0') done = true;
    if (tl[i] == ' ') done = true;
   // if (i >= limit) done = true;
  } while (!done);
  data_conversion[i] ='\0';
  return (char *)&data_conversion;
}

void replace_space_with_under_score(char * tl)
{
  int i=0;
  while (tl[i]!='\0') {
    if (tl[i]==' ') tl[i]='_';
    i++;
  }
}
void replace_forward_slash_with_under_score(char *tl)
{
  int i=0;
  while (tl[i]!='\0') {
    if (tl[i]=='/') tl[i]='_';
    i++;
  }
}

void safe_line(char * tl)
{
  int i=0;
  while (tl[i]!='\0') {
    if (tl[i]=='\'') tl[i]=' ';
    if (tl[i]==',') tl[i]=' ';
    if (tl[i]=='/') tl[i]=' ';
    i++;
  }
}

double NASR_coord_to_d(char * coord)
{
#define COORD_SECONDS_SIZE 11
  double ret;
  char dir;
  int i=0;
  if ((coord[0]==' ') || (coord[0]=='\0')) return 0.0;
  dir = coord[i];
  while (!isalpha(dir)) {
    dir = coord[i];
    i++;
  }
  sscanf(coord,"%lf",&ret);
  ret = ret/3600.0;
  if ( (dir=='N') || (dir == 'E')) return ret; else return -ret;
}

double NASR_f_coord_to_d(char * coord)
{
// latitude [45-40-18.410N ] longitude [092-13-39.690W]
  double ret;
  char degree[7];
  char minute[7];
  char sec[7];
  char dir;
  int i;
  int j;
  i=0;
  if (coord[0] == '\0' || coord[0]==' ') {
 //   printf("Bad call to NASR_f_coord_to_d [%s]\n",coord);
    return(0.0);//    exit(-1);
  }
  while (coord[i]!='-') {
    degree[i]=coord[i];
    i++;
  }
  degree[i]='\0';
  i++;
  j=0;
  while (coord[i]!='-') {
    minute[j]=coord[i];
    i++;
    j++;
  }
  minute[j]='\0';
  i++;
  j=0;
  while (!isalpha(coord[i])) {
    sec[j]=coord[i];
    i++;
    j++;
  }
  sec[j]='\0';
  dir=coord[i];
  ret = strtod(degree,NULL) + strtod(minute,NULL)/60.0 + strtod(sec,NULL)/3600.0;
  if ( (dir=='N') || (dir == 'E')) return ret; else return -ret;
}


// These are hard numbers from the WGS84 standard.  DON'T MODIFY
// unless you want to change the datum.
#define _EQURAD 6378137.0
#define _FLATTENING 298.257223563

double rad2deg(const double& val)
  { return val*180/SGD_PI; }

double deg2rad(const double& val)
  { return val*SGD_PI/180; }


/**
// given lat1, lon1, lat2, lon2, calculate starting and ending
// az1, az2 and distance (s).  Lat, lon, and azimuth are in degrees.
// distance in meters
**/
/**
int geo_inverse_wgs_84( double lat1, double lon1, double lat2,
			double lon2, double *az1, double *az2,
                        double *s )
{
//    double a = SGGeodesy::EQURAD, rf = SGGeodesy::iFLATTENING;    int iter=0;
    double a = _EQURAD, rf = _FLATTENING;    int iter=0;
    double testv = 1.0E-10;
    double f = ( rf > 0.0 ? 1.0/rf : 0.0 );
    double b = a*(1.0-f);
    // double e2 = f*(2.0-f); // unused in this routine
    double phi1 = deg2rad(lat1), lam1 = deg2rad(lon1);
    double sinphi1 = sin(phi1), cosphi1 = cos(phi1);
    double phi2 = deg2rad(lat2), lam2 = deg2rad(lon2);
    double sinphi2 = sin(phi2), cosphi2 = cos(phi2);

    if( (fabs(lat1-lat2) < testv &&
	 ( fabs(lon1-lon2) < testv)) || (fabs(lat1-90.0) < testv ) )
    {
	// TWO STATIONS ARE IDENTICAL : SET DISTANCE & AZIMUTHS TO ZERO
	*az1 = 0.0; *az2 = 0.0; *s = 0.0;
	return 0;
    } else if(  fabs(cosphi1) < testv ) {
	// initial point is polar
	int k = geo_inverse_wgs_84( lat2,lon2,lat1,lon1, az1,az2,s );
	k = k; // avoid compiler error since return result is unused
	b = *az1; *az1 = *az2; *az2 = b;
	return 0;
    } else if( fabs(cosphi2) < testv ) {
	// terminal point is polar
        double _lon1 = lon1 + 180.0f;
	int k = geo_inverse_wgs_84( lat1, lon1, lat1, _lon1,
				    az1, az2, s );
	k = k; // avoid compiler error since return result is unused
	*s /= 2.0;
	*az2 = *az1 + 180.0;
	if( *az2 > 360.0 ) *az2 -= 360.0;
	return 0;
    } else if( (fabs( fabs(lon1-lon2) - 180 ) < testv) &&
	       (fabs(lat1+lat2) < testv) )
    {
	// Geodesic passes through the pole (antipodal)
	double s1,s2;
	geo_inverse_wgs_84( lat1,lon1, lat1,lon2, az1,az2, &s1 );
	geo_inverse_wgs_84( lat2,lon2, lat1,lon2, az1,az2, &s2 );
	*az2 = *az1;
	*s = s1 + s2;
	return 0;
    } else {
	// antipodal and polar points don't get here
	double dlam = lam2 - lam1, dlams = dlam;
	double sdlams,cdlams, sig,sinsig,cossig, sinaz,
	    cos2saz, c2sigm;
	double tc,temp, us,rnumer,denom, ta,tb;
	double cosu1,sinu1, sinu2,cosu2;

	// Reduced latitudes
	temp = (1.0-f)*sinphi1/cosphi1;
	cosu1 = 1.0/sqrt(1.0+temp*temp);
	sinu1 = temp*cosu1;
	temp = (1.0-f)*sinphi2/cosphi2;
	cosu2 = 1.0/sqrt(1.0+temp*temp);
	sinu2 = temp*cosu2;

	do {
	    sdlams = sin(dlams), cdlams = cos(dlams);
	    sinsig = sqrt(cosu2*cosu2*sdlams*sdlams+
			  (cosu1*sinu2-sinu1*cosu2*cdlams)*
			  (cosu1*sinu2-sinu1*cosu2*cdlams));
	    cossig = sinu1*sinu2+cosu1*cosu2*cdlams;

	    sig = atan2(sinsig,cossig);
	    sinaz = cosu1*cosu2*sdlams/sinsig;
	    cos2saz = 1.0-sinaz*sinaz;
	    c2sigm = (sinu1 == 0.0 || sinu2 == 0.0 ? cossig :
		      cossig-2.0*sinu1*sinu2/cos2saz);
	    tc = f*cos2saz*(4.0+f*(4.0-3.0*cos2saz))/16.0;
	    temp = dlams;
	    dlams = dlam+(1.0-tc)*f*sinaz*
		(sig+tc*sinsig*
		 (c2sigm+tc*cossig*(-1.0+2.0*c2sigm*c2sigm)));
	    if (fabs(dlams) > SGD_PI && iter++ > 50) {
		return iter;
	    }
	} while ( fabs(temp-dlams) > testv);

	us = cos2saz*(a*a-b*b)/(b*b); // !!
	// BACK AZIMUTH FROM NORTH
	rnumer = -(cosu1*sdlams);
	denom = sinu1*cosu2-cosu1*sinu2*cdlams;
	*az2 = rad2deg(atan2(rnumer,denom));
	if( fabs(*az2) < testv ) *az2 = 0.0;
	if(*az2 < 0.0) *az2 += 360.0;

	// FORWARD AZIMUTH FROM NORTH
	rnumer = cosu2*sdlams;
	denom = cosu1*sinu2-sinu1*cosu2*cdlams;
	*az1 = rad2deg(atan2(rnumer,denom));
	if( fabs(*az1) < testv ) *az1 = 0.0;
	if(*az1 < 0.0) *az1 += 360.0;

	// Terms a & b
	ta = 1.0+us*(4096.0+us*(-768.0+us*(320.0-175.0*us)))/
	    16384.0;
	tb = us*(256.0+us*(-128.0+us*(74.0-47.0*us)))/1024.0;

	// GEODETIC DISTANCE
	*s = b*ta*(sig-tb*sinsig*
		   (c2sigm+tb*(cossig*(-1.0+2.0*c2sigm*c2sigm)-tb*
			       c2sigm*(-3.0+4.0*sinsig*sinsig)*
			       (-3.0+4.0*c2sigm*c2sigm)/6.0)/
		    4.0));
	return 0;
    }
}
**/

// latest simgear simgear-2020.3.5 _geo_inverse_wgs_84 tweaked
/// sg_geodesy.hxx and SGGeodesy.cxx



static double pi() { return double(3.1415926535897932384626433832795029L); }

int geo_inverse_wgs_84(
      double lat1,
      double lon1,
      double lat2,
			double lon2,
			double *az1,
			double *az2,
      double *s
      )
{
   // double a = EQURAD, rf = iFLATTENING;
    int iter=0;
    double a = _EQURAD, rf = _FLATTENING;   // int iter=0;

    double testv = 1.0E-10;
    double f = ( rf > 0.0 ? 1.0/rf : 0.0 );
    double b = a*(1.0-f);
    // double e2 = f*(2.0-f); // unused in this routine
    double phi1 = deg2rad(lat1), lam1 = deg2rad(lon1);
    double sinphi1 = sin(phi1), cosphi1 = cos(phi1);
    double phi2 = deg2rad(lat2), lam2 = deg2rad(lon2);
    double sinphi2 = sin(phi2), cosphi2 = cos(phi2);

    if( (fabs(lat1-lat2) < testv &&
	 ( fabs(lon1-lon2) < testv)) || (fabs(lat1-90.0) < testv ) )
    {
	// TWO STATIONS ARE IDENTICAL : SET DISTANCE & AZIMUTHS TO ZERO */
	*az1 = 0.0; *az2 = 0.0; *s = 0.0;
	return 0;
    } else if(  fabs(cosphi1) < testv ) {
	// initial point is polar
	//int k =
	geo_inverse_wgs_84( lat2,lon2,lat1,lon1, az1,az2,s );
//	SG_UNUSED(k);

	b = *az1; *az1 = *az2; *az2 = b;
	return 0;
    } else if( fabs(cosphi2) < testv ) {
	// terminal point is polar
        double _lon1 = lon1 + 180.0f;
	//int k =
	geo_inverse_wgs_84( lat1, lon1, lat1, _lon1, az1, az2, s );
//	SG_UNUSED(k);

	*s /= 2.0;
	*az2 = *az1 + 180.0;
	if( *az2 > 360.0 ) *az2 -= 360.0;
	return 0;
    } else if( (fabs( fabs(lon1-lon2) - 180 ) < testv) &&
	       (fabs(lat1+lat2) < testv) )
    {
	// Geodesic passes through the pole (antipodal)
	double s1,s2;
	geo_inverse_wgs_84( lat1,lon1, lat1,lon2, az1,az2, &s1 );
	geo_inverse_wgs_84( lat2,lon2, lat1,lon2, az1,az2, &s2 );
	*az2 = *az1;
	*s = s1 + s2;
	return 0;
    } else {
	// antipodal and polar points don't get here
	double dlam = lam2 - lam1, dlams = dlam;
	double sdlams,cdlams, sig,sinsig,cossig, sinaz,
	    cos2saz, c2sigm;
	double tc,temp, us,rnumer,denom, ta,tb;
	double cosu1,sinu1, sinu2,cosu2;

	// Reduced latitudes
	temp = (1.0-f)*sinphi1/cosphi1;
	cosu1 = 1.0/sqrt(1.0+temp*temp);
	sinu1 = temp*cosu1;
	temp = (1.0-f)*sinphi2/cosphi2;
	cosu2 = 1.0/sqrt(1.0+temp*temp);
	sinu2 = temp*cosu2;

	do {
	    sdlams = sin(dlams), cdlams = cos(dlams);
	    sinsig = sqrt(cosu2*cosu2*sdlams*sdlams+
			  (cosu1*sinu2-sinu1*cosu2*cdlams)*
			  (cosu1*sinu2-sinu1*cosu2*cdlams));
	    cossig = sinu1*sinu2+cosu1*cosu2*cdlams;

	    sig = atan2(sinsig,cossig);
	    sinaz = cosu1*cosu2*sdlams/sinsig;
	    cos2saz = 1.0-sinaz*sinaz;
	    c2sigm = (sinu1 == 0.0 || sinu2 == 0.0 ? cossig :
		      cossig-2.0*sinu1*sinu2/cos2saz);
	    tc = f*cos2saz*(4.0+f*(4.0-3.0*cos2saz))/16.0;
	    temp = dlams;
	    dlams = dlam+(1.0-tc)*f*sinaz*
		(sig+tc*sinsig*
		 (c2sigm+tc*cossig*(-1.0+2.0*c2sigm*c2sigm)));
	    if (fabs(dlams) > pi() && iter++ > 50) {
		return iter;
	    }
	} while ( fabs(temp-dlams) > testv);

	us = cos2saz*(a*a-b*b)/(b*b); // !!
	// BACK AZIMUTH FROM NORTH
	rnumer = -(cosu1*sdlams);
	denom = sinu1*cosu2-cosu1*sinu2*cdlams;
	*az2 = rad2deg(atan2(rnumer,denom));
	if( fabs(*az2) < testv ) *az2 = 0.0;
	if(*az2 < 0.0) *az2 += 360.0;

	// FORWARD AZIMUTH FROM NORTH
	rnumer = cosu2*sdlams;
	denom = cosu1*sinu2-sinu1*cosu2*cdlams;
	*az1 = rad2deg(atan2(rnumer,denom));
	if( fabs(*az1) < testv ) *az1 = 0.0;
	if(*az1 < 0.0) *az1 += 360.0;

	// Terms a & b
	ta = 1.0+us*(4096.0+us*(-768.0+us*(320.0-175.0*us)))/
	    16384.0;
	tb = us*(256.0+us*(-128.0+us*(74.0-47.0*us)))/1024.0;

	// GEODETIC DISTANCE
	*s = b*ta*(sig-tb*sinsig*
		   (c2sigm+tb*(cossig*(-1.0+2.0*c2sigm*c2sigm)-tb*
			       c2sigm*(-3.0+4.0*sinsig*sinsig)*
			       (-3.0+4.0*c2sigm*c2sigm)/6.0)/
		    4.0));
	return 0;
    }
}


/**

// given lat1, lon1, lat2, lon2, calculate starting and ending
// az1, az2 and distance (s).  Lat, lon, and azimuth are in degrees.
// distance in meters
//static
int geo_inverse_wgs_84( double lat1, double lon1, double lat2,
			double lon2, double *az1, double *az2,
                        double *s )
{
// openeaglehack    double a = SGGeodesy::EQURAD, rf = SGGeodesy::iFLATTENING;
  double a = _EQURAD, rf = _FLATTENING;   // int iter=0;
  int iter=0;
  double testv = 1.0E-10;
  double f = ( rf > 0.0 ? 1.0/rf : 0.0 );
  double b = a*(1.0-f);
  // double e2 = f*(2.0-f); // unused in this routine
  double phi1 = deg2rad(lat1), lam1 = deg2rad(lon1);
  double sinphi1 = sin(phi1), cosphi1 = cos(phi1);
  double phi2 = deg2rad(lat2), lam2 = deg2rad(lon2);
  double sinphi2 = sin(phi2), cosphi2 = cos(phi2);

  if( (fabs(lat1-lat2) < testv &&
	 ( fabs(lon1-lon2) < testv)) || (fabs(lat1-90.0) < testv ) )
  {
	// TWO STATIONS ARE IDENTICAL : SET DISTANCE & AZIMUTHS TO ZERO
	*az1 = 0.0; *az2 = 0.0; *s = 0.0;
	printf("geo_inverse_wgs_84 ret #1\n");
	return 0;
  }
  if(  fabs(cosphi1) < testv ) {
	// initial point is polar
	int k = geo_inverse_wgs_84( lat2,lon2,lat1,lon1, az1,az2,s );
//	SG_UNUSED(k);

  	b = *az1; *az1 = *az2; *az2 = b;
  	printf("geo_inverse_wgs_84 ret #2\n");
    return 0;
  }
  if( fabs(cosphi2) < testv ) {
	// terminal point is polar
    double _lon1 = lon1 + 180.0f;
	int k = geo_inverse_wgs_84( lat1, lon1, lat1, _lon1,
				    az1, az2, s );
	  //SG_UNUSED(k);

  	*s /= 2.0;
	*az2 = *az1 + 180.0;
	if( *az2 > 360.0 ) *az2 -= 360.0;
 	printf("geo_inverse_wgs_84 ret #3\n");
	return 0;
  }
  if( (fabs( fabs(lon1-lon2) - 180 ) < testv) &&
	       (fabs(lat1+lat2) < testv) )
  {
	// Geodesic passes through the pole (antipodal)
	double s1,s2;
	geo_inverse_wgs_84( lat1,lon1, lat1,lon2, az1,az2, &s1 );
	geo_inverse_wgs_84( lat2,lon2, lat1,lon2, az1,az2, &s2 );
	*az2 = *az1;
	*s = s1 + s2;
    printf("geo_inverse_wgs_84 ret #4\n");
	return 0;
  }
  else {
	// antipodal and polar points don't get here
	double dlam = lam2 - lam1, dlams = dlam;
  	double sdlams,cdlams, sig,sinsig,cossig, sinaz,
	  cos2saz, c2sigm;
	double tc,temp, us,rnumer,denom, ta,tb;
	double cosu1,sinu1, sinu2,cosu2;

 	// Reduced latitudes
	temp = (1.0-f)*sinphi1/cosphi1;
	cosu1 = 1.0/sqrt(1.0+temp*temp);
	sinu1 = temp*cosu1;
	temp = (1.0-f)*sinphi2/cosphi2;
	cosu2 = 1.0/sqrt(1.0+temp*temp);
	sinu2 = temp*cosu2;
  	do {
	  sdlams = sin(dlams), cdlams = cos(dlams);
	  sinsig = sqrt(cosu2*cosu2*sdlams*sdlams+
			  (cosu1*sinu2-sinu1*cosu2*cdlams)*
			  (cosu1*sinu2-sinu1*cosu2*cdlams));
	  cossig = sinu1*sinu2+cosu1*cosu2*cdlams;

	  sig = atan2(sinsig,cossig);
	  sinaz = cosu1*cosu2*sdlams/sinsig;
	  cos2saz = 1.0-sinaz*sinaz;
	  c2sigm = (sinu1 == 0.0 || sinu2 == 0.0 ? cossig :
	    cossig-2.0*sinu1*sinu2/cos2saz);
	  tc = f*cos2saz*(4.0+f*(4.0-3.0*cos2saz))/16.0;
	  temp = dlams;
	  dlams = dlam+(1.0-tc)*f*sinaz*
		(sig+tc*sinsig*
		 (c2sigm+tc*cossig*(-1.0+2.0*c2sigm*c2sigm)));
	  if (fabs(dlams) > pi() && iter++ > 50) {
        printf("geo_inverse_wgs_84 ret #5\n");
		return iter;
	  }
    } while ( fabs(temp-dlams) > testv);
    us = cos2saz*(a*a-b*b)/(b*b); // !!
	// BACK AZIMUTH FROM NORTH
	rnumer = -(cosu1*sdlams);
	denom = sinu1*cosu2-cosu1*sinu2*cdlams;
	*az2 = rad2deg(atan2(rnumer,denom));
	if( fabs(*az2) < testv ) *az2 = 0.0;
	if(*az2 < 0.0) *az2 += 360.0;

	  // FORWARD AZIMUTH FROM NORTH
	rnumer = cosu2*sdlams;
	denom = cosu1*sinu2-sinu1*cosu2*cdlams;
	*az1 = rad2deg(atan2(rnumer,denom));
	if( fabs(*az1) < testv ) *az1 = 0.0;
	if(*az1 < 0.0) *az1 += 360.0;

	  // Terms a & b
	ta = 1.0+us*(4096.0+us*(-768.0+us*(320.0-175.0*us)))/
	    16384.0;
	tb = us*(256.0+us*(-128.0+us*(74.0-47.0*us)))/1024.0;

	  // GEODETIC DISTANCE
	*s = b*ta*(sig-tb*sinsig*
		   (c2sigm+tb*(cossig*(-1.0+2.0*c2sigm*c2sigm)-tb*
			       c2sigm*(-3.0+4.0*sinsig*sinsig)*
			       (-3.0+4.0*c2sigm*c2sigm)/6.0)/
		    4.0));
	printf("geo_inverse_wgs_84 ret #6\n");
    return 0;
  }
}
**/
// from early OpenEagle work on .ac file building
// hmm meaning of notation dlatc dlongc dlatp dlongp?
// dlatc dlongc are center coordinates of a tile
// return r...distance between lat/long pair in meters?
double ac_from_wgs_84(double dlatc, double dlongc, double dlatp, double dlongp,double *ac_x, double *ac_y)
{
  double start_az = 0.0;
  double az2 = 0.0 ;
  double r = 0.0;
  bool nanbug = false;
  if (std::isnan(dlatc)!=0) {
        printf("dlatc is nan\n");
        nanbug = true;
  }
   if (std::isnan(dlongc)!=0) {
        printf("dlongc is nan\n");
        nanbug = true;
  }
  if (std::isnan(dlatp)!=0) {
        printf("dlatc is nan\n");
        nanbug = true;
  }
   if (std::isnan(dlongp)!=0) {
        printf("dlongc is nan\n");
        nanbug = true;
  }
  if (nanbug) {
    exit(1);
  }
  geo_inverse_wgs_84(dlatc, dlongc, dlatp,dlongp, &start_az, &az2,&r);

  if (std::isnan(r)!=0) {
    printf("r is nan\n");
    nanbug = true;
  }
//  if (nanbug) {
//    exit(1);
//  }

  start_az+=180.0; //get ac to flightgear bearings aligned
  *ac_x = r * cos(start_az*SGD_DEGREES_TO_RADIANS);
  *ac_y = r * sin(start_az*SGD_DEGREES_TO_RADIANS);
  //  printf("ac_from_wgs_84(   ) start_az %f az2 %f r %f ac_x %f ac_y %f \n",start_az,az2, r,ac_x, ac_y);
  return r;
}

double angle_to_360_to_720(double angle)
{
  while (angle > 720.0) angle -= 360.0;
  while (angle <360.0) angle +=360.0;
  return angle;
}
