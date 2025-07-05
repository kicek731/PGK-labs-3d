/* #ifndef SKY_VIEW_H
#define SKY_VIEW_H

#include <vector>
#include <string>
#include <glm.hpp>
#include "Shader.h"

class sky_viev {
public:
    // Poprawiony konstruktor z œcie¿kami do shaderów
    sky_viev(const std::vector<std::string>& faces, const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~sky_viev();

    void Draw(const glm::mat4& view, const glm::mat4& projection);

private:
    unsigned int VAO, VBO;
    unsigned int cubemapTexture;
    Shader shader;

    void SetupCube();
    unsigned int LoadCubemap(const std::vector<std::string>& faces);
};

#endif */