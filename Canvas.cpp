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
      //
      Canvas* canvas = new Canvas(reinterpret_cast<wxFrame*>(frame));
      const char * filepath = this->file_path.c_str();
      canvas->bmp.Reader(const_cast<char*>(filepath));
      
      // making the new scroll frame

      frame->Show();
}
//painting event
BEGIN_EVENT_TABLE(Canvas, wxPanel)

      EVT_PAINT(Canvas::paintEvent) END_EVENT_TABLE()

void Canvas::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}


void Canvas::render(wxDC&  dc)
{
    // draw some text
     
    
    wxBrush brush;
    //construct image matri
   vector<vector<rgb> > rgb_vec = this->bmp.construct_DCT(this->bmp.data,this->bmp.head.height, this->bmp.head.width);

    for(int i = 0; i < this->bmp.head.height*this->bmp.head.width*3; i+=3)
    {
           uint8_t blue = this->bmp.data[i];
           uint8_t green = this->bmp.data[i+1];
           uint8_t red= this->bmp.data[i+2];
           uint32_t rgb; 
           uint32_t mask;
           //ALPHA
           int Y  = (int)( 0.299   * red + 0.587   * green + 0.114   * blue);
           int cb = (int)(-0.16874 * red - 0.33126 * green + 0.50000 * blue)+128;
           int cr = (int)( 0.50000 * red - 0.41869 * green - 0.08131 * blue)+128;

   //        cout << "y: " << Y << " cb: "<<cb << " cr: " << cr << endl;  
           
           cb = cb - 128;
           cr = cr - 128;
           int r = (int) Y + 45 * (cr) / 32 ;
           int g = (int) Y - (11 * (cb)  + 23 * (cr)) / 32 ;
           int b = (int) Y + 113 * (cb)/ 64 ;

           if(r < 0)  r = 0;
           if(r > 255)  r = 255;
           if(g < 0)  g = 0;
           if(g > 255)  g = 255;
           if(b < 0)  b = 0;
           if(b > 255)  b = 255;


           dc.SetPen( wxPen( wxColor(red,green,blue), 2 ) ); // 10-pixels-thick pink outline


           float pad = (float)i/3.0;
           uint32_t x = (uint32_t) pad % this->bmp.head.width;
           uint32_t y = (uint32_t) pad / this->bmp.head.width;

           dc.DrawRectangle(x,this->bmp.head.height - y ,2,2);
      
    }

   cout << rgb_vec[0].size() << endl;
   for(int i = 0 ; i < rgb_vec.size()-3 ; i++)
   {
     for(int j = 0; j < rgb_vec[i].size()-3; j++)
     {
          dc.SetPen( wxPen( wxColor(rgb_vec[i][j].r,rgb_vec[i][j].g,rgb_vec[i][j].b), 2 ) );
          dc.DrawRectangle(j+this->bmp.head.width + 100, this->bmp.head.height-i,1,1);
     }
   }


   // for(int i = 0; i < this->bmp.head.height*this->bmp.head.width*3; i+=3)
   // {
   //        uint8_t blue = this->bmp.data[i];
   //        uint8_t green = this->bmp.data[i+1];
   //        uint8_t red= this->bmp.data[i+2];

   //        dc.SetPen( wxPen( wxColor(red,green,blue), 2 ) ); // 10-pixels-thick pink outline


   //        float pad = (float)i/3.0;
   //        uint32_t x = (uint32_t) pad % this->bmp.head.width;
   //        uint32_t y = (uint32_t) pad / this->bmp.head.width;

   //        dc.DrawRectangle(x+this->bmp.head.width + 500 ,this->bmp.head.height - y ,2,2);
   //   
   // }
          
}

