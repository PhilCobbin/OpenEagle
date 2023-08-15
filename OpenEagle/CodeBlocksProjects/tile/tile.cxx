/***************************************************************
 * Name:      tile.cxx
 * Purpose:   Derived from simgear::Cherry picked versions of FlightGear tiling routines for use in generating 3d Models of Airspace boundaries and inserting them into the FlightGear Scenery Database
 * Created:   2021-04-11
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
#include "tile.hxx"
#include "../3rdparty/constants.h"
#include "../3rdparty/math/SGMisc.hxx"
// default constructor
tile::tile() :
    lon(-1000),
    lat(-1000),
    x(0),
    y(0)
{
}

bool tile::isValid() const
{
    // The most northerly valid latitude is 89, not 90. There is no tile
    // whose *bottom* latitude is 90. Similar there is no tile whose left egde
    // is 180 longitude.
    return (lon >= -180) &&
            (lon < 180) &&
            (lat >= -90) &&
            (lat < 90) &&
            (x < 8) && (y < 8);
}

void tile::make_bad()
{
    lon = -1000;
    lat = -1000;
}

double normalizePeriodic(const double& min, const double& max, const double& value)
{


  double range = max - min;
    if (range < SGLimits <double>::min())
      return min;
    double normalized = value - range*floor((value - min)/range);
    // two security checks that can only happen due to roundoff
    if (normalized <= min)
      return min;
    if (max <= normalized)
      return min;
    return normalized;
}

static double min(const double& a, const double& b)
  { return a < b ? a : b; }

  static double max(const double& a, const double& b)
  { return a > b ? a : b; }
  double clip(const double& a, const double& _min, const double& _max)
  { return max(_min, min(_max, a)); }

    static int      floorWithEpsilon( double x )
    {
    return static_cast<int>(floor(x + SG_EPSILON));
}


// Set the bucket params for the specified lat and lon
void tile::innerSet( double dlon, double dlat )
{
    if ((dlon < -180.0) || (dlon >= 180.0)) {
   //     SG_LOG(SG_TERRAIN, SG_WARN, "SGBucket::set_bucket: passed longitude:" << dlon);
    //    dlon = SGMiscd::normalizePeriodic(-180.0, 180.0, dlon);
        dlon = normalizePeriodic(-180.0, 180.0, dlon);
    }

    if ((dlat < -90.0) || (dlat > 90.0)) {
  //      SG_LOG(SG_TERRAIN, SG_WARN, "SGBucket::set_bucket: passed latitude" << dlat);
    //    dlat = SGMiscd::clip(dlat, -90.0, 90.0);
        dlat = clip(dlat, -90.0, 90.0);

    }

    //
    // longitude first
    //
    double span = sg_bucket_span( dlat );
    // we do NOT need to special case lon=180 here, since
    // normalizePeriodic will never return 180; it will
    // return -180, which is what we want.
    lon = floorWithEpsilon(dlon);

    // find subdivision or super lon if needed
    if ( span <= 1.0 ) {
        /* We have more than one tile per degree of
         * longitude, so we need an x offset.
         */
        x = floorWithEpsilon((dlon - lon) / span);
    } else {
        /* We have one or more degrees per tile,
         * so we need to find the base longitude
         * of that tile.
         *
         * First we calculate the integral base longitude
         * (e.g. -85.5 => -86) and then find the greatest
         * multiple of span that is less than or equal to
         * that longitude.
         *
         * That way, the Greenwich Meridian is always
         * a tile border.
         */
        lon=static_cast<int>(floor(lon / span) * span);
        x = 0;
    }

    //
    // then latitude
    //
    lat = floorWithEpsilon(dlat);

    // special case when passing in the north pole point (possibly due to
    // clipping latitude above). Ensures we generate a valid bucket in this
    // scenario
    if (lat == 90) {
        lat = 89;
        y = 7;
    } else {
        /* Latitude base and offset are easier, as
         * tiles always are 1/8 degree of latitude wide.
         */
        y = floorWithEpsilon((dlat - lat) * 8);
    }
}

void tile::set_tile(double dlon, double dlat)
{
    innerSet(dlon, dlat);
}


// constructor for specified location
tile::tile(const double dlon, const double dlat) {
    set_tile(dlon, dlat);
}

std::string tile::gen_index_str() const
{
	char tmp[20];
	::snprintf(tmp, 20, "%ld",
                 (((long)lon + 180) << 14) + ((lat + 90) << 6)
                 + (y << 3) + x);
	return (std::string)tmp;
}

// Build the path name for this bucket
std::string tile::gen_base_path() const {
    // long int index;
    int top_lon, top_lat, main_lon, main_lat;
    char hem, pole;
    char raw_path[256];

    top_lon = lon / 10;
    main_lon = lon;
    if ( (lon < 0) && (top_lon * 10 != lon) ) {
	top_lon -= 1;
    }
    top_lon *= 10;
    if ( top_lon >= 0 ) {
	hem = 'e';
    } else {
	hem = 'w';
	top_lon *= -1;
    }
    if ( main_lon < 0 ) {
	main_lon *= -1;
    }

    top_lat = lat / 10;
    main_lat = lat;
    if ( (lat < 0) && (top_lat * 10 != lat) ) {
	top_lat -= 1;
    }
    top_lat *= 10;
    if ( top_lat >= 0 ) {
	pole = 'n';
    } else {
	pole = 's';
	top_lat *= -1;
    }
    if ( main_lat < 0 ) {
	main_lat *= -1;
    }

    ::snprintf(raw_path, 256, "%c%03d%c%02d/%c%03d%c%02d",
	    hem, top_lon, pole, top_lat,
	    hem, main_lon, pole, main_lat);

    return raw_path;
}


double tile::get_highest_lat() const
{
    unsigned char adjustedY = y;
    if (lat >= 0) {
        // tile is north of the equator, so we want the top edge. Add one
        // to y to achieve this.
        ++adjustedY;
    }

	return lat + (adjustedY / 8.0);
}

// return width of the tile in degrees
double tile::get_width() const {
    return sg_bucket_span( get_center_lat() );
}


// return height of the tile in degrees
double tile::get_height() const {
    return SG_BUCKET_SPAN;
}

// return width of the tile in meters. This function is used by the
// tile-manager to estimate how many tiles are in the view distance, so
// we care about the smallest width, which occurs at the highest latitude.
double tile::get_width_m() const
{
    double clat_rad = get_highest_lat() * SGD_DEGREES_TO_RADIANS;
    double cos_lat = cos( clat_rad );
    if (fabs(cos_lat) < SG_EPSILON) {
        // happens for polar tiles, since we pass in a latitude of 90
        // return an arbitrary small value so all tiles are loaded
        return 10.0;
    }

    double local_radius = cos_lat * SG_EQUATORIAL_RADIUS_M;
    double local_perimeter = local_radius * SGD_2PI;
    double degree_width = local_perimeter / 360.0;

    return get_width() * degree_width;
}


// return height of the tile in meters
double tile::get_height_m() const {
    double perimeter = SG_EQUATORIAL_RADIUS_M * SGD_2PI;
    double degree_height = perimeter / 360.0;

    return SG_BUCKET_SPAN * degree_height;
}







