#ifndef METABALLS_CPP
#define METABALLS_HPP


#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"

#include <random>
#include <string>
#include <GL/glew.h>


#define NBALLS 8


class Metaballs {
public:
    Metaballs(std::default_random_engine& rnd,
              const std::string& vsFileName,
              const std::string& fsFileName);

    void draw(GLuint quadId, float time, float aspectRatio);
    void draw(GLuint quadId, Framebuffer& fb, float time, float aspectRatio);

private:
    struct BallParams {
        float xSpeed, xPhase, xTrans, xAmp;
        float ySpeed, yPhase, yTrans, yAmp;
        float zSpeed, zPhase, zTrans, zAmp;
        float sizeSpeed, sizePhase, sizeTrans, sizeAmp;
    };

    BallParams ballParams[NBALLS];

    float ballData[NBALLS*4];

    ShaderProgram shader_;
    GLint uniformLoc_aspectRatio_;
    GLint uniformLoc_ballPos_;

    void generateBallData(float time);
};


#endif // METABALLS_CPP
