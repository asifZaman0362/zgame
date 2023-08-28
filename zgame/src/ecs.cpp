#include "ecs.hpp"

#include "logger.hpp"

using namespace zifmann::logger;

void ISystem::AddEntity(Entity e) { m_entities.insert(e); }

void ISystem::RemoveEntity(Entity e) { m_entities.erase(e); }

Registry::Registry() {
    m_aliveEntities = 0;
    for (size_t i = 0; i < MAX_ENTITIES; i++) {
        m_availableEntities.push_back(i);
    }
}

Entity Registry::CreateEntity() {
    assert(m_availableEntities.size() &&
           "No available entity ID's to give out");
    Entity id = m_availableEntities.front();
    m_availableEntities.pop_front();
    m_aliveEntities++;
    return id;
}

Signature Registry::RemoveEntity(Entity e) {
    assert(std::find(m_availableEntities.begin(), m_availableEntities.end(),
                     e) == m_availableEntities.end() &&
           "Attempting to remove a non-existent entity!");
    m_availableEntities.push_back(e);
    Signature signature = m_entitySignatures[e];
    for (auto comp_array : m_componentArrays) {
        if (signature.test(comp_array.first)) {
            comp_array.second->OnEntityRemoved(e);
        }
    }
    m_aliveEntities--;
    return signature;
}

void SystemManager::EntityUpdated(Entity e, Signature s) {
    for (auto& system : m_systems) {
        auto system_s = system.second->GetSignature();
        if ((system_s & s) == system_s) {
            system.second->AddEntity(e);
        } else {
            system.second->RemoveEntity(e);
        }
    }
}

void SystemManager::Update(float dt) {
    for (auto& system : m_systems) {
        system.second->Update(dt);
    }
}

Entity Coordinator::CreateEntity() { return m_registry.CreateEntity(); }

void Coordinator::DestroyEntity(Entity e) {
    m_registry.RemoveEntity(e);
    m_systemManager.EntityUpdated(e, 0);
}

void Coordinator::Update(float dt) { m_systemManager.Update(dt); }
