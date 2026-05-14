#include "DDRenderSystem.h"

#include "DDGameWorld.h"
#include "IDDRenderer.h"
#include "DDList.h"
#include "DDGameObject.h"
#include "DDRenderComponent.h"
#include "DDTransformComponent.h"
#include "DDVector2.h"

DDRenderSystem::DDRenderSystem()
{}

DDRenderSystem::~DDRenderSystem()
{}

void DDRenderSystem::Render(DDGameWorld* world, IDDRenderer* renderer)
{
    if (!world) return;
    if (!renderer) return;

    renderer->BeginFrame();

    const DDList<DDRenderComponent>& renderComponents = world->GetRenderComponents();

    for (int i = 0; i < renderComponents.Size(); i++)
    {
        DDRenderComponent* renderComponent = renderComponents.GetAt(i);
        if (!renderComponent) continue;
        if (!renderComponent->IsEnabled()) continue;
        if (!renderComponent->IsVisible()) continue;

        DDGameObject* owner = renderComponent->GetOwner();
        if (!owner) continue;

        DDTransformComponent* transform = owner->GetTransform();
        if (!transform) continue;
        if (!transform->IsEnabled()) continue;

        const DDVector2& position = transform->GetPosition();
        const DDVector2& scale = transform->GetScale();

        renderer->DrawRect2D(position.x, position.y, scale.x, scale.y);
    }

    renderer->EndFrame();
}