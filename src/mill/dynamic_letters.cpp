#include "dynamic_letters.hpp"

#include "gfx_table.hpp"
#include "string_fit.hpp"
#include "colors.hpp"
#include "rainbow_colors.hpp"

#include "object_fields.h"

extern "C" const char * strchr ( const char * str, int character );

#define DYNLET_TEXT ((char*) OBJECT_FIELD_S32(0x1b))
#define TEXT_COLOR  oBehParams2ndByte

const char text[] = "$";

void DynamicLetters::Init()
{ 
    OBJECT_FIELD_S32(0x1b) = (s32) text;
}

void DynamicLetters::Step()
{ }

static float symlen(const char* text)
{
    float symlen = 0;
    for (int i = 0; text[i] != '\0' && text[i] != '\n'; i++)
    {
        int sym = text[i];
        symlen += LetterSizes[sym];
    }
    return symlen;
}

#define SEG_ADDR(x) ((int)x & 0x00FFFFFF)

Gfx* DynamicLetters::Draw(u32 sp50, struct GraphNode* node, u32 sp58)
{
    if (sp50 == 0)
    {
        node->flags = (node->flags & 0xFF) | 0x100;
        return nullptr;
    }

    int dllen = 0;
    for (int i = 0; DYNLET_TEXT[i] != '\0'; i++)
    {
        int sym = DYNLET_TEXT[i];
        if (LetterGfxs[sym])
        {
            dllen++;
        }
    }
    
    int linecount = 0;
    {
        const char* text = DYNLET_TEXT;
        while ((text = strchr(text, '\n')))
        {
            text++;
            linecount++;
        }
    }

    // Do not forget to fix me!
    Gfx *displayList = (Gfx*) alloc_display_list((dllen * 3 + 3) * sizeof(Gfx));
    Gfx *displayListIter = displayList;
    
    if (TEXT_COLOR == (u8)-1)
    {
        gSPLight(displayListIter++, G_MV_L0, SEG_ADDR(RainbowDarkColor));
        gSPLight(displayListIter++, G_MV_L1, SEG_ADDR(RainbowLightColor));
    }
    else
    {
        gSPLight(displayListIter++, G_MV_L0, SEG_ADDR(DarkColors [TEXT_COLOR]));
        gSPLight(displayListIter++, G_MV_L1, SEG_ADDR(LightColors[TEXT_COLOR]));
    }

    float offsetY = 20.0f + (StringFit::SymbolHeight / 2.0f) * (float) linecount;
    const char* curLine = DYNLET_TEXT;
    while (true)
    {
        float offsetX = -symlen(curLine) / 2.0f;
        for (; *curLine != '\0' && *curLine != '\n'; curLine++) 
        {
            Mtx* mtx = (Mtx*) alloc_display_list(sizeof(Mtx));

            int sym = *curLine;
            guTranslate(mtx, offsetX, offsetY, 0);
            offsetX += LetterSizes[sym];
            if (LetterGfxs[sym])
            {
                gSPMatrix(displayListIter++, mtx, G_MTX_PUSH | G_MTX_MODELVIEW);
                gSPDisplayList(displayListIter++, LetterGfxs[sym]);
                gSPPopMatrix(displayListIter++, G_MTX_MODELVIEW);
            }
        }
        if (*curLine == '\0')
            break;

        curLine++;
        offsetY -= StringFit::SymbolHeight;
    }

    gSPEndDisplayList(displayListIter);

    return displayList;
}
