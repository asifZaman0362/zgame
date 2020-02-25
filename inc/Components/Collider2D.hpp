#pragma once
#include "Component.hpp"
#include <list>

namespace ze {
    enum ColliderType { Rectangle, Circle, Polygon };
    struct Collider2D : public Component {
    public:
        Collider2D(const std::weak_ptr<int> object_id) : Component(std::move(object_id)) {}
        ~Collider2D();
        virtual bool IsColliding(Collider2D*) = 0;
        virtual ColliderType GetType() = 0;
        std::list<std::weak_ptr<Collider2D>> m_contacts;
    };
}
