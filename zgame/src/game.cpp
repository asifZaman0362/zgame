#include "game.hpp"

#include "material.hpp"

#define GLFW_INCLUDE_NONE

#include <iostream>

#include "assetmanager.hpp"
#include "camera.hpp"
#include "ecs.hpp"
#include "input.hpp"
#include "logger.hpp"
#include "mesh.hpp"
#include "obj.hpp"
#include "renderer.hpp"
#include "transform.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "window.hpp"

Coordinator coordinator;

glm::vec3 camera_position;
glm::mat4 projected_view_matrix;
glm::mat4 projection_matrix;
glm::mat4 view_matrix;

zifmann::zgame::core::rendering::Light light_source{
    .intensity = 1.0f,
    .color = {1.0f, 1.0f, 1.0f},
};
zifmann::zgame::core::Transform light_transform{.position = {1.0f, 0.0f, 0.0f},
                                                .euler_rotation = glm::vec3(0),
                                                .scale = glm::vec3(1)};
glm::vec3 ambient = {0.1f, 0.1f, 0.2f};

#include <random>

// Function to generate random numbers within a range [min, max]
int generateRandomNumber(int min, int max) {
    std::random_device rd;  // Seed generator
    std::mt19937 mt(rd());  // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max);  // Distribution

    return dist(mt);  // Generate and return a random number
}

namespace zifmann::zgame::core::game {
rendering::MeshRenderer mesh_renderer;
float angle = 0.0;
float prevFrameTime = 0;
Camera camera;
float input_x = 0;
float input_y = 0;
// TODO: update this to not use magic number
double last_mouse_x = 69420;
double last_mouse_y = 69420;

float dx = 0, dy = 0;

#define GLFW_KEY(WIN, KEY) glfwGetKey(WIN, KEY) == GLFW_PRESS

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
    zifmann::logger::log_debug("FPS: %f", fps);
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
    transformation =
        glm::rotate(transformation, -cam_rot.x, glm::vec3(1, 0, 0));
    transformation =
        glm::rotate(transformation, -cam_rot.y, glm::vec3(0, 1, 0));
    transformation =
        glm::rotate(transformation, -cam_rot.z, glm::vec3(0, 0, 1));
    camera.translate((glm::vec4(movement, 0.0f) * transformation) * dt);
    projected_view_matrix = camera.get_view_matrix();
    view_matrix = camera.get_view();
    projection_matrix = camera.get_projection();
    camera_position = camera.get_position();
    coordinator.Update(dt);
    glfwSwapBuffers(window);
}

void create_mesh() {
    auto obj = AssetManager::LoadObjModel("res/cube.obj");
    if (!obj) {
        exit(-1);
    }
    unsigned diff = AssetManager::LoadTexture("res/diff.jpg")->get_id();
    unsigned normal =
        AssetManager::LoadTexture("res/normal.jpg")->get_id();
    unsigned metal = AssetManager::LoadTexture("res/metal.jpg")->get_id();
    unsigned rough = AssetManager::LoadTexture("res/roughness.jpg")->get_id();
    auto mesh = new rendering::Mesh();
    CreateMesh(mesh, obj->data, obj->indices);
    auto shared_material = rendering::CreatePbrMaterial(
        "default", rendering::PbrWorkflowType::Specular,
        glm::vec3(1.0f, 1.0f, 1.0f), diff, metal, normal, 0, rough, 1, 64);
    mesh_renderer = {mesh, shared_material};
}

class CameraController : public input::KeyListener,
                         public input::MouseListener {
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
        return utils::SignatureHelper(1, GetComponentId<Transform>());
    }
    void Update(float dt) override {
        float time = (float)glfwGetTime();
        for (auto entity : m_entities) {
            auto transform = coordinator.GetComponent<Transform>(entity);
            transform->euler_rotation =
                glm::vec3(1.0f, 1.0f, 1.0f) * time * 10.0f;
        }
    }
};

Transform GetRandomTransform() {
    Transform t;
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
    //logger::init();
    WindowSettings settings{};
    Window window = create_window(settings);
    if (!window) {
        return EXIT_FAILURE;
    }
    create_mesh();
    coordinator.RegisterComponent<rendering::MeshRenderer>();
    coordinator.RegisterComponent<Transform>();
    //coordinator.LoadSystem<rendering::Renderer<rendering::PbrMaterial>>();
    coordinator.LoadSystem<RotationSystem>();
    for (int i = 0; i < 1000000; i++) {
        Entity e = coordinator.CreateEntity();
        Transform transform = GetRandomTransform();
        coordinator.AddComponent<Transform>(e, transform);
        coordinator.AddComponent<rendering::MeshRenderer>(e, mesh_renderer);
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
    //logger::flush();
    DeleteMesh(mesh_renderer.mesh);
    close_window(window);
    return EXIT_SUCCESS;
}
}  // namespace zifmann::zgame::core::game
