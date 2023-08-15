/***************************************************************
 * Name:      OpenEagleAirportLookupApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Philip Cobbin (philcobbin@gmail.com)
 * Created:   2021-02-05
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

#include "OpenEagleAirportLookupApp.h"

//(*AppHeaders
#include "OpenEagleAirportLookupMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(OpenEagleAirportLookupApp);

bool OpenEagleAirportLookupApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	OpenEagleAirportLookupFrame* Frame = new OpenEagleAirportLookupFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
