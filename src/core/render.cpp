#include <render.hpp>

RenderSystem::RenderSystem(std::shared_ptr<Shader> shaderProgram)
    : shader(shaderProgram) {}

void RenderSystem::render_entity(const std::shared_ptr<Entity>& entity, const glm::mat4& parentTransform) {
    if (!entity->_active) return;

    glm::mat4 model = parentTransform;

    if (entity->transform) {
        model = glm::translate(model, entity->transform->position);
        model = glm::rotate(model, glm::radians(entity->transform->rotation.x), glm::vec3(1, 0, 0));
        model = glm::rotate(model, glm::radians(entity->transform->rotation.y), glm::vec3(0, 1, 0));
        model = glm::rotate(model, glm::radians(entity->transform->rotation.z), glm::vec3(0, 0, 1));
        model = glm::scale(model, entity->transform->scale);
    }

    if (entity->meshes) {
        shader->use();
        shader->setMat4("model", model);
        entity->meshes->Draw();
    }

    for (const auto& child : entity->children) {
        render_entity(child, model);
    }
}

void RenderSystem::render_all(const std::vector<std::shared_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        render_entity(entity);
    }
}

GLuint LoadShader(const char* vertSrc, const char* fragSrc) {
    if (!vertSrc || !fragSrc) {
        std::cerr << "[SHADER LOAD ERROR] Shader source is null!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (!glad_glCreateShader) {
        std::cerr << "OpenGL context not initialized properly!" << std::endl;
        exit(EXIT_FAILURE);
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSrc, NULL);
    glCompileShader(vertexShader);
    
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "[VERTEX ERROR] " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSrc, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "[FRAGMENT ERROR] " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "[PROGRAM LINK ERROR] " << infoLog << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::string loadShaderCode(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Failed open shader file! " << filepath << std::endl;
        exit(EXIT_FAILURE);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}