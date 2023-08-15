/***************************************************************
 * Name:      instruments.cxx
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
#include <string.h>
#include <string>
#include "instruments.hxx"
#include <stdio.h>
#include <cstddef>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string>
#include <sstream>
using namespace std;
#define		r2d	57.2958
#define		d2r     0.01745

void instruments::generate_round_HUD_bezel(char *name)
{  // standardized HUD steam guage
  double width = 512.0;
  double height = 512.0;
  print_header(width,height);
  print_color((char *)"black");
  double cx = 256.0;
  double cy = 256.0;
//  double r1 = 170.0;
//  double r2 = 190.0;

  for (int i = 0; i<4; i++) {

  }
  draw_arc(cx,cy,190.0,190.0,180.0, 360.0);
  draw_arc(cx,cy,189.0,189.0,180.0, 360.0);
  draw_arc(cx,cy,188.0,188.0,180.0, 360.0);

  draw_arc(cx,cy,190.0,190.0,360.0, 450.0);
  draw_arc(cx,cy,189.0,189.0,360.0, 450.0);
  draw_arc(cx,cy,188.0,188.0,360.0, 450.0);

  draw_arc(cx,cy,170.0,170.0,180.0, 360.0);
  draw_arc(cx,cy,169.0,169.0,180.0, 360.0);
  draw_arc(cx,cy,168.0,168.0,180.0, 360.0);

  draw_arc(cx,cy,170.0,170.0,360.0, 450.0);
  draw_arc(cx,cy,169.0,169.0,360.0, 450.0);
  draw_arc(cx,cy,168.0,168.0,360.0, 450.0);


  end_file((char *)"draw_arc_test");
  std::string command = sys_string.c_str();
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make geneare_round_HUD_bezel [%s]\n",command.c_str());
    exit(1);
  }

}

void instruments::generate_horizontal_scale_numbers(
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
                    )
{
  std::string numbers_path = "numbers/";
  numbers_path += name;
  numbers_path += "/";
  std::string command = "mkdir -p ";
  command += numbers_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make numbers directory [%s]\n",command.c_str());
    exit(1);
  }
  string sindex;

  if (centering == CENTER) {
    int y = 0;
    int x = x_offset;
    for (int index = nl; index <= nh; index += delta_n) {
      sys_string = "";
      fn = numbers_path.c_str();
      fn += name;
      fn += "_";
      if (nl < 0) fn += string_i_signed(index); else fn+= string_i(index);
      fn_n = fn;
      fn_n_txt=fn_n + ".txt";
      print_header(width,height);
      print_color(_color);
      if (nl < 0) sindex = string_i_signed(index); else sindex = string_i(index);
      draw_text_w_stroke((char *)"Center", x, y + y_offset0, (char *)sindex.c_str());
      draw_text_w_stroke((char *)"Center", x, y + y_offset1, (char *)sindex.c_str());
      end_file((char *)fn_n.c_str());
      printf("output[%s]\n",sys_string.c_str());
      system(sys_string.c_str());
    }
  }
  if (centering == BOTTOM) {
    int y = 0;
    int x = x_offset;
    for (int index = nl; index <= nh; index += delta_n) {
      sys_string = "";
      fn = numbers_path.c_str();
      fn += name;
      fn += "_";
      if (nl <0) fn += string_i_signed(index); else fn += string_i(index);
      fn_n = fn;
      fn_n_txt=fn_n + ".txt";
      print_header(width,height);
      print_color(_color);
      if (nl < 0)  sindex = string_i_signed(index); else sindex = string_i(index);
      draw_text_w_stroke((char *)"Center", x , y + y_offset0, (char *)sindex.c_str());
      end_file((char *)fn_n.c_str());
      printf("output[%s]\n",sys_string.c_str());
      system(sys_string.c_str());
    }
  }
  if (centering == TOP) {
    int y = 0;
    int x = x_offset;
    for (int index = nl; index <= nh; index += delta_n) {
      sys_string = "";
      fn = numbers_path.c_str();
      fn += name;
      fn += "_";
      if (nl <0) fn += string_i_signed(index); else fn += string_i(index);
      fn_n = fn;
      fn_n_txt=fn_n + ".txt";
      print_header(width,height);
      print_color(_color);
      if (nl < 0)  sindex = string_i_signed(index); else sindex = string_i(index);
      draw_text_w_stroke((char *)"Center", x , y - y_offset0, (char *)sindex.c_str());
      end_file((char *)fn_n.c_str());
      printf("output[%s]\n",sys_string.c_str());
      system(sys_string.c_str());
    }
  }
}



void instruments::generate_vertical_scale_numbers(
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
                    )
{
  std::string numbers_path = "numbers/";
  numbers_path += name;
  numbers_path += "/";
  std::string command = "mkdir -p ";
  command += numbers_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make numbers directory [%s]\n",command.c_str());
    exit(1);
  }
  string sindex;
  if (centering == CENTER) {
    int x = 0;
    int y = y_offset;
    for (int index = nl; index <= nh; index += delta_n) {
      sys_string = "";
      fn = numbers_path.c_str();
      fn += name;
      fn += "_";
      if (nl < 0) fn += string_i_signed(index); else fn+= string_i(index);
      fn_n = fn;
      fn_n_txt=fn_n + ".txt";
      print_header(width,height);
      print_color(_color);
      if (nl < 0) sindex = string_i_signed(index); else sindex = string_i(index);
      draw_text_w_stroke((char *)"Center", x - x_offset, y, (char *)sindex.c_str());
      draw_text_w_stroke((char *)"Center", x + x_offset, y, (char *)sindex.c_str());
      end_file((char *)fn_n.c_str());
      printf("output[%s]\n",sys_string.c_str());
      system(sys_string.c_str());
    }
  }
  else {
    if (centering == LEFT) {
      int x = 0;
      int y = y_offset;
      for (int index = nl; index <= nh; index += delta_n) {
        sys_string = "";
        fn = numbers_path.c_str();
        fn += name;
        fn += "_";
        if (nl <0) fn += string_i_signed(index); else fn += string_i(index);
        fn_n = fn;
        fn_n_txt=fn_n + ".txt";
        print_header(width,height);
        print_color(_color);
        if (nl < 0)  sindex = string_i_signed(index); else sindex = string_i(index);
        draw_text_w_stroke((char *)"East", x + x_offset , y, (char *)sindex.c_str());
        end_file((char *)fn_n.c_str());
        printf("output[%s]\n",sys_string.c_str());
        system(sys_string.c_str());
      }
    }
    else {
      if (centering == RIGHT) {
              int x = 0;
      int y = y_offset;
      for (int index = nl; index <= nh; index += delta_n) {
        sys_string = "";
        fn = numbers_path.c_str();
        fn += name;
        fn += "_";
        if (nl <0) fn += string_i_signed(index); else fn += string_i(index);
        fn_n = fn;
        fn_n_txt=fn_n + ".txt";
        print_header(width,height);
        print_color(_color);
        if (nl < 0)  sindex = string_i_signed(index); else sindex = string_i(index);
        draw_text_w_stroke((char *)"West", x + x_offset , y, (char *)sindex.c_str());
        end_file((char *)fn_n.c_str());
        printf("output[%s]\n",sys_string.c_str());
        system(sys_string.c_str());
      }
      }
    }
  }
}

void instruments::generate_horizontal_scale_texture(
                    char * name,
                    char * _color,
                    double width,
                    double height,
                    int centering,
                    int span,
                    int oneOffset,
                    int fiveOffset,
                    int tenOffset
                    )
{

  std::string scale_path = "scale/";
  scale_path += name;
  scale_path += "/";
  std::string command = "mkdir -p ";
  command += scale_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make scale directory [%s]\n",command.c_str());
    exit(1);
  }
  /// (1) generate scale
  color = _color;
  sys_string = "";
  fn = scale_path.c_str();
  //fn += name;
  fn += "scale";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);

//  int dy;
  int dx = width/span;
  int x = 0;
  int offset;
  int y = height;
  if (centering == CENTER) y = height/2;

  int x0;
  int x1;
  int y0;
  int y1;

  for (int index =-(span/2); index <= (span/2); index++)
  {
    if (index == 0) offset = tenOffset;
    else {
      if ( (index % 10) == 0) offset = tenOffset;
      else {
        if ( (index %5) == 0) offset = fiveOffset;
        else offset = oneOffset;
      }
    }
    if (centering == BOTTOM) {
      y0 = 0;
      x0 = x-2;
      y1 = offset;
      x1 = x+1;
    }
    if (centering == TOP) {
      y0 = y-offset;
      x0 = x-2;
      y1 = height;
      x1 = x+1;
    }
    if (centering == CENTER) {
      y0 = y-offset;
      x0 = x-2;
      y1 = y + offset;
      x1 = x+1;

    }
    sys_string += " -stroke black";
    sys_string += " -fill ";
    sys_string += color;
    sys_string += " ";
    sys_string +=" -strokewidth 1 -draw \"rectangle ";
    sys_string += string_i(x0);
    sys_string += ",";
    sys_string += string_i(y0);
    sys_string += " ";
    sys_string += string_i(x1);
    sys_string += ",";
    sys_string += string_i(y1);
    sys_string += "\" \\\n";
    x += dx;
  }
  if (centering != CENTER) {
    if (centering == BOTTOM) {
      y0 = 0;
      x0 = 0;
      y1 = 3;
      x1 = width-1;
    }
    if (centering == TOP) {
      y0 = height-1;
      x0 = 0;
      y1 = height-4;
      x1 = width-1;
    }
    sys_string += " -stroke black";
    sys_string += " -fill cyan ";
    sys_string +=" -strokewidth 1 -draw \"rectangle ";
    sys_string += string_i(x0);
    sys_string += ",";
    sys_string += string_i(y0);
    sys_string += " ";
    sys_string += string_i(x1);
    sys_string += ",";
    sys_string += string_i(y1);
    sys_string += "\" \\\n";
  }
  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());

  /// (2) generate reticle
  std::string reticle_path = "reticle/";
  reticle_path += name;
  reticle_path += "/";
  command = "mkdir -p ";
  command += reticle_path.c_str();
  command += "\n";
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make reticle directory [%s]\n",command.c_str());
    exit(1);
  }
  /// reticle.png
  sys_string = "";
  fn = reticle_path.c_str();
  fn += "reticle";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);
  x = width/2;
  y = width;
  if (centering == CENTER) y = width/2;
 // int index = 0;
  offset = tenOffset;

  x0 = x-2;
  x1 = x+1;
  y0 = 0;
  y1 = height;

  sys_string += " -stroke black";
  sys_string += " -fill ";
  sys_string += "red";
  sys_string += " ";
  sys_string +=" -strokewidth 1 -draw \"rectangle ";
  sys_string += string_i(x0);
  sys_string += ",";
  sys_string += string_i(y0);
  sys_string += " ";
  sys_string += string_i(x1);
  sys_string += ",";
  sys_string += string_i(y1);
  sys_string += "\" \\\n";

  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());

/// (2A) reticle-brg
  /// reticle-brg.png
  sys_string = "";
  fn = reticle_path.c_str();
  fn += "reticle-brg";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);
  x = width/2;
  y = width;
  if (centering == CENTER) y = width/2;
 // int index = 0;
  offset = tenOffset;

  x0 = x-2;
  x1 = x+1;
  y0 = 0;
  y1 = height;

  sys_string += " -stroke black";
  sys_string += " -fill ";
  sys_string += "yellow";
  sys_string += " ";
  sys_string +=" -strokewidth 1 -draw \"rectangle ";
  sys_string += string_i(x0);
  sys_string += ",";
  sys_string += string_i(y0);
  sys_string += " ";
  sys_string += string_i(x1);
  sys_string += ",";
  sys_string += string_i(y1);
  sys_string += "\" \\\n";

  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());

///(3) if heading_flag generate bug
  if (!heading_flag) return;
/// now for bug
  reticle_path = "bug/";
  reticle_path += name;
  reticle_path += "/";
  command = "mkdir -p ";
  command += reticle_path.c_str();
  command += "\n";
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make bug directory [%s]\n",command.c_str());
    exit(1);
  }

  sys_string = "";
  fn = reticle_path.c_str();
  fn += "bug";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);
  x = width/2;
  y = width;
  if (centering == CENTER) y = width/2;
  //index = 0;
  offset = tenOffset;

  x0 = x-2;
  x1 = x+1;
  y0 = 0;
  y1 = height;

  sys_string += " -stroke black";
  sys_string += " -fill ";
  sys_string += "red";
  sys_string += " ";
  sys_string +=" -strokewidth 1 -draw \"polygon 442,63 442,60 450,52 458,60 458,63 442,63";
  sys_string += "\" \\\n";

  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());
//  exit(1);


}

void instruments::generate_vertical_scale_texture(
                    char * name,
                    char * _color,
                    double width,
                    double height,
                    int centering,
                    int span,
                    int oneOffset,
                    int fiveOffset,
                    int tenOffset
                    )
{
  std::string scale_path = "scale/";
  scale_path += name;
  scale_path += "/";
  std::string command = "mkdir -p ";
  command += scale_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make scale directory [%s]\n",command.c_str());
    exit(1);
  }
  /// (1) generate scale
  color = _color;
  sys_string = "";
  fn = scale_path.c_str();
  //fn += name;
  fn += "scale";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);

  int dy = height/span;
  int y = 0;
  int offset;
  x = width;
  if (centering == CENTER) x = width/2;

  int x0;
  int x1;
  int y0;
  int y1;

  for (int index =-(span/2); index <= (span/2); index++)
  {
    if (index == 0) offset = tenOffset;
    else {
      if ( (index % 10) == 0) offset = tenOffset;
      else {
        if ( (index %5) == 0) offset = fiveOffset;
        else offset = oneOffset;
      }
    }
    if (centering == RIGHT) {
      x0 = 0;
      y0 = y-2;
      x1 = offset;
      y1 = y+1;
    }
    if (centering == LEFT) {
      x0 = x-offset;
      y0 = y-2;
      x1 = width;
      y1 = y+1;
    }
    if (centering == CENTER) {
      x0 = x-offset;
      y0 = y-2;
      x1 = x + offset;
      y1 = y+1;
    }
    sys_string += " -stroke black";
    sys_string += " -fill ";
    sys_string += color;
    sys_string += " ";
    sys_string +=" -strokewidth 1 -draw \"rectangle ";
    sys_string += string_i(x0);
    sys_string += ",";
    sys_string += string_i(y0);
    sys_string += " ";
    sys_string += string_i(x1);
    sys_string += ",";
    sys_string += string_i(y1);
    sys_string += "\" \\\n";
    y += dy;
  }
  if (centering != CENTER) {
    if (centering == RIGHT) {
      x0 = 0;
      y0 = 0;
      x1 = 3;
      y1 = height-1;
    }
    if (centering == LEFT) {
      x0 = width-1;
      y0 = 0;
      x1 = width-4;
      y1 = height-1;
    }
    sys_string += " -stroke black";
    sys_string += " -fill cyan ";
    sys_string +=" -strokewidth 1 -draw \"rectangle ";
    sys_string += string_i(x0);
    sys_string += ",";
    sys_string += string_i(y0);
    sys_string += " ";
    sys_string += string_i(x1);
    sys_string += ",";
    sys_string += string_i(y1);
    sys_string += "\" \\\n";
  }
  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());

  /// (2) generate reticle
  std::string reticle_path = "reticle/";
  reticle_path += name;
  reticle_path += "/";
  command = "mkdir -p ";
  command += reticle_path.c_str();
  command += "\n";
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make reticle directory [%s]\n",command.c_str());
    exit(1);
  }
  sys_string = "";
  fn = reticle_path.c_str();
  fn += "reticle";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);
  y = height/2;
  x = width;
  if (centering == CENTER) x = width/2;
//  int index = 0;
  offset = tenOffset;

  x0 = 0; ;
  x1 = width;
  y0 = y-2;
  y1 = y+1;

  sys_string += " -stroke black";
  sys_string += " -fill ";
  sys_string += "red";
  sys_string += " ";
  sys_string +=" -strokewidth 1 -draw \"rectangle ";
  sys_string += string_i(x0);
  sys_string += ",";
  sys_string += string_i(y0);
  sys_string += " ";
  sys_string += string_i(x1);
  sys_string += ",";
  sys_string += string_i(y1);
  sys_string += "\" \\\n";

  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());

  if (!bug_flag) return;
/// now for bug
  reticle_path = "bug/";
  reticle_path += name;
  reticle_path += "/";
  command = "mkdir -p ";
  command += reticle_path.c_str();
  command += "\n";
  command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make bug directory [%s]\n",command.c_str());
    exit(1);
  }
  sys_string = "";
  fn = reticle_path.c_str();
  fn += "bug";
  fn_n = fn;// + "";
  fn_n_txt=fn_n + ".txt";
  print_header(width,height);
  x = width/2;
  y = width;
  if (centering == CENTER) y = width/2;
  //index = 0;
  offset = tenOffset;

  x0 = x-2;
  x1 = x+1;
  y0 = 0;
  y1 = height;

  sys_string += " -stroke black";
  sys_string += " -fill ";
  sys_string += "red";
  sys_string += " ";
  switch (bug_orientation) {
  case BUG_LEFT:
    sys_string += " -strokewidth 1 -draw \"polygon  0,217  4,217  9,225  4,233  0,233  0,217";
    break;
  case BUG_CENTER:
    sys_string += " -strokewidth 1 -draw \"polygon 17,225 23,217 39,217 45,225 39,233 23,233, 17,225";
    break;
  case BUG_RIGHT:
    sys_string += " -strokewidth 1 -draw \"polygon 63,217 60,217 52,225 60,233 63,233 63,217";
    break;

  }
///  sys_string +=" -strokewidth 1 -draw \"polygon 442,63 442,60 450,52 458,60 458,63 442,63";
  sys_string += "\" \\\n";

  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());
  /**
convert -size 64.0000000x900.000000 xc:none  -encoding None -font AvantGarde-Demi \
 -stroke black -fill red  -strokewidth 1 -draw "polygon 63,442 60,442 52,450 60,458 63,458 63,442" \
bug/heading-true/bug-right.png

convert -size 64.0000000x900.000000 xc:none  -encoding None -font AvantGarde-Demi \
 -stroke black -fill red  -strokewidth 1 -draw "polygon 0,442 4,442 9,450 4,458 0,458 0,442" \
bug/heading-true/bug-left.png


convert -size 64.0000000x900.000000 xc:none  -encoding None -font AvantGarde-Demi \
 -stroke black -fill red  -strokewidth 1 -draw "polygon 17,450 23,442 39,442 45,450 39,458 23,458, 17,450" \
bug/heading-true/bug-center.png
  **/

}

void instruments::generate_ac_file_n_textures(
                    char * name,
                    double width,
                    double height,
                    int n,
                    int n0,
                    int delta_n
                    )
{
  int nbug = 0;
  if (bug_flag) nbug = 1;
  FILE * fp;
  std::string fn=name;
  fn+=".ac";
  fp = fopen(fn.c_str(),"w++");
  fprintf(fp,"AC3Db\n");
  fprintf(fp,"MATERIAL \"illum\" rgb 1.000 1.000 1.000  amb 0.800 0.800 0.800  emis 1.000 1.000 1.000  spec 0.000 0.000 0.000  shi 64 trans 0.000\n");
  fprintf(fp,"OBJECT world\n");
  fprintf(fp,"name \"Blender_exporter_v3.3__untitled.ac\"\n");
  fprintf(fp,"kids %d\n\n",n+2+nbug+1);  /// +1 at end for reticle-brg
  std::string _name = name;
  std::string _texture = name;
  int ni = n0;
  for (int i = 0; i < n; i++) {
    _name = name;
    _name += "_";
    _texture = "numbers/";
    _texture += name;
    _texture += "/";
    _texture += name;
    _texture += "_";
    if (n0 < 0) {
      _texture += string_i_signed(ni);
      _name += string_i_signed(ni);
    }
    else {
      _texture += string_i(ni);
      _name += string_i(ni);
    }
    ni += delta_n;

    fprintf(fp,"OBJECT poly\n");
    fprintf(fp,"name \"%s\"\n",_name.c_str());
    fprintf(fp,"data 15\n");
    fprintf(fp,"a.mesh\n");
    fprintf(fp,"crease 45.0\n");
    fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
    fprintf(fp,"texrep 1 1\n");
    fprintf(fp,"numvert 6\n");
    fprintf(fp,"0 %10.6f %10.6f\n",height, -width);
    fprintf(fp,"0 %10.6f %10.6f\n",-height,-width);
    fprintf(fp,"0 %10.6f %10.6f1\n",-height,width);
    fprintf(fp,"0 %10.6f %10.6f\n",height,width);
    fprintf(fp,"0 -0 %10.6f\n",width);
    fprintf(fp,"0 0 %10.6f\n",-width);
    fprintf(fp,"numsurf 2\n");
    fprintf(fp,"SURF 0X0\n");
    fprintf(fp,"mat 0\n");
    fprintf(fp,"refs 4\n");
    fprintf(fp,"0 0.998047 1\n");
    fprintf(fp,"3 0 1\n");
    fprintf(fp,"4 0 0.5\n");
    fprintf(fp,"5 0.998047 0.5\n");
    fprintf(fp,"SURF 0X0\n");
    fprintf(fp,"mat 0\n");
    fprintf(fp,"refs 4\n");
    fprintf(fp,"1 0.998047 0\n");
    fprintf(fp,"5 0.998047 0.5\n");
    fprintf(fp,"4 0 0.5\n");
    fprintf(fp,"2 0 0\n");
    fprintf(fp,"kids 0\n\n");
  }

  _name = "reticle";
  _texture = "reticle/";
  _texture += name;
  _texture += "/reticle";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height, -width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",-height,-width);
  fprintf(fp,"0.00001 %10.6f %10.6f1\n",-height,width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height,width);
  fprintf(fp,"0.00001 -0 %10.6f\n",width);
  fprintf(fp,"0.00001 0 %10.6f\n",-width);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");


  _name = "reticle-brg";
  _texture = "reticle/";
  _texture += name;
  _texture += "/reticle-brg";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height, -width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",-height,-width);
  fprintf(fp,"0.00001 %10.6f %10.6f1\n",-height,width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height,width);
  fprintf(fp,"0.00001 -0 %10.6f\n",width);
  fprintf(fp,"0.00001 0 %10.6f\n",-width);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");

  if (bug_flag) {

  _name = "bug";
  _texture = "bug/";
  _texture += name;
  _texture += "/bug";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height, -width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",-height,-width);
  fprintf(fp,"0.00001 %10.6f %10.6f1\n",-height,width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height,width);
  fprintf(fp,"0.00001 -0 %10.6f\n",width);
  fprintf(fp,"0.00001 0 %10.6f\n",-width);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");
  }


  _name = "scale";
  _texture = "scale/";
  _texture += name;
  _texture += "/scale";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0 %10.6f %10.6f\n",height, -width);
  fprintf(fp,"0 %10.6f %10.6f\n",-height,-width);
  fprintf(fp,"0 %10.6f %10.6f1\n",-height,width);
  fprintf(fp,"0 %10.6f %10.6f\n",height,width);
  fprintf(fp,"0 -0 %10.6f\n",width);
  fprintf(fp,"0 0 %10.6f\n",-width);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");

  fclose(fp);
}

void instruments::generate_ac_file_n_textures_w_xml(
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
                    )
{
  width  *= INCH_TO_METER;
  height *= INCH_TO_METER;
  generate_ac_file_n_textures(name, width, height, n, n0, delta_n);


  FILE * fp;
  std::string fn=name;
  fn+=".xml";
  fp = fopen(fn.c_str(),"w++");
  fprintf(fp,"<?xml version=\"1.0\"?>\n");
  fprintf(fp,"<PropertyList>\n");
  fprintf(fp,"  <path>%s.ac</path>\n\n",name);


  std::string andor[2];
  andor[0] = "or";
  andor[1] = "and";
  int ni = n0;
  int r0;
  int r1;
  int ri;
  std::string _name = name;
  std::string _texture = name;

  if (rotate_flag) {  /// true only for pitch tape
    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>rotate</type>\n");
    fprintf(fp,"    <object-name>scale</object-name>\n");
    fprintf(fp,"    <object-name>reticle</object-name>\n");
    for (int i = 0; i < n; i++) {
      _texture = name;
      _texture += "_";
      if (n0 < 0) _texture += string_i_signed(ni); else _texture += string_i(ni);
      _name = _texture.c_str();

      r0 = ni - range;
      r1 = ni + range;
      if ( (r1-r0) > delta_n) ri = 1; else ri = 0;
      fprintf(fp,"    <object-name>%s</object-name>\n",_name.c_str());
      ni += delta_n;
    }
    fprintf(fp,"    <property>/orientation/roll-deg</property>\n");
    fprintf(fp,"    <factor>1</factor>\n");
    fprintf(fp,"    <axis>\n");
    fprintf(fp,"      <x>1</x>\n");
    fprintf(fp,"      <y>0</y>\n");
    fprintf(fp,"      <z>0</z>\n");
    fprintf(fp,"    </axis>\n");
    fprintf(fp,"  </animation>\n");
    fprintf(fp,"\n");

  }


  fprintf(fp,"  <animation>\n");
  fprintf(fp,"    <type>textranslate</type>\n");
  fprintf(fp,"    <object-name>scale</object-name>\n");
  fprintf(fp,"    <property>%s</property>\n",property);
  fprintf(fp,"    <bias>0</bias>\n");
  fprintf(fp,"    <factor>%10.6f</factor>\n",factor);
  fprintf(fp,"    <step>0</step>\n");
  fprintf(fp,"    <axis>\n");
  fprintf(fp,"      <x>%d</x>\n",x);
  fprintf(fp,"      <y>%d</y>\n",y);
  fprintf(fp,"      <z>%d</z>\n",z);
  fprintf(fp,"    </axis>\n");
  fprintf(fp,"  </animation>\n\n");
  fprintf(fp,"\n");

  if (bug_flag) {
    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>select</type>\n");
    fprintf(fp,"    <object-name>bug</object-name>\n");
    fprintf(fp,"    <condition>\n");
    fprintf(fp,"      <equals>\n");
    fprintf(fp,"        <property>%s</property>\n",bug_nasal_str_switch.c_str());
    fprintf(fp,"        <value type=\"double\">1.0</value>\n");
    fprintf(fp,"      </equals>\n");
    fprintf(fp,"    </condition>\n");
    fprintf(fp,"  </animation>\n");

    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>textranslate</type>\n");
    fprintf(fp,"    <object-name>bug</object-name>\n");
    fprintf(fp,"    <property>%s</property>\n",bug_nasal_str_distance.c_str());
    fprintf(fp,"    <bias>\n");
    fprintf(fp,"    0.0\n");
    fprintf(fp,"    </bias>\n");
    fprintf(fp,"    <factor>%12.9f</factor>\n",factor);
    fprintf(fp,"    <step>0</step>\n");
    fprintf(fp,"    <axis>\n");
    fprintf(fp,"      <x>%d</x>\n",x);
    fprintf(fp,"      <y>%d</y>\n",y);
    fprintf(fp,"      <z>%d</z>\n",z);
    fprintf(fp,"    </axis>\n");
    fprintf(fp,"  </animation>\n");
    fprintf(fp,"\n");

  }

  ni = n0;

  for (int i = 0; i < n; i++) {
    _texture = name;
    _texture += "_";
    if (n0 < 0) _texture += string_i_signed(ni); else _texture += string_i(ni);
    _name = _texture.c_str();

    r0 = ni - range;
    r1 = ni + range;

    if (heading_flag) {
      if (r0 < 0) r0+=360;
      if (r1 < 0) r1+=360;
      if (r0 > 360) r0-=360;
      if (r1 > 360) r1-=360;
    }

    if ( (r1-r0) > delta_n) ri = 1; else ri = 0;

    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>select</type>\n");
    fprintf(fp,"    <object-name>%s</object-name>\n",_name.c_str());
    fprintf(fp,"    <condition>\n");
    fprintf(fp,"      <%s>\n",andor[ri].c_str());
    fprintf(fp,"        <greater-than-equals>\n");
    fprintf(fp,"          <property>%s</property>\n",property);
    fprintf(fp,"          <value type=\"double\">%10.6f</value>\n",(double)(r0));
    fprintf(fp,"        </greater-than-equals>\n");
    fprintf(fp,"        <less-than-equals>\n");
    fprintf(fp,"          <property>%s</property>\n",property);
    fprintf(fp,"          <value type=\"double\">%10.6f</value>\n",(double)(r1));
    fprintf(fp,"        </less-than-equals>\n");
    fprintf(fp,"      </%s>\n",andor[ri].c_str());
    fprintf(fp,"    </condition>\n");
    fprintf(fp,"  </animation>\n");

    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>textranslate</type>\n");
    fprintf(fp,"    <object-name>%s</object-name>\n",_name.c_str());
    fprintf(fp,"    <property>%s</property>\n",property);
    fprintf(fp,"    <bias>%10.6f</bias>\n",(double)-ni);
    fprintf(fp,"    <factor>%10.6f</factor>\n",factor*nfactor);
    fprintf(fp,"    <step>0</step>\n");
    fprintf(fp,"    <axis>\n");
    fprintf(fp,"      <x>%d</x>\n",x);
    fprintf(fp,"      <y>%d</y>\n",y);
    fprintf(fp,"      <z>%d</z>\n",z);
    fprintf(fp,"    </axis>\n");

    fprintf(fp,"  </animation>\n\n");

    ni += delta_n;

  }
  fprintf(fp,"</PropertyList>\n");
  fclose(fp);
}
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
/**
void instruments::generate_ac_file_w_caption_n_digits(
                    char * name,
                    int decimal_pos,
                    double n_digits,
                    double cxl,
                    double cyl,
                    double cxh,
                    double cyh,
                    double centerdx,
                    double centerdy,
                    double widthdx,
                    double widthdy
                  //  char * property
                    )
{
  FILE * fp;
  std::string fn=name;
  fn+=".ac";
  fp = fopen(fn.c_str(),"w++");
  fprintf(fp,"AC3Db\n");
  fprintf(fp,"MATERIAL \"illum\" rgb 1.000 1.000 1.000  amb 0.800 0.800 0.800  emis 1.000 1.000 1.000  spec 0.000 0.000 0.000  shi 64 trans 0.000\n");
  fprintf(fp,"OBJECT world\n");
  fprintf(fp,"name \"Blender_exporter_v3.3__untitled.ac\"\n");
  int nkids = n_digits+1;
  if (decimal_pos > 0) nkids ++;
  fprintf(fp,"kids %d\n\n",nkids);
  std::string _name = name;
  std::string _texture = name;
    _name = "caption";
  _texture = "caption/";
  _texture += name;
  _texture += "/caption";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxl);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxh);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");

  for (int i = 0; i <n_digits; i++){
    if (i == 0) {
      fprintf(fp,"OBJECT poly\n");
      fprintf(fp,"name \"digit%d\"\n",i);
      fprintf(fp,"texture \"digits/digits.png\"\n");
      fprintf(fp,"texrep 1 1\n");
      fprintf(fp,"crease 20\n");
      fprintf(fp,"numvert 4\n");
      cyh = centerdy +0.5* widthdy;
      cyl = centerdy -0.5* widthdy;
      cxl = centerdx -1.5* widthdx;
      cxh = cxl + widthdx;
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxl);
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxh);
      fprintf(fp,"numsurf 1\n");
      fprintf(fp,"SURF 0x00\n");
      fprintf(fp,"mat 0\n");
      fprintf(fp,"refs 4\n");
      fprintf(fp,"0 0.249496638775 0.0891927108169\n");
      fprintf(fp,"3 0.194574713707 0.0891927108169\n");
      fprintf(fp,"2 0.194574713707 0.0147162750363\n");
      fprintf(fp,"1 0.249496638775 0.0147162750363\n");
      fprintf(fp,"kids 0\n");
    }
    else {
      if (i==1) {
        if (decimal_pos == DECIMAL_AT1) {
          fprintf(fp,"OBJECT poly\n");
          fprintf(fp,"name \"decimal-point\"\n");
          fprintf(fp,"texture \"digits/decimal-point.png\"\n");
          fprintf(fp,"texrep 1 1\n");
          fprintf(fp,"crease 20\n");
          fprintf(fp,"numvert 4\n");
          cxl += widthdx;
          cxh += widthdx;
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxl);
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxh);
          fprintf(fp,"numsurf 1\n");
          fprintf(fp,"SURF 0x00\n");
          fprintf(fp,"mat 0\n");
          fprintf(fp,"refs 4\n");
          fprintf(fp,"0 0.249496638775 0.0891927108169\n");
          fprintf(fp,"3 0.194574713707 0.0891927108169\n");
          fprintf(fp,"2 0.194574713707 0.0147162750363\n");
          fprintf(fp,"1 0.249496638775 0.0147162750363\n");
          fprintf(fp,"kids 0\n");
        }
      }
      if (i==2) {
        if (decimal_pos == DECIMAL_AT2) {
          fprintf(fp,"OBJECT poly\n");
          fprintf(fp,"name \"decimal-point\"\n");
          fprintf(fp,"texture \"digits/decimal-point.png\"\n");
          fprintf(fp,"texrep 1 1\n");
          fprintf(fp,"crease 20\n");
          fprintf(fp,"numvert 4\n");
          cxl += widthdx;
          cxh += widthdx;
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxl);
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
          fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxh);
          fprintf(fp,"numsurf 1\n");
          fprintf(fp,"SURF 0x00\n");
          fprintf(fp,"mat 0\n");
          fprintf(fp,"refs 4\n");
          fprintf(fp,"0 0.249496638775 0.0891927108169\n");
          fprintf(fp,"3 0.194574713707 0.0891927108169\n");
          fprintf(fp,"2 0.194574713707 0.0147162750363\n");
          fprintf(fp,"1 0.249496638775 0.0147162750363\n");
          fprintf(fp,"kids 0\n");
        }
      }
      fprintf(fp,"OBJECT poly\n");
      fprintf(fp,"name \"digit%d\"\n",i);
      fprintf(fp,"texture \"digits/digits.png\"\n");
      fprintf(fp,"texrep 1 1\n");
      fprintf(fp,"crease 20\n");
      fprintf(fp,"numvert 4\n");
      cxl += widthdx;
      cxh += widthdx;
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxl);
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
      fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxh);
      fprintf(fp,"numsurf 1\n");
      fprintf(fp,"SURF 0x00\n");
      fprintf(fp,"mat 0\n");
      fprintf(fp,"refs 4\n");
      fprintf(fp,"0 0.249496638775 0.0891927108169\n");
      fprintf(fp,"3 0.194574713707 0.0891927108169\n");
      fprintf(fp,"2 0.194574713707 0.0147162750363\n");
      fprintf(fp,"1 0.249496638775 0.0147162750363\n");
      fprintf(fp,"kids 0\n");
    }
  }
  fclose(fp);
}
**/
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
/**
void instruments::generate_ac_file_w_caption_n_textures(
                    char * name,
                    double cxl,
                    double cyl,
                    double cxh,
                    double cyh,
                    double width,
                    double height,
                    int n,
                    int n0,
                    int delta_n
                    )
{

  int nbug = 0;
  if (bug_flag) nbug = 1;
  FILE * fp;
  std::string fn=name;
  fn+=".ac";
  fp = fopen(fn.c_str(),"w++");
  fprintf(fp,"AC3Db\n");
  fprintf(fp,"MATERIAL \"illum\" rgb 1.000 1.000 1.000  amb 0.800 0.800 0.800  emis 1.000 1.000 1.000  spec 0.000 0.000 0.000  shi 64 trans 0.000\n");
  fprintf(fp,"OBJECT world\n");
  fprintf(fp,"name \"Blender_exporter_v3.3__untitled.ac\"\n");
  fprintf(fp,"kids %d\n\n",n+4+nbug);
  std::string _name = name;
  std::string _texture = name;
  int ni = n0;
  for (int i = 0; i < n; i++) {
    _name = name;
    _name += "_";
    _texture = "numbers/";
    _texture += name;
    _texture += "/";
    _texture += name;
    _texture += "_";
    if (n0 < 0) {
      _texture += string_i_signed(ni);
      _name += string_i_signed(ni);
    }
    else {
      _texture += string_i(ni);
      _name += string_i(ni);
    }
    ni += delta_n;

    fprintf(fp,"OBJECT poly\n");
    fprintf(fp,"name \"%s\"\n",_name.c_str());
    fprintf(fp,"data 15\n");
    fprintf(fp,"a.mesh\n");
    fprintf(fp,"crease 45.0\n");
    fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
    fprintf(fp,"texrep 1 1\n");
    fprintf(fp,"numvert 6\n");
    fprintf(fp,"0 %10.6f %10.6f\n",height, -width);
    fprintf(fp,"0 %10.6f %10.6f\n",-height,-width);
    fprintf(fp,"0 %10.6f %10.6f1\n",-height,width);
    fprintf(fp,"0 %10.6f %10.6f\n",height,width);
    fprintf(fp,"0 -0 %10.6f\n",width);
    fprintf(fp,"0 0 %10.6f\n",-width);
    fprintf(fp,"numsurf 2\n");
    fprintf(fp,"SURF 0X0\n");
    fprintf(fp,"mat 0\n");
    fprintf(fp,"refs 4\n");
    fprintf(fp,"0 0.998047 1\n");
    fprintf(fp,"3 0 1\n");
    fprintf(fp,"4 0 0.5\n");
    fprintf(fp,"5 0.998047 0.5\n");
    fprintf(fp,"SURF 0X0\n");
    fprintf(fp,"mat 0\n");
    fprintf(fp,"refs 4\n");
    fprintf(fp,"1 0.998047 0\n");
    fprintf(fp,"5 0.998047 0.5\n");
    fprintf(fp,"4 0 0.5\n");
    fprintf(fp,"2 0 0\n");
    fprintf(fp,"kids 0\n\n");
  }

  _name = "reticle";
  _texture = "reticle/";
  _texture += name;
  _texture += "/reticle";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height, -width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",-height,-width);
  fprintf(fp,"0.00001 %10.6f %10.6f1\n",-height,width);
  fprintf(fp,"0.00001 %10.6f %10.6f\n",height,width);
  fprintf(fp,"0.00001 -0 %10.6f\n",width);
  fprintf(fp,"0.00001 0 %10.6f\n",-width);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");

  if (bug_flag) {
    _name = "bug";
    _texture = "bug/";
    _texture += name;
    _texture += "/bug";

    fprintf(fp,"OBJECT poly\n");
    fprintf(fp,"name \"%s\"\n",_name.c_str());
    fprintf(fp,"data 15\n");
    fprintf(fp,"a.mesh\n");
    fprintf(fp,"crease 45.0\n");
    fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
    fprintf(fp,"texrep 1 1\n");
    fprintf(fp,"numvert 6\n");
    fprintf(fp,"0.00001 %10.6f %10.6f\n",height, -width);
    fprintf(fp,"0.00001 %10.6f %10.6f\n",-height,-width);
    fprintf(fp,"0.00001 %10.6f %10.6f1\n",-height,width);
    fprintf(fp,"0.00001 %10.6f %10.6f\n",height,width);
    fprintf(fp,"0.00001 -0 %10.6f\n",width);
    fprintf(fp,"0.00001 0 %10.6f\n",-width);
    fprintf(fp,"numsurf 2\n");
    fprintf(fp,"SURF 0X0\n");
    fprintf(fp,"mat 0\n");
    fprintf(fp,"refs 4\n");
    fprintf(fp,"0 0.998047 1\n");
    fprintf(fp,"3 0 1\n");
    fprintf(fp,"4 0 0.5\n");
    fprintf(fp,"5 0.998047 0.5\n");
    fprintf(fp,"SURF 0X0\n");
    fprintf(fp,"mat 0\n");
    fprintf(fp,"refs 4\n");
    fprintf(fp,"1 0.998047 0\n");
    fprintf(fp,"5 0.998047 0.5\n");
    fprintf(fp,"4 0 0.5\n");
    fprintf(fp,"2 0 0\n");
    fprintf(fp,"kids 0\n\n");
  }

  _name = "scale";
  _texture = "scale/";
  _texture += name;
  _texture += "/scale";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0 %10.6f %10.6f\n",height, -width);
  fprintf(fp,"0 %10.6f %10.6f\n",-height,-width);
  fprintf(fp,"0 %10.6f %10.6f1\n",-height,width);
  fprintf(fp,"0 %10.6f %10.6f\n",height,width);
  fprintf(fp,"0 -0 %10.6f\n",width);
  fprintf(fp,"0 0 %10.6f\n",-width);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");

  _name = "caption";
  _texture = "caption/";
  _texture += name;
  _texture += "/caption";

  fprintf(fp,"OBJECT poly\n");
  fprintf(fp,"name \"%s\"\n",_name.c_str());
  fprintf(fp,"data 15\n");
  fprintf(fp,"a.mesh\n");
  fprintf(fp,"crease 45.0\n");
  fprintf(fp,"texture \"%s.png\"\n",_texture.c_str());
  fprintf(fp,"texrep 1 1\n");
  fprintf(fp,"numvert 6\n");
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxl);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyh, cxh);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxh);
  fprintf(fp,"0.0001 %10.6f %10.6f\n", cyl, cxl);
  fprintf(fp,"numsurf 2\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"0 0.998047 1\n");
  fprintf(fp,"3 0 1\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"SURF 0X0\n");
  fprintf(fp,"mat 0\n");
  fprintf(fp,"refs 4\n");
  fprintf(fp,"1 0.998047 0\n");
  fprintf(fp,"5 0.998047 0.5\n");
  fprintf(fp,"4 0 0.5\n");
  fprintf(fp,"2 0 0\n");
  fprintf(fp,"kids 0\n\n");

  fclose(fp);
}
**/
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
/**
void instruments::generate_ac_file_w_caption_n_digits_w_xml(
           char * name,
           int decimal_pos,
           double n_digits,
           double cxl,
           double cyl,
           double cxh,
           double cyh,
           double centerdx,
           double centerdy,
           double widthdx,
           double widthdy,
           char * property
           )
{
  double factorBase        = 0.1;
  double factorMultiplier  = 0.1;
  double nfactorBase       = 1.0;
  double nfactorMultiplier = 10.0;

  cxl *= INCH_TO_METER;
  cyl *= INCH_TO_METER;
  cxh *= INCH_TO_METER;
  cyh *= INCH_TO_METER;
  centerdx *= INCH_TO_METER;
  centerdy *= INCH_TO_METER;
  widthdx *= INCH_TO_METER;
  widthdy *= INCH_TO_METER;
  generate_ac_file_w_caption_n_digits(name, decimal_pos, n_digits, cxl, cyl, cxh, cyh, centerdx, centerdy, widthdx, widthdy);
  FILE * fp;
  std::string fn=name;
  fn+=".xml";
  fp = fopen(fn.c_str(),"w++");
  fprintf(fp,"<?xml version=\"1.0\"?>\n");
  fprintf(fp,"<PropertyList>\n");
  fprintf(fp,"  <path>%s.ac</path>\n\n",name);
  double factor = factorBase;
  double nfactor = nfactorBase;
  for (int i = 0; i < n_digits; i++) {
    fprintf(fp,"<animation>\n");
    fprintf(fp,"	 <type>textranslate</type>\n");
    fprintf(fp,"	 <object-name>digit%d</object-name>\n",i);
    fprintf(fp,"	 <property>%s</property>\n",property);
    fprintf(fp,"	 <factor>%f</factor>\n",factor);
    fprintf(fp,"	 <step>%f</step>\n",nfactor);
    fprintf(fp,"	 <axis>\n");
    fprintf(fp,"		 <x>0</x>\n");
    fprintf(fp,"		 <y>1</y>\n");
    fprintf(fp,"		 <z>0</z>\n");
    fprintf(fp,"	 </axis>\n");
    fprintf(fp," </animation>\n");
    factor *= factorMultiplier;
    nfactor *= nfactorMultiplier;
  }
  fprintf(fp,"</PropertyList>\n");
  fclose(fp);
}
**/
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
/**
void instruments::generate_ac_file_w_caption_n_textures_w_xml(
                    bool rotate_flag,
                    char * name,
                    double cxl,
                    double cyl,
                    double cxh,
                    double cyh,
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
                    int z)
{
  width  *= INCH_TO_METER;
  height *= INCH_TO_METER;
  cxl *= INCH_TO_METER;
  cyl *= INCH_TO_METER;
  cxh *= INCH_TO_METER;
  cyh *= INCH_TO_METER;
  generate_ac_file_w_caption_n_textures(name,cxl, cyl, cxh, cyh, width,height, n, n0, delta_n);

  FILE * fp;
  std::string fn=name;
  fn+=".xml";
  fp = fopen(fn.c_str(),"w++");
  fprintf(fp,"<?xml version=\"1.0\"?>\n");
  fprintf(fp,"<PropertyList>\n");
  fprintf(fp,"  <path>%s.ac</path>\n\n",name);


  std::string andor[2];
  andor[0] = "or";
  andor[1] = "and";
  int ni = n0;
  int r0;
  int r1;
  int ri;
  std::string _name = name;
  std::string _texture = name;

  if (rotate_flag) {  /// pitch tape currently pitch is not captioned....
    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>rotate</type>\n");
    fprintf(fp,"    <object-name>scale</object-name>\n");
    fprintf(fp,"    <object-name>reticle</object-name>\n");
    for (int i = 0; i < n; i++) {
      _texture = name;
      _texture += "_";
      if (n0 < 0) _texture += string_i_signed(ni); else _texture += string_i(ni);
      _name = _texture.c_str();

      r0 = ni - range;
      r1 = ni + range;
      if ( (r1-r0) > delta_n) ri = 1; else ri = 0;
      fprintf(fp,"    <object-name>%s</object-name>\n",_name.c_str());
      ni += delta_n;
    }
    fprintf(fp,"    <property>/orientation/roll-deg</property>\n");
    fprintf(fp,"    <factor>1</factor>\n");
    fprintf(fp,"    <axis>\n");
    fprintf(fp,"      <x>1</x>\n");
    fprintf(fp,"      <y>0</y>\n");
    fprintf(fp,"      <z>0</z>\n");
    fprintf(fp,"    </axis>\n");
    fprintf(fp,"  </animation>\n");
    fprintf(fp,"\n");

  }


  fprintf(fp,"  <animation>\n");
  fprintf(fp,"    <type>textranslate</type>\n");
  fprintf(fp,"    <object-name>scale</object-name>\n");
  fprintf(fp,"    <property>%s</property>\n",property);
  fprintf(fp,"    <bias>0</bias>\n");
  fprintf(fp,"    <factor>%10.6f</factor>\n",factor);
  fprintf(fp,"    <step>0</step>\n");
  fprintf(fp,"    <axis>\n");
  fprintf(fp,"      <x>%d</x>\n",x);
  fprintf(fp,"      <y>%d</y>\n",y);
  fprintf(fp,"      <z>%d</z>\n",z);
  fprintf(fp,"    </axis>\n");
  fprintf(fp,"  </animation>\n\n");
  fprintf(fp,"\n");

  if (bug_flag) {
    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>select</type>\n");
    fprintf(fp,"    <object-name>bug</object-name>\n");
    fprintf(fp,"    <condition>\n");
    fprintf(fp,"      <equals>\n");
    fprintf(fp,"        <property>%s</property>\n",bug_nasal_str_switch.c_str());
    fprintf(fp,"        <value type=\"double\">1.0</value>\n");
    fprintf(fp,"      </equals>\n");
    fprintf(fp,"    </condition>\n");
    fprintf(fp,"  </animation>\n");
    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>textranslate</type>\n");
    fprintf(fp,"    <object-name>bug</object-name>\n");
    fprintf(fp,"    <property>%s</property>\n",bug_nasal_str_distance.c_str());
    fprintf(fp,"    <bias>\n");
    fprintf(fp,"    0.0\n");
    fprintf(fp,"    </bias>\n");
    fprintf(fp,"    <factor>%12.9f</factor>\n",factor);
    fprintf(fp,"    <step>0</step>\n");
    fprintf(fp,"    <axis>\n");
    fprintf(fp,"      <x>%d</x>\n",x);
    fprintf(fp,"      <y>%d</y>\n",y);
    fprintf(fp,"      <z>%d</z>\n",z);
   /// fprintf(fp,"      <x>0</x>\n");
   /// fprintf(fp,"      <y>1</y>\n");
   /// fprintf(fp,"      <z>0</z>\n");
    fprintf(fp,"    </axis>\n");
    fprintf(fp,"  </animation>\n");
    fprintf(fp,"\n");
  }

  ni = n0;


  for (int i = 0; i < n; i++) {
    _texture = name;
    _texture += "_";
    if (n0 < 0) _texture += string_i_signed(ni); else _texture += string_i(ni);
    _name = _texture.c_str();

    r0 = ni - range;
    r1 = ni + range;

    if (heading_flag) {
      if (r0 < 0) r0+=360;
      if (r1 < 0) r1+=360;
      if (r0 > 360) r0-=360;
      if (r1 > 360) r1-=360;
    }

    if ( (r1-r0) > delta_n) ri = 1; else ri = 0;

    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>select</type>\n");
    fprintf(fp,"    <object-name>%s</object-name>\n",_name.c_str());
    fprintf(fp,"    <condition>\n");
    fprintf(fp,"      <%s>\n",andor[ri].c_str());
    fprintf(fp,"        <greater-than-equals>\n");
    fprintf(fp,"          <property>%s</property>\n",property);
    fprintf(fp,"          <value type=\"double\">%10.6f</value>\n",(double)(r0));
    fprintf(fp,"        </greater-than-equals>\n");
    fprintf(fp,"        <less-than-equals>\n");
    fprintf(fp,"          <property>%s</property>\n",property);
    fprintf(fp,"          <value type=\"double\">%10.6f</value>\n",(double)(r1));
    fprintf(fp,"        </less-than-equals>\n");
    fprintf(fp,"      </%s>\n",andor[ri].c_str());
    fprintf(fp,"    </condition>\n");
    fprintf(fp,"  </animation>\n");

    fprintf(fp,"  <animation>\n");
    fprintf(fp,"    <type>textranslate</type>\n");
    fprintf(fp,"    <object-name>%s</object-name>\n",_name.c_str());
    fprintf(fp,"    <property>%s</property>\n",property);
    fprintf(fp,"    <bias>%10.6f</bias>\n",(double)-ni);
    fprintf(fp,"    <factor>%10.6f</factor>\n",factor*nfactor);
    fprintf(fp,"    <step>0</step>\n");
    fprintf(fp,"    <axis>\n");
    fprintf(fp,"      <x>%d</x>\n",x);
    fprintf(fp,"      <y>%d</y>\n",y);
    fprintf(fp,"      <z>%d</z>\n",z);
    fprintf(fp,"    </axis>\n");

    fprintf(fp,"  </animation>\n\n");

    ni += delta_n;

  }
  fprintf(fp,"</PropertyList>\n");
  fclose(fp);
}
**/

void instruments::generate_digits(char * _color)
{
 std::string digits_path = "digits/";
  std::string command = "mkdir -p ";
  command += digits_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make digits directory [%s]\n",command.c_str());
    exit(1);
  }
  sys_string = "";
  fn = digits_path.c_str();
  fn +="digits";

  fn_n = fn;
  fn_n_txt=fn_n + ".txt";
  print_header(512,512);
  print_color(_color);
//  draw_text_w_stroke((char *)"SouthWest", 99, 9, (char *) ".");
  for (int i = 0; i<10; i++) {
    draw_text_w_stroke((char *)"SouthWest", 99, i*52+9, (char *) std::to_string(i).c_str());
  }
//  draw_text_w_stroke((char *)"SouthWest", 99, 529, (char *) ".");
  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());
/// now for decimal point
  sys_string = "";
  fn = digits_path.c_str();
  fn +="decimal-point";

  fn_n = fn;
  fn_n_txt=fn_n + ".txt";
  print_header(512,512);
  print_color(_color);
  draw_text_w_stroke((char *)"SouthWest", 99, 9, (char *) ".");
//  for (int i = 0; i<10; i++) {
//    draw_text_w_stroke((char *)"SouthWest", 99, i*52+9, (char *) std::to_string(i).c_str());
 // }
 // draw_text_w_stroke((char *)"SouthWest", 99, 529, (char *) ".");
  end_file((char *)fn_n.c_str());
  printf("output[%s]\n",sys_string.c_str());
  system(sys_string.c_str());



}
    /// BUG: Unknown Reason adding caption leads to degraded frame rates over time.
/**
void instruments::generate_caption(
                    char * name,
                    char * _color,
                    char * caption,
                    double width,
                    double height,
                    int x_offset,
                    int y_offset,
                    int centering
                    )
{
 std::string caption_path = "caption/";
  caption_path += name;
  caption_path += "/";
  std::string command = "mkdir -p ";
  command += caption_path.c_str();
  command += "\n";
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make caption directory [%s]\n",command.c_str());
    exit(1);
  }
  string sindex;
  if (centering == CENTER) {
    sys_string = "";
    fn = caption_path.c_str();
    fn +="caption";

    fn_n = fn;
    fn_n_txt=fn_n + ".txt";
    print_header(width,height);
    print_color(_color);

    draw_text_w_stroke((char *)"Center", x_offset , y_offset, caption);
    end_file((char *)fn_n.c_str());
    printf("output[%s]\n",sys_string.c_str());
    system(sys_string.c_str());
  }
  else {
    if (centering == RIGHT) {
      sys_string = "";
      fn = caption_path.c_str();
      fn += name;
      fn_n = fn;
      fn_n_txt=fn_n + ".txt";
      print_header(width,height);
      print_color(_color);
      draw_text_w_stroke((char *)"East", x_offset , y_offset, caption);
      end_file((char *)fn_n.c_str());
      printf("output[%s]\n",sys_string.c_str());
      system(sys_string.c_str());
    }
    else {
      if (centering == LEFT) {
        sys_string = "";
        fn = caption_path.c_str();
        fn += name;
        fn_n = fn;
        fn_n_txt=fn_n + ".txt";
        print_header(width,height);
        print_color(_color);
        draw_text_w_stroke((char *)"West", x_offset , y_offset, caption);
        end_file((char *)fn_n.c_str());
        printf("output[%s]\n",sys_string.c_str());
        system(sys_string.c_str());
      }
    }
  }
}
**/

void instruments::draw_text(
                    char * gravity,
                    double x,
                    double y,
                    char * text
                    )
{
    sys_string += "-pointsize ";
    sys_string +=string_i(pointsize);
    sys_string +=" -gravity ";
    sys_string += gravity;
    sys_string += " -draw \"text   ";
    sys_string +=string_d(x);
    sys_string +="  ";
    sys_string +=string_d(y);
    sys_string +=" '";
    sys_string +=text;
    sys_string +="'\" \\\n";
}
void instruments::draw_text_w_stroke(
                    char * gravity,
                    double x,
                    double y,
                    char * text
                    )
{
    sys_string += "-stroke black ";
    sys_string += "-pointsize ";
    sys_string +=string_i(pointsize);
    sys_string +=" -gravity ";
    sys_string += gravity;
    sys_string += " -draw \"text   ";
    sys_string +=string_d(x);
    sys_string +="  ";
    sys_string +=string_d(y);
    sys_string +=" '";
    sys_string +=text;
    sys_string +="'\" \\\n";
}

void instruments::draw_text(
                    double x,
                    double y,
                    char * text
                    )
{
    sys_string += "-pointsize ";
    sys_string +=string_i(pointsize);
    sys_string += " -draw \"text   ";
    sys_string +=string_d(x);
    sys_string +="  ";
    sys_string +=string_d(y);
    sys_string +=" '";
    sys_string +=text;
    sys_string +="'\" \\\n";
}

void instruments::draw_text_w_stroke(
                    double x,
                    double y,
                    char * text
                    )
{
    sys_string += "-stroke black ";
    sys_string += "-pointsize ";
    sys_string +=string_i(pointsize);
    sys_string += " -draw \"text   ";
    sys_string +=string_d(x);
    sys_string +="  ";
    sys_string +=string_d(y);
    sys_string +=" '";
    sys_string +=text;
    sys_string +="'\" \\\n";
}
char * instruments::string_i_signed(int i)
{
  if (i >= 0) sprintf(buffer,"+%d",i);
  else sprintf(buffer,"%d",i);
  return (char *)&buffer;
}
char * instruments::string_i(int i)
{
  sprintf(buffer,"%d",i);
  return (char *)&buffer;
}
char * instruments::string_d(double d)
{
  sprintf(buffer,"%f",d);
  return (char *)&buffer;
}

void instruments::draw_stroke(char * color)
{
    sys_string += "-stroke ";
    sys_string += color;
    sys_string += " \\\n";
}
void instruments::draw_strokewidth(int n)
{
    sys_string += "-strokewidth ";
    sys_string += string_d(n);
    sys_string += " \\\n";
}

void instruments::draw_fill(char * color)
{
    sys_string += "-fill ";
    sys_string += color;
    sys_string += " \\\n";
}
void instruments::draw_line(double x0,
                            double y0,
                            double x1,
                            double y1)
{
  sys_string += "-draw \"line ";
  sys_string += string_d(x0);
  sys_string += ",";
  sys_string += string_d(y0);
  sys_string += ",";
  sys_string += string_d(x1);
  sys_string += ",";
  sys_string += string_d(y1);
  sys_string += "\" \\\n";
}
void instruments::draw_circle(              /// experimental code in HUD (translucent condensed steam guages
           double cx,
           double cy,
           double px,
           double py)
{
  sys_string += "-draw \"circle ";
  sys_string += string_d(cx);
  sys_string += ",";
  sys_string += string_d(cy);
  sys_string += ",";
  sys_string += string_d(px);
  sys_string += ",";
  sys_string += string_d(py);
  sys_string += "\" \\\n";
}



void instruments::draw_arc(
                    double x,
                    double y,
                    double r0,
                    double r1,
                    double a0,
                    double a1
                    )
{
  x -=2;

  sys_string += "-draw \"polyline ";

  double px;
  double py;
  double angle = a0;
  for (angle = a0; angle <= a1; angle++)
  {
    px = x + cos(angle*d2r)*r0;
    py = y + sin(angle*d2r)*r0;
    sys_string += string_d(px);
    sys_string += ",";
    sys_string += string_d(py);
    sys_string += ",";
  }
  px = x + cos(a1*d2r)*r1;
  py = y + sin(a1*d2r)*r1;
  sys_string += string_d(px);
  sys_string += ",";
  sys_string += string_d(py);
  sys_string += ",";

  for (angle = a1; angle >= a0; angle --)
  {
    px = x + cos(angle*d2r)*r1;
    py = y + sin(angle*d2r)*r1;
    sys_string += string_d(px);
    sys_string += ",";
    sys_string += string_d(py);
    sys_string += ",";

  }

  px = x + cos(a0*d2r)*r0;
  py = y + sin(a0*d2r)*r0;
    sys_string += string_d(px);
    sys_string += ",";
    sys_string += string_d(py);
    sys_string += "\" \\\n";

}

void instruments::roll_indicator(char * roll_ind_fn,
                                 double img_size,
                                 double radius,
                                 double single_width,
                                 double single_height,
                                 double fives_width,
                                 double fives_height,
                                 double tens_width,
                                 double tens_height)
{
/**
                     1024.0,  /// double img_size,
                      480.0,  /// double radius,
                        4.0,  /// double single_width,
                       10.0,  /// double single_height,
                        6.0,  /// double fives_width,
                       20.0,  /// double fives_height,
                        8.0,  /// double tens_width,
                       30.0); ///     double tens_height);
**/
  sys_string = "";
  print_header(img_size,img_size);
  print_color((char *)"cyan");
  draw_stroke((char *)"black");
  draw_fill((char *)"none");
  draw_strokewidth(2);
  draw_circle(img_size/2,
              img_size/2,
              img_size/2+radius,
              img_size/2);

/// zero bar
  draw_strokewidth(2);
  #define NUM_TENS 19
  double tens[19] = {-90,-80,-70,-60,-50,-40,-30,-20,-10,0,10,20,30,40,50,60,70,80,90};

//  string tens_abs[19] = {"90","80","70","60","50","40","30","20","10","0","10","20","30","40","50","60","70","80","90"};
  string tens_abs[19] = {"9","8","7","6","5","4","3","2","1","0","1","2","3","4","5","6","7","8","9"};
  double angle;
  double x0,y0,x1,y1;

  draw_fill((char *)"cyan");
  for (int i = 0; i<19; i++) {
    angle = tens[i];
    x0 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*radius + img_size/2.0;
    y0 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*radius + img_size/2.0;
    x1 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+tens_height) + img_size/2.0;
    y1 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+tens_height) + img_size/2.0;
    draw_line(x0,y0,x1,y1);
                       ///  90  80  70  60  50  40  30  20  10   0  10  20  30  40  59  60  70  80  89
                       ///   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18
    double x_offset[19] = { -4, -4, -4, -4, -4, -4, -8,-12,-20,-15,-22,-27,-42,-42,-42,-42,-42,-42,-42};
    double y_offset[19] = { 19, 19, 21, 21, 22, 30, 34, 36, 40, 42, 40, 36, 34, 30, 23, 21, 21, 19, 19};


    x1 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+tens_height+50) + img_size/2.0;
    y1 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+tens_height+50) + img_size/2.0;
    printf("i %d x %f y %f\n",i,x1,y1);
    draw_text(x1 +x_offset[i], y1 +y_offset[i], (char *) tens_abs[i].c_str());
  }
  double fives[18] = {-85,-75,-65,-55,-45,-35,-25,-15,5,-5,15,25,35,45,55,65,75,85};
  draw_strokewidth(2);
  for (int i = 0; i<18; i++) {
    angle = fives[i];
    x0 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*radius + img_size/2.0;
    y0 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*radius + img_size/2.0;
    x1 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+fives_height) + img_size/2.0;
    y1 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+fives_height) + img_size/2.0;
    draw_line(x0,y0,x1,y1);
  }
  double singles[16] = {-19,-18,-40,-35,-25 -20,-10,-5,5,10,20,25,35,40,50,55};
  draw_strokewidth(1);
  for (int i = -90; i<=90; i++) {
    angle = i;//singles[i];
    x0 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*radius + img_size/2.0;
    y0 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*radius + img_size/2.0;
    x1 = cos( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+single_height) + img_size/2.0;
    y1 = sin( (angle-90.0) *SG_DEGREES_TO_RADIANS)*(radius+single_height) + img_size/2.0;
    draw_line(x0,y0,x1,y1);

  }
  end_file((char *)roll_ind_fn);
  printf("roll_indicator [%s]\n",sys_string.c_str());
  string command = sys_string.c_str();
  bool command_ok = system_io(&command);
  if (!command_ok) {
    printf("failed to make roll_indicator[%s]\n",command.c_str());
//    exit(1);
  }


}

void instruments::generate_bezel_circle(
                    double width,
                    double height,
                    double radius
                    )
{
  sys_string +="-fill black \\\n";
  sys_string +="-draw 'circle ";
  sys_string +=string_d(width/2.0);
  sys_string +=",";
  sys_string +=string_d(height/2.0);
  sys_string +=",";
  sys_string +=string_d(width/2.0+radius);
  sys_string +=",";
  sys_string +=string_d(height/2.0);
  sys_string +="' \\\n";
}
/**
void instruments::print_caption(
                    double x,
                    double y,
                    int pointsize,
                    char * c
                    )
{
  sys_string +="-fill yellow \\\n";
  sys_string +="-pointsize ";
  sys_string +=string_i(pointsize);
  sys_string +=" -gravity Center -draw \"text   ";
  sys_string +=string_d(x);
  sys_string +="  ";
  sys_string +=string_d(y);
  sys_string +=" '";
  sys_string +=c;
  sys_string +="'\" \\\n";

}
**/

void instruments::print_n(
                    double x0,
                    double y0,
                    double d,
                    double r,
                    int n,
                    int pointsize
                    )
{
  /*
    fprintf(fp,"-pointsize %d -gravity Center -draw \"text   %4.0f  %4.0f  '%d'\" \\\n",pointsize,x0+cos(d*d2r)*r,y0+sin(d*d2r)*r,n);
  */
  sys_string +="-pointsize ";
  sys_string +=string_i(pointsize);
  sys_string +=" -gravity Center -draw \"text   ";
  sys_string +=string_d(x0+cos(d*d2r)*r);
  sys_string +="  ";
  sys_string +=string_d(y0+sin(d*d2r)*r);
  sys_string +=" '";
  sys_string +=string_i(n);
  sys_string +="'\" \\\n";
}

void instruments::print_n_scale(
                    double x0,
                    double y0,
                    double r,
                    double start_d,
                    int start_n,
                    int nn,
                    double dd,
                    int dn ,
                    int pointsize
                    )
{
int n=0;
double d;
int nd;
  d=start_d;
  nd = start_n;
  while (n<nn){
    print_n(x0,y0,d,r,nd,pointsize);
    n++;
    d+=dd;
    nd+=dn;
  }
}

void instruments::rotate_point(
                    double * x,
                    double * y,
                    double d
                    )
{
  double c;
  double s;
  double xt;
  double yt;
  xt=*x;
  yt=*y;
  c= cos(d*d2r);
  s= sin(d*d2r);

  *x= c*xt+s*yt;
  *y= -s*xt+c*yt;

}

void instruments::rotate_points(double d)
{
  rotate_point(&x_0,&y_0,d);
  rotate_point(&x_1,&y_1,d);
  rotate_point(&x_2,&y_2,d);
  rotate_point(&x_3,&y_3,d);
}

void instruments::set_corners(
                    double sr,
                    double ll,
                    double lo
                    )
{
// staying consistent with the rotation/position sense for text..

 y_0 = -lo;
 y_1 = -lo;
 y_2 = lo;
 y_3 = lo;
 x_0 = sr;
 x_1 = sr+ll;
 x_2 = sr+ll;
 x_3 = sr;
}

void instruments::set_relative_to(
                    double x_orig,
                    double y_orig
                    )
{
 x_0+=x_orig;     y_0+=y_orig;
 x_1+=x_orig;     y_1+=y_orig;
 x_2+=x_orig;     y_2+=y_orig;
 x_3+=x_orig;     y_3+=y_orig;
}

void instruments::print_lines(
                    double x0,
                    double y0,
                    double x1,
                    double y1,
                    double x2,
                    double y2,
                    double x3,
                    double y3
                    )
{
// fprintf(fp,"-draw \"polyline %4.0f,%4.0f,%4.0f,%4.0f,%4.0f,%4.0f,%4.0f,%4.0f,%4.0f,%4.0f\" \\\n",x0,y0,x1,y1,x2,y2,x3,y3,x0,y0);
  sys_string += "-draw \"polyline ";
  sys_string += string_d(x0);
  sys_string += ",";
  sys_string += string_d(y0);
  sys_string += ",";
  sys_string += string_d(x1);
  sys_string += ",";
  sys_string += string_d(y1);
  sys_string += ",";
  sys_string += string_d(x2);
  sys_string += ",";
  sys_string += string_d(y2);
  sys_string += ",";
  sys_string += string_d(x3);
  sys_string += ",";
  sys_string += string_d(y3);
  sys_string += ",";
  sys_string += string_d(x0);
  sys_string += ",";
  sys_string += string_d(y0);
  sys_string += "\" \\\n";
}

void instruments::print_bezel_lines (
                    double width,
                    double height,
                    double r_start,
                    double length,
                    double hwidth,
                    double start_d,
                    double n_lines,
                    double delta_line
                    )
{
 double d;
 d=start_d;

 int n=0;
 for (n=0; n<n_lines; n++) {
   set_corners(r_start,length,hwidth);
   rotate_points(-d);
   set_relative_to((width/2.0)-1.0, (height/2.0)-1.0);

   print_lines(
               x_0,y_0,
               x_1,y_1,
               x_2,y_2,
               x_3,y_3
               );
   d+=delta_line;
  }
}
void instruments::print_bezel_lines_linear (
                    double x0,
                    double y0,
                    double width,
                    double height,
                    double dy,
                    int n
                    )
{
 double x = x0;
 double y = y0;

 int i=0;
 for (i=0; i<n; i++) {

   print_lines(
               x,y,
               x,y+height,
               x+width,y+height,
               x+width,y
               );
   y += dy;
  }
}

void instruments::print_n_scale_linear(
                    double x0,
                    double y0,
                    double dy,
                    int n,
                    int start_n,
                    int dn
                    )
{
 double x = x0;
 double y = y0;
 int cn = start_n;
 int i=0;
 for (i=0; i<n; i++) {

   sys_string +="-pointsize ";
   sys_string +=string_i(pointsize);
//   sys_string +=" -gravity Center -draw \"text   ";
   sys_string +=" -gravity North -draw \"text   ";
   sys_string += string_d(x);
   sys_string +="  ";
   sys_string +=string_d(y - pointsize/3);
   sys_string +=" '";
   sys_string +=string_i(cn);
   sys_string +="'\" \\\n";

   y += dy;
   cn += dn;
  }

}
void instruments::print_header_no_font(
                    double width,
                    double height
                    )
{
  sys_string +="convert -size ";
  sys_string += string_d(width);
  sys_string += "x";
  sys_string += string_d(height);
  sys_string +=" xc:none  -encoding None \\\n";
}

void instruments::print_header(
                    double width,
                    double height
                    )
{
 sys_string +="convert -size ";
 sys_string += string_d(width);
 sys_string +="x";
 sys_string +=string_d(height);
 sys_string +=" xc:none  -encoding None -font ";
 sys_string +=font;
 sys_string +=" \\\n";
}

void instruments::print_color(char *color)
{
  sys_string += "-fill ";
  sys_string += color;
  sys_string += " \\\n";
}

void instruments::end_file(char * fn)
{
//  sys_string += "-compress RLE SGI:";
  sys_string += fn;
  sys_string += ".png\n";
}

void instruments::generate_data_box(
                    double box_width,
                    double box_height,
                    double box_thick,
                    double box_x,
                    double box_y
                    )
{
  sys_string +="-fill darkgrey \\\n";
  sys_string +="-draw 'rectangle ";
  sys_string += string_d(box_x-1);
  sys_string +=", ";
  sys_string +=string_d(box_y);
  sys_string +=", ";
  sys_string +=string_d(box_x+box_width-1);
  sys_string +=", ";
  sys_string +=string_d(box_y+box_height);
  sys_string +="' \\\n";
  sys_string +="-fill black \\\n";

  sys_string +="-draw 'rectangle ";
  sys_string += string_d(box_x+box_thick-1);
  sys_string +=", ";
  sys_string += string_d(box_y+box_thick-1);
  sys_string +=", ";
  sys_string +=string_d(box_x+box_width-box_thick);
  sys_string +=", ";
  sys_string +=string_d(box_y+box_height-box_thick);
  sys_string +="' \\\n";
  sys_string +="-fill black \\\n";
}


