#include <DDGameObject.h>

DDGameObject::DDGameObject(){}
DDGameObject::DDGameObject(int scaleX, scaleY, int posX, int posY)
{
    _scale.x = scaleX;
    _scale.y = scaleY;

    _position.x = posX;
    _position.y = posY;
}

DDGameObject::SetPosition(int x, int y)
{
    _position.x = x;
    _position.y = y;
}

const DDVector2& DDGameObject::GetPosition() const
{
    return _position;
}
