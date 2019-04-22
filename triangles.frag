//vim: ft=opengl
#version 120 
#define in varying
uniform sampler2D tex;
in vec4 v4AllColor;
in vec2 v2Tex_coord;
void main(){
    vec4 v;
    v = texture2D(tex,v2Tex_coord);
    //gl_FragColor = v; 
    gl_FragColor = v * v4AllColor; 
}
