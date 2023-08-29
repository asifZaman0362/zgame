//#include "mesh.hpp"

#include "mesh.hpp"

#include <glad/glad.h>

#include "logger.hpp"
#include "types.hpp"

namespace zifmann::zgame::core::rendering {
void CreateMesh(Mesh *mesh, std::vector<Vertex> verts, std::vector<int> tris) {
    mesh->triangle_count = tris.size();
    mesh->vertex_count = verts.size() * 8;
    float *vert_data = new float[8 * mesh->vertex_count];
    int i = 0;
    for (auto vert : verts) {
        vert_data[i++] = vert.position.x;
        vert_data[i++] = vert.position.y;
        vert_data[i++] = vert.position.z;
        vert_data[i++] = vert.normal.x;
        vert_data[i++] = vert.normal.y;
        vert_data[i++] = vert.normal.z;
        vert_data[i++] = vert.uv.x;
        vert_data[i++] = vert.uv.y;
    }
    glGenVertexArrays(1, &mesh->vao);
    glBindVertexArray(mesh->vao);
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, mesh->vertex_count * sizeof(float), vert_data,
                 GL_STATIC_DRAW);
    // unsigned int ebo;
    glGenBuffers(1, &mesh->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tris.size() * sizeof(int), &tris[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void DeleteMesh(Mesh *mesh) {
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    free(mesh);
}

}  // namespace zifmann::zgame::core::rendering
