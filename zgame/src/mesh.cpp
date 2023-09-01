//#include "mesh.hpp"

#include "mesh.hpp"

#include <cstring>
#include <unordered_map>

#include "glheader.hpp"
#include "glm/ext/vector_float3.hpp"
#include "logger.hpp"
#include "types.hpp"

namespace zifmann::zgame::core::rendering {
void CreateMesh(Mesh *mesh, std::vector<Vertex> verts, std::vector<int> tris) {
    mesh->triangle_count = tris.size();
    mesh->vertex_count = verts.size() * 11;
    float *vert_data = new float[11 * mesh->vertex_count];
    int i = 0;
    std::unordered_map<int, float[3]> tangentData;
    for (size_t i = 0; i < tris.size(); i += 3) {
        auto v1 = verts[tris[i]].position;
        auto v2 = verts[tris[i + 1]].position;
        auto v3 = verts[tris[i + 2]].position;
        auto uv1 = verts[tris[i]].uv;
        auto uv2 = verts[tris[i + 1]].uv;
        auto uv3 = verts[tris[i + 2]].uv;
        auto e1 = v2 - v1;
        auto e2 = v3 - v1;
        auto duv1 = uv2 - uv1;
        auto duv2 = uv3 - uv1;
        float f = 1.0f / (duv1.x * duv2.y - duv2.x * duv1.y);
        float tx = f * (duv2.y * e1.x - duv1.y * e2.x);
        float ty = f * (duv2.y * e1.y - duv1.y * e2.y);
        float tz = f * (duv2.y * e1.z - duv1.y * e2.z);
        tangentData[tris[i]][0] = tx;
        tangentData[tris[i]][1] = ty;
        tangentData[tris[i]][2] = tz;
        tangentData[tris[i+1]][0] = tx;
        tangentData[tris[i+1]][1] = ty;
        tangentData[tris[i+1]][2] = tz;
        tangentData[tris[i+2]][0] = tx;
        tangentData[tris[i+2]][1] = ty;
        tangentData[tris[i+2]][2] = tz;
        tangentData[tris[i+3]][0] = tx;
        tangentData[tris[i+3]][1] = ty;
        tangentData[tris[i+3]][2] = tz;
        logger::log_debug("i %i tx %f ty %f tz %f", tris[i], tangentData[tris[i]][0], tangentData[tris[i]][1], tangentData[tris[i]][2]);
    }
    int j = 0, d = 0;
    for (auto vert : verts) {
        d = i;
        vert_data[i++] = vert.position.x;
        vert_data[i++] = vert.position.y;
        vert_data[i++] = vert.position.z;
        vert_data[i++] = vert.normal.x;
        vert_data[i++] = vert.normal.y;
        vert_data[i++] = vert.normal.z;
        vert_data[i++] = vert.uv.x;
        vert_data[i++] = vert.uv.y;
        vert_data[i++] = tangentData[j][0];
        vert_data[i++] = tangentData[j][1];
        vert_data[i++] = tangentData[j][2];
        zifmann::logger::log_debug(
            "vertex x%f y%f z%f nx%f ny%f nz%f u%f v%f tx%f ty%f tz%f",
            vert_data[d], vert_data[d + 1], vert_data[d + 2], vert_data[d + 3],
            vert_data[d + 4], vert_data[d + 5], vert_data[d + 6],
            vert_data[d + 7], tangentData[d][0], tangentData[d][1],
            tangentData[d][2]);
        j++;
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float),
                          (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float),
                          (void *)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);
}

void DeleteMesh(Mesh *mesh) {
    glDeleteBuffers(1, &mesh->vbo);
    glDeleteVertexArrays(1, &mesh->vao);
    free(mesh);
}

}  // namespace zifmann::zgame::core::rendering
