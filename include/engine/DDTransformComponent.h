#pragma once

#include "DDComponent.h"
#include "DDVector2.h"

class DDTransformComponent : public DDComponent
{
private:
    DDVector2 _position;
    DDVector2 _scale;

public:
    DDTransformComponent();

    const DDVector2& GetPosition() const;
    void SetPosition(float x, float y);

    const DDVector2& GetScale() const;
    void SetScale(float x, float y);
};