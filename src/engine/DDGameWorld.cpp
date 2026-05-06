#include "DDGameWorld.h"
#include "DDList.h"
#include "DDGameObject.h"

DDGameWorld::DDGameWorld(DDGameEngine* gameEngine) : _gameEngine{gameEngine}, _worldGameObjects{} {}
DDGameWorld::~DDGameWorld()
{
    for (int i = 0; i < _worldGameObjects.Size(); ++i)
    {
        delete _worldGameObjects.GetAt(i);
    }

    _worldGameObjects.Clear();
}

const DDList<DDGameObject>& DDGameWorld::GetWorldGameObjects() const
{
    return _worldGameObjects;
}

void DDGameWorld::Init()
{
    for (int i = 0; i < _worldGameObjects.Size(); i++)
    {
        _worldGameObjects.GetAt(i)->Init();
    }
}

void DDGameWorld::Start()
{
    // Add player for testing
    DDGameObject* player = new DDGameObject();
    _worldGameObjects.Add(player);

    for (int i = 0; i < _worldGameObjects.Size(); i++)
    {
        _worldGameObjects.GetAt(i)->Start();
    }
}

void DDGameWorld::Update(float deltaTime)
{
    for (int i = 0; i < _worldGameObjects.Size(); i++)
    {
        _worldGameObjects.GetAt(i)->Update(deltaTime);
    }
}
