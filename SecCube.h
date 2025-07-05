#pragma once
/*
#include "Object3D.h"
#include "Shader.h"
#include "Texture.h"

class StaticCube : public Object3D {
public:
    StaticCube();
    ~StaticCube();

    void Draw(const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& viewPos,
        bool lightingEnabled,
        bool shadingEnabled) override;

    glm::mat4 GetModelMatrix() const override;

private:
    void SetupMesh();

    unsigned int VAO = 0, VBO = 0;
    Shader shader;
    Texture texture;
};
*/