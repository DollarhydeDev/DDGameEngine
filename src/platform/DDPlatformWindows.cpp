#include "platform/DDPlatformWindows.h"

#include <timeapi.h>

DDPlatformWindows::DDPlatformWindows() : _instance{ nullptr }, _window{ nullptr }, _windowWidth{ 800 }, _windowHeight{ 600 }, _performanceFrequency{}, _lastCounter{}
{}

LRESULT CALLBACK DDPlatformWindows::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
}

int DDPlatformWindows::Init(int width, int height, const char* title)
{
    _windowWidth = width;
    _windowHeight = height;

    _instance = GetModuleHandleA(nullptr);
    if (!_instance) return -1;

    WNDCLASSA windowClass{};
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = DDPlatformWindows::WindowProc;
    windowClass.hInstance = _instance;
    windowClass.lpszClassName = "DDGameWindowClass";

    if (!RegisterClassA(&windowClass))
    {
        if (GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
        {
            return -1;
        }
    }

    RECT windowRect{};
    windowRect.left = 0;
    windowRect.top = 0;
    windowRect.right = _windowWidth;
    windowRect.bottom = _windowHeight;

    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    int windowPixelWidth = windowRect.right - windowRect.left;
    int windowPixelHeight = windowRect.bottom - windowRect.top;

    _window = CreateWindowExA
    (
        0,
        windowClass.lpszClassName,
        title,
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100,
        100,
        windowPixelWidth,
        windowPixelHeight,
        nullptr,
        nullptr,
        _instance,
        nullptr
    );

    if (!_window) return -1;

    timeBeginPeriod(1);
    QueryPerformanceFrequency(&_performanceFrequency);
    QueryPerformanceCounter(&_lastCounter);

    return 0;
}

bool DDPlatformWindows::PollEvent(DDPlatformEvent& event)
{
    event = {};

    MSG msg;

    while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        switch (msg.message)
        {
        case WM_QUIT:
        {
            event.type = DDPlatformEvent::DD_EVENT_QUIT;
            return true;
        }

        case WM_KEYDOWN:
        {
            event.type = DDPlatformEvent::DD_EVENT_KEY_DOWN;
            event.key = TranslateKey(msg.wParam);
            return true;
        }

        case WM_KEYUP:
        {
            event.type = DDPlatformEvent::DD_EVENT_KEY_UP;
            event.key = TranslateKey(msg.wParam);
            return true;
        }

        case WM_SIZE:
        {
            _windowWidth = LOWORD(msg.lParam);
            _windowHeight = HIWORD(msg.lParam);

            event.type = DDPlatformEvent::DD_EVENT_RESIZE;
            event.width = _windowWidth;
            event.height = _windowHeight;
            return true;
        }

        default:
        {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
            break;
        }
        }
    }

    return false;
}

float DDPlatformWindows::GetDeltaTime()
{
    LARGE_INTEGER currentCounter;
    QueryPerformanceCounter(&currentCounter);

    LONGLONG elapsed = currentCounter.QuadPart - _lastCounter.QuadPart;

    float deltaTime = (float)((double)elapsed / (double)_performanceFrequency.QuadPart);

    _lastCounter = currentCounter;

    return deltaTime;
}

void DDPlatformWindows::SleepMilliseconds(int milliseconds)
{
    Sleep(milliseconds);
}

void DDPlatformWindows::Shutdown()
{
    timeEndPeriod(1);

    if (_window)
    {
        DestroyWindow(_window);
        _window = nullptr;
    }
}

void* DDPlatformWindows::GetNativeDisplay()
{
    return nullptr;
}

uintptr_t DDPlatformWindows::GetNativeWindow()
{
    return (uintptr_t)_window;
}

DDKey DDPlatformWindows::TranslateKey(WPARAM key) const
{
    switch (key)
    {
    case VK_ESCAPE: return DD_KEY_ESCAPE;
    case 'W': return DD_KEY_W;
    case 'A': return DD_KEY_A;
    case 'S': return DD_KEY_S;
    case 'D': return DD_KEY_D;
    default: return DD_KEY_UNKNOWN;
    }
}