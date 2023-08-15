/***************************************************************
 * Name:      OpenEagle_flightgear_aptApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Philip Cobbin (phil@cobbin.com)
 * Created:   2023-07-12
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

#include "OpenEagle_flightgear_aptApp.h"

//(*AppHeaders
#include "OpenEagle_flightgear_aptMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(OpenEagle_flightgear_aptApp);

bool OpenEagle_flightgear_aptApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	OpenEagle_flightgear_aptFrame* Frame = new OpenEagle_flightgear_aptFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
