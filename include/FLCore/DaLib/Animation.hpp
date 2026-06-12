#pragma once

#include "../FLCoreDefs.hpp"

enum class AnimationDirection
{
    Forwards = 0,
    Backwards = 1,
    Repeat = 2,
    Cycle = 4
};

struct AnimObject
{
    void* vtable;
    st6::map<u32, u32> map;
};

struct IAnimation2
{
    // IUnknown interface, query returns HResult
    virtual u32 __stdcall QueryInterface(const char* name, void** component);
    virtual u32 __stdcall AddRef();
    virtual u32 __stdcall Release();
    virtual void __stdcall func_0c();
    virtual void __stdcall func_10();

    virtual float __stdcall TotalTime(long);

    virtual void __stdcall func_18();
    virtual void __stdcall func_1c();
    virtual float __stdcall GetFullAnimTime_unk(long id);

    virtual long __stdcall Open(AnimObject* animObj, long parentOrSelfIndex, const char* animationName, int,
                                int);
    virtual void __stdcall Close(long);
    virtual void __stdcall Play(long id,                      // id - Open's return value
                                AnimationDirection direction, // 1 = backwards, 2 = repeat, 4 = cycle
                                float,                        // start pos (-2 = normal, -1 = end)
                                float,                        // speed
                                float,                        // time to run (seconds)
                                float,                        // end pos
                                float,                        // unknown (apparently unused)
                                float);                       // unknown (apparently unused)

    virtual void __stdcall func_30();
    virtual void __stdcall func_34();

    virtual void __stdcall Stop(long); // flush?

    virtual void __stdcall func_3c();

    virtual float __stdcall CurrentTime(long);
};
