#pragma once

struct Point
{
public:
    int x, y;

    Point() {}
    Point(int xx, int yy) : x(xx), y(yy) {}

    std::string to_string() {
        return std::to_string(x) + " " + std::to_string(y);
    }
};
