#include <glm/glm.hpp>
#ifndef VERTEX_H
class Vertex
{
public:
    glm::dvec3 position;
    glm::dvec4 color;
    Vertex(glm::dvec3 position, glm::dvec4 color);
    ~Vertex();
};

#define VERTEX_H
#endif
