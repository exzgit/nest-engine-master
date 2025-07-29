#pragma once

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <world.hpp>

class GameLoop {
    private:
        std::string name;
        int width = 1024, height = 600;

        GLFWwindow* _window;
        WorldManager* _world_manager = nullptr;
    
    public:
        GameLoop(const std::string& name, int w, int h);
        ~GameLoop();

        void init();
        void run();


        WorldManager* getWorldManager();
};