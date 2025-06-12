#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

class Object3D {
public:
    Object3D();
    virtual ~Object3D() = default;

    void SetPosition(const glm::vec3& pos);
    void SetRotation(const glm::vec3& rot);
    void SetScale(const glm::vec3& scl);

    glm::vec3 GetPosition() const;

    virtual void Update(float deltaTime) {}
    virtual void Draw(const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& viewPos,
        bool lightingEnabled,
        bool shadingEnabled) = 0;

protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 GetModelMatrix() const;
};
