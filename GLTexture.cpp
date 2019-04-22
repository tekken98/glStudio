#include "GLTexture.h"
#include "loadfile.h"

//GLTEXTURE BEGIN
void GLTexture::setTexture(const char * key)
{
    glBindTexture(GL_TEXTURE_2D,d_texture[key]);
}
GLuint GLTexture::getTexture(const char * key)
{
    return d_texture[key];
}
void GLTexture::loadTexture(const char * filename,const char* key)
{
    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    jpegImage img(filename);
    int w = img.getWidth();
    int h = img.getHeight();
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,img.getBuf());
    //glTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGBA,w,h,0,GL_BGRA,GL_UNSIGNED_BYTE,img.getBuf());
    glGenerateMipmap(GL_TEXTURE_2D);

    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    d_texture.insert(make_pair(key,texture));
}
GLTexture::~GLTexture()
{
}
GLTexture& GLTexture::operator=(const GLTexture& s)
{
    return *this;
}
GLTexture::GLTexture(const GLTexture& s)
{
}
GLTexture::GLTexture()
{
}
//GLTEXTURE END
