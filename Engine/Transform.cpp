
#include "CoreEngine.hpp"

namespace Core
{
    ::Transform _raylibTransform;

    Transform::Transform() {}
    Transform::~Transform() {}

    void Transform::SetEulerAngles(const Vector3 &eulerAngles)
    {
        _raylibTransform.rotation = QuaternionFromEuler(WrapAngle(eulerAngles.z), WrapAngle(eulerAngles.y), WrapAngle(eulerAngles.x));
    }
    void Transform::SetEulerAnglesDegrees(const Vector3 &eulerAngles) { _raylibTransform.rotation = QuaternionFromEuler(eulerAngles.z * DEG2RAD, eulerAngles.y * DEG2RAD, eulerAngles.x * DEG2RAD); }

    Vector3 Transform::GetForward() const
    {
        return Vector3Normalize(Vector3Transform((Vector3){0, 0, 1}, QuaternionToMatrix(_raylibTransform.rotation)));
    }

    Vector3 Transform::GetUp() const
    {
        return Vector3Normalize(Vector3Transform((Vector3){0, 1, 0}, QuaternionToMatrix(_raylibTransform.rotation)));
    }

    Vector3 Transform::GetRight() const
    {
        return Vector3Normalize(Vector3Transform((Vector3){1, 0, 0}, QuaternionToMatrix(_raylibTransform.rotation)));
    }

    Quaternion Transform::LookRotation(Vector3 direction, Vector3 up)
    {
        direction = Vector3Normalize(direction);
        Vector3 right = Vector3Normalize(Vector3CrossProduct(up, direction));
        Vector3 recalculatedUp = Vector3CrossProduct(direction, right);

        // Erstelle LookAt-Matrix
        Matrix lookAt = {
            right.x, right.y, right.z, 0,
            recalculatedUp.x, recalculatedUp.y, recalculatedUp.z, 0,
            -direction.x, -direction.y, -direction.z, 0,
            0, 0, 0, 1};

        return QuaternionFromMatrix(lookAt);
    }

    void Transform::LookAt(Vector3 position)
    {
        Vector3 direction = position - _raylibTransform.translation;
        _raylibTransform.rotation = LookRotation(direction);
    }

    void Transform::Rotate(float angleRadians, Vector3 axis)
    {
        _raylibTransform.rotation = QuaternionMultiply(QuaternionFromAxisAngle(axis, angleRadians), _raylibTransform.rotation);
    }

    void Transform::OnDraw3D()
    {
        Vector3 startPos = GetPosition();
        Vector3 endPos = Vector3Add(startPos, GetUp());
        DrawLine3D(startPos, endPos, GREEN);

        endPos = Vector3Add(startPos, GetRight());
        DrawLine3D(startPos, endPos, RED);

        endPos = Vector3Add(startPos, GetForward());
        DrawLine3D(startPos, endPos, BLUE);
    }
}