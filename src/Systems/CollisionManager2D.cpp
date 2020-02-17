#include "Systems/CollisionManager2D.hpp"

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
    void CollisionManager::Update() {
        
    }
}