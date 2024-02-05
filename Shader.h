#include "GL/glew.h"
#include <glm/glm.hpp>
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
    void SetMat4(const std::string &name, const glm::mat4 &mat) const;
};
#define SHADER_H
#endif