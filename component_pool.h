#pragma once
#include "ecs_types.h"
#include <memory>

class IComponentPool {
public:
    virtual ~IComponentPool() = default;
    virtual void erase(Entity entity) = 0;
};

template<typename T>
class ComponentPool : public IComponentPool {
private:
    std::vector<T> data;
    std::unordered_map<Entity, size_t> entityToIndex;
    std::unordered_map<size_t, Entity> indexToEntity;
    size_t size;

public:
    ComponentPool() : size(0) {
        data.resize(MAX_ENTITIES);
    }

    void insert(Entity entity, T component) {
        data[size] = component;
        entityToIndex[entity] = size;
        indexToEntity[size] = entity;
        size++;
    }

    T& get(Entity entity) {
        return data[entityToIndex[entity]];
    }

    void erase(Entity entity) override {
        size_t index = entityToIndex[entity];
        size_t lastEntity = indexToEntity[size - 1];
        
        data[index] = data[size - 1];
        entityToIndex[lastEntity] = index;
        indexToEntity[index] = lastEntity;
        
        entityToIndex.erase(entity);
        indexToEntity.erase(size - 1);
        size--;
    }

    bool has(Entity entity) {
        return entityToIndex.find(entity) != entityToIndex.end();
    }
};