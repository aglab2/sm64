#pragma once

extern "C"
{
#include "include/types.h"
#include "game/object_list_processor.h"
}
#include "cpp/proxy.hpp"

class Memes : public Object
{
public:
    void Init();
    void Step();

    void Dorrie();
    void Firsty();
};
