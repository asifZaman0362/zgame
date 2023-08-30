#include "camera.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "types.hpp"

namespace zifmann::zgame::core {
Camera::Camera()
    : m_translation(glm::vec3(0)),
      m_rotation_angles(glm::vec3(0)),
      projection(Perspective),
      aspect_ratio(1.77f),
      m_ortho_bounds(0, 0, 0, 0),
      fov(60.0f),
      m_clip_dist(0.01f, 100.0f) {}

void Camera::translate(glm::vec3 translation) { m_translation += translation; }

void Camera::rotate(glm::vec3 angles) {
    float x = (m_rotation_angles.x + angles.x);
    float y = (m_rotation_angles.y + angles.y);
    float z = (m_rotation_angles.z + angles.z);
    m_rotation_angles.x = x;
    m_rotation_angles.y = y;
    m_rotation_angles.z = z;
}

void Camera::set_rotation(glm::vec3 rotation) { m_rotation_angles = rotation; }

void Camera::set_translation(glm::vec3 translation) {
    m_translation = translation;
}

void Camera::set_projection_mode(Camera::ProjectionMode mode) {
    projection = mode;
}

void Camera::set_aspect_ratio(float aspect_ratio) {
    this->aspect_ratio = aspect_ratio;
}

void Camera::set_clipping_planes(float near, float far) {
    m_clip_dist = {near, far};
}

void Camera::set_ortho_bounds(float l, float r, float t, float b) {
    m_ortho_bounds = {l, r, t, b};
}

void Camera::set_fov(float fov) { this->fov = fov; }

glm::vec3 Camera::get_rotation() {
    return m_rotation_angles;
}

glm::vec3 Camera::get_position() {
    return m_translation;
}

glm::mat4 Camera::get_view_matrix() {
    glm::mat4 proj;
    if (projection == Perspective) {
        proj = glm::perspective<float>(glm::radians(fov), (aspect_ratio),
                                       m_clip_dist.x, m_clip_dist.y);
    } else {
        proj = glm::ortho(m_ortho_bounds.x, m_ortho_bounds.y, m_ortho_bounds.z,
                          m_ortho_bounds.w);
    }
    //glm::mat4 matrix = glm::translate(glm::mat4(1.0f), -m_translation);
    //
    /*
    glm::vec3 cam_direction =
        glm::vec3(0, 0, 1);  // glm::normalize(m_translation - m_camera_target);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 cam_right = glm::normalize(glm::cross(up, cam_direction));
    glm::vec3 cam_up = glm::normalize(glm::cross(cam_direction, cam_right));
    */
    glm::mat4 matrix = glm::mat4(1.0f);

    matrix = glm::rotate(matrix, -m_rotation_angles.x, RIGHT);
    matrix = glm::rotate(matrix, -m_rotation_angles.y, UP);
    matrix = glm::rotate(matrix, -m_rotation_angles.z, FORWARD);
    matrix = glm::translate(matrix, -m_translation);
    return proj * matrix;
}

glm::mat4 Camera::get_view() {
    glm::mat4 matrix = glm::mat4(1.0f);

    matrix = glm::rotate(matrix, -m_rotation_angles.x, RIGHT);
    matrix = glm::rotate(matrix, -m_rotation_angles.y, UP);
    matrix = glm::rotate(matrix, -m_rotation_angles.z, FORWARD);
    matrix = glm::translate(matrix, -m_translation);
    return matrix;
}

glm::mat4 Camera::get_projection() {
    glm::mat4 proj;
    if (projection == Perspective) {
        proj = glm::perspective<float>(glm::radians(fov), (aspect_ratio),
                                       m_clip_dist.x, m_clip_dist.y);
    } else {
        proj = glm::ortho(m_ortho_bounds.x, m_ortho_bounds.y, m_ortho_bounds.z,
                          m_ortho_bounds.w);
    }
    return proj;
}

}  // namespace zifmann::zgame::core
