#pragma once

#include "IDDRenderer.h"

#include <X11/Xlib.h>

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

    void BeginFrame() override;
    void DrawRect2D(float x, float y, float width, float height) override;
    void DrawText2D(int x, int y, const char* text, int length) override;
    void EndFrame() override;

    void Shutdown() override;
    void ResizeWindow(int width, int height) override;
};