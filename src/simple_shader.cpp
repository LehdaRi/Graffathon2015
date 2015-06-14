#include "GLObjects.h"

//--------------------

namespace GL
{
ShaderProgram ShaderProgram::simple(void) {
	return GL::ShaderProgram(
		"#version 330\n"
		GL_SHADER_SOURCE(
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec3 aNormal;
			layout(location = 2) in vec2 aTexCoord;

			uniform mat4 uModelToClip = mat4(1.0);
			uniform mat3 uNormalToWorld = mat3(1.0);

			out vec3 vColor;
			out vec3 vNormal;
			out vec2 vTexCoord;

			void main() {
				const vec3 distinctColors[6] = vec3[6](vec3(0, 0, 1), vec3(0, 1, 0), vec3(0, 1, 1),
													   vec3(1, 0, 0), vec3(1, 0, 1), vec3(1, 1, 0));

				vColor = distinctColors[gl_VertexID % 6];
				vNormal = normalize(uNormalToWorld * aNormal);
				vTexCoord = aTexCoord;

				gl_Position = uModelToClip * vec4(aPosition, 1.0);
			}
		),
		"#version 330\n"
		GL_SHADER_SOURCE(
			in vec3 vColor;
			in vec3 vNormal;
			in vec2 vTexCoord;

			uniform bool uTextureFlag = false;
			uniform sampler2D uTextureSampler;

			layout(location = 0) out vec4 fColor;

			void main() {
				fColor = vec4(vColor, 1.0);
				if (uTextureFlag)
					fColor = texture2D(uTextureSampler, vTexCoord);
			}
		)
	);
}
} // namespace GL