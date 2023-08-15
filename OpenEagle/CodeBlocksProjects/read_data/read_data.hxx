/***************************************************************
 * Name:      read_data.hxx
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
#ifndef READ_DATA_H
#define READ_DATA_H
#include <stdio.h>

extern  char tab_char;
extern  char carriage_return_char;
extern  char tc;
extern  char tc2;

bool nextok(FILE* t);
char peek(FILE* t);
void read_field(FILE * fp, char * f, int fs, char  d);
void skip_record(FILE * fp);
void set_field(char * data, char * field, int field_length, int offset);
void set_field_all_blank_null(char * data, char * field, int field_length, int offset);
void set_field_no_trailing_blank(char * data, char * field, int field_length, int offset);

#endif
