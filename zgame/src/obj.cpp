#include "obj.hpp"

#include <array>
#include <exception>
#include <optional>
#include <tuple>
#include <utility>

#include "logger.hpp"
#include "types.hpp"
#include "utils.hpp"

#define opt(a) (a == std::nullopt ? "none" : std::to_string(a.value()))

namespace zifmann::zgame::core::obj_loader {
ObjLoadStatus load_file(const std::string& path) {
    using namespace zifmann::zgame::core::utils::string;
    std::ifstream file(path);
    if (!file.is_open()) {
        return ObjLoadStatus::ReadError;
    }
    std::vector<vec3f> vertices;
    std::vector<vec3f> normals;
    std::vector<vec2f> uvs;
    std::vector<vec3<vec3<std::optional<uint>>>> faces;

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
                vec3<std::optional<uint>> v1, v2, v3;
                if (v1tokens.size() == 1) {
                    v1 = {std::optional(std::stoi(v1tokens[0])), std::nullopt,
                          std::nullopt};
                    v2 = {std::optional(std::stoi(v2tokens[0])), std::nullopt,
                          std::nullopt};
                    v3 = {std::optional(std::stoi(v3tokens[0])), std::nullopt,
                          std::nullopt};
                } else if (v1tokens.size() == 2) {
                    v1 = {std::optional(std::stoi(v1tokens[0])),
                          std::optional(std::stoi(v1tokens[1])), std::nullopt};
                    v2 = {std::optional(std::stoi(v2tokens[0])),
                          std::optional(std::stoi(v2tokens[1])), std::nullopt};
                    v3 = {std::optional(std::stoi(v3tokens[0])),
                          std::optional(std::stoi(v3tokens[1])), std::nullopt};
                } else {
                    v1 = {std::optional(std::stoi(v1tokens[0])),
                          !v1tokens[1].empty()
                              ? std::optional(std::stoi(v1tokens[1]))
                              : std::nullopt,
                          std::optional(std::stoi(v1tokens[2]))};
                    v2 = {std::optional(std::stoi(v2tokens[0])),
                          !v2tokens[1].empty()
                              ? std::optional(std::stoi(v2tokens[1]))
                              : std::nullopt,
                          std::optional(std::stoi(v2tokens[2]))};
                    v3 = {std::optional(std::stoi(v3tokens[0])),
                          !v3tokens[1].empty()
                              ? std::optional(std::stoi(v3tokens[1]))
                              : std::nullopt,
                          std::optional(std::stoi(v3tokens[2]))};
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
    std::cout << ("Loaded OBJ model:\nAttributes:");
    std::cout << ("\tVertices:\n");
    for (auto& vert : vertices) {
        std::cout << "\tx: " << vert.x << " y: " << vert.y << " z: " << vert.z
                  << "\n";
    }
    std::cout << ("\tUVs:\n");
    for (auto& uv : uvs) {
        std::cout << "\tu: " << uv.x << " v: " << uv.y << "\n";
    }
    std::cout << ("\tNormals:\n");
    for (auto& norm : normals) {
        std::cout << "\tx: " << norm.x << " y: " << norm.y << " z: " << norm.z
                  << "\n";
    }
    std::cout << ("\tFaces:\n");
    for (auto& face : faces) {
        std::cout << "\t" << opt(face.x.x) << "/" << opt(face.x.y) << "/"
                  << opt(face.x.z);
        std::cout << "\t" << opt(face.y.x) << "/" << opt(face.y.y) << "/"
                  << opt(face.y.z);
        std::cout << "\t" << opt(face.z.x) << "/" << opt(face.z.y) << "/"
                  << opt(face.z.z) << "\n";
    }
    return Success;
}
}  // namespace zifmann::zgame::core::obj_loader
