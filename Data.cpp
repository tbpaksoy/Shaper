#include "Data.h"
#include <iostream>
#include "simdjson.h"
#include "simdjson.cpp"
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