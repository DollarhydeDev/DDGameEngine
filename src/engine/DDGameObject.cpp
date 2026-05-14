#include "DDGameObject.h"

DDGameObject::DDGameObject() : _gameObjectID{ -1 }, _world{ nullptr }, _transform{ nullptr }, _render{ nullptr }
{}

DDGameObject::DDGameObject(int gameObjectID, DDGameWorld* world) : _gameObjectID{ gameObjectID }, _world{ world }, _transform{ nullptr }, _render{ nullptr }
{}

int DDGameObject::GetGameObjectID() const
{
    return _gameObjectID;
}

DDGameWorld* DDGameObject::GetWorld() const
{
    return _world;
}

DDTransformComponent* DDGameObject::GetTransform() const
{
    return _transform;
}

void DDGameObject::SetTransform(DDTransformComponent* transform)
{
    _transform = transform;
}

DDRenderComponent* DDGameObject::GetRender() const
{
    return _render;
}

void DDGameObject::SetRender(DDRenderComponent* render)
{
    _render = render;
}

void DDGameObject::Start()
{}

void DDGameObject::Update(float deltaTime)
{}