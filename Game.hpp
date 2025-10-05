#pragma once
#include <iostream>
#include "Engine/CoreEngine.hpp"

class Game
{
public:
    Game();
    void Run();
    void PlaceRandomTree();
    void GenerateGround();
    void DrawPerformanceTest();
};
