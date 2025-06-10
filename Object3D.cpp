#include "Object3D.h"

Object3D::Object3D()
    : position(0.0f), rotation(0.0f), scale(1.0f) {
}

void Object3D::SetPosition(const glm::vec3& pos) {
    position = pos;
}

void Object3D::SetRotation(const glm::vec3& rot) {
    rotation = rot;
}

void Object3D::SetScale(const glm::vec3& scl) {
    scale = scl;
}

glm::vec3 Object3D::GetPosition() const {
    return position;
}

glm::mat4 Object3D::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    model = glm::scale(model, scale);
    return model;
}
