#include <GL/glew.h>
#include <GLFW/glfw3.h>

void GenVAO(GLuint *VAO);
void GenVBO(GLuint *VBO, GLfloat *data, unsigned int size);
void GenEBO(GLuint *EBO, unsigned int *data, unsigned int size);
void EnablePositionAttributes();
void EnableColorAttributes();