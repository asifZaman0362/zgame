//#include "mesh.hpp"

#include <glad/glad.h>

#include "logger.hpp"
#include "mesh.hpp"
#include "types.hpp"

namespace zifmann::zgame::core {
Mesh::Mesh(std::vector<Vertex> verts, std::vector<int> tris,
           AssetManager::ShaderProgram shader, uint texture) {
    this->texture = texture;
    triangle_count = tris.size();
    vertex_count = verts.size() * 5;
    float vert_data[5 * vertex_count];
    int i = 0;
    for (auto vert : verts) {
        vert_data[i++] = vert.position.x;
        vert_data[i++] = vert.position.y;
        vert_data[i++] = vert.position.z;
        //vert_data[i++] = vert.normal.x;
        //vert_data[i++] = vert.normal.y;
        //vert_data[i++] = vert.normal.z;
        vert_data[i++] = vert.uv.x;
        vert_data[i++] = vert.uv.y;
        log_debug("vertex: %f %f %f uv: %f %f", vert.position.x, vert.position.y, vert.position.z, vert.uv.x, vert.uv.y);
    }
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(float), vert_data,
                 GL_STATIC_DRAW);
    //unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tris.size() * sizeof(int), &tris[0],
                 GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    /*glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);*/
    glBindVertexArray(0);
    this->shader = shader;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Mesh::draw(glm::mat4 transform) {
    glUseProgram(shader);
    glBindVertexArray(vao);
    auto transform_location = glGetUniformLocation(shader, "transform");
    glUniformMatrix4fv(transform_location, 1, GL_FALSE,
                       glm::value_ptr(transform));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    auto textureId  = glGetUniformLocation(shader, "ourTexture");
    glUniform1i(textureId, 0);
    //auto lightPos = glGetUniformLocation(shader, "lightPos");
    //glUniform3f(lightPos, 1.0f, 0.5f, 1.0f);
    glDrawElements(GL_TRIANGLES, triangle_count, GL_UNSIGNED_INT, 0);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Mesh::set_shader(AssetManager::ShaderProgram shader) {
    this->shader = shader;
}
}  // namespace zifmann::zgame::core
