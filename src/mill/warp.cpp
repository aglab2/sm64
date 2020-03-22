#include "warp.hpp"
extern "C"
{
    #include "game/level_update.h"
}

void TriggerWarp(int id, int type)
{
    // 8024A9CC
    level_trigger_warp(gMarioStates, type);
    // 8033B252
    sDelayedWarpOp = type;
    // 8033B256
    sSourceWarpNodeId = id;
}