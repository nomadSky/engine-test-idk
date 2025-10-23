#pragma once
#include "ecs_types.h"
#include "component_pool.h"
#include <array>
#include <memory>

class Registry {
private:
    std::array<std::unique_ptr<IComponentPool>, MAX_COMPONENTS> componentPools;
    std::array<Signature, MAX_ENTITIES> entitySignatures;
    std::vector<Entity> freeEntities;

public:
    Registry() {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            freeEntities.push_back(entity);
        }
    }

    Entity createEntity() {
        Entity entity = freeEntities.back();
        freeEntities.pop_back();
        return entity;
    }

    void destroyEntity(Entity entity) {
        for (ComponentType i = 0; i < MAX_COMPONENTS; ++i) {
            if (entitySignatures[entity].test(i)) {
                componentPools[i]->erase(entity);
            }
        }
        entitySignatures[entity].reset();
        freeEntities.push_back(entity);
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        ComponentType type = getComponentType<T>();
        if (!componentPools[type]) {
            componentPools[type] = std::make_unique<ComponentPool<T>>();
        }
        auto& pool = static_cast<ComponentPool<T>&>(*componentPools[type]);
        pool.insert(entity, component);
        entitySignatures[entity].set(type);
    }

    template<typename T>
    T& getComponent(Entity entity) {
        ComponentType type = getComponentType<T>();
        auto& pool = static_cast<ComponentPool<T>&>(*componentPools[type]);
        return pool.get(entity);
    }

    template<typename T>
    bool hasComponent(Entity entity) {
        ComponentType type = getComponentType<T>();
        if (!componentPools[type]) return false;
        auto& pool = static_cast<ComponentPool<T>&>(*componentPools[type]);
        return pool.has(entity);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        ComponentType type = getComponentType<T>();
        componentPools[type]->erase(entity);
        entitySignatures[entity].reset(type);
    }

    template<typename T>
    ComponentType getComponentType() {
        static ComponentType type = nextComponentType++;
        return type;
    }

private:
    ComponentType nextComponentType = 0;
};