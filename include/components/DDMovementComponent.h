#pragma once

#include "DDComponent.h"

class DDMovementComponent : public DDComponent
{
private:
    float _velocityX;
    float _velocityY;
    float _speed;

public:
    DDMovementComponent();

    float GetVelocityX() const;
    float GetVelocityY() const;
    float GetSpeed() const;

    void SetVelocity(float x, float y);
    void SetSpeed(float speed);
};