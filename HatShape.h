#pragma once

#include "Point.h"
#include "IShape.h"
#include "shapes.h"

class HatShape : public IShape
{
    Rectangle* hatRectangle;
    Line* hatVisor;
    RightTriangle* hatSymbol;

public:
    HatShape(Point, Point);

    Point north() const { return this->hatRectangle->north(); }
    Point east() const { return this->hatRectangle->east(); }
    Point west() const { return this->hatRectangle->west(); }
    Point neast() const { return this->hatRectangle->neast(); }
    Point nwest() const { return this->hatRectangle->nwest(); }

    Point south() const { return this->hatVisor->south(); }
    Point seast() const { return this->hatVisor->seast(); }
    Point swest() const { return this->hatVisor->swest(); }

    void draw() {};
    void move(int, int);
};

HatShape::HatShape(Point a, Point b)
{
    this->hatRectangle = new Rectangle(a, b);
    this->hatRectangle->rotate_right();

    this->hatVisor = new Line(Point(0, 15), 25);
    up(this->hatRectangle, this->hatVisor);

    auto hatSymbolA = this->hatRectangle->nwest();
    hatSymbolA.x += 2;
    auto hatSymbolB = this->hatRectangle->seast();
    hatSymbolB.x--;
    hatSymbolB.y += 1;
    this->hatSymbol = new RightTriangle(
        hatSymbolA,
        hatSymbolB
    );
}

void HatShape::move(int a, int b)
{
    this->hatRectangle->move(a, b);
    this->hatVisor->move(a, b);
    this->hatSymbol->move(a, b);
}
