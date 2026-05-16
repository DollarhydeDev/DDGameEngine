#pragma once

class DDGameWorld;
class DDTransformComponent;
class DDRenderComponent;
class DDMovementComponent;

class DDGameObject
{
private:
    int _gameObjectID;
    DDGameWorld* _world;

    DDTransformComponent* _transform;
    DDRenderComponent* _render;
    DDMovementComponent* _movement;

public:
    int GetGameObjectID() const;
    DDGameWorld* GetWorld() const;

    DDTransformComponent* GetTransform() const;
    void SetTransform(DDTransformComponent* transform);

    DDRenderComponent* GetRender() const;
    void SetRender(DDRenderComponent* render);

    DDMovementComponent* GetMovement() const;
    void SetMovement(DDMovementComponent* movement);

public:
    DDGameObject();
    DDGameObject(int gameObjectID, DDGameWorld* world);

    void Start();
    void Update(float deltaTime);
};