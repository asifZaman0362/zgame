#pragma once
#include "../Components/Collider2D.hpp"
#include <list>
#include <memory>


namespace ze {
    class CollisionManager {
    typedef std::shared_ptr<Collider2D> Collider;
    public:
        CollisionManager();
        ~CollisionManager();
        /* Only called automatically each frame by physics manager for 
        physically simulated objects as static objects don't have to be 
        constantly checked for collisions but can be explicitly called if required */
        void Update(const Collider&);
        void AddCollider(const Collider);
        void RemoveCollider(const Collider);
        void PopBack();
        void PopFront();
        void ClearList();
        void CheckCollision(const Collider&, const Collider&);
    private:
        std::list<Collider> m_colliders;
    };
}