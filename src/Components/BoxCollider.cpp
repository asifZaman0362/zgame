#include "Components/BoxCollider.hpp"
#include "Components/CircleCollider.hpp"

namespace ze {
    bool BoxCollider::IsColliding(Collider2D* other) {
        bool colliding = false;
        if (other->GetType() == ColliderType::Rectangle) {
            BoxCollider* other_box = dynamic_cast<BoxCollider*>(other);
            colliding = this->m_aabb.intersects(other_box->GetRect());
        } else if (other->GetType() == ColliderType::Circle) {
            CircleCollider* other_circle = dynamic_cast<CircleCollider*>(other);
            colliding = other_circle->IsColliding(this);
        }
        return colliding;
    }

    ColliderType BoxCollider::GetType() {
        return ColliderType::Rectangle;
    }

    sf::FloatRect BoxCollider::GetRect() {
        return m_aabb;
    }
}