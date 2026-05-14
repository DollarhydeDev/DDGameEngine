#pragma once

#include <stdint.h>

#include "DDKey.h"
#include "DDPlatformEvent.h"

class IDDPlatform
{
public:
    virtual ~IDDPlatform() = default;

    virtual int Init(int width, int height, const char* title) = 0;
    virtual bool PollEvent(DDPlatformEvent& event) = 0;

    virtual float GetDeltaTime() = 0;
    virtual void SleepMilliseconds(int milliseconds) = 0;

    virtual void Shutdown() = 0;

    virtual void* GetNativeDisplay() = 0;
    virtual uintptr_t GetNativeWindow() = 0;
};