#pragma once
#include "ResourcesController.hpp"

namespace Core
{
    class ResourcesService
    {
    public:
        template <typename T>
        static void Load(const std::string &filePath)
        {
            GetController<T>().Load(filePath);
        }

        template <typename T>
        static void Load(const std::vector<std::string> &filePaths)
        {
            GetController<T>().Load(filePaths);
        }

        template <typename T>
        static void Unload(const std::string &filePath)
        {
            GetController<T>().Unload(filePath);
        }

        template <typename T>
        static void Unload(const std::vector<std::string> &filePaths)
        {
            GetController<T>().Unload(filePaths);
        }

        template <typename T>
        static bool TryGet(const std::string &filePath, std::shared_ptr<T> &outResource)
        {
            return GetController<T>().TryGet(filePath, outResource);
        }

        template <typename T>
        static bool TryGet(const std::vector<std::string> &filePaths, std::shared_ptr<T> &outResource)
        {
            return GetController<T>().TryGet(filePaths, outResource);
        }

    private:
        template <typename T>
        static ResourcesController<T> &GetController()
        {
            static ResourcesController<T> controller;
            return controller;
        }
    };
}
