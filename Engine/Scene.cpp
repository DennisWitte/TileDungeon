#include "CoreEngine.hpp"

namespace Core
{
    std::unordered_map<int, std::shared_ptr<Core::Entity>> _entities;

    Scene::Scene()
    {
    }
    Scene::~Scene()
    {
    }

    /// @brief Create a new Entity in this scene.
    /// @return
    std::shared_ptr<Core::Entity> Scene::CreateEntity()
    {
        std::shared_ptr<Core::Entity> entity = std::make_shared<Core::Entity>(shared_from_this());
        _entities[entity->GetId()] = entity;
        return entity;
    }

    void Scene::RemoveEntity(int entityId)
    {
        // Entferne die Entity anhand ihrer ID aus der Map
        _entities.erase(entityId);
    }

    void Scene::Enable()
    {
        for (const auto &[id, e] : _entities)
        {
            e->Enable();
        }
    }

    void Scene::Disable()
    {
        for (const auto &[id, e] : _entities)
        {
            e->Disable();
        }
    }

    void Scene::Update()
    {
        //  OnUpdate();

        for (auto &pair : _entities)
        {
            pair.second->Update();
        }
    }

    void Scene::Draw()
    {
        // OnDraw();

        for (auto &pair : _entities)
        {
            pair.second->Draw();
        }
    }
}
