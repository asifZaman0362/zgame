#ifndef ZIFMANN_ZGAME_LIGHTING_HPP
#define ZIFMANN_ZGAME_LIGHTING_HPP

#include "assetmanager.hpp"
#include "ecs.hpp"
#include "material.hpp"
#include "types.hpp"
#include "utils.hpp"


extern Coordinator coordinator;

namespace zifmann::zgame::core::rendering {
struct __attribute__((packed)) Light {
    float intensity;
    vec3 color;
};

class LightingSystem : public ISystem {
    public:
    Signature GetSignature() override {
        return zifmann::zgame::core::utils::SignatureHelper(1, GetComponentId<Light>());
    }
    void Update(float) override {
        auto shaders = coordinator.GetComponentArray<LitMaterial>();
        for (auto light : m_entities) {
            auto light_source = coordinator.GetComponent<Light>(light);
            //auto pos = coordinator.GetComponent<zifmann::zgame::core::Position
            /*for (auto material : shaders) {
                auto lightPos = glGetUniformLocation(material.shader, "lightPos");
                auto [x, y, z] = light_source.;
                glUniform3f(lightPos, x, y, z);
                auto lightCol = glGetUniformLocation(mesh->shader, "lightColor");
                auto [r, g, b] = light_source.color;
                glUniform3f(lightCol, r, g, b);
            }*/
        }
    }
};
}

#endif
