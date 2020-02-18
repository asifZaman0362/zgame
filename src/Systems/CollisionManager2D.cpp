#include "Systems/CollisionManager2D.hpp"
#include "Components/BoxCollider.hpp"
#include "Components/CircleCollider.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace ze {
    void CollisionManager::AddCollider(const Collider coll) {
        m_colliders.push_back(std::move(coll));
    }
    void CollisionManager::RemoveCollider(const Collider coll) {
        m_colliders.remove(coll);
    }
    void CollisionManager::PopBack() {
        m_colliders.pop_back();
    }
    void CollisionManager::PopFront() {
        m_colliders.pop_front();
    }
    void CollisionManager::ClearList() {
        m_colliders.clear();
    }
    void CollisionManager::Update(const Collider& coll) {
        for (auto &other : m_colliders) {
            if (coll != other) {
                coll->IsColliding(other.get());
            }
        }
    }
}