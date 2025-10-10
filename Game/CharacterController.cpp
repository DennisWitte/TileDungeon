#include "CharacterController.hpp"

Vector3 _moveThisFrame;
float _rotationThisFrame;

void CharacterController::OnEnable()
{
    _moveThisFrame = {0, 0, 0};
    _rotationThisFrame = 0;
    _transform = GetEntity()->GetComponent<Core::Transform>();
}
void CharacterController::OnDisable()
{
}

void CharacterController::OnUpdate()
{
    if (!_transform.lock())
        return;

    std::shared_ptr<Core::Transform> transform = this->_transform.lock();

    transform->SetPosition(Vector3Add(transform->GetPosition(), _moveThisFrame));
    // transform->Rotate(_targetEulerAngles);
    _moveThisFrame = {0, 0, 0};
    _targetEulerAngles = 0;
    // transform.SetPosition(Vector3Lerp(transform.GetPosition(), _targetPosition, tickTime));
    // transform.SetEulerAngles(Vector3Lerp(transform.GetEulerAngles(), _targetEulerAngles, tickTime));
}

void CharacterController::Move(Vector3 movement)
{
    _moveThisFrame = {_moveThisFrame.x + movement.x, _moveThisFrame.y + movement.y, _moveThisFrame.z + movement.z};
}

void CharacterController::Rotate(float yAngle)
{
    _targetEulerAngles += yAngle;
}