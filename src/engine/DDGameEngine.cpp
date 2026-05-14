#include "DDGameEngine.h"

#include "IDDPlatform.h"
#include "IDDRenderer.h"
#include "DDGameObject.h"
#include "DDGameWorld.h"
#include "DDTransformComponent.h"
#include "DDVector2.h"

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

DDGameEngine::DDGameEngine() : _platform{ CreatePlatform() }, _renderer{ CreateRenderer() }, _gameWorld{ this }, _renderSystem{}, _inputSystem{}, _isRunning{ false }
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
    if (_inputSystem.IsKeyDown(DD_KEY_ESCAPE)) _isRunning = false;

    float playerSpeed = 300.0f;
    float distance = playerSpeed * deltaTime;

    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);
    if (!player) return;

    DDTransformComponent* transform = player->GetTransform();
    if (!transform) return;

    const DDVector2& position = transform->GetPosition();

    float x = position.x;
    float y = position.y;

    if (_inputSystem.IsKeyDown(DD_KEY_W)) y -= distance;
    if (_inputSystem.IsKeyDown(DD_KEY_S)) y += distance;
    if (_inputSystem.IsKeyDown(DD_KEY_A)) x -= distance;
    if (_inputSystem.IsKeyDown(DD_KEY_D)) x += distance;

    transform->SetPosition(x, y);

    _gameWorld.Update(deltaTime);
}

void DDGameEngine::Render(float deltaTime)
{
    _renderSystem.Render(&_gameWorld, _renderer);
}

void DDGameEngine::ProcessEvents()
{
    DDPlatformEvent event{};

    while (_platform->PollEvent(event))
    {
        _inputSystem.ProcessEvent(event);

        switch (event.type)
        {
        case DDPlatformEvent::DD_EVENT_QUIT:
            _isRunning = false;
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

        _inputSystem.BeginFrame();

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