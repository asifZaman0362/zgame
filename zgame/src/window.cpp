#include <glad/glad.h>
#include <iostream>
#include "window.hpp"

namespace zifmann::zgame::core
{

    Window create_window(WindowSettings settings) {
        glfwInit();
        glfwWindowHint(GLFW_VERSION_MAJOR, settings.version_major);
        glfwWindowHint(GLFW_VERSION_MINOR, settings.version_minor);
        Window window = glfwCreateWindow(
            settings.width, settings.height, settings.title, 
            settings.fullscreen ? glfwGetPrimaryMonitor() : nullptr, 
            nullptr
        );
        if (!window) {
            std::cerr << "Failed to create window!" << std::endl;
            return nullptr;
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cerr << "Failed to load GLAD!" << std::endl;
            return nullptr;
        }
        return window;
    }

    void close_window(Window window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
} // namespace zifmann::zgame::core::window
