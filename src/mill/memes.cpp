#include "memes.hpp"
extern "C"
{
    #include "engine/behavior_script.h"
    #include "game/print.h"
    #include "game/level_update.h"
    #include "sm64.h"
}
#include "cpp/fields.hpp"

#define PREV_ACT    OBJECT_FIELD_S32(0x1b)
#define IS_RED      OBJECT_FIELD_S32(0x1c)
#define FIRSTY_CNT  OBJECT_FIELD_S32(0x1d)
#define CAN_RED     OBJECT_FIELD_S32(0x1e)
#define DORRIE_TIME OBJECT_FIELD_S32(0x1f)

void Memes::Init()
{

}

const char* DorriesText[] = { "RIGHTDORRIE"
                            , "LEFTDORRIE"
                            , "COMFYDORRIE"
                            , "YEETDORRIE"
                            , "HIGHDORRIE"
                            , "CRAFTDORRIE"
                            , "CRAFTW"
                            , "AYY LMAO" };

void Memes::Dorrie()
{
    DORRIE_TIME += RandomU16() % 10;
    if (DORRIE_TIME > 3000)
    {
        DORRIE_TIME = 0;
        int idx = sizeof(DorriesText) / sizeof(DorriesText[0]);
        print_text_centered(160, 200, DorriesText[RandomU16() % idx]);
    }
}

void Memes::Firsty()
{
    auto act = gMarioStates->action;
    if (act != PREV_ACT)
    {
        if (act != ACT_WALL_KICK_AIR && act != ACT_AIR_HIT_WALL)
        {
            if (FIRSTY_CNT != 0 && !IS_RED)
            {
                IS_RED = true;
            }
            else
            {
                IS_RED = false;
                FIRSTY_CNT = 0;
            }
        }
        if (PREV_ACT == ACT_AIR_HIT_WALL && act == ACT_WALL_KICK_AIR)
        {
            if (IS_RED)
            {
                IS_RED = false;
                FIRSTY_CNT = 0;
            }
            FIRSTY_CNT++;
        }
        PREV_ACT = act;
    }
    if (IS_RED)
        print_text_centered(140, 200, "HECK");

    if (FIRSTY_CNT > 0)
        print_text_fmt_int(180, 200, "FIRSTIES %d", FIRSTY_CNT);
}

void Memes::Step()
{
    Firsty();
    Dorrie();
}

PROXY_OBJECT(mill, Memes, Init);
PROXY_OBJECT(mill, Memes, Step);