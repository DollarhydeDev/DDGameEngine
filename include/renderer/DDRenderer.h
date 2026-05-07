#pragma once

#include <X11/Xlib.h>
#include "DDList.h"
#include "DDGameObject.h"

class DDRenderer
{
    private:
    Display* _display;
    GC _gc;
    Window _rootWindow;
    Window _window;
    Pixmap _backBuffer;

    int _screen;
    int _windowWidth;
    int _windowHeight;

    public:
    DDRenderer();

    Display* GetDisplay();

    int Init();
    void Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const;
    void Shutdown();
    void ResizeWindow(int width, int height);
};
