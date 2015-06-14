#include "Torus.hpp"
#include "GLUtils.h"

Torus::Torus(float majorRadius, float minorRadius, size_t majorSteps, size_t minorSteps)
:	torus_shader_	(GL::ShaderProgram::simple()),
	torus_			(Mesh::torus(majorRadius, minorRadius, majorSteps, minorSteps))
{}

void Torus::draw(Framebuffer& gameFb, float time) {
	GLint old_fbo; glGetIntegerv(GL_FRAMEBUFFER_BINDING, &old_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int width = 1280; int height = 720;
	glViewport(0, 0, width, height);

	// Camera.
	Eigen::Vector3f eye					= Eigen::Vector3f(4 * std::sin(time), 2, 4 * std::cos(time));
	Eigen::Matrix4f view				= GLUtils::look_at(eye);
	Eigen::Matrix4f projection			= GLUtils::perspective(width, height, PI / 2);

	// The torus is already in world space.
	Eigen::Matrix4f model_to_clip		= projection * view;
	Eigen::Matrix3f normal_to_world		= Eigen::Matrix3f::Identity();

	// Get the uniform locations from OpenGL.
	GLuint model_to_clip_uniform, normal_to_world_uniform;
	GLuint texture_flag_uniform, texture_sampler_uniform;

	model_to_clip_uniform				= glGetUniformLocation(torus_shader_, "uModelToClip");
	normal_to_world_uniform				= glGetUniformLocation(torus_shader_, "uNormalToWorld");
	texture_flag_uniform				= glGetUniformLocation(torus_shader_, "uTextureFlag");
	texture_sampler_uniform				= glGetUniformLocation(torus_shader_, "uTextureSampler");

	// Set the uniforms and draw.
	glUseProgram(torus_shader_);

	glUniformMatrix4fv(model_to_clip_uniform, 1, GL_FALSE, model_to_clip.data());
	glUniformMatrix3fv(normal_to_world_uniform, 1, GL_FALSE, normal_to_world.data());
	glUniform1i(texture_sampler_uniform, 1);

	glUniform1i(texture_flag_uniform, GL_TRUE);
	GLint old_active; glGetIntegerv(GL_ACTIVE_TEXTURE, &old_active);
	glActiveTexture(GL_TEXTURE1);
	GLint old_tex; glGetIntegerv(GL_TEXTURE_BINDING_2D, &old_tex);
	glBindTexture(GL_TEXTURE_2D, gameFb.getTextureId());

	glBindVertexArray(torus_.vao_);
	glDrawArrays(torus_.primitive_type_, 0, torus_.num_vertices_);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, old_tex);
	glActiveTexture(old_active);
	glUniform1i(texture_flag_uniform, GL_FALSE);

	glUseProgram(0);

	glBindFramebuffer(GL_FRAMEBUFFER, old_fbo);
}
