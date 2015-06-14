#ifndef TORUS_HPP
#define TORUS_HPP

#define START_TIME 40.0F

#include "Mesh.h"
#include "Framebuffer.hpp"

class Torus {
public:
	Torus(float majorRadius, float minorRadius,
		  size_t majorSteps, size_t minorSteps);

	void draw(Framebuffer& gameFb, float time);
private:
	GL::ShaderProgram torus_shader_;
	Mesh torus_;
};

#endif // TORUS_HPP
