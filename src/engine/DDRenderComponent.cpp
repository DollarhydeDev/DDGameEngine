#include "DDRenderComponent.h"

DDRenderComponent::DDRenderComponent() : _visible{ true }
{}

bool DDRenderComponent::IsVisible() const
{
    return _visible;
}

void DDRenderComponent::SetVisible(bool visible)
{
    _visible = visible;
}