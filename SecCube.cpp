



/*#include "SecCube.h"
#include <glm>
#include <vector>

SecCube::SecCube()
    : shader("vertex.glsl", "fragment.glsl"),  // mo¿esz zmieniæ œcie¿ki
    texture("textures/wood.jpg")                         // zmieniona tekstura
{
    SetupMesh();
}

SecCube::~SecCube()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void SecCube::Draw(const glm::mat4& view,
    const glm::mat4& projection,
    const glm::vec3& viewPos,
    bool lightingEnabled,
    bool shadingEnabled)
{
    shader.use();

    glm::mat4 model = GetModelMatrix();
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setVec3("viewPos", viewPos);
    shader.setInt("lightingEnabled", lightingEnabled);
    shader.setInt("shadingEnabled", shadingEnabled);

    texture.bind();

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

glm::mat4 SecCube::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    // Przesuniêcie lub skalowanie inne ni¿ Cube
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f)); // np. przesuniêty w bok
    model = glm::scale(model, glm::vec3(0.8f));                 // mniejszy
    return model;
}

void SecCube::SetupMesh()
{
    float vertices[] = {
        // identyczna siatka jak w Cube
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  -1.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -1.0f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   1.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   1.0f,  0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, 0.0f, -1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, 0.0f, -1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // pozycja (vec3)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texcoords (vec2)
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // normalne (vec3)
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

*/