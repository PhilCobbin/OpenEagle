/***************************************************************
 * Name:      OpenEagle_flightgear_fixApp.h
 * Purpose:   Defines Application Class
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-07-11
 * Copyright: Philip Cobbin (www.cobbin.com)
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

#ifndef OPENEAGLE_FLIGHTGEAR_FIXAPP_H
#define OPENEAGLE_FLIGHTGEAR_FIXAPP_H

#include <wx/app.h>

class OpenEagle_flightgear_fixApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // OPENEAGLE_FLIGHTGEAR_FIXAPP_H
