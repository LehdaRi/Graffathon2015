/**

    Graffathon 2015
    FS_Metaballs.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

#define NBALLS 8

in vec4 pos;

//out vec4 color;
layout(location = 0) out vec4 color;

uniform float aspectRatio;
uniform vec4 ballPos[NBALLS]; //x-pos, y-pos, z-pos, size
uniform vec3 cameraPosition;
uniform mat3 cameraOrientation;

float hFovm = 0.5;
float vFovm = hFovm / aspectRatio;

const int maxSteps = 128;
const float farPlane = 5.0;
const float uEpsilon = 0.0001;

float dScene(vec3 p) {
    float f = 0.0f;
    for (int j=0; j<NBALLS; ++j) {
        vec3 bp = ballPos[j].xyz;
        f += ballPos[j].w / length(p-bp);
    }
    float d = (1.0/f)-1.0;
    //if (d<-0.1)
        //d = 0.1;
    return d;
}

vec3 getNormal(in vec3 pos) {
	vec2 epsilon = vec2(uEpsilon, 0);
	return normalize(vec3(dScene(pos + epsilon.xyy) - dScene(pos - epsilon.xyy),
						  dScene(pos + epsilon.yxy) - dScene(pos - epsilon.yxy),
						  dScene(pos + epsilon.yyx) - dScene(pos - epsilon.yyx) ));
}

void main() {
    vec3 ray = cameraOrientation[0]
               + pos.x * hFovm * cameraOrientation[1]
               + pos.y * vFovm * cameraOrientation[2];
    ray = normalize(ray);
    float dis = 1.0;

    color = vec4(0.0, 0.0, 0.0, 1.0);

    float t = 0.0;
    for (int i=0; i<maxSteps; ++i) {
        vec3 p = cameraPosition + ray*dis*t;
        float d = dScene(p);
        if (d < 0.01) {
            color = vec4(0.2 + 0.8*clamp(dot(getNormal(p), vec3(0.0, 1.0, 0.0)), 0.0, 1.0), 0.0, 0.0, 1.0);
            break;
        }
        t+=0.01f + 0.2f*d;
        if (t>farPlane)
            break;
    }

    /*float dis = 0.0f;
    for (int i=0; i<8; ++i) {
        vec2 bp = vec2(ballPos[i].x, ballPos[i].y);
        dis += ballPos[i].w / length(pos_-bp);
    }

    float ndis = smoothstep(0.85, 0.9, dis)-pow(smoothstep(0.91, 1.5, dis), 1.0);
*/
    //color = vec4(ndis, 0.0, 0.0, 1.0);
}
