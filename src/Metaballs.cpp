#include "Metaballs.hpp"


#define PI 3.14159265359


Metaballs::Metaballs(std::default_random_engine& rnd,
                     const std::string& vsFileName,
                     const std::string& fsFileName) :
    uniformLoc_aspectRatio_(-1),
    uniformLoc_ballPos_(-1),
    uniformLoc_cameraPosition_(-1),
    uniformLoc_cameraOrientation_(-1)
{
    double rn = 1.0/(double)rnd.max();
    for (auto i=0; i<NBALLS; ++i) {
        ballParams[i].xSpeed = 0.5f+rnd()*rn*3.5f;
        ballParams[i].xPhase = rnd()*rn*PI*2.0f;
        ballParams[i].xTrans = -0.5f+rnd()*rn*1.0f;
        ballParams[i].xAmp = rnd()*rn*1.0f;
        ballParams[i].ySpeed = 0.5f+rnd()*rn*3.5f;
        ballParams[i].yPhase = rnd()*rn*PI*2.0f;
        ballParams[i].yTrans = -0.5f+rnd()*rn*1.0f;
        ballParams[i].yAmp = rnd()*rn*1.0f;
        ballParams[i].zSpeed = 0.5f+rnd()*rn*3.5f;
        ballParams[i].zPhase = rnd()*rn*PI*2.0f;
        ballParams[i].zTrans = -0.5f+rnd()*rn*1.0f;
        ballParams[i].zAmp = rnd()*rn*1.0f;
        ballParams[i].sizeSpeed = 0.1f+rnd()*rn*0.9f;
        ballParams[i].sizePhase = rnd()*rn*PI*2.0f;
        ballParams[i].sizeTrans = 0.075f+rnd()*rn*0.03f;
        ballParams[i].sizeAmp = 0.035f+rnd()*rn*0.025f;
        /*ballParams[i].colorSpeed = 0.1f+rnd()*rn*0.9f;
        ballParams[i].colorPhase = rnd()*rn*PI*2.0f;
        ballParams[i].colorTrans = 0.042f+rnd()*rn*0.021f;
        ballParams[i].colorAmp = 0.015f+rnd()*rn*0.015f;*/
    }

    ShaderObject vs(vsFileName, GL_VERTEX_SHADER);
    ShaderObject fs(fsFileName, GL_FRAGMENT_SHADER);
    shader_ = std::move(ShaderProgram( { &vs, &fs } ));
    uniformLoc_aspectRatio_ = glGetUniformLocation(shader_.getId(), "aspectRatio");
    uniformLoc_ballPos_ = glGetUniformLocation(shader_.getId(), "ballPos");
    uniformLoc_cameraPosition_ = glGetUniformLocation(shader_.getId(), "cameraPosition");
    uniformLoc_cameraOrientation_ = glGetUniformLocation(shader_.getId(), "cameraOrientation");

    cameraLookAt(Eigen::Vector3f(2.0f, 0.5f, 2.0f),
                 Eigen::Vector3f(0.0f, 0.0f, 0.0f),
                 Eigen::Vector3f(0.0f, 1.0f, 0.0f));
}

void Metaballs::draw(GLuint quadId, float time, float aspectRatio) {
    generateBallData(time);

    glUseProgram(shader_.getId());

    glUniform1f(uniformLoc_aspectRatio_, aspectRatio);
    glUniform4fv(uniformLoc_ballPos_, NBALLS*4, ballData);
    glUniform3fv(uniformLoc_cameraPosition_, 1, cameraPos_.data());
    glUniformMatrix3fv(uniformLoc_cameraOrientation_, 1, GL_FALSE, cameraView_.data());

    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Metaballs::draw(GLuint quadId, Framebuffer& fb, float time, float aspectRatio) {
    fb.bind();
    draw(quadId, time, aspectRatio);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Metaballs::generateBallData(float time) {
    for (auto i=0; i<NBALLS; ++i) {
        ballData[4*i] = ballParams[i].xTrans + ballParams[i].xAmp*sinf(ballParams[i].xSpeed*time + ballParams[i].xPhase);
        ballData[4*i+1] = ballParams[i].yTrans + ballParams[i].yAmp*sinf(ballParams[i].ySpeed*time + ballParams[i].yPhase);
        ballData[4*i+2] = ballParams[i].zTrans + ballParams[i].zAmp*sinf(ballParams[i].zSpeed*time + ballParams[i].zPhase);
        ballData[4*i+3] = ballParams[i].sizeTrans + ballParams[i].sizeAmp*sinf(ballParams[i].sizeSpeed*time + ballParams[i].sizePhase);
    }
}

void Metaballs::cameraLookAt(const Eigen::Vector3f& from,
                             const Eigen::Vector3f& to,
                             const Eigen::Vector3f& up) {
    Eigen::Vector3f forward = (to-from).normalized();
    Eigen::Vector3f right = forward.cross(up).normalized();
    Eigen::Vector3f upn = right.cross(forward).normalized();

    cameraView_ = (Eigen::Matrix3f() << forward, right, upn).finished();
    cameraPos_ = from;
}
