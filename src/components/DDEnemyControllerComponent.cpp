#include "DDEnemyControllerComponent.h"

#include <cmath>

#include "DDGameObject.h"
#include "DDGameWorld.h"
#include "DDMovementComponent.h"
#include "DDTransformComponent.h"
#include "DDVector2.h"

DDEnemyControllerComponent::DDEnemyControllerComponent() : _target{ nullptr }
{}

void DDEnemyControllerComponent::SetTarget(DDGameObject* target)
{
    _target = target;
}

DDGameObject* DDEnemyControllerComponent::GetTarget() const
{
    return _target;
}

void DDEnemyControllerComponent::Update(float deltaTime)
{
    DDGameObject* owner = GetOwner();
    if (!owner) return;

    DDGameObject* target = _target;

    if (!target)
    {
        DDGameWorld* world = owner->GetWorld();
        if (!world) return;

        target = world->GetPlayer();
        if (!target) return;
    }

    DDTransformComponent* ownerTransform = owner->GetTransform();
    DDTransformComponent* targetTransform = target->GetTransform();
    DDMovementComponent* movement = owner->GetMovement();

    if (!ownerTransform) return;
    if (!targetTransform) return;
    if (!movement) return;

    const DDVector2& ownerPosition = ownerTransform->GetPosition();
    const DDVector2& targetPosition = targetTransform->GetPosition();

    float x = targetPosition.x - ownerPosition.x;
    float y = targetPosition.y - ownerPosition.y;

    float length = sqrtf(x * x + y * y);

    if (length > 0.0001f)
    {
        x /= length;
        y /= length;
    }
    else
    {
        x = 0.0f;
        y = 0.0f;
    }

    movement->SetVelocity(x, y);
}