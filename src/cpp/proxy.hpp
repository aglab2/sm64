#pragma once

extern "C"
{
    #include "game/object_list_processor.h"
}

#define PROXY_OBJECT(module, cl, fn) extern "C" void module##_##cl##_##fn() { return reinterpret_cast<cl*>(gCurrentObject)->fn(); }
#define PROXY_DRAW(module, cl, fn)   extern "C" Gfx* module##_##cl##_##fn(u32 sp50, struct GraphNode *sp54, u32 sp58) { return reinterpret_cast<cl*>(gCurGraphNodeObject)->fn(sp50, sp54, sp58); }