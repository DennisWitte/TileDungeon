#include "Game.hpp"
#include "Game/JungleScene.hpp"
using namespace Core;
using namespace std;

std::shared_ptr<Model> quad;

Game::Game()
{
    // Initialisierungscode
}

void Game::DrawPerformanceTest()
{ // 28-29FPS nach 3-4 sekunden
    int tileCount = 200 * 200;
    float x = 0;
    float z = 0;
    for (int i = 0; i < tileCount; i++)
    {
        DrawModel(*quad, {x, 0, z}, 1, WHITE);
        x++;
        if (x > 199)
        {
            x = 0;
            z++;
        }
    }
}

void Game::Run()
{
    InitWindow(800, 600, "Tile Dungeon");
    SetTargetFPS(60);

    /* Core::Camera camera;
     camera.SetPosition({10.0f, 3.0f, 10.0f});
     camera.SetTarget({0.0f, 2.0f, 0.0f});
     camera.SetUp({0.0f, 1.0f, 0.0f});
     camera.SetFov(65.0f);
     camera.SetProjection(Core::Camera::CAMERA_PERSPECTIVE);
    */

    Camera3D rlCam;
    rlCam.position = {10, 5, 10};
    rlCam.target = {0, 0, 0};
    rlCam.up = {0.0f, 1.0f, 0.0f};
    rlCam.fovy = 65;
    rlCam.projection = 0;

    JungleScene scene;

    DisableCursor();
    char fps[9];
    float tickTime = 0;

    // TEST
    //  Texture tex = LoadTexture("../Resources/JungleGround.png");
    //  ResourcesController::TryGetModel("../Resources/Quad.glb", quad);
    //  quad->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = tex;

    while (!WindowShouldClose()) // Hauptspiel-Schleife
    {
        UpdateCamera(&rlCam, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(MAGENTA); // Hintergrundfarbe setzen

        BeginMode3D(rlCam);
        // TEST
        //  DrawPerformanceTest();

        scene.Update();
        DrawGrid(100, 1.0f);

        EndMode3D();

        snprintf(fps, sizeof(fps), "FPS: %d", GetFPS());
        DrawText(fps, 10, 10, 25, RED);

        EndDrawing();

        tickTime = tickTime + GetFrameTime();
        if (tickTime > 1)
            tickTime = 0;
    }

    CloseWindow(); // Fenster schließen
}
