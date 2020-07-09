#include <wx/wx.h>
#include <wx/sizer.h>
#include "Canvas.h"

Canvas::Canvas(wxFrame* parent) :
wxPanel(parent)
{
}

void Canvas::Draw()
{

      wxFrame* frame = new wxFrame(nullptr, -1,"WAV Fade_in _out", wxPoint(50,50), wxSize(2000,500));

      //sets up the canvas frame
      Canvas* canvas = new Canvas(reinterpret_cast<wxFrame*>(frame));
      canvas->file_path = this->file_path;
      canvas->bmp = this->bmp;
      
      // making the new scroll frame


      frame->Layout();
      frame->Show();
}
//painting event
BEGIN_EVENT_TABLE(Canvas, wxPanel)

      EVT_PAINT(Canvas::paintEvent)

END_EVENT_TABLE()

void Canvas::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}
void Canvas::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}


void Canvas::render(wxDC&  dc)
{
    // draw some text
     
    wxBrush brush;
    
    //construct image matrix

          brush.SetColour(255,255,255);
          dc.SetBrush(brush);
          dc.DrawRectangle(this->bmp.head.height , this->bmp.head.width,3,3);
          


    //2000x300 window
    //
    //
    
    //dc.SetBrush(*wxGREEN_BRUSH); // green filling
    //dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // 5-pixels-thick red outline
    //int samples2=0;
    //
    // wxFile file(this->file_path);
    // char sample[128];

    // //12 bytes of RIF header
    // char RIFBuffer[12];
    // //24 bytes FMT 
    // char FMTBuffer[24];
    // //6 bytes of Data
    // char DATABuffer[6];

    // file.Read(RIFBuffer, 12);
    // file.Read(FMTBuffer, 24);
    // file.Read(DATABuffer, 6);
    // // seek the next 42 bytes since thats our actual data
    // file.Seek(42);
    // int i= 0;
    // int k =1;
    // std::vector<int> buffer;

    // while(!file.Eof())
    // {
    //    std::cout<< "k is : "<< k <<std::endl;
    //    std::cout<< "i is : "<< i <<std::endl;
    //    file.Read(sample,2); 
    //    int samples=reinterpret_cast<char>(sample[k]);
    //    k++;
    //    //scale
    //    buffer.push_back(samples*2);
    //    i+=1200;
    //    //dc.DrawLine(i/4,samples2*2+500,(i+1)/4,samples*2+500);
    //  }
    // std::cout <<"i made it out:";

    // for(int i = 0 ; i < buffer.size(); i += 1200)
    // {
    //    dc.DrawLine(i/4,buffer[i]+500,(i+1)/4,buffer[i]+500);
    // }

    // draw some text
    //dc.DrawText(this->file_path, 40, 60);

    //// draw a circle
    //dc.SetBrush(*wxGREEN_BRUSH); // green filling
    //dc.SetPen( wxPen( wxColor(255,0,0), 5 ) ); // 5-pixels-thick red outline
    //dc.DrawCircle( wxPoint(200,100), 25 /* radius */ );

    //// draw a rectangle
    //dc.SetBrush(*wxBLUE_BRUSH); // blue filling
    //dc.SetPen( wxPen( wxColor(255,175,175), 10 ) ); // 10-pixels-thick pink outline
    //dc.DrawRectangle( 300, 100, 400, 200 );

    //// draw a line
    //dc.SetPen( wxPen( wxColor(0,0,0), 3 ) ); // black line, 3 pixels thick
    //dc.DrawLine( 300, 100, 700, 300 ); // draw line across the rectangle

    // Look at the wxDC docs to learn how to draw other stuff
}

