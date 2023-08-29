#ifndef ZIFMANN_ZGAME_CORE_MESH_HPP
#define ZIFMANN_ZGAME_CORE_MESH_HPP

#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "assetmanager.hpp"
#include "ecs.hpp"
#include "lighting.hpp"
#include "material.hpp"

namespace zifmann::zgame::core::rendering {
struct Mesh {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int triangle_count;
    unsigned int vertex_count;
};

struct MeshRenderer {
    Mesh *mesh;
    Material *shared_material;
};

void CreateMesh(Mesh *mesh, std::vector<Vertex> verts, std::vector<int> tris);

void DeleteMesh(Mesh *mesh);



}  // namespace zifmann::zgame::core::rendering

#endif
