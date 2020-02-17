#include <memory>

namespace ze {
    class Component {
    public:
        Component(std::weak_ptr<int> objectId) : m_objectId(std::move(objectId)) {}
    private:
        std::weak_ptr<int> m_objectId;
    };
}
