#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    // Tambahkan setUniform lainnya bila perlu
};
