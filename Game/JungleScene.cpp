#include "JungleScene.hpp"
using namespace Core;
using namespace std;

JungleScene::JungleScene() : Scene()
{
    ResourcesService::Load<Model>("../Resources/PalmTree/PalmTrees.glb");
    ResourcesService::Load<Model>("../Resources/Quad.glb");

    /*
    std::shared_ptr<Model> treeModel;
    if (ResourcesController::TryGetModel("../Resources/PalmTree/PalmTrees.glb", treeModel))
    {
        GenTextureMipmaps(&treeModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture);
        SetTextureFilter(treeModel->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture, TEXTURE_FILTER_POINT); // ⬅️ Für Mipmaps notwendig
        GenTextureMipmaps(&treeModel->materials[1].maps[MATERIAL_MAP_DIFFUSE].texture);
        SetTextureFilter(treeModel->materials[1].maps[MATERIAL_MAP_DIFFUSE].texture, TEXTURE_FILTER_POINT); // ⬅️ Für Mipmaps notwendig
    }

     std::shared_ptr<Model> quadModel;
     if (ResourcesController::TryGetModel("../Resources/Quad.glb", quadModel))
     {
         _jungleGroundTexture = LoadTexture("../Resources/JungleGround.png");
         GenTextureMipmaps(&_jungleGroundTexture);                     // ⬅️ Mipmaps generieren
         SetTextureFilter(_jungleGroundTexture, TEXTURE_FILTER_POINT); // ⬅️ Für Mipmaps notwendig
     }

    _alphaCutoutShader = LoadShader("../Resources/Shader/AlphaCutout.vs", "../Resources/Shader/AlphaCutout.fs");
    int locThreshold = GetShaderLocation(_alphaCutoutShader, "alphaThreshold");
    float threshold = 0.8f;
    SetShaderValue(_alphaCutoutShader, locThreshold, &threshold, SHADER_UNIFORM_FLOAT);
*/
    // Place a few trees
    for (size_t i = 0; i < 200; i++)
    {
        PlaceRandomTree();
    }

    GenerateGround();

    Enable();
}

JungleScene::~JungleScene()
{
    ResourcesService::Unload<Model>("../Resources/PalmTree/PalmTrees.glb");
    ResourcesService::Unload<Model>("../Resources/Quad.glb");
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
    // r->SetShader(1, _alphaCutoutShader);
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
        //        r->SetTexture(0, _jungleGroundTexture);

        x++;
        if (x > 199)
        {
            x = 0;
            z++;
        }
    }
}
