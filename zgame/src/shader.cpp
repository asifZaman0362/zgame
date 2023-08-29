#include "shader.hpp"

#include <glad/glad.h>

#include <fstream>

#include "logger.hpp"

using namespace zifmann::logger;

namespace zifmann::zgame::core::rendering::shader {
ShaderLoadStatus load_shader(const char *path, GLenum type, unsigned int &id,
                             char log[512]) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return ShaderLoadStatus::ReadError;
    }
    std::istreambuf_iterator<char> it{file}, end;
    std::string content(it, end);
    unsigned int shader = glCreateShader(type);
    if (!shader) {
        return ShaderLoadStatus::AllocationError;
    }
    const char *buffer = content.c_str();
    glShaderSource(shader, 1, &buffer, nullptr);
    glCompileShader(shader);
    int result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(shader, 512, nullptr, log);
        return ShaderLoadStatus::CompilationError;
    }
    id = shader;
    return ShaderLoadStatus::Success;
}

ShaderLoadStatus load_shader_program(const char *vert_path,
                                     const char *frag_path, unsigned int &id,
                                     char log_output[512]) {
    unsigned int vert_shader, frag_shader;
    auto status =
        load_shader(vert_path, GL_VERTEX_SHADER, vert_shader, log_output);
    if (status != ShaderLoadStatus::Success) {
        log_error("failed to load vert shader");
        // std::cout << "failed to load vert shader" << std::endl;
        return status;
    }
    status =
        load_shader(frag_path, GL_FRAGMENT_SHADER, frag_shader, log_output);
    if (status != ShaderLoadStatus::Success) {
        log_error("failed to load fragment shader");
        // std::cout << "failed to load frag shader" << std::endl;
        return status;
    }
    unsigned int program = glCreateProgram();
    if (!program) {
        return ShaderLoadStatus::AllocationError;
    }
    glAttachShader(program, vert_shader);
    glAttachShader(program, frag_shader);
    glLinkProgram(program);
    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);
    int result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(program, 512, nullptr, log_output);
        return ShaderLoadStatus::LinkError;
    }
    id = program;
    return ShaderLoadStatus::Success;
}
template<>
void SetUniform<float, 1> (ShaderProgram shader, const char *name, glm::vec<1, float> u) {
    auto location = glGetUniformLocation(shader, name);
    glUniform1f(location, u.x);
}

template<>
void SetUniform<int, 1> (ShaderProgram shader, const char *name, glm::vec<1, int> u) {
    auto location = glGetUniformLocation(shader, name);
    glUniform1i(location, u.x);
}

template<>
void SetUniform<float, 2> (ShaderProgram shader, const char *name, glm::vec<2, float> u) {
    auto location = glGetUniformLocation(shader, name);
    glUniform2f(location, u.x, u.y);
}

template<>
void SetUniform<float, 3> (ShaderProgram shader, const char *name, glm::vec<3, float> u) {
    auto location = glGetUniformLocation(shader, name);
    glUniform3f(location, u.x, u.y, u.z);
}

void SetUniform(ShaderProgram shader, const char *name, glm::mat4 mat) {
    auto location = glGetUniformLocation(shader, name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

}  // namespace zifmann::zgame::core::rendering::shader
