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
uniform float ballPos[NBALLS*5]; //x-pos, y-pos, z-pos, size, color
uniform vec3 cameraPosition;
uniform mat3 cameraOrientation;

float hFovm = 0.5;
float vFovm = hFovm / aspectRatio;

const int maxSteps = 128;
const float farPlane = 5.0;
const float uEpsilon = 0.0001;

vec3 hsv_to_rgb(float h, float s, float v)
{
	float c = v * s;
	h = mod((h * 6.0), 6.0);
	float x = c * (1.0 - abs(mod(h, 2.0) - 1.0));
	vec3 color;

	if (0.0 <= h && h < 1.0) {
		color = vec3(c, x, 0.0);
	} else if (1.0 <= h && h < 2.0) {
		color = vec3(x, c, 0.0);
	} else if (2.0 <= h && h < 3.0) {
		color = vec3(0.0, c, x);
	} else if (3.0 <= h && h < 4.0) {
		color = vec3(0.0, x, c);
	} else if (4.0 <= h && h < 5.0) {
		color = vec3(x, 0.0, c);
	} else if (5.0 <= h && h < 6.0) {
		color = vec3(c, 0.0, x);
	} else {
		color = vec3(0.0, 0.0, 0.0);
	}

	color.rgb += v - c;

	return color;
}

float dScene(vec3 p) {
    float f = 0.0f;
    for (int j=0; j<NBALLS; ++j) {
        vec3 bp = vec3(ballPos[5*j], ballPos[5*j+1], ballPos[5*j+2]);
        f += ballPos[5*j+3] / length(p-bp);
    }
    float d = (1.0/f)-1.0;
    //if (d<-0.1)
        //d = 0.1;
    return d;
}

vec3 dSceneCol(vec3 p) {
    vec3 col = vec3(0.0);
    for (int j=0; j<NBALLS; ++j) {
        vec3 bp = vec3(ballPos[5*j], ballPos[5*j+1], ballPos[5*j+2]);
        col += (ballPos[5*j+3] / length(p-bp))*hsv_to_rgb(ballPos[5*j+4], 1.0, 1.0);
    }
    return col;
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

    color = vec4(0.5+0.5*sin(0.32*cos(1.5*pos.x*(pos.x-0.543)/ballPos[0]+2*(pos.y-0.8)/ballPos[1])+1.345*cos(3.4*pos.x*pos.y/ballPos[2]+1.6*pos.y*(pos.y+0.234)/ballPos[3])),
                 0.5+0.5*sin(0.54*cos(2.2*pos.x*(pos.x-0.123)/ballPos[5]+2*(pos.y-0.76)/ballPos[6])+1.543*cos(3.4*pos.x*pos.y/ballPos[7]+0.1*pos.y*(pos.y+0.123)/ballPos[8])),
                 0.5+0.5*sin(0.73*cos(0.8*pos.x*(pos.x-0.543)/ballPos[10]+2*(pos.y-0.23)/ballPos[11])+1.234*cos(3.4*pos.x*pos.y/ballPos[12]+1.1*pos.y*(pos.y+0.653)/ballPos[13])), 1.0);

    float t = 0.0;
    for (int i=0; i<maxSteps; ++i) {
        vec3 p = cameraPosition + ray*dis*t;
        float d = dScene(p);
        if (d < 0.01) {
            color = vec4((0.2 + 0.8*clamp(dot(getNormal(p), vec3(0.0, 1.0, 0.0)), 0.0, 1.0))*dSceneCol(p), 1.0);
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
