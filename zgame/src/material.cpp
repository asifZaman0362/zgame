#include "material.hpp"
#include "assetmanager.hpp"

namespace zifmann::zgame::core::rendering {
Material* CreatePbrMaterial(const char* name, const vec3& diffuse, const TextureID albedo,
                            const TextureID specular, const TextureID normal,
                            const TextureID displacement,
                            const TextureID metallic) {
    auto material = AssetManager::LoadMaterial<PbrMaterial>(name);
    auto shader = AssetManager::LoadShaderProgram("res/vert.glsl", "res/frag.glsl");
    material->shader_id = shader;
    material->diffuse = diffuse;
    material->albedo = albedo;
    material->specular_map = specular;    
    material->metallic_map = metallic;
    material->displacement_map = displacement;
    material->normal_map = normal;
    return material.get();
}

Material* CreateUnlitMaterial(const char* name, const vec3& diffuse,
                              const TextureID albedo) {
    auto material = AssetManager::LoadMaterial<StandardUnlit>(name);
    material->diffuse = diffuse;
    material->albedo = albedo;
    return material.get();
}

Material* CreateEmissiveMaterial(const char* name, const float strength,
                                 const vec3& color, const TextureID albedo,
                                 const TextureID emission) {
    auto material = AssetManager::LoadMaterial<EmissiveMaterial>(name);
    material->strength = strength;
    material->color = color;
    material->albedo = albedo;
    material->emission_map = emission;
    return material.get();
}
}  // namespace zifmann::zgame::core::rendering
