#pragma once

#include <string>
#include <glm.hpp>
#include "Shader.h"
#include "Texture.h"

class Sky {
public:
    Sky();
    ~Sky();

    // Za³aduj teksturê nieba z pliku
    bool LoadSkyTexture(const std::string& texturePath);

    // Zainicjalizuj zasoby OpenGL, shadery, bufory itp.
    bool Initialize();

    // Renderuj niebo, podaj¹c macierze view i projection
    void Draw(const glm::mat4& view, const glm::mat4& projection);

    // Zwolnij zasoby
    void Cleanup();

private:
    unsigned int VAO, VBO;
    Shader shader;
    Texture* skyTexture;

    bool initialized;

    // Utwórz prost¹ siatkê kwadratow¹ (np. cube lub quad)
    void SetupMesh();
};