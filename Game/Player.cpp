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

void Player::StartTick()
{
    _isInTick = true;
    _tickTimer = _tickDuration;
}

void Player::OnUpdate()
{

    std::shared_ptr<Core::Transform> transform = this->_transform.lock();
    if (transform == nullptr)
        return;

    std::shared_ptr<CharacterController> controller = this->_controller.lock();
    if (controller == nullptr)
        return;

    std::shared_ptr<Core::TextRenderer> textRenderer = this->_textRenderer.lock();
    if (textRenderer == nullptr)
        return;

    textRenderer->SetText("FPS: " + std::to_string(GetFPS()));

    if (_isInTick)
    {
        _tickTimer -= GetFrameTime();

        if (_tickTimer <= 0.0f)
        {
            _isInTick = false;
            _tickTimer = 0.0f;
            _fromPosition = _targetPosition;
            _fromRotation = _targetRotation;
        }

        float norm = Normalize(_tickDuration - _tickTimer, 0, _tickDuration);
        transform->SetPosition(Vector3Lerp(_fromPosition, _targetPosition, norm));
        transform->SetRotation(QuaternionSlerp(_fromRotation, _targetRotation, norm));
        printf("Norm: %f", norm);

        return;
    }

    // POSITION
    if (IsKeyDown(KEY_W))
    {
        // controller->Move(Vector3Scale(transform->GetForward(), (float)2 * GetFrameTime()));
        _targetPosition = Vector3Add(transform->GetPosition(), transform->GetForward());
        _fromPosition = transform->GetPosition();
        StartTick();
        return;
    }

    if (IsKeyDown(KEY_S))
    {
        _targetPosition = Vector3Add(transform->GetPosition(), Vector3Scale(transform->GetForward(), -1));
        _fromPosition = transform->GetPosition();
        // controller->Move(Vector3Scale(transform->GetForward(), -(float)2 * GetFrameTime()));
        StartTick();
        return;
    }

    if (IsKeyDown(KEY_A))
    {
        _targetPosition = Vector3Add(transform->GetPosition(), transform->GetRight());
        _fromPosition = transform->GetPosition();
        // controller->Move(Vector3Scale(transform->GetRight(), (float)2 * GetFrameTime()));
        StartTick();
        return;
    }

    if (IsKeyDown(KEY_D))
    {
        _targetPosition = Vector3Add(transform->GetPosition(), Vector3Scale(transform->GetRight(), -1));
        _fromPosition = transform->GetPosition();
        // controller->Move(Vector3Scale(transform->GetRight(), -(float)2 * GetFrameTime()));
        StartTick();
        return;
    }

    // ROTATION
    if (IsKeyDown(KEY_Q))
    {
        // controller->Rotate(90.0f * DEG2RAD * GetFrameTime());
        _targetRotation = QuaternionFromAxisAngle({0, 1, 0}, transform->GetEulerAngles().y + (90.0f * DEG2RAD)), transform->GetRotation();
        _fromRotation = transform->GetRotation();
        StartTick();
        return;
    }
    if (IsKeyDown(KEY_E))
    {
        // controller->Rotate(-90.0f * DEG2RAD * GetFrameTime());
        _targetRotation = QuaternionFromAxisAngle({0, 1, 0}, transform->GetEulerAngles().y - (90.0f * DEG2RAD)), transform->GetRotation();
        _fromRotation = transform->GetRotation();
        StartTick();
        return;
    }

    //_cameraTarget->SetPosition(_transform->GetPosition());
    //_cameraTarget->SetEulerAngles(_transform->GetEulerAngles());
}