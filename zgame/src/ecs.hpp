#ifndef ECS_HPP
#define ECS_HPP

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <deque>
#include <memory>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <utility>

#define MAX_COMPONENTS 32
#define MAX_ENTITIES 100000

using Entity = size_t;
using Signature = std::bitset<MAX_COMPONENTS>;

class IComponentArray {
   public:
    virtual void OnEntityRemoved(Entity) = 0;
};

class ISystem {
   public:
    virtual ~ISystem() = default;
    virtual Signature GetSignature() = 0;
    virtual void Update(float) = 0;
    void AddEntity(Entity);
    void RemoveEntity(Entity);

   protected:
    std::set<Entity> m_entities;
};

template <typename T>
class ComponentArray : public IComponentArray {
   public:
    virtual ~ComponentArray() = default;
    T* GetComponent(Entity);
    void AddComponent(Entity, const T&);
    void RemoveComponent(Entity);
    void OnEntityRemoved(Entity) override;
    T* begin();
    T* end();

   private:
    T m_items[MAX_ENTITIES];
    std::unordered_map<Entity, size_t> m_entityToIndexMap;
    std::unordered_map<size_t, Entity> m_indexToEntityMap;
    size_t m_length = 0;
};

class Registry {
   public:
    Registry();
    template <typename T>
    void RegisterComponent();
    template <typename T>
    void UnregisterComponent();
    template <typename T>
    Signature AddComponent(Entity, T);
    template <typename T>
    Signature RemoveComponent(Entity);
    template <typename T>
    T* GetComponent(Entity);
    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();

    Entity CreateEntity();
    Signature RemoveEntity(Entity);

    template <typename T>
    size_t IsComponentRegistered();

   private:
    std::unordered_map<size_t, std::shared_ptr<IComponentArray>>
        m_componentArrays;
    std::deque<Entity> m_availableEntities;
    std::unordered_map<Entity, Signature> m_entitySignatures;
    size_t m_aliveEntities;
};

template <typename T>
concept DerivesSystem = std::is_base_of_v<ISystem, T>;

class SystemManager {
   public:
    template <DerivesSystem T>
    void LoadSystem();
    template <DerivesSystem T>
    void UnloadSystem();

    void EntityUpdated(Entity, Signature);
    void Update(float);

    template <DerivesSystem T>
    size_t IsSystemRegistered();

   private:
    std::unordered_map<size_t, std::shared_ptr<ISystem>> m_systems;
};

class Coordinator {
   public:
    template <typename T>
    void RegisterComponent();
    template <typename T>
    void UnregisterComponent();
    template <DerivesSystem T>
    void LoadSystem();
    template <DerivesSystem T>
    void UnloadSystem();

    Entity CreateEntity();
    void DestroyEntity(Entity);

    template <typename T>
    void AddComponent(Entity, T);
    template <typename T>
    void RemoveComponent(Entity);
    template <typename T>
    T* GetComponent(Entity);
    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray();

    void Update(float);

   private:
    Registry m_registry;
    SystemManager m_systemManager;
};

/* ID Generation */

inline size_t component_id_counter = 1;
inline size_t system_id_counter = 1;

template <typename T>
inline size_t GetComponentId() {
    static size_t id = component_id_counter++;
    return id;
}

template <typename T>
inline size_t GetSystemId() {
    static size_t id = system_id_counter++;
    return id;
}

/* Definitions */

template <typename T>
T* ComponentArray<T>::GetComponent(Entity e) {
    assert(m_entityToIndexMap.contains(e) &&
           "Entity does not contain the desired component!");
    size_t index = m_entityToIndexMap[e];
    T* item = &m_items[index];
    return item;
}

template <typename T>
void ComponentArray<T>::AddComponent(Entity e, const T& comp) {
    assert(!m_entityToIndexMap.contains(e) &&
           "Entity already contains a component of the same type!");
    m_entityToIndexMap[e] = m_length;
    m_indexToEntityMap[m_length] = e;
    m_items[m_length] = comp;
    m_length++;
}

template <typename T>
void ComponentArray<T>::RemoveComponent(Entity e) {
    assert(m_entityToIndexMap.contains(e) &&
           "Entity does not contain the desired component!");
    size_t index_of_removed = m_entityToIndexMap[e];
    size_t last_index = m_length - 1;
    size_t entity_at_the_end = m_indexToEntityMap[last_index];
    m_indexToEntityMap[index_of_removed] = entity_at_the_end;
    m_entityToIndexMap[entity_at_the_end] = index_of_removed;
    m_entityToIndexMap.erase(e);
    m_indexToEntityMap.erase(last_index);
}

template <typename T>
void ComponentArray<T>::OnEntityRemoved(Entity e) {
    if (m_entityToIndexMap.contains(e)) {
        RemoveComponent(e);
    }
}

template <typename T>
T* ComponentArray<T>::begin() {
    return m_items;
}

template <typename T>
T* ComponentArray<T>::end() {
    return m_items + m_length;
}

template <typename T>
void Registry::RegisterComponent() {
    if (!IsComponentRegistered<T>()) {
        size_t id = GetComponentId<T>();
        m_componentArrays[id] = std::make_shared<ComponentArray<T>>();
    }
}

template <typename T>
void Registry::UnregisterComponent() {
    if (size_t id = IsComponentRegistered<T>()) {
        m_componentArrays.erase(id);
    }
}

template <typename T>
Signature Registry::AddComponent(Entity e, T comp) {
    size_t id = IsComponentRegistered<T>();
    assert(id && "Attempting to add an unregistered component!");
    auto array =
        std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[id]);
    array->AddComponent(e, comp);
    Signature new_signature = 0;
    if (m_entitySignatures.contains(e)) {
        new_signature = m_entitySignatures[e];
    }
    new_signature.set(id, true);
    m_entitySignatures[e] = new_signature;
    return new_signature;
}

template <typename T>
Signature Registry::RemoveComponent(Entity e) {
    size_t id = IsComponentRegistered<T>();
    assert(id && "Attempting to remove an unregistered component!");
    auto array =
        std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[id]);
    array->RemoveComponent(e);
    Signature new_signature = 0;
    if (m_entitySignatures.contains(e)) {
        new_signature = m_entitySignatures[e];
    }
    new_signature.set(id, true);
    m_entitySignatures[e] = new_signature;
    return new_signature;
}

template <typename T>
T* Registry::GetComponent(Entity e) {
    size_t id = IsComponentRegistered<T>();
    assert(id && "Component not registered!");
    auto array =
        std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[id]);
    return array->GetComponent(e);
}

template <typename T>
std::shared_ptr<ComponentArray<T>> Registry::GetComponentArray() {
    auto id = IsComponentRegistered<T>();
    assert(id && "Attempting to retrieve list of unregistered component type");
    return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[id]);
}

template <typename T>
size_t Registry::IsComponentRegistered() {
    size_t id = GetComponentId<T>();
    if (m_componentArrays.contains(id))
        return id;
    else
        return 0;
}

template <DerivesSystem T>
void SystemManager::LoadSystem() {
    if (!IsSystemRegistered<T>()) {
        size_t id = GetSystemId<T>();
        m_systems[id] =
            std::static_pointer_cast<ISystem>(std::make_shared<T>());
    }
}

template <DerivesSystem T>
void SystemManager::UnloadSystem() {
    if (size_t id = IsSystemRegistered<T>()) {
        m_systems.erase(id);
    }
}

template <DerivesSystem T>
size_t SystemManager::IsSystemRegistered() {
    size_t id = GetSystemId<T>();
    if (m_systems.contains(id))
        return id;
    else
        return 0;
}

template <typename T>
void Coordinator::AddComponent(Entity e, T comp) {
    auto signature = m_registry.AddComponent(e, comp);
    m_systemManager.EntityUpdated(e, signature);
}

template <typename T>
void Coordinator::RemoveComponent(Entity e) {
    m_registry.RemoveComponent<T>(e);
}

template <typename T>
T* Coordinator::GetComponent(Entity e) {
    return m_registry.GetComponent<T>(e);
}

template <typename T>
std::shared_ptr<ComponentArray<T>> Coordinator::GetComponentArray() {
    return m_registry.GetComponentArray<T>();
}

template <typename T>
void Coordinator::RegisterComponent() {
    m_registry.RegisterComponent<T>();
}

template <typename T>
void Coordinator::UnregisterComponent() {
    m_registry.UnregisterComponent<T>();
}

template <DerivesSystem T>
void Coordinator::LoadSystem() {
    m_systemManager.LoadSystem<T>();
}

template <DerivesSystem T>
void Coordinator::UnloadSystem() {
    m_systemManager.UnloadSystem<T>();
}

#endif
