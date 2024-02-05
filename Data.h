#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GenVAO(GLuint *VAO);
void GenVBO(GLuint *VBO, GLdouble *data, unsigned int size);
void GenEBO(GLuint *EBO, unsigned int *data, unsigned int size);
void EnablePositionAttributes();
void EnableColorAttributes();
double *ConstructDataFromJson(int *size, const char *source, bool pos, bool col);