#pragma once
extern "C"
{
#include "include/types.h"
#include "game/object_list_processor.h"
}
#include "cpp/proxy.hpp"

class DeathRoom : public Object
{
public:
    void Init();
    void Step();
};
