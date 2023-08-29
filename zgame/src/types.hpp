#ifndef ZIFMANN_ZGAME_CORE_TYPES_HPP
#define ZIFMANN_ZGAME_CORE_TYPES_HPP
#include <glm/gtc/type_ptr.hpp>

namespace zifmann::zgame::core {

using vec4 = glm::vec4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;
using vec3i = glm::vec<3, int>;
using vec2i = glm::vec<2, int>;

using mat4 = glm::mat4;
using mat3 = glm::mat3;

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 uv;
};

static const auto UP = glm::vec3(0, 1.0f, 0);
static const auto DOWN = glm::vec3(0, -1.0f, 0);
static const auto FORWARD = glm::vec3(0, 0.0f, 1.0f);
static const auto BACKWARD = glm::vec3(0, 0.0f, -1.0f);
static const auto RIGHT = glm::vec3(1.0f, 0.0f, 0.0f);
static const auto LEFT = glm::vec3(-1.0f, 0.0f, 0.0f);

}  // namespace zifmann::zgame::core

#endif
