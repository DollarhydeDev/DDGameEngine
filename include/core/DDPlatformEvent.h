#pragma once

#include "DDKey.h"

struct DDPlatformEvent
{
    enum DDPlatformEventType
    {
        DD_EVENT_NONE = 0,
        DD_EVENT_QUIT,
        DD_EVENT_KEY_DOWN,
        DD_EVENT_KEY_UP,
        DD_EVENT_RESIZE
    };

    DDPlatformEventType type = DD_EVENT_NONE;
    DDKey key = DD_KEY_UNKNOWN;

    int width = 0;
    int height = 0;
};