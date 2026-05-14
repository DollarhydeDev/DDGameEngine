#pragma once

#include "DDGameWorld.h"
#include "DDRenderSystem.h"
#include "DDInputSystem.h"

class IDDPlatform;
class IDDRenderer;

class DDGameEngine
{
private:
    IDDPlatform* _platform;
    IDDRenderer* _renderer;

    DDGameWorld _gameWorld;
    DDRenderSystem _renderSystem;
    DDInputSystem _inputSystem;

    bool _isRunning;

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