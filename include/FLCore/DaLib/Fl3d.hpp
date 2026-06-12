#pragma once

#include "../FLCoreDefs.hpp"

struct Fl3dData
{
    void* vmt;
    Matrix mat;
    f32 radius;
    Vector center;
    u32 unk;
};

struct Fl3dDesc
{
    u32 unk;
    const char* mesh;
    u32 meshLength;
    u32 meshBuffer; // unknown how big this is
    // these things start after tho
    u32 hash;
    u32 refCount;
    u32 unkBlock[9];
    u32 hash2; // unsure about this one
};

struct Fl3dInfo
{
    u32 unk;
    const char* name;
    u32 nameLen;
    // actual length unknown, needs validation
    char nameBuffer[32];
};

struct Fl3d
{
    u32 two;
    Fl3dData* data;
    Fl3dDesc* desc;
    Fl3dInfo* info;
    u32 unk;
    Vector unkVec;
};

struct Fl3db
{
    void* vmt;
    Fl3d* _3d;
    u32 unk1;
    u32 unk2;
    u32 unk3;
    f32 r;
    f32 g;
    f32 b;
    f32 unk;
    f32 a;
};
