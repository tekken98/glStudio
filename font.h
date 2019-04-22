#ifndef FONT_H
#define FONT_H
#include<ft2build.h>
#include FT_FREETYPE_H
#include FT_OUTLINE_H
#include <mupdf/fitz.h>
#include "common.h"

class Font{
    private:
        FT_Library d_lib;
        FT_Face d_face;
        int d_curwidth;
        int d_curheight;
    public:
        //constructor
        Font(FT_String * FontFile);
        Font(const Font& s);
        Font& operator=(const Font& s);
        ~Font();
    public:
        //maniulator
        void drawChar(int x,int y,unsigned short c);
        template<typename T>
            void drawString(int x , int y, T * s)
            {
                string ss (s);
                drawString(x,y,ss);
            }
        template<typename T>
            void drawString(int x , int y , T s)
            {
                int x0 = x;
                int y0 = y;
                d_curwidth = 0;
                const char * c =NULL;
                int ucs = 0xff;
                const char * p = s.c_str();

                int size = s.size();
                c = p + size;
                while(p < c)
                {
                        p += fz_chartorune(&ucs,(const char*)p);
                        drawChar(x0,y0,ucs);
                        x0 += d_curwidth;
                }
            }
        //accessor
}; 
#endif
