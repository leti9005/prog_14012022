#pragma once

#include "IShape.h"

class IRotatable : virtual public IShape
{
public:
    virtual void rotate_left() = 0;  // Повернуть влево
    virtual void rotate_right() = 0; // Повернуть вправо
};
