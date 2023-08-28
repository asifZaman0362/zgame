#include "game.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "assetmanager.hpp"
#include "camera.hpp"
#include "ecs.hpp"
#include "gameobject.hpp"
#include "input.hpp"
#include "logger.hpp"
#include "mesh.hpp"
#include "obj.hpp"
#include "renderer.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "window.hpp"

Coordinator coordinator;
glm::mat4 projected_view_matrix;

#include <random>

// Function to generate random numbers within a range [min, max]
int generateRandomNumber(int min, int max) {
    std::random_device rd;  // Seed generator
    std::mt19937 mt(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max);  // Distribution

    return dist(mt);  // Generate and return a random number
}

namespace zifmann::zgame::core::game {
Mesh* mesh;
float angle = 0.0;
float prevFrameTime = 0;
// GameObject* gameObject;
Camera camera;
float input_x = 0;
float input_y = 0;
// TODO: update this to not use magic number
double last_mouse_x = 69420;
double last_mouse_y = 69420;

float dx = 0, dy = 0;

#define GLFW_KEY(WIN, KEY) glfwGetKey(WIN, KEY) == GLFW_PRESS

void mouse_move_callback(Window window, double xpos, double ypos) {
    if (last_mouse_x == 69420 || last_mouse_y == 69420) {
    } else {
        dx = xpos - last_mouse_x;
        dy = last_mouse_y - ypos;
    }
    last_mouse_x = xpos;
    last_mouse_y = ypos;
}

void process_input(Window window) {
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        input_y = -1;
    } else if (GLFW_KEY(window, GLFW_KEY_S)) {
        input_y = 1;
    }
    if (GLFW_KEY(window, GLFW_KEY_A)) {
        input_x = -1;
    } else if (GLFW_KEY(window, GLFW_KEY_D)) {
        input_x = 1;
    }
}

void resize(Window window, int width, int height) {
    glViewport(0, 0, width, height);
}

void render(Window window) {
    float currentTime = (float)glfwGetTime();
    float dt = currentTime - prevFrameTime;
    float fps = 1 / dt;
    zifmann::logger::log_debug("FPS: %f", fps);
    prevFrameTime = currentTime;
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // camera.rotate(glm::vec3(0, 1, 0) * dt);
    camera.translate(glm::vec3(input_x, 0, input_y) * dt);
    glm::vec3 rot(0);
    rot.y = -dx;
    rot.x = dy;
    dx = 0;
    dy = 0;
    camera.rotate(rot * dt);
    projected_view_matrix = camera.get_view_matrix();
    coordinator.Update(dt);
    glfwSwapBuffers(window);
    input_x = 0;
    input_y = 0;
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
    // mesh = new Mesh(obj->data, obj->indices, shader,
    // texture.get()->get_id());
    mesh = new Mesh();
    CreateMesh(mesh, obj->data, obj->indices, shader, texture->get_id());
    /*gameObject =
        new GameObject(mesh, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f));
    gameObject->rotate(glm::vec3(0, 0, 45.0f));
    gameObject->translate(glm::vec3(0, 0, -5.0f));*/
}

class RotationSystem : public ISystem {
    Signature GetSignature() override {
        return utils::SignatureHelper(1, GetComponentId<systems::Transform>());
    }
    void Update(float dt) override {
        float time = (float)glfwGetTime();
        for (auto entity : m_entities) {
            auto transform =
                coordinator.GetComponent<systems::Transform>(entity);
            transform->euler_rotation =
                glm::vec3(1.0f, 1.0f, 1.0f) * time * 10.0f;
        }
    }
};

systems::Transform GetRandomTransform() {
    systems::Transform t;
    float px = generateRandomNumber(0, 5) - 2.5f;
    float py = generateRandomNumber(0, 5) - 2.5f;
    float pz = generateRandomNumber(50, 100) / 10.0f * -1;
    float rx = generateRandomNumber(0, 360);
    float ry = generateRandomNumber(0, 360);
    float rz = generateRandomNumber(0, 360);
    float sx = generateRandomNumber(1, 5) / 10.0f;
    // float sy = generateRandomNumber(1, 5) / 10.0f;
    // float sz = generateRandomNumber(1, 5) / 10.0f;
    t.position = {px, py, pz};
    t.scale = {sx, sx, sx};
    t.euler_rotation = {rx, ry, rz};
    return t;
}

void set_callbacks(Window window) {
    using namespace zifmann::zgame::core::input;
    glfwSetFramebufferSizeCallback(window, resize);
    glfwSetKeyCallback(window, key_press_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, mouse_cursor_callback);
    glfwSetScrollCallback(window, scroll_wheel_callback);
}

int start() {
    WindowSettings settings{};
    Window window = create_window(settings);
    if (!window) {
        return EXIT_FAILURE;
    }
    create_mesh();
    coordinator.RegisterComponent<Mesh>();
    coordinator.RegisterComponent<systems::Transform>();
    coordinator.LoadSystem<systems::Renderer>();
    coordinator.LoadSystem<RotationSystem>();
    for (int i = 0; i < 100; i++) {
        Entity e = coordinator.CreateEntity();
        systems::Transform transform = GetRandomTransform();
        coordinator.AddComponent<systems::Transform>(e, transform);
        coordinator.AddComponent<Mesh>(e, *mesh);
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // set orthographic projection
    camera.set_aspect_ratio((float)settings.width / settings.height);
    camera.rotate(glm::vec3(0, 0, 90.0f));
    prevFrameTime = (float)glfwGetTime();
    zifmann::logger::log_debug("%f", prevFrameTime);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        render(window);
    }
    DeleteMesh(mesh);
    // delete gameObject;
    close_window(window);
    return EXIT_SUCCESS;
}
}  // namespace zifmann::zgame::core::game
