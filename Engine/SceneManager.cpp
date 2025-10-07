#include "CoreEngine.hpp"

namespace Core
{
    std::unordered_map<std::string, std::shared_ptr<Core::Scene>> Core::SceneManager::_scenes;

    std::shared_ptr<Core::Scene> SceneManager::CreateScene(std::string name)
    {
        if (_scenes.find(name) != _scenes.end())
        {
            return _scenes[name];
        }

        std::shared_ptr<Core::Scene> scene = std::make_shared<Core::Scene>();
        _scenes[name] = scene;
        return scene;
    }

    void SceneManager::Update()
    {
        for (const auto &[name, scene] : _scenes)
        {
            scene->Update();
        }
    }
}