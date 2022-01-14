#pragma once

#include "Point.h"
#include "screen.h"
#include "IRotatable.h"
#include "IReflectable.h"

using namespace std;

/* ---
Отрезок прямой ["w", "e" ].
north( ) определяет точку "выше центра отрезка и так далеко на север, как самая его северная точка", и т. п.
 --- */
class Line : public IShape
{
    Point w, e;

public:
    Line(Point a, Point b) : w(a), e(b){};
    Line(Point a, int L) : w(Point(a.x + L - 1, a.y)), e(a){};

    Point north() const { return Point((w.x + e.x) / 2, (w.y + e.y) / 2); }
    Point south() const { return Point((w.x + e.x) / 2, (w.y + e.y) / 2); }
    Point east() const { return e; }
    Point west() const { return w; }
    Point neast() const { return e; }
    Point seast() const { return e; }
    Point nwest() const { return w; }
    Point swest() const { return w; }

    void move(int a, int b)
    {
        w.x += a;
        w.y += b;
        e.x += a;
        e.y += b;
    }

    void draw()
    {
        Screen::put_line(w, e);
    }
};

// Прямоугольник
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
    Point neast() const { return ne; }
    Point seast() const { return Point(sw.x, ne.y); }
    Point nwest() const { return Point(ne.x, sw.y); }
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
    Point nw(sw.x, ne.y);
    Point se(ne.x, sw.y);
    Screen::put_line(nw, ne);
    Screen::put_line(ne, se);
    Screen::put_line(se, sw);
    Screen::put_line(sw, nw);
}

// Прямоугольный треугольник
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
        h1.y += b;
        h2.x += a;
        h2.y += b;
        a1.x += a;
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

// Поместить p над q
void up(IShape* p, const IShape* q)
{
    Point n = q->north();
    Point s = p->south();
    p->move(n.x - s.x, n.y - s.y + 1);
}

void leftUp(IShape* p, const IShape* q)
{
    p->move(q->nwest().x - p->swest().x, q->nwest().y - p->swest().y + 1);
}

void rightUp(IShape* p, const IShape* q)
{
    p->move(q->neast().x - p->seast().x, q->nwest().y - p->swest().y + 1);
}

void rightDown(IShape* p, const IShape* q)
{
    p->move(q->east().x - p->west().x, q->swest().y - p->nwest().y);
}

void leftDown(IShape* p, const IShape* q)
{
    p->move(q->west().x - p->east().x, q->swest().y - p->nwest().y);
}
