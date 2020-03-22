#include "death_room.hpp"
extern "C"
{
    #include "behavior_data.h"
    #include "game/object_helpers.h"
    #include "model_ids.h"
}
#include "dynamic_letters.hpp"
#include "colors.hpp"
#include "global.hpp"
#include "scores.hpp"
#include "rainbow_colors.hpp"
#include "fountain.hpp"
#include "music.hpp"
#include "cpp/fields.hpp"

static struct triplet DeadPos = { 0, -30, 0 };
static const char DeadText[] = "You Died";
static const char QuitText[] = "You Quit";
static const char WinText[]  = "You Did t";

static struct triplet ScorePos = { 0, -850, 0 };

static const float Scale = 0.95;

extern "C" void play_sequence(u8 player, u8 seqId, u16 fadeTimer);

void DeathRoom::Init()
{
    if (State == MS_ALIVE)
    {
        activeFlags = 0;
        return;
    }

    // The top sign
    {
        auto obj = spawn_object(this, MODEL_DYN_TEXT, bhvMillLetter);

        if (State == MS_DEAD)
        {
            F_DYNLET_TEXT(obj) = (int) DeadText;
            F_TEXT_COLOR(obj) = COLOR_RED;
        }
        if (State == MS_QUIT)
        {
            F_DYNLET_TEXT(obj) = (int) QuitText;
            F_TEXT_COLOR(obj) = COLOR_YELLOW;
        }
        if (State == MS_WIN)
        {
            F_DYNLET_TEXT(obj) = (int) WinText;
            F_TEXT_COLOR(obj) = COLOR_RAINBOW;
        }
        fPos(obj) = DeadPos;
        obj_scale(obj, Scale);
    }

    // The score sign
    {
        int score = Question;
        if (State == MS_DEAD)
        {
            if (score > 10)
                score = 10;
            else if (score > 5)
                score = 5;
            else
                score = 0;
        }
        else if (State == MS_QUIT)
        {
            score--;
        }
        else if (State == MS_WIN)
        {
            play_sequence(0, Music::MUSIC_TITLE, 0);
            score = 15;
        }
        
        auto obj = spawn_object(this, MODEL_DYN_TEXT, bhvMillLetter);
        F_DYNLET_TEXT(obj) = (int) Scores[score];
        F_TEXT_COLOR(obj) = COLOR_YELLOW;
        fPos(obj) = ScorePos;
        obj_scale(obj, Scale);
    }

    // The fountain
    if (State == MS_WIN)
    {
        {
            auto fountain = spawn_object(this, 0, bhvMillFountain);
            fPos(fountain) = { 0, -500, -400 };
            fountain->oBehParams2ndByte = 100;
        }
        {
            auto fountain = spawn_object(this, 0, bhvMillFountain);
            fPos(fountain) ={ -900, -1500, -1000 };
            fountain->oBehParams2ndByte = 150;
        }
        {
            auto fountain = spawn_object(this, 0, bhvMillFountain);
            fPos(fountain) = { 900,  -1500, -1000 };
            fountain->oBehParams2ndByte = 130;
        }
    }
}

void DeathRoom::Step()
{
    NextRainbowColor();
    if (oTimer > 100)
    {
        mPos = oPos;
    }
}

PROXY_OBJECT(mill, DeathRoom, Init)
PROXY_OBJECT(mill, DeathRoom, Step)