#include "../Components/Collider2D.hpp"
#include <list>
#include <memory>


namespace ze {
    class CollisionManager {
    typedef std::weak_ptr<Collider2D> Collider;
    public:
        CollisionManager();
        ~CollisionManager();
        void Update();
        void AddCollider(const Collider);
        void RemoveCollider(const Collider);
        void PopBack();
        void PopFront();
        void ClearList();
    private:
        std::list<Collider> m_colliders;
    };
}