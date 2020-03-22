#include "mill_ctl.hpp"
extern "C"
{
    #include "behavior_data.h"
    #include "game/game.h"
    #include "game/camera.h"
    #include "game/print.h"
    #include "game/object_helpers.h"
    #include "game/spawn_sound.h"
    #include "engine/behavior_script.h"
    #include "model_ids.h"
}
#include "warp.hpp"
#include "color_pads.hpp"
#include "numbers_input.hpp"
#include "numbers_writer.hpp"
#include "World.hpp"
#include "string_fit.hpp"
#include "rainbow_colors.hpp"
#include "colors.hpp"
#include "global.hpp"
#include "music.hpp"
#include "dynamic_letters.hpp"
#include "numbers_writer.hpp"
#include "cpp/fields.hpp"

extern s16 s8DirModeYawOffset;
extern s16 sSelectionFlags;

#pragma pack(push, 1)
struct AnswerInfo
{
    char txt[63];
    char nofit;
};

struct QuestionInfo
{
    char question[253];
    char musicOverride;
    char nofit;
    char correctAnswer;
    struct AnswerInfo answers[4];
};
#pragma pack(pop)

#define QUESTION_NUMBER oBehParams2ndByte
#define COUNTDOWN_X     OBJECT_FIELD_S32(0x1b)
#define COUNTDOWN_Y     OBJECT_FIELD_S32(0x1c)
#define SONG_ID  OBJECT_FIELD_S32(0x1d)
#define SONG_LEN OBJECT_FIELD_S32(0x1e)
#define oSubSubAction OBJECT_FIELD_S32(0x1f)
#define oPickedAnswer OBJECT_FIELD_S32(0x20)

#define CHILDREN (&OBJECT_FIELD_OBJ(0x48))

#define DYNAMIC_LETTERS (CHILDREN + 6)

#define QUESTION_INFOS_ROM 0x3ff0000
#define QUESTION_INFOS ((struct QuestionInfo*)(0x807f0000))
#define QUESTION_INFO (&QUESTION_INFOS[QUESTION_NUMBER - 1])
#define QUESTION_CORR (QUESTION_INFO->correctAnswer - 1)

extern "C" void play_sequence(u8 player, u8 seqId, u16 fadeTimer);

template<typename T, int sz>
static constexpr int size(T(&)[sz])
{
    return sz;
}

static const triplet CoatsPos[] = {
    { -1193, 0, -1110 }, 
    { -446, 0, -1110 }, 
    { 446, 0, -1110 }, 
    { 1193, 0, -1110 },
};

static const struct triplet QuestionPos = { 0, 654, -717 };

static const struct triplet LettersPos[] = {
    { -1193, 190, -886 },
    { -446,  190, -886 }, 
    { 446,   190, -886 }, 
    { 1193,  190, -886 },
};

static const int Collisions[] = { 0x7B, 0x15, 0x29, 0x30 };

enum LifeLines
{
    LL_FIFTYFIFTY = 0,
    LL_AUDIENCE,
    LL_CALLFRIEND,
};

static const int LifelinesCollision[]  = { 0x35, 0x36, 0x37 };

enum Actions
{
    PREPARE,
    UNVEIL,
    PICKING,
    FINAL,
    RESULTS,
    WALKAWAY,

    LIFELINES,
    FIFTYFIFTY = LIFELINES,
    AUDIENCE,
    CALLFRIEND,
    AUDIENCE_PICKING,
    AUDIENCE_PICKINGAFTER,
    CALLFRIEND_CD,
};

void MillCtl::FreezeMario()
{
    mPos = oPos;
}

void MillCtl::MaskInputs(int inputs)
{
    gPlayer1Controller->buttonDown    &= ~(inputs);
    gPlayer1Controller->buttonPressed &= ~(inputs);
}

void MillCtl::SetCamera()
{
    sSelectionFlags = 4;
    gCameraMovementFlags = 10;
    PickedAngle(10);
}

void MillCtl::SetMusic(int music)
{
    SONG_ID  = music;
    SONG_LEN = 0;
    
    play_sequence(0, music, 0);
}

void MillCtl::SetGamingMusic()
{
    int track = 0;
    if (QUESTION_INFO->musicOverride)
    {
        track = QUESTION_INFO->musicOverride;
    }
    else
    {
        track = Music::GetGameMusic(GetWorld(QUESTION_NUMBER), 
                                    GetLevel(QUESTION_NUMBER));
    }
    SetMusic(track);
}

// culprit :(

static int Culprits[] = { 4700, 4450, 4200, 3950, 3750 };

void MillCtl::FixMusic()
{
    SONG_LEN++;
    if (SONG_ID == Music::MUSIC_P1)
    {
        if (SONG_LEN > 3250)
            SetMusic(SONG_ID);
    }
    if (Music::MUSIC_P2 <= SONG_ID  && SONG_ID <= Music::MUSIC_P4_END)
    {
        if (SONG_LEN > Culprits[GetLevel(QUESTION_NUMBER)])
            SetMusic(SONG_ID);
    }

    //PrintInt(20, 20, "%d", SONG_LEN);
}

void MillCtl::SetWinMusic()
{
    int track = Music::GetWinMusic(GetLevel(QUESTION_NUMBER));
    SetMusic(track);
}

void MillCtl::PrintHint(const char* msg, int offset)
{
    print_text_centered(160, 20 + offset, msg);
}

void MillCtl::Init()
{
    Question = QUESTION_NUMBER;

    SetCamera();
    for (int i = 0; i <= 3; i++)
        SetColorAnswer(i, 0xff, 0xff, 0xff);

    for (int i = 0; i < size(CoatsPos); i++)
    {
        CHILDREN[i] = spawn_object(this, MODEL_VEIL, bhvStaticObject);
        fPos(CHILDREN[i]) = CoatsPos[i];
    }

    QuestionInfo* info = &QUESTION_INFOS[QUESTION_NUMBER - 1];

    {
        float scale;
        if (info->nofit)
        {
            scale = StringFit::GetOptScale(info->question);
        }
        else
        {
            scale = StringFit::Fit(info->question);
        }

        auto obj = spawn_object(this, MODEL_DYN_TEXT, bhvMillLetter);
        F_DYNLET_TEXT(obj) = (int) info->question;
        F_TEXT_COLOR(obj) = GetWorld(QUESTION_NUMBER);
        fPos(obj) = QuestionPos;
        obj_scale(obj, scale);
    }

    for (int i = 0; i < 4; i++)
    {
        AnswerInfo* ai = &info->answers[i];
        float scale;
        if (ai->nofit)
            scale = StringFit::GetOptScale(ai->txt);
        else
            scale = StringFit::Fit(ai->txt);

        scale *= 0.61f;

        DYNAMIC_LETTERS[i] = spawn_object(this, MODEL_DYN_TEXT, bhvMillLetter);
        F_DYNLET_TEXT(DYNAMIC_LETTERS[i]) =  (int) ai->txt;
        F_TEXT_COLOR(DYNAMIC_LETTERS[i]) = GetWorld(QUESTION_NUMBER);
        fPos(DYNAMIC_LETTERS[i]) = LettersPos[i];
        obj_scale(DYNAMIC_LETTERS[i], scale);
    }
}

void MillCtl::Prepare()
{
    FreezeMario();
    if (QUESTION_NUMBER < 6)
    {
        SetGamingMusic();
        for (int i = 0; i < size(CoatsPos); i++)
            CHILDREN[i]->activeFlags = 0;
        oAction = PICKING;
    }
    else
    {
        if (oTimer == 0)
            SetMusic(Music::MUSIC_LETSPLAY);

        if (oTimer < 105)
            return;

        SetGamingMusic();
        oAction = UNVEIL;
    }
}

void MillCtl::PickedAngle(int pick)
{
    if (pick == 0) s8DirModeYawOffset =  0x2000;
    if (pick == 1) s8DirModeYawOffset =  0x1000;
    if (pick == 2) s8DirModeYawOffset = -0x1000;
    if (pick == 3) s8DirModeYawOffset = -0x2000;
    if (pick > 3) s8DirModeYawOffset =  0;
    MaskInputs(R_CBUTTONS | L_CBUTTONS);
}

int MillCtl::GetWorld(int q)
{
    if (q <= 5)  return 0;
    if (q <= 10) return 1;
    if (q < 15)  return 2;
    return 3;
}

int MillCtl::GetLevel(int q)
{
    if (q == 15)
        return 0;
    
    return (q - 1) % 5;
}

void MillCtl::Unveil()
{
    FreezeMario();

    if (oSubAction < 4)
    {
        PrintHint("Press Start to show");
        if (gPlayer1Controller->buttonPressed & START_BUTTON)
        {
            if (!oSubSubAction)
            {
                CHILDREN[oSubAction]->activeFlags = 0;
                oSubAction++;
                oSubSubAction = 1;
            }
        }
        else
        {
            oSubSubAction = 0;
        }
    }
    else
    {
        oAction = PICKING;
    }

    PickedAngle(oSubAction - 1);
}

void MillCtl::Picking()
{
    for (int i = 0; i < size(Collisions); i++)
        if (gMarioStates->floor->type == Collisions[i])
        {
            PrintHint("Start to set final answer");
            if (gPlayer1Controller->buttonPressed & START_BUTTON)
            {
                oPickedAnswer = i;
                SetColorAnswer(oPickedAnswer, 0xFF, 0x7F, 0x00);
                if (QUESTION_NUMBER >= 5)
                {
                    int track = Music::GetFinalMusic(GetLevel(QUESTION_NUMBER));
                    SetMusic(track);
                }

                oAction = FINAL;
            }
        }
        
    for (int i = 0; i < size(LifelinesCollision); i++)
        if (gMarioStates->floor->type == LifelinesCollision[i])
        {
            PrintHint("Start to use lifeline");
            if (gPlayer1Controller->buttonPressed & START_BUTTON)
            {
                if (LIFELINES + i != FIFTYFIFTY)
                    SetMusic(Music::MUSIC_AWAIT);
                oAction = LIFELINES + i;
            }
        }
    
    if (gMarioStates->floor->type == 0)
        if (gPlayer1Controller->buttonPressed & L_TRIG)
        {
            SetMusic(0);
            oAction = WALKAWAY;
        }
}

void MillCtl::Final()
{
    FreezeMario();
    PickedAngle(oPickedAnswer);
    if (QUESTION_NUMBER > 5)
    {
        PrintHint("R to show correct");
        if (!(gPlayer1Controller->buttonPressed & R_TRIG))
            return;
    }
    
    PickedAngle(QUESTION_CORR);

    SetColorAnswer(oPickedAnswer, 0xFF, 0x00, 0x00);
    SetColorAnswer(QUESTION_CORR, 0x00, 0xFF, 0x00);

    F_TEXT_COLOR(DYNAMIC_LETTERS[oPickedAnswer]) = COLOR_RED;
     
    if (oPickedAnswer == QUESTION_CORR)
    {
        F_TEXT_COLOR(DYNAMIC_LETTERS[oPickedAnswer]) = COLOR_RAINBOW;
        SetWinMusic();
    }
    else
    {
        F_TEXT_COLOR(DYNAMIC_LETTERS[oPickedAnswer]) = COLOR_GREEN;
        int track = Music::GetLoseMusic(GetWorld(QUESTION_NUMBER), GetLevel(QUESTION_NUMBER));
        SetMusic(track);
    }

    oAction = RESULTS;
}

void MillCtl::Results()
{
    NextRainbowColor();
    bool wrongAnswer = oPickedAnswer != QUESTION_CORR;

    FreezeMario();
    PickedAngle(QUESTION_CORR);

    PrintHint("L to finish game");
    if (gPlayer1Controller->buttonPressed & L_TRIG)
    {
        if (wrongAnswer)
        {
            State = MS_DEAD;
            gMarioStates->health = 0;
        }
        else
        {
            if (QUESTION_NUMBER == 15)
                State = MS_WIN;

            TriggerWarp(72);
        }
    }
}

void MillCtl::WalkAway()
{
    FreezeMario();
    
    PrintHint("Start to finish game", 20);
    PrintHint("B to cancel");
    if (gPlayer1Controller->buttonPressed & START_BUTTON)
    {
        State = MS_QUIT;
        TriggerWarp(69);
    }
    
    if (gPlayer1Controller->buttonPressed & B_BUTTON)
    {
        SetGamingMusic();
        oAction = PICKING;
    }
}

void MillCtl::FiftyFifty()
{
    int answerToLeave;
    do
    {
        answerToLeave = RandomU16() % 4;
    } while (answerToLeave == QUESTION_CORR);
    
    for (int i = 0; i < size(CoatsPos); i++)
    {
        if (i == QUESTION_CORR || i == answerToLeave)
            continue;

        mPos = oPos;
        s8DirModeYawOffset = 0;
        
        SetColorAnswer(i, 0x40, 0x40, 0x40);
        auto child = spawn_object(this, MODEL_VEIL, bhvStaticObject);
        fPos(child) = CoatsPos[i];
    }

    oAction = PICKING;
    create_sound_spawner(0x2439ff81);
    SetColorLifelines(FIFTYFIFTY - LIFELINES, 0x40, 0x40, 0x40);
}

void MillCtl::Audience()
{
    if (oTimer == 0)
        NumbersInput::Init();
        
    FreezeMario();
    s8DirModeYawOffset = 0;

    PrintHint("Press R to start audience");
    if (gPlayer1Controller->buttonPressed & R_TRIG)
    {
        SetMusic(Music::MUSIC_TIMEOUT);
        oAction = AUDIENCE_PICKING;
    }
}

void MillCtl::AudiencePicking()
{
    if (oTimer > 30 * 25)
    {
        SetMusic(Music::MUSIC_AWAIT);
        oAction = AUDIENCE_PICKINGAFTER;
    }
}

void MillCtl::AudienceAfterPicking()
{
    FreezeMario();
    NumbersInput::Step();

    PrintHint("Press R to finish");
    if (gPlayer1Controller->buttonPressed & R_TRIG)
    {
        auto writer = spawn_object(this, 0, bhvMillNumbersWriter);
        NumbersInput::GetResults(fNumbersWriterNumbers(writer));

        // spawn the things

        SetGamingMusic();
        oAction = PICKING;
        SetColorLifelines(AUDIENCE - LIFELINES, 0x40, 0x40, 0x40);
    }
}

void MillCtl::CallFriend()
{
    mPos = oPos;
    s8DirModeYawOffset = 0;

    PrintHint("Press R to start call");
    if (gPlayer1Controller->buttonPressed & R_TRIG)
    {
        SetMusic(Music::MUSIC_TIMEOUT);
        s8DirModeYawOffset = 0;
        oAction = CALLFRIEND_CD;
    }
}

void MillCtl::CallFriendCountDown()
{
    FreezeMario();
    if (oTimer % 30 == 0)
    {
        COUNTDOWN_X = 20 + RandomU16() % 260;
        COUNTDOWN_Y = 20 + RandomU16() % 180;
    }

    print_text_fmt_int(COUNTDOWN_X + RandomU16() % 5, COUNTDOWN_Y + RandomU16() % 5, "%d", 30 - (oTimer / 30));

    if (oTimer == 30 * 30)
    {
        SetGamingMusic();
        oAction = PICKING;
        SetColorLifelines(CALLFRIEND - LIFELINES, 0x40, 0x40, 0x40);
    }
}

void MillCtl::Step()
{
    RandomU16();
    FixMusic();

    World::Advance();
    switch (oAction)
    {
        case PREPARE:  
            World::Flashy();
        case AUDIENCE_PICKING:
        case CALLFRIEND_CD:
            World::SlowTremble(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5, oTimer);
        break;

        case WALKAWAY:
        case FINAL:
            break;
        case RESULTS:
        {
        bool wrongAnswer = oPickedAnswer != QUESTION_CORR;
            if (!wrongAnswer)
            {
                World::Flashy();
                int maxTime = GetLevel(QUESTION_NUMBER) == 4 ? 200 : 100;
                if (oTimer < maxTime)
                {
                    World::Tremble(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5);
                }
                else
                {
                    World::Wave(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5, 20);
                }
            }
        }
        break;
        default:
            World::Wave(GetWorld(QUESTION_NUMBER), (QUESTION_NUMBER - 1) % 5, 20);
        break;
    }

    switch (oAction)
    {
        case PREPARE:
            Prepare();
        break;
        case UNVEIL:
            Unveil();
        break;
        case PICKING:
            Picking();
        break;
        case FINAL:
            Final();
        break;
        case RESULTS:
            Results();
        break;
        case WALKAWAY:
            WalkAway();
        break;
        case FIFTYFIFTY:
            FiftyFifty();
        break;
        case AUDIENCE:
            Audience();
        break;
        case AUDIENCE_PICKING:
            AudiencePicking();
        break;
        case AUDIENCE_PICKINGAFTER:
            AudienceAfterPicking();
        break;
        case CALLFRIEND:
            CallFriend();
        break;
        case CALLFRIEND_CD:
            CallFriendCountDown();
        break;
    };
    
    MaskInputs(START_BUTTON | U_CBUTTONS | D_CBUTTONS | R_TRIG | U_JPAD | D_JPAD | L_JPAD | R_JPAD);
}

PROXY_OBJECT(mill, MillCtl, Init)
PROXY_OBJECT(mill, MillCtl, Step)
