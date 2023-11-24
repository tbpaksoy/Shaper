#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <string_view>
#include "Window.h"
#include "Window.cpp"
#include "Data.h"
#include "Data.cpp"
#ifndef SHADER_H
#include "Shader.h"
#endif
#include "Shader.cpp"

#include "simdjson.h"
#include "simdjson.cpp"
int w, h;
std::string name;
void ErrorCallback(int id, const char *desc)
{
    std::cout << id << "->" << desc << std::endl;
}
const unsigned int glVersionMinor = 3;
const unsigned int glVersionMajor = 3;

int main()
{
    simdjson::ondemand::parser parser;
    simdjson::padded_string json = simdjson::padded_string::load("settings.json");
    simdjson::ondemand::document settings = parser.iterate(json);

    Shader *shader = new Shader("Shaders\\core.frag", "Shaders\\core.vs", false);
    srand(std::time(nullptr));
    float data[36];
    for (int i = 0; i < 36; i += 6)
    {
        data[i] = (rand() % 2 == 0 ? 1 : -1) * (float)rand() / (float)RAND_MAX;
        data[i + 1] = (rand() % 2 == 0 ? 1 : -1) * (float)rand() / (float)RAND_MAX;
        data[i + 2] = (rand() % 2 == 0 ? 1 : -1) * (float)rand() / (float)RAND_MAX;
        data[i + 3] = (float)rand() / (float)RAND_MAX;
        data[i + 4] = (float)rand() / (float)RAND_MAX;
        data[i + 5] = (float)rand() / (float)RAND_MAX;
    }
    glfwSetErrorCallback(ErrorCallback);

    w = settings["width"].get_int64();
    h = settings["height"].get_int64();
    auto nameSV = settings["name"].get_string();
    std::string nameS(nameSV.value());
    name = nameS.c_str();
    int sw, sh;
    GLFWwindow *window = CreateWindow(w, h, 3, 3, name.c_str());
    glfwGetFramebufferSize(window, &sw, &sh);
    glfwMakeContextCurrent(window);
    glewInit();
    shader->Compile();
    GLuint VAO, VBO, EBO;
    GenVAO(&VAO);
    GenVBO(&VBO, data, sizeof(data));

    EnablePositionAttributes();
    EnableColorAttributes();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    WindowLoop(window, VAO, sizeof(data), shader);
}