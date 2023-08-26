#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "assetmanager.hpp"
#include "ecs.hpp"
#include "mesh.hpp"

namespace zifmann::zgame::core::systems {

struct __attribute__((packed)) Transform {
    glm::vec3 position;
    glm::vec3 euler_rotation;
    glm::vec3 scale;
};

class Renderer : public ISystem {
    public:
        Signature GetSignature() override;
        void Update(float) override;
};

}