#pragma once

#include <vector>
#include "Point.h"

using namespace std;

struct IShape
{
    static vector<IShape*> shapes;

    IShape()
    {
        IShape::shapes.push_back(this);
    }

    virtual Point north() const = 0;
    virtual Point south() const = 0;
    virtual Point east() const = 0;
    virtual Point west() const = 0;
    virtual Point neast() const = 0;
    virtual Point seast() const = 0;
    virtual Point nwest() const = 0;
    virtual Point swest() const = 0;

    virtual void draw() = 0;
    virtual void move(int, int) = 0;
};

vector<IShape*> IShape::shapes = vector<IShape*>();
