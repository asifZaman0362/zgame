#include "renderer.hpp"

#include "assetmanager.hpp"
#include "ecs.hpp"
#include "glm/ext/vector_float3.hpp"
#include "logger.hpp"
#include "material.hpp"
#include "types.hpp"
#include "utils.hpp"
#include "transform.hpp"
#include "shader.hpp"


extern Coordinator coordinator;
extern glm::mat4 projected_view_matrix;
extern glm::mat4 view_matrix;
extern glm::mat4 projection_matrix;
extern glm::vec3 camera_position;
extern zifmann::zgame::core::rendering::Light light_source;
extern zifmann::zgame::core::Transform light_transform;
extern glm::vec3 ambient;

namespace zifmann::zgame::core::rendering {

mat4 CalculateMvp(Transform* transform) {
    auto scaled_translation = transform->position;
    scaled_translation.x *= 1 / transform->scale.x;
    scaled_translation.y *= 1 / transform->scale.y;
    scaled_translation.z *= 1 / transform->scale.z;
    auto model_matrix = glm::translate(
        glm::scale(glm::mat4(1.0f), transform->scale), scaled_translation);
    model_matrix = glm::rotate(
        model_matrix, glm::radians(transform->euler_rotation.x), RIGHT);
    model_matrix = glm::rotate(
        model_matrix, glm::radians(transform->euler_rotation.y), UP);
    model_matrix = glm::rotate(
        model_matrix, glm::radians(transform->euler_rotation.z), FORWARD);
    return projected_view_matrix * model_matrix;
}

mat4 ModelMatrix(Transform *transform) {
    auto scaled_translation = transform->position;
    scaled_translation.x *= 1 / transform->scale.x;
    scaled_translation.y *= 1 / transform->scale.y;
    scaled_translation.z *= 1 / transform->scale.z;
    auto model_matrix = glm::translate(
        glm::scale(glm::mat4(1.0f), transform->scale), scaled_translation);
    model_matrix = glm::rotate(
        model_matrix, glm::radians(transform->euler_rotation.x), RIGHT);
    model_matrix = glm::rotate(
        model_matrix, glm::radians(transform->euler_rotation.y), UP);
    model_matrix = glm::rotate(
        model_matrix, glm::radians(transform->euler_rotation.z), FORWARD);
    return model_matrix;
}

template<>
Signature Renderer<PbrMaterial>::GetSignature() {
    return utils::SignatureHelper(2, GetComponentId<Transform>(),
                                  GetComponentId<rendering::MeshRenderer>());
}

template<>
void Renderer<PbrMaterial>::Update(float) {
    //auto lights = coordinator.GetComponentArray<Light>();
    auto i = 0;
    for (auto entity : m_entities) {
        auto mesh_renderer = coordinator.GetComponent<rendering::MeshRenderer>(entity);
        auto material = static_cast<PbrMaterial*>(mesh_renderer->shared_material);
        auto shader = material->shader_id;
        auto diffuse = material->diffuse;
        auto albedo = material->albedo;
        auto normal = material->normal_map;
        auto displacement = material->displacement_map;
        auto metallic = material->metallic_map;
        auto specular = material->specular_map;
        auto mesh = mesh_renderer->mesh;
        auto transform = coordinator.GetComponent<Transform>(entity);
        glUseProgram(material->shader_id);
        glBindVertexArray(mesh->vao);
        shader::SetUniform(shader, "model", ModelMatrix(transform));
        shader::SetUniform(shader, "view", view_matrix);
        shader::SetUniform(shader, "projection", projection_matrix);
        //shader::SetUniform(shader, "MVP", CalculateMvp(transform));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, albedo);
        shader::SetUniform(shader, "ourTexture", glm::vec<1, int>(0));
        shader::SetUniform(shader, "lightPos", light_transform.position);
        shader::SetUniform(shader, "lightColor", light_source.color);
        shader::SetUniform(shader, "ambientLight", ambient);
        shader::SetUniform(shader, "diffuseColor", diffuse);
        shader::SetUniform(shader, "cameraPosition", camera_position);
        glDrawElements(GL_TRIANGLES, mesh->triangle_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

}  // namespace zifmann::zgame::core::systems
