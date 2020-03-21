#define _LANGUAGE_C_PLUS_PLUS

#include <PR/gbi.h>
extern "C"
{
#include "include/types.h"
#include "game/object_list_processor.h"
#include "game/rendering_graph_node.h"
#include "engine/graph_node.h"
}

class DynamicLetters : public Object
{
public:
    void Init();
    void Step();
    Gfx* Draw(u32 sp50, struct GraphNode *sp54, u32 sp58);
};

extern "C"
{
    void mill_letter_Init() { reinterpret_cast<DynamicLetters*>(gCurrentObject)->Init(); }
    void mill_letter_Step() { reinterpret_cast<DynamicLetters*>(gCurrentObject)->Step(); }
    Gfx* mill_letter_Draw(u32 sp50, struct GraphNode *sp54, u32 sp58) { return reinterpret_cast<DynamicLetters*>(gCurGraphNodeObject)->Draw(sp50, sp54, sp58); }
}
