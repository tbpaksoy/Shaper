#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Shader.h"
GLFWwindow *CreateWindow(int width, int height, int versionMajor, int versionMinor, const char *name);
void WindowLoop(GLFWwindow *window);
void WindowLoop(GLFWwindow *window, GLuint VAO, int count, Shader *shader);
void WindowLoop(GLFWwindow *window, GLuint VAO, int vaoCount, GLuint EBO, int eboCount, Shader *shader);
void WindowLoop(GLFWwindow *window, GLuint VAO, int count, Shader *shader, std::function<void()> func);
void WindowLoop(GLFWwindow *window, GLuint VAO, int vaoCount, GLuint EBO, int eboCount, Shader *shader, std::function<void()> func);