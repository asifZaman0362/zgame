#include "triangle.hpp"

#include <iostream>

#include "shader.hpp"

namespace zifmann::zgame::test {
void draw_triangle() {
    using namespace zgame::core::rendering::shader;
    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
                        0.0f,  0.0f,  0.5f, 0.0f};
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
    unsigned int shader;
    char log[512];
    ShaderLoadStatus code =
        load_shader_program("res/vert.glsl", "res/frag.glsl", shader, log);
    if (code != ShaderLoadStatus::Success) {
        std::cerr << "failed to load shader: " << code << "\nLog: " << log
                  << std::endl;
        exit(-1);
    }
    glUseProgram(shader);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

}  // namespace zifmann::zgame::test
