/**

    Graffathon 2015
    FS_Pixelizer.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

varying vec2 UV;

out vec4 color;

uniform sampler2D tex;

const float imageBurn = 0.5;
const float pixelBurn = 0.0;
const float xDivs = 800.0/16;
const float yDivs = 600.0/16;

void main() {
    color = texture(tex, UV);

    if (imageBurn > 0.0) {
        vec2 UVRounded = vec2(round(UV.x*xDivs)/xDivs, round(UV.y*yDivs)/yDivs);
        vec4 pixColor = texture(tex, UVRounded);
        vec4 pixColorRounded = round(pixColor);
        vec4 burnColor = pixColor + pixelBurn*(pixColorRounded-pixColor);

        color += imageBurn*(burnColor-color);
    }
}

