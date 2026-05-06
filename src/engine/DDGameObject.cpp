#include <DDGameObject.h>

DDGameObject::DDGameObject(){}
DDGameObject::DDGameObject(int scaleX, int scaleY, int posX, int posY)
{
    _scale.x = scaleX;
    _scale.y = scaleY;

    _position.x = posX;
    _position.y = posY;
}

void DDGameObject::Init()
{

}
void DDGameObject::Start()
{

}
void DDGameObject::Update(float deltaTime)
{

}

const DDVector2& DDGameObject::GetScale() const
{
    return _scale;
}
void DDGameObject::SetScale(int x, int y)
{
    _scale.x = x;
    _scale.y = y;
}

const DDVector2& DDGameObject::GetPosition() const
{
    return _position;
}
void DDGameObject::SetPosition(int x, int y)
{
    _position.x = x;
    _position.y = y;
}
