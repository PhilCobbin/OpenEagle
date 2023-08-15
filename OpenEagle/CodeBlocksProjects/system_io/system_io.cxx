/***************************************************************
 * Name:      system_io.cxx
 * Purpose:   manage system calls.
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
#include "../system_io/system_io.hxx"
#include <errno.h>
bool system_io(std::string* command)
{
  int sys_ret;
  sys_ret = system(command->c_str());
  if (sys_ret==-1) {
    printf("system command failed for string [%s]; errno set to %d\n)\n",command->c_str(),errno);
    //string lookup = "errno ";
    //lookup += to_string(errno);

    return false;
  }
  return true;
}

double read_write_dbl_as_string(std::string* path, std::string* filename, std::string * ext)
{
  std::string command_str = "mkdir -p ";
  command_str += path->c_str();
  command_str += "\n";
  bool path_test = system_io(&command_str);
  if (path_test == false) {
    printf("read_write_double_as_string( [%s], [%s], [%s] ) failed\n",path->c_str(), filename->c_str(),ext->c_str());
    exit(1);
  }
  std::string ffn = path->c_str();
  ffn += "/";
  ffn += filename->c_str();
  ffn += ".";
  ffn += ext->c_str();

  FILE * fp;
  fp = fopen(ffn.c_str(),"r");
  if (fp != NULL) {
    std:: string double_string = "";
    bool eol=false;
    while (!eol) {
      char test = fgetc(fp);
      if (test != '\n') double_string += test;
      else eol=true;
        //   printf("        double_string [%s]\n",double_string.c_str());
    }
    double read_double = stod(double_string,NULL);
    fclose(fp);
    return read_double;
  }
  else {
    fp = fopen(ffn.c_str(),"w++");
    if (fp != NULL) {
      fprintf(fp,"0.0\n");
      fclose(fp);
      return 0.0;
    }
    else {
      printf("unable to open [%s] to write 0.0 double\n",ffn.c_str());
      exit(1);
    }
  }
}
