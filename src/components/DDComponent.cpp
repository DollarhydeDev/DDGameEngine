#include "DDComponent.h"
#include "DDGameObject.h"

DDComponent::DDComponent() : _componentID{ -1 }, _ownerID{ -1 }, _owner{ nullptr }, _enabled{ true }
{}

int DDComponent::GetComponentID() const
{
    return _componentID;
}

int DDComponent::GetOwnerID() const
{
    return _ownerID;
}

DDGameObject* DDComponent::GetOwner() const
{
    return _owner;
}

bool DDComponent::IsEnabled() const
{
    return _enabled;
}

void DDComponent::SetEnabled(bool enabled)
{
    _enabled = enabled;
}

void DDComponent::SetComponentID(int componentID)
{
    _componentID = componentID;
}

void DDComponent::SetOwner(DDGameObject* owner)
{
    _owner = owner;
    _ownerID = owner ? owner->GetGameObjectID() : -1;
}

void DDComponent::Start()
{}

void DDComponent::Update(float deltaTime)
{}