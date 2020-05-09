#include "world.hpp"
extern "C"
{
    #include "math.h"
}
#include "lights_ctl.hpp"
#include "color_pads.hpp"

Color sColors[] = {
    { 0xa0, 0xff, 0xa0 },
    { 0xff, 0xa0, 0xa0 },
    { 0xa0, 0xa0, 0xff },
    { 0xff, 0xff, 0xff },
};

namespace World
{
    static int Timer;

    void Advance()
    {
        Timer++;
    }

    void Wave(int world, int offset, float amount)
    {
        float fluct = sinf((float) Timer / amount);
        auto color = sColors[world] * (0xE0 + fluct * 0x1F - offset * 0x20);
        SetColorWorlds(color.r, color.g, color.b);
    }

    static int GetFluct(int t)
    {
        if (t < 5)
            return t - 2;
        else
            return 6 - t;
    }
    
    void Flashy()
    {
        if (Timer % 8 == 0)
            FlashyScroll(0, 64);
    }

    void SlowTremble(int world, int offset, int localTimer)
    {
        int fluct = (localTimer / 30) % 2;
        auto color = sColors[world] * ((224.f/256.f) + fluct * (31.f/256.f) - offset * (32.f/256.f));
        SetColorWorlds(color.r, color.g, color.b);
    }

    void Tremble(int world, int offset)
    {
        int fluct = GetFluct(Timer % 8);
        auto color = sColors[world] * ((224.f/256.f) + fluct * (31.f/256.f) - offset * (32.f/256.f));
        SetColorWorlds(color.r, color.g, color.b);
    }
}