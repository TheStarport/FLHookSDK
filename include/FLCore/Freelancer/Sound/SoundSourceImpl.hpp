#pragma once

#include "../../FLCoreDefs.hpp"

#include "../../SoundManager/ISound.hpp"

struct SoundArchetype;
enum class SoundSourceFlags : byte
{
    Default = 0,
    IsLooping = 1 << 1,
    RelativePlayback = 5 << 1,
};

struct SoundSourceImpl : ISoundSource
{
    virtual void ReplaySound(SoundArchetype*, void*);
    virtual void dunno();
    virtual void PlaySound(SoundArchetype*);
    // Not entirely sure, if RelativePlayback as we've named it is set
    // then it subtracts time from the current startTime
    // It returns the new value of startTime (which is probably not startTime tbh)
    virtual u32 SetSoundTime(u32 time);
    virtual void sub_4296B0_u68();
    virtual void sub_4296E0_u6C();
    virtual void sub_4287E0_u70();
    virtual void sub_429840_u74();
    virtual void sub_429730_u78();
    virtual void sub_429450_u7C();
    // Sets the attenuation value, clamping it between 0 and -98.f
    virtual void SetAttenuation(float attn);
    // Set frequency, clamping between -10000 and 10000
    virtual void SetFrequency(f32 distance);
    virtual void SetLooping(bool looping);
    virtual void sub_429CA0_u80();
    virtual void sub_429DC0_u84();
    virtual void sub_429E70_u88();
    // sub_4299A0, clamps panning between -100 and 100
    virtual void SetSpeakerPanning(f32 pan);
    virtual void sub_428810_u90();
    virtual void sub_44FD00_u94();
    // sub_428820, seems to be a manual destructor
    virtual void Destructor(byte flag);
    virtual void sub_42A020_u98();

    UnkData unkData[2];
    SoundSourceFlags state;
    f32 panning;
    u32 startTime;
    SoundArchetype* soundArch;
    f32 attenuation;
    f32 frequency;
    UnkData unkData3[2];
    bool isOn;
    Vector position;
    UnkData unkData4[9];
    long objectTrackingIndex;
};
