#ifndef ZIFMANN_ZGAME_MATERIAL_HPP
#define ZIFMANN_ZGAME_MATERIAL_HPP

#include "types.hpp"
#include "utils.hpp"

namespace zifmann::zgame::core::rendering {

using ShaderProgram = unsigned int;
using TextureID = unsigned int;

enum class PbrWorkflowType { Metallic, Specular };

struct Material {
    ShaderProgram shader_id;
};

struct LitMaterial : public Material {};

struct UnlitMaterial : public Material {};

PACK(struct PbrMaterial
     : public LitMaterial {
         PbrWorkflowType workflow_type;
         vec3 diffuse;
         TextureID albedo;
         TextureID normal_map;
         TextureID displacement_map;
         TextureID roughness_map;
         union {
             TextureID metallic_map;
             TextureID specular_map;
         };
         union {
             float metallic_intensity;
             float specular_intensity;
         };
         float smoothness;
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

Material* CreatePbrMaterial(const char* name, const PbrWorkflowType workflow,
                            const vec3& diffuse, const TextureID albedo,
                            const TextureID specular_metallic_map,
                            const TextureID normal_map,
                            const TextureID displacement_map,
                            const TextureID roughness_map,
                            const TextureID specular_metallic_intensity,
                            const float smoothness);
Material* CreateUnlitMaterial(const char* name, const vec3& diffuse,
                              const TextureID albedo);
Material* CreateEmissiveMaterial(const char* name, const float strength,
                                 const vec3& color, const TextureID albedo,
                                 const TextureID emission);

}  // namespace zifmann::zgame::core::rendering

#endif
