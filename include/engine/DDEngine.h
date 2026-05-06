#pragma once

#include "DDList.h"
#include "DDRenderer.h"
#include "DDGameObject.h"


class DDEngine
{
    private:
    DDRenderer _renderer;
    DDList<DDGameObject> _gameObjects;
    bool _isRunning;

    public:
    DDEngine();
    ~DDEngine();

    int Init();
    void Run();
    void Shutdown();
};
