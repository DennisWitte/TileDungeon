#pragma once

// C-API von Raylib importieren
#include "../raylib/src/raylib.h"
#include "../raylib/src/raymath.h"

// C++-Wrapper Namespace to avoid name conflicts
namespace Rl
{
    // --- Typen ---
    using ::BoundingBox;
    using ::Camera;
    using ::Camera2D;
    using ::Camera3D;
    using ::Color;
    using ::Font;
    using ::Image;
    using ::Material;
    using ::MaterialMap;
    using ::Matrix;
    using ::Mesh;
    using ::Model;
    using ::Ray;
    using ::RayCollision;
    using ::RenderTexture2D;
    using ::Shader;
    using ::Texture;
    using ::Texture2D;
    using ::Transform;
    using ::Vector2;
    using ::Vector3;
    using ::Vector4;

    // --- Drawing ---
    using ::BeginDrawing;
    using ::ClearBackground;
    using ::EndDrawing;

    // --- Models ---
    using ::DrawModel;
    using ::DrawModelEx;
    using ::LoadModel;
    using ::UnloadModel;

    // --- Text ---
    using ::DrawText;
    using ::GetFontDefault;
    using ::MeasureText;

    // --- Camera ---
    using ::BeginMode3D;
    using ::EndMode3D;
    using ::UpdateCamera;

    // --- Window & Input ---
    using ::CloseWindow;
    using ::GetFrameTime;
    using ::GetKeyPressed;
    using ::InitWindow;
    using ::IsKeyDown;
    using ::IsKeyPressed;
    using ::SetTargetFPS;
    using ::WindowShouldClose;

    // --- Math ---
    using ::Vector3Add;
    using ::Vector3CrossProduct;
    using ::Vector3DotProduct;
    using ::Vector3Length;
    using ::Vector3Normalize;
    using ::Vector3Scale;
    using ::Vector3Subtract;

    // --- Other ---
    using ::GetScreenHeight;
    using ::GetScreenWidth;
    using ::SetWindowTitle;
}
