#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "types.hpp"

float wrap_angle(int x) { return (x < 0) ? 360 + x : x; }

namespace zifmann::zgame::core {
    Camera::Camera() = default;

    void Camera::scale(glm::vec3 scale) {
        m_scale = scale;
    }

    void Camera::translate(glm::vec3 translation) {
        m_translation += translation;
    }

    void Camera::rotate(glm::vec3 angles) {
        float x = wrap_angle(m_rotation_angles.x + angles.x);
        float y = wrap_angle(m_rotation_angles.y + angles.y);
        float z = wrap_angle(m_rotation_angles.z + angles.z);
        m_rotation_angles.x = x;
        m_rotation_angles.y = y;
        m_rotation_angles.z = z;
    }

    glm::mat4 Camera::get_view_matrix() {
        auto matrix = glm::translate(glm::scale(glm::mat4(1.0), m_scale), m_translation);
        matrix = glm::rotate(matrix, m_rotation_angles.x, RIGHT);
        matrix = glm::rotate(matrix, m_rotation_angles.y, UP);
        matrix = glm::rotate(matrix, m_rotation_angles.z, FORWARD);
        return matrix;
    }
}
