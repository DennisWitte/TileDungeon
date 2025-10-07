#pragma once

#include <memory>
#include <vector>
#include "CoreEngine.hpp"

namespace Core
{
    class RenderManager
    {
    public:
        RenderManager();
        ~RenderManager();

        static void RegisterCamera(Core::Camera *camera)
        {
            _cameras.push_back(camera);
        }
        static void DeregisterCamera(Core::Camera *camera)
        {
            _cameras.erase(std::remove(_cameras.begin(), _cameras.end(), camera), _cameras.end());
        }
        static void RenderCameras()
        {
            BeginDrawing();
            for (auto camera : _cameras)
            {
                camera->Render();

                Texture t = camera->GetRenderTexture()->texture;
                DrawTexturePro(t,
                               {0, 0, (float)t.width, -(float)t.height}, // flipped
                               {0, 0, 800, 600},
                               {0, 0},
                               0.0f,
                               WHITE);
            }

            // TODO: Momentan kann man nur 3D in den Draw() methoden der entities rendern. Es braucht eine lösung für UI / 2D
            char fps[9];
            sprintf(fps, "FPS: %02d", GetFPS());
            DrawText(fps, 10, 10, 40, BLACK);
            EndDrawing();
        }

    private:
        inline static std::vector<Core::Camera *> _cameras;
    };
}