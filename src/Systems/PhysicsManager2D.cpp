#include "Systems/PhysicsManager2D.hpp"
#include "Components/PhysicsObject2D.hpp"

namespace TstBits {

    std::list<RigidBody> PhysicsManager2D::m_objects;

    void PhysicsManager2D::AddObject(const RigidBody rb) {
        m_objects.push_back(std::move(rb));
    }

    void PhysicsManager2D::RemoveObject(const RigidBody rb) {
        for (auto i = m_objects.begin(); i != m_objects.end(); ++i) {
            if(*i == rb) {
                m_objects.erase(i);
            }
        }
    }

    void PhysicsManager2D::PopBack() {
        if (!m_objects.empty()) m_objects.pop_back();
    }

    void PhysicsManager2D::PopFront() {
        if (!m_objects.empty()) m_objects.pop_front();
    }

    void PhysicsManager2D::Update(const float fdt) {
        for (auto obj : m_objects) {
            if (obj != nullptr) {
                //obj->m_position.y += 9.8f;
            }
        }
    }

}