#include "window.hpp"

#include <iostream>

namespace zifmann::zgame::core {

Window create_window(WindowSettings settings) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.version_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.version_minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    Window window = glfwCreateWindow(
        settings.width, settings.height, settings.title,
        settings.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window!" << std::endl;
        return nullptr;
    }
    glfwMakeContextCurrent(window);
#ifndef __APPLE__
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load GLAD!" << std::endl;
        return nullptr;
    }
#endif
    return window;
}

void close_window(Window window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}
}  // namespace zifmann::zgame::core
