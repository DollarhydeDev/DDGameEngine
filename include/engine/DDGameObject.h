#pragma once

#include "DDVector2.h"

class DDGameObject
{
    private:
    DDVector2 _position;
    DDVector2 _scale;

    public:
    const DDVector2& GetScale() const;
    void SetScale(int x, int y);

    const DDVector2& GetPosition() const;
    void SetPosition(int x, int y);

    public:
    DDGameObject();
    DDGameObject(int scaleX, int scaleY, int posX, int posY);

    void Init();
    void Start();
    void Update(float deltaTime);
};
