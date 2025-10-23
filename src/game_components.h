#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <ecs_types.h>

// Psychology & Social Traits
struct Psychology {
    float sanity = 100.0f;
    float stress = 0.0f;
    float fear = 0.0f;
    float aggression = 50.0f;
    float empathy = 50.0f;
};

struct SocialTraits {
    std::string factionId;
    std::unordered_map<Entity, float> relationships; // entity -> relationship score
    std::vector<std::string> traits; // "Brave", "Greedy", "Loyal", etc.
    float loyalty = 50.0f;
    float charisma = 50.0f;
};

// Physical stats
struct PhysicalStats {
    float health = 100.0f;
    float maxHealth = 100.0f;
    float stamina = 100.0f;
    float strength = 50.0f;
    float dexterity = 50.0f;
    float endurance = 50.0f;
};

// Inventory & Equipment
struct Inventory {
    std::vector<Entity> items;
    size_t capacity = 20;
};

struct Equipment {
    Entity head;
    Entity torso;
    Entity legs;
    Entity feet;
    Entity primaryWeapon;
    Entity secondaryWeapon;
};

// Armor System
struct Armor {
    std::string material; // "Steel", "Ceramic", "Kevlar"
    float durability = 100.0f;
    float maxDurability = 100.0f;
    std::unordered_map<std::string, float> protection; // damageType -> protection value
    float coverage = 1.0f; // 0-1, what body area is covered
    float bluntResistance = 0.0f;
};

// Weapon System
struct Weapon {
    std::string type; // "AssaultRifle", "Pistol", "Melee"
    std::string caliber;
    float damage = 10.0f;
    float penetration = 0.0f;
    float fireRate = 1.0f;
    float accuracy = 1.0f;
    int magazineSize = 30;
    int currentAmmo = 30;
    float durability = 100.0f;
};

// Combat & Ballistics
struct CombatStats {
    float accuracy = 1.0f;
    float reloadSpeed = 1.0f;
    float meleeSkill = 1.0f;
    float rangedSkill = 1.0f;
};

struct Projectile {
    Entity shooter;
    std::string damageType;
    float baseDamage;
    float penetration;
    float velocity;
    float distanceTraveled = 0.0f;
    float maxDistance = 100.0f;
};

// Faction System
struct Faction {
    std::string id;
    std::string name;
    std::unordered_map<std::string, float> relationships; // factionId -> relationship
    std::vector<std::string> allies;
    std::vector<std::string> enemies;
    float aggression = 50.0f;
    float wealth = 0.0f;
};

// World & Location
struct Transform {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float rotation = 0.0f;
};

struct Location {
    std::string locationId;
    std::string type; // "Settlement", "Dungeon", "Outpost", "Ruins"
    int securityLevel = 0;
    float wealth = 0.0f;
    std::string controllingFaction;
    std::vector<std::string> tags; // "Urban", "Military", "Abandoned", etc.
};

// AI & Behavior
struct AIBehavior {
    std::string currentState; // "Idle", "Combat", "Flee", "Loot"
    Entity currentTarget;
    float decisionMaking = 1.0f;
    float riskTolerance = 50.0f;
};

struct Needs {
    float hunger = 0.0f;
    float thirst = 0.0f;
    float sleep = 0.0f;
    float comfort = 50.0f;
};