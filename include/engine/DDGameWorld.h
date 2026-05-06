#pragma once

// Includes
#include "DDList.h"
#include "DDGameObject.h"

// Forward declares
class DDGameEngine;

class DDGameWorld
{
    private:
    DDGameEngine* _gameEngine;
    DDList<DDGameObject> _worldGameObjects;

    public:
    const DDList<DDGameObject>& GetWorldGameObjects() const;

    public:
    DDGameWorld(DDGameEngine* gameEngine);
    ~DDGameWorld();

    void Init();
    void Start();
    void Update(float deltaTime);
};
