#pragma once
#include <list>
#include <memory>

namespace ze {

    class PhysicsObject2D;
    typedef std::shared_ptr<PhysicsObject2D> RigidBody;

    class PhysicsManager2D {

    public:
        PhysicsManager2D() = delete;
        ~PhysicsManager2D() = delete;

        void AddObject(const RigidBody);
        void RemoveObject(const RigidBody);
        /* Only use this when you're sure about the objects position in the list */
        void PopBack();
        /* Only use this when you're sure about the objects position in the list */
        void PopFront();
        void Update(const float);
        void ClearList();
    
    private:
        static std::list<RigidBody> m_objects;

    };

}
