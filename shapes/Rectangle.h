#pragma once

#include "../base/Point.h"
#include "../screen.h"
#include "../base/IRotatable.h"
#include "../base/IReflectable.h"

class Rectangle : public IRotatable
{
    /* ---
        nw ------ n ------ ne
        |		           |
        |		           |
        w	     c         e
        | 		           |
        |		           |
        sw ------ s ------ se
     --- */

    Point sw, ne;

  public:
    Rectangle(Point, Point);

    Point north() const { return Point((sw.x + ne.x) / 2, ne.y); }
    Point south() const { return Point((sw.x + ne.x) / 2, sw.y); }
    Point east() const { return Point(sw.x, (sw.y + ne.y) / 2); }
    Point west() const { return Point(ne.x, (sw.y + ne.y) / 2); }
    Point seast() const { return Point(ne.x, sw.y); }
    Point nwest() const { return Point(sw.x, ne.y); }
    Point neast() const { return ne; }
    Point swest() const { return sw; }

    // Поворот вправо относительно se
    void rotate_right()
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        sw.x = ne.x - h * 2;
        ne.y = sw.y + w / 2;
    }

    // Поворот влево относительно sw
    void rotate_left()
    {
        int w = ne.x - sw.x, h = ne.y - sw.y;
        ne.x = sw.x + h * 2;
        ne.y = sw.y + w / 2;
    }

    void move(int a, int b)
    {
        sw.x += a;
        sw.y += b;
        ne.x += a;
        ne.y += b;
    }

    void draw();
};

Rectangle::Rectangle(Point a, Point b)
{
    if (a.x <= b.x)
    {
        if (a.y <= b.y)
            sw = a, ne = b;
        else
            sw = Point(a.x, b.y), ne = Point(b.x, a.y);
    }
    else
    {
        if (a.y <= b.y)
            sw = Point(b.x, a.y), ne = Point(a.x, b.y);
        else
            sw = b, ne = a;
    }
}

void Rectangle::draw()
{
    auto nw = nwest();
    auto se = seast();

    Screen::put_line(nw, ne);
    Screen::put_line(ne, se);
    Screen::put_line(se, sw);
    Screen::put_line(sw, nw);
}
