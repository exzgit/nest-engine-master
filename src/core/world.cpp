#include <world.hpp>

// ==========
// World
// ==========

World::World() {
    std::string vertexCameraSource = loadShaderCode("./shaders/uniform.vert");
    std::string fragmentCameraSource = loadShaderCode("./shaders/uniform.frag");

    std::cout << "vertex and fragment successfully loader!\n";

    shaderID = LoadShader(vertexCameraSource.c_str(), fragmentCameraSource.c_str());
    std::cout << "Load Shader Successfully!\n";

    std::shared_ptr<Shader> myShader = std::make_shared<Shader>("./shaders/uniform.vert", "./shaders/uniform.frag");
    renderer = RenderSystem(myShader);
}

World::~World() {}

void World::update(float dt) {
    // setCameraUniform(shaderID, worldCam);
}

void World::render() {
    ecs.render(renderer);
}

// void World::onAttach(GLFWwindow* window) {
//     glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xpos, double ypos) {
//         auto* world = static_cast<World*>(glfwGetWindowUserPointer(win));
//         if (world->controller) {
//             world->controller->handleMouse((float)xpos, (float)ypos);
//         }
//     });

//     glfwSetWindowUserPointer(window, this);
// }

// ==========
// World Manager
// ==========

WorldManager::WorldManager() {
    this->create_world("Main Scene", "./scenes/");
}

WorldManager::~WorldManager() {
    worldlist.clear();
}

void WorldManager::create_world(const std::string& name, const std::string& path) {
    World newWorld = World();
    newWorld.name = name;
    newWorld.path = path;

    worldlist.push_back(std::make_shared<World>(newWorld));
    if (active == nullptr) 
        active = worldlist.back();
}

bool WorldManager::remove_world(const std::string& name) {
    for (auto it = worldlist.begin(); it != worldlist.end(); ++it) {
        if (it->get()->name == name) {
            if (it->get()->name == active->name) active = nullptr;
            worldlist.erase(it);
            return true; 
        }
    }

    return false;
}

void WorldManager::setActive(const std::string& name) {
    for (auto world : worldlist) {
        if (world->name == name) {
            active = world;
            return;
        }
    }
}

std::shared_ptr<World> WorldManager::getActive() {
    return active;
}

std::vector<std::shared_ptr<World>> WorldManager::getAllScene() {
    return worldlist;
}
