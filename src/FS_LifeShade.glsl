/**

    Graffathon 2015
    FS_LifeShade.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D frameTexture;
uniform float aspectRatio;

void main() {
    vec2 UV_ = vec2(UV.x, (UV.y*2.0-1.0)/aspectRatio*.5+.5);
    color = texture(frameTexture, UV_);
}
