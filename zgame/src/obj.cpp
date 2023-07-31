#include "obj.hpp"

#include <algorithm>
#include <array>
#include <exception>
#include <optional>
#include <tuple>
#include <utility>

#include "logger.hpp"
#include "types.hpp"
#include "utils.hpp"

#define opt(a) (a == -1 ? "" : std::to_string(a))

template <typename T>
inline bool contains(const std::vector<T>& vec, const T& item) {
    return std::find(vec.begin(), vec.end(), item) != vec.end();
}

namespace zifmann::zgame::core::obj_loader {
ObjLoadStatus load_file(const std::string& path, ObjData& dest) {
    using namespace zifmann::zgame::core::utils::string;
    std::ifstream file(path);
    if (!file.is_open()) {
        return ObjLoadStatus::ReadError;
    }
    std::vector<vec3f> vertices;
    std::vector<vec3f> normals;
    std::vector<vec2f> uvs;
    std::vector<vec3<vec3i>> faces;

    std::string line;
    while (!file.eof()) {
        try {
            std::getline(file, line);
            auto tokens = split_str(line, " ");
            if (line.starts_with('#')) {
                continue;
            } else if (line.starts_with("vt")) {
                auto u = std::stof(tokens[1]);
                auto v = std::stof(tokens[2]);
                /* we dont care about supporting the w coordinate yet
                std::optional<float> w = std::nullopt;
                if (tokens.size() == 4) {
                    w = std::optional(std::stof(tokens[3]));
                }*/
                uvs.push_back({u, v});

            } else if (line.starts_with("vn")) {
                auto x = std::stof(tokens[1]);
                auto y = std::stof(tokens[2]);
                auto z = std::stof(tokens[3]);
                normals.push_back({x, y, z});
            } else if (line.starts_with("v")) {
                auto x = std::stof(tokens[1]);
                auto y = std::stof(tokens[2]);
                auto z = std::stof(tokens[3]);
                vertices.push_back({x, y, z});
            } else if (line.starts_with('f')) {
                auto v1tokens = split_str(tokens[1], "/");
                auto v2tokens = split_str(tokens[2], "/");
                auto v3tokens = split_str(tokens[3], "/");
                // vec3<std::optional<uint>> v1, v2, v3;
                vec3i v1, v2, v3;
                if (v1tokens.size() == 1) {
                    v1 = {std::stoi(v1tokens[0]) - 1, -1, -1};
                    v2 = {std::stoi(v2tokens[0]) - 1, -1, -1};
                    v3 = {std::stoi(v3tokens[0]) - 1, -1, -1};
                } else if (v1tokens.size() == 2) {
                    v1 = {std::stoi(v1tokens[0]) - 1, std::stoi(v1tokens[1]) - 1, -1};
                    v2 = {std::stoi(v2tokens[0]) - 1, std::stoi(v2tokens[1]) - 1, -1};
                    v3 = {std::stoi(v3tokens[0]) - 1, std::stoi(v3tokens[1]) - 1, -1};
                } else {
                    v1 = {std::stoi(v1tokens[0]) - 1,
                          !v1tokens[1].empty() ? std::stoi(v1tokens[1]) - 1 : -1,
                          std::stoi(v1tokens[2]) - 1};
                    v2 = {std::stoi(v2tokens[0]) - 1,
                          !v2tokens[1].empty() ? std::stoi(v2tokens[1]) - 1 : -1,
                          std::stoi(v2tokens[2]) - 1};
                    v3 = {std::stoi(v3tokens[0]) - 1,
                          !v3tokens[1].empty() ? std::stoi(v3tokens[1]) - 1 : -1,
                          std::stoi(v3tokens[2]) - 1};
                }
                faces.push_back({v1, v2, v3});
            } else {
                // discard any other attributes (not supported, yet)
                continue;
            }
        } catch (std::exception e) {
            return ParseError;
        }
    }
    std::vector<vec3f> verts;
    std::vector<vec2f> texCoords;
    for (auto face : faces) {
        dest.data.push_back(Vertex{vertices[face.x.x], {0, 0, 0}, uvs[face.x.y]});
        dest.data.push_back(Vertex{vertices[face.y.x], {0, 0, 0}, uvs[face.y.y]});
        dest.data.push_back(Vertex{vertices[face.z.x], {0, 0, 0}, uvs[face.z.y]});
    }
    dest.indices = {};
    /*dest.vertices = vertices;
    dest.normals = normals;
    dest.uvs = uvs;
    dest.faces = faces;*/
    return Success;
}
}  // namespace zifmann::zgame::core::obj_loader
