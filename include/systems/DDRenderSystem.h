#pragma once

class DDGameWorld;
class IDDRenderer;

class DDRenderSystem
{
public:
    DDRenderSystem();
    ~DDRenderSystem();

    void Render(DDGameWorld* world, IDDRenderer* renderer);
};