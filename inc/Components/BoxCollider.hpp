#pragma once
#include "Collider2D.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>


namespace ze {
    struct BoxCollider : public Collider2D {
        friend class CollisionManager;
    public:
        BoxCollider(const std::weak_ptr<int> object_id) : Collider2D(std::move(object_id)) {}
        
        bool IsColliding(Collider2D* other) override {
            
            bool colliding = false;
            if (other->GetType() == ColliderType::Rectangle) {
                BoxCollider* other_box = dynamic_cast<BoxCollider*>(other);
                colliding = this->m_aabb.intersects(other_box->GetRect());
            } else if (other->GetType() == ColliderType::Circle) {
                CircleCollider* other_circle = dynamic_cast<CircleCollider*>(other);
                colliding = other_circle->IsColliding(this);
            }
            if (colliding) {
                this->m_contacts.push_back(std::make_shared<Collider2D>(other));
                other->m_contacts.push_back(std::make_shared<Collider2D>(this));
            }
            return colliding;

        }

        ColliderType GetType() {
            return ColliderType::Rectangle;
        }

        sf::FloatRect GetRect() {
            return m_aabb;
        }

    private:
        sf::FloatRect m_aabb;
    };
}