#ifndef GLTEXTURE_H
#define GLTEXTURE_H
#include <map>
#include "common.h"
class GLTexture
{
    private:
        map<const char * , GLuint> d_texture;
    public:
        //constructor
        GLTexture();
        GLTexture(const GLTexture& s);
        GLTexture& operator=(const GLTexture& s);
        ~GLTexture();
    public:
        //maniulator
        void loadTexture(const char * filename,const char* key);
        //accessor
        GLuint getTexture(const char * key);
        void setTexture(const char * key);
};
#endif

