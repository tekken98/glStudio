// vim: ft=opengl
#version 120
#define in attribute
#define out varying 

in vec3 v3Position;
in vec2 v2Coord;
in vec3 v3Normal;

uniform vec4 v4vColor;
uniform vec4 v4Color;
uniform vec3 v3Dir;

out vec2 v2Tex_coord;
out vec4 v4AllColor;
void main()
{
    vec4 v4T = vec4(v3Position,1.0);
    vec4 v4ModelView= gl_ModelViewMatrix * v4T ;
    vec4 v4Dir = vec4(v3Dir,1);
    vec4 v4 = v4Dir * gl_ModelViewMatrix;
    vec3 v3Mode = v4.xyz;
    vec3 v3LightDir = normalize(v3Normal - v3Mode);
    float diff = max(0.0,dot(v3Normal , v3LightDir));
    v4AllColor = (v4Color + v4vColor) * diff;
    //v4AllColor = vec4(1,0,0,1);
    gl_Position=gl_ProjectionMatrix * gl_ModelViewMatrix * v4T;
    v2Tex_coord = v2Coord;
}
