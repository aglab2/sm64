#pragma once

extern "C"
{
#include "include/types.h"
#include "game/object_list_processor.h"
}
#include "cpp/proxy.hpp"

#define oNumbersWriterNumbers (&OBJECT_FIELD_S32(0x1b))
#define fNumbersWriterNumbers(obj) (&((obj)->OBJECT_FIELD_S32(0x1b)))
class NumbersWriter : public Object
{
public:
    void Init();
    void Step();
};
