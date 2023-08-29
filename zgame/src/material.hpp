#ifndef ZIFMANN_ZGAME_MATERIAL_HPP
#define ZIFMANN_ZGAME_MATERIAL_HPP

#include "types.hpp"

namespace zifmann::zgame::core::rendering {

using ShaderProgram = unsigned int;
using TextureID = unsigned int;

struct Material {
    ShaderProgram shader_id;
};

struct LitMaterial : public Material {};

struct UnlitMaterial : public Material {};

struct __attribute__((packed)) PbrMaterial : public LitMaterial {
    vec3 diffuse;
    TextureID albedo;
    TextureID normal_map;
    TextureID displacement_map;
    TextureID metallic_map;
    TextureID specular_map;
};

struct __attribute__((packed)) StandardUnlit : public UnlitMaterial {
    vec3 diffuse;
    TextureID albedo;
};

struct __attribute__((packed)) EmissiveMaterial : public UnlitMaterial {
    float strength;
    vec3 color;
    TextureID emission_map;
    TextureID albedo;
};

Material* CreatePbrMaterial(const char* name, const vec3& diffuse,
                            const TextureID albedo, const TextureID specular,
                            const TextureID normal, const TextureID displacement,
                            const TextureID metallic);
Material* CreateUnlitMaterial(const char* name, const vec3& diffuse,
                              const TextureID albedo);
Material* CreateEmissiveMaterial(const char* name, const float strength,
                                 const vec3& color, const TextureID albedo,
                                 const TextureID emission);

}  // namespace zifmann::zgame::core::rendering

#endif