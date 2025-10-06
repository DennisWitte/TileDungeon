#include "JungleScene.hpp"
using namespace Core;
using namespace std;

JungleScene::JungleScene() : Scene()
{
    ResourcesService::Load<Model>("../Resources/PalmTree/PalmTrees.glb");
    ResourcesService::Load<Model>("../Resources/ArtDungeonScene1/ArtDungeonScene1.glb");

    ResourcesService::Load<Model>("../Resources/Quad.glb");
    ResourcesService::Load<Texture>("../Resources/JungleGround.png");
    ResourcesService::Load<Texture>("../Resources/ArtDungeonScene1/Tiles_Moss.jpg");
    std::vector<std::string> alphaCutoutShaderPaths;
    alphaCutoutShaderPaths.emplace_back("../Resources/Shader/AlphaCutout.vs");
    alphaCutoutShaderPaths.emplace_back("../Resources/Shader/AlphaCutout.fs");
    ResourcesService::Load<Shader>(alphaCutoutShaderPaths);

    std::vector<std::string> diffuseShaderPaths;
    diffuseShaderPaths.emplace_back("../Resources/Shader/OpaquePS1.vs");
    diffuseShaderPaths.emplace_back("../Resources/Shader/OpaquePS1.fs");
    ResourcesService::Load<Shader>(diffuseShaderPaths);

    // Place a few trees
    for (size_t i = 0; i < 200; i++)
    {
        // PlaceRandomTree();
    }

    // GenerateGround();

    std::shared_ptr<Core::Entity> levelModelEntity = CreateEntity();
    levelModelEntity->Name = "ArtDungeonScene1";
    auto t = levelModelEntity->AddComponent<Core::Transform>();
    t->SetPosition({0, 0, 0});
    t->SetEulerAngles({0, 0, 0});
    t->SetScale({1, 1, 1});

    auto r = levelModelEntity->AddComponent<Core::MeshRenderer>();
    r->SetModel("../Resources/ArtDungeonScene1/ArtDungeonScene1.glb");
    r->SetBackfaceCulling(true);
    r->SetShader(-1, "../Resources/Shader/OpaquePS1.vs", "../Resources/Shader/OpaquePS1.fs");
    // r->SetTexture(1, "texture0", "../Resources/ArtDungeonScene1/Tiles_Moss.jpg");
    // r->SetTexture(1, "texture1", "../Resources/ArtDungeonScene1/Lightmap.png");

    Enable();
}

JungleScene::~JungleScene()
{
    ResourcesService::Unload<Model>("../Resources/PalmTree/PalmTrees.glb");
    ResourcesService::Unload<Model>("../Resources/Quad.glb");
    ResourcesService::Unload<Texture>("../Resources/JungleGround.png");
    ResourcesService::Unload<Model>("../Resources/ArtDungeonScene1/ArtDungeonScene1.glb");
    ResourcesService::Unload<Texture>("../Resources/ArtDungeonScene1/Tiles_Moss.jpg");

    std::vector<std::string> shaderPaths;
    shaderPaths.emplace_back("../Resources/Shader/AlphaCutout.vs");
    shaderPaths.emplace_back("../Resources/Shader/AlphaCutout.fs");
    ResourcesService::Unload<Shader>(shaderPaths);

    std::vector<std::string> diffuseShaderPaths;
    diffuseShaderPaths.emplace_back("../Resources/Shader/OpaquePS1.vs");
    diffuseShaderPaths.emplace_back("../Resources/Shader/OpaquePS1.fs");
    ResourcesService::Unload<Shader>(diffuseShaderPaths);
}

void JungleScene::PlaceRandomTree()
{
    std::shared_ptr<Core::Entity> treeEntity = CreateEntity();
    treeEntity->Name = "PalmTree";
    auto t = treeEntity->AddComponent<Core::Transform>();
    t->SetPosition({(float)GetRandomValue(0, 100), 0, (float)GetRandomValue(0, 100)});
    t->SetEulerAngles({0, (float)GetRandomValue(0, DEG2RAD * 360), 0});
    t->SetScale({1, (float)GetRandomValue(1, 2) * 0.5f, 1});

    auto r = treeEntity->AddComponent<Core::MeshRenderer>();
    r->SetModel("../Resources/PalmTree/PalmTrees.glb");
    r->SetBackfaceCulling(false);
    r->SetShader(1, "../Resources/Shader/AlphaCutout.vs", "../Resources/Shader/AlphaCutout.fs");
    r->SetAlphaThreshold(1, 0.6f);
}

void JungleScene::GenerateGround()
{
    int tileCount = 200 * 200;
    float x = 0;
    float z = 0;
    for (int i = 0; i < tileCount; i++)
    {
        shared_ptr<Entity> groundEntity = CreateEntity();
        groundEntity->Name = "Ground " + to_string(i);
        auto t = groundEntity->AddComponent<Core::Transform>();
        t->SetPosition({x, 0, z});
        t->SetScale({1, 1, 1});

        auto r = groundEntity->AddComponent<Core::MeshRenderer>();
        r->SetModel("../Resources/Quad.glb");
        r->SetBackfaceCulling(true);
        r->SetTexture(0, "../Resources/JungleGround.png");

        x++;
        if (x > 199)
        {
            x = 0;
            z++;
        }
    }
}
