#include "Cube.h"
#include <glad/glad.h>
#include <vector>

Cube::Cube()
    : shader("vertex.glsl", "fragment.glsl"),
    texture("assets/textures/brick.jpg") , position(0.0f, 0.0f, 0.0f) {
    SetupMesh();

    SetupIrregularMesh();

    SetDrawConcaveDisk(false);

    SetupConcaveDiskMesh();
}

glm::mat4 Cube::GetModelMatrix() const
{

    return glm::mat4();
}

Cube::~Cube() {
    if (VAO) glDeleteVertexArrays(1, &VAO);
    if (VBO) glDeleteBuffers(1, &VBO);

    if (VAO_irregular) glDeleteVertexArrays(1, &VAO_irregular);
    if (VBO_irregular) glDeleteBuffers(1, &VBO_irregular);
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

    if (drawIrregular) {
        DrawIrregular(view, projection, viewPos, lightingEnabled, shadingEnabled);
        return;
    }
    if (drawConcaveDisk) {
        DrawConcaveDisk(view, projection, viewPos, lightingEnabled, shadingEnabled);
        return;
    }


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







void Cube::SetupIrregularMesh()
{

    // Przyk³adowy nieregularny kszta³t (trochê „piramidy” z odchylonym wierzcho³kiem)
    float irregularVertices[] = {
        // pozycja        // normal         // tex
         0.0f,  0.5f,  0.0f,  0, 1, 0,  0.5f, 1.0f,   // szczyt
        -0.5f, -0.5f,  0.5f,  0, 0, 1,  0.0f, 0.0f,   // przód-lewo
         0.5f, -0.5f,  0.5f,  0, 0, 1,  1.0f, 0.0f,   // przód-prawo

         0.0f,  0.5f,  0.0f,  1, 0, 0,  0.5f, 1.0f,   // szczyt
         0.5f, -0.5f,  0.5f,  1, 0, 0,  0.0f, 0.0f,   // przód-prawo
         0.5f, -0.5f, -0.5f,  1, 0, 0,  1.0f, 0.0f,   // ty³-prawo

         0.0f,  0.5f,  0.0f,  0, 0, -1, 0.5f, 1.0f,   // szczyt
         0.5f, -0.5f, -0.5f, 0, 0, -1, 1.0f, 0.0f,    // ty³-prawo
        -0.5f, -0.5f, -0.5f, 0, 0, -1, 0.0f, 0.0f,    // ty³-lewo

         0.0f,  0.5f,  0.0f, -1, 0, 0,  0.5f, 1.0f,   // szczyt
        -0.5f, -0.5f, -0.5f, -1, 0, 0, 0.0f, 0.0f,    // ty³-lewo
        -0.5f, -0.5f,  0.5f, -1, 0, 0, 1.0f, 0.0f,    // przód-lewo

        // podstawa (dó³)
        -0.5f, -0.5f,  0.5f, 0, -1, 0, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0, -1, 0, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f, 0, -1, 0, 1.0f, 0.0f,

         0.5f, -0.5f, -0.5f, 0, -1, 0, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0, -1, 0, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f, 0, -1, 0, 0.0f, 1.0f,
    };

    irregularVertexCount = sizeof(irregularVertices) / (8 * sizeof(float));

    glGenVertexArrays(1, &VAO_irregular);
    glGenBuffers(1, &VBO_irregular);

    glBindVertexArray(VAO_irregular);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_irregular);
    glBufferData(GL_ARRAY_BUFFER, sizeof(irregularVertices), irregularVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Cube::DrawIrregular(const glm::mat4& view, const glm::mat4& projection, const glm::vec3& viewPos, bool lightingEnabled, bool shadingEnabled)
{
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
    glBindVertexArray(VAO_irregular);
    glDrawArrays(GL_TRIANGLES, 0, irregularVertexCount);



}

void Cube::SetupConcaveDiskMesh() {

    const int segments = 80;
    const float baseRadius = 0.86f;
    const float amplitude = 0.15f; // wysokoœæ fali
    const int frequency = 6;       // liczba fal

    std::vector<float> vertices;

    // Œrodkowy punkt (czubek kopu³y)
    vertices.push_back(0.0f); // x
    vertices.push_back(0.2f); // y - lekko wypuk³y
    vertices.push_back(0.0f); // z

    vertices.push_back(0.0f); // normal x
    vertices.push_back(1.0f); // normal y
    vertices.push_back(0.0f); // normal z

    vertices.push_back(0.5f); // tex u
    vertices.push_back(0.5f); // tex v

    for (int i = 0; i <= segments; ++i) {
        float angle = i * 2.0f * glm::pi<float>() / segments;

        // promieñ modyfikowany fal¹
        float radius = baseRadius + amplitude * sin(frequency * angle);

        float x = radius * cos(angle);
        float z = radius * sin(angle);

        // wysokoœæ krawêdzi - te¿ zale¿y od sinusa
        float y = 0.1f * sin(frequency * angle);

        vertices.push_back(x);
        vertices.push_back(y); // wysokoœæ! teraz nie 0.0f
        vertices.push_back(z);

        // normalka przybli¿ona na sztywno — mo¿na wyliczyæ lepiej póŸniej
        vertices.push_back(0.0f);
        vertices.push_back(1.0f);
        vertices.push_back(0.0f);

        // UV wspó³rzêdne
        vertices.push_back(0.5f + x);
        vertices.push_back(0.5f + z);
    }

    concaveDiskVertexCount = segments + 2;

    glGenVertexArrays(1, &VAO_concaveDisk);
    glGenBuffers(1, &VBO_concaveDisk);

    glBindVertexArray(VAO_concaveDisk);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_concaveDisk);

    // *** Tutaj jest poprawne wywo³anie glBufferData ***
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}


void Cube::DrawConcaveDisk(const glm::mat4& view, const glm::mat4& projection,
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
    glBindVertexArray(VAO_concaveDisk);
    glDrawArrays(GL_TRIANGLE_FAN, 0, concaveDiskVertexCount);
}



