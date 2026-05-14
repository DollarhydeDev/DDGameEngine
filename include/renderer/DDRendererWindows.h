#pragma once

#include "IDDRenderer.h"

#include <windows.h>

#include "DDList.h"
#include "DDGameObject.h"

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
    void Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const override;
    void Shutdown() override;
    void ResizeWindow(int width, int height) override;
};