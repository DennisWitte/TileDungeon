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

        static void Shutdown()
        {
            _cameras.clear();
        }

        static void RenderCameras()
        {
            BeginDrawing();

            // First Draw all 3D content through each camera.
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

            // Then Draw all 2D content from all scenes.
            for (const auto &[name, scene] : SceneManager::GetScenes())
            {
                scene->Draw2D();
            }

            EndDrawing();
        }

    private:
        inline static std::vector<Core::Camera *> _cameras;
    };
}