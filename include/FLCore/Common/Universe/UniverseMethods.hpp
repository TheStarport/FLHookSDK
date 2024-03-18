#pragma once
#include "../../FLCoreDefs.hpp"

namespace Universe
{
    IMPORT ISystem* GetFirstSystem();
    IMPORT IBase* GetNextBase();
    IMPORT ISystem* GetNextSystem();
    IMPORT void Shutdown();
    IMPORT bool Startup(const char*);
    IMPORT const IZone* first_zone(unsigned int);
    IMPORT IBase* __cdecl GetFirstBase();
    IMPORT IBase* __cdecl GetNextBase();
    IMPORT unsigned int __cdecl get_base_id(const char*);
    IMPORT IBase* get_base(unsigned int);
    IMPORT unsigned int get_base_id(const char*);
    IMPORT void get_filename(char*, const char*);
    IMPORT unsigned int get_gate_system(unsigned int);
    IMPORT IZone* get_non_const_zone(unsigned int, unsigned int);
    IMPORT IZone* get_non_const_zone(unsigned int, const char*);
    IMPORT const ISystem* get_system(unsigned int);
    IMPORT unsigned int get_system_id(const char*);
    IMPORT const IZone* get_zone(unsigned int);
    IMPORT const IZone* get_zone(unsigned int, const char*);
    IMPORT const IZone* next_zone(const IZone*);
    IMPORT unsigned int num_bases();
    IMPORT unsigned int num_systems();
}