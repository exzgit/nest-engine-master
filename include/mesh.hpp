#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <memory>
#include <iostream>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texCoord;
};

class Mesh {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        GLuint VAO, VBO, EBO;

        Mesh() = default;
        Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds);

        void Draw() const;

    private:
        void setupMesh();
};
