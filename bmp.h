#pragma once
#include<iostream>
#include<vector> 
#include<string>
#include<cmath>

#define pi 3.1415926535

//#define Chrominance [ [17,18,24,47,99,99,99,99], [18,21,26,66,99,99,99,99],[24,26,56,99,99,99,99,99],[47,66,99,99,99,99,99,99],[99,99,99,99,99,99,99,99],[99,99,99,99,99,99,99,99],[99,99,99,99,99,99,99,99],[99,99,99,99,99,99,99,99]]

using namespace std;



#pragma pack(push, 1)//bmp header;

class Header
{
  public: 
     //Hader
     uint16_t signature;
     uint32_t filesize;
     uint32_t reserved1;
     uint32_t offset;
     
     //info Header
     uint32_t size;
     uint32_t width;
     uint32_t height;
     uint16_t planes;
     uint16_t bitsperpixel;
     uint32_t compression;
     uint32_t imgsize;
     uint32_t hres;
     uint32_t vres;
     uint32_t color;
     uint32_t icolor;

     //Color table
     uint8_t red;
     uint8_t green;
     uint8_t blue;
     uint8_t alpha;


     //rest is the raw pixle data;
};
#pragma pack(pop)

class ycbcr
{

  public: 
    uint32_t y;
    uint32_t cb;
    uint32_t cr;

    long double y_dct;
    long double cb_dct;
    long double cr_dct;

    ycbcr(uint32_t y,uint32_t cb,uint32_t cr){this->y = y; this->cb = cb; this->cr=cr;};
    ycbcr(long double y,long double cb,long double cr){this->y_dct = y; this->cb_dct=cb; this->cr_dct = cr;};
};
class rgb
{

  public: 
    int r;
    int g;
    int b;
    rgb(int r,int g,int b){this->r = r; this->g = g; this->b=b;};
};

class Bmp_reader
{
  public:

    //the header data
    Header head;


    //the data
    uint8_t* data;


    //reader / parser
    void Reader(char* path);

    /* Encode to IMG */
    vector<vector<rgb> > construct_DCT(uint8_t* data, uint32_t height, uint32_t width);
};



vector<vector<rgb> > Bmp_reader::construct_DCT(uint8_t* data, uint32_t height, uint32_t width)
{
  //we must convertg our array into chunks of 8;
  int counter = 0;
  vector< vector<uint32_t> > bit_map;

  vector<ycbcr> rgb_concat; 

  vector<ycbcr> cols(width,ycbcr((uint32_t)0,(uint32_t)0,(uint32_t)0));
  vector<vector<ycbcr> > rgb_vec(height,cols);

  vector<ycbcr> cols2(width,ycbcr((long double)0.0,(long double)0.0,(long double)0.0));
  vector<vector<ycbcr> > dct(height,cols2);

  for(int i = 0; i< height*width*3; i+=3)
  {
       uint8_t blue   = data[i];
       uint8_t green  = data[i+1];
       uint8_t red = data[i+2];

       uint32_t rgb; 
       uint32_t mask;

       uint32_t Y  = (uint32_t)( 0.299   * red + 0.587   * green + 0.114   * blue);
       uint32_t cb = (uint32_t)(-0.16874 * red - 0.33126 * green + 0.50000 * blue)+128;
       uint32_t cr = (uint32_t)( 0.50000 * red - 0.41869 * green - 0.08131 * blue)+128;

       //ALPHA
      // rgb = 0x11 | rgb;
      // rgb = rgb << 24;

      // //BLUE
      // rgb = blue | rgb;
      // rgb = rgb << 16;

      // //Green
      // mask = (mask | green);
      // mask = mask << 8;
      // rgb = rgb | mask;
      // mask = 0;

      // //RED
      // mask = (mask | red); 
      // rgb = rgb | mask;
      // mask = 0;
      ycbcr YCBCR= ycbcr(Y,cb,cr);
      rgb_concat.push_back(YCBCR);
  }
  //converted it to a 2D 

  for(int i = 0 ; i <height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      rgb_vec[i][j] = rgb_concat[i*width +j];
    }
  }
  for(int i = 0 ; i <height; i++)
  {
    for(int j = 0; j < width; j++)
    {
      dct[i][j].y=rgb_vec[i][j].y;
      dct[i][j].cb=rgb_vec[i][j].cb;
      dct[i][j].cr=rgb_vec[i][j].cr;
    }
  }

  //construct the cosine since its faster 
  vector<long double> cos_col(8,0.0);
  vector<vector<long double> > cosine(8,cos_col);
  vector<long double> ck(8,0.0);

  for(int i=0; i < 8;i++)
  {
    for(int j = 0; j< 8; j++)
    {

      cosine[i][j]=(long double)(cos((2*i+1)*j*acos(-1)/(2*8)));
      if(i)
      {
        ck[i] = (long double)1;
      }    
      else
      {
        ck[i] =(long double) (1/sqrt(2)); 
      }
    }
  
  }
  //split into and perform DCT;
  long double sumy = 0.0;
  long double sumcb = 0.0;
  long double sumcr = 0.0;

  for(int i = 0; i < height/8; i++)
  {
    for(int j = 0; j <width/8;j++)
    {
      // ci and cj depends on frequency as well as
      // number of row and columns of specified matrix
      for(int k = 0 ; k < 8 ; k++)
      {
        for(int h = 0; h < 8 ; h++)
        {
          sumy = 0;
          sumcb = 0;
          sumcr = 0;

          for(int x = 0; x < 8 ; x++)
          {
            for(int y = 0 ; y < 8 ; y++)
            {
                sumy += (long double)((rgb_vec[i*8+x][j*8+y].y) * cosine[x][k] * cosine[y][h]);
                sumcb += (long double)((rgb_vec[i*8+x][j*8+y].cb) * cosine[x][k] * cosine[y][h]);
                sumcr += (long double)((rgb_vec[i*8+x][j*8+y].cr) * cosine[x][k] * cosine[y][h]);
            }
          }
          sumy*=(long double)(ck[k]*ck[h]*0.25);
          sumcb*=(long double)(ck[k]*ck[h]*0.25);
          sumcr*=(long double)(ck[k]*ck[h]*0.25);


          dct[i*8+k][j*8+h].y_dct = sumy;
          dct[i*8+k][j*8+h].cb_dct = sumcb;
          dct[i*8+k][j*8+h].cr_dct = sumcr;
        }
      }
    }
  }
  // Quantization 
  
 vector<vector<long double>> Luminance {{16,11,10,16,24,40,51,61},{12,12,14,19,26,58,60,55},{14,13,16,24,40,57,69,56},{14,17,22,29,51,87,80,62},{18,22,37,56,68,109,103,77},{24,35,55,64,81,104,113,92},{49,64,78,87,103,121,120,101},{72,92,95,98,112,100,103,99}};
 vector<vector<long double>> Chrominance {{17,18,24,47,99,99,99,99},{18,21,26,66,99,99,99,99},{24,26,56,99,99,99,99,99},{47,66,99,99,99,99,99,99},{99,99,99,99,99,99,99,99},{99,99,99,99,99,99,99,99},{99,99,99,99,99,99,99,99},{99,99,99,99,99,99,99,99}};

  for(int i = 0; i < height/8; i++)
  {
    for(int j = 0; j < width/8;j++)
    {
      // ci and cj depends on frequency as well as
      // number of row and columns of specified matrix
      for(int k = 0 ; k < 8 ; k++)
      {
        for(int h = 0; h < 8 ; h++)
        {

          dct[i*8+k][j*8+h].y_dct = (long double) round(dct[i*8+k][j*8+h].y_dct+1/Luminance[k][h]);
          dct[i*8+k][j*8+h].cb_dct = (long double) round(dct[i*8+k][j*8+h].cb_dct+1/Chrominance[k][h]);
          dct[i*8+k][j*8+h].cr_dct = (long double) round(dct[i*8+k][j*8+h].cr_dct+1/Chrominance[k][h]);


          cout << " y : " << dct[i*8+k][j*8+h].y_dct << " CB " << dct[i*8+k][j*8+h].cb_dct << " CR " << dct[i*8+k][j*8+h].cr_dct << endl;

        }
      }
    }
  }




  //
  

  vector<rgb> rgb_c(width,rgb(0,0,0));
  vector<vector<rgb> > idct(height,rgb_c);

  sumy = 0.0;
  sumcb = 0.0;
  sumcr= 0.0;

  for(int i = 0; i < height/8; i++)
  {
    for(int j = 0; j <width/8;j++)
    {
      // ci and cj depends on frequency as well as
      // number of row and columns of specified matrix
      for(int k = 0 ; k < 8 ; k++)
      {
        for(int h = 0; h < 8 ; h++)
        {
          sumy = 0.0;
          sumcb = 0.0;
          sumcr = 0.0;

          for(int x = 0; x < 8 ; x++)
          {
            for(int y = 0 ; y < 8 ; y++)
            {
                sumy +=ck[x]*ck[y]* (dct[i*8+x][j*8+y].y_dct) * cosine[k][x] * cosine[h][y];
                sumcb +=ck[x]*ck[y]* (dct[i*8+x][j*8+y].cb_dct) * cosine[k][x] * cosine[h][y];
                sumcr +=ck[x]*ck[y]* (dct[i*8+x][j*8+y].cr_dct) * cosine[k][x] * cosine[h][y];
            }
          }
          sumy*=0.25;
          sumcb*=0.25;
          sumcr*=0.25;

          sumcr -= 128;
          sumcb -= 128;
          //where we lose most our shit
            
          int r = (int) sumy + 45 * (sumcr) / 32 ;
          int g = (int) sumy - (11 * (sumcb)  + 23 * (sumcr)) / 32 ;
          int b = (int) sumy + 113 * (sumcb)/ 64 ;
           if(r < 0)  r = 0;
           if(r > 255)  r = 255;
           if(g < 0)  g = 0;
           if(g > 255)  g = 255;
           if(b < 0)  b = 0;
           if(b > 255)  b = 255;


          idct[i*8+k][j*8+h].r = r;
          idct[i*8+k][j*8+h].g = g;
          idct[i*8+k][j*8+h].b = b;
        }
      }
    }
  }
  return idct;


}


void Bmp_reader::Reader(char* path)
{
   // start reading the header as a chunk
   //
    
   cout << "size of header is " << sizeof(Header) << endl;

   int head_len = sizeof(Header);


   FILE* file = fopen(path, "r");

   size_t read_head = fread(&this->head ,1, head_len , file);


   if(read_head <= 0)
   {
      cout << "couldnt read properly" << endl;
      return;
   }
   
   cout << "height s" <<  this->head.height << endl; 
   cout << "width s" <<  this->head.width << endl; 
   cout << "offset is : "<<this->head.offset << endl;

   fseek(file,this->head.offset,SEEK_SET);

   int width_stride = this->head.width*3;
   
   int size = 0;
  

   int offset = 4 - ((width_stride)%4);
   
   //we dont need to take padding into account
   if(offset  == 4)
   {
      offset = 0;
   }
   this->data = new uint8_t[this->head.width * this->head.height * 3 ];
   
   
   int padd = 0;
   for(int i = 0 ; i < this->head.height ; i++)
   {
     // need to pad right

     padd = i*(width_stride);

     read_head = fread(&this->data[padd] ,1, width_stride ,file);

   
     //go back to where you came from
     fseek(file,offset,SEEK_CUR);
   }


   cout << "file size " << this->head.size << endl;
   cout << "hrez" << this->head.hres << endl;

   fclose(file);
   cout << "file size " << this->head.size << endl;

};

