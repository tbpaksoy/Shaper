#include "Object.h"

Object::Object()
{
    position = glm::dvec3(0.0, 0.0, 0.0);
    rotation = glm::dquat(1.0, 0.0, 0.0, 0.0);
    scale = glm::dvec3(1.0, 1.0, 1.0);
}
Object::Object(glm::dvec3 position, glm::dquat rotation, glm::dvec3 scale)
{
    this->position = position;
    this->rotation = rotation;
    this->scale = scale;
}
Object::~Object()
{
}
glm::dvec3 Object::Front()
{
    return rotation * glm::dvec3(0, 0, 1);
}
glm::dvec3 Object::Right()
{
    return rotation * glm::dvec3(1, 0, 0);
}
glm::dvec3 Object::Up()
{
    return rotation * glm::dvec3(0, 1, 0);
}