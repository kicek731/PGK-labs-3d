#include "Cube.h"
#include <glad/glad.h>

Cube::Cube()
    : shader("vertex.glsl", "fragment.glsl"),
    texture("assets/textures/brick.jpg") {
    SetupMesh();
}

Cube::~Cube() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);
}

void Cube::SetupMesh() {
    float vertices[] = {
        // pos       // normal         // tex
        -0.5f,-0.5f,-0.5f, 0,0,-1, 0,0,  0.5f,-0.5f,-0.5f, 0,0,-1, 1,0,  0.5f, 0.5f,-0.5f, 0,0,-1, 1,1,
         0.5f, 0.5f,-0.5f, 0,0,-1, 1,1, -0.5f, 0.5f,-0.5f, 0,0,-1, 0,1, -0.5f,-0.5f,-0.5f, 0,0,-1, 0,0,
        -0.5f,-0.5f, 0.5f, 0,0,1, 0,0,   0.5f,-0.5f, 0.5f, 0,0,1, 1,0,   0.5f, 0.5f, 0.5f, 0,0,1, 1,1,
         0.5f, 0.5f, 0.5f, 0,0,1, 1,1,  -0.5f, 0.5f, 0.5f, 0,0,1, 0,1,  -0.5f,-0.5f, 0.5f, 0,0,1, 0,0,
        -0.5f, 0.5f, 0.5f,-1,0,0, 1,0,  -0.5f, 0.5f,-0.5f,-1,0,0, 1,1,  -0.5f,-0.5f,-0.5f,-1,0,0, 0,1,
        -0.5f,-0.5f,-0.5f,-1,0,0, 0,1,  -0.5f,-0.5f, 0.5f,-1,0,0, 0,0,  -0.5f, 0.5f, 0.5f,-1,0,0, 1,0,
         0.5f, 0.5f, 0.5f, 1,0,0, 1,0,   0.5f, 0.5f,-0.5f, 1,0,0, 1,1,   0.5f,-0.5f,-0.5f, 1,0,0, 0,1,
         0.5f,-0.5f,-0.5f, 1,0,0, 0,1,   0.5f,-0.5f, 0.5f, 1,0,0, 0,0,   0.5f, 0.5f, 0.5f, 1,0,0, 1,0,
        -0.5f,-0.5f,-0.5f, 0,-1,0, 0,1,  0.5f,-0.5f,-0.5f, 0,-1,0, 1,1,  0.5f,-0.5f, 0.5f, 0,-1,0, 1,0,
         0.5f,-0.5f, 0.5f, 0,-1,0, 1,0, -0.5f,-0.5f, 0.5f, 0,-1,0, 0,0, -0.5f,-0.5f,-0.5f, 0,-1,0, 0,1,
        -0.5f, 0.5f,-0.5f, 0,1,0, 0,1,   0.5f, 0.5f,-0.5f, 0,1,0, 1,1,   0.5f, 0.5f, 0.5f, 0,1,0, 1,0,
         0.5f, 0.5f, 0.5f, 0,1,0, 1,0,  -0.5f, 0.5f, 0.5f, 0,1,0, 0,0,  -0.5f, 0.5f,-0.5f, 0,1,0, 0,1,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Cube::Draw(const glm::mat4& view, const glm::mat4& projection,
    const glm::vec3& viewPos, bool lightingEnabled, bool shadingEnabled) {
    shader.Use();
    shader.SetMat4("model", GetModelMatrix());
    shader.SetMat4("view", view);
    shader.SetMat4("projection", projection);
    shader.SetVec3("viewPos", viewPos);
    shader.SetBool("lightingEnabled", lightingEnabled);
    shader.SetBool("shadingEnabled", shadingEnabled);

    if (lightingEnabled) {
        shader.SetVec3("lightDir", glm::normalize(glm::vec3(-0.2f, -1.0f, -0.3f)));
        shader.SetVec3("lightColor", glm::vec3(1.0f));
    }

    texture.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
