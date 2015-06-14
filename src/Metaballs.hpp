#ifndef METABALLS_HPP
#define METABALLS_HPP


#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"

#include <random>
#include <string>
#include <GL/glew.h>
#include <Eigen/Dense>


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
        float colorSpeed, colorPhase, colorTrans, colorAmp;
    };

    BallParams ballParams[NBALLS];

    float ballData[NBALLS*5];

    Eigen::Vector3f cameraPos_;
    Eigen::Matrix3f cameraView_;

    ShaderProgram shader_;
    GLint uniformLoc_aspectRatio_;
    GLint uniformLoc_ballPos_;
    GLint uniformLoc_cameraPosition_;
    GLint uniformLoc_cameraOrientation_;

    void generateBallData(float time);
    void cameraLookAt(const Eigen::Vector3f& from,
                      const Eigen::Vector3f& to,
                      const Eigen::Vector3f& up);
};


#endif // METABALLS_HPP
