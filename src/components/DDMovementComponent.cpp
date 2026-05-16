#include "DDMovementComponent.h"

DDMovementComponent::DDMovementComponent() : _velocityX{ 0.0f }, _velocityY{ 0.0f }, _speed{ 0.0f }
{}

float DDMovementComponent::GetVelocityX() const
{
    return _velocityX;
}

float DDMovementComponent::GetVelocityY() const
{
    return _velocityY;
}

float DDMovementComponent::GetSpeed() const
{
    return _speed;
}

void DDMovementComponent::SetVelocity(float x, float y)
{
    _velocityX = x;
    _velocityY = y;
}

void DDMovementComponent::SetSpeed(float speed)
{
    _speed = speed;
}