#pragma once
#include "../Engine/CoreEngine.hpp"
#include "CharacterController.hpp"
#include <memory>

class Player
{
public:
    Player();
    ~Player();
    std::shared_ptr<Core::Transform> GetCameraTarget() { return _cameraTarget; };
    std::shared_ptr<Core::Transform> GetTransform() { return _transform; };

    void Update(float tickTime);

private:
    std::shared_ptr<Core::Transform> _transform;
    std::shared_ptr<Core::Transform> _cameraTarget;
    std::shared_ptr<Core::MeshRenderer> _meshRenderer;
    std::shared_ptr<CharacterController> _controller;
    Vector3 _nextMoveDirection;
};