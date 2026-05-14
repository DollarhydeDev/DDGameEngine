#pragma once

template<typename T>
class DDList;

class DDGameObject;
class IDDPlatform;

class IDDRenderer
{
public:
    virtual ~IDDRenderer() = default;

    virtual int Init(IDDPlatform* platform) = 0;
    virtual void Render(const DDList<DDGameObject>& gameObjects, float deltaTime) const = 0;
    virtual void Shutdown() = 0;
    virtual void ResizeWindow(int width, int height) = 0;
};