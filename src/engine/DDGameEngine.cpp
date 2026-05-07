#include "DDGameEngine.h"

#include "X11/Xlib.h"
#include <X11/keysym.h>
#include <time.h>

DDGameEngine::DDGameEngine() : _renderer{}, _gameWorld{this}, _isRunning{false} {}
DDGameEngine::~DDGameEngine(){}

float DDGameEngine::GetDeltaTime()
{
    timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);

    long seconds = currentTime.tv_sec - _lastTime.tv_sec;
    long nanoSeconds = currentTime.tv_nsec - _lastTime.tv_nsec;

    float deltaTime = (float)seconds + (float)nanoSeconds / 1000000000.0f;
    _lastTime = currentTime;

    return deltaTime;
}

void DDGameEngine::Start()
{
    _isRunning = true;
    _gameWorld.Start();
    clock_gettime(CLOCK_MONOTONIC, &_lastTime);
}

void DDGameEngine::Update(float deltaTime)
{
    // Here for testing. Will offload player logic to somewhere else later.
    float playerSpeed = 300.0f;
    float distance = playerSpeed * deltaTime;

    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);

    float x = player->GetPosition().x;
    float y = player->GetPosition().y;

    if (_upPressed)    y -= distance;
    if (_downPressed)  y += distance;
    if (_leftPressed)  x -= distance;
    if (_rightPressed) x += distance;

    player->SetPosition(x, y);

    _gameWorld.Update(deltaTime);
}

void DDGameEngine::Render(float deltaTime)
{
    _renderer.Render(_gameWorld.GetWorldGameObjects(), deltaTime);
}

void DDGameEngine::ProcessEvents()
{
    while (XPending(_renderer.GetDisplay()) > 0)
    {
        XEvent event;
        XNextEvent(_renderer.GetDisplay(), &event);

        switch (event.type)
        {
            case KeyPress:
            {
                KeySym key = XLookupKeysym(&event.xkey, 0);

                if (key == XK_Escape)
                {
                    _isRunning = false;
                    return;
                }

                if (key == XK_w) _upPressed = true;
                if (key == XK_s) _downPressed = true;
                if (key == XK_a) _leftPressed = true;
                if (key == XK_d) _rightPressed = true;

                break;
            }

            case KeyRelease:
            {
                KeySym key = XLookupKeysym(&event.xkey, 0);

                if (key == XK_w) _upPressed = false;
                if (key == XK_s) _downPressed = false;
                if (key == XK_a) _leftPressed = false;
                if (key == XK_d) _rightPressed = false;

                break;
            }

            case ConfigureNotify:
                _renderer.ResizeWindow(event.xconfigure.width, event.xconfigure.height);
                break;

            case DestroyNotify:
                _isRunning = false;
                break;
        }
    }
}

int DDGameEngine::Init()
{
    if (_renderer.Init() != 0) return -1;
    return 0;
}

void DDGameEngine::Run()
{
    Start();

    while(_isRunning)
    {
        float deltaTime = GetDeltaTime();
        ProcessEvents();
        Update(deltaTime);
        Render(deltaTime);
        
        timespec sleepTime;
        sleepTime.tv_sec = 0;
        // sleepTime.tv_nsec = 16000000; // 60 fps
        sleepTime.tv_nsec = 8000000; // 120 fps

        nanosleep(&sleepTime, nullptr);
    }
}

void DDGameEngine::Shutdown()
{
    _renderer.Shutdown();
}
