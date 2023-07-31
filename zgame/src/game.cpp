#include "game.hpp"

#include <iostream>

#include "assetmanager.hpp"
#include "gameobject.hpp"
#include "mesh.hpp"
#include "obj.hpp"
#include "triangle.hpp"
#include "types.hpp"
#include "window.hpp"

namespace zifmann::zgame::core::game {
Mesh* mesh;
float angle = 0.0;
GameObject* gameObject;
void process_input(Window window) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void resize(Window window, int width, int height) {
    glViewport(0, 0, width, height);
}

void render(Window window) {
    float dt = (float)glfwGetTime();
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // test::draw_triangle();
    // gameObject->rotate(glm::vec3(0, 0.1f, 0));
    gameObject->set_rotation(glm::vec3(1.0f, 1.0f, 1.0f) * dt * 10.0f);
    // gameObject->translate(glm::vec3(0.001f, 0.0f, 0.0f));
    // gameObject->set_position(glm::vec3(glm::sin((float)glfwGetTime()), 0,
    // 0));
    gameObject->draw();
    // glPopMatrix();
    glfwSwapBuffers(window);
}

void create_mesh() {
    // std::vector<float> vertices = {0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f,
    //  -0.5f, -0.5f, 0.0f, -0.5f, 0.5f,  0.0f};
    // std::vector<int> indices = {0, 1, 3, 1, 2, 3};
    auto shader =
        AssetManager::LoadShaderProgram("res/vert.glsl", "res/frag.glsl");
    auto obj = AssetManager::LoadObjModel("res/cube.obj").lock().get();
    if (!obj) {
        exit(-1);
    }
    auto texture = AssetManager::LoadTexture("res/tex.png").lock()->get_id();
    mesh = new Mesh(obj->data, obj->indices, *shader.lock().get(), texture);
    gameObject =
        new GameObject(mesh, glm::vec3(0.0f), glm::vec3(0.5f), glm::vec3(0.0f));
}

int start() {
    Window window = create_window(WindowSettings{});
    if (!window) {
        return EXIT_FAILURE;
    }
    glfwSetFramebufferSizeCallback(window, resize);
    create_mesh();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        render(window);
    }
    delete mesh;
    delete gameObject;
    close_window(window);
    return EXIT_SUCCESS;
}
}  // namespace zifmann::zgame::core::game
