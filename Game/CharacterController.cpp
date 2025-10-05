#include "CharacterController.hpp"

Vector3 _moveThisFrame;
Vector3 _targetEulerAngles;

void CharacterController::Move(Vector3 movement)
{
    _moveThisFrame = {_moveThisFrame.x + movement.x, _moveThisFrame.y + movement.y, _moveThisFrame.z + movement.z};
}

void CharacterController::Rotate(float yAngle)
{
    _targetEulerAngles = {_targetEulerAngles.x, _targetEulerAngles.y + yAngle, _targetEulerAngles.z};
}

void CharacterController::Update(float deltaTime, float tickTime, Core::Transform &transform)
{
    transform.SetPosition(Vector3Add(transform.GetPosition(), _moveThisFrame));
    // transform.SetEulerAngles(Vector3Add(transform.GetPosition(), _targetEulerAngles));
    _moveThisFrame = {0, 0, 0};
    _targetEulerAngles = {0, 0, 0};
    // transform.SetPosition(Vector3Lerp(transform.GetPosition(), _targetPosition, tickTime));
    // transform.SetEulerAngles(Vector3Lerp(transform.GetEulerAngles(), _targetEulerAngles, tickTime));
}