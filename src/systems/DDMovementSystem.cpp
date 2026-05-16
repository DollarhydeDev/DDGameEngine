#include "DDMovementSystem.h"

#include "DDGameWorld.h"
#include "DDGameObject.h"
#include "DDMovementComponent.h"
#include "DDTransformComponent.h"
#include "DDVector2.h"
#include "DDList.h"

DDMovementSystem::DDMovementSystem()
{}

DDMovementSystem::~DDMovementSystem()
{}

void DDMovementSystem::Update(DDGameWorld* world, float deltaTime)
{
    if (!world) return;

    const DDList<DDMovementComponent>& movementComponents = world->GetMovementComponents();

    for (int i = 0; i < movementComponents.Size(); i++)
    {
        DDMovementComponent* movement = movementComponents.GetAt(i);
        if (!movement) continue;
        if (!movement->IsEnabled()) continue;

        DDGameObject* owner = movement->GetOwner();
        if (!owner) continue;

        DDTransformComponent* transform = owner->GetTransform();
        if (!transform) continue;
        if (!transform->IsEnabled()) continue;

        const DDVector2& position = transform->GetPosition();

        float x = position.x + movement->GetVelocityX() * movement->GetSpeed() * deltaTime;
        float y = position.y + movement->GetVelocityY() * movement->GetSpeed() * deltaTime;

        transform->SetPosition(x, y);
    }
}