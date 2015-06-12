#include "ShaderProgram.hpp"


ShaderProgram::ShaderProgram(const std::vector<ShaderObject*>& shaders) :
    programId_(0)
{
    programId_ = glCreateProgram();

    for (auto& object : shaders)
        glAttachShader(programId_, object->getId());

    glLinkProgram(programId_);

    GLint linkStatus, infoLogLength;
    glGetProgramiv(programId_, GL_LINK_STATUS, &linkStatus);

    if (linkStatus == GL_FALSE) {
        glGetShaderiv(programId_, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = new char[infoLogLength];
        glGetProgramInfoLog(programId_, infoLogLength, NULL, &infoLog[0]);
        fprintf(stderr, "%s", infoLog);
        throw infoLog; // TODO_EXCEPTION: throw a proper exception
    }
}

ShaderProgram::~ShaderProgram(void) {
    if (programId_ != 0)
        glDeleteProgram(programId_);
}

GLuint ShaderProgram::getId(void) const {
    return programId_;
}
