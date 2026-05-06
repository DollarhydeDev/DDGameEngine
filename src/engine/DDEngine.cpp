#include "DDEngine.h"
#include "X11/Xlib.h"

DDEngine::DDEngine() : _renderer{}, _gameObjects{}, _isRunning{false} {}
DDEngine::~DDEngine()
{
    for (int i = 0; i < _gameObjects.Size(); ++i)
    {
        delete _gameObjects.GetAt(i);
    }

    _gameObjects.Clear();
}

int DDEngine::Init()
{
    if (_renderer.Init() != 0) return -1;

    DDGameObject* player = new DDGameObject();
    _gameObjects.Add(player);

    return 0;
}

void DDEngine::Run()
{
    _isRunning = true;

    while (isRunning)
    {
        // I think this waits for input
        // Bad for us because game doesn't move until player presses a key
        // Need to revisit
        XEvent event;
        XNextEvent(_display, &event);

        switch (event.type)
        {
            case KeyPress:
                DDGameObject* player = _gameObjects.GetAt(0);
                player->SetPosition(player->GetPosition().x + 1, player->GetPosition().y);
                break;

            case ConfigureNotify:
                _renderer.ResizeWindow(event.xconfigure.width, event.xconfigure.height);
                break;

            case DestroyNotify:
                _isRunning = false;
                break;
        }

        _renderer.Render(_gameObjects);
    }
}

void DDEngine::Shutdown()
{
    _renderer.Shutdown();
}
