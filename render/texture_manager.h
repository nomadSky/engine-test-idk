#pragma once
#include <unordered_map>

#include <vector>

#include <string>

#include <memory>

class Texture {
    public:

    virtual ~Texture() = default;
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;

};

class TextureManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::string texturePath = "assets/textures/";

public:
    std::shared_ptr<Texture> loadTexture(const std::string& textureId, const std::string& filename) {
        // Implementation depends on your graphics library (SDL, SFML, etc.)
        // For now, return a stub
        auto texture = std::make_shared<Texture>();
        textures[textureId] = texture;
        return texture;
    }

    std::shared_ptr<Texture> getTexture(const std::string& textureId) {
        auto it = textures.find(textureId);
        if (it != textures.end()) {
            return it->second;
        }
        return nullptr;
    }

    void setTexturePath(const std::string& path) {
        texturePath = path;
    }
};