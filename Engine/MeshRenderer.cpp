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
    /// @param materialIndex Use -1 to assign the shader to all materials on this model.
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

        // Standardwerte
        float paletteBits = 5.0f;
        float ditherStrength = 0.5f;
        Vector3 fogColor = {0.5f, 0.5f, 0.6f}; // graublauer Nebel
        float fogStart = 5.0f;
        float fogEnd = 50.0f;

        SetShaderValue(*shader, GetShaderLocation(*shader, "paletteBits"), &paletteBits, SHADER_UNIFORM_FLOAT);
        SetShaderValue(*shader, GetShaderLocation(*shader, "ditherStrength"), &ditherStrength, SHADER_UNIFORM_FLOAT);
        SetShaderValue(*shader, GetShaderLocation(*shader, "fogColor"), &fogColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(*shader, GetShaderLocation(*shader, "fogStart"), &fogStart, SHADER_UNIFORM_FLOAT);
        SetShaderValue(*shader, GetShaderLocation(*shader, "fogEnd"), &fogEnd, SHADER_UNIFORM_FLOAT);

        // TODO: Checken ob auch ein korrekter Vert / Frag shader vorliegt. Ansonsten SEG FAULT
        if (materialIndex > 0 && materialIndex < _model->materialCount)
        {
            _model->materials[materialIndex].shader = *shader;
            return;
        }
        else if (materialIndex < 0)
        {
            for (size_t i = 0; i < _model->materialCount; i++)
            {
                _model->materials[i].shader = *shader;
            }
        }

        printf("ERROR: Material index out of range\n");
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

    void MeshRenderer::SetTexture(const int materialIndex, std::string texturePath)
    {
        if (materialIndex < 0 || materialIndex >= _model->materialCount)
        {
            printf("ERROR: Material index out of range\n");
            return;
        }

        std::shared_ptr<Texture> texture;
        if (ResourcesService::TryGet<Texture>(texturePath, texture))
        {
            _model->materials[materialIndex].maps[MATERIAL_MAP_DIFFUSE].texture = *texture;
        }
    }

    void MeshRenderer::SetTexture(const int materialIndex, std::string textureParameter, std::string texturePath)
    {
        if (materialIndex > 0 && materialIndex < _model->materialCount)
        {
            std::shared_ptr<Texture> texture;
            if (ResourcesService::TryGet<Texture>(texturePath, texture))
            {
                int texLoc = GetShaderLocation(_model->materials[materialIndex].shader, textureParameter.c_str());
                SetShaderValueTexture(_model->materials[materialIndex].shader, texLoc, *texture);
            }
            return;
        }
        else if (materialIndex < 0)
        {
            std::shared_ptr<Texture> texture;
            if (ResourcesService::TryGet<Texture>(texturePath, texture))
            {
                for (size_t i = 0; i < _model->materialCount; i++)
                {
                    int texLoc = GetShaderLocation(_model->materials[i].shader, textureParameter.c_str());
                    SetShaderValueTexture(_model->materials[i].shader, texLoc, *texture);
                }
            }
        }
        else
        {
            printf("ERROR: Material index out of range\n");
        }
    }

    void MeshRenderer::OnDraw()
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

        if (_transform == nullptr)
            return;
        if (_model == nullptr)
            return;

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