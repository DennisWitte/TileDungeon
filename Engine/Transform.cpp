
#include "CoreEngine.hpp"

namespace Core
{
    Transform::Transform() {}
    Transform::~Transform() {}

    Vector3 Transform::GetForward() const
    {
        return Vector3Normalize(Vector3Transform((Vector3){0, 0, -1}, QuaternionToMatrix(_raylibTransform.rotation)));
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
}