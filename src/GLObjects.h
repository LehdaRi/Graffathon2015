#ifndef GLOBJECTS_H
#define GLOBJECTS_H

#include <GL/glew.h>
#define GL_SHADER_SOURCE(CODE) #CODE

//--------------------

namespace GL
{
class Buffer {
public:
	Buffer(void);
	Buffer(const Buffer&);
	Buffer(Buffer&&);
	~Buffer(void);

	Buffer& operator=(const Buffer&);
	Buffer& operator=(Buffer&&);
	operator GLuint(void) const {return buffer_;}
private:
	GLuint buffer_;
};

class Texture {
public:
	Texture(void);
	Texture(const Texture&) = delete; // TODO: Implement texture copying.
	Texture(Texture&&);
	~Texture(void);

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&);
	operator GLuint(void) const {return texture_;}
public:
	static Texture from_png(const char* filename);
	static Texture empty_2D(int width, int height);
	static Texture empty_2D_depth(int width, int height);
	static Texture empty_cube(int resolution);
	static Texture empty_cube_depth(int resolution);
	static Texture buffer_texture(const Buffer& buffer, GLenum format); // TODO: Width.
private:
	GLuint texture_;
public:
	unsigned int width_, height_; // TODO: Make these const with casting.
};

class VAO {
public:
	VAO(void);
	VAO(const VAO&) = delete;
	VAO(VAO&&);
	~VAO(void);

	VAO& operator=(const VAO&) = delete;
	VAO& operator=(VAO&&);
	operator GLuint(void) const {return vao_;}
private:
	GLuint vao_;
};

class FBO {
public:
	FBO(void);
	FBO(const FBO&) = delete;
	FBO(FBO&&);
	~FBO(void);

	FBO& operator=(const FBO&) = delete;
	FBO& operator=(FBO&&);
	operator GLuint(void) const {return fbo_;}
public:
	static FBO simple_C0(const Texture& color);
	static FBO simple_C0D(const Texture& color, const Texture& depth);
private:
	GLuint fbo_;
};

class ShaderProgram {
public:
	ShaderProgram(void);
	ShaderProgram(const char* vertex_source, const char* fragment_source);
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram(ShaderProgram&&);
	~ShaderProgram(void);

	ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&&);
	operator GLuint(void) const {return shader_program_;}
public:
	static ShaderProgram simple(void);
	static ShaderProgram from_files(const char* vertex_file, const char* fragment_file);
	static ShaderProgram raymarcher(void);
private:
	GLuint shader_program_;
};
} // namespace GL

#endif // GLOBJECTS_H