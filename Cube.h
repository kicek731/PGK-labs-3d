#pragma once

#include "Object3D.h"
#include "Shader.h"
#include "Texture.h"

class Cube : public Object3D {
public:
    Cube();
    ~Cube();

    void Draw(const glm::mat4& view, const glm::mat4& projection) override;

private:
    unsigned int VAO, VBO;
    Shader shader;
    Texture texture;

    void SetupMesh();
};
