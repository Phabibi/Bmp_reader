#include <wx/string.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/wx.h>
#include <wx/sizer.h>
#include "bmp.h"

// MainApp is the class for our application, it just acts
// as a container for the window or frame in MainFrame.

//Main window
class MainApp: public wxApp
{
public:
	virtual bool OnInit();
};


// MainFrame is the class for our window, it
// contains the window and all objects in it.
class MainFrame: public wxFrame
{
public:
	MainFrame( const wxString &title, const wxPoint &pos, const wxSize &size );

	void Quit( wxCommandEvent& event );
	void OpenFile(wxCommandEvent& event );

        void New_window();

	wxTextCtrl *MainEditBox;
	wxButton **Buttons;
	// The Path to the file we have open
	wxString CurrentDocPath;

	DECLARE_EVENT_TABLE()
};

enum
{
	// declares an id which will be used to call our button
	BUTTON_open = wxID_HIGHEST,
        BUTTON_close = BUTTON_open+1
};

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
	EVT_BUTTON(BUTTON_open, MainFrame::OpenFile)
	EVT_BUTTON(BUTTON_close, MainFrame::Quit)
END_EVENT_TABLE()
