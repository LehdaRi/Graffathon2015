#include "Framebuffer.hpp"

#include <cstdio>
#include <iostream>


Framebuffer::Framebuffer(GLuint width, GLuint height) :
    width_(width),
    height_(height),
    framebuffer_(0),
    texture_(0)
{
    glGenFramebuffers(1, &framebuffer_);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);

    glGenTextures(1, &texture_);
    glBindTexture(GL_TEXTURE_2D, texture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0,
                 GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture_, 0);
    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE  )
        printf("Framebuffer fail\n");

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer(void) {
    if (framebuffer_)
        glDeleteFramebuffers(1, &framebuffer_);
    if (texture_)
        glDeleteTextures(1, &texture_);
}

void Framebuffer::bind(void) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer_);
    GLenum drawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, drawBuffers);

    glViewport(0, 0, width_, height_);
}

GLuint Framebuffer::getWidth(void) const {
    return width_;
}

GLuint Framebuffer::getHeight(void) const {
    return height_;
}

GLuint Framebuffer::getTextureId(void) const {
    return texture_;
}
