#include "CoreEngine.hpp"

namespace Core
{
    Core::Entity *_entity;

    void Component::SetEntity(Core::Entity *entity) { _entity = entity; }
    Entity *Component::GetEntity() { return _entity; }

    void Component::EntityEnable()
    {
        OnEntityEnable();
    };
    void Component::EntityDisable()
    {
        OnEntityDisable();
    };
    void Component::Enable()
    {
        _enabledSelf = true;
        OnEnable();
    };
    void Component::Disable()
    {
        _enabledSelf = false;
        OnDisable();
    };
    void Component::Update() { OnUpdate(); };
    void Component::Draw3D() { OnDraw3D(); };
    void Component::Draw2D() { OnDraw2D(); };

    bool Component::IsEnabled() const { return _enabledSelf && _entity->IsEnabled(); }
    bool Component::IsEnabledSelf() const { return _enabledSelf; }

}