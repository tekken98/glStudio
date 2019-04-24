//TRAITS
// void GLModel::moveTo(GLfloat x , GLfloat y, GLfloat z)
// GLuint GLModel::getSize()
// void GLModel::loadModel()
// void GLModel::drawModel() 
// void GLModel::bind()
// GLfloat * GLModel::getVertex()
// void GLModel::pushVertex(Lib3dsVector& v,Lib3dsVector& nv,int i)
// void GLModel::loadNode(Lib3dsNode *node)
// void GLModel::load(const char * filename)
// GLModel::~GLModel()
// GLModel& GLModel::operator=(const GLModel& s)
// GLModel::GLModel(const GLModel& s)
// GLModel::GLModel(const char* filename)
#include "GLModel.h"
#include <iostream>
using namespace std;
//GLMODEL BEGIN
void GLModel::offsetTo(GLfloat x , GLfloat y, GLfloat z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    d_pos[0] += x;
    d_pos[1] += y;
    d_pos[2] += z;
    glPopMatrix();
}
GLuint GLModel::getSize()
{
    return d_size;
}
void GLModel::loadModel()
{
    Lib3dsNode *p;
    for (p=d_file->nodes; p!=0; p=p->next){
        loadNode(p);
    }
    glGenVertexArrays(1,&d_VAO);
    //cout << "GLModel:" << d_VAO << endl;
    glBindVertexArray(d_VAO);

    GLuint buf;
    glGenBuffers(1,&buf);
    glBindBuffer(GL_ARRAY_BUFFER,buf);
    //cout << "GLModel:" << buf << endl;

    GLfloat * pv = getVertex();
    glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex) * d_size,pv,GL_STATIC_DRAW);
}
void GLModel::drawModel()
{   
    glPushMatrix();
    glTranslatef(d_pos[0],d_pos[1],d_pos[2]);

    glBindVertexArray(d_VAO);
    for (unsigned int i = 0; i < d_size;i++)
        glDrawArrays(GL_TRIANGLE_FAN,i*3,3);
    glPopMatrix();
}
void GLModel::bind()
{
    glBindVertexArray(d_VAO);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) , (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) ,
            (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, (GLfloat)(sizeof(GLfloat) * 8) ,
            (GLvoid*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);


}
GLfloat * GLModel::getVertex()
{
    d_size = d_vertex.size();
    if (d_p)
        delete [] d_p;
    d_p =(Vertex*) new GLfloat[d_size * sizeof(Vertex)];
    int i = 0;
    for (auto a : d_vertex)
    {
        d_p[i++] = a;
    }
    return (GLfloat*)d_p;
}
void GLModel::pushVertex(Lib3dsVector& v,Lib3dsVector& nv,int i)
{
    Vertex vertex;
    vertex.x = v[0] / 2 ;
    vertex.y=v[1] / 2 ;
    vertex.z=v[2];
    vertex.nx = nv[0];
    vertex.ny = nv[1];
    vertex.nz = nv[2];
    switch (i)
    {
        case 0:
            vertex.s = 0 ;
            vertex.t = 0;
            break;
        case 1:
            vertex.s = .1;
            vertex.t = .1;
            break;
        case 2:
            vertex.s = 0.05;
            vertex.t = 0;
            break;
    }

    d_vertex.push_back(vertex);
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
    d_VAO = 0;
    d_size = 0;
    load(filename);
}
//GLMODEL END
