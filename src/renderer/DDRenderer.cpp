#include "DDRenderer.h"
#include <X11/Xlib.h>

DDRenderer::DDRenderer() : _display{nullptr}, _screen{-1}, _windowWidth{800}, _windowHeight{600}
{}

int DDRenderer::Init()
{
    _display = XOpenDisplay(nullptr);
    if (!_display) return -1;

    _screen = XDefaultScreen(_display);
    _gc = XDefaultGC(_display, _screen);
    _rootWindow = XDefaultRootWindow(_display);

    _window = XCreateSimpleWindow
    (
        _display,
        _rootWindow,
        100, 100, // position
        _windowWidth, _windowHeight, // size
        1,        // border width
        BlackPixel(_display, _screen),
        WhitePixel(_display, _screen)
    );

    XStoreName(_display, _window, "Basic X11 Window");
    XSelectInput(_display, _window, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(_display, _window);

    return 0;
}

void DDRenderer::Render(DDGameObject* gameObjects, int count) // need to make DDList
{
    XClearWindow(_display, _window);
    for (int i = 0; i < count; i++)
    {
        XFillRectangle(_display, _window, _gc, gameObject->GetPosition()->x, gameObject->GetPosition()->y, 50, 50); // need to add scale
    }
}

void DDRenderer::ResizeWindow(int width, int height)
{
    _windowWidth = width;
    _windowHeight = height;
}

void DDRenderer::Shutdown()
{
    XDestroyWindow(_display, _window);
    XCloseDisplay(_display);
}
