#include "Data.h"
#include <iostream>
#include "simdjson.h"
#include "simdjson.cpp"
#include "Mesh.cpp"
void GenVAO(GLuint *VAO)
{
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}
void GenVBO(GLuint *VBO, GLdouble *data, unsigned int size)
{
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void GenEBO(GLuint *EBO, unsigned int *data, unsigned int size)
{
    glGenBuffers(1, EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
void EnablePositionAttributes()
{
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid *)0);
    glEnableVertexAttribArray(0);
}
void EnableColorAttributes()
{
    glVertexAttribPointer(1, 3, GL_DOUBLE, GL_FALSE, 6 * sizeof(GLdouble), (GLvoid *)(3 * sizeof(GLdouble)));
    glEnableVertexAttribArray(1);
}
double *ConstructDataFromJson(int *size, const char *source, bool pos, bool col)
{
    double *data = nullptr;
    *size = 0;
    try
    {
        simdjson::dom::parser parser;
        simdjson::padded_string json = simdjson::padded_string::load(source);
        simdjson::dom::document ds;
        parser.parse_into_document(ds, json);
        std::vector<double> _pos;

        if (pos)
        {
            simdjson::dom::array arr = ds.root()["pos"].get_array();
            size_t length = arr.size();
            for (int i = 0; i < length; i++)
            {
                simdjson::dom::array temp = arr.at(i).get_array();
                for (auto d : temp)
                {
                    _pos.push_back(double(d));
                }
            }
        }

        std::vector<double> _col;

        if (col)
        {
            simdjson::dom::array arr = ds.root()["col"].get_array();
            size_t length = arr.size();
            for (int i = 0; i < length; i++)
            {
                simdjson::dom::array temp = arr.at(i);
                for (auto d : temp)
                {
                    _col.push_back(double(d));
                }
            }
        }

        std::vector<double> _data;

        size_t _size = _pos.size() + _col.size();
        for (size_t i = 0; _data.size() < _size; i += 3)
        {
            _data.push_back(_pos[i]);
            _data.push_back(_pos[i + 1]);
            _data.push_back(_pos[i + 2]);
            _data.push_back(_col[i]);
            _data.push_back(_col[i + 1]);
            _data.push_back(_col[i + 2]);
        }

        *size = _data.size();
        data = _data.data();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return data;
}
unsigned int *GenIndices(std::vector<Mesh *> meshes, size_t *size)
{
    unsigned int last = 0;
    std::vector<unsigned int> indices;
    for (Mesh *mesh : meshes)
    {
        for (unsigned int i : mesh->indices)
            indices.push_back(i + last);
        last = indices.size();
    }
    *size = indices.size();
    return indices.data();
}
double *GenData(std::vector<Mesh *> meshes, size_t *size, bool includeAlpha = false)
{
    std::vector<double> data;
    if (includeAlpha)
        for (Mesh *mesh : meshes)
        {
            size_t length;
            double *meshData = mesh->VerticesData(length);
            for (size_t i = 0; i < length; i++)
                data.push_back(meshData[i]);
        }
    else
        for (Mesh *mesh : meshes)
        {
            size_t length;
            double *meshData = mesh->VerticesData(length);
            for (size_t i = 0; i < length; i += 7)
            {
                data.push_back(meshData[i]);
                data.push_back(meshData[i + 1]);
                data.push_back(meshData[i + 2]);
                data.push_back(meshData[i + 3]);
                data.push_back(meshData[i + 4]);
                data.push_back(meshData[i + 5]);
            }
        }
    *size = data.size();
    return data.data();
}
void GenObjects(std::vector<Mesh *> meshes, GLuint *VAO, GLuint *VBO, GLuint *EBO, size_t *sizes[3])
{
    GenVAO(VAO);
    size_t size;
    double *data = GenData(meshes, &size);
    *sizes[1] = size;
    GenVBO(VBO, data, size * sizeof(double));
    unsigned int *indices = GenIndices(meshes, &size);
    *sizes[2] = size;
    GenEBO(EBO, indices, size * sizeof(unsigned int));
}
void GenObjects(std::vector<double> data, std::vector<unsigned int> indices, GLuint *VAO, GLuint *VBO, GLuint *EBO)
{
    GenVAO(VAO);
    GenVBO(VBO, data.data(), data.size() * sizeof(double));
    GenEBO(EBO, indices.data(), indices.size() * sizeof(unsigned int));
}
void GenObjects(double *data, unsigned int *indices, size_t sizes[3], GLuint *VAO, GLuint *VBO, GLuint *EBO)
{
    GenVAO(VAO);
    GenVBO(VBO, data, sizes[1] * sizeof(double));
    GenEBO(EBO, indices, sizes[2] * sizeof(unsigned int));
}
void BindObjects(GLuint VAO, GLuint VBO)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(0);
}
void BindObjects(GLuint VAO, GLuint VBO, GLuint EBO)
{
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBindVertexArray(0);
}