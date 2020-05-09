#pragma once

extern "C"
{
#include "include/types.h"
#include "game/object_list_processor.h"
}
#include "cpp/proxy.hpp"


// bparam2 question number
class MillCtl : public Object
{
private:
    void FreezeMario();
    void MaskInputs(int inputs);
    void SetCamera();
    void SetGamingMusic();
    void FixMusic();
    void SetMusic(int music);
    void SetWinMusic();

    void PrintHint(const char* msg, int offsetY = 0);
    
    void PickedAngle(int pick);

    int GetWorld(int q);
    int GetLevel(int q);

    // Normal states
    void Prepare();
    void Unveil();
    void Picking();
    void Final();
    void Results();
    void WalkAway();


    // Lifelines
    void FiftyFifty();
    void Audience();
    void CallFriend();
    void AudiencePicking();
    void AudienceAfterPicking();
    void CallFriendCountDown();

    void ResetWorld();

public:
    void Init();
    void Step();
};
