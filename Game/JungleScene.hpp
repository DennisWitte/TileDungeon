#pragma once
#include "../Engine/CoreEngine.hpp"

class JungleScene
{
public:
    JungleScene();
    ~JungleScene();
    void Draw();

private:
    void GenerateGround();
    void PlaceRandomTree();
    std::shared_ptr<Core::Scene> scene;
};