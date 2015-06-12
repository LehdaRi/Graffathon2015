/**
    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

layout(location = 0) in vec3 position;

out vec4 pos;

void main() {
    pos = vec4(position, 1.0);
    gl_Position = pos;
}
