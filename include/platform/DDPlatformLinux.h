#pragma once

#include "IDDPlatform.h"

#include <X11/Xlib.h>
#include <time.h>

class DDPlatformLinux final : public IDDPlatform
{
private:
    Display* _display;
    Window _rootWindow;
    Window _window;
    int _screen;

    int _windowWidth;
    int _windowHeight;

    timespec _lastTime;

private:
    DDKey TranslateKey(KeySym key) const;

public:
    DDPlatformLinux();

    int Init(int width, int height, const char* title) override;
    bool PollEvent(DDPlatformEvent& event) override;

    float GetDeltaTime() override;
    void SleepMilliseconds(int milliseconds) override;

    void Shutdown() override;

    void* GetNativeDisplay() override;
    uintptr_t GetNativeWindow() override;
};