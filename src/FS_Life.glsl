/**

    Graffathon 2015
    FS_Life.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D gameTexture;

const uint xSize = 32;
const uint ySize = 32;

const float xDis = 1.0/float(xSize);
const float yDis = 1.0/float(ySize);

void main() {
    int nnR = 0;
    color = round(texture(gameTexture, UV));

    for (int i=-1; i<2; ++i) {
        for (int j=-1; j<2; ++j) {
            if (i==0 && j==0)
                continue;
            vec4 pix = round(texture(gameTexture, UV+vec2(i*xDis, j*yDis)));
            if (pix.r == 1.0)
                nnR++;
        }
    }

    if (color.r == 1.0) {
        if (nnR < 2)
            color.r = 0.0;
        else if (nnR > 3)
            color.r = 0.0;
    }
    else {
        if (nnR == 3)
            color.r = 1.0;
    }

    //color = vec4(round(texture(gameTexture, UV)).r, 0.0, nnR/8.0, 1.0);

    //color = texture(gameTexture, UV);
}


