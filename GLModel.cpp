//TRAITS
// GLfloat * GLModel::getVertex(int index)
// GLModel& GLModel::operator=(const GLModel& s)
// GLModel::GLModel(const GLModel& s)
// GLModel::GLModel(const char* filename)
// GLModel::~GLModel()
// GLuint GLModel::getSize()
// void GLModel::bind()
// void GLModel::drawModel() 
// void GLModel::drawNormal()
// void GLModel::load(const char * filename)
// void GLModel::loadModel()
// void GLModel::loadNode(Lib3dsNode *node)
// void GLModel::moveTo(GLfloat x , GLfloat y, GLfloat z)
// void GLModel::offsetTo(GLfloat x , GLfloat y, GLfloat z)
// void GLModel::pushVertex(Lib3dsVector& v,Lib3dsVector& nv,int i)
#include "GLModel.h" 
#include <iostream>
#include "common.h"
using namespace std;
//GLMODEL BEGIN
void GLModel::drawNormal()
{
    static GLfloat d = 0.01;
    d +=0.01;
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(d / 3.1415 *180,0,1,0);
    glTranslatef(d_pos[0],d_pos[1],d_pos[2]);
    glBindVertexArray(d_VAO[0]);
    int begin = getSize(0); 
    //begin = 0;
    glLineWidth(1);
    for (unsigned int i = 0; i < getSize(1) / 2 ;i++)
        glDrawArrays(GL_LINES,begin + i*2,2);
    glPopMatrix();
}
void GLModel::offsetTo(GLfloat x , GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    d_pos[0] += x;
    d_pos[1] += y;
    d_pos[2] += z;
    glPopMatrix();
}
GLuint GLModel::getSize(int index)
{
    return d_vertex[index].size();
}
void GLModel::loadModel()
{
    Lib3dsNode *p;
    for (p=d_file->nodes; p!=0; p=p->next){
        loadNode(p);
    }
    glGenVertexArrays(1,d_VAO);

    glBindVertexArray(d_VAO[0]);
    glGenBuffers(1,d_buf);
    glBindBuffer(GL_ARRAY_BUFFER,d_buf[0]);


    GLfloat * pv = getVertex(0);
    //glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * (getSize(0)),pv,GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * (getSize(0) + getSize(1)),NULL,GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Vertex) * getSize(0),pv);
    GLfloat * npv = getVertex(1);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(Vertex) * getSize(0),sizeof(Vertex) * getSize(1),npv);
}
void GLModel::drawModel()
{   
    static GLfloat d = 0.01;
    d +=0.01;
    glPushMatrix();
    glTranslatef(0,0,0);
    glRotatef(d / 3.1415 *180,0,1,0);
    glTranslatef(d_pos[0],d_pos[1],d_pos[2]);
    glBindVertexArray(d_VAO[0]);
    for (unsigned int i = 0; i < d_size[0] / 3;i++)
        glDrawArrays(GL_TRIANGLE_FAN,i*3,3);
    glPopMatrix();
}
void GLModel::bind()
{
    glBindVertexArray(d_VAO[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) , (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8 ) ,
            (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) ,
            (GLvoid*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

}
GLfloat * GLModel::getVertex(int index)
{
    d_size[index] = d_vertex[index].size();
    if (d_p)
    {
        delete [] d_p;
        d_p = NULL;
    }
    d_p =(Vertex*) new GLfloat[d_size[index] * sizeof(Vertex)];
    int i = 0;
    for (auto a : d_vertex[index])
    {
        d_p[i++] = a;
    }
    return (GLfloat*)d_p;
}
void GLModel::pushVertex(Lib3dsVector& v,Lib3dsVector& nv,int i)
{
    Vertex vertex;
    Vertex vn;
    vertex.x = v[0] / 2 ;
    vertex.y=v[1] / 2 ;
    vertex.z=v[2] / 2;
    vertex.nx = v[0];
    vertex.ny = v[1];
    vertex.nz = v[2];
    // (x+1) /4 + (1-x) / 2  when z <0
    // (x+1) / 4 when z >= 0
    vertex.s = (v[0] + 1) / 4 + (v[2] <0 ? (1-v[0])/2: 0) ; 
    vertex.t = (.3- v[1] ) / 2;  
    vn = vertex;
    cout.width(10);
    cout << vn.x << "\t\t"  << vn.y << "\t\t" << vn.z <<endl;

    d_vertex[1].push_back(vn);
    vn.x = vn.x   ;
    vn.y = vn.y   ;
    vn.z = vn.z   ;
    cout << vn.x << "\t\t"  << vn.y << "\t\t" << vn.z <<endl;
    cout << "***********" << endl;
    d_vertex[1].push_back(vn);
    d_vertex[0].push_back(vertex);
}
void GLModel::loadNode(Lib3dsNode *node)
{
    ASSERT(d_file);
    Lib3dsNode *p;
    for (p = node->childs; p!=0; p=p->next){
        loadNode(p);
    }
    if (node->type==LIB3DS_OBJECT_NODE) {
        Lib3dsMesh *mesh;
        if (strcmp(node->name,"$$$DUMMY")==0) {
            return;
        }
        mesh = lib3ds_file_mesh_by_name(d_file, node->data.object.morph);
        if( mesh == NULL )
            mesh = lib3ds_file_mesh_by_name(d_file, node->name);

        if (!mesh->user.d) {
            ASSERT(mesh);
            if (!mesh) {
                return;
            }
        }
        Lib3dsVector *normalL = (Lib3dsVector*)malloc(3*sizeof(Lib3dsVector)*mesh->faces);
        lib3ds_mesh_calculate_normals(mesh, normalL);
        // begin make vertex
        unsigned pface;
        //cout << "faces:" << mesh->faces << endl;
        for (pface=0; pface<mesh->faces; ++pface) 
        {
            Lib3dsFace *f = &mesh->faceL[pface];
            for (int i=0; i<3; i++)
            {
                pushVertex(mesh->pointL[f->points[i]].pos,normalL[3*pface+i],i);
            }
        }
        free(normalL);
    }
}
void GLModel::load(const char * filename)
{
    d_file = lib3ds_file_load(filename);
    if (!d_file){
        puts("error load file\n");
        exit(1);
    }
    if(!d_file->nodes)
    {
        Lib3dsMesh *mesh;
        Lib3dsNode *node;

        for(mesh = d_file->meshes; mesh != NULL; mesh = mesh->next)
        {
            node = lib3ds_node_new_object();
            strcpy(node->name, mesh->name);
            node->parent_id = LIB3DS_NO_PARENT;
            lib3ds_file_insert_node(d_file, node);
        }
    }
 // lib3ds_file_eval(d_file, 1.0f);
 // lib3ds_file_eval(d_file,0.);
}
GLModel::~GLModel()
{
    if (d_p)
        delete [] d_p;
}
GLModel& GLModel::operator=(const GLModel& s)
{
    return *this;
}
GLModel::GLModel(const GLModel& s)
{
}
GLModel::GLModel(const char* filename)
{
    d_file = NULL;
    d_p = NULL;
    d_VAO[0] = 0;
    d_VAO[1] = 0;
    d_size[0] = 0;
    d_size[1] = 0;
    load(filename);
}
//GLMODEL END
