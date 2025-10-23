#pragma once
#include "ecs_registry.h"
#include "game_components.h"
#include <cmath>

class CombatSystem {
private:
    Registry& registry;
    
public:
    CombatSystem(Registry& reg) : registry(reg) {}
    
    void update(float deltaTime) {
        // Process combat interactions
        // Handle weapon firing, damage calculation, etc.
    }
    
    void calculateDamage(Entity projectile, Entity target) {
        if (!registry.hasComponent<Projectile>(projectile) || 
            !registry.hasComponent<PhysicalStats>(target)) return;
            
        auto& proj = registry.getComponent<Projectile>(projectile);
        auto& targetStats = registry.getComponent<PhysicalStats>(target);
        
        float finalDamage = proj.baseDamage;
        
        // Apply armor penetration calculations if target has armor
        if (registry.hasComponent<Armor>(target)) {
            auto& armor = registry.getComponent<Armor>(target);
            finalDamage = applyArmorPenetration(finalDamage, proj.penetration, armor);
        }
        
        targetStats.health -= finalDamage;
        
        // Handle psychology impact
        if (registry.hasComponent<Psychology>(target)) {
            auto& psych = registry.getComponent<Psychology>(target);
            psych.fear += finalDamage * 0.1f;
            psych.stress += finalDamage * 0.05f;
        }
    }
    
private:
    float applyArmorPenetration(float damage, float penetration, Armor& armor) {
        float protection = armor.protection["ballistic"]; // Example
        float effectivePenetration = penetration * (armor.durability / armor.maxDurability);
        
        if (effectivePenetration >= protection) {
            // Full penetration
            armor.durability -= damage * 0.1f;
            return damage * 0.8f; // Some energy absorbed
        } else {
            // Partial penetration
            float penetrationRatio = effectivePenetration / protection;
            armor.durability -= damage * 0.2f;
            return damage * penetrationRatio * 0.5f;
        }
    }
};

class PsychologySystem {
private:
    Registry& registry;
    
public:
    PsychologySystem(Registry& reg) : registry(reg) {}
    
    void update(float deltaTime) {
        // Update psychological states
        // Handle stress decay, fear propagation, mental breakdowns, etc.
    }
};

class FactionSystem {
private:
    Registry& registry;
    std::unordered_map<std::string, Faction> factions;
    
public:
    FactionSystem(Registry& reg) : registry(reg) {}
    
    void updateFactionRelations() {
        // Dynamic faction relationship updates
        // Handle reputation changes, war declarations, alliances
    }
    
    float getRelationship(Entity entity1, Entity entity2) {
        if (!registry.hasComponent<SocialTraits>(entity1) || 
            !registry.hasComponent<SocialTraits>(entity2)) return 0.0f;
            
        auto& social1 = registry.getComponent<SocialTraits>(entity1);
        auto& social2 = registry.getComponent<SocialTraits>(entity2);
        
        // Check direct relationship first
        if (social1.relationships.count(entity2)) {
            return social1.relationships[entity2];
        }
        
        // Fall back to faction relationship
        return getFactionRelationship(social1.factionId, social2.factionId);
    }
    
private:
    float getFactionRelationship(const std::string& faction1, const std::string& faction2) {
        if (factions.count(faction1) && factions[faction1].relationships.count(faction2)) {
            return factions[faction1].relationships[faction2];
        }
        return 0.0f; // Neutral
    }
};