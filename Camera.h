#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(glm::vec3 position, float yaw, float pitch, float fov, float aspectRatio);

    void ProcessKeyboard(float deltaTime, bool forward, bool backward, bool left, bool right);
    void ProcessMouse(float offsetX, float offsetY);
    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    glm::vec3 GetPosition() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw, pitch;
    float movementSpeed;
    float mouseSensitivity;
    float fov, aspect;

    void UpdateCameraVectors();
};
