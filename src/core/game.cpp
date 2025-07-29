#include <game.hpp>
#include <camera.hpp>


GameLoop::GameLoop(const std::string& name, int w, int h) 
    : name(name), width(w), height(h) {
}

void GameLoop::init() {
    if (!glfwInit()) {
        std::cout << "Failed setup OpenGL!\n";
        exit(EXIT_FAILURE);
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif

    _window = glfwCreateWindow(1024, 600, "My Window", NULL, NULL);

    if (!_window) {
        std::cout << "Failed init window\n";
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL successfully create context!\n";

    _world_manager = new WorldManager();
}

GameLoop::~GameLoop() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}



void GameLoop::run() {
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    while(!glfwWindowShouldClose(_window)) {
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        _world_manager->getActive()->update(deltaTime);
        _world_manager->getActive()->render();

        glfwSwapBuffers(_window);
        glfwPollEvents();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // std::cout << "DeltaTime -> " << deltaTime << "\n";
    }
}

WorldManager* GameLoop::getWorldManager() {
    return _world_manager;
}
