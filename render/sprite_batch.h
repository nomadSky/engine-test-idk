#pragma once
#include "rendering_components.h"
#include "texture_manager.h"
#include <vector>
#include <algorithm>

struct SpriteRenderCommand {
    float x, y;
    float width, height;
    std::string textureId;
    int layer;
    float rotation;
    float scale;
    ColorTint color;
    int frame = 0;
    int totalFrames = 1;
};

class SpriteBatch {
private:
    std::vector<SpriteRenderCommand> renderCommands;
    TextureManager& textureManager;

public:
    SpriteBatch(TextureManager& texManager) : textureManager(texManager) {}

    void clear() {
        renderCommands.clear();
    }

    void submit(const SpriteRenderCommand& command) {
        renderCommands.push_back(command);
    }

    void sortByLayer() {
        std::sort(renderCommands.begin(), renderCommands.end(),
            [](const SpriteRenderCommand& a, const SpriteRenderCommand& b) {
                return a.layer < b.layer;
            });
    }

    void render() {
        sortByLayer();
        
        for (const auto& command : renderCommands) {
            auto texture = textureManager.getTexture(command.textureId);
            if (!texture) continue;

            // Here you'd implement actual rendering with your graphics library
            // This is where you'd draw the sprite with the given parameters
            drawSprite(texture, command);
        }
    }

private:
    void drawSprite(std::shared_ptr<Texture> texture, const SpriteRenderCommand& command) {
        // Implementation depends on your graphics library
        // Example pseudo-code:
        // - Calculate source rectangle based on frame
        // - Apply rotation and scale
        // - Draw with color tint
        // - Handle transparency
    }
};