#pragma once
#include "../Engine/CoreEngine.hpp"

class CharacterController
{
public:
    void Move(Vector3 movement);
    void Rotate(float yAngle);
    void Update(float deltaTime, float tickTime, Core::Transform &transform);

private:
    Shader _alphaCutoutShader;
    Texture _jungleGroundTexture;

    std::vector<std::shared_ptr<Core::Transform>> _transforms;
    std::vector<std::shared_ptr<Core::MeshRenderer>> _renderer;
};