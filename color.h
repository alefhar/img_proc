#ifndef COLOR_H
#define COLOR_H

#include <iostream>

using namespace std;

class Color
{
public:
    int r;
    int g;
    int b;

    Color()
    {
        r = g = b = 0;
    }

    Color(int v)
    {
        r = g = b = v;
    }

    Color(int _r, int _g, int _b)
    {
        r = _r;
        g = _g;
        b = _b;
    }

    ~Color()
    {
    }

    friend bool operator<(const Color &a, const Color &b)
    {
        float grey_a = a.r * .212671f + a.g * .715160 + a.b * .072169;
        float grey_b = b.r * .212671f + b.g * .715160 + b.b * .072169;
        return grey_a < grey_b;
    }

    friend Color operator/(const Color &a, const int v)
    {
        return Color(a.r / v, a.g / v, a.b / v);
    }

    friend Color operator-(const Color &a, const Color &b)
    {
        return Color(a.r - b.r, a.g - b.g, a.b - b.b);
    }

    friend Color operator-(int a, const Color &b)
    {
        return Color(a - b.r, a - b.g, a - b.b);
    }

    friend Color operator+(const Color &a, const Color &b)
    {
        return Color(a.r + b.r, a.g + b.g, a.b + b.b);
    }

    friend ostream& operator<<(ostream& out, const Color &c)
    {
        out << c.r << ' ' << c.g << ' ' << c.b;
        return out;
    }

    friend istream& operator>>(istream& in, Color &c)
    {
        in >> c.r >> c.g >> c.b;
        return in;
    }
};

#endif // COLOR_H
