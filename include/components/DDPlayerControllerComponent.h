#pragma once

#include "DDComponent.h"

class DDPlayerControllerComponent : public DDComponent
{
public:
    DDPlayerControllerComponent();

    void Update(float deltaTime) override;
};