#ifndef LIFE_HPP
#define LIFE_HPP


#include "ShaderProgram.hpp"
#include "Framebuffer.hpp"

#include <string>
#include <GL/glew.h>


class Life {
public:
    Life(const std::string& vsGameFileName,
         const std::string& fsGameFileName,
         const std::string& vsShadeFileName,
         const std::string& fsShadeFileName);

	void drawBuffer(GLuint quaidId, Framebuffer& gameFb);
    void draw(GLuint quadId, Framebuffer& gameFb, float aspectRatio);

private:
    ShaderProgram gameShader_;
    ShaderProgram shadeShader_;
    GLint uniformLoc_gameTexture_;
    GLint uniformLoc_shadeTexture_;
    GLint uniformLoc_aspectRatio_;
    GLuint gameTextureCopy_;
};


#endif // LIFE_HPP
