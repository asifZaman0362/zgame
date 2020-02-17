#include "Collider2D.hpp"
#include <SFML/System/Vector2.hpp>


namespace ze {
    class CircleCollider : public Collider2D {
    public:
        CircleCollider(const std::weak_ptr<int> object_id) : Collider2D(std::move(object_id)) {}
        ~CircleCollider() {}
    private:
        sf::Vector2f m_position;
        float m_radius;
    };
}