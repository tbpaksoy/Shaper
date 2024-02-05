#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#ifndef CAMERA_H
class Camera
{
private:
    glm::dvec3 position;
    glm::dquat rotation;
    glm::dvec3 worldUp;
    glm::mat4 projection;
    double fov;
    double aspectRatio;
    double nearPlane;
    double farPlane;

public:
    Camera(glm::dvec3 position, glm::dquat rotation, glm::dvec3 worldUp);
    ~Camera();
    glm::dvec3 Front();
    glm::dvec3 Right();
    glm::dvec3 Up();
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix();
    glm::dvec3 GetPosition();
    glm::dquat GetRotation();
    glm::dvec3 GetWorldUp();
    double GetFov();
    double GetAspectRatio();
    double GetNearPlane();
    double GetFarPlane();
    void Translate(glm::dvec3 translation);
    void Rotate(glm::dquat rotation);
    void SetFov(double fov);
    void SetAspectRatio(double aspectRatio);
    void SetNearPlane(double nearPlane);
    void SetFarPlane(double farPlane);
    void SetProjection();
};
#define CAMERA_H
#endif