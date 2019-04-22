#include "object.h"
#include <GL/gl.h>
#include <iostream>

 //OBJECT BEGIN
void Object::drawBevel(unsigned int ot,unsigned int it,unsigned int ib,unsigned int ob)
{
    setGLColor(ot);
    glRectf(x0, y0, x1-1, y0+1);
    glRectf(x0, y0+1, x0+1, y1-1);
    setGLColor(ob);
    glRectf(x1-1, y0, x1, y1);
    glRectf(x0, y1-1, x1-1, y1);
    setGLColor(it);
    glRectf(x0+1, y0+1, x1-2, y0+2);
    glRectf(x0+1, y0+2, x0+2, y1-2);
    setGLColor(ib);
    glRectf(x1-2, y0+1, x1-1, y1-1);
    glRectf(x0+1, y1-2, x1-2, y1-1);
}
void Object::setGLColor(unsigned int c)
{
    float r = ((c >> 16)&0xff) / 255.0f;
    float g = ((c >> 8) & 0xff) / 255.0f;
    float b = (c & 0xff) / 255.0f;
    glColor3f(r,g,b);
}
bool Object::ptIn(int x , int y){
    return  x > x0 && x < x1 && y > y0 && y < y1;
};
Object& Object::operator=(const Object& s){
    return *this;
};

Object::Object(const Object& s){
};
Object::Object():x0(0),y0(0),x1(80),y1(40),
    d_pressed(false),d_redraw(true){
};
 //OBJECT END
