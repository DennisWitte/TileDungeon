#include "Player.hpp"
#include <string>

Player::Player()
{
}

Player::~Player()
{
}

void Player::Update(float tickTime)
{

    if (GetKeyPressed() == KEY_W)
    {
        _controller->Move({0, 0, (float)1 * GetFrameTime()});
    }

    if (GetKeyPressed() == KEY_S)
    {
        _controller->Move({0, 0, -((float)1 * GetFrameTime())});
    }
    // _controller->Rotate(10 * GetFrameTime());
    // _controller->Update(0, tickTime, *_transform);
    Vector3 nextPosition = {_transform->GetPosition().x + GetFrameTime(), 2, _transform->GetPosition().z + GetFrameTime()};
    //_transform->LookAt(nextPosition);
    float yRot = _transform->GetEulerAngles().y + GetFrameTime();
    if (yRot > PI / 2)
        yRot = 0;
    if (yRot < 0)
        yRot = PI / 2;

    std::string eulerAnglesText = std::to_string(_transform->GetEulerAngles().y);
    DrawText(eulerAnglesText.c_str(), 10, 10, 25, BLACK);

    Vector3 dir = Vector3Subtract({0, 0, 0}, _transform->GetPosition());
    _transform->SetRotation(_transform->LookRotation(dir));
    _transform->SetPosition(nextPosition);

    //_cameraTarget->SetPosition(_transform->GetPosition());
    //_cameraTarget->SetEulerAngles(_transform->GetEulerAngles());
}