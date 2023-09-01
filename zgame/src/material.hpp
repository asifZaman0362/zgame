#ifndef ZIFMANN_ZGAME_MATERIAL_HPP
#define ZIFMANN_ZGAME_MATERIAL_HPP

#include "types.hpp"
#include "utils.hpp"

namespace zifmann::zgame::core::rendering {

using ShaderProgram = unsigned int;
using TextureID = unsigned int;

struct Material {
    ShaderProgram shader_id;
};

struct LitMaterial : public Material {};

struct UnlitMaterial : public Material {};

PACK(struct PbrMaterial
     : public LitMaterial {
         vec3 diffuse;
         TextureID albedo;
         TextureID normal_map;
         // TextureID displacement_map;
         // TextureID metallic_map;
         // TextureID specular_map;
         float metallic;
         float smoothness;
         float specular;
     });

PACK(struct StandardUnlit
     : public UnlitMaterial {
         vec3 diffuse;
         TextureID albedo;
     });

PACK(struct EmissiveMaterial
     : public UnlitMaterial {
         float strength;
         vec3 color;
         TextureID emission_map;
         TextureID albedo;
     });

Material* CreatePbrMaterial(const char* name, const vec3& diffuse,
                            const TextureID albedo,
                            const TextureID specular_map,
                            const TextureID normal,
                            const TextureID displacement,
                            const TextureID metallic, const float specular,
                            const float smoothness);
Material* CreateUnlitMaterial(const char* name, const vec3& diffuse,
                              const TextureID albedo);
Material* CreateEmissiveMaterial(const char* name, const float strength,
                                 const vec3& color, const TextureID albedo,
                                 const TextureID emission);

}  // namespace zifmann::zgame::core::rendering

#endif
