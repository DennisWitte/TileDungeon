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
    Entity::~Entity()
    {
        _components.clear();
    }

    /// @brief Will be called when the Entity gets enabled
    void Entity::Enable()
    {
        for (const auto &[type, component] : _components)
        {
            component->EntityEnable();
            component->Enable();
        }
    }
    /// @brief Will be called when the Entity gets disabled
    void Entity::Disable()
    {
        for (const auto &[type, component] : _components)
        {
            component->EntityDisable();
            component->Disable();
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

    /// @brief Will be called every frame during the 3D draw context. Use 3D draw commands here.
    void Entity::Draw3D()
    {
        if (!_enabled)
            return;

        for (const auto &[type, component] : _components)
        {
            component->Draw3D();
        }
    }

    /// @brief Will be called every frame during the 2D draw context. Use 2D draw commands here.
    void Entity::Draw2D()
    {
        if (!_enabled)
            return;

        for (const auto &[type, component] : _components)
        {
            component->Draw2D();
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