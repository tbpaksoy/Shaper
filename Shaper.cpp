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

    simdjson::ondemand::parser settingsParser;
    simdjson::padded_string json = simdjson::padded_string::load("settings.json");
    simdjson::ondemand::document settings = settingsParser.iterate(json);

    simdjson::dom::parser dataParser;
    simdjson::dom::document data;
    dataParser.parse_into_document(data, simdjson::padded_string::load("Shape.json"));

    auto cube = data.root()["cube"];

    Shader *shader = new Shader("Shaders\\core.frag", "Shaders\\core.vs", false);

    srand(std::time(nullptr));

    std::vector<double> _data;

    {
        simdjson::dom::array position = cube["position"].get_array().value();
        for (int i = 0; i < position.size(); i++)
        {
            try
            {
                _data.push_back(position.at(i).at(0).get_double().value());
                _data.push_back(position.at(i).at(1).get_double().value());
                _data.push_back(position.at(i).at(2).get_double().value());
                _data.push_back((double)rand() / RAND_MAX);
                _data.push_back((double)rand() / RAND_MAX);
                _data.push_back((double)rand() / RAND_MAX);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }

    std::vector<unsigned int> indices;

    {
        simdjson::dom::array index = cube["index"].get_array().value();
        for (int i = 0; i < index.size(); i++)
        {
            try
            {
                indices.push_back(index.at(i).get_uint64().value());
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
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
    GenVBO(&VBO, _data.data(), sizeof(double) * _data.size());
    GenEBO(&EBO, indices.data(), sizeof(unsigned int) * indices.size());

    EnablePositionAttributes();
    EnableColorAttributes();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindVertexArray(0);

    Camera *camera = new Camera(glm::dvec3(10, 2, 10), glm::angleAxis(1.0, glm::dvec3(0, 1, 0)), glm::dvec3(0, 1, 0));
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

    WindowLoop(window, VAO, _data.size(), EBO, indices.size(), shader, [&]()
               {
                   shader->SetMat4("projection", camera->GetProjectionMatrix());
                   shader->SetMat4("view", camera->GetViewMatrix());
                   camera->Rotate(glm::angleAxis(0.001, camera->GetWorldUp())); });
}