#pragma once

#include "../base/Point.h"
#include "../screen.h"
#include "../base/IRotatable.h"
#include "../base/IReflectable.h"

class RightTriangle : public IRotatable, public IReflectable
{

    /* ---
        nw        n         ne
        |    -
        |       -
        w         c         e
        |              -
        |                 -
        sw ------ s ------  se
     --- */

    Point h1, h2, a1;

  public:
    RightTriangle(Point a, Point b)
    {
        if (a.x <= b.x)
        {
            if (a.y >= b.y)
                h1 = a, h2 = b;
            else
                h1 = Point(a.x, b.y), h2 = Point(b.x, a.y);
        }
        else
        {
            if (b.y >= a.y)
                h1 = b, h2 = a;
            else
                h1 = Point(b.x, a.y), h2 = Point(a.x, b.y);
        }

        a1 = Point(h1.x, h2.y);
    }

    int width() const { return (max(h1.x, h2.x) - min(h1.x, h2.x)); }
    int margin_x() const { return min(min(h1.x, h2.x), a1.x); }
    int height() const { return (max(h1.y, h2.y) - min(h1.y, h2.y)); }
    int margin_y() const { return min(min(h1.y, h2.y), a1.y); }

    Point north() const { return Point(margin_x() + width() / 2, margin_y() + height()); }
    Point south() const { return Point(margin_x() + width() / 2, margin_y()); }
    Point west() const { return Point(margin_x(), margin_y() + height() / 2); }
    Point east() const { return Point(margin_x() + width(), margin_y() + height() / 2); }
    Point nwest() const { return Point(margin_x(), margin_y() + height()); }
    Point neast() const { return Point(margin_x() + width(), margin_y() + height()); }
    Point swest() const { return Point(margin_x(), margin_y()); }
    Point seast() const { return Point(margin_x() + width(), margin_y()); }

    // Поворот влево относительно sw
    void rotate_left()
    {
        int w = width();
        int h = height();

        h1.y -= h;
        a1.x += h;
        h2.x = h1.x + h;
        h2.y += w;
    }

    // Поворот вправо относительно se
    void rotate_right()
    {
        int w = width();
        int h = height();

        h1.y = a1.y + w;
        h1.x = h2.x;
        a1.y = h1.y;
        a1.x = h1.x-h;
        h2.x = a1.x;
    }

    // Отразить горизонтально
    void flip_horisontally()
    {
        if (a1.y == h1.y)
            a1.y = h2.y;
        else
            a1.y = h1.y;
        std::swap(h1.y, h2.y);
    }

    // Отразить вертикально
    void flip_vertically()
    {
        if (a1.x == h1.x)
            a1.x = h2.x;
        else
            a1.x = h1.x;
        std::swap(h1.x, h2.x);
    }

    void move(int a, int b)
    {
        h1.x += a;
        h2.x += a;
        a1.x += a;

        h1.y += b;
        h2.y += b;
        a1.y += b;
    }

    void draw();
};

void RightTriangle::draw()
{
    Screen::put_line(h1, a1);
    Screen::put_line(a1, h2);
    Screen::put_line(h1, h2);
}
