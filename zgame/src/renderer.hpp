#include <glm/gtc/type_ptr.hpp>
#include <type_traits>

#include "assetmanager.hpp"
#include "ecs.hpp"
#include "mesh.hpp"

namespace zifmann::zgame::core::rendering {

template<typename T>
concept DerivesMaterial = std::is_base_of_v<Material, T>;

template<DerivesMaterial T>
class Renderer : public ISystem {
   public:
    Signature GetSignature() override;
    void Update(float) override;
};

template<>
Signature Renderer<PbrMaterial>::GetSignature();

template<>
void Renderer<PbrMaterial>::Update(float);

template<>
Signature Renderer<StandardUnlit>::GetSignature();

template<>
void Renderer<StandardUnlit>::Update(float);

template<>
Signature Renderer<EmissiveMaterial>::GetSignature();

template<>
void Renderer<EmissiveMaterial>::Update(float);

}  // namespace zifmann::zgame::core::systems
