#ifndef ZIFMANN_ZGAME_CORE_TYPES_HPP
#define ZIFMANN_ZGAME_CORE_TYPES_HPP

namespace zifmann::zgame::core {
template <typename T>
struct vec2 {
    T x, y;
};

template <typename T>
struct vec3 {
    T x, y, z;
};

template <typename T>
struct vec4 {
    T w, x, y, z;
};

template<typename T>
bool operator==(const vec2<T>& left, const vec2<T>& right) {
    return left.x == right.x && left.y == right.y;
}

template<typename T>
bool operator==(const vec3<T>& left, const vec3<T>& right) {
    return left.x == right.x && left.y == right.y && left.z == right.z;
}

typedef vec2<float> vec2f;
typedef vec3<float> vec3f;
typedef vec4<float> vec4f;
typedef vec2<int> vec2i;
typedef vec3<int> vec3i;
typedef vec4<int> vec4i;
typedef vec2<unsigned int> vec2ui;
typedef vec3<unsigned int> vec3ui;
typedef vec4<unsigned int> vec4ui;

struct Vertex {
    vec3f position;
    vec3f normal;
    vec2f uv;
};

}  // namespace zifmann::zgame::core

#endif
