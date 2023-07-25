#ifndef ZIFMANN_ZGAME_CORE_MESH_HPP
#define ZIFMANN_ZGAME_CORE_MESH_HPP

#include <vector>

namespace zifmann::zgame::core {
class Mesh {
   private:
    unsigned int vao;

   public:
    Mesh(std::vector<float> vertices, std::vector<int> triangles);
    ~Mesh();
};
}  // namespace zifmann::zgame::core

#endif