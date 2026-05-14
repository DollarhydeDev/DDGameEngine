#pragma once

#include "DDComponent.h"

class DDRenderComponent : public DDComponent
{
private:
    bool _visible;

public:
    DDRenderComponent();

    bool IsVisible() const;
    void SetVisible(bool visible);
};