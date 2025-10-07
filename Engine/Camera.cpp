#include "CoreEngine.hpp"
#include "RenderManager.hpp"

namespace Core
{
    // ::Camera _raylibCamera; // Make sure we can use this camera in raylib functions

    Camera::Camera()
    {
        // Define the camera to look into our 3d world
        Camera3D camera = {0};
        _raylibCamera = std::make_shared<::Camera>(camera);
        _raylibCamera->position = (Vector3){10.0f, 10.0f, 10.0f}; // Camera position
        _raylibCamera->target = (Vector3){0.0f, 2.0f, 0.0f};      // Camera looking at point
        _raylibCamera->up = (Vector3){0.0f, 1.0f, 0.0f};          // Camera up vector (rotation towards target)
        _raylibCamera->fovy = 45.0f;                              // Camera field-of-view Y
        _raylibCamera->projection = CAMERA_PERSPECTIVE;           // Camera projection type
        RenderTexture r = LoadRenderTexture(800, 600);
        _renderTexture = std::make_shared<RenderTexture>(r);

        RenderManager::RegisterCamera(this);
    }
    Camera::~Camera()
    {
        RenderManager::DeregisterCamera(this);
        UnloadRenderTexture(*_renderTexture);
    }

    void Camera::SetTarget(Vector3 target) { _raylibCamera->target = target; }
    void Camera::SetUp(Vector3 up) { _raylibCamera->up = up; }
    void Camera::SetFov(float fov) { _raylibCamera->fovy = fov; }
    void Camera::SetProjection(ProjectionType projection) { _raylibCamera->projection = projection; }

    Vector3 Camera::GetPosition() { return _raylibCamera->position; }
    Vector3 Camera::GetTarget() { return _raylibCamera->target; }
    Vector3 Camera::GetUp() { return _raylibCamera->up; }
    float Camera::GetFov() { return _raylibCamera->fovy; }
    Camera::ProjectionType Camera::GetProjection() { return (ProjectionType)_raylibCamera->projection; }

    void Camera::OnUpdate()
    {
        // Update the camera (with keyboard and mouse)
        // UpdateCamera(*_raylibCamera, CAMERA_FREE);
    }

    void Camera::Render()
    {
        // Draw the Scene that the camera is part of
        BeginTextureMode(*_renderTexture);
        ClearBackground(MAGENTA);
        BeginMode3D(*_raylibCamera);
        GetEntity()->GetScene()->Draw();
        EndMode3D();
        EndTextureMode();

        // Dann z. B. nebeneinander zeichnen
        // DrawTextureRec(_renderTexture.texture, (Rectangle){0, 0, 640, -720}, (Vector2){0, 0}, WHITE);
        //_raylibCamera.position = transform.GetPosition();
        //_raylibCamera.target = Vector3Subtract(transform.GetPosition(), transform.GetForward());
        // UpdateCamera(&_raylibCamera, CAMERA_FREE);
    }

}
