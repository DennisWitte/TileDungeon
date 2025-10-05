#include "CoreEngine.hpp"

namespace Core
{
    unsigned int Core::Entity::_nextId = 0;

    Entity::Entity()
    {
        Name = "";
        _id = _nextId;
        _nextId++;
        SetEnabled(true);
    }
    Entity::~Entity() {}

    /// @brief Will be called when the Entity gets enabled
    void Entity::OnEnable()
    {
        for (const auto &[type, component] : _components)
        {
            component->OnEntityEnable();
        }
    }
    /// @brief Will be called when the Entity gets disabled
    void Entity::OnDisable()
    {
        for (const auto &[type, component] : _components)
        {
            component->OnEntityDisable();
        }
    }
    /// @brief Will be called every frame and updates all Components on this Entity
    void Entity::OnUpdate()
    {
        if (!_enabled)
            return;

        for (const auto &[type, component] : _components)
        {
            component->OnUpdate();
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