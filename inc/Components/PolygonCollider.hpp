#include "Collider2D.hpp"

namespace ze {
    struct PolygonCollider : public Collider2D {
    public:
        PolygonCollider(const std::weak_ptr<int> object_id) : Collider2D(std::move(object_id)) {}
        ~PolygonCollider() {}
    private:
        unsigned short int m_sides;
        float m_sideLength;
    };
}