#include "DDGameWorld.h"

#include "DDGameObject.h"
#include "DDComponent.h"
#include "DDTransformComponent.h"
#include "DDRenderComponent.h"

DDGameWorld::DDGameWorld(DDGameEngine* gameEngine) : _gameEngine{ gameEngine }, _nextGameObjectID{ 0 }, _nextComponentID{ 0 }, _worldGameObjects{}, _worldComponents{}, _transformComponents{}, _renderComponents{}
{}

DDGameWorld::~DDGameWorld()
{
    for (int i = 0; i < _worldComponents.Size(); i++) delete _worldComponents.GetAt(i);
    _worldComponents.Clear();

    _transformComponents.Clear();
    _renderComponents.Clear();

    for (int i = 0; i < _worldGameObjects.Size(); i++) delete _worldGameObjects.GetAt(i);
    _worldGameObjects.Clear();
}

const DDList<DDGameObject>& DDGameWorld::GetWorldGameObjects() const
{
    return _worldGameObjects;
}

const DDList<DDComponent>& DDGameWorld::GetWorldComponents() const
{
    return _worldComponents;
}

const DDList<DDTransformComponent>& DDGameWorld::GetTransformComponents() const
{
    return _transformComponents;
}

const DDList<DDRenderComponent>& DDGameWorld::GetRenderComponents() const
{
    return _renderComponents;
}

DDGameObject* DDGameWorld::SpawnGameObject()
{
    DDGameObject* gameObject = new DDGameObject(_nextGameObjectID++, this);
    _worldGameObjects.Add(gameObject);
    return gameObject;
}

DDGameObject* DDGameWorld::SpawnGameObject(float scaleX, float scaleY, float posX, float posY)
{
    DDGameObject* gameObject = SpawnGameObject();

    DDTransformComponent* transform = SpawnTransformComponent(gameObject);
    transform->SetScale(scaleX, scaleY);
    transform->SetPosition(posX, posY);

    SpawnRenderComponent(gameObject);

    return gameObject;
}

DDTransformComponent* DDGameWorld::SpawnTransformComponent(DDGameObject* owner)
{
    if (!owner) return nullptr;

    DDTransformComponent* component = new DDTransformComponent();
    component->SetComponentID(_nextComponentID++);
    component->SetOwner(owner);

    _worldComponents.Add(component);
    _transformComponents.Add(component);

    owner->SetTransform(component);

    return component;
}

DDRenderComponent* DDGameWorld::SpawnRenderComponent(DDGameObject* owner)
{
    if (!owner) return nullptr;

    DDRenderComponent* component = new DDRenderComponent();
    component->SetComponentID(_nextComponentID++);
    component->SetOwner(owner);

    _worldComponents.Add(component);
    _renderComponents.Add(component);

    owner->SetRender(component);

    return component;
}

void DDGameWorld::Init()
{
    for (int i = 0; i < _worldGameObjects.Size(); i++) _worldGameObjects.GetAt(i)->Init();
    for (int i = 0; i < _worldComponents.Size(); i++) _worldComponents.GetAt(i)->Init();
}

void DDGameWorld::Start()
{
    SpawnGameObject(20.0f, 20.0f, 300.0f, 180.0f);

    for (int i = 0; i < _worldGameObjects.Size(); i++) _worldGameObjects.GetAt(i)->Start();
    for (int i = 0; i < _worldComponents.Size(); i++) _worldComponents.GetAt(i)->Start();
}

void DDGameWorld::Update(float deltaTime)
{
    for (int i = 0; i < _worldGameObjects.Size(); i++) _worldGameObjects.GetAt(i)->Update(deltaTime);

    for (int i = 0; i < _worldComponents.Size(); i++)
    {
        DDComponent* component = _worldComponents.GetAt(i);
        if (!component->IsEnabled()) continue;
        component->Update(deltaTime);
    }
}