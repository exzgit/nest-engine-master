#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

struct CameraUniform {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float fov = 45.0f;
    float aspectRatio = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    glm::mat4 getViewMatrix() const {
        return glm::lookAt(position, target, up);
    }

    glm::mat4 getProjectionMatrix() const {
        return glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }

};

class CameraController {
public:
    CameraController(CameraUniform& cam, float moveSpeed = 5.0f, float turnSpeed = 0.1f);

    void handleKeyboard(GLFWwindow* window, float dt);
    void handleMouse(float xpos, float ypos);
    void update(float dt, GLFWwindow* window);

private:
    CameraUniform& camera;
    float moveSpeed;
    float turnSpeed;

    float lastX = 400.0f;
    float lastY = 300.0f;
    bool firstMouse = true;

    float yaw = -90.0f;
    float pitch = 0.0f;

    void updateDirection();
};

void setCameraUniform(GLuint shaderID, const CameraUniform& cam);
// void updateCamera(CameraUniform& am, float dt, InputEvent& input);