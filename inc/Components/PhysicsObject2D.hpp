#pragma once
#include "Components/Component.hpp"
#include "Components/Transform.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <memory>

namespace ze {

    class PhysicsObject2D : public Component {

    private:
        Transform* m_transform;

    public:
        PhysicsObject2D(const std::weak_ptr<int> id, const Transform* transform) :
            Component(std::move(id)), m_transform(const_cast<Transform*>(transform)) {
                
        }

        friend class PhysicsManager2D;
    };

}
