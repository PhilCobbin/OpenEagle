/***************************************************************
 * Name:      read_data.cxx
 * Purpose:   collection or read routines for reading faa's fixed line length text data files.
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2005
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

#include "read_data.hxx"

char tab_char = '\t';
char carriage_return_char ='\n';

char tc = '\t';
char tc2= '\n';

bool nextok(FILE* t)
{
  char tt;
  int status;
  status =feof(t);
  if (status!=0) return false;
  tt=fgetc(t);
  status=feof(t);
  tt=ungetc(tt,t);
 if (status!=0) return false; else return true;
}

char peek(FILE* t)
{
  char tt;
  char tback;
 // char tret;
  tt=fgetc(t);
  tback=tt;
  //tret=
  ungetc(tback,t);
  return tt;
}


void read_field(FILE * fp, char * f, int fs, char  d) {
  int i=0;
  char ch;
  f[0]=i=0;
  bool done =false;
  while (!done) {
    ch=fgetc(fp);
    if (ch != d) {
      if (i<=fs) f[i]=ch;
      i++;
      if (i<fs) f[i] ='\0';
    } else done=true;
  }
}

void skip_record(FILE * fp)
{
//  char ch;
  while (peek(fp)!='\n') {
    //ch=
    fgetc(fp);
  }
  //ch=
  fgetc(fp);
}

void set_field(char * data, char * field, int field_length, int offset)
{
  int i;
  for (i=0; i<field_length; i++) field[i] = data[i+offset];
  field[i]='\0';
}

void set_field_all_blank_null(char * data, char * field, int field_length, int offset)
{
  bool all_blank = true;
  int i;
  for (i=0; i<field_length; i++) {
    field[i] = data[i+offset];
    if (field[i] != ' ') all_blank = false;
  }
  field[i]='\0';
  if (all_blank) field[0] ='\0';
}


void set_field_no_trailing_blank(char * data, char * field, int field_length, int offset)
{
  int last_space;
  int sl;
  int i;
  for (i=0; i<field_length; i++) field[i] = data[i+offset];
  field[i]='\0';
  sl=i;
  last_space=sl-1;
  for (i=sl-1; i>0; i--) if (field[i]==' ') last_space=i; else i=0;
  field[last_space]='\0';
}

