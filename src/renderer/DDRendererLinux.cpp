#include "DDRendererLinux.h"

#include "IDDPlatform.h"

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

    _backBuffer = XCreatePixmap(_display, _window, _windowWidth, _windowHeight, DefaultDepth(_display, _screen));
    if (!_backBuffer) return -1;

    return 0;
}

void DDRendererLinux::BeginFrame()
{
    XSetForeground(_display, _gc, WhitePixel(_display, _screen));
    XFillRectangle(_display, _backBuffer, _gc, 0, 0, _windowWidth, _windowHeight);
}

void DDRendererLinux::DrawRect2D(float x, float y, float width, float height)
{
    XSetForeground(_display, _gc, BlackPixel(_display, _screen));
    XFillRectangle(_display, _backBuffer, _gc, (int)x, (int)y, (unsigned int)width, (unsigned int)height);
}

void DDRendererLinux::DrawText2D(int x, int y, const char* text, int length)
{
    XSetForeground(_display, _gc, BlackPixel(_display, _screen));
    XDrawString(_display, _backBuffer, _gc, x, y, text, length);
}

void DDRendererLinux::EndFrame()
{
    XCopyArea(_display, _backBuffer, _window, _gc, 0, 0, _windowWidth, _windowHeight, 0, 0);
    XFlush(_display);
}

void DDRendererLinux::ResizeWindow(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;

    if (_display && _window && _backBuffer)
    {
        XFreePixmap(_display, _backBuffer);
        _backBuffer = XCreatePixmap(_display, _window, _windowWidth, _windowHeight, DefaultDepth(_display, _screen));
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