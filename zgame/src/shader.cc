#include "shader.hpp"
#include <fstream>
#include <glad/glad.h>

namespace zifmann::zgame::core::rendering::shader
{
    ShaderLoadStatus load_shader(const char *path, GLenum type, unsigned int &id, char log[512]) {
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

    ShaderLoadStatus load_shader_program(const char *vert_path, const char *frag_path, unsigned int &id, char log[512]) {
        unsigned int vert_shader, frag_shader;
        auto status = load_shader(vert_path, GL_VERTEX_SHADER, vert_shader, log);
        if (status != ShaderLoadStatus::Success) {
            return status;
        }
        status = load_shader(frag_path, GL_FRAGMENT_SHADER, frag_shader, log);
        if (status != ShaderLoadStatus::Success) {
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
            glGetProgramInfoLog(program, 512, nullptr, log);
            return ShaderLoadStatus::LinkError;
        }
        id = program;
        return ShaderLoadStatus::Success;
    }
} // namespace zifmann::zgame::core::rendering::shader
