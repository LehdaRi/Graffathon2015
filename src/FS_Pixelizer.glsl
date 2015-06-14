/**

    Graffathon 2015
    FS_Pixelizer.glsl

    @version    0.1
    @author     Miika 'LehdaRi' Lehtimäki
    @date       2015-04-18

**/


#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D frameTexture;
uniform float aspectRatio;
uniform float imageBurn;
uniform float pixelBurn;
uniform uint xDivs;
uniform uint yDivs;

void main() {
    color = texture(frameTexture, UV);

    if (imageBurn > 0.0) {
        vec2 UVRounded = vec2((floor(UV.x*xDivs)+0.5)/xDivs, (floor(UV.y*yDivs)+0.5)/yDivs);
        vec4 pixColor = texture(frameTexture, UVRounded);
        vec4 pixColorRounded = round(pixColor);
        vec4 burnColor = pixColor + pixelBurn*(pixColorRounded-pixColor);

        color += imageBurn*(burnColor-color);
    }
}

