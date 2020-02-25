#pragma once
#include "Collider2D.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>


namespace ze {
    struct BoxCollider : public Collider2D {
        friend class CollisionManager;
    public:
        BoxCollider(const std::weak_ptr<int> object_id) : Collider2D(std::move(object_id)) {}
        
        bool IsColliding(Collider2D*) override;

        ColliderType GetType() override;

        sf::FloatRect GetRect();

    private:
        sf::FloatRect m_aabb;
    };
}