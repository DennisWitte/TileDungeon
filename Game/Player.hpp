#pragma once
#include "../Engine/CoreEngine.hpp"
#include "CharacterController.hpp"

class Player : public Core::Component
{
public:
    Player() {};
    ~Player() {};

private:
    void OnEnable() override;
    void OnDisable() override;
    void OnUpdate() override;

    void StartTick();

    std::weak_ptr<Core::Transform> _transform;
    std::weak_ptr<CharacterController> _controller;
    std::weak_ptr<Core::TextRenderer> _textRenderer;

    bool _isInTick = false;
    float _tickTimer;
    float _tickDuration = 0.333333f;
    Vector3 _targetPosition;
    Vector3 _fromPosition;
};