#pragma once

using uint = unsigned int;
using uchar = unsigned char;
using ushort = unsigned short;
using ulong = unsigned long;
using mstime = unsigned long long;

using st6_malloc_t = void* (*)(size_t);
using st6_free_t = void (*)(void*);

using _RCSendChatMsg = void(__stdcall*)(uint iId, uint iTo, uint iSize, void* pRDL);
using _CRCAntiCheat = void(__stdcall*)();
using _CreateChar = void(__stdcall*)(const wchar_t* wszName);
using _GetFLName = int(__cdecl*)(char* szBuf, const wchar_t* wszStr);
using _GetShipInspect = bool(__cdecl*)(uint& iShip, class IObjInspectImpl*& inspect, uint& iDunno);

using BLOWFISH_CTX = struct
{
	unsigned long P[16 + 2];
	unsigned long S[4][256];
};

using UserCmdProc = void(*)(const uint& clientId, const std::wstring_view& param);

// Common types that can be used to explain what is being used
using ClientId = uint;
using SystemId = uint;
using EquipId = uint;
using BaseId = uint;
using RepId = ushort;
using GoodId = uint;