#pragma once

#include "../Common/Unknown.hpp"
#include "../FLCoreDefs.hpp"

struct EngBaseObject
{
    virtual void __stdcall u00();
    virtual void __stdcall u04();
    virtual void __stdcall u08();
    virtual void __stdcall u0C();
    virtual void __stdcall u10();
    virtual void __stdcall u14();
    virtual void __stdcall u18();
    virtual void __stdcall u1C();
    virtual void __stdcall u20();
    virtual void __stdcall u24();
    virtual void __stdcall u28();
    virtual void __stdcall u2C();
    virtual void __stdcall u30();
    virtual void __stdcall u34();
    virtual void __stdcall u38();
    virtual void __stdcall u3C();

    Transform transform;
    // Unsure about next two, seems to be 6 floats, in last test I got:
    // 0.692640126 0.000410914450 -0.0455088615 -0.116086125 0.00000000 -581.721008
    Vector v1;
    Vector v2;
    u32 unk1; // These two might be some kind of hash?
    u32 unk2;
};
struct Fl3d;

// All the functions for this are in engbase.dll
struct IEngine
{
    // IUnknown interface, query returns HResult
    virtual u32 __stdcall QueryInterface(const char* name, void** component);
    virtual u32 __stdcall AddRef();
    virtual u32 __stdcall Release();
    virtual u32 __stdcall InitializeEngineComponents(u32 unk);
    virtual u32 __stdcall u10(bool (*callback)(u32*, u32));
    virtual void __stdcall u14();
    virtual void __stdcall SetSearchPath(u32 unk);
    virtual void __stdcall u1C(); // unk, does a lookup with 1.11_ISearchPath
    virtual void __stdcall u20(); //
    // This sets up unkDacomStruct1 and acquires it through dacom
    virtual void __stdcall GetDacomStruct(void** outPtr); // 0x661FF90
    // Does some kind of Filesystem (the DA virtual one) lookup?
    virtual void __stdcall u28(u32 a1, u32 a2, u32 a3); // 0x661FFC0
    virtual void __stdcall u2C(u32 a1, u32 a2);         // 0x6621150, again another filesystem thing
    virtual void __stdcall u30(u32 a1, u32 a2);         // 0x66212C0, loads archetype and animations
    virtual void __stdcall u34(u32 a1);                 // 0x066213b0
    virtual void __stdcall u38(const char* archetype);  // 0x066213d0, look up string in archetype name map
    // Data is two u32 values, unk & crc hash
    virtual void __stdcall u3C(void* data, st6::string* name); // 0x06621850
    virtual void __stdcall u40();
    virtual void __stdcall u44();
    virtual void __stdcall u48();
    virtual void __stdcall u4C();
    virtual void __stdcall u50();
    virtual void __stdcall u54();
    virtual void __stdcall u58();
    virtual void __stdcall u5C();
    virtual void __stdcall u60();
    virtual void __stdcall u64();
    virtual void __stdcall u68();
    virtual void __stdcall Unknown6C(const Fl3d* _3d, u32 a1, u32 a2);
    virtual void __stdcall u70();
    virtual void __stdcall u74();
    virtual void __stdcall u78();
    virtual void __stdcall u7C();
    virtual void __stdcall u80();
    virtual void __stdcall u84();
    virtual void __stdcall u88();
    virtual void __stdcall SetPosition(const Fl3d* _3d, Vector vector);
    virtual void __stdcall u90();
    virtual void __stdcall SetMatrix(const Fl3d* _3d, Matrix mat);
    virtual void __stdcall u98();
    virtual void __stdcall u9C();
    // This grabs just the transform from the EngBaseObject defined above
    // I am not convinced that everything in that struct is accurate
    virtual Transform* __stdcall GetTransform(const Fl3d* _3d);

    // Don't know how many fields there are exactly
    // Current known count: 22 (offset 88 + 4 for vtable)

    void* unkDacomStruct1; // Some other part of DACom/EngBase, can probably get the exact type if we need
    UnkData unkData1[3];   // 8-16
    void* unkLinkedList1;  // At a glance some kind of linked list?
    UnkData unkData[17];
    void* unkLinkedList2; // 92
};
