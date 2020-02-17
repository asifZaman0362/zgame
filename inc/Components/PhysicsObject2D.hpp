#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace ze {

    class PhysicsObject2D : public Component {

    public:
        PhysicsObject2D(const std::weak_ptr<int> id) :
            Component(std::move(id)) {
                if (true) return;
        }

        friend class PhysicsManager2D;
    };

}
