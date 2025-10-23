#pragma once

#include <string>

#include <vector>

#include <memory>


struct ColorTint {
    float r = 1.0f;
    float g = 1.0f;
    float b = 1.0f;
    float a = 1.0f;

    ColorTint() = default;
    ColorTint(float red, float green, float blue, float alpha = 1.0f) 
        : r(red), g(green), b(blue), a(alpha) {}
    
    // Common colors as static constants
    static ColorTint White() { return ColorTint(1.0f, 1.0f, 1.0f, 1.0f); }
    static ColorTint Black() { return ColorTint(0.0f, 0.0f, 0.0f, 1.0f); }
    static ColorTint Red() { return ColorTint(1.0f, 0.0f, 0.0f, 1.0f); }
    static ColorTint Green() { return ColorTint(0.0f, 1.0f, 0.0f, 1.0f); }
    static ColorTint Blue() { return ColorTint(0.0f, 0.0f, 1.0f, 1.0f); }
    static ColorTint Yellow() { return ColorTint(1.0f, 1.0f, 0.0f, 1.0f); }
};

struct Sprite {


    std::string textureId;
    int width = 32;
    int height = 32;
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    int frame = 0;
    int totalFrames = 1;
    float frameTime = 0.0f;
    float currentTime = 0.0f;
    bool animated = false;





};


struct Renderable {

    int layer = 0;
    bool visible = true;
    float rotation = 0.0f;
    float scale = 1.0f;








};


struct PawnAppearance {
    std::string bodyType = "average";
    std::string hairStyle = "short";
    ColorTint hairColor{0.3f, 0.2f, 0.1f, 1.0f};
    ColorTint skinColor{0.8f, 0.6f, 0.4f, 1.0f};
    std::vector<std::string> scars;
    std::string headShape = "normal";
};

struct EquipmentSprites {
    std::string headGear;
    std::string torsoGear;
    std::string legGear;
    std::string weapon;
};


struct Tile {
    std::string terrainType;
    float elevation = 0.0f;
    float fertility = 1.0f;
    bool constructed = false;
    std::string buildingType; 
};

struct Camera {
    float x = 0.0f;
    float y = 0.0f;
    float zoom = 1.0f;
    float viewportWidth = 800.0f;
    float viewportHeight = 600.0f;
};

