#pragma once
#include <memory>

namespace ze {
    struct Component {
    public:
        Component(std::weak_ptr<int> objectId) : m_objectId(std::move(objectId)) {}
    private:
        std::weak_ptr<int> m_objectId;
    };
}
