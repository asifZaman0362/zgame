#ifndef ZIFMANN_ZGAME_CORE_MESH_HPP
#define ZIFMANN_ZGAME_CORE_MESH_HPP

#include <vector>
#include <glm/gtc/type_ptr.hpp>

#include "assetmanager.hpp"

namespace zifmann::zgame::core {
class Mesh {
    friend class GameObject;
   private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int triangle_count;
    unsigned int vertex_count;
    AssetManager::ShaderProgram shader;  // TODO: convert to material

   public:
    Mesh(std::vector<vec3f> vertices, std::vector<int> triangles,
         AssetManager::ShaderProgram shader);
    ~Mesh();
    void draw(glm::mat4);
    void set_shader(AssetManager::ShaderProgram shader);
};
}  // namespace zifmann::zgame::core

#endif
