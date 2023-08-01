#ifndef ZIFMANN_ZGAME_CORE_GAMEOBJECT_HPP
#define ZIFMANN_ZGAME_CORE_GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "assetmanager.hpp"
#include "mesh.hpp"

namespace zifmann::zgame::core {
class GameObject {
   public:
    GameObject(Mesh* mesh, glm::vec3 pos, glm::vec3 scale,
               glm::vec3 euler_rot);
    ~GameObject();
    void translate(glm::vec3 delta);
    void rotate(glm::vec3 euler);
    void scale(glm::vec3 scale);
    void set_position(glm::vec3 pos);
    void set_rotation(glm::vec3 axes);
    void set_scale(glm::vec3 scale);
    void draw(glm::mat4);

   private:
    glm::vec3 m_rotation_angles;
    glm::vec3 m_translation;
    glm::vec3 m_scale;
    Mesh* mesh;
};
}  // namespace zifmann::zgame::core

#endif
