#include "numbers_writer.hpp"
extern "C"
{
    #include "game/object_helpers.h"
    #include "game/print.h"
    #include "model_ids.h"
    #include "behavior_data.h"
}
#include "cpp/fields.hpp"

static const struct triplet AudienceVisual[] = {
    { -1190, 30, -880 },
    { -450,  30, -880 }, 
    { 450,   30, -880 }, 
    { 1190,  30, -880 },
};

void NumbersWriter::Init()
{
    float totalCount = 0;
    for (int i = 0; i < 4; i++)
        totalCount += oNumbersWriterNumbers[i];
    
    for (int i = 0; i < 4; i++)
    {
        float scale = ((float) oNumbersWriterNumbers[i]) / totalCount;

        auto obj = spawn_object(this, MODEL_AUDIENCE, bhvStaticObject);
        fPos(obj) = AudienceVisual[i];
        obj_scale_xyz(obj, scale, 1, 1);
    }
}

void NumbersWriter::Step()
{
    for (int i = 0; i < 4; i++)
    {
        char str[] = "A %d";
        str[0] += i;
        print_text_fmt_int(20, 100 - 20 * i, str, oNumbersWriterNumbers[i]);
    }
}

PROXY_OBJECT(mill, NumbersWriter, Init)
PROXY_OBJECT(mill, NumbersWriter, Step)
