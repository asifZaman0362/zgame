#ifndef ZIFMANN_ZGAME_CORE_CAMERA_HPP
#define ZIFMANN_ZGAME_CORE_CAMERA_HPP

#include <glm/glm.hpp>

namespace zifmann::zgame::core {
class Camera {
   public:
    Camera();
    ~Camera() = default;

    void rotate(glm::vec3 angles);
    void scale(glm::vec3 scale);
    void translate(glm::vec3 translation);
    glm::mat4 get_view_matrix();

   private:
    glm::vec3 m_scale;
    glm::vec3 m_translation;
    glm::vec3 m_rotation_angles;
};
}  // namespace zifmann::zgame::core

#endif
