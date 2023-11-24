#include "Data.h"

void GenVAO(GLuint *VAO)
{
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}
void GenVBO(GLuint *VBO, GLfloat *data, unsigned int size)
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
}
void EnableColorAttributes()
{
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}
