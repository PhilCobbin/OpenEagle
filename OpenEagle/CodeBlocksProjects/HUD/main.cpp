/***************************************************************
 * Name:      main.cpp (HUD)
 * Purpose:   HUD modeling.
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
#include <iostream>
#include "../instruments/instruments.hxx"
using namespace std;

int main()
{
  std::string numbers_path = "numbers/";
  std::string command = "mkdir -p ";
  command += numbers_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make numbers directory [%s]\n",command.c_str());
    exit(1);
  }
  std::string scale_path = "scale/";
  command = "mkdir -p ";
  command += scale_path.c_str();
  command += "\n";
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make scale directory [%s]\n",command.c_str());
    exit(1);
  }
  std::string reticle_path = "reticle/";
  command = "mkdir -p ";
  command += reticle_path.c_str();
  command += "\n";
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make scale directory [%s]\n",command.c_str());
    exit(1);
  }
  instruments ins;
  ins.sys_string = "";
  ins.font              = "AvantGarde-Demi";
  ins.pointsize            = 24;
  ins.heading_flag         = true;
  ins.generate_horizontal_scale_texture(
        (char *)"heading-true",   /// char * name,
        (char *)"cyan",           /// char * _color,
        900,                      /// double width,
        64,                       /// double height,
        TOP,                      /// int centering,
        60,                       /// int span,
        8,                        /// int oneOffset,
        16,                       /// int fiveOffset,
        32                        /// int tenOffset
                                        );
  ins.generate_horizontal_scale_numbers(
        (char *)"heading-true",
        (char *)"cyan",
        900,
        64,
        TOP,
        0,
        350,
        10,
        0,
        10,
        -10
           );
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
 /**
  ins.generate_caption(
        (char *)"heading-true"      ,
        (char *)"cyan",
        (char *)"True (deg)"   ,
        128,
        64,
        0,
        -8,
        CENTER
        );
        **/
  ins.heading_flag         = false;
  ins.pointsize            = 48;

  ins.heading_flag           = true;
  ins.bug_flag               = true;
  ins.bug_nasal_str_switch   = "/OpenEagle/autopilot/move_true_reticle";
  ins.bug_nasal_str_distance = "/OpenEagle/autopilot/move_true_reticle_deg";

  ins.generate_ac_file_n_textures_w_xml(
        NO_ROTATE,                            /// bool rotate_flag,
        (char *)"heading-true"   ,            /// char * name,
        15.0,                                 /// double width,
        1.0,                                  /// double height,
        36,                                   /// int n,
        0,                                    /// int n0,
        10,                                   /// int delta_n,
        (char *)"/orientation/heading-deg",   /// char * property,
        0.016666 ,                            /// double factor,
        1.0,                                  /// double nfactor,
        28  ,                                 /// int range,
        1,                                    /// int x,
        0,                                    /// int y,
        0                                     /// int z
        );

  ins.heading_flag           = false;
  ins.bug_flag               = false;
  ins.bug_nasal_str_switch   = "";
  ins.bug_nasal_str_distance = "";

  ins.generate_ac_file_n_textures_w_xml(
        NO_ROTATE,                                /// bool rotate_flag,
        (char *)"airspeed"   ,                    /// char * name,
 //       -1.75,                                    /// double cxl,
 //       8.0,                                      /// double cyl,
 //       1.75,                                     /// double cxh,
 //       8.75,                                     /// double cyh,
        1.25,                                     /// double width,
        8.0,                                      /// double height,
        21,                                       /// int n,
        0,                                        /// int n0,
        10,                                       /// int delta_n,
        (char *)"/velocities/airspeed-kt",        /// char * property,
        0.02       ,                              /// double factor,
        1.0,                                      /// double nfactor,
        22,                                       /// int range,
        0,                                        /// int x,
        1,                                        /// int y,
        0                                         /// int z
        );

  ins.heading_flag           = false;
  ins.bug_flag               = false;
  ins.bug_nasal_str_switch   = "";
  ins.bug_nasal_str_distance = "";

/**

  ins.print_header(512.0,512.0);
  ins.print_color((char *)"black");
  ins.draw_arc(256.0,256.0,190.0,190.0,180.0, 360.0);
  ins.draw_arc(256.0,256.0,189.0,189.0,180.0, 360.0);
  ins.draw_arc(256.0,256.0,188.0,188.0,180.0, 360.0);

  ins.draw_arc(256.0,256.0,190.0,190.0,360.0, 450.0);
  ins.draw_arc(256.0,256.0,189.0,189.0,360.0, 450.0);
  ins.draw_arc(256.0,256.0,188.0,188.0,360.0, 450.0);

  ins.draw_arc(256.0,256.0,170.0,170.0,180.0, 360.0);
  ins.draw_arc(256.0,256.0,169.0,169.0,180.0, 360.0);
  ins.draw_arc(256.0,256.0,168.0,168.0,180.0, 360.0);

  ins.draw_arc(256.0,256.0,170.0,170.0,360.0, 450.0);
  ins.draw_arc(256.0,256.0,169.0,169.0,360.0, 450.0);
  ins.draw_arc(256.0,256.0,168.0,168.0,360.0, 450.0);
  ins.end_file((char *)"draw_arc_test");

  command = ins.sys_string.c_str();
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make draw_arc_test [%s]\n",command.c_str());
    exit(1);
  }
**/
  ins.pointsize            = 60;
  ins.roll_indicator((char *)"roll",  /// char * roll_ind_fn,
                     1024.0,  /// double img_size,
                      440.0,  /// double radius,
                        2.0,  /// double single_width,
                        6.0,  /// double single_height,
                        2.0,  /// double fives_width,
                       12.0,  /// double fives_height,
                        2.0,  /// double tens_width,
                       18.0); ///     double tens_height);

  ins.pointsize            = 48;

//  exit(1);
/**
  ins.print_header(512.0,512.0);
  ins.print_color((char *)"black");
  ins.draw_circle(255.0,255.0,511.0,255.0);

  ins.end_file((char *)"draw_arc_test2");
  command = ins.sys_string.c_str();
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make draw_arc_test [%s]\n",command.c_str());
    exit(1);
  }

**/
  printf("fini\n");
  exit(1);
  ins.generate_digits((char *)"cyan");
/**
  ins.generate_ac_file_n_digits_w_xml(
        (char *)"groundspeed",                        /// char * name,
        DECIMAL_NULL,                                 /// int decimal_pos
        3,                                            /// int n_digits,
        -1.5,                                         /// double cxl,
        0.125,                                        /// double cyl,
        1.5,                                          /// double cxh,
        0.75,                                         /// double cyh,
        0.0,                                          /// double centerdx
        -0.1875,                                      /// double centerdy
        0.5,                                          /// double widthdx,
        0.75,                                         /// double widthdy,
        (char *)"/velocities/groundspeed-kt"          /// char * property
        );
**/
/**
  ins.generate_ac_file_w_n_digits_w_xml(
        (char *)"tas",                                /// char * name,
        DECIMAL_NULL,                                 /// int decimal_pos
        3,                                            /// int n_digits,
        -1.5,                                         /// double cxl,
        0.125,                                        /// double cyl,
        1.5,                                          /// double cxh,
        0.75,                                         /// double cyh,
        0.0,                                          /// double centerdx
        -0.1875,                                      /// double centerdy
        0.5,                                          /// double widthdx,
        0.75,                                         /// double widthdy,
        (char *)"/OpenEagle/airspeed/true-airspeed"   /// char * property
                                                      );
**/

/**
  ins.generate_ac_file_w_n_digits_w_xml(
       (char *)"density-altitude",                     /// char * name,
       DECIMAL_NULL,                                   /// int decimal_pos,
       5,                                              /// int n_digits,
       -2.25,                                          /// double cxl,
       0.0,                                            /// double cyl,
       2.25,                                           /// double cxh,
       1.375,                                          /// double cyh,
       0.0,                                            /// double centerdx,
       -0.1875,                                        /// double centerdy,
       0.375,                                          /// double widthdx,
       0.625,                                          /// double widthdy,
       (char *)"/OpenEagle/altitude/density-altitude"
                                                       );
**/







  ins.generate_vertical_scale_texture(
        (char *)"pitch"      ,        /// char * name,
        (char *)"cyan",               /// char * _color,
        128,                          /// double width,
        450,                          /// double height,
        CENTER,                       /// int centering,
        30,                           /// int span,
        5,                            /// int oneOffset,
        10,                           /// int fiveOffset
        20                            /// int tenOffset
                                      );
  ins.generate_vertical_scale_texture(
        (char *)"airspeed"   ,        /// char * name,
        (char *)"cyan",               /// char * _color,
        64,                           /// double width,
        450,                          /// double height,
        LEFT ,                       /// int centering,
        50,                           /// int span,
        5,                            /// int oneOffset,
        10,                           /// int fiveOffset
        15                            /// int tenOffset
                                      );
    ins.bug_flag               = true;
    ins.bug_orientation        = BUG_LEFT;
    ins.bug_nasal_str_switch   = "/OpenEagle/autopilot/move_reticle_alt";
    ins.bug_nasal_str_distance = "/OpenEagle/autopilot/move_reticle_alt_ft";
  ins.generate_vertical_scale_texture(
        (char *)"altitude"   ,        /// char * name,
        (char *)"cyan",               /// char * _color,
        96,                           /// double width,
        450,                          /// double height,
        RIGHT  ,                      /// int centering,
        30,                           /// int span,
        8,                            /// int oneOffset,
        16,                           /// int fiveOffset
        24                            /// int tenOffset
                                      );
    ins.bug_flag               = false;
    ins.bug_nasal_str_switch   = "";
    ins.bug_nasal_str_distance = "";
  ins.generate_vertical_scale_texture(
        (char *)"AGL"        ,        /// char * name,
        (char *)"cyan",               /// char * _color,
        96,                           /// double width,
        450,                          /// double height,
        RIGHT  ,                      /// int centering,
        30,                           /// int span,
        8,                            /// int oneOffset,
        16,                           /// int fiveOffset
        24                            /// int tenOffset
                                      );
  ins.generate_vertical_scale_texture(
        (char *)"VSI"        ,        /// char * name,
        (char *)"cyan",               /// char * _color
        96,                           /// double width,
        450,                          /// double height
        LEFT  ,                      /// int centering
        30,                           /// int span,
        8,                            /// int oneOffset
        16,                           /// int fiveOffse
        24                            /// int tenOffset
                                      );

                                      /// engine instruments removed in favor of xml guages using RGraph


  ins.generate_vertical_scale_numbers(
        (char *)"pitch"      ,        /// char * name,
        (char *)"cyan",               /// char * _color
        256,                          /// double width,
        900,                          /// double height
        CENTER,                       /// int centering
        -90,                          /// int nl,
        90,                           /// int nh,
        10,                           /// int delta_n,
        85,                           /// int x_offset,
        10                            /// int y_offset
                                      );

  ins.generate_vertical_scale_numbers(
        (char *)"airspeed"   ,        /// char * name,
        (char *)"cyan",               /// char * _color
        128,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        0,                            /// int nl,
        300,                          /// int nh,
        10,                           /// int delta_n,
        30,                            /// int x_offset,
        10                            /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"altitude"   ,        /// char * name,
        (char *)"cyan",               /// char * _color
        192,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        0,                            /// int nl,
        15000,                        /// int nh,
        500,                          /// int delta_n,
        2,                            /// int x_offset,
        10                            /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"AGL"        ,        /// char * name,
        (char *)"cyan",               /// char * _color
        192,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        0,                            /// int nl,
        15000,                        /// int nh,
        500,                          /// int delta_n,
        2,                            /// int x_offset,
        10                            /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"VSI"        ,        /// char * name,
        (char *)"cyan",               /// char * _color
        192,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        -3500,                        /// int nl,
        3500,                         /// int nh,
        500,                          /// int delta_n,
        60,                            /// int x_offset,
        10                            /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"fuelpsi"    ,        /// char * name,
        (char *)"cyan",               /// char * _color
        128,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        0,                            /// int nl,
        50,                           /// int nh,
        10,                           /// int delta_n,
        2,                            /// int x_offset,
        10                            /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"oilpsi"     ,        /// char * name,
         (char *)"cyan",              /// char * _color
         128,                         /// double width,
         900,                         /// double height
         LEFT,                        /// int centering
         0,                           /// int nl,
         100,                         /// int nh,
         10,                          /// int delta_n,
         2,                           /// int x_offset,
         10                           /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"oilF"       ,        /// char * name,
         (char *)"cyan",              /// char * _color
         128,                         /// double width,
         900,                         /// double height
         LEFT,                        /// int centering
         0,                           /// int nl,
         250,                         /// int nh,
         50,                          /// int delta_n,
         2,                           /// int x_offset,
         10                           /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"CHT"        ,        /// char * name,
        (char *)"cyan",               /// char * _color
        128,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        0,                            /// int nl,
        400,                          /// int nh,
        100,                          /// int delta_n,
        2,                            /// int x_offset,
        10                            /// int y_offset
                                      );
  ins.generate_vertical_scale_numbers(
        (char *)"EGT"        ,        /// char * name,
        (char *)"cyan",               /// char * _color
        128,                          /// double width,
        900,                          /// double height
        LEFT,                         /// int centering
        0,                            /// int nl,
        1500,                         /// int nh,
        100,                          /// int delta_n,
        2,                            /// int x_offset,
        10                            /// int y_offset
                                      );
/**
  ins.generate_caption(
        (char *)"airspeed"      ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"AS (kt)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"density-altitude",   /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"DA (ft)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"groundspeed"   ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"GS (kt)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );

  ins.generate_caption(
        (char *)"airspeed"      ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"AS (kt)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );

  ins.generate_caption(
        (char *)"tas"      ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"TAS (kt)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );

  ins.generate_caption(
        (char *)"altitude"      ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"MSL (ft)"  ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"AGL"           ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"AGL (ft)"   ,        /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"VSI"           ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"VSI (fpm)" ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"fuelpsi"       ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"FP (psi)"  ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"oilpsi"        ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"Oil (psi)" ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"oilF"          ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"Oil (F)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"CHT"           ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"CHT (F)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"EGT"           ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"EGT (F)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"RPM"           ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"RPM"   ,             /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"MP"            ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"MP (InHg)"   ,       /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"FF"            ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"FF (gph)"   ,        /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"OAT"           ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"OAT (F)"   ,         /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
  ins.generate_caption(
        (char *)"ALT-setting"   ,     /// char * name,
        (char *)"cyan",               /// char * _color,
        (char *)"Alt (inhg)"   ,      /// char * caption,
        256,                          /// double width,
        128,                          /// double height,
        0,                            /// int x_offset,
        -16,                          /// int y_offset,
        CENTER                        /// int centering
                                      );
**/


  ins.generate_ac_file_n_textures_w_xml(
        ROTATE,                            /// bool rotate_flag,
        (char *)"pitch"      ,             /// char * name,
        2.5,                               /// double width,
        8.5,                               /// double height,
        19,                                /// int n,
        -90,                               /// int n0,
        10,                                /// int delta_n,
        (char *)"/orientation/pitch-deg",   /// char * property,
        0.033333334,                       /// double factor,
        1.0,                               /// double nfactor,
        14,                                /// int range,
        0,                                 /// int x,
        1,                                 /// int y,
        0                                  /// int z
                                        );
/**

  ins.generate_ac_file_w_n_textures_w_xml(
        NO_ROTATE,                                /// bool rotate_flag,
        (char *)"airspeed"   ,                    /// char * name,
        -1.75,                                    /// double cxl,
        8.0,                                      /// double cyl,
        1.75,                                     /// double cxh,
        8.75,                                     /// double cyh,
        1.25,                                     /// double width,
        8.0,                                      /// double height,
        21,                                       /// int n,
        0,                                        /// int n0,
        10,                                       /// int delta_n,
        (char *)"/velocities/airspeed-kt",        /// char * property,
        0.02       ,                              /// double factor,
        1.0,                                      /// double nfactor,
        22,                                       /// int range,
        0,                                        /// int x,
        1,                                        /// int y,
        0                                         /// int z
        );
        **/
    ins.bug_flag               = true;
    ins.bug_orientation        = BUG_LEFT;
    ins.bug_nasal_str_switch   = "/OpenEagle/autopilot/move_reticle_alt";
    ins.bug_nasal_str_distance = "/OpenEagle/autopilot/move_reticle_alt_ft";

  ins.generate_ac_file_n_textures_w_xml(
        NO_ROTATE,                                /// bool rotate_flag,
        (char *)"altitude"   ,                    /// char * name,
     //   -1.75,                                    /// double cxl,
     //   8.0,                                      /// double cyl,
     //   1.75,                                     /// double cxh,
     //   8.75,                                     /// double cyh,
        1.7,                                      /// double width,
        8.0,                                      /// double height,
        30,                                       /// int n,
        0,                                        /// int n0,
        500,                                      /// int delta_n,
        (char *)"/position/altitude-ft",          /// char * property,
        0.000333334,                              /// double factor,
        1.0,                                      /// double nfactor,
        1400,                                     /// int range,
        0,                                        /// int x,
        1,                                        /// int y,
        0                                         /// int z
        );

    ins.bug_flag               = false;
    ins.bug_nasal_str_switch   = "";
    ins.bug_nasal_str_distance = "";

  ins.generate_ac_file_n_textures_w_xml(
        NO_ROTATE,                                /// bool rotate_flag,
        (char *)"AGL"        ,                    /// char * name,
 ///       -1.75,                                    /// double cxl,
 ///       8.0,                                      /// double cyl,
 ///       1.75,                                     /// double cxh,
 ///       8.75,                                     /// double cyh,
        1.7,                                      /// double width,
        8.0,                                      /// double height,
        30,                                       /// int n,
        0,                                        /// int n0,
        500,                                      /// int delta_n,
        (char *)"/position/altitude-agl-ft",      /// char * property,
        0.000333334,                              /// double factor,
        1.0,                                      /// double nfactor,
        1400,                                     /// int range,
        0,                                        /// int x,
        1,                                        /// int y,
        0                                         /// int z
        );


  ins.generate_ac_file_n_textures_w_xml(
        NO_ROTATE,                                /// bool rotate_flag,
        (char *)"VSI"        ,                    /// char * name,
 ///       -1.75,                                    /// double cxl,
 ///       8.0,                                      /// double cyl,
 ///       1.75,                                     /// double cxh,
 ///       8.75,                                     /// double cyh,
        1.7,                                      /// double width,
        8.0,                                      /// double height,
        15,                                       /// int n,
        -3500,                                    /// int n0,
        500,                                      /// int delta_n,
        (char *)"/OpenEagle/vsi-fpm",             /// char * property,
        0.000333334,                              /// double factor,
        1.0,                                      /// double nfactor,
        1400,                                     /// int range,
        0,                                        /// int x,
        1,                                        /// int y,
        0                                         /// int z
        );
/**
  ins.generate_ac_file_w_n_textures_w_xml(
        NO_ROTATE,                                     /// bool rotate_flag,
        (char *)"fuelpsi"    ,                         /// char * name,
        -1.75,                                         /// double cxl,
        8.0,                                           /// double cyl,
        1.75,                                          /// double cxh,
        8.75,                                          /// double cyh,
        1.25,                                          /// double width,
        8.0,                                           /// double height,
        6,                                             /// int n,
        0,                                             /// int n0,
        10,                                            /// int delta_n,
        (char *)"/OpenEagle/engine/fuel-pressure-psi", /// char * property,
        0.02       ,                                   /// double factor,
        1.0,                                           /// double nfactor,
        24,                                            /// int range,
        0,                                             /// int x,
        1,                                             /// int y,
        0                                              /// int z
        );
  ins.generate_ac_file_w_n_textures_w_xml(
        NO_ROTATE,                                    /// bool rotate_flag,
        (char *)"oilpsi"     ,                        /// char * name,
        -1.75,                                        /// double cxl,
        8.0,                                          /// double cyl,
        1.75,                                         /// double cxh,
        8.75,                                         /// double cyh,
        1.0 ,                                         /// double width,
        8.0,                                          /// double height,
        11,                                           /// int n,
        0,                                            /// int n0,
        10,                                           /// int delta_n,
        (char *)"/OpenEagle/engine/oil-pressure-psi", /// char * property,
        0.01       ,                                  /// double factor,
        1.0,                                          /// double nfactor,
        44,                                           /// int range,
        0,                                            /// int x,
        1,                                            /// int y,
        0                                             /// int z
         );
  ins.generate_ac_file_w_n_textures_w_xml(
        NO_ROTATE,                                        /// bool rotate_flag,
        (char *)"oilF"       ,                            /// char * name,
        -1.75,                                            /// double cxl,
        8.0,                                              /// double cyl,
        1.75,                                             /// double cxh,
        8.75,                                             /// double cyh,
        1.25,                                             /// double width,
        8.0,                                              /// double height,
        6,                                                /// int n,
        0,                                                /// int n0,
        50,                                               /// int delta_n,
        (char *)"/OpenEagle/engine/oil-temperature-degf", /// char * property,
        0.004      ,                                      /// double factor,
        1.0,                                              /// double nfactor,
        140,                                              /// int range,
        0,                                                /// int x,
        1,                                                /// int y,
        0                                                 /// int z
        );
  ins.generate_ac_file_w_n_textures_w_xml(
        NO_ROTATE,                                /// bool rotate_flag,
        (char *)"CHT"        ,                    /// char * name,
        -1.75,                                    /// double cxl,
        8.0,                                      /// double cyl,
        1.75,                                     /// double cxh,
        8.75,                                     /// double cyh,
        1.25,                                     /// double width,
        8.0,                                      /// double height,
        5,                                        /// int n,
        0,                                        /// int n0,
        100,                                      /// int delta_n,
        (char *)"/OpenEagle/engine/cht0-degf",    /// char * property,
        0.002      ,                              /// double factor,
        1.0,                                      /// double nfactor,
        140,                                      /// int range,
        0,                                        /// int x,
        1,                                        /// int y,
        0                                         /// int z
       );
**/
  ins.pointsize            = 48;

  return 0;
}

