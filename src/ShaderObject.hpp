/**

    Graffathon 2015
    ShaderObject.hpp

    @author Miika 'Lehdari' Lehtimäki
    @date   2015-06-12

**/

#ifndef SHADEROBJECT_HPP
#define SHADEROBJECT_HPP


#include <string>
#include <GL/glew.h>


class ShaderObject {
public:
    ShaderObject(const std::string& fileName, GLenum type);
    ~ShaderObject(void);

    GLuint getId(void) const;

private:
    GLuint objectId_;
};


#endif // SHADEROBJECT_HPP
