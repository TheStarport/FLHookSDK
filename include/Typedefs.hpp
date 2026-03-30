#pragma once

using uint = unsigned int;
using uchar = unsigned char;
using ushort = unsigned short;
using ulong = unsigned long;
using int64 = long long;
using unsigned64 = unsigned long long;
using mstime = unsigned64;

// Otherwords for common things
using byte = uchar;

// Common types that can be used to explain what is being used

using ArchId = const unsigned;
using LocationId = const unsigned;

class StarSystem;
using RCSendChatMsgT = void(__thiscall*)(void* hook, unsigned id, unsigned to, unsigned size, void* RDL);
using CRCAntiCheatT = void(__stdcall*)();
using GetFLNameT = int(__cdecl*)(char* buf, const wchar_t* str);
using GetShipInspectT = bool(__cdecl*)(const unsigned& ship, class IObjInspectImpl*& inspect, StarSystem*& starSystem);
