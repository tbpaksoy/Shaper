#ifndef VERTEX_H
#include "Vertex.h"
#endif
Vertex::Vertex(glm::dvec3 position, glm::dvec4 color)
{
    this->position = position;
    this->color = color;
}
Vertex::~Vertex()
{
}
