#ifndef ZIFMANN_ZGAME_CORE_CAMERA_HPP
#define ZIFMANN_ZGAME_CORE_CAMERA_HPP

#include <glm/glm.hpp>

namespace zifmann::zgame::core {
class Camera {
    enum ProjectionMode { Orthographic, Perspective };

   public:
    Camera();
    ~Camera() = default;

    void rotate(glm::vec3 angles);
    void set_rotation(glm::vec3 angles);
    void translate(glm::vec3 translation);
    void set_translation(glm::vec3 translation);
    void set_projection_mode(ProjectionMode mode);
    void set_aspect_ratio(float aspect_ratio);
    void set_clipping_planes(float near, float far);
    void set_ortho_bounds(float left, float right, float top, float bottom);
    void set_fov(float fov);

    glm::mat4 get_view_matrix();

   private:
    glm::vec3 m_translation;
    glm::vec3 m_rotation_angles;
    ProjectionMode projection;
    glm::vec4 m_ortho_bounds;
    glm::vec2 m_clip_dist;
    float aspect_ratio;
    float fov;
};
}  // namespace zifmann::zgame::core

#endif
