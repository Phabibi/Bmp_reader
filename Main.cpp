#include <wx/wxprec.h>
#include <iostream>
#include <string>
#include <fstream>
#include <wx/wfstream.h>

#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

#include "base.h"
#include "Canvas.cpp"

IMPLEMENT_APP(MainApp) // Initializes the MainApp class...

bool MainApp::OnInit()
{
	// Create an instance of our frame, or window
	MainFrame *MainWin = new MainFrame(_("WAV File Opener")
                                           , wxPoint(30 , 30), wxSize(600, 400));
	MainWin->Show(); // show the window
	SetTopWindow(MainWin); // and finally, set it as the main window

	return TRUE;
}


MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame(nullptr, -1, title, pos, size)
{
        Buttons = new wxButton*[2];
        wxGridSizer *grid  = new wxGridSizer(2,2,0,0);
        //Create our buttons
        
        Buttons[0] = new wxButton(this,BUTTON_open, "Open File"); 
        Buttons[1] = new wxButton(this,BUTTON_open+1, "Quit"); 

        //add it to the grid

        grid->Add(Buttons[0],1,wxEXPAND|wxALL);
        grid->Add(Buttons[1],1,wxEXPAND|wxALL);

        this->SetSizer(grid);
        grid->Layout();

        

        cout << "dare mikeshe" << endl;


}

void MainFrame::OpenFile(wxCommandEvent& WXUNUSED(event))
{
        //opens a custom file exploarer that only opens *WAV files
	wxFileDialog *OpenDialog = new wxFileDialog(this, _("Choose a .BMP file to open"), wxEmptyString, wxEmptyString,("Text files (*.txt)|*.txt|BMP file (*.bmp)|*.bmp"),wxFD_OPEN, wxDefaultPosition);

            // if they pressed cancel, dont terminate the program
            if(OpenDialog->ShowModal() != wxID_OK)
            {
               return;
            }
            else
            {
              CurrentDocPath = OpenDialog->GetPath();
              const char* path  = CurrentDocPath.mb_str();

              //rip the const

              wxFrame* frame = new wxFrame(nullptr, -1,"WAV Fade_in _out", wxPoint(50,50), wxSize(2000,500));
              Canvas* canvas = new Canvas(reinterpret_cast<wxFrame*>(frame));
              //canvas->bmp.Reader(const_cast<char*>(path));

              //std::cout<<"i get here " << canvas->bmp.head.height << std::endl;
              canvas->file_path = CurrentDocPath;
              canvas->Draw();

            }

}
void MainFrame::Quit(wxCommandEvent& WXUNUSED(event))
{
	Close(TRUE); // Close the window
}
