#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    GLuint Program;

    Shader(const char* vertexPath, const char* fragmentPath);
    
    void use();
};

#endif
