#include "DDVector2.h"

DDVector2::DDVector2() : x{0}, y{0} {}

DDVector2::DDVector2(float x, float y) : x{x}, y{y}
{
    this->x = x;
    this->y = y;
}
