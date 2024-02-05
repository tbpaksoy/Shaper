#include "Camera.h"

Camera::Camera(glm::dvec3 position, glm::dquat rotation, glm::dvec3 worldUp)
{
    this->position = position;
    this->rotation = rotation;
    this->worldUp = worldUp;
}
Camera::~Camera() {}
glm::dvec3 Camera::Front()
{
    return rotation * glm::dvec3(0, 0, 1);
}
glm::dvec3 Camera::Right()
{
    return rotation * glm::dvec3(1, 0, 0);
}
glm::dvec3 Camera::Up()
{
    return rotation * glm::dvec3(0, 1, 0);
}
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + Front(), Up());
}
glm::mat4 Camera::GetProjectionMatrix()
{
    return projection;
}
glm::dvec3 Camera::GetPosition()
{
    return this->position;
}
glm::dquat Camera::GetRotation()
{
    return this->rotation;
}
glm::dvec3 Camera::GetWorldUp()
{
    return this->worldUp;
}
double Camera::GetFov()
{
    return this->fov;
}
double Camera::GetAspectRatio()
{
    return this->aspectRatio;
}
double Camera::GetNearPlane()
{
    return this->nearPlane;
}
double Camera::GetFarPlane()
{
    return this->farPlane;
}
void Camera::Translate(glm::dvec3 translation)
{
    this->position += translation;
}
void Camera::Rotate(glm::dquat rotation)
{
    this->rotation = rotation * this->rotation;
}
void Camera::SetFov(double fov)
{
    this->fov = fov;
}
void Camera::SetAspectRatio(double aspectRatio)
{
    this->aspectRatio = aspectRatio;
}
void Camera::SetNearPlane(double nearPlane)
{
    this->nearPlane = nearPlane;
}
void Camera::SetFarPlane(double farPlane)
{
    this->farPlane = farPlane;
}
void Camera::SetProjection()
{
    this->projection = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}