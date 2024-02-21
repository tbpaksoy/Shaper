#include "Mesh.h"
#include "Object.cpp"
// Constructors
Mesh::Mesh() : Object()
{
}
Mesh::Mesh(std::vector<Vertex *> vertices, std::vector<unsigned int> indices, glm::dvec3 position, glm::dquat rotation, glm::dvec3 scale) : Object(position, rotation, scale)
{
    this->vertices = vertices;
    this->indices = indices;
}
Mesh::~Mesh()
{
}
// Methods
void Mesh::AddVertex(Vertex *vertex)
{
    vertices.push_back(vertex);
}
void Mesh::OverrideVertex(Vertex *vertex, size_t index)
{
    if (index < vertices.size())
        vertices[index] = vertex;
}
Vertex **Mesh::Vertices(size_t &size)
{
    size = vertices.size();
    return vertices.data();
}
unsigned int *Mesh::Indices(size_t &size)
{
    size = indices.size();
    return indices.data();
}
double *Mesh::VerticesData(size_t &size)
{
    size = vertices.size() * 7;
    double *data = new double[size];
    for (size_t i = 0; i < vertices.size(); i++)
    {
        data[i * 7] = vertices[i]->position.x;
        data[i * 7 + 1] = vertices[i]->position.y;
        data[i * 7 + 2] = vertices[i]->position.z;
        data[i * 7 + 3] = vertices[i]->color.x;
        data[i * 7 + 4] = vertices[i]->color.y;
        data[i * 7 + 5] = vertices[i]->color.z;
        data[i * 7 + 6] = vertices[i]->color.w;
    }

    return data;
}