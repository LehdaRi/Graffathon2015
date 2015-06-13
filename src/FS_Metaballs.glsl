/**

    Graffathon 2015
    FS_Metaballs.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

varying vec4 pos;

//out vec4 color;
layout(location = 0) out vec4 color;

uniform float aspectRatio;
uniform vec4 ballPos[8]; //x-pos, y-pos, size

void main() {
    vec2 pos_ = pos.xy;//.xy;
    pos_.y /= aspectRatio;

    float dis = 0.0f;
    for (int i=0; i<8; ++i) {
        vec2 bp = vec2(ballPos[i].x, ballPos[i].y);
        dis += ballPos[i].w / length(pos_-bp);
    }

    float ndis = smoothstep(0.85, 0.9, dis)-pow(smoothstep(0.91, 1.5, dis), 1.0);

    color = vec4(ndis, 0.0, 0.0, 1.0);
}
