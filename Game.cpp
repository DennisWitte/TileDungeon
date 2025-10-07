#include "Game.hpp"
#include "Game/JungleScene.hpp"
#include "Engine/RenderManager.hpp"
using namespace Core;
using namespace std;

Game::Game()
{
    // Initialisierungscode
}

void Game::Run()
{
    InitWindow(800, 600, "Tile Dungeon");
    SetTargetFPS(60);

    JungleScene scene;

    DisableCursor();

    while (!WindowShouldClose()) // Hauptspiel-Schleife
    {
        SceneManager::Update();
        RenderManager::RenderCameras();
    }
    CloseWindow(); // Fenster schließen
}
