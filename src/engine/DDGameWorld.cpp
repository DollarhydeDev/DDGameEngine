#include <cstdlib>

#include "DDGameWorld.h"

#include "DDGameEngine.h"
#include "DDInputSystem.h"
#include "DDGameObject.h"
#include "DDComponent.h"
#include "DDTransformComponent.h"
#include "DDRenderComponent.h"
#include "DDMovementComponent.h"
#include "DDPlayerControllerComponent.h"
#include "DDEnemyControllerComponent.h"

DDGameWorld::DDGameWorld(DDGameEngine* gameEngine) : _gameEngine{ gameEngine }, _nextGameObjectID{ 0 }, _nextComponentID{ 0 }, _player{ nullptr }, _worldGameObjects{}, _worldComponents{}, _transformComponents{}, _renderComponents{}, _movementComponents{}, _playerControllerComponents{}, _enemyControllerComponents{}
{}

DDGameWorld::~DDGameWorld()
{
    for (int i = 0; i < _worldComponents.Size(); i++) delete _worldComponents.GetAt(i);
    _worldComponents.Clear();

    _transformComponents.Clear();
    _renderComponents.Clear();
    _movementComponents.Clear();
    _playerControllerComponents.Clear();
    _enemyControllerComponents.Clear();

    for (int i = 0; i < _worldGameObjects.Size(); i++) delete _worldGameObjects.GetAt(i);
    _worldGameObjects.Clear();

    _player = nullptr;
}

DDInputSystem* DDGameWorld::GetInputSystem() const
{
    return _gameEngine ? _gameEngine->GetInputSystem() : nullptr;
}

DDGameObject* DDGameWorld::GetPlayer() const
{
    return _player;
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

const DDList<DDMovementComponent>& DDGameWorld::GetMovementComponents() const
{
    return _movementComponents;
}

const DDList<DDPlayerControllerComponent>& DDGameWorld::GetPlayerControllerComponents() const
{
    return _playerControllerComponents;
}

const DDList<DDEnemyControllerComponent>& DDGameWorld::GetEnemyControllerComponents() const
{
    return _enemyControllerComponents;
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

DDGameObject* DDGameWorld::SpawnPlayer(float posX, float posY)
{
    DDGameObject* player = SpawnGameObject();

    DDTransformComponent* transform = SpawnTransformComponent(player);
    transform->SetScale(10.0f, 10.0f);
    transform->SetPosition(posX, posY);

    SpawnRenderComponent(player);

    DDMovementComponent* movement = SpawnMovementComponent(player);
    movement->SetSpeed(500.0f);

    SpawnPlayerControllerComponent(player);

    _player = player;

    return player;
}

DDGameObject* DDGameWorld::SpawnEnemy(float posX, float posY)
{
    DDGameObject* enemy = SpawnGameObject();

    DDTransformComponent* transform = SpawnTransformComponent(enemy);
    transform->SetScale(10.0f, 10.0f);
    transform->SetPosition(posX, posY);

    SpawnRenderComponent(enemy);

    DDMovementComponent* movement = SpawnMovementComponent(enemy);
    movement->SetSpeed(100.0f);

    DDEnemyControllerComponent* controller = SpawnEnemyControllerComponent(enemy);
    controller->SetTarget(_player);

    return enemy;
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

DDMovementComponent* DDGameWorld::SpawnMovementComponent(DDGameObject* owner)
{
    if (!owner) return nullptr;

    DDMovementComponent* component = new DDMovementComponent();
    component->SetComponentID(_nextComponentID++);
    component->SetOwner(owner);

    _worldComponents.Add(component);
    _movementComponents.Add(component);

    owner->SetMovement(component);

    return component;
}

DDPlayerControllerComponent* DDGameWorld::SpawnPlayerControllerComponent(DDGameObject* owner)
{
    if (!owner) return nullptr;

    DDPlayerControllerComponent* component = new DDPlayerControllerComponent();
    component->SetComponentID(_nextComponentID++);
    component->SetOwner(owner);

    _worldComponents.Add(component);
    _playerControllerComponents.Add(component);

    return component;
}

DDEnemyControllerComponent* DDGameWorld::SpawnEnemyControllerComponent(DDGameObject* owner)
{
    if (!owner) return nullptr;

    DDEnemyControllerComponent* component = new DDEnemyControllerComponent();
    component->SetComponentID(_nextComponentID++);
    component->SetOwner(owner);

    _worldComponents.Add(component);
    _enemyControllerComponents.Add(component);

    return component;
}

void DDGameWorld::Start()
{
    SpawnPlayer(300.0f, 180.0f);

    srand(12345);

    for (int i = 0; i < 6000; i++)
    {
        float x = (float)(-2000 + rand() % 4000);
        float y = (float)(-1000 + rand() % 2000);

        SpawnEnemy(x, y);
    }

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