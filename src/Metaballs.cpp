#include "Metaballs.hpp"


#define PI 3.14159265359


Metaballs::Metaballs(std::default_random_engine& rnd,
                     const std::string& vsFileName,
                     const std::string& fsFileName) :
    uniformLoc_aspectRatio(-1),
    uniformLoc_ballPos(-1)
{
    double rn = 1.0/(double)rnd.max();
    for (auto i=0; i<NBALLS; ++i) {
        ballParams[i].xSpeed = 0.5f+rnd()*rn*3.5f;
        ballParams[i].xPhase = rnd()*rn*PI*2.0f;
        ballParams[i].xTrans = -0.5f+rnd()*rn*1.0f;
        ballParams[i].xAmp = -1.0f+rnd()*rn*2.0f;
        ballParams[i].ySpeed = 0.5f+rnd()*rn*3.5f;
        ballParams[i].yPhase = rnd()*rn*PI*2.0f;
        ballParams[i].yTrans = -0.5f+rnd()*rn*1.0f;
        ballParams[i].yAmp = -1.0f+rnd()*rn*2.0f;
        ballParams[i].zSpeed = 0.5f+rnd()*rn*3.5f;
        ballParams[i].zPhase = rnd()*rn*PI*2.0f;
        ballParams[i].zTrans = -0.5f+rnd()*rn*1.0f;
        ballParams[i].zAmp = -1.0f+rnd()*rn*2.0f;
        ballParams[i].sizeSpeed = 0.1f+rnd()*rn*0.9f;
        ballParams[i].sizePhase = rnd()*rn*PI*2.0f;
        ballParams[i].sizeTrans = 0.06f+rnd()*rn*0.02f;
        ballParams[i].sizeAmp = 0.025f+rnd()*rn*0.025f;
    }

    ShaderObject vs(vsFileName, GL_VERTEX_SHADER);
    ShaderObject fs(fsFileName, GL_FRAGMENT_SHADER);
    shader_ = std::move(ShaderProgram( { &vs, &fs } ));
    uniformLoc_aspectRatio = glGetUniformLocation(shader_.getId(), "aspectRatio");
    uniformLoc_ballPos = glGetUniformLocation(shader_.getId(), "ballPos");
}

void Metaballs::draw(GLuint quadId, float time, float aspectRatio) {
    generateBallData(time);

    glUseProgram(shader_.getId());

    glUniform1f(uniformLoc_aspectRatio, aspectRatio);
    glUniform4fv(uniformLoc_ballPos, NBALLS*4, ballData);

    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Metaballs::generateBallData(float time) {
    for (auto i=0; i<NBALLS; ++i) {
        ballData[4*i] = ballParams[i].xTrans + ballParams[i].xAmp*sinf(ballParams[i].xSpeed*time + ballParams[i].xPhase);
        ballData[4*i+1] = ballParams[i].yTrans + ballParams[i].yAmp*sinf(ballParams[i].ySpeed*time + ballParams[i].yPhase);
        ballData[4*i+2] = ballParams[i].zTrans + ballParams[i].zAmp*sinf(ballParams[i].zSpeed*time + ballParams[i].zPhase);
        ballData[4*i+3] = ballParams[i].sizeTrans + ballParams[i].sizeAmp*sinf(ballParams[i].sizeSpeed*time + ballParams[i].sizePhase);
    }
}
