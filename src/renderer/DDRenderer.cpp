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
    XSelectInput(_display, _window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask);
    XMapWindow(_display, _window);

    return 0;
}

void DDRenderer::Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const // need to make DDList
{
    // Clear back buffer
    XSetForeground(_display, _gc, WhitePixel(_display, _screen));
    XFillRectangle(_display, _backBuffer, _gc, 0, 0, _windowWidth, _windowHeight);

    // Draw objects to back buffer
    XSetForeground(_display, _gc, BlackPixel(_display, _screen));

    for (int i = 0; i < gameObjects.Size(); i++)
    {
        DDGameObject* gameObject = gameObjects.GetAt(i);
        XFillRectangle(_display, _backBuffer, _gc, gameObject->GetPosition().x, gameObject->GetPosition().y, gameObject->GetScale().x, gameObject->GetScale().y); // need to add scale
    }

    // Need to move this handling to another class or something. Fine here for testing though.
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

        while (fps > 0)
        {
            reversedFpsText[fpsDigitCount++] = '0' + (fps % 10);
            fps /= 10;
        }

        for (int i = fpsDigitCount - 1; i >= 0; i--)
        {
            fpsText[index++] = reversedFpsText[i];
        }
    }

    int textLength = index;
    XDrawString(_display, _backBuffer, _gc, 10, 20, fpsText, textLength);

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
