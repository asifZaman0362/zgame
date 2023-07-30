#include "gameobject.hpp"

#include <glad/glad.h>

#include <glm/fwd.hpp>

#include "assetmanager.hpp"
#include "logger.hpp"

float wrap_angle(int x) { return (x < 0) ? 360 + x : x; }

inline void UpdateTransform(glm::mat4 transform, unsigned int shader) {
    glUseProgram(shader);
    unsigned int transformLoc = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

static const auto UP = glm::vec3(0, 1.0f, 0);
static const auto DOWN = glm::vec3(0, -1.0f, 0);
static const auto FORWARD = glm::vec3(0, 0.0f, 1.0f);
static const auto BACKWARD = glm::vec3(0, 0.0f, -1.0f);
static const auto RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
static const auto LEFT = glm::vec3(-1.0f, 0.0f, 0.0f);

namespace zifmann::zgame::core {
GameObject::GameObject(Mesh* mesh, glm::vec3 pos, glm::vec3 scale,
                       glm::vec3 rot) {
    this->m_translation = pos;
    this->m_scale = scale;
    this->m_rotation_angles = rot;
    this->mesh = mesh;
}

GameObject::~GameObject() = default;

void GameObject::rotate(glm::vec3 angles) {
    float x = wrap_angle(m_rotation_angles.x + angles.x);
    float y = wrap_angle(m_rotation_angles.y + angles.y);
    float z = wrap_angle(m_rotation_angles.z + angles.z);
    m_rotation_angles.x = x;
    m_rotation_angles.y = y;
    m_rotation_angles.z = z;
}

void GameObject::translate(glm::vec3 delta) { this->m_translation += delta; }

void GameObject::scale(glm::vec3 scale) { this->m_scale = scale; }

void GameObject::set_position(glm::vec3 pos) { this->m_translation = pos; }

void GameObject::set_rotation(glm::vec3 euler) {
    this->m_rotation_angles = euler;
}

void GameObject::set_scale(glm::vec3 scale) {
    this->m_scale = scale;
}

void GameObject::draw() {
    auto transform =
        glm::translate(glm::scale(glm::mat4(1.0f), m_scale), m_translation);
    transform =
        glm::rotate(transform, glm::radians(m_rotation_angles.x), RIGHT);
    transform = glm::rotate(transform, glm::radians(m_rotation_angles.y), UP);
    transform =
        glm::rotate(transform, glm::radians(m_rotation_angles.z), FORWARD);
    mesh->draw(transform);
}

}  // namespace zifmann::zgame::core
