#ifndef COMMON_H
#define COMMON_H
#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
typedef struct _vec4 {
    union{
        GLfloat v[4];
        GLfloat x,y,z,w;
    };
    operator GLfloat* (){
        return &v[0];
    }
} vec4;
 typedef struct _vec3 {
    union{
        GLfloat v[3];
        GLfloat x,y,z;
    };
    operator GLfloat* (){
        return &v[0];
    }
} vec3;
              
#define RGB(r,g,b) ((r<<24) & (b << 16) & (b << 8)) 
#define SAME(a,b) (is_same<a,b>::value)
using namespace std;
    template <typename T>
void msg (T m) 
{
    std::cout << m; 
}
void _init(vec4& v,GLuint u);
enum
{
    UI_COLOR_PANEL = 0xc0c0c0,
    UI_COLOR_BUTTON = 0xc0c0c0,
    UI_COLOR_SCROLLBAR = 0xdfdfdf,
    UI_COLOR_TEXT_BG = 0xffffff,
    UI_COLOR_TEXT_FG = 0x000000,
    UI_COLOR_TEXT_SEL_BG = 0x000080,
    UI_COLOR_TEXT_SEL_FG = 0xffffff,
    UI_COLOR_BEVEL_1 = 0x000000,
    UI_COLOR_BEVEL_2 = 0x808080,
    UI_COLOR_BEVEL_3 = 0xdfdfdf,
    UI_COLOR_BEVEL_4 = 0xffffff,
};
#endif
