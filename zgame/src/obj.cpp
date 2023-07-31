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
#include <glm/gtc/type_ptr.hpp>

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
    bool smooth = false;

    std::vector<Vertex> vert_data;
    std::vector<int> indices;
    std::vector<std::tuple<int, int, int>> entries;

    std::string line;
    while (!file.eof()) {
        try {
            std::getline(file, line);
            if (line.starts_with("vt")) {
                float x, y;
                sscanf(line.c_str(), "vt %f %f", &x, &y);
                uvs.push_back({x, y});
            } else if (line.starts_with("vn")) {
                float x, y, z;
                sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
                normals.push_back({x, y, z});
            } else if (line.starts_with("v")) {
                float x, y, z;
                sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
                vertices.push_back({x, y, z});
            } else if (line.starts_with("f")) {
                int v1 = 0, vt1 = 0, vn1 = 0;
                int v2 = 0, vt2 = 0, vn2 = 0;
                int v3 = 0, vt3 = 0, vn3 = 0;
                sscanf(line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
                auto entry1 = std::make_tuple(v1, vt1, vn1);
                auto entry2 = std::make_tuple(v2, vt2, vn2);
                auto entry3 = std::make_tuple(v3, vt3, vn3);
                /*indices.push_back(vert_data.size());
                indices.push_back(vert_data.size() + 1);
                indices.push_back(vert_data.size() + 2);
                vert_data.push_back(Vertex{vertices[v1 - 1], normals[vn1 - 1], uvs[vt1 - 1]});
                vert_data.push_back(Vertex{vertices[v2 - 1], normals[vn2 - 1], uvs[vt2 - 1]});
                vert_data.push_back(Vertex{vertices[v3 - 1], normals[vn3 - 1], uvs[vt3 - 1]});*/
                auto position = std::find(entries.begin(), entries.end(), entry1);
                if (position == std::end(entries)) {
                    entries.push_back(entry1);
                    indices.push_back(vert_data.size());
                    vert_data.push_back(Vertex{vertices[v1 - 1], normals[vn1 - 1], uvs[vt1 - 1]});
                } else {
                    indices.push_back(std::distance(entries.begin(), position));
                }
                position = std::find(entries.begin(), entries.end(), entry2);
                if (position == std::end(entries)) {
                    entries.push_back(entry2);
                    indices.push_back(vert_data.size());
                    vert_data.push_back(Vertex{vertices[v2 - 1], normals[vn2 - 1], uvs[vt2 - 1]});
                } else {
                    indices.push_back(std::distance(entries.begin(), position));
                }
                position = std::find(entries.begin(), entries.end(), entry3);
                if (position == std::end(entries)) {
                    entries.push_back(entry3);
                    indices.push_back(vert_data.size());
                    vert_data.push_back(Vertex{vertices[v3 - 1], normals[vn3 - 1], uvs[vt3 - 1]});
                } else {
                    indices.push_back(std::distance(entries.begin(), position));
                }
            } else if (line.starts_with("s")) {
                char smoothing[10];
                sscanf(line.c_str(), "s %s", smoothing);
                if (strcmp(smoothing, "on") == 0 || strcmp(smoothing, "1") == 0) {
                    smooth = true;
                }
            } else continue;
        } catch (std::exception e) {
            return ParseError;
        }
    }
    dest.data = vert_data;
    dest.indices = indices;
    return Success;
}
}  // namespace zifmann::zgame::core::obj_loader
