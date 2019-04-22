#include "font.h"
#include <GL/gl.h>
#include <assert.h>
#include <string>

//FONT BEGIN
Font::Font(FT_String * FontFile)
{
    FT_Open_Args args;
    args.flags = FT_OPEN_PATHNAME;
    args.pathname =FontFile;
    FT_Error err  = FT_Init_FreeType(&d_lib);
    assert(err == 0);
    err = FT_Open_Face(d_lib,&args,0,&d_face);
    assert(err == 0);
}
Font::~Font()
{
    FT_Done_Face(d_face);
    FT_Done_FreeType(d_lib);
}

Font& Font::operator=(const Font& s)
{
    return *this;
};

void Font::drawChar(int x,int y,unsigned short c)
{
    int code;
    int err;
    float x0 = x;
    float y0 = y;
    float wd;
    wd = 1;

    code = FT_Get_Char_Index(d_face, c);
    err = FT_Set_Char_Size(d_face,64*25,64*25,64,64);
    assert(err ==0);
    err = FT_Load_Glyph(d_face,code,FT_LOAD_NO_HINTING);
    assert(err ==0);
    err = FT_Render_Glyph(d_face->glyph,FT_RENDER_MODE_NORMAL);
    assert(err ==0);
    FT_Bitmap * pBitmap = &d_face->glyph->bitmap;
    assert(err == 0);
    d_curwidth = pBitmap->width > 0 ? pBitmap->width:10;
    d_curheight = pBitmap->rows > 0 ? pBitmap->rows:10;
    d_curwidth *= wd;

    switch (c)
    {
        case 'g':
        case 'j':
        case 'p':
        case 'q':
        case 'y':
            y0 += d_curheight / 4 ;
            break;
    }
    for (int i=pBitmap->rows - 1 ;i >= 0; i-- )
    {
        for (unsigned int j = 0; j < pBitmap->width; j++)
        {

            int c =  (pBitmap->buffer[i * pBitmap->width + j] & 0xff);
            float cc = 1.0 -  c / 255.0;
            if (cc < 0.8)
            {
                glColor3f(cc,cc,cc);
                glRectf(x0,y0,x0+wd,y0+wd);
            }
            x0+=wd;
        }
        x0 = x;
        y0 -= wd;
    }
}

//FONT END
