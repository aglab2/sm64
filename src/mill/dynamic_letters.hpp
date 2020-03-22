#pragma once

#define _LANGUAGE_C_PLUS_PLUS

#include <PR/gbi.h>
extern "C"
{
#include "include/types.h"
#include "game/object_list_processor.h"
#include "game/rendering_graph_node.h"
#include "engine/graph_node.h"
}
#include "cpp/proxy.hpp"

#define DYNLET_TEXT ((char*) OBJECT_FIELD_S32(0x1b))
#define TEXT_COLOR  oBehParams2ndByte

#define F_DYNLET_TEXT(obj) ((obj)->OBJECT_FIELD_S32(0x1b))
#define F_TEXT_COLOR(obj)  (obj)->oBehParams2ndByte

class DynamicLetters : public Object
{
public:
    void Init();
    void Step();
    Gfx* Draw(u32 sp50, struct GraphNode *sp54, u32 sp58);
};
