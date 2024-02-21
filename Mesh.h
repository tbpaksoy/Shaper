#ifndef OBJECT_H
#include "Object.h"
#endif
#ifndef VERTEX_H
#include "Vertex.h"
#endif
#include <vector>
#ifndef MESH_H
class Mesh : public Object
{
public:
    // Fields
    std::vector<unsigned int> indices;
    // Constructors
    Mesh();
    Mesh(std::vector<Vertex *> vertices, std::vector<unsigned int> indices, glm::dvec3 position = glm::dvec3(0), glm::dquat rotation = glm::dquat(1, 0, 0, 0), glm::dvec3 scale = glm::dvec3(1));
    ~Mesh();
    // Methods
    void AddVertex(Vertex *vertex);
    void OverrideVertex(Vertex *vertex, size_t index);
    Vertex **Vertices(size_t &size);
    unsigned int *Indices(size_t &size);
    double *VerticesData(size_t &size);

private:
    // Fields
    std::vector<Vertex *> vertices;
};
#define MESH_H
#endif