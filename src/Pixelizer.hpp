#ifndef PIXELIZER_HPP
#define PIXELIZER_HPP


#include "ShaderProgram.hpp"

#include <string>
#include <GL/glew.h>


class Pixelizer {
public:
    Pixelizer(const std::string& vsFileName,
              const std::string& fsFileName);

    void draw(GLuint quadId, float time, float aspectRatio,
              GLuint frameTexture, unsigned xDivs, unsigned yDivs,
              float imageBurn, float pixelBurn);

private:
    ShaderProgram shader_;
    GLint uniformLoc_frameTexture_;
    GLint uniformLoc_aspectRatio_;
    GLint uniformLoc_imageBurn_;
    GLint uniformLoc_pixelBurn_;
    GLint uniformLoc_xDivs_;
    GLint uniformLoc_yDivs_;
};


#endif // PIXELIZER_HPP
