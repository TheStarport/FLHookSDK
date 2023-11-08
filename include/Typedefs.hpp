#pragma once

using uint = unsigned int;
using uchar = unsigned char;
using ushort = unsigned short;
using ulong = unsigned long;
using int64 = long long;
using uint64 = unsigned long long;
using mstime = uint64;

// Otherwords for common things
using byte = uchar;

// Common types that can be used to explain what is being used

using EquipId = const uint;
using RepId = const ushort;
using GoodId = const uint;
using ArchId = const uint;
using LocationId = const uint;

using st6_malloc_t = void* (*)(size_t);
using st6_free_t = void (*)(void*);

using RCSendChatMsg = void(__stdcall*)(uint id, uint to, uint size, void* RDL);
using CRCAntiCheat = void(__stdcall*)();
using GetFLName = int(__cdecl*)(char* buf, const wchar_t* str);
using GetShipInspect = bool(__cdecl*)(uint& ship, class IObjInspectImpl*& inspect, uint& dunno);
