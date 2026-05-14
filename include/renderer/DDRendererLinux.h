#pragma once

#include "IDDRenderer.h"

#include <X11/Xlib.h>

#include "DDList.h"
#include "DDGameObject.h"

class DDRendererLinux : public IDDRenderer
{
private:
    Display* _display;
    Window _window;
    GC _gc;
    Pixmap _backBuffer;

    int _screen;
    int _windowWidth;
    int _windowHeight;

public:
    DDRendererLinux();

    int Init(IDDPlatform* platform) override;
    void Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const override;
    void Shutdown() override;
    void ResizeWindow(int width, int height) override;
};