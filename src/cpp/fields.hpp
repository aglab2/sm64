#pragma once

#include "object_fields.h"
extern "C"
{
    #include "game/level_update.h"
}
#include "triplet.hpp"

#define TRIPLET(val) (*(triplet*) &(val))
#define FIELD_TRIPLET(obj, off) TRIPLET((obj)->off)

#define oHome TRIPLET(oHomeX)
#define oPos  TRIPLET(oPosX)
#define oVel  TRIPLET(oVelX)

#define fHome(obj) FIELD_TRIPLET(obj, oHomeX)
#define fPos(obj)  FIELD_TRIPLET(obj, oPosX)
#define fVel(obj)  FIELD_TRIPLET(obj, oVelX)

#define mPos  FIELD_TRIPLET(gMarioStates, pos)
#define mVel  FIELD_TRIPLET(gMarioStates, vel)