#ifndef GLPROGRAM_H
#define GLPROGRAM_H
#define GL_GLEXT_PROTOTYPES
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <map>
#include "common.h"
struct ShaderInfo
{
    GLuint d_type;
    const char * filename;
};
class GLProgram
{
    private:
        GLuint d_program;
        GLuint d_unicolor;
        map<const char *,GLuint> d_location;
    public:
        //constructor
        GLProgram();
        GLProgram(const GLProgram& s);
        GLProgram& operator=(const GLProgram& s);
        ~GLProgram();
    public:
        //maniulator
        void bindUniform(const char *name);
        void setUniform(const char *name ,GLuint value);
        template <typename T> 
            void setUniform(const char *name ,T& value);
        //accessor
        GLuint getProgram();
        GLint getUniformLocation(const char * name);
        char ** loadProgramFile(const char * filename,int & lines);
        void loadProgram(ShaderInfo* info);
        GLuint loadShader(GLuint type,const char * filename);
        bool checkShader(GLuint shader);
        bool checkLink();
        operator GLuint()
        {
            return d_program;
        }
};
//GLPROGRAM BEGIN
template <typename T> void GLProgram::setUniform(const char *name ,T& value)
{
    if (is_same<T,vec3>::value) {
        GLuint loc = d_location[name];
        glUniform3fv(loc,1,value);
        //cout << "vec3 " <<endl;
    }
    else if (SAME(T,vec4)){
        GLuint loc = d_location[name];
        glUniform4fv(loc,1,value);
        //cout << "vec4 " << endl;
    }
    else if (SAME(T,float)){
        cout << "float" << endl;
    }

    else if (SAME(T,GLuint)){
        cout << "GLuint" << endl;
    }
}
//GLPROGRAM END
#endif
