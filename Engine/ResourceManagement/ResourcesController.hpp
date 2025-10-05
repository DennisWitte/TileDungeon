#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>

namespace Core
{
    template <typename T>
    std::shared_ptr<T> LoadResource(const std::string &filePath); // Generischer Fallback

    template <typename T>
    void UnloadResource(const std::string &filePath); // Generischer Fallback

    /// @brief Generic Resources Controller. Can be used by providing the type that you want to load / unload or get.
    /// @tparam T
    template <typename T>
    class ResourcesController
    {
    public:
        ResourcesController() {}
        ~ResourcesController() {}

        static void Load(const std::string &filePath)
        {
            if (_resourceMap.find(filePath) != _resourceMap.end())
                return;

            std::shared_ptr<T> resource = LoadResource<T>(filePath);
            _resourceMap[filePath] = resource;
        }

        static void Unload(const std::string &filePath)
        {
            if (_resourceMap.find(filePath) == _resourceMap.end())
                return;

            UnloadResource<T>(filePath);
            _resourceMap.erase(filePath);
        }

        static bool TryGet(const std::string &filePath, std::shared_ptr<T> &outResource)
        {
            auto it = _resourceMap.find(filePath);
            if (it == _resourceMap.end())
                return false;

            outResource = it->second;
            return true;
        }

    private:
        static std::unordered_map<std::string, std::shared_ptr<T>> _resourceMap;
    };

    template <typename T>
    std::unordered_map<std::string, std::shared_ptr<T>> ResourcesController<T>::_resourceMap;

#pragma region LOADING / UNLOADING Implementations

    // Spezialisierung für Model
    template <>
    inline std::shared_ptr<Model> LoadResource<Model>(const std::string &filePath)
    {
        Model rawModel = LoadModel(filePath.c_str());
        if (rawModel.meshCount == 0)
        {
            std::cerr << "ERROR: Can't load Model at " << filePath << std::endl;
        }
        return std::make_shared<Model>(rawModel);
    }
    template <>
    inline void UnloadResource<Model>(const std::string &filePath)
    {
        std::shared_ptr<Model> res;
        if (ResourcesController<Model>::TryGet(filePath, res))
        {
            UnloadModel(*res);
        }
    }

    // Spezialisierung für Texture
    template <>
    inline std::shared_ptr<Texture> LoadResource<Texture>(const std::string &filePath)
    {
        Texture tex = LoadTexture(filePath.c_str());
        return std::make_shared<Texture>(tex);
    }

    template <>
    inline void UnloadResource<Texture>(const std::string &filePath)
    {
        std::shared_ptr<Texture> res;
        if (ResourcesController<Texture>::TryGet(filePath, res))
        {
            UnloadTexture(*res);
        }
    }

#pragma endregion
}