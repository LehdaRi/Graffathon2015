/**
    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

varying vec4 pos;

out vec4 color;

void main() {
    color = pos;
}
