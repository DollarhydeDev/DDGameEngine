#include "DDGameEngine.h"

#include "IDDPlatform.h"
#include "IDDRenderer.h"
#include "DDGameObject.h"
#include "DDGameWorld.h"

#if defined(_WIN32)
#include "DDPlatformWindows.h"
#include "DDRendererWindows.h"
#elif defined(__linux__)
#include "DDPlatformLinux.h"
#include "DDRendererLinux.h"
#else
#error Unsupported platform
#endif

static IDDPlatform* CreatePlatform()
{
#if defined(_WIN32)
    return new DDPlatformWindows();
#elif defined(__linux__)
    return new DDPlatformLinux();
#else
    return nullptr;
#endif
}

static IDDRenderer* CreateRenderer()
{
#if defined(_WIN32)
    return new DDRendererWindows();
#elif defined(__linux__)
    return new DDRendererLinux();
#else
    return nullptr;
#endif
}

DDGameEngine::DDGameEngine() : _platform{ CreatePlatform() }, _renderer{ CreateRenderer() }, _gameWorld{ this }, _isRunning{ false }
{}

DDGameEngine::~DDGameEngine()
{
    delete _renderer;
    _renderer = nullptr;

    delete _platform;
    _platform = nullptr;
}

void DDGameEngine::Start()
{
    _isRunning = true;
    _gameWorld.Start();
}

void DDGameEngine::Update(float deltaTime)
{
    float playerSpeed = 300.0f;
    float distance = playerSpeed * deltaTime;

    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);

    float x = player->GetPosition().x;
    float y = player->GetPosition().y;

    if (_upPressed) y -= distance;
    if (_downPressed) y += distance;
    if (_leftPressed) x -= distance;
    if (_rightPressed) x += distance;

    player->SetPosition(x, y);

    _gameWorld.Update(deltaTime);
}

void DDGameEngine::Render(float deltaTime)
{
    _renderer->Render(_gameWorld.GetWorldGameObjects(), deltaTime);
}

void DDGameEngine::ProcessEvents()
{
    DDPlatformEvent event{};

    while (_platform->PollEvent(event))
    {
        switch (event.type)
        {
        case DDPlatformEvent::DD_EVENT_QUIT:
            _isRunning = false;
            break;

        case DDPlatformEvent::DD_EVENT_KEY_DOWN:
            if (event.key == DD_KEY_ESCAPE) _isRunning = false;
            if (event.key == DD_KEY_W) _upPressed = true;
            if (event.key == DD_KEY_S) _downPressed = true;
            if (event.key == DD_KEY_A) _leftPressed = true;
            if (event.key == DD_KEY_D) _rightPressed = true;
            break;

        case DDPlatformEvent::DD_EVENT_KEY_UP:
            if (event.key == DD_KEY_W) _upPressed = false;
            if (event.key == DD_KEY_S) _downPressed = false;
            if (event.key == DD_KEY_A) _leftPressed = false;
            if (event.key == DD_KEY_D) _rightPressed = false;
            break;

        case DDPlatformEvent::DD_EVENT_RESIZE:
            _renderer->ResizeWindow(event.width, event.height);
            break;

        default:
            break;
        }
    }
}

int DDGameEngine::Init()
{
    if (!_platform) return -1;
    if (!_renderer) return -1;

    if (_platform->Init(800, 600, "GameWindow") != 0) return -1;
    if (_renderer->Init(_platform) != 0) return -1;

    return 0;
}

void DDGameEngine::Run()
{
    Start();

    while (_isRunning)
    {
        float deltaTime = _platform->GetDeltaTime();

        ProcessEvents();
        Update(deltaTime);
        Render(deltaTime);

        _platform->SleepMilliseconds(8);
    }
}

void DDGameEngine::Shutdown()
{
    if (_renderer) _renderer->Shutdown();
    if (_platform) _platform->Shutdown();
}