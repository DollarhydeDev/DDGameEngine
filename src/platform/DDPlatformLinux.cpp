#include "platform/DDPlatformLinux.h"

#include <X11/keysym.h>

DDPlatformLinux::DDPlatformLinux() : _display{ nullptr }, _rootWindow{}, _window{}, _screen{ -1 }, _windowWidth{ 800 }, _windowHeight{ 600 }, _lastTime{}
{}

int DDPlatformLinux::Init(int width, int height, const char* title)
{
    _windowWidth = width;
    _windowHeight = height;

    _display = XOpenDisplay(nullptr);
    if (!_display) return -1;

    _screen = XDefaultScreen(_display);
    _rootWindow = XDefaultRootWindow(_display);

    _window = XCreateSimpleWindow
    (
        _display,
        _rootWindow,
        100,
        100,
        _windowWidth,
        _windowHeight,
        1,
        BlackPixel(_display, _screen),
        WhitePixel(_display, _screen)
    );

    XStoreName(_display, _window, title);

    XSelectInput
    (
        _display,
        _window,
        ExposureMask |
        KeyPressMask |
        KeyReleaseMask |
        StructureNotifyMask
    );

    XMapWindow(_display, _window);

    clock_gettime(CLOCK_MONOTONIC, &_lastTime);

    return 0;
}

bool DDPlatformLinux::PollEvent(DDPlatformEvent& event)
{
    event = {};

    if (!_display) return false;
    if (XPending(_display) <= 0) return false;

    XEvent xEvent;
    XNextEvent(_display, &xEvent);

    switch (xEvent.type)
    {
    case KeyPress:
    {
        KeySym key = XLookupKeysym(&xEvent.xkey, 0);
        event.type = DDPlatformEvent::DD_EVENT_KEY_DOWN;
        event.key = TranslateKey(key);
        return true;
    }

    case KeyRelease:
    {
        KeySym key = XLookupKeysym(&xEvent.xkey, 0);
        event.type = DDPlatformEvent::DD_EVENT_KEY_UP;
        event.key = TranslateKey(key);
        return true;
    }

    case ConfigureNotify:
    {
        _windowWidth = xEvent.xconfigure.width;
        _windowHeight = xEvent.xconfigure.height;

        event.type = DDPlatformEvent::DD_EVENT_RESIZE;
        event.width = _windowWidth;
        event.height = _windowHeight;
        return true;
    }

    case DestroyNotify:
    {
        event.type = DDPlatformEvent::DD_EVENT_QUIT;
        return true;
    }

    default:
        event.type = DDPlatformEvent::DD_EVENT_NONE;
        return true;
    }
}

float DDPlatformLinux::GetDeltaTime()
{
    timespec currentTime;
    clock_gettime(CLOCK_MONOTONIC, &currentTime);

    long seconds = currentTime.tv_sec - _lastTime.tv_sec;
    long nanoseconds = currentTime.tv_nsec - _lastTime.tv_nsec;

    float deltaTime = (float)seconds + (float)nanoseconds / 1000000000.0f;

    _lastTime = currentTime;

    return deltaTime;
}

void DDPlatformLinux::SleepMilliseconds(int milliseconds)
{
    timespec sleepTime;
    sleepTime.tv_sec = milliseconds / 1000;
    sleepTime.tv_nsec = (milliseconds % 1000) * 1000000L;

    nanosleep(&sleepTime, nullptr);
}

void DDPlatformLinux::Shutdown()
{
    if (_display && _window)
    {
        XDestroyWindow(_display, _window);
        _window = {};
    }

    if (_display)
    {
        XCloseDisplay(_display);
        _display = nullptr;
    }
}

void* DDPlatformLinux::GetNativeDisplay()
{
    return _display;
}

uintptr_t DDPlatformLinux::GetNativeWindow()
{
    return (uintptr_t)_window;
}

DDKey DDPlatformLinux::TranslateKey(KeySym key) const
{
    switch (key)
    {
    case XK_Escape: return DD_KEY_ESCAPE;
    case XK_w:
    case XK_W: return DD_KEY_W;
    case XK_a:
    case XK_A: return DD_KEY_A;
    case XK_s:
    case XK_S: return DD_KEY_S;
    case XK_d:
    case XK_D: return DD_KEY_D;
    default: return DD_KEY_UNKNOWN;
    }
}