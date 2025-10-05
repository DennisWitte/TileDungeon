#include "CoreEngine.hpp"
#include "../raylib/src/rlgl.h"

namespace Core
{
    MeshRenderer::MeshRenderer()
    {
    }
    MeshRenderer::~MeshRenderer()
    {
    }

    void MeshRenderer::OnEntityEnable()
    {
        _transform = Component::GetEntity()->GetComponent<Transform>();
    }

    void MeshRenderer::OnEntityDisable()
    {
    }

    void MeshRenderer::SetModel(std::string filePath)
    {
        if (ResourcesController<Model>::TryGet(filePath, _model))
        {
            _valid = true;
        }
        else
        {
            _valid = false;
        }
    }

    /// @brief Sets a custom shader for a specific material index of the model.
    /// @param materialIndex
    /// @param shaderVertPath
    /// @param shaderFragPath
    void MeshRenderer::SetShader(const int materialIndex, std::string vertexShaderPath, std::string fragmentShaderPath)
    {
        std::shared_ptr<Shader> shader;
        std::string id = vertexShaderPath + fragmentShaderPath;
        if (!ResourcesService::TryGet<Shader>(id, shader))
        {
            return;
        }

        // TODO: Checken ob auch ein korrekter Vert / Frag shader vorliegt. Ansonsten SEG FAULT
        if (materialIndex < 0 || materialIndex >= _model->materialCount)
        {
            printf("ERROR: Material index out of range\n");
            return;
        }
        _model->materials[materialIndex].shader = *shader;
    }
    /// @brief Set the alpha threshold for shaders with alpha cutout.
    /// @param threshold
    void MeshRenderer::SetAlphaThreshold(int materialIndex, float threshold)
    {
        if (materialIndex < 0 || materialIndex >= _model->materialCount)
        {
            printf("ERROR: Material index out of range\n");
            return;
        }
        int locThreshold = GetShaderLocation(_model->materials[materialIndex].shader, "alphaThreshold");
        SetShaderValue(_model->materials[materialIndex].shader, locThreshold, &threshold, SHADER_UNIFORM_FLOAT);
    }

    void MeshRenderer::SetBackfaceCulling(bool cull) { _backfaceCulling = cull; }

    void MeshRenderer::SetTexture(int materialIndex, std::string texturePath)
    {
        if (materialIndex < 0 || materialIndex >= _model->materialCount)
        {
            printf("ERROR: Material index out of range\n");
            return;
        }

        std::shared_ptr<Texture> texture;
        if (ResourcesService::TryGet<Texture>("../Resources/JungleGround.png", texture))
        {
            _model->materials[materialIndex].maps[MATERIAL_MAP_DIFFUSE].texture = *texture;
        }
    }

    void MeshRenderer::OnUpdate()
    {
        if (!_valid)
            return;

        if (!_model)
        {
            printf("FEHLER: _model ist NULL!\n");
            return;
        }

        if (_model->meshCount == 0)
        {
            printf("FEHLER: _model hat keine Meshes!\n");
            return;
        }

        // TODO: Unperformant but works for now
        if (_backfaceCulling)
            rlEnableBackfaceCulling();
        else
            rlDisableBackfaceCulling();

        DrawModelEx(*_model, _transform->GetPosition(), {0, 1, 0}, 0, _transform->GetScale(), WHITE);

        if (!_backfaceCulling)
            rlEnableBackfaceCulling();
        else
            rlDisableBackfaceCulling();
        }
}