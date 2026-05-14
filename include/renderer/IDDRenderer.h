#pragma once

class IDDPlatform;

class IDDRenderer
{
public:
    virtual ~IDDRenderer() = default;

    virtual int Init(IDDPlatform* platform) = 0;

    virtual void BeginFrame() = 0;
    virtual void DrawRect2D(float x, float y, float width, float height) = 0;
    virtual void DrawText2D(int x, int y, const char* text, int length) = 0;
    virtual void EndFrame() = 0;

    virtual void Shutdown() = 0;
    virtual void ResizeWindow(int width, int height) = 0;
};