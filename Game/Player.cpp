#include "Player.hpp"
#include <string>

void Player::OnEnable()
{
    _transform = GetEntity()->GetComponent<Core::Transform>();
    _controller = GetEntity()->GetComponent<CharacterController>();
    _textRenderer = GetEntity()->GetComponent<Core::TextRenderer>();
}
void Player::OnDisable()
{
}

void Player::OnUpdate()
{
    if (!_transform.lock() || !_controller.lock())
        return;

    std::shared_ptr<Core::Transform> transform = this->_transform.lock();
    std::shared_ptr<CharacterController> controller = this->_controller.lock();

    std::shared_ptr<Core::TextRenderer> textRenderer = this->_textRenderer.lock();
    if (!textRenderer)
        return;

    textRenderer->SetText("FPS: " + std::to_string(GetFPS()));

    if (GetKeyPressed() == KEY_W)
    {
        controller->Move({0, 0, (float)1 * GetFrameTime()});
    }

    if (GetKeyPressed() == KEY_S)
    {
        controller->Move({0, 0, -((float)1 * GetFrameTime())});
    }
    // _controller->Rotate(10 * GetFrameTime());
    // _controller->Update(0, tickTime, *_transform);
    Vector3 nextPosition = {transform->GetPosition().x + GetFrameTime(), 2, transform->GetPosition().z + GetFrameTime()};
    //_transform->LookAt(nextPosition);
    float yRot = transform->GetEulerAngles().y + GetFrameTime();
    if (yRot > PI / 2)
        yRot = 0;
    if (yRot < 0)
        yRot = PI / 2;

    std::string eulerAnglesText = std::to_string(transform->GetEulerAngles().y);
    DrawText(eulerAnglesText.c_str(), 10, 10, 25, BLACK);

    Vector3 dir = Vector3Subtract({0, 0, 0}, transform->GetPosition());
    transform->SetRotation(transform->LookRotation(dir));
    transform->SetPosition(nextPosition);

    //_cameraTarget->SetPosition(_transform->GetPosition());
    //_cameraTarget->SetEulerAngles(_transform->GetEulerAngles());
}