#pragma once

#include "IDDRenderer.h"

#include <windows.h>

class DDRendererWindows : public IDDRenderer
{
private:
    HWND _window;

    HDC _windowDC;
    HDC _backBufferDC;
    HBITMAP _backBufferBitmap;
    HBITMAP _oldBackBufferBitmap;

    int _windowWidth;
    int _windowHeight;

public:
    DDRendererWindows();

    int Init(IDDPlatform* platform) override;

    void BeginFrame() override;
    void DrawRect2D(float x, float y, float width, float height) override;
    void DrawText2D(int x, int y, const char* text, int length) override;
    void EndFrame() override;

    void Shutdown() override;
    void ResizeWindow(int width, int height) override;
};