// Refactored with Delegation Pattern and Lazy Loading Pattern
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "cocos2d.h"
#include <unordered_map>
#include <string>
#include <functional>

class ResourceManager {
public:
    // Get texture from the cache or load it if not cached
    static cocos2d::Texture2D* getTexture(const std::string& filepath);

    // Asynchronously load a list of resources
    static void loadResourcesAsync(
        const std::vector<std::string>& filepaths,
        std::function<void(float)> progressCallback = nullptr,
        std::function<void()> completionCallback = nullptr
    );

    // Create a new sprite from a given file path
    static cocos2d::Sprite* CreateNewSprite(const std::string& path);

    // Clear the texture cache
    static void clearTextureCache();

private:
    ResourceManager(); // Private constructor for singleton pattern
    std::unordered_map<std::string, cocos2d::Texture2D*> textureCache; // Cache for textures
    static ResourceManager* getInstance(); // Get the singleton instance

};

#endif // RESOURCEMANAGER_H
