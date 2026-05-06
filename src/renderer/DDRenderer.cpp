#include "DDRenderer.h"
#include <X11/Xlib.h>
#include "DDList.h"
#include "DDGameObject.h"

DDRenderer::DDRenderer() : _display{nullptr}, _gc{}, _rootWindow{}, _window{}, _backBuffer{}, _screen{-1}, _windowWidth{800}, _windowHeight{600}
{}

Display* DDRenderer::GetDisplay()
{
    return _display;
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
        _windowWidth,
        _windowHeight,
        1,        // border width
        BlackPixel(_display, _screen),
        WhitePixel(_display, _screen)
    );

    _backBuffer = XCreatePixmap
    (
        _display,
        _window,
        _windowWidth,
        _windowHeight,
        DefaultDepth(_display, _screen)
    );

    XStoreName(_display, _window, "Basic X11 Window");
    XSelectInput(_display, _window, ExposureMask | KeyPressMask | StructureNotifyMask);
    XMapWindow(_display, _window);

    return 0;
}

void DDRenderer::Render(const DDList<DDGameObject>& gameObjects) const // need to make DDList
{
    // Clear back buffer
    XSetForeground(_display, _gc, WhitePixel(_display, _screen));
    XFillRectangle(_display, _backBuffer, _gc, 0, 0, _windowWidth, _windowHeight);

    // Draw objects to back buffer
    XSetForeground(_display, _gc, BlackPixel(_display, _screen));

    for (int i = 0; i < gameObjects.Size(); i++)
    {
        DDGameObject* gameObject = gameObjects.GetAt(i);
        XFillRectangle(_display, _backBuffer, _gc, gameObject->GetPosition().x, gameObject->GetPosition().y, 50, 50); // need to add scale
    }

    // Copy finished frame to visible window
    XCopyArea(_display, _backBuffer, _window, _gc, 0, 0, _windowWidth, _windowHeight, 0, 0);
    XFlush(_display);
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
