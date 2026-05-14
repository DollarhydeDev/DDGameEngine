#include "DDRendererLinux.h"

#include "IDDPlatform.h"
#include "DDList.h"
#include "DDGameObject.h"

DDRendererLinux::DDRendererLinux()
    : _display{ nullptr },
    _window{},
    _gc{},
    _backBuffer{},
    _screen{ -1 },
    _windowWidth{ 800 },
    _windowHeight{ 600 }
{}

int DDRendererLinux::Init(IDDPlatform* platform)
{
    if (!platform) return -1;

    _display = (Display*)platform->GetNativeDisplay();
    _window = (Window)platform->GetNativeWindow();

    if (!_display || !_window) return -1;

    _screen = XDefaultScreen(_display);
    _gc = XDefaultGC(_display, _screen);

    _backBuffer = XCreatePixmap
    (
        _display,
        _window,
        _windowWidth,
        _windowHeight,
        DefaultDepth(_display, _screen)
    );

    if (!_backBuffer) return -1;

    return 0;
}

void DDRendererLinux::Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const
{
    XSetForeground(_display, _gc, WhitePixel(_display, _screen));
    XFillRectangle(_display, _backBuffer, _gc, 0, 0, _windowWidth, _windowHeight);

    XSetForeground(_display, _gc, BlackPixel(_display, _screen));

    for (int i = 0; i < gameObjects.Size(); i++)
    {
        DDGameObject* gameObject = gameObjects.GetAt(i);

        XFillRectangle
        (
            _display,
            _backBuffer,
            _gc,
            (int)gameObject->GetPosition().x,
            (int)gameObject->GetPosition().y,
            (unsigned int)gameObject->GetScale().x,
            (unsigned int)gameObject->GetScale().y
        );
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

    XDrawString(_display, _backBuffer, _gc, 10, 20, fpsText, index);

    XCopyArea
    (
        _display,
        _backBuffer,
        _window,
        _gc,
        0,
        0,
        _windowWidth,
        _windowHeight,
        0,
        0
    );

    XFlush(_display);
}

void DDRendererLinux::ResizeWindow(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;

    if (_display && _window && _backBuffer)
    {
        XFreePixmap(_display, _backBuffer);

        _backBuffer = XCreatePixmap
        (
            _display,
            _window,
            _windowWidth,
            _windowHeight,
            DefaultDepth(_display, _screen)
        );
    }
}

void DDRendererLinux::Shutdown()
{
    if (_display && _backBuffer)
    {
        XFreePixmap(_display, _backBuffer);
        _backBuffer = {};
    }

    _display = nullptr;
    _window = {};
}