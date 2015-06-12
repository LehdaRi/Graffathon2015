#include "ShaderObject.hpp"

#include <cstdio>
#include <memory>


ShaderObject::ShaderObject(const std::string& fileName, GLenum type) :
    objectId_(0)
{
    std::unique_ptr<char> src;

    FILE* f = fopen(fileName.c_str(), "rb");
    if (f) {
        fseek(f, 0l, SEEK_END);

        unsigned size = ftell(f);
        src = std::unique_ptr<char>(new char[size+1]);
        src.get()[size] = '\0';

        fseek(f, 0l, SEEK_SET);
        fread(src.get(), sizeof(char), size, f);

        fclose(f);
    }
    else throw "Cannot open shader object file";

    objectId_ = glCreateShader(type);

    const char* srcP = src.get();

    glShaderSource(objectId_, 1, &srcP , NULL);
    glCompileShader(objectId_);

    GLint compileStatus, infoLogLength;
    glGetShaderiv(objectId_, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus == GL_FALSE) {
        glGetShaderiv(objectId_, GL_INFO_LOG_LENGTH, &infoLogLength);

        char* infoLog = new char[infoLogLength];
        glGetShaderInfoLog(objectId_, infoLogLength, NULL, &infoLog[0]);
        fprintf(stderr, "%s", infoLog);
        throw infoLog; // TODO_EXCEPTION: throw a proper exception
    }
}

ShaderObject::~ShaderObject(void) {
    if (objectId_)
        glDeleteShader(objectId_);
}

GLuint ShaderObject::getId(void) const {
    return objectId_;
}
