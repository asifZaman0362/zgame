#include "game.hpp"

#include <iostream>

#include "mesh.hpp"
#include "obj.hpp"
#include "triangle.hpp"
#include "window.hpp"

namespace zifmann::zgame::core::game {
Mesh *mesh;
void process_input(Window window) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void render(Window window) {
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // test::draw_triangle();
    mesh->draw();
    glfwSwapBuffers(window);
}

void create_mesh() {
    std::vector<float> vertices = {0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f,
                                   -0.5f, -0.5f, 0.0f, -0.5f, 0.5f,  0.0f};
    std::vector<int> indices = {0, 1, 3, 1, 2, 3};
    auto shader =
        AssetManager::LoadShaderProgram("res/vert.glsl", "res/frag.glsl");
    mesh = new Mesh(vertices, indices, *shader.lock().get());
}

int start() {
    Window window = create_window(WindowSettings{});
    if (!window) {
        return EXIT_FAILURE;
    }
    create_mesh();
    obj_loader::load_file("res/cube.obj");
    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        render(window);
    }
    delete mesh;
    close_window(window);
    return EXIT_SUCCESS;
}
}  // namespace zifmann::zgame::core::game
