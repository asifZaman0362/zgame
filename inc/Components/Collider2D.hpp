#include "Component.hpp"

namespace ze {
    enum ColliderType { Box, Circle, Polygon };
    struct Collider2D : public Component {
    public:
        Collider2D(const std::weak_ptr<int> object_id) : Component(std::move(object_id)) {}
        ~Collider2D();
	ColliderType m_type;
	friend class CollisionManager;
    };
}
