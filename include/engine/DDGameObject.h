#pragma once

class DDGameWorld;
class DDTransformComponent;
class DDRenderComponent;

class DDGameObject
{
private:
    int _gameObjectID;
    DDGameWorld* _world;

    DDTransformComponent* _transform;
    DDRenderComponent* _render;

public:
    int GetGameObjectID() const;
    DDGameWorld* GetWorld() const;

    DDTransformComponent* GetTransform() const;
    void SetTransform(DDTransformComponent* transform);

    DDRenderComponent* GetRender() const;
    void SetRender(DDRenderComponent* render);

public:
    DDGameObject();
    DDGameObject(int gameObjectID, DDGameWorld* world);

    void Init();
    void Start();
    void Update(float deltaTime);
};