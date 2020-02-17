#include "Collider2D.hpp"
#include <SFML/Graphics/Rect.hpp>

namespace ze {
    struct BoxCollider : public Collider2D {
        public:
            BoxCollider(const std::weak_ptr<int> object_id) : Collider2D(std::move(object_id)) {}
        private:
            sf::FloatRect m_aabb;
    };
}