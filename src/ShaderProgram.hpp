/**

    Graffathon 2015
    ShaderProgram.hpp

    @author Miika 'Lehdari' Lehtimäki
    @date   2015-06-12

**/

#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP


#include "ShaderObject.hpp"

#include <vector>
#include <GL/glew.h>


class ShaderProgram {
public:
    ShaderProgram(const std::vector<ShaderObject*>& shaders);
    ~ShaderProgram(void);

    GLuint getId(void) const;

private:
    GLuint programId_;
};


#endif // SHADERPROGRAM_HPP

