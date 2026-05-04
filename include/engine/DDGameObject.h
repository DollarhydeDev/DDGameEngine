#pragma once

#include "DDVector2.h"

class DDGameObject
{
    private:
    DDVector2 _position;
    DDVector2 _scale;

    public:
    DDGameObject();
    DDGameObject(int scaleX, scaleY, int posX, int posY);

    const DDVector2& GetPosition() const;
    void SetPosition(x, y);
}
