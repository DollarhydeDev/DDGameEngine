#include "DDPlayerControllerComponent.h"

#include "DDGameObject.h"
#include "DDGameWorld.h"
#include "DDInputSystem.h"
#include "DDMovementComponent.h"

DDPlayerControllerComponent::DDPlayerControllerComponent()
{}

void DDPlayerControllerComponent::Update(float deltaTime)
{
    DDGameObject* owner = GetOwner();
    if (!owner) return;

    DDGameWorld* world = owner->GetWorld();
    if (!world) return;

    DDInputSystem* input = world->GetInputSystem();
    if (!input) return;

    DDMovementComponent* movement = owner->GetMovement();
    if (!movement) return;

    float x = 0.0f;
    float y = 0.0f;

    if (input->IsKeyDown(DD_KEY_W)) y -= 1.0f;
    if (input->IsKeyDown(DD_KEY_S)) y += 1.0f;
    if (input->IsKeyDown(DD_KEY_A)) x -= 1.0f;
    if (input->IsKeyDown(DD_KEY_D)) x += 1.0f;

    movement->SetVelocity(x, y);
}