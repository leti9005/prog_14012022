#include <iostream>
#include "screen.h"
#include "shapes.h"

using namespace std;

// Дополнительная "сборная" фигура
// Лицо
class MyShape : public Rectangle
{
    // 10
    Line* l_eye; // левый глаз

    // 11
    Line* r_eye; // правый глаз

    // Rectangle* hat; point(0, 0), point(14, 5)
    // Line* brim; point(0,15), 17
    // HalfCircle beard; point(40,10), point(50,20)

    // rectangle hat(point(0, 0), point(14, 5));
    // line brim(point(0,15),17);
    // myshape face(point(15,10), point(27,18));
    // h_circle beard(point(40,10), point(50,20));

  public:
    MyShape(Point, Point);
    void draw();
    void move(int, int);
};

MyShape::MyShape(Point a, Point b) : Rectangle(a, b)
{
    int ll = neast().x - swest().x + 1;
    int hh = neast().y - swest().y + 1;
    this->l_eye = new Line(Point(swest().x + 2, swest().y + hh * 3 / 4), 2);
    this->r_eye = new Line(Point(swest().x + ll - 4, swest().y + hh * 3 / 4), 2);
}

void MyShape::draw()
{
    Rectangle::draw();
    Screen::put_point(
        (swest().x + neast().x) / 2,
        (swest().y + neast().y) / 2
    );
}

void MyShape::move(int a, int b)
{
    Rectangle::move(a, b);
    l_eye->move(a, b);
    r_eye->move(a, b);
}

int main()
{
    // Screen::screen_clear();

    auto p1 = new Rectangle(Point(0, 0), Point(14, 5));
    auto p2 = new Line(Point(0, 15), 17);
    auto p3 = new MyShape(Point(15, 10), Point(27, 18));
    auto p4 = new RightTriangle(Point(31, 5), Point(36, 1));
    auto p5 = new RightTriangle(Point(41, 5), Point(46, 1));
    auto p6 = new RightTriangle(Point(31, 15), Point(36, 11));
    auto p7 = new RightTriangle(Point(41, 15), Point(46, 11));

    Screen::shape_refresh();
    std::cin.get();

    p1->rotate_right();
    p4->flip_vertically();
    p6->flip_vertically();

    Screen::shape_refresh();
    std::cin.get();

    p3->move(30,0);
    p3->move(-10,10);

    up(p2, p3);
    up(p1, p2);
    leftUp(p4,p2);
    rightUp(p5,p2);
    leftDown(p7,p3);
    rightDown(p6,p3);
    p6->move(-6,4);
    p7->move(6,4);

    Screen::shape_refresh();
    std::cin.get();

    return 0;
}
