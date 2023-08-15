#ifndef FILEDIALOGSELECTFLIGHTHISTORY_H
#define FILEDIALOGSELECTFLIGHTHISTORY_H

//(*Headers(FileDialogSelectFlightHistory)
#include <wx/dialog.h>
//*)

class FileDialogSelectFlightHistory: public wxDialog
{
	public:

		FileDialogSelectFlightHistory(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~FileDialogSelectFlightHistory();

		//(*Declarations(FileDialogSelectFlightHistory)
		//*)

	protected:

		//(*Identifiers(FileDialogSelectFlightHistory)
		//*)

	private:

		//(*Handlers(FileDialogSelectFlightHistory)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
