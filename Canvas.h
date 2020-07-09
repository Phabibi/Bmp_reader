#include <wx/wx.h>
#include "bmp.h"

// Our canvas class

class Canvas: public wxPanel
{
  public:

        // Wav file 

        Bmp_reader bmp;

        //the file path for our .wav file
        std::string file_path;

        // Actual constructor for the frame window 
        Canvas(wxFrame* parent);

        //this is to draw our waves
        void Draw();

        //event to actually draw
        void paintEvent(wxPaintEvent& event);

        void paintNow();
        
        //render the drawings
        void render(wxDC& dc);

        DECLARE_EVENT_TABLE()



};
