#pragma once

#include "../base/Point.h"
#include "../screen.h"
#include "../base/IRotatable.h"
#include "../base/IReflectable.h"

class Line : public IShape
{
    Point w, e;

public:
    Line(Point a, Point b) : w(a), e(b){};
    Line(Point a, int L) : w(Point(a.x + L - 1, a.y)), e(a) {};

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
