#include <X11/Xlib.h>

class DDRenderer
{
    private:
    Display* _display;
    GC _gc;
    Window _rootWindow;
    Window _window;

    int _screen;
    bool _isRunning;

    int _windowWidth;
    int _windowHeight;

    public:
    DDRenderer();

    int Init();
    void Run();
    void Shutdown();
    void ResizeWindow(int width, int height);
};
