#include "Life.hpp"


Life::Life(const std::string& vsGameFileName,
           const std::string& fsGameFileName,
           const std::string& vsShadeFileName,
           const std::string& fsShadeFileName) :
    uniformLoc_gameTexture_(-1),
    uniformLoc_shadeTexture_(-1),
    uniformLoc_aspectRatio_(-1)
{
    ShaderObject gvs(vsGameFileName, GL_VERTEX_SHADER);
    ShaderObject gfs(fsGameFileName, GL_FRAGMENT_SHADER);
    gameShader_ = std::move(ShaderProgram( { &gvs, &gfs } ));
    ShaderObject svs(vsShadeFileName, GL_VERTEX_SHADER);
    ShaderObject sfs(fsShadeFileName, GL_FRAGMENT_SHADER);
    shadeShader_ = std::move(ShaderProgram( { &svs, &sfs } ));

    uniformLoc_gameTexture_ = glGetUniformLocation(gameShader_.getId(), "gameTexture");
    uniformLoc_shadeTexture_ = glGetUniformLocation(shadeShader_.getId(), "shadeTexture");
    uniformLoc_aspectRatio_ = glGetUniformLocation(shadeShader_.getId(), "aspectRatio");
}

void Life::drawBuffer(GLuint quadId, Framebuffer& gameFb) {
    gameFb.bind();
    glUseProgram(gameShader_.getId());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gameFb.getTextureId());
    glUniform1i(uniformLoc_gameTexture_, 0);

    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Life::draw(GLuint quadId, Framebuffer& gameFb, float aspectRatio) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1280, 720);
    glUseProgram(shadeShader_.getId());

    glUniform1f(uniformLoc_aspectRatio_, aspectRatio);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gameFb.getTextureId());
    glUniform1i(uniformLoc_shadeTexture_, 0);

    glBindBuffer(GL_ARRAY_BUFFER, quadId);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
