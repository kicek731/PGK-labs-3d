#pragma once

#include <string>
#include <glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use() const;

    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetMat4(const std::string& name, const glm::mat4& mat) const;
    void SetVec3(const std::string& name, const glm::vec3& vec) const;

private:
    unsigned int ID;

    std::string LoadFile(const std::string& path);
    void CheckCompileErrors(unsigned int shader, const std::string& type);
};
