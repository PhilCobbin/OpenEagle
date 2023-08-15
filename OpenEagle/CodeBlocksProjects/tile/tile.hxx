/***************************************************************
 * Name:      tile.cxx
 * Purpose:   Derived from simgear:: Cherry picked versions of FlightGear tiling routines for use in generating 3d Models of Airspace boundaries and inserting them into the FlightGear Scenery Database
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
#ifndef TILE_H
#define TILE_H
#include <stdio.h>
#include <string.h>
#include <string>


#define  NPRECISION 15

/**
 * standard size of a bucket in degrees (1/8 of a degree)
 */
#define SG_BUCKET_SPAN      0.125

/**
 * half of a standard SG_BUCKET_SPAN
 */
#define SG_HALF_BUCKET_SPAN ( 0.5 * SG_BUCKET_SPAN )


// return the horizontal tile span factor based on latitude
static double sg_bucket_span( double l ) {
    if ( l >= 89.0 ) {
	return 12.0;
    } else if ( l >= 86.0 ) {
	return 4.0;
    } else if ( l >= 83.0 ) {
	return 2.0;
    } else if ( l >= 76.0 ) {
	return 1.0;
    } else if ( l >= 62.0 ) {
	return 0.5;
    } else if ( l >= 22.0 ) {
	return 0.25;
    } else if ( l >= -22.0 ) {
	return 0.125;
    } else if ( l >= -62.0 ) {
	return 0.25;
    } else if ( l >= -76.0 ) {
	return 0.5;
    } else if ( l >= -83.0 ) {
	return 1.0;
    } else if ( l >= -86.0 ) {
	return 2.0;
    } else if ( l >= -89.0 ) {
	return 4.0;
    } else {
	return 12.0;
    }
}

class tile {  //hacked from SGBucket

private:
    short lon;        // longitude index (-180 to 179)
    short lat;        // latitude index (-90 to 89)
    unsigned char x;          // x subdivision (0 to 7)
    unsigned char y;          // y subdivision (0 to 7)

    void innerSet( double dlon, double dlat );

public:


    /**
     * Default constructor, creates an invalid tile //SGBucket
     */
    tile();

    /**
     * Check if this bucket refers to a valid tile, or not.
     */
    bool isValid() const;

    /**
     * Create an impossible bucket.
     * This is useful if you are comparing cur_bucket to last_bucket
     * and you want to make sure last_bucket starts out as something
     * impossible.
     */
    void make_bad();

   /**
     * Construct a bucket given a specific location.
     * @param dlon longitude specified in degrees
     * @param dlat latitude specified in degrees
     */
    tile(const double dlon, const double dlat);

    /**
     * Reset a bucket to represent a new lat and lon
     * @param dlon longitude specified in degrees
     * @param dlat latitude specified in degrees
     */
    void set_tile( double dlon, double dlat );


     /**
     * Generate the unique scenery tile index for this bucket
     *
     * The index is constructed as follows:
     *
     * 9 bits - to represent 360 degrees of longitude (-180 to 179)
     * 8 bits - to represent 180 degrees of latitude (-90 to 89)
     *
     * Each 1 degree by 1 degree tile is further broken down into an 8x8
     * grid.  So we also need:
     *
     * 3 bits - to represent x (0 to 7)
     * 3 bits - to represent y (0 to 7)
     * @return tile index
     */
    inline long int gen_index() const {
	return ((lon + 180) << 14) + ((lat + 90) << 6) + (y << 3) + x;
    }

    /**
     * Generate the unique scenery tile index for this bucket in ascii
     * string form.
     * @return tile index in string form
     */
    std::string gen_index_str() const;

    /**
     * Build the base path name for this bucket.
     * @return base path in string form
     */
    std::string gen_base_path() const;

    /**
     * @return the center lon of a tile.
     */
    inline double get_center_lon() const {
	double span = sg_bucket_span( lat + y / 8.0 + SG_HALF_BUCKET_SPAN );

	if ( span >= 1.0 ) {
	    return lon + get_width() / 2.0;
	} else {
	    return lon + x * span + get_width() / 2.0;
	}
    }

    /**
     * @return the center lat of a tile.
     */
    inline double get_center_lat() const {
	return lat + y / 8.0 + SG_HALF_BUCKET_SPAN;
    }

    /**
     * @return the highest (furthest from the equator) latitude of this
     * tile. This is the top edge for tiles north of the equator, and
     * the bottom edge for tiles south
     */
    double get_highest_lat() const;

    /**
     * @return the width of the tile in degrees.
     */
    double get_width() const;

    /**
     * @return the height of the tile in degrees.
     */
    double get_height() const;

    /**
     * @return the width of the tile in meters.
     */
    double get_width_m() const;

    /**
     * @return the height of the tile in meters.
     */
    double get_height_m() const;

};
#endif
