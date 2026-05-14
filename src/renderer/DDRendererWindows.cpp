#include "DDRendererWindows.h"

#include "IDDPlatform.h"
#include "DDList.h"
#include "DDGameObject.h"

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

void DDRendererWindows::Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const
{
    HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);

    RECT clearRect{};
    clearRect.left = 0;
    clearRect.top = 0;
    clearRect.right = _windowWidth;
    clearRect.bottom = _windowHeight;

    FillRect(_backBufferDC, &clearRect, whiteBrush);

    for (int i = 0; i < gameObjects.Size(); i++)
    {
        DDGameObject* gameObject = gameObjects.GetAt(i);

        RECT objectRect{};
        objectRect.left = (LONG)gameObject->GetPosition().x;
        objectRect.top = (LONG)gameObject->GetPosition().y;
        objectRect.right = objectRect.left + (LONG)gameObject->GetScale().x;
        objectRect.bottom = objectRect.top + (LONG)gameObject->GetScale().y;

        FillRect(_backBufferDC, &objectRect, blackBrush);
    }

    char fpsText[15];
    fpsText[0] = 'F';
    fpsText[1] = 'P';
    fpsText[2] = 'S';
    fpsText[3] = ':';
    fpsText[4] = ' ';

    int index = 5;
    int fps = (int)(deltaTime > 0.0f ? 1.0f / deltaTime : 0.0f);

    if (fps == 0)
    {
        fpsText[index++] = '0';
    }
    else
    {
        int fpsDigitCount = 0;
        char reversedFpsText[10];

        while (fps > 0 && fpsDigitCount < 10)
        {
            reversedFpsText[fpsDigitCount++] = '0' + (fps % 10);
            fps /= 10;
        }

        for (int i = fpsDigitCount - 1; i >= 0; i--)
        {
            fpsText[index++] = reversedFpsText[i];
        }
    }

    SetBkMode(_backBufferDC, TRANSPARENT);
    SetTextColor(_backBufferDC, RGB(0, 0, 0));
    TextOutA(_backBufferDC, 10, 10, fpsText, index);

    BitBlt
    (
        _windowDC,
        0,
        0,
        _windowWidth,
        _windowHeight,
        _backBufferDC,
        0,
        0,
        SRCCOPY
    );
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