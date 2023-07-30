#include "mesh.hpp"

#include <glad/glad.h>

#include "logger.hpp"

namespace zifmann::zgame::core {
Mesh::Mesh(std::vector<vec3f> verts, std::vector<int> tris,
           std::vector<vec2f> texCoords, AssetManager::ShaderProgram shader,
           uint texture) {
    this->texture = texture;
    triangle_count = tris.size();
    vertex_count = verts.size() * 3;
    auto uv_count = texCoords.size() * 2;
    float vertices[vertex_count + uv_count];
    int i = 0;
    for (auto vert : verts) {
        vertices[i++] = vert.x;
        vertices[i++] = vert.y;
        vertices[i++] = vert.z;
    }
    for (auto uv : texCoords) {
        vertices[i++] = uv.x;
        vertices[i++] = uv.y;
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
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void*)(vertex_count * sizeof(float)));
    glEnableVertexAttribArray(1);
    this->shader = shader;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::draw(glm::mat4 transform) {
    glUseProgram(shader);
    auto transform_location = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transform_location, 1, GL_FALSE,
                       glm::value_ptr(transform));
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, triangle_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::set_shader(AssetManager::ShaderProgram shader) {
    this->shader = shader;
}
}  // namespace zifmann::zgame::core
