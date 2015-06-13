/**

    Graffathon 2015
    VS_LifeShade.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

layout(location = 0) in vec3 position;

out vec2 UV;

void main() {
    UV = (position.xy+vec2(1.0, 1.0))*0.5;
    gl_Position = vec4(position, 1.0);
}
