#pragma once

#include "time.h"

#include "DDList.h"
#include "DDRenderer.h"
#include "DDGameWorld.h"
#include "DDGameObject.h"

class DDGameEngine
{
    private:
    DDRenderer _renderer;
    DDGameWorld _gameWorld;
    timespec _lastTime;
    bool _isRunning;

    // Need to move this to some sort of input handler later
    bool _upPressed = false;
    bool _downPressed = false;
    bool _leftPressed = false;
    bool _rightPressed = false;

    float GetDeltaTime();

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
