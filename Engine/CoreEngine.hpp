#pragma once
#include <string>
#include <vector>
#include <memory>
#include "RaylibWrapper.hpp"
#include <unordered_map>
#include <functional> // std::hash
#include <type_traits>
#include <typeindex>
#include "ResourceManagement/ResourcesService.hpp"

namespace Core
{
#pragma region RESOURCE MANAGEMENT

#pragma endregion

#pragma region ENTITY COMPONENT SCENE SYSTEM
    class Entity;
    class Component;
    class Scene;

    /// @brief Base class for all components that can be added to an Entity.
    class Component
    {
    public:
        /// @brief Will be called by Entity.AddComponent
        void SetEntity(Core::Entity *entity) { _entity = entity; }
        Core::Entity *GetEntity() { return _entity; }

        void EntityEnable() { OnEntityEnable(); };
        void EntityDisable() { OnEntityDisable(); };
        void Enable() { OnEnable(); };
        void Disable() { OnDisable(); };
        void Update() { OnUpdate(); };
        void Draw3D() { OnDraw3D(); };
        void Draw2D() { OnDraw2D(); };

    private:
        Core::Entity *_entity;

        virtual void OnUpdate() {}
        virtual void OnDraw3D() {}
        virtual void OnDraw2D() {}
        virtual void OnEntityDisable() {}
        virtual void OnEntityEnable() {}
        virtual void OnEnable() {};
        virtual void OnDisable() {};
    };

    /// @brief Game Entity that holds components which get updates based on the Entities state.
    class Entity
    {
    public:
        std::string Name;

        Entity(std::shared_ptr<Core::Scene> scene);
        ~Entity();

        void Enable();
        void Disable();
        void Update();
        void Draw3D();
        void Draw2D();

        void SetEnabled(bool enabled);
        bool IsEnabled() const;
        int GetId() const { return _id; }
        // Returns the scene this entity belongs to. May return a nullptr if the scene has been destroyed!
        std::shared_ptr<Core::Scene> GetScene() const { return _scene.lock(); }

        // TODO: ADD und GET in tpp file ?
        template <typename T, typename... Args>
        std::shared_ptr<T> AddComponent(Args &&...args)
        {
            static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

            auto component = std::make_shared<T>(std::forward<Args>(args)...);
            component->SetEntity(this);
            _components[typeid(T)] = std::static_pointer_cast<Component>(component);
            return component;
        }

        template <typename T>
        std::shared_ptr<T> GetComponent() // TODO: TryGet anstatt nen nullpointer ?
        {
            auto it = _components.find(typeid(T));
            if (it != _components.end())
                return std::dynamic_pointer_cast<T>(it->second);
            return nullptr;
        }

    private:
        bool _enabled;
        unsigned int _id;
        static unsigned int _nextId;
        std::weak_ptr<Core::Scene> _scene; // The scene this entity belongs to
        std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;

        virtual void OnEnable() {};
        virtual void OnDisable() {};
        virtual void OnUpdate() {};
    };

    /// @brief Right now a scene is just a Container for Entities.
    class Scene : public std::enable_shared_from_this<Scene>
    {
    public:
        Scene();
        ~Scene();

        std::shared_ptr<Core::Entity> CreateEntity();
        void RemoveEntity(int entityId);

        /// @brief Updates the Scene and all its Entities. Call this in your main game loop.
        void Update();
        void Draw3D();
        void Draw2D();

        void Enable();
        void Disable();

    private:
        std::unordered_map<int, std::shared_ptr<Core::Entity>> _entities;

        /// @brief Will be called every frame as long as this entity is enabled.
        /// Override this in your custom Scene class. OnUpdate is called before all entities get updated.
        // virtual void OnUpdate() {};
        // virtual void OnDraw() {};
    };

    class SceneManager
    {
    public:
        /// @brief Creates a new scene with the given name or returns an existing one if it already exists.
        static std::shared_ptr<Core::Scene> CreateScene(std::string name);

        /// @brief Updates all registered scenes. Call this in your main game loop.
        static void Update();
        static void Shutdown() { _scenes.clear(); };

        /// @brief Returns all loaded scenes.
        static const std::unordered_map<std::string, std::shared_ptr<Core::Scene>> &GetScenes()
        {
            return _scenes;
        }

    private:
        static std::unordered_map<std::string, std::shared_ptr<Core::Scene>> _scenes;
    };

#pragma endregion

#pragma region COMPONENTS

    class Transform : public Component
    {
    public:
        Transform();
        ~Transform();

        void SetPosition(const Vector3 &position) { _raylibTransform.translation = position; }
        Vector3 GetPosition() const { return _raylibTransform.translation; }

        void SetEulerAngles(const Vector3 &eulerAngles) { _raylibTransform.rotation = QuaternionFromEuler(eulerAngles.z, eulerAngles.y, eulerAngles.x); }
        Vector3 GetEulerAngles() const { return QuaternionToEuler(_raylibTransform.rotation); }

        void SetScale(const Vector3 &scale) { _raylibTransform.scale = scale; }
        Vector3 GetScale() const { return _raylibTransform.scale; }

        void SetRotation(Quaternion rotation) { _raylibTransform.rotation = rotation; }
        Quaternion GetRotation() { return _raylibTransform.rotation; }

        Vector3 GetForward() const;
        Vector3 GetUp() const;
        Vector3 GetRight() const;

        Quaternion LookRotation(Vector3 direction, Vector3 up = {0, 1, 0});
        void LookAt(Vector3 position);

    private:
        ::Transform _raylibTransform;
    };

    class Camera : public Component
    {

    public:
        enum ProjectionType
        {
            CAMERA_PERSPECTIVE = 0,
            CAMERA_ORTHOGRAPHIC = 1
        };

        Camera();
        ~Camera();

        void Render();
        void SetTarget(Vector3 target);
        void SetUp(Vector3 up);
        void SetFov(float fov);
        void SetProjection(ProjectionType projection);
        std::shared_ptr<RenderTexture> GetRenderTexture() const { return _renderTexture; }

        Vector3 GetPosition();
        Vector3 GetTarget();
        Vector3 GetUp();
        float GetFov();
        ProjectionType GetProjection();

    private:
        std::shared_ptr<::Camera> _raylibCamera; // Make sure we can use this camera in raylib functions
        std::shared_ptr<RenderTexture> _renderTexture;

        void OnUpdate() override;
    };

    class MeshRenderer : public Component
    {
    public:
        MeshRenderer();
        ~MeshRenderer();
        void SetModel(std::string filePath);
        void SetAlphaThreshold(int materialIndex, float threshold);
        void SetShader(const int materialIndex, std::string vertexShaderPath, std::string fragmentShaderPath);
        void SetBackfaceCulling(bool cull);
        void SetTexture(const int materialIndex, std::string texturePath);
        void SetTexture(const int materialIndex, std::string textureParameter, std::string texturePath);

        void OnEntityEnable() override;
        void OnEntityDisable() override;
        //        void OnUpdate() override;
        void OnDraw3D() override;

    private:
        std::shared_ptr<Model> _model;
        bool _backfaceCulling = true;
        std::shared_ptr<Core::Transform> _transform;
        bool _cullBackfaces = true;
        bool _valid; // will be false if theres no Model set.
    };

    class TextRenderer : public Component
    {
    public:
        TextRenderer();
        ~TextRenderer();
        void SetText(const std::string text) { _text = text; }
        void SetFontSize(int fontSize) { _fontSize = fontSize; }
        void SetColor(Color color) { _color = color; }
        void SetPosition(int x, int y) { _position = {(float)x, (float)y}; }
        void SetFont(std::string fontPath);

    private:
        void OnDraw2D() override;

        std::string _text;
        int _fontSize;
        Color _color;
        Vector2 _position;
        Font _font;
    };

#pragma endregion
}