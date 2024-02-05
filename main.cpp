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
#include "Camera.h"
#include "Camera.cpp"
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
    int l;
    double *data = ConstructDataFromJson(&l, "data.json", true, true);
    double _data[l];
    for (int i = 0; i < l; i++)
    {
        _data[i] = data[i];
    }

    glfwSetErrorCallback(ErrorCallback);
    w = settings["width"].get_int64();
    h = settings["height"].get_int64();
    name = std::string(settings["name"].get_string().value()).c_str();
    int sw, sh;
    GLFWwindow *window = CreateWindow(w, h, 3, 3, name.c_str());
    glfwGetFramebufferSize(window, &sw, &sh);
    glfwMakeContextCurrent(window);
    glewInit();
    shader->Compile();
    shader->Use();
    GLuint VAO, VBO, EBO;
    GenVAO(&VAO);
    GenVBO(&VBO, _data, sizeof(double) * l);

    EnablePositionAttributes();
    EnableColorAttributes();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    Camera *camera = new Camera(glm::dvec3(0, 0, 0), glm::dquat(1, 0, 0, 0), glm::dvec3(0, 0, 1));
    camera->SetFov(settings["fov"].get_double());
    camera->SetAspectRatio((double)sw / (double)sh);
    camera->SetNearPlane(settings["near"].get_double());
    camera->SetFarPlane(settings["far"].get_double());
    camera->SetProjection();

    glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 rotation = glm::mat4_cast(glm::quat(1.0, 1.0, 1.0, 1.0));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

    glm::mat4 model = translation * rotation * scale;

    shader->SetMat4("model", model);
    WindowLoop(window, VAO, l, shader, [&]()
               {
                   shader->SetMat4("projection", camera->GetProjectionMatrix());
                   glm::mat4 view = camera->GetViewMatrix();
                   shader->SetMat4("view", camera->GetViewMatrix()); });
}