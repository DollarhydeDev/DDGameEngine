#pragma once

#include "IDDPlatform.h"

#include <windows.h>

class DDPlatformWindows final : public IDDPlatform
{
private:
    HINSTANCE _instance;
    HWND _window;

    int _windowWidth;
    int _windowHeight;

    LARGE_INTEGER _performanceFrequency;
    LARGE_INTEGER _lastCounter;

private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    DDKey TranslateKey(WPARAM key) const;

public:
    DDPlatformWindows();

    int Init(int width, int height, const char* title) override;
    bool PollEvent(DDPlatformEvent& event) override;

    float GetDeltaTime() override;
    void SleepMilliseconds(int milliseconds) override;

    void Shutdown() override;

    void* GetNativeDisplay() override;
    uintptr_t GetNativeWindow() override;
};