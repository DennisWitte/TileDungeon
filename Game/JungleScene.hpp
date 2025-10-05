#pragma once
#include "../Engine/CoreEngine.hpp"

class JungleScene : public Core::Scene
{
public:
    JungleScene();
    ~JungleScene();

private:
    void GenerateGround();
    void PlaceRandomTree();
};