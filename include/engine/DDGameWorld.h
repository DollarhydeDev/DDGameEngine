#pragma once

#include "DDList.h"
#include "DDGameObject.h"
#include "DDComponent.h"
#include "DDTransformComponent.h"
#include "DDRenderComponent.h"
#include "DDMovementComponent.h"
#include "DDPlayerControllerComponent.h"
#include "DDEnemyControllerComponent.h"

class DDGameEngine;
class DDInputSystem;

class DDGameWorld
{
private:
    DDGameEngine* _gameEngine;

    int _nextGameObjectID;
    int _nextComponentID;

    DDGameObject* _player;

    DDList<DDGameObject> _worldGameObjects;
    DDList<DDComponent> _worldComponents;
    DDList<DDTransformComponent> _transformComponents;
    DDList<DDRenderComponent> _renderComponents;
    DDList<DDMovementComponent> _movementComponents;
    DDList<DDPlayerControllerComponent> _playerControllerComponents;
    DDList<DDEnemyControllerComponent> _enemyControllerComponents;

public:
    DDInputSystem* GetInputSystem() const;
    DDGameObject* GetPlayer() const;

    const DDList<DDGameObject>& GetWorldGameObjects() const;
    const DDList<DDComponent>& GetWorldComponents() const;
    const DDList<DDTransformComponent>& GetTransformComponents() const;
    const DDList<DDRenderComponent>& GetRenderComponents() const;
    const DDList<DDMovementComponent>& GetMovementComponents() const;
    const DDList<DDPlayerControllerComponent>& GetPlayerControllerComponents() const;
    const DDList<DDEnemyControllerComponent>& GetEnemyControllerComponents() const;

    DDGameObject* SpawnGameObject();
    DDGameObject* SpawnGameObject(float scaleX, float scaleY, float posX, float posY);

    DDGameObject* SpawnPlayer(float posX, float posY);
    DDGameObject* SpawnEnemy(float posX, float posY);

    DDTransformComponent* SpawnTransformComponent(DDGameObject* owner);
    DDRenderComponent* SpawnRenderComponent(DDGameObject* owner);
    DDMovementComponent* SpawnMovementComponent(DDGameObject* owner);
    DDPlayerControllerComponent* SpawnPlayerControllerComponent(DDGameObject* owner);
    DDEnemyControllerComponent* SpawnEnemyControllerComponent(DDGameObject* owner);

public:
    DDGameWorld(DDGameEngine* gameEngine);
    ~DDGameWorld();

    void Start();
    void Update(float deltaTime);
};