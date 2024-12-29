// Refactored with Delegation Pattern and Lazy Loading Pattern
#include "ResourceManager.h"

ResourceManager::ResourceManager() {}

ResourceManager* ResourceManager::getInstance() {
    static ResourceManager instance; // Singleton instance
    return &instance;
}

cocos2d::Texture2D* ResourceManager::getTexture(const std::string& filepath) {
    auto& cache = getInstance()->textureCache;
    if (cache.find(filepath) == cache.end()) {
        // If the texture is not found in the cache, load it
        cache[filepath] = cocos2d::Director::getInstance()->getTextureCache()->addImage(filepath);
    }
    return cache[filepath];
}

void ResourceManager::loadResourcesAsync(
    const std::vector<std::string>& filepaths,
    std::function<void(float)> progressCallback,
    std::function<void()> completionCallback
) {
    int total = filepaths.size();
    int loaded = 0;

    // Asynchronously load each texture and track the progress
    for (const auto& filepath : filepaths) {
        cocos2d::Director::getInstance()->getTextureCache()->addImageAsync(filepath, [=, &loaded](cocos2d::Texture2D* texture) mutable {
            // Store the texture in the cache when it finishes loading
            getInstance()->textureCache[filepath] = texture;
            loaded++;

            // Update progress if the callback is provided
            if (progressCallback) {
                progressCallback(static_cast<float>(loaded) / total);
            }

            // Call the completion callback once all resources are loaded
            if (loaded == total && completionCallback) {
                completionCallback();
            }
            });
    }
}

cocos2d::Sprite* ResourceManager::CreateNewSprite(const std::string& path)
{
    // Create and return a new sprite from the given path
    cocos2d::Sprite* newSprite = cocos2d::Sprite::create(path);
    return newSprite;
}

void ResourceManager::clearTextureCache() {
    // Clear the texture cache and remove all textures from the Director's cache
    auto& cache = getInstance()->textureCache;
    cache.clear();
    cocos2d::Director::getInstance()->getTextureCache()->removeAllTextures();
}
