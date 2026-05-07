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

    float GetDeltaTime();

    public:
    DDGameEngine();
    ~DDGameEngine();

    private:
    void Start();
    void Update();
    void Render();
    void ProcessEvents();
    
    public:
    int Init();
    void Run();
    void Shutdown();
};
