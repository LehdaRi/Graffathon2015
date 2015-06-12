/**

    Graffathon 2015
    FS_Metaballs.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

varying vec4 pos;

out vec4 color;

uniform vec3 ballPos[3]; //x-pos, y-pos, size

const float aspectRatio = 4.0/3.0;

void main() {
    vec2 pos_ = pos.xy;
    pos_.x *= aspectRatio;

    float dis = 0.0f;
    for (int i=0; i<3; ++i) {
        vec2 bp = vec2(ballPos[i].x*aspectRatio, ballPos[i].y);
        dis += ballPos[i].z / length(pos_-bp);
    }

    float ndis = smoothstep(0.8, 0.9, dis)-pow(smoothstep(0.91, 5.0, dis), 0.4);

    color = vec4(ndis, 0.0, 0.0, 1.0);
}
