#ifndef ZIFMANN_ZGAME_COLLISION_HPP
#define ZIFMANN_ZGAME_COLLISION_HPP
#include <algorithm>

#include "ecs.hpp"
#include "glm/ext/vector_float3.hpp"
#include "types.hpp"
#include "utils.hpp"

constexpr size_t MAX_COLLISIONS = 32;

extern Coordinator coordinator;

namespace zifmann::zgame::core::physics {

struct BoxCollider {
    glm::vec3 size;
    glm::vec3 offset;
};

struct CapsuleCollider {
    glm::vec3 offset;
    float radius;
    float height;
};

struct Collider;

PACK(struct CollisionInfo {
    vec3 hitNormal;
    Collider* other;
    bool flag;  // for syncing between consecutive calls
});

enum class ColliderType { Box, Capsule };

struct Collider {
    ColliderType type;
    union {
        CapsuleCollider capsule;
        BoxCollider box;
    };
    int layer;
    std::array<CollisionInfo, MAX_COLLISIONS> collisions;
    size_t count;
};

using CollisionResult = std::pair<bool, vec3>;

template <typename T, typename U>
CollisionResult collide(Collider* a, Collider* b);

template <>
inline CollisionResult collide<BoxCollider, CapsuleCollider>(Collider* a, Collider* b) {
    bool result;
    vec3 normal;
    return std::make_pair(result, normal);
}

template <>
inline CollisionResult collide<BoxCollider, BoxCollider>(Collider* a, Collider* b) {
    bool result;
    vec3 normal;
    return std::make_pair(result, normal);
}

template <>
inline CollisionResult collide<CapsuleCollider, CapsuleCollider>(Collider* a,
                                                      Collider* b) {
    bool result;
    vec3 normal;
    return std::make_pair(result, normal);
}

inline std::unordered_map<std::pair<ColliderType, ColliderType>,
                          std::function<CollisionResult(Collider*, Collider*)>>
    collision_funcs = {
        {std::make_pair(ColliderType::Box, ColliderType::Capsule),
         collide<BoxCollider, CapsuleCollider>},
        {std::make_pair(ColliderType::Box, ColliderType::Box),
         collide<BoxCollider, BoxCollider>},
        {std::make_pair(ColliderType::Capsule, ColliderType::Capsule),
         collide<CapsuleCollider, CapsuleCollider>},
        {std::make_pair(ColliderType::Capsule, ColliderType::Box),
         collide<CapsuleCollider, BoxCollider>},
};

inline void check_collision(Collider* a, Collider* b, bool flag) {
    auto res = collision_funcs[std::make_pair(a->type, b->type)](a, b);
    if (res.first) {
        a->collisions[a->count++] = { res.second, b, flag };
        b->collisions[b->count++] = { res.second, a, flag };
    }
}

struct ColliderSystem : public ISystem {
   private:
    bool flag = true;

   public:
    Signature GetSignature() override {
        return utils::SignatureHelper(1, GetComponentId<Collider>());
    }
    void Update(float) override {
        flag = !flag;
        for (auto entity : m_entities) {
            auto coll = coordinator.GetComponent<Collider>(entity);
            auto others = coordinator.GetComponentArray<Collider>();
            coll->collisions.fill({{0, 0, 0}, 0});
            bool f = flag;
            for (auto& other : *others) {
                if (std::find_if(other.collisions.begin(),
                                 other.collisions.end(),
                                 [coll, f](CollisionInfo& a) -> bool {
                                     return a.other == coll && a.flag == f;
                                 }) == std::end(other.collisions)) {
                    check_collision(coll, &other, flag);
                }
            }
        }
    }
};

}  // namespace zifmann::zgame::core::physics
#endif
