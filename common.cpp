#include "common.h"
void _init(vec4 v,GLuint u){
    for (int i = 0; i < 4; i++)
        v[3-i] = ((u >> (i*8)) & 0xff) / 255.0; 
}
