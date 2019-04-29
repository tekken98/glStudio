//vim: ft=opengl
#version 120 
#define in varying
uniform sampler2D tex;
uniform vec4 diffuseColor;
uniform vec4 ambientColor;

in vec3 v3FragNormal;
in vec3 v3LightDir;
in vec2 v2Tex_coord;
void main(){
    float diff = max(0.0,dot(normalize(v3FragNormal), normalize(v3LightDir)));
    vec4 vFragColor = diff * diffuseColor;
    vFragColor += ambientColor;
    vec3 vReflection = normalize(reflect(-normalize(v3LightDir),normalize(v3FragNormal)));
    float spec = max(0.0,dot(normalize(v3FragNormal),vReflection));
    if (diff != 0)
    {
        float fSpec = pow(spec,128.0);
        vFragColor.rgb += vec3(fSpec,fSpec,fSpec);
    }
    vec4 v;
    v = texture2D(tex,v2Tex_coord);
    gl_FragColor =  vFragColor * v; 
}
