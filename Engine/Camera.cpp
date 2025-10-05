#include "CoreEngine.hpp"

namespace Core
{
    ::Camera _raylibCamera; // Make sure we can use this camera in raylib functions

    Camera::Camera()
    {
        // Define the camera to look into our 3d world
        _raylibCamera = {0};
        _raylibCamera.position = (Vector3){10.0f, 10.0f, 10.0f}; // Camera position
        _raylibCamera.target = (Vector3){0.0f, 2.0f, 0.0f};      // Camera looking at point
        _raylibCamera.up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
        _raylibCamera.fovy = 45.0f;                              // Camera field-of-view Y
        _raylibCamera.projection = CAMERA_PERSPECTIVE;           // Camera projection type
    }
    Camera::~Camera() {}

    // void Camera::Update() { UpdateCamera(&_raylibCamera, CAMERA_CUSTOM); }
    void Camera::BeginMode3D() { ::BeginMode3D(_raylibCamera); }
    void Camera::EndMode3D() { ::EndMode3D(); }

    void Camera::SetPosition(Vector3 position) { _raylibCamera.position = position; }
    void Camera::SetTarget(Vector3 target) { _raylibCamera.target = target; }
    void Camera::SetUp(Vector3 up) { _raylibCamera.up = up; }
    void Camera::SetFov(float fov) { _raylibCamera.fovy = fov; }
    void Camera::SetProjection(ProjectionType projection) { _raylibCamera.projection = projection; }

    Vector3 Camera::GetPosition() { return _raylibCamera.position; }
    Vector3 Camera::GetTarget() { return _raylibCamera.target; }
    Vector3 Camera::GetUp() { return _raylibCamera.up; }
    float Camera::GetFov() { return _raylibCamera.fovy; }
    Camera::ProjectionType Camera::GetProjection() { return (ProjectionType)_raylibCamera.projection; }

    void Camera::Update(Core::Transform &transform)
    {
        //_raylibCamera.position = transform.GetPosition();
        //_raylibCamera.target = Vector3Subtract(transform.GetPosition(), transform.GetForward());
        UpdateCamera(&_raylibCamera, CAMERA_FREE);
    }

}
