#include "game.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

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
zifmann::zgame::core::systems::Light light_source {
    .position = { 1.0f, 1.0f, 0.0f },
    .color = { 1.0f, 0.8f, 0.65 },
    .intensity = 1.0f
};

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

/*
void mouse_move_callback(Window window, double xpos, double ypos) {
    if (last_mouse_x == 69420 || last_mouse_y == 69420) {
    } else {
        dx = xpos - last_mouse_x;
        dy = last_mouse_y - ypos;
    }
    last_mouse_x = xpos;
    last_mouse_y = ypos;
}*/

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
    float currentTime = (float)glfwGetTime();
    float dt = currentTime - prevFrameTime;
    float fps = 1 / dt;
    //zifmann::logger::log_debug("FPS: %f", fps);
    prevFrameTime = currentTime;
    glClearColor(0.5f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // camera.rotate(glm::vec3(0, 1, 0) * dt);
    glm::vec3 rot(0);
    rot.y = -dx;
    rot.x = -dy;
    dx = 0;
    dy = 0;
    camera.rotate(rot * dt);
    glm::vec3 cam_rot = camera.get_rotation();
    glm::vec3 movement(input_x, 0, input_y);
    glm::mat4 transformation(1.0f);
    transformation = glm::rotate(transformation, -cam_rot.x, glm::vec3(1, 0, 0));
    transformation = glm::rotate(transformation, -cam_rot.y, glm::vec3(0, 1, 0));
    transformation = glm::rotate(transformation, -cam_rot.z, glm::vec3(0, 0, 1));
    camera.translate((glm::vec4(movement, 0.0f) * transformation) * dt);
    projected_view_matrix = camera.get_view_matrix();
    coordinator.Update(dt);
    glfwSwapBuffers(window);
}

void create_mesh() {
    auto shader =
        AssetManager::LoadShaderProgram("res/vert.glsl", "res/frag.glsl");
    auto obj = AssetManager::LoadObjModel("res/cube.obj");
    if (!obj) {
        exit(-1);
    }
    auto texture = AssetManager::LoadTexture("res/tex.png");
    mesh = new Mesh();
    CreateMesh(mesh, obj->data, obj->indices, shader, texture->get_id());
}

class CameraController : public input::KeyListener, public input::MouseListener {

    void OnKeyPress(int key, int mods) override {
        if (key == GLFW_KEY_W) {
            input_y = -1;
        } else if (key == GLFW_KEY_S) {
            input_y = 1;
        }
        if (key == GLFW_KEY_A) {
            input_x = -1;
        } else if (key == GLFW_KEY_D) {
            input_x = 1;
        }
    }

    void OnKeyRelease(int key, int mods) override {
        if (key == GLFW_KEY_W) {
            input_y = 0;
        } else if (key == GLFW_KEY_S) {
            input_y = 0;
        }
        if (key == GLFW_KEY_A) {
            input_x = 0;
        } else if (key == GLFW_KEY_D) {
            input_x = 0;
        }
    }

    void OnMouseMove(double _dx, double _dy) override {
        dx = _dx;
        dy = _dy;
    }

};

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
    CameraController controller;
    zifmann::zgame::core::input::AddRawKeyListener(&controller);
    zifmann::zgame::core::input::AddMouseListener(&controller);
    set_callbacks(window);
    input::lock_mouse(window);
    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        render(window);
    }
    DeleteMesh(mesh);
    close_window(window);
    return EXIT_SUCCESS;
}
}  // namespace zifmann::zgame::core::game
