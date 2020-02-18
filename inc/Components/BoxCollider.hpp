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
                sf::Vector2f circ_pos = other_circle->GetPosition();
                float sqr_dist_nw = pow(m_aabb.left - circ_pos.x, 2) + pow(m_aabb.top - circ_pos.y, 2);
                float sqr_dist_ne = pow(m_aabb.left - m_aabb.width - circ_pos.x, 2) + pow(m_aabb.top - circ_pos.y, 2);
                float sqr_dist_sw = pow(m_aabb.left - circ_pos.x, 2) + pow(m_aabb.top - m_aabb.height - circ_pos.y, 2);
                float sqr_dist_se = pow(m_aabb.left - m_aabb.width - circ_pos.x, 2) + pow(m_aabb.top - m_aabb.height - circ_pos.y, 2);
                if (sqr_dist_ne < pow(other_circle->GetRadius(), 2) || sqr_dist_nw < pow(other_circle->GetRadius(), 2) 
                    || sqr_dist_se < pow(other_circle->GetRadius(), 2) || sqr_dist_sw < pow(other_circle->GetRadius(), 2)
                    || m_aabb.contains(other_circle->GetPosition())) {
                    colliding = true;
                }
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