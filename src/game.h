#pragma once
#include "ecs_registry.h"
#include "game_components.h"
#include "game_systems.h"

class Game {
private:
    Registry registry;
    
    // Systems
    CombatSystem combatSystem;
    PsychologySystem psychologySystem;
    FactionSystem factionSystem;
    
    bool running = false;
    
public:
    Game() : combatSystem(registry), psychologySystem(registry), factionSystem(registry) {}
    
    void initialize() {
        // Initialize core systems
        // Create initial entities (player, factions, etc.)
        createInitialFactions();
        createPlayer();
    }
    
    void run() {
        running = true;
        float deltaTime = 0.016f; // ~60 FPS
        
        while (running) {
            update(deltaTime);
            // render(); // You'll implement this later
        }
    }
    
    void update(float deltaTime) {
        combatSystem.update(deltaTime);
        psychologySystem.update(deltaTime);
        factionSystem.updateFactionRelations();
        
        // Update other systems...
    }
    
    Registry& getRegistry() { return registry; }
    
private:
    void createInitialFactions() {
        // Create base factions
        Faction holyNation{"holy_nation", "Holy Nation", {}, {}, {}, 70.0f, 10000.0f};
        Faction shekKingdom{"shek_kingdom", "Shek Kingdom", {}, {}, {}, 85.0f, 8000.0f};
        
        // Add to faction system (you'll need to extend FactionSystem)
    }
    
    void createPlayer() {
        Entity player = registry.createEntity();
        
        registry.addComponent<Transform>(player, Transform{});
        registry.addComponent<PhysicalStats>(player, PhysicalStats{});
        registry.addComponent<Psychology>(player, Psychology{});
        registry.addComponent<SocialTraits>(player, SocialTraits{"player_faction"});
        registry.addComponent<Inventory>(player, Inventory{});
        registry.addComponent<Equipment>(player, Equipment{});
        registry.addComponent<CombatStats>(player, CombatStats{});
        registry.addComponent<AIBehavior>(player, AIBehavior{});
        registry.addComponent<Needs>(player, Needs{});
    }
};