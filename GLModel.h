#ifndef GLMODEL_H
#define GLMODEL_H
#define GL_GLEXT_PROTOTYPES
#include <lib3ds/file.h>
#include <lib3ds/mesh.h>
#include <lib3ds/node.h>
#include <lib3ds/vector.h>
#include <lib3ds/types.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
struct Vertex {
    GLfloat x,y,z,s,t;
    GLfloat nx,ny,nz;
};
class GLModel
{
    private:
        Lib3dsFile * d_file=NULL;
        std::vector<Vertex> d_vertex;
        Vertex * d_p=NULL;
        GLuint d_VAO;
        GLuint d_size;
        std::vector<GLuint> d_texture;
        GLfloat d_pos[3];
    public:
        //constructor
        GLModel(const char* filename);
        GLModel(const GLModel& s);
        GLModel& operator=(const GLModel& s);
        ~GLModel();
    public:
        //maniulator
        void load(const char * filename);
        void pushVertex(Lib3dsVector& v,Lib3dsVector& nv,int i);
        void loadNode(Lib3dsNode *node);
        void bind();
        void loadModel();
        void drawModel();
        void offsetTo(GLfloat x , GLfloat y, GLfloat z);
        //accessor
        //
        GLfloat * getVertex();
        GLuint getSize();
};
#endif

