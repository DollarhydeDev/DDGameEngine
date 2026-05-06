#include "DDGameEngine.h"
#include "X11/Xlib.h"
#include <X11/keysym.h>

DDGameEngine::DDGameEngine() : _renderer{}, _gameWorld{this}, _isRunning{false} {}
DDGameEngine::~DDGameEngine(){}

void DDGameEngine::Start()
{
    _isRunning = true;
    _gameWorld.Start();
}

void DDGameEngine::Update()
{
    float deltaTime = 0; // need to figure out how to get this
    _gameWorld.Update(deltaTime);
}

void DDGameEngine::Render()
{
    _renderer.Render(_gameWorld.GetWorldGameObjects());
}

void DDGameEngine::ProcessEvents()
{
    while(XPending(_renderer.GetDisplay()) > 0)
    {
        XEvent event;
        XNextEvent(_renderer.GetDisplay(), &event);

        switch (event.type)
        {
            case KeyPress:
            {
                KeySym key = XLookupKeysym(&event.xkey, 0);
                if (key == XK_Escape) { _isRunning = false; return; }

                if (key == XK_Up)
                {
                    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);
                    player->SetPosition(player->GetPosition().x, player->GetPosition().y - 1);
                }
                else if (key == XK_Down)
                {
                    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);
                    player->SetPosition(player->GetPosition().x, player->GetPosition().y + 1);
                }
                else if (key == XK_Right)
                {
                    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);
                    player->SetPosition(player->GetPosition().x + 1, player->GetPosition().y);
                }
                else if (key == XK_Left)
                {
                    DDGameObject* player = _gameWorld.GetWorldGameObjects().GetAt(0);
                    player->SetPosition(player->GetPosition().x - 1, player->GetPosition().y);
                }

                break;
            }

            case ConfigureNotify:
            {
                _renderer.ResizeWindow(event.xconfigure.width, event.xconfigure.height);
                break;
            }

            case DestroyNotify:
            {
                _isRunning = false;
                break;
            }
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
        ProcessEvents();
        Update();
        Render();
    }
}

void DDGameEngine::Shutdown()
{
    _renderer.Shutdown();
}
