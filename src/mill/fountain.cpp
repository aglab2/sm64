#include "fountain.hpp"
extern "C"
{
    #include "game/object_helpers.h"
    #include "engine/behavior_script.h"
    #include "behavior_data.h"
}
#include "cpp/fields.hpp"

static float rng()
{
    return RandomFloat() - 0.5f;
}

void Fountain::Step()
{
    auto particle = spawn_object(this, 0, bhvMillFountainParticle);
    fVel(particle) = { rng() * 50, (float) oBehParams2ndByte, rng() * 50 };
    particle->oBehParams2ndByte = 5;
    particle->oAnimState = RandomU16() % 6;
}

void FountainParticle::Step()
{
    oPos += oVel;
    oFaceAngleRoll += 100;
    oVelY -= oBehParams2ndByte;
    if (oPosY < -2000)
        activeFlags = 0;
}

PROXY_OBJECT(mill, Fountain, Step)
PROXY_OBJECT(mill, FountainParticle, Step)