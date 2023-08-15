/***************************************************************
 * Name:      OpenEagleExt.cxx
 * Purpose:   read/write extended data integrated from data sources by flightgear
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2023-06-21
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

#include "data_mgr.hxx"
#include <math.h>
#include "../3rdparty/constants.h"

bool data_mgr::OpenOpenEagleExtFile(std::string path, std::string filename)
{
  std::string full_filename = path;
  full_filename+= filename;
  OpenEagleExtfp = fopen(full_filename.c_str(),"rb");
  if (OpenEagleExtfp==NULL) {
    return false;
  }
  return true;
}
void data_mgr::SendOpenEagleExtProtocol()
{
  bool done = false;
  int OpenEagleExtSize = sizeof(OpenEagleExt);
  printf("OpenEagleExtSize %d\n",OpenEagleExtSize);
  while (!done) {;
    int nread = fread(&OpenEagleExt,sizeof(OpenEagleExt),1,OpenEagleExtfp);
    ///printf("nread %d\n",nread);
    if (nread == 1) {
      int io_ret = 0;
      io_ret = write(OpenEagleExtsockfd,&OpenEagleExt,sizeof(OpenEagleExt) );
      if (io_ret < OpenEagleExtSize) {
         printf(" flightgear session ended: socket failure io_ret %d\n",io_ret);
         close(OpenEagleExtsockfd);
         done = true;
      } else {
        //printf(" socket successful\n");
        /// 10 hz update rate
        struct timespec ts;
        ts.tv_sec = 0;
        //// tv_nesec range: 0 to
        ///           999999999
        ts.tv_nsec =  499999999;
        ts.tv_nsec = nsec_speeds[PlayBackSpeed];
        nanosleep(&ts, NULL);
      }
    }
    else {
      printf("EOF on flight history\n");
      done = true;
    }
  }
  fclose(OpenEagleExtfp);
}
void data_mgr::initOpenEagleExt()
{
  PlayBackSpeed = 2;
}
