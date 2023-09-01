#include "material.hpp"

#include "assetmanager.hpp"

namespace zifmann::zgame::core::rendering {
Material* CreatePbrMaterial(const char* name, const PbrWorkflowType workflow,
                            const vec3& diffuse, const TextureID albedo,
                            const TextureID specular_metallic_map,
                            const TextureID normal_map,
                            const TextureID displacement_map,
                            const TextureID roughness_map,
                            const TextureID specular_metallic_intensity,
                            const float smoothness) {
    auto material = AssetManager::LoadMaterial<PbrMaterial>(name);
    auto shader =
        AssetManager::LoadShaderProgram("res/vert.glsl", "res/frag.glsl");
    material->workflow_type = workflow;
    material->shader_id = shader;
    material->diffuse = diffuse;
    material->albedo = albedo;
    if (workflow == PbrWorkflowType::Metallic) {
        material->metallic_map = specular_metallic_map;
        material->metallic_intensity = specular_metallic_intensity;
    } else {
        material->specular_map = specular_metallic_map;
        material->specular_intensity = specular_metallic_intensity;
    }
    material->smoothness = smoothness;
    material->normal_map = normal_map;
    material->displacement_map = displacement_map;
    material->roughness_map = roughness_map;
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
