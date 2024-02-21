#include <GL/glew.h>
#include <GLFW/glfw3.h>
#ifndef MESH_H
#include "Mesh.h"
#endif
#include <vector>
void GenVAO(GLuint *VAO);
void GenVBO(GLuint *VBO, GLdouble *data, unsigned int size);
void GenEBO(GLuint *EBO, unsigned int *data, unsigned int size);
void EnablePositionAttributes();
void EnableColorAttributes();
double *ConstructDataFromJson(int *size, const char *source, bool pos, bool col);
unsigned int *GenIndices(std::vector<Mesh *> meshes, size_t *size);
double *GenData(std::vector<Mesh *> meshes, size_t *size, bool includeAlpha);
void GenObjects(std::vector<Mesh *> meshes, GLuint *VAO, GLuint *VBO, GLuint *EBO, size_t *sizes[3]);
void GenObjects(std::vector<double> data, std::vector<unsigned int> indices, GLuint *VAO, GLuint *VBO, GLuint *EBO);
void GenObjects(double *data, unsigned int *indices, size_t sizes[3], GLuint *VAO, GLuint *VBO, GLuint *EBO);
void BindObjects(GLuint VAO, GLuint VBO);
void BindObjects(GLuint VAO, GLuint VBO, GLuint EBO);