#include "lights_ctl.hpp"

#include <PR/gbi.h>

Color::Color(u8 c) : Color(c, c, c) { }

Color::Color(u8 r, u8 g , u8 b) : r(r), g(g), b(b) { }

void Color::To(u8 l[3])
{
    l[0] = r;
    l[1] = g;
    l[2] = b;
}

Color Color::operator+(const Color& o)
{
    return { (u8) (r + o.r), (u8) (g + o.g), (u8) (b + o.b) };
}

Color Color::operator-(const Color& o)
{
    return { (u8) (r - o.r), (u8) (g - o.g), (u8) (b - o.b) };
}

Color Color::operator/(float v)
{
    return { (u8) (r / v), (u8) (g / v), (u8) (b / v) };
}

Color Color::operator*(float v)
{
    return { (u8) (r * v), (u8) (g * v), (u8) (b * v) };
}

void LightsCtl::Set(Color c, Lights1& l)
{
    auto& ambient = l.a;
    (c / 2).To(ambient.l.col);
    (c / 2).To(ambient.l.colc);

    auto& light = l.l[0];
    c.To(light.l.col);
    c.To(light.l.colc);
}
