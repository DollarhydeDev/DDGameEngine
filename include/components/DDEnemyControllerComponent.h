#pragma once

#include "DDComponent.h"

class DDGameObject;

class DDEnemyControllerComponent : public DDComponent
{
private:
    DDGameObject* _target;

public:
    DDEnemyControllerComponent();

    void SetTarget(DDGameObject* target);
    DDGameObject* GetTarget() const;

    void Update(float deltaTime) override;
};