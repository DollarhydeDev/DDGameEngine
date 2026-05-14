#include "DDInputSystem.h"

DDInputSystem::DDInputSystem()
{
    for (int i = 0; i < DD_KEY_COUNT; i++)
    {
        _keysDown[i] = false;
        _keysPressed[i] = false;
        _keysReleased[i] = false;
    }
}

DDInputSystem::~DDInputSystem()
{}

bool DDInputSystem::IsValidKey(DDKey key) const
{
    return key > DD_KEY_UNKNOWN && key < DD_KEY_COUNT;
}

void DDInputSystem::BeginFrame()
{
    for (int i = 0; i < DD_KEY_COUNT; i++)
    {
        _keysPressed[i] = false;
        _keysReleased[i] = false;
    }
}

void DDInputSystem::ProcessEvent(const DDPlatformEvent& event)
{
    if (!IsValidKey(event.key)) return;

    int keyIndex = (int)event.key;

    switch (event.type)
    {
    case DDPlatformEvent::DD_EVENT_KEY_DOWN:
        if (!_keysDown[keyIndex]) _keysPressed[keyIndex] = true;
        _keysDown[keyIndex] = true;
        break;

    case DDPlatformEvent::DD_EVENT_KEY_UP:
        _keysReleased[keyIndex] = true;
        _keysDown[keyIndex] = false;
        break;

    default:
        break;
    }
}

bool DDInputSystem::IsKeyDown(DDKey key) const
{
    if (!IsValidKey(key)) return false;
    return _keysDown[(int)key];
}

bool DDInputSystem::WasKeyPressed(DDKey key) const
{
    if (!IsValidKey(key)) return false;
    return _keysPressed[(int)key];
}

bool DDInputSystem::WasKeyReleased(DDKey key) const
{
    if (!IsValidKey(key)) return false;
    return _keysReleased[(int)key];
}