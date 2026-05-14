#include "DDRendererWindows.h"

#include "IDDPlatform.h"

DDRendererWindows::DDRendererWindows()
    : _window{ nullptr },
    _windowDC{ nullptr },
    _backBufferDC{ nullptr },
    _backBufferBitmap{ nullptr },
    _oldBackBufferBitmap{ nullptr },
    _windowWidth{ 800 },
    _windowHeight{ 600 }
{}

int DDRendererWindows::Init(IDDPlatform* platform)
{
    if (!platform) return -1;

    _window = (HWND)platform->GetNativeWindow();
    if (!_window) return -1;

    _windowDC = GetDC(_window);
    if (!_windowDC) return -1;

    _backBufferDC = CreateCompatibleDC(_windowDC);
    if (!_backBufferDC) return -1;

    _backBufferBitmap = CreateCompatibleBitmap(_windowDC, _windowWidth, _windowHeight);
    if (!_backBufferBitmap) return -1;

    _oldBackBufferBitmap = (HBITMAP)SelectObject(_backBufferDC, _backBufferBitmap);
    if (!_oldBackBufferBitmap) return -1;

    return 0;
}

void DDRendererWindows::BeginFrame()
{
    HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);

    RECT clearRect{};
    clearRect.left = 0;
    clearRect.top = 0;
    clearRect.right = _windowWidth;
    clearRect.bottom = _windowHeight;

    FillRect(_backBufferDC, &clearRect, whiteBrush);
}

void DDRendererWindows::DrawRect2D(float x, float y, float width, float height)
{
    HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

    RECT rect{};
    rect.left = (LONG)x;
    rect.top = (LONG)y;
    rect.right = rect.left + (LONG)width;
    rect.bottom = rect.top + (LONG)height;

    FillRect(_backBufferDC, &rect, blackBrush);
}

void DDRendererWindows::DrawText2D(int x, int y, const char* text, int length)
{
    SetBkMode(_backBufferDC, TRANSPARENT);
    SetTextColor(_backBufferDC, RGB(0, 0, 0));
    TextOutA(_backBufferDC, x, y, text, length);
}

void DDRendererWindows::EndFrame()
{
    BitBlt(_windowDC, 0, 0, _windowWidth, _windowHeight, _backBufferDC, 0, 0, SRCCOPY);
}

void DDRendererWindows::ResizeWindow(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;

    if (!_windowDC || !_backBufferDC) return;

    if (_backBufferBitmap)
    {
        SelectObject(_backBufferDC, _oldBackBufferBitmap);
        DeleteObject(_backBufferBitmap);
        _backBufferBitmap = nullptr;
    }

    _backBufferBitmap = CreateCompatibleBitmap(_windowDC, _windowWidth, _windowHeight);
    if (!_backBufferBitmap) return;

    SelectObject(_backBufferDC, _backBufferBitmap);
}

void DDRendererWindows::Shutdown()
{
    if (_backBufferDC && _oldBackBufferBitmap)
    {
        SelectObject(_backBufferDC, _oldBackBufferBitmap);
        _oldBackBufferBitmap = nullptr;
    }

    if (_backBufferBitmap)
    {
        DeleteObject(_backBufferBitmap);
        _backBufferBitmap = nullptr;
    }

    if (_backBufferDC)
    {
        DeleteDC(_backBufferDC);
        _backBufferDC = nullptr;
    }

    if (_window && _windowDC)
    {
        ReleaseDC(_window, _windowDC);
        _windowDC = nullptr;
    }

    _window = nullptr;
}