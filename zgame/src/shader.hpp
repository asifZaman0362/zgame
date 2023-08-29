#ifndef SHADER_HPP
#define SHADER_HPP

#include "glheader.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace zifmann::zgame::core::rendering::shader {
using ShaderProgram = unsigned int;
enum ShaderLoadStatus {
    Success,
    CompilationError,
    ReadError,
    LinkError,
    AllocationError
};
ShaderLoadStatus load_shader(const char *source_path, GLenum type,
                             unsigned int &id, char log[512]);
ShaderLoadStatus load_shader_program(const char *vert_source_path,
                                     const char *frag_source_path,
                                     unsigned int &id, char log[512]);

template<typename T, int N>
void SetUniform(ShaderProgram shader, const char *name, glm::vec<N, T> u);

void SetUniform(ShaderProgram shader, const char *name, glm::mat4 mat);

// unsigned int load_shader_program(const char *)
}  // namespace zifmann::zgame::core::rendering::shader

#endif
