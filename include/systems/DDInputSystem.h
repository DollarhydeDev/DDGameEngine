#pragma once

#include "DDKey.h"
#include "DDPlatformEvent.h"

class DDInputSystem
{
private:
    bool _keysDown[DD_KEY_COUNT];
    bool _keysPressed[DD_KEY_COUNT];
    bool _keysReleased[DD_KEY_COUNT];

private:
    bool IsValidKey(DDKey key) const;

public:
    DDInputSystem();
    ~DDInputSystem();

    void BeginFrame();
    void ProcessEvent(const DDPlatformEvent& event);

    bool IsKeyDown(DDKey key) const;
    bool WasKeyPressed(DDKey key) const;
    bool WasKeyReleased(DDKey key) const;
};