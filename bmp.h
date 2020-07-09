#pragma once
#include<iostream>
#include<vector> 
#include<string>

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

class Bmp_reader
{
  public:

    //the header data
    Header head;


    //the data
    uint8_t* data;


    //reader / parser
    void Reader(Header head , char* path);
};


void Bmp_reader::Reader(Header head , char* path)
{
   // start reading the header as a chunk
   //
    
   cout << "size of header is " << sizeof(Header) << endl;

   int head_len = sizeof(Header);


   FILE* file = fopen(path, "r");

   size_t read_head = fread(&head ,1, head_len , file);


   if(read_head <= 0)
   {
      cout << "couldnt read properly" << endl;
      return;
   }
   
   cout << "height s" <<  head.height << endl; 
   cout << "width s" <<  head.width << endl; 
   /*Start reading the data*/ 
   
   // data in bytes width*height*bitsperpixle / 8       
   // padding the data 
   //

   //stop here
   //

   fseek(file,head.offset,SEEK_SET);

   int width_stride = head.width*3;
   
   int size = 0;
  

   //pad
   //

   // 4 - for half a byte
   int offset = 4 - ((width_stride)%4);
   
   //we dont need to take padding into account
   if(offset  == 4)
   {
      offset = 0;
   }
   this->data = new uint8_t(head.width * head.height * 3 );
   
   
   int padd = 0;
   for(int i = 0 ; i <= head.height ; i++)
   {
     // need to pad right

     padd = i*(width_stride);

     read_head = fread(this->data + padd ,1, width_stride ,file);
   
     //go back to where you came from
     fseek(file,offset,SEEK_CUR);
     cout << "padding" << endl;
   }


   cout << "file size " << head.size << endl;
   cout << "hrez" << head.hres << endl;

   fclose(file);

};

