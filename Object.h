#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef OBJECT_H
class Object
{
public:
    glm::dvec3 position;
    glm::dquat rotation;
    glm::dvec3 scale;
    Object();
    Object(glm::dvec3 position, glm::dquat rotation, glm::dvec3 scale);
    ~Object();
    glm::dvec3 Front();
    glm::dvec3 Right();
    glm::dvec3 Up();
};
#define OBJECT_H
#endif