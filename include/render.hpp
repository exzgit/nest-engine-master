#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <shader.hpp>
#include <entity.hpp>

class RenderSystem {
public:
    std::shared_ptr<Shader> shader;

    RenderSystem() = default;

    RenderSystem(std::shared_ptr<Shader> shaderProgram);
    void render_entity(const std::shared_ptr<Entity>& entity, const glm::mat4& parentTransform = glm::mat4(1.0f));
    void render_all(const std::vector<std::shared_ptr<Entity>>& entities);
};

GLuint LoadShader(const char* vertSrc, const char* fragSrc);

std::string loadShaderCode(const std::string& filepath);