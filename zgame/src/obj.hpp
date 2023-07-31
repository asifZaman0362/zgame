#ifndef ZIFMANN_ZGAME_CORE_OBJ_HPP
#define ZIFMANN_ZGAME_CORE_OBJ_HPP

#include <fstream>
#include <string>
#include <vector>

#include "types.hpp"

namespace zifmann::zgame::core::obj_loader {

typedef unsigned int uint;

struct ObjData {
    /*
    std::vector<vec3f> vertices;
    std::vector<vec2f> uvs;
    std::vector<vec3f> normals;
    std::vector<vec3<vec3i>> faces;
    */
    std::vector<Vertex> data;
    std::vector<int> indices;
};

enum ObjLoadStatus { Success, ReadError, ParseError };
ObjLoadStatus load_file(const std::string& path, ObjData& dest);
}  // namespace zifmann::zgame::core::obj_loader

#endif
