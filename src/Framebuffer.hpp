#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP


#include <GL/glew.h>


class Framebuffer {
public:
    Framebuffer(GLuint width, GLuint height);
    ~Framebuffer(void);

    void bind(void);
    GLuint getTextureId(void) const;

private:
    GLuint width_;
    GLuint height_;
    GLuint framebuffer_;
    GLuint texture_;
    GLenum drawBuffers[1];
};


#endif // FRAMEBUFFER_HPP
