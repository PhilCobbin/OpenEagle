/***************************************************************
 * Name:      instruments.hxx
 * Purpose:   HUD modeling tools to auto generate .ac, .xml and .png files for a HUD with specified fonts and point size(s), and colors
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2021-04-11
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

#ifndef INSTRUMENTS_H
#define INSTRUMENTS_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <sstream>

#include <stdio.h>
#include "../system_io/system_io.hxx"
#include "../avl_tree/avl_tree.hxx"
#include "../3rdparty/constants.h"
using namespace std;

class instruments
{
  public:
#define INCH_TO_METER    0.02523333333333
#define		r2d	57.2958
#define		d2r     0.01745

    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
///    string caption1;
///    string caption2;
///    string caption3;
///    string caption4;

    double width;
    double height;
    string font;  //              = "AvantGarde-Demi";
    int pointsize; //            = 36;
    string color;//             = "white";

    double text_radius;   //    = 170.0;
    double start_degree;//      = 130.0;
    int start_number;    //     =0;
    int n_numbers;         //   = 11;
    double delta_deg;        // =28.0;
    int delta_number;       //  =1;

    double line_radius_base;//  = 110.0;
    double line_height;     //  = 35.0;
    double line_hwidth;     //  = 3.0;


    FILE * fp;
    string sys_string;
    string fn;
    string fn_n;
    string fn_n_txt;

    double x;

    double x_0;
    double y_0;
    double x_1;
    double y_1;
    double x_2;
    double y_2;
    double x_3;
    double y_3;

    char buffer[100];
    char * string_i(int i);
    char * string_i_signed(int i);
    char * string_d(double d);
#define LEFT -1
#define CENTER 0
#define RIGHT 1
#define TOP 1
#define BOTTOM -1
#define ROTATE true
#define NO_ROTATE false

    bool heading_flag;
    bool bug_flag;
    int bug_orientation;
    #define BUG_CENTER 0
    #define BUG_LEFT -1
    #define BUG_RIGHT 1
    std::string bug_nasal_str_switch;
    std::string bug_nasal_str_distance;

#define DECIMAL_NULL -1
#define DECIMAL_AT1 1   /// ff = 8.6
#define DECIMAL_AT2 2   /// InHg = 29.92

    void generate_round_HUD_bezel(char *name);

    /// non captioned HUD tape(s) (see pitch)

    void generate_ac_file_n_textures(
           char * name,
           double width,
           double height,
           int n,
           int n0,
           int delta_n
          );

    void generate_ac_file_n_textures_w_xml(
           bool rotate_flag,
           char * name,
           double width,
           double height,
           int n,
           int n0,
           int delta_n,
           char * property,
           double factor,
           double nfactor,
           int range,
           int x,
           int y,
           int z
           );

    /// captioned HUD tapes
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
///    void generate_ac_file_w_caption_n_textures(
///           char * name,
///           double cxl,
///           double cyl,
///           double cxh,
///           double cyh,
///           double width,
///           double height,
///           int n,
///           int n0,
///           int delta_n
///           );

    /// generate AC file and associated XML files for HUD tape animation
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
///    void generate_ac_file_w_caption_n_textures_w_xml(
///           bool rotate_flag,
///           char * name,
///           double cxl,
///           double cyl,
///           double cxh,
///           double cyh,
///           double width,
///           double height,
///           int n,
///           int n0,
///           int delta_n,
///           char * property,
///           double factor,
///           double nfactor,
///           int range,
///           int x,
///           int y,
///           int z
///           );

    /// simple digit HUD elements
    void generate_digits(char * _color);

    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
///    void generate_ac_file_w_caption_n_digits(
///           char * name,
///           int decimal_pos,
///           double n_digits,
///           double cxl,
///           double cyl,
///           double cxh,
///           double cyh,
///           double centerdx,
///           double centerdy,
///           double widthdx,
///           double widthdy
///           );
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
///    void generate_ac_file_w_caption_n_digits_w_xml(
///           char * name,
///           int decimal_pos,
///           double n_digits,
///           double cxl,
///           double cyl,
///           double cxh,
///           double cyh,
///           double centerdx,
///           double centerdy,
///           double widthdx,
///           double widthdy,
///           char * property
///           );


    /// HUD Tape SCALE generation
    void generate_horizontal_scale_texture(
           char * name,
           char * _color,
           double width,
           double height,
           int centering,
           int span,
           int oneOffset,
           int fiveOffset,
           int tenOffset
           );
    void generate_vertical_scale_texture(
           char * name,
           char * _color,
           double width,
           double height,
           int centering,
           int span,
           int oneOffset,
           int fiveOffset,
           int tenOffset
           );

    void generate_roll_indicator(
           char * _color,
           double radius
           );

    /// HUD Tape NUMBER generation
    void generate_horizontal_scale_numbers(
           char * name,
           char * _color,
           double width,
           double height,
           int centering,
           int nl,
           int nh,
           int delta_n,
           int x_offset,
           int y_offset0,
           int y_offset1
           );
    void generate_vertical_scale_numbers(
           char * name,
           char * _color,
           double width,
           double height,
           int centering,
           int nl,
           int nh,
           int delta_n,
           int x_offset,
           int y_offset
           );

    /// Caption generation for HUD tapes
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
///    void generate_caption(
///           char * name,
///           char * _color,
///           char * caption,
///           double width,
///           double height,
///           int x_offset,
///           int y_offset,
///           int centering
///           );


    void roll_indicator(char * roll_ind_fn,
                        double img_size,
                        double radius,
                        double single_width,
                        double single_height,
                        double fives_width,
                        double fives_height,
                        double tens_width,
                        double tens_height);

    void draw_arc(              /// experimental code in HUD (translucent condensed steam guages
           double x,
           double y,
           double r0,
           double r1,
           double a0,
           double a1
                  );
    void draw_circle(              /// experimental code in HUD (translucent condensed steam guages
           double cx,
           double cy,
           double px,
           double py);
    void draw_line(double x0,
                   double y0,
                   double x1,
                   double y1);
    void draw_stroke(char * color);
    void draw_strokewidth(int n);
    void draw_fill(char * color);
    void generate_bezel_circle(  /// looks to be dead code to HUD
           double width,
           double height,
           double radius
                               );
///    void print_caption(  /// looks to be dead code to HUD
///           double x,
///           double y,
///           int pointsize,
///           char * c
///            );
    void print_n(       /// used by print_n_scale
           double x0,
           double y0,
           double d,
           double r,
           int n,
           int pointsize
                 );
    void print_n_scale(       /// unused by HUD
           double x0,
           double y0,
           double r,
           double start_d,
           int start_n,
           int nn,
           double dd,
           int dn ,
           int pointsize
                       );
    void rotate_point(  /// used by rotate_points
           double * x,
           double * y,
           double d
                      );

    void rotate_points(double d); /// used by print_bezel_lines
    void set_corners(
           double sr,
           double ll,
           double lo
                     );
    void set_relative_to(  /// used by print_bezel_lines
           double x_orig,
           double y_orig
                         );
    void print_lines(  /// used by print_bezel_lines and print_bezel_lines_linear
           double x0,
           double y0,
           double x1,
           double y1,
           double x2,
           double y2,
           double x3,
           double y3
                     );
    void print_bezel_lines(  /// currently not used in HUD
           double width,
           double height,
           double r_start,
           double length,
           double hwidth,
           double start_d,
           double n_lines,
           double delta_line
                           );
    void print_bezel_lines_linear(  /// currently not used in HUD
           double x0,
           double y0,
           double width,
           double height,
           double dy,
           int n
                                  );
    void print_n_scale_linear(  /// currently not used in HUD
           double x0,
           double y0,
           double dy,
           int n,
           int start_n,
           int dn
                              );
    void print_header_no_font(  /// internal utility
           double width,
           double height
                              );
    void print_header(   ///internal utility
           double width,
           double height
                      );
    void print_color(char *color);  /// internal utility
    void end_file(char * fn);      /// internal utility
    void generate_data_box(       /// internal utility, currently dead code use
           double box_width,
           double box_height,
           double box_thick,
           double box_x,
           double box_y
                           );

    void draw_text(            /// early development version
           char * gravity,
           double x,
           double y,
           char * text
                   );
    void draw_text(           /// early development version
           double x,
           double y,
           char * text
                   );
    /// draw text bordered in black
    void draw_text_w_stroke(  /// used to draw text via ImageMagick console calls
           char * gravity,
           double x,
           double y,
           char * text
                            );
    void draw_text_w_stroke(  /// early development version
           double x,
           double y,
           char * text
                            );
    inline instruments(void)
    {
///      caption1               = "";
///      caption2               = "";
///      caption3               = "";
///      caption4               = "";
      width                  = 512.0;
      height                 = 512.0;
      font                   = "AvantGarde-Demi";
      pointsize              = 36;
      color                  = "white";
      text_radius            = 170.0;
      start_degree           = 130.0;
      start_number           = 0;
      n_numbers              = 11;
      delta_deg              = 28.0;
      delta_number           = 1;
      line_radius_base       = 110.0;
      line_height            = 35.0;
      line_hwidth            = 3.0;
      heading_flag           = false;
      bug_flag               = false;
      bug_nasal_str_switch   = "";
      bug_nasal_str_distance = "";
      bug_orientation        = BUG_CENTER;
    }
};
#endif
