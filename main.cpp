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

    // рот
    Line* mouth;

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
    this->mouth = new Line(Point(swest().x + 2, swest().y + hh / 4), ll - 4);
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
    this->mouth->move(a, b);
    this->beard->move(a, b);
}

int main()
{
    auto hatRectangle = new Rectangle(Point(0, 0), Point(14, 5));
    hatRectangle->rotate_right();

    auto hatVisor = new Line(Point(0, 15), 25);
    auto person = new MyShape(Point(15, 10), Point(27, 18));

    person->move(-5, 0);

    up(hatVisor, person);
    up(hatRectangle, hatVisor);

    Screen::shape_refresh();
    std::cin.get();

    return 0;
}
