//TRAITS
// GLProgram& GLProgram::operator=(const GLProgram& s)
// GLProgram::GLProgram()
// GLProgram::GLProgram(const GLProgram& s)
// GLProgram::~GLProgram()
// GLint GLProgram::getUniformLocation(const char * name)
// GLuint GLProgram::getProgram()
// GLuint GLProgram::loadShader(GLuint type,const char * filename)
// bool GLProgram::checkLink() 
// bool GLProgram::checkShader(GLuint shader)
// char ** GLProgram::loadProgramFile(const char * filename,int & lines)
// void GLProgram::bindUniform(const char *name)
// void GLProgram::loadProgram(ShaderInfo* info)
// void GLProgram::setUniform(const char *name ,GLuint value)
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include "GLProgram.h"
//GLPROGRAM BEGIN
void GLProgram::setUniform(const char *name ,GLuint value)
{
    vec4 v;
    _init(v,value);
    setUniform(name,v);
}
void GLProgram::bindUniform(const char *name)
{
    GLint loc;
    loc = glGetUniformLocation(d_program,name);
    if (loc == -1)
        cout << "Error bind :" << name << endl;
    d_location.insert(make_pair(name,loc));
}
GLuint GLProgram::getProgram()
{
    return d_program;
}
void GLProgram::loadProgram(
        ShaderInfo* info)
{
    d_program = glCreateProgram();
    vector<GLuint> shader;
    while(info->d_type !=GL_NONE)
    {
        GLuint sh = loadShader(info->d_type,info->filename);
        cout << "loading " << info->filename ;
        checkShader(sh);
        cout << " finished." << endl;
        shader.push_back(sh);
        glAttachShader(d_program,sh);
        info++;
    }
    glLinkProgram(d_program);
    checkLink();
    glUseProgram(d_program);
    for (auto a : shader)
        glDeleteShader(a);
}
bool GLProgram::checkLink()
{   
    int err;
    glGetProgramiv(d_program,GL_LINK_STATUS, &err);
    if (err == GL_FALSE) 
    {
        char buff[1024];
        int ret;
        glGetProgramInfoLog(d_program,1024,&ret,buff);
        msg(buff);
        return false;
    }
    return true;
}
bool GLProgram::checkShader(GLuint shader)
{
    int ret;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&ret);
    if (ret != GL_TRUE)
    {
        char buff[1024];
        glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&ret);
        glGetShaderInfoLog(shader,1024,&ret,buff);
        msg(buff);
        return false;
    }
    return true;
}
GLuint GLProgram::loadShader(GLuint type,const char * filename)
{
    int lines;
    char **p = loadProgramFile(filename,lines);
    GLuint shader = glCreateShader(type);
    glShaderSource(shader,lines,p,NULL);
    glCompileShader(shader);
    delete [](char*)p;
    return shader;
}
char ** GLProgram::loadProgramFile(const char * filename,int & lines)
{
    ifstream  infile(filename);
    int len=0;
    vector<string> vs;
    while (infile.good())
    {
        string s;
        getline(infile,s);
        if ( s.size() == 0) 
            continue;
        vs.push_back(s);
        len += s.size() + 3;
    }
    lines = vs.size();
    char *b;
    char *p;
    char **pp;
    p = new char[ lines * sizeof(char*) + len];
    pp = (char**)p;
    b = p + lines * sizeof(char*);
    int i = 0;
    for (auto a: vs) 
    {
        strcpy(b,a.c_str());
        pp[i++]  = b;
        b += a.size();
        *b++ = 0xd;
        *b++ = 0xa;
        *b++ = 0x0;
    }
    return pp;
}
GLint GLProgram::getUniformLocation(const char * name)
{
    return 0;
}
GLProgram::~GLProgram()
{
    glDeleteProgram(d_program);
}
GLProgram& GLProgram::operator=(const GLProgram& s)
{
    return *this;
}
GLProgram::GLProgram(const GLProgram& s)
{
}
GLProgram::GLProgram()
{
}
//GLPROGRAM END
