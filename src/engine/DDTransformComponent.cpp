#include "DDTransformComponent.h"

DDTransformComponent::DDTransformComponent() : _position{}, _scale{}
{}

const DDVector2& DDTransformComponent::GetPosition() const
{
    return _position;
}

void DDTransformComponent::SetPosition(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

const DDVector2& DDTransformComponent::GetScale() const
{
    return _scale;
}

void DDTransformComponent::SetScale(float x, float y)
{
    _scale.x = x;
    _scale.y = y;
}