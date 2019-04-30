// vim: ft=opengl
#version 120
#define in attribute
#define out varying 

in vec3 v3Position;
in vec2 v2Coord;
in vec3 v3Normal;

uniform vec3 v3Dir;
uniform vec3 v3BDir;

out vec3 v3FragNormal;
out vec3 v3LightDir;
out vec2 v2Tex_coord;
void main()
{
    
    v3FragNormal = mat3(gl_ModelViewMatrix) * v3Normal;
    vec4 v4T = vec4(v3Position,1.0);
    vec4 v4ModelView= gl_ModelViewMatrix * v4T ;
    vec3 v3 = v3BDir + v3Dir;
    v3LightDir = normalize(v3 - v4ModelView.xyz);

    gl_Position=gl_ProjectionMatrix * gl_ModelViewMatrix * v4T;
    v2Tex_coord = v2Coord;
}
