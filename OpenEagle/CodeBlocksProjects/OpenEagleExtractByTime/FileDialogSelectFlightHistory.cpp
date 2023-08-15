#include "FileDialogSelectFlightHistory.h"

//(*InternalHeaders(FileDialogSelectFlightHistory)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(FileDialogSelectFlightHistory)
//*)

BEGIN_EVENT_TABLE(FileDialogSelectFlightHistory,wxDialog)
	//(*EventTable(FileDialogSelectFlightHistory)
	//*)
END_EVENT_TABLE()

FileDialogSelectFlightHistory::FileDialogSelectFlightHistory(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(FileDialogSelectFlightHistory)
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	//*)
}

FileDialogSelectFlightHistory::~FileDialogSelectFlightHistory()
{
	//(*Destroy(FileDialogSelectFlightHistory)
	//*)
}

