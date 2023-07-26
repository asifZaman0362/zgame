#include "triangle.hpp"

#include <iostream>

#include "assetmanager.hpp"
#include "logger.hpp"
#include "shader.hpp"

namespace zifmann::zgame::test {
void draw_triangle() {
    using namespace zgame::core::rendering::shader;
    float vertices[] = {-0.5f, -1.0f, 0.0f, 0.5f, -1.0f,
                        0.0f,  0.0f,  0.0f, 0.0f};
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);
    auto shader = zifmann::zgame::core::AssetManager::LoadShaderProgram(
                      "res/vert.glsl", "res/other.glsl")
                      .lock()
                      .get();
    if (!shader) {
        log_error("Somethings wrong!");
        exit(-1);
    }
    glUseProgram(*shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    glUseProgram(0);
}

}  // namespace zifmann::zgame::test
