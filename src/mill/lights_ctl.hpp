#pragma once

#include "types.h"

struct Color
{
public:
    Color(u8);
    Color(u8, u8, u8);

    void To(u8 l[3]);
    
    Color operator+(const Color&);
    Color operator-(const Color&);
    Color operator/(float);
    Color operator*(float);

    u8 r;
    u8 g;
    u8 b;
};

namespace LightsCtl
{
    void Set(Color l, Lights1&);
};
