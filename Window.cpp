#include "Window.h"

#include <iostream>
#include <exception>

GLFWwindow *CreateWindow(int width, int height, int versionMajor, int versionMinor, const char *name = nullptr)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    return glfwCreateWindow(width, height, name, nullptr, nullptr);
}
void WindowLoop(GLFWwindow *window)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }
}
void WindowLoop(GLFWwindow *window, GLuint VAO, int count, Shader *shader = nullptr)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        if (shader)
            shader->Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, count);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
}
void WindowLoop(GLFWwindow *window, GLuint VAO, int vaoCount, GLuint EBO, int eboCount, Shader *shader)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        if (shader)
            shader->Use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, eboCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
}
void WindowLoop(GLFWwindow *window, GLuint VAO, int count, Shader *shader, std::function<void()> func)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        if (shader)
            shader->Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, count);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        func();
    }
}
void WindowLoop(GLFWwindow *window, GLuint VAO, int vaoCount, GLuint EBO, int eboCount, Shader *shader, std::function<void()> func)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        if (shader)
            shader->Use();
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, eboCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glfwSwapBuffers(window);
        func();
    }
}