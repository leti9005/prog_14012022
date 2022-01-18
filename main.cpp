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

    try
    {
        cout << "Try moving the shape outside of screen" << endl;
        person->move(100000, 3);
        Screen::shape_refresh();
    }
    catch (OutsideOfScreenException& e)
    {
        std::cerr << e.get_error_message() << '\n';
    }

    std::cin.get();
    cout << "Try creating bad triangle" << endl;
    Screen::screen_clear();

    try
    {
        RightTriangle badTriangle(
            Point(-124124, -1), Point(-100, 1)
        );
    }
    catch (RightTriangle::Exception e)
    {
        std::cerr << e.what() << '\n' << e.get_points_message() << endl;
    }

    return 0;
}
