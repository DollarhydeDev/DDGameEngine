#pragma once

#include "DDGameWorld.h"

class IDDPlatform;
class IDDRenderer;

class DDGameEngine
{
private:
    IDDPlatform* _platform;
    IDDRenderer* _renderer;

    DDGameWorld _gameWorld;
    bool _isRunning;

    bool _upPressed = false;
    bool _downPressed = false;
    bool _leftPressed = false;
    bool _rightPressed = false;

public:
    DDGameEngine();
    ~DDGameEngine();

private:
    void Start();
    void Update(float deltaTime);
    void Render(float deltaTime);
    void ProcessEvents();

public:
    int Init();
    void Run();
    void Shutdown();
};