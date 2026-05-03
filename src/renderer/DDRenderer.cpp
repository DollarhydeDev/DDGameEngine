#include "DDRenderer.h"
#include <X11/Xlib.h>

DDRenderer::DDRenderer()
{
    _display = nullptr;
    _screen = 1;
    _isRunning = false;

    _windowWidth = 800;
    _windowHeight = 600;
}

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

void DDRenderer::Run()
{
    _isRunning = true;

    while (_isRunning)
    {
        XEvent event;
        XNextEvent(_display, &event);

        switch (event.type)
        {
            case Expose:
                XClearWindow(_display, _window);
                XFillRectangle(_display, _window, _gc, 0, 0, 50, 50);
                break;

            case KeyPress:
                _isRunning = false;
                break;

            case ConfigureNotify:
                ResizeWindow(event.xconfigure.width, event.xconfigure.height);
                break;

            case DestroyNotify:
                _isRunning = false;
                break;
        }
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
