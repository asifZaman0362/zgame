#include <list>
#include <memory>

namespace TstBits {
    
    class Component;
    typedef std::shared_ptr<Component> ComponentRef;
    class Entity {
    public:
        Entity();
        ~Entity();

        void AddComponent(const ComponentRef ref) {
            if (ref != nullptr) m_components.push_back(ref);
        }

        template <typename T> std::weak_ptr<T> GetComponent() {
            for (auto i : m_components) {
                if (typeid(i.get()) == typeid(T)) return i;
            }
        }

        template <typename T> void RemoveComponent() {
            for (auto i : m_components) {
                if (typeid(i.get()) == typeid(T)) m_components.remove(i); 
            }
        }

    private:
        std::list<ComponentRef> m_components;
    };
}