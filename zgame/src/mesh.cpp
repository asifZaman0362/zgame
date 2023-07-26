#include "mesh.hpp"

#include <glad/glad.h>

#include "logger.hpp"

namespace zifmann::zgame::core {
Mesh::Mesh(std::vector<vec3f> verts, std::vector<int> tris,
           AssetManager::ShaderProgram shader) {
    triangle_count = tris.size();
    vertex_count = verts.size() * 3;
    float vertices[vertex_count];
    int i = 0;
    for (auto& vert : verts) {
        vertices[i++] = vert.x;
        vertices[i++] = vert.y;
        vertices[i++] = vert.z;
    }
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vertices,
                 GL_STATIC_DRAW);
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tris.size() * sizeof(int), &tris[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    this->shader = shader;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::draw() {
    glUseProgram(shader);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, triangle_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::set_shader(AssetManager::ShaderProgram shader) {
    this->shader = shader;
}
}  // namespace zifmann::zgame::core
