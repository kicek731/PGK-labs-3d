#pragma once

#include "Object3D.h"
#include "Shader.h"
#include "Texture.h"

class Cube : public Object3D {
public:
    Cube();
    ~Cube();

    void Draw(const glm::mat4& view,
        const glm::mat4& projection,
        const glm::vec3& viewPos,
        bool lightingEnabled,
        bool shadingEnabled) override;




    void SetupIrregularMesh();

    void DrawIrregular(const glm::mat4& view, const glm::mat4& projection,
        const glm::vec3& viewPos, bool lightingEnabled, bool shadingEnabled);

    void SetDrawIrregular(bool value) { drawIrregular = value; }


    void SetupConcaveDiskMesh();
    void DrawConcaveDisk(const glm::mat4& view, const glm::mat4& projection,
        const glm::vec3& viewPos, bool lightingEnabled, bool shadingEnabled);

    void SetDrawConcaveDisk(bool value) { drawConcaveDisk = value; }


    glm::vec3 position;  // pozycja obiektu

    Cube() : position(); // w konstruktorze inicjalizacja pozycji

    glm::mat4 GetModelMatrix() const;



private:
    unsigned int VAO, VBO;
    Shader shader;
    Texture texture;


                     
    unsigned int VAO_irregular, VBO_irregular;  // dla nieregularnego kszta³tu
    size_t irregularVertexCount = 0;

    
    bool drawIrregular = false;  

    bool drawConcaveDisk = false;

    void SetupMesh();

    unsigned int VAO_concaveDisk = 0;
    unsigned int VBO_concaveDisk = 0;
    size_t concaveDiskVertexCount = 0;

};





