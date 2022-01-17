#pragma once

#include "IShape.h"

class IReflectable : virtual public IShape
{
public:
    virtual void flip_horisontally() = 0;
    virtual void flip_vertically() = 0;
};
