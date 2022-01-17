#include <iostream>
#include "screen.h"
#include "utils.h"
#include "shapes/HatShape.h"
#include "shapes/PersonShape.h"

using namespace std;


int main()
{
    auto hat = new HatShape(Point(0, 0), Point(14, 5));
    auto person = new PersonShape(Point(7, 5), Point(25, 15));
    person->move(10, 3);

    up(hat, person);

    Screen::shape_refresh();
    std::cin.get();

    return 0;
}
