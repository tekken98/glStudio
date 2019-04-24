//TRAITS
// void on_special(int key,int cx, int cy)
// int main(int argc , char** argv)
// void do_draw()
// void init2()
// void loadTexture()
// void msgln(T m)
// void on_display()
// void on_mouse(int button,int action,int x, int y)
// void on_time(int timer_id)
// void pushVertex(GLfloat x,GLfloat y, GLfloat z, GLfloat r,GLfloat s)
// void pushVertex(texturePos& p)
// void reload()
//GLfloat * getVertex(int & size)
//no use
//void managerWidget()
//
//void on_btn(Object* o)
#define GL_GLEXT_PROTOTYPES
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include "button.h"
#include "common.h"
#include "loadfile.h"
#include "GLProgram.h"
#include "GLModel.h"
#include "GLTexture.h"
#if __version__ < 120
using namespace std;
    template <typename T>
void msgln(T m)
{
    cout << m << endl;
}
typedef void (* FUN)(Object*);
//Global

GLuint gFlagLoc;
GLuint gFlag = 0;
GLuint VAOs[2];
GLuint BUFs[2];
vector<Object*> g_Obj;
vector<Object*> g_redrawObj;
map<Object*,FUN> g_Func;
GLProgram gProgram;
GLModel gModel("1.3ds");
GLModel gModelBall("2.3ds");
GLTexture gTexture;

//Font f((FT_String*)"NotoSansCJK-Medium.ttc");
bool gReloadNeeded = false;
void on_display();
void do_draw();
void loadTexture();
struct texturePos {
    GLfloat x,y,z;
    GLfloat r,s;
    GLfloat nx,ny,nz;
};

vector<texturePos> gTexturePos;
GLfloat * getVertex (int & size){
    int c = gTexturePos.size();
    size = c;
    texturePos* p = (texturePos*) new char [sizeof(texturePos) * (c+1)] ;
    int i = 0;
    for (auto a : gTexturePos)
    {
        p[i++] =  a;
    }
    return (GLfloat*)p;
}
void pushVertex(texturePos& p)
{
    gTexturePos.push_back(p);
}
void pushVertex(GLfloat x,GLfloat y, GLfloat z,
        GLfloat r,GLfloat s){
    texturePos p;
    p.x = x;
    p.y = y;
    p.z = z;
    p.r = r;
    p.s = s;
    p.nx = x;
    p.ny = y;
    p.nz = 1;
    pushVertex(p);
}
void managerWidget(){
    int x ,y ;
    x =0,y=0;
    int w ,h;
    for (auto a:g_Obj)
    {
        a->moveWindow(x,y);
        a->getSize(w,h); 
        x += w + 2;
        if ( x > 800)
        {
            x = 0;
            y += h + 2;
        }
    }
}
void on_btn(Object* o){
    cout << "good" << o << endl;
}
void on_special(int key,int cx, int cy)
{
    GLfloat step = 0.05f;
    GLfloat x=0;
    GLfloat y=0;
    switch (key){
        case GLUT_KEY_UP: y += step;break;
        case GLUT_KEY_DOWN: y -= step;break;
        case GLUT_KEY_LEFT: x -= step;break;
        case GLUT_KEY_RIGHT:  x+= step;break;
    }
    y = y < -1.0f ? -1 + 2 * step : y;
    y = y > 1.0f ? 1 - 2 * step : y;
    x = x > 1.0f ? 1 - 2 * step : x;
    x = x < -1.0f ? -1 + 2 * step : x;
    gModelBall.offsetTo(x,y,0);
    do_draw();
}
void on_mouse(int button,int action,int cx, int cy)
{
GLfloat step = 0.01f;
    GLfloat z=0;
    switch (action){
        case GLUT_UP: z += step;break;
    }
    gModelBall.offsetTo(cx/800,cy/600,z);
    do_draw();
}

const char * textureFile[][2] = {
    {"a.jpg","draw"},
    {"b.jpg","ball"},
    {"c.jpg","fish"},
    {"d.jpg","black"}
};

void reload()
{
    glutPostRedisplay();

}
void on_time(int timer_id)
{
    do_draw();
    glutTimerFunc(1000/10,on_time,0);
}
void init2()
{
    loadTexture();

    ShaderInfo shader[] = { 
        {GL_VERTEX_SHADER,"triangles.vert"},
        {GL_FRAGMENT_SHADER,"triangles.frag"},
        {GL_NONE,NULL}};
    gProgram.loadProgram(shader);
    gProgram.bindUniform("v4Color");
    gProgram.bindUniform("v4vColor");
    gProgram.bindUniform("v3Dir");
    vec3 l = {0,-1,0};
    gProgram.setUniform("v3Dir",l);
   //left 
    for (int i = 0; i< 60.0f;i+= 10.0f)
    {
        pushVertex(-1.0,1.0,i, 0,0);
        pushVertex(-1.0,1.0,i + 10.0, 1,0);
        pushVertex(-1.0,-1.0,i + 10.0, 1,1);
        pushVertex(-1.0,-1.0,i, 0,1);
    }
    //right
    for (int i = 0; i< 60.0f;i+= 10.0f)
    {
        pushVertex(1.0,1.0,i + 10.0, 0,0);
        pushVertex(1.0,1.0,i , 1,0);
        pushVertex(1.0,-1.0,i , 1,1);
        pushVertex(1.0,-1.0,i+ 10.0, 0,1);
    }
    //top
    for (int i = 0; i< 60.0f;i+= 10.0f)
    {
        pushVertex(-1.0,1.0,i + 10.0, 0,0);
        pushVertex(-1.0,1.0,i , 1,0);
        pushVertex(1.0,1.0,i , 1,1);
        pushVertex(1.0,1.0,i+ 10.0, 0,1);
    }
    //bottom
    for (int i = 0; i< 60.0f;i+= 10.0f)
    {
        pushVertex(-1.0,-1.0,i + 10.0, 0,0);
        pushVertex(1.0,-1.0,i+ 10.0, 0,1);
        pushVertex(1.0,-1.0,i , 1,1);
        pushVertex(-1.0,-1.0,i , 1,0);
    }
        pushVertex(1.0,1.0,60.0, 0,0);
        pushVertex(1.0,-1.0,60.0, 0,1);
        pushVertex(-1.0,-1.0,60 , 1,1);
        pushVertex(-1.0,1.0,60 , 1,0);
    int size;
    GLfloat * quad_data=getVertex(size); 

    // Create and initialize a buffer object
    glGenVertexArrays(1,VAOs);
    glBindVertexArray(VAOs[0]);

    glGenBuffers(1, &BUFs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, BUFs[0]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat) * 8 * size, quad_data,GL_STATIC_DRAW);


    delete [] quad_data;
    //glBindVertexArray(VAOs[0]);
    // Setup vertex attributes

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) , (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) ,
            (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) ,
            (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);


    gModel.loadModel();
    gModel.bind();

    gModelBall.loadModel();
    gModelBall.bind();


    // Ready. Draw.
    glViewport(0,0,800,600);
    gluPerspective(45,0.5,.1,1000);
    gluLookAt(0,0,0,0,0,1000, 0,1,0);
}

void loadTexture()
{
    int size = sizeof(textureFile) / (sizeof(char*) * 2);
    for (int i =0; i < size;i ++)
    {
       gTexture.loadTexture(textureFile[i][0],textureFile[i][1]);
    }
}
void do_draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glBindVertexArray(VAOs[0]);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH);
    glEnable(GL_POLYGON_SMOOTH);
   // glLoadIdentity().; 

    gProgram.setUniform("v4vColor",0xaaaaaaaa);
    //gProgram.setUniform("v4Color",0x88888888);
    gTexture.setTexture("draw");
    for (int i = 0;i < 12;i++)
    {
        glDrawArrays(GL_TRIANGLE_FAN,i*4,4);
    }
   gTexture.setTexture("ball");
    for (int i = 12;i < 24;i++)
    {
        glDrawArrays(GL_TRIANGLE_FAN,i*4,4);
    }
    
   gTexture.setTexture("fish");
    glDrawArrays(GL_TRIANGLE_FAN,24*4,4);
    static float z = 1;
    static float i = 1;
    if (z>60)
        i= -1;
    if (z<0)
        i = 1;
    z += i;

    glPushMatrix();
    gProgram.setUniform("v4Color",0x0000ffff);
    //gTexture.setTexture("fish");
    glTranslatef(.2,.5,15);
    //glTranslatef(1-z /30,.1,60-z);
    gModelBall.drawModel();
    glPopMatrix();

    glPushMatrix();
    gProgram.setUniform("v4Color",0x00ff00ff);
    gTexture.setTexture("fish");
    //glTranslatef(0,.4,z*2- 60);
    glTranslatef(0,-.2,5);
    gModelBall.drawModel();
    glPopMatrix();
    string a;
    {
    glPushMatrix();
    glTranslatef(-.5,.5,3);
    //glTranslatef(0,0,z);
    gProgram.setUniform("v4Color",0xff0000ff);
    gTexture.setTexture("draw");
    gModelBall.drawModel();
    glPopMatrix();
    }
    reload();
}
void on_display()
{
    glutSwapBuffers();
}
int main(int argc , char** argv)
{
    glutInit(&argc,argv);
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("good");
    glutDisplayFunc(on_display);
    glutMouseFunc(on_mouse);
    glutSpecialFunc(on_special);
    glutTimerFunc(50,on_time,0);
    GLenum err = glewInit();
    if (GLEW_OK != err){
        printf("GLEW Error:%s\n",glewGetErrorString(err));
        return 1;
    }
    init2();
    glutMainLoop();
    return 0;
}
#endif
