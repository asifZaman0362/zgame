#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

namespace zifmann::zgame::core::rendering::shader {
    enum ShaderLoadStatus {
        Success, CompilationError, ReadError, LinkError, AllocationError
    };
    ShaderLoadStatus load_shader(const char* source_path, GLenum type, unsigned int &id, char log[512]);
    ShaderLoadStatus load_shader_program(const char *vert_source_path, const char *frag_source_path, unsigned int &id, char log[512]);
    //unsigned int load_shader_program(const char *)
}

#endif