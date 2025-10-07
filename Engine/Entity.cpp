#include "CoreEngine.hpp"

namespace Core
{
    unsigned int Core::Entity::_nextId = 0;

    Entity::Entity(std::shared_ptr<Core::Scene> scene)
    {
        Name = "";
        _id = _nextId;
        _nextId++;
        _scene = scene;
        SetEnabled(true);
    }
    Entity::~Entity() {}

    /// @brief Will be called when the Entity gets enabled
    void Entity::Enable()
    {
        for (const auto &[type, component] : _components)
        {
            component->EntityEnable();
        }
    }
    /// @brief Will be called when the Entity gets disabled
    void Entity::Disable()
    {
        for (const auto &[type, component] : _components)
        {
            component->EntityDisable();
        }
    }
    /// @brief Will be called every frame and updates all Components on this Entity. Will be called before drawing.
    void Entity::Update()
    {
        if (!_enabled)
            return;

        for (const auto &[type, component] : _components)
        {
            component->Update();
        }
    }

    /// @brief Will be called every frame during the draw context. Use draw commands here.
    void Entity::Draw()
    {
        if (!_enabled)
            return;

        for (const auto &[type, component] : _components)
        {
            component->Draw();
        }
    }

    /// @brief Sets the 'enabled' state of this Entity. This will affect all Components on it as well.
    /// @param enabled
    void Entity::SetEnabled(bool enabled)
    {
        if (_enabled && !enabled)
            OnDisable();
        else if (!_enabled && enabled)
            OnEnable();
        _enabled = enabled;
    }

    bool Entity::IsEnabled() const { return _enabled; }
}