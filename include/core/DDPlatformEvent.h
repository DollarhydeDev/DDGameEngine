#pragma once

struct DDPlatformEvent
{
    enum Type
    {
        None = 0,
        Quit,
        KeyDown,
        KeyUp,
        Resize
    };

    Type type = None;
    DDKey key = DD_KEY_UNKNOWN;
    int width = 0;
    int height = 0;
};