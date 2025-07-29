#pragma once

#include <vector>
#include <string>
#include <camera.hpp>
#include <memory>
#include <render.hpp>
#include <mesh.hpp>
#include <ecs.hpp>


class World {
public:
    std::string name;
    std::string path;

    GLuint shaderID;

    RenderSystem renderer;
    ECS ecs;

    World();
    ~World();

    void update(float dt);
    void render();

    // void onAttach(GLFWwindow* window);
};


class WorldManager {
private:
    std::vector<std::shared_ptr<World>> worldlist;
    std::shared_ptr<World> active = NULL;

public:
    WorldManager();
    ~WorldManager();

    void create_world(const std::string& name, const std::string& path);
    bool remove_world(const std::string& name);

    void setActive(const std::string& name);
    std::shared_ptr<World> getActive();

    std::vector<std::shared_ptr<World>> getAllScene();
};