#pragma once

#include "DDList.h"
#include "DDGameObject.h"
#include "DDComponent.h"
#include "DDTransformComponent.h"
#include "DDRenderComponent.h"

class DDGameEngine;

class DDGameWorld
{
private:
    DDGameEngine* _gameEngine;

    int _nextGameObjectID;
    int _nextComponentID;

    DDList<DDGameObject> _worldGameObjects;
    DDList<DDComponent> _worldComponents;
    DDList<DDTransformComponent> _transformComponents;
    DDList<DDRenderComponent> _renderComponents;

public:
    const DDList<DDGameObject>& GetWorldGameObjects() const;
    const DDList<DDComponent>& GetWorldComponents() const;
    const DDList<DDTransformComponent>& GetTransformComponents() const;
    const DDList<DDRenderComponent>& GetRenderComponents() const;

    DDGameObject* SpawnGameObject();
    DDGameObject* SpawnGameObject(float scaleX, float scaleY, float posX, float posY);

    DDTransformComponent* SpawnTransformComponent(DDGameObject* owner);
    DDRenderComponent* SpawnRenderComponent(DDGameObject* owner);

public:
    DDGameWorld(DDGameEngine* gameEngine);
    ~DDGameWorld();

    void Start();
    void Update(float deltaTime);
};