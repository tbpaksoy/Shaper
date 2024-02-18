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
private:
    std::vector<Vertex *> vertices;
    std::vector<unsigned int> indices;
};
#define MESH_H
#endif