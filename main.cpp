#include <iostream>
#include "screen.h"
#include "shapes.h"

using namespace std;

// Дополнительная "сборная" фигура
// Лицо
class MyShape : public Rectangle
{
    // 10
    RightTriangle* l_eye;

    // 11
    RightTriangle* r_eye;

    // 1
    RightTriangle* beard;

    Line* mouth;

  public:
    MyShape(Point, Point);
    void draw();
    void move(int, int);
    Point get_nose_point();
};

MyShape::MyShape(Point a, Point b) : Rectangle(a, b)
{
    int ll = neast().x - swest().x + 1;
    int hh = neast().y - swest().y + 1;

    auto eyesY = swest().y + hh * 3 / 4;
    auto nose = this->get_nose_point();

    this->l_eye = new RightTriangle(
        Point(
            swest().x + 2,
            eyesY
        ),
        Point(
            swest().x + 2 + 4,
            nose.y
        )
    );

    this->r_eye = new RightTriangle(
        Point(
            swest().x + ll - 3,
            eyesY
        ),
        Point(
            swest().x + ll - 4 - 3,
            nose.y
        )
    );
    this->r_eye->flip_vertically();

    this->mouth = new Line(Point(swest().x + 2, swest().y + hh / 4), ll - 4);
    this->beard = new RightTriangle(
        Point(swest().x, swest().y - 5),
        Point(seast().x, seast().y - 1)
    );
    this->beard->flip_horisontally();
}

Point MyShape::get_nose_point() {
    return Point(
        (swest().x + neast().x) / 2,
        (swest().y + neast().y) / 2
    );
}

void MyShape::draw()
{
    Rectangle::draw();
    Screen::put_point(this->get_nose_point());
    this->beard->flip_horisontally();
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

    auto person = new MyShape(Point(7, 5), Point(25, 15));
    person->move(10, 3);

    up(hatVisor, person);
    up(hatRectangle, hatVisor);

    Screen::shape_refresh();
    std::cin.get();

    return 0;
}
