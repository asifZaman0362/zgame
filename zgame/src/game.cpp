#include "game.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "assetmanager.hpp"
#include "camera.hpp"
#include "gameobject.hpp"
#include "mesh.hpp"
#include "obj.hpp"
#include "types.hpp"
#include "window.hpp"

namespace zifmann::zgame::core::game {
Mesh* mesh;
float angle = 0.0;
GameObject* gameObject;
Camera camera;
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
    // gameObject->set_rotation(glm::vec3(1.0f, 1.0f, 1.0f) * dt * 10.0f);
    // gameObject->translate(glm::vec3(0.001f, 0.0f, 0.0f));
    // gameObject->set_position(glm::vec3(glm::sin((float)glfwGetTime()), 0,
    // 0));
    gameObject->draw(camera.get_view_matrix());
    // glPopMatrix();
    glfwSwapBuffers(window);
}

void create_mesh() {
    // std::vector<float> vertices = {0.5f,  0.5f,  0.0f, 0.5f,  -0.5f, 0.0f,
    //  -0.5f, -0.5f, 0.0f, -0.5f, 0.5f,  0.0f};
    // std::vector<int> indices = {0, 1, 3, 1, 2, 3};
    auto shader =
        AssetManager::LoadShaderProgram("res/vert.glsl", "res/frag.glsl");
    auto obj = AssetManager::LoadObjModel("res/cube.obj");
    if (!obj) {
        exit(-1);
    }
    auto texture = AssetManager::LoadTexture("res/tex.png");
    mesh = new Mesh(obj->data, obj->indices, shader, texture.get()->get_id());
    gameObject =
        new GameObject(mesh, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
    gameObject->rotate(glm::vec3(0, 0, 45.0f));
    gameObject->translate(glm::vec3(0, 0, -5.0f));
}

int start() {
    WindowSettings settings{};
    Window window = create_window(settings);
    if (!window) {
        return EXIT_FAILURE;
    }
    glfwSetFramebufferSizeCallback(window, resize);
    create_mesh();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // set orthographic projection
    camera.set_aspect_ratio((float)settings.width / settings.height);
    camera.rotate(glm::vec3(0, 0, 90.0f));
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
