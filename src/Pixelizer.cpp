#include "Pixelizer.hpp"


Pixelizer::Pixelizer(const std::string& vsFileName,
                     const std::string& fsFileName) :
    uniformLoc_frameTexture_(-1),
    uniformLoc_aspectRatio_(-1),
    uniformLoc_imageBurn_(-1),
    uniformLoc_pixelBurn_(-1),
    uniformLoc_xDivs_(-1),
    uniformLoc_yDivs_(-1)
{
    ShaderObject vs(vsFileName, GL_VERTEX_SHADER);
    ShaderObject fs(fsFileName, GL_FRAGMENT_SHADER);
    shader_ = std::move(ShaderProgram( { &vs, &fs } ));
    uniformLoc_frameTexture_ = glGetUniformLocation(shader_.getId(), "frameTexture");
    uniformLoc_aspectRatio_ = glGetUniformLocation(shader_.getId(), "aspectRatio");
    uniformLoc_imageBurn_ = glGetUniformLocation(shader_.getId(), "imageBurn");
    uniformLoc_pixelBurn_ = glGetUniformLocation(shader_.getId(), "pixelBurn");
    uniformLoc_xDivs_ = glGetUniformLocation(shader_.getId(), "xDivs");
    uniformLoc_yDivs_ = glGetUniformLocation(shader_.getId(), "yDivs");
}

void Pixelizer::draw(GLuint quadId, float time, float aspectRatio,
                     GLuint frameTexture, unsigned xDivs, unsigned yDivs,
                     float imageBurn, float pixelBurn) {
    glUseProgram(shader_.getId());

    glUniform1f(uniformLoc_imageBurn_, imageBurn);
    glUniform1f(uniformLoc_pixelBurn_, pixelBurn);
    glUniform1ui(uniformLoc_xDivs_, xDivs);
    glUniform1ui(uniformLoc_yDivs_, yDivs);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, frameTexture);
    glUniform1i(uniformLoc_frameTexture_, 0);

    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}
