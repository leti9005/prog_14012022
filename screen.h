#pragma once

#include <iostream>
#include "base/Point.h"
#include "base/IShape.h"

const int XMAX = 80; // Размер экрана
const int YMAX = 30;

// Цвет
enum Color
{
    Black = '*',
    White = ' '
};

char _screen[XMAX][YMAX];

// Экран
struct Screen {
    // Проверка попадания на экран
    static int on_screen(int a, int b)
    {
        return 0 <= a && a < XMAX && 0 <= b && b < YMAX;
    }

    static void put_point(int a, int b)
    {
        if (on_screen(a, b))
            _screen[a][b] = Color::Black;
    }

    static void put_point(Point p)
    {
        Screen::put_point(p.x, p.y);
    }

    // Перерисовка всех фигур
    static void shape_refresh()
    {
        Screen::screen_clear();
        for (auto p: IShape::shapes)
        {
            p->draw();
        }

        Screen::screen_refresh();
    }

    static void screen_clear()
    {
        for (int y = 0; y < YMAX; y++)
            for (int x = 0; x < XMAX; x++)
                _screen[x][y] = Color::White;
    }

    /* ---
    Рисование отрезка прямой (x0,y0) - (x1,y1).
    Уравнение прямой: b(x-x0) + a(y-y0) = 0.
    Минимизируется величина abs(eps),
    где eps = 2*(b(x-x0)) + a(y-y0).
    --- */
    static void put_line(int x0, int y0, int x1, int y1)
    {
        int dx = 1;
        int a = x1 - x0;

        if (a < 0)
            dx = -1, a = -a;
        int dy = 1;
        int b = y1 - y0;

        if (b < 0)
            dy = -1, b = -b;

        int two_a = 2 * a;
        int two_b = 2 * b;
        int xcrit = -b + two_a;
        int eps = 0;

        for (;;)
        {
            Screen::put_point(x0, y0);
            if (x0 == x1 && y0 == y1)
                break;
            if (eps <= xcrit)
                x0 += dx, eps += two_b;
            if (eps >= a || a < b)
                y0 += dy, eps -= two_a;
        }
    }

    // Вывод линии
    static void put_line(Point a, Point b) {
        Screen::put_line(a.x, a.y, b.x, b.y);
    }


private:
    static void screen_refresh()
    {
        for (int y = YMAX - 1; 0 <= y; --y)
        {                                  // с верхней строки до нижней
            for (int x = 0; x < XMAX; ++x) // от левого столбца до правого
            {
                std::cout << _screen[x][y];
            }

            std::cout << std::endl;
        }
    }
};
