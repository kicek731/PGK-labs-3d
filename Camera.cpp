#include "Camera.h"

Camera::Camera(glm::vec3 position, float yaw, float pitch, float fov, float aspectRatio)
    : position(position), yaw(yaw), pitch(pitch), fov(fov), aspect(aspectRatio),
    movementSpeed(5.0f), mouseSensitivity(0.1f), worldUp(0.0f, 1.0f, 0.0f) {
    UpdateCameraVectors();
}

void Camera::ProcessKeyboard(float deltaTime, bool forward, bool backward, bool left, bool rightMove) {
    float velocity = movementSpeed * deltaTime;
    if (forward) position += front * velocity;
    if (backward) position -= front * velocity;
    if (left) position -= this->right * velocity;
    if (rightMove) position += this->right * velocity;
}

void Camera::ProcessMouse(float offsetX, float offsetY) {
    yaw += offsetX * mouseSensitivity;
    pitch += offsetY * mouseSensitivity;

    // Ograniczenie pitch
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::GetProjectionMatrix() const {
    return glm::perspective(glm::radians(fov), aspect, 0.1f, 100.0f);
}

glm::vec3 Camera::GetPosition() const {
    return position;
}

void Camera::UpdateCameraVectors() {
    glm::vec3 f;
    f.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    f.y = sin(glm::radians(pitch));
    f.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(f);
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
