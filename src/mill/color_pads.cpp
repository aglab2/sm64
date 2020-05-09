#include "color_pads.hpp"
extern "C"
{
    #include "types.h"
    #include "game/memory.h"
}
#include "lights_ctl.hpp"
#include "cpp/virtual.hpp"

extern Lights1 bob_answer1_lights;
extern Lights1 bob_answer2_lights;
extern Lights1 bob_answer3_lights;
extern Lights1 bob_answer4_lights;
extern Lights1 bob__5050_lights;
extern Lights1 bob_audience_lights;
extern Lights1 bob_scroll_lights;
extern Lights1 bob_phone_lights;
extern Lights1 bob__1_f3d_lights;

extern Gfx mat_bob_scroll[];

/*
0	gsDPPipeSync(),
1	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
2	gsSPTexture(65535, 65535, 0, 0, 1),
3	gsDPTileSync(),
4	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, bob__3_rgba16),
5	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
6	gsDPLoadSync(),
7	gsDPLoadTile(7, 0, 0, 124, 124),
8	gsDPPipeSync(),
9	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 8, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0),
10	gsDPSetTileSize(0, 0, 0, 124, 124),
11	gsSPSetLights1(bob_scroll_lights),
12	gsSPEndDisplayList(),
 */
#define TO_SETTILESIZE(gfx) ((gfx) + 10)

static Lights1* cmdsAnswer[] = { &bob_answer1_lights, &bob_answer2_lights, &bob_answer3_lights, &bob_answer4_lights };
static Lights1* cmdsLifelines[] = { &bob__5050_lights, &bob_audience_lights, &bob_phone_lights };
static auto cmdsWorlds = &bob__1_f3d_lights;
static auto cmdsFlashy = TO_SETTILESIZE(&bob_scroll_lights);

void SetColorAnswer(int n, unsigned char r, unsigned char g, unsigned char b)
{
    auto val = toVirtual(cmdsAnswer[n]);
    return LightsCtl::Set({r, g, b}, *val);
}

void SetColorLifelines(int n, unsigned char r, unsigned char g, unsigned char b)
{
    auto val = toVirtual(cmdsLifelines[n]);
    return LightsCtl::Set({r, g, b}, *val);
}

void SetColorWorlds(unsigned char r, unsigned char g, unsigned char b)
{
    auto val = toVirtual(cmdsWorlds);
    return LightsCtl::Set({r, g, b}, *val);
}

void FlashyScroll(int x_off, int y_off)
{
    char* ptr = (char*) segmented_to_virtual(cmdsFlashy);

    int b1 = ptr[1];
    int b2 = ptr[2];
    int b3 = ptr[3];

    int x = ((b1 << 4) & 0xFF0) | ((b2 >> 4) & 0x00F);
    int y = ((b2 << 4) & 0xF00) | b3;

    x += x_off;
    y += y_off;

    b1 = (x & 0xFF0) >> 4;
    b2 = ((x & 0x00F) << 4) | ((y & 0xF00) >> 8);
    b3 = y & 0xFF;

    ptr[1] = b1;
    ptr[2] = b2;
    ptr[3] = b3;
}