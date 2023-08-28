#include "renderer.hpp"

#include "ecs.hpp"
#include "glm/ext/vector_float3.hpp"
#include "types.hpp"
#include "utils.hpp"


extern Coordinator coordinator;
extern glm::mat4 projected_view_matrix;
extern zifmann::zgame::core::systems::Light light_source;

namespace zifmann::zgame::core::systems {


Signature Renderer::GetSignature() {
    return utils::SignatureHelper(2, GetComponentId<Transform>(),
                                  GetComponentId<Mesh>());
}

void Renderer::Update(float) {
    //auto lights = coordinator.GetComponentArray<Light>();
    for (auto entity : m_entities) {
        auto mesh = coordinator.GetComponent<Mesh>(entity);
        auto transform = coordinator.GetComponent<Transform>(entity);
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
        glUseProgram(mesh->shader);
        glBindVertexArray(mesh->vao);
        auto transform_location = glGetUniformLocation(mesh->shader, "MVP");
        glm::mat4 mvp = projected_view_matrix * model_matrix;
        glUniformMatrix4fv(transform_location, 1, GL_FALSE,
                           glm::value_ptr(mvp));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->texture);
        auto textureId = glGetUniformLocation(mesh->shader, "ourTexture");
        glUniform1i(textureId, 0);
        auto lightPos = glGetUniformLocation(mesh->shader, "lightPos");
        auto [x, y, z] = light_source.position;
        glUniform3f(lightPos, x, y, z);
        auto lightCol = glGetUniformLocation(mesh->shader, "lightColor");
        auto [r, g, b] = light_source.color;
        glUniform3f(lightCol, r, g, b);
        glDrawElements(GL_TRIANGLES, mesh->triangle_count, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
}

}  // namespace zifmann::zgame::core::systems
