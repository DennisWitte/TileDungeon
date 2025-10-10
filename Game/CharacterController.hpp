#pragma once
#include "../Engine/CoreEngine.hpp"

class CharacterController : public Core::Component
{
public:
    CharacterController() {};
    ~CharacterController() {};
    void Move(Vector3 movement);
    void Rotate(float yAngle);

private:
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

    std::weak_ptr<Core::Transform> _transform;
    Vector3 _moveThisFrame;
    float _targetEulerAngles;
};