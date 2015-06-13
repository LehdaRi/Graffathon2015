#ifndef METABALLS_CPP
#define METABALLS_HPP


#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"

#include <random>
#include <string>
#include <GL/glew.h>


#define NBALLS 8


class Pixelizer {
public:
    Pixelizer(const std::string& vsFileName,
              const std::string& fsFileName);

    void draw(GLuint quadId, float time, float aspectRatio,
              GLuint frameTexture);

private:
    ShaderProgram shader_;
    GLint uniformLoc_frameTexture_;
    GLint uniformLoc_aspectRatio_;
};


#endif // METABALLS_CPP
