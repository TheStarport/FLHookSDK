#pragma once
#include "../../FLCoreDefs.hpp"

namespace Universe
{
    IMPORT ISystem* GetFirstSystem();
    IMPORT IBase* GetNextBase();
    IMPORT ISystem* GetNextSystem();
    IMPORT void Shutdown();
    IMPORT bool Startup(const char*);
    IMPORT const IZone* first_zone(u32);
    IMPORT IBase* __cdecl GetFirstBase();
    IMPORT IBase* __cdecl GetNextBase();
    IMPORT u32 __cdecl get_base_id(const char*);
    IMPORT IBase* get_base(u32);
    IMPORT u32 get_base_id(const char*);
    IMPORT void get_filename(char*, const char*);
    IMPORT u32 get_gate_system(u32);
    IMPORT IZone* get_non_const_zone(u32, u32);
    IMPORT IZone* get_non_const_zone(u32, const char*);
    IMPORT const ISystem* get_system(u32);
    IMPORT u32 get_system_id(const char*);
    IMPORT const IZone* get_zone(u32);
    IMPORT const IZone* get_zone(u32, const char*);
    IMPORT const IZone* next_zone(const IZone*);
    IMPORT u32 num_bases();
    IMPORT u32 num_systems();
}