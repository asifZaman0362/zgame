#include "game.hpp"

#include <iostream>

#include "triangle.hpp"
#include "window.hpp"

namespace zifmann::zgame::core::game {
void process_input(Window window) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(Window window) {
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    test::draw_triangle();
    glfwSwapBuffers(window);
}

int start() {
    Window window = create_window(WindowSettings{});
    if (!window) {
        return EXIT_FAILURE;
    }
    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        render(window);
    }
    close_window(window);
    return EXIT_SUCCESS;
}
}  // namespace zifmann::zgame::core::game
