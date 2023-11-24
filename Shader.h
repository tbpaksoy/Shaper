#include "GL/glew.h"

#ifndef SHADER_H
class Shader
{
private:
    GLuint program;
    const char *fragmentShader;
    const char *vertexShader;

public:
    Shader(const char *fragmentShader, const char *vertexShader, bool compile);
    ~Shader();
    void Compile();
    void Use();
};
#define SHADER_H
#endif