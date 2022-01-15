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

    HalfCircle* beard;

    // Rectangle* hat; point(0, 0), point(14, 5)
    // Line* brim; point(0,15), 17

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
    this->beard = new HalfCircle(Point(a.x + 1, a.y), Point(b.x - 1, b.y), false);
    down(this->beard, this);
}

void MyShape::draw()
{
    // Контур лица
    Rectangle::draw();

    // Нос
    Screen::put_point(
        (swest().x + neast().x) / 2,
        (swest().y + neast().y) / 2
    );

    down(this->beard, this);
}

void MyShape::move(int a, int b)
{
    Rectangle::move(a, b);
    this->l_eye->move(a, b);
    this->r_eye->move(a, b);
}

int main()
{
    // auto p1 = new Rectangle(Point(0, 0), Point(14, 5));
    // auto p2 = new Line(Point(0, 15), 17);
    auto p3 = new MyShape(Point(15, 10), Point(27, 18));

    // p1->rotate_right();
    // p3->move(-10, 10);

    // up(p2, p3);
    // up(p1, p2);

    Screen::shape_refresh();
    std::cin.get();

    return 0;
}
