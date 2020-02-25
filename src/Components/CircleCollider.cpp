#include "Components/CircleCollider.hpp"
#include "Components/BoxCollider.hpp"

namespace ze {
    bool CircleCollider::IsColliding(Collider2D* other) {
        if (other->GetType() == ColliderType::Circle) {
            
            CircleCollider* other_circle = dynamic_cast<CircleCollider*>(other);
            auto other_pos = other_circle->GetPosition();
            float other_radius = other_circle->GetRadius();
            float dist_sqr = pow(other_pos.x - m_position.x, 2) + pow(other_pos.y - m_position.y, 2);
            return dist_sqr <= (other_radius + m_radius) * (other_radius + m_radius);
        
        } else if (other->GetType() == ColliderType::Rectangle) {
            
            BoxCollider* other_box = dynamic_cast<BoxCollider*>(other);
            auto other_rect = other_box->GetRect();
            float distx = abs(other_rect.left + other_rect.width/2 - m_position.x);
            float disty = abs(other_rect.top + other_rect.height/2 - m_position.y);
            if (distx > other_rect.width/2 + m_radius || disty > other_rect.height/2 + m_radius) { 
                return false;
            } else {
                float dist = sqrt(pow(other_rect.left + other_rect.width/2 - m_position.x, 2) +
                                pow(other_rect.top + other_rect.height/2 - m_position.y, 2));
                float hyp = sqrt(pow(other_rect.width/2, 2) + pow(other_rect.height/2, 2));
                if (dist - hyp <= m_radius) {
                    return true;
                }
            }
        }
        return false;
    }

    ColliderType CircleCollider::GetType() {
        return ColliderType::Circle;
    }

    sf::Vector2f CircleCollider::GetPosition() {
        return m_position;
    }

    float CircleCollider::GetRadius() {
        return m_radius;
    }

}