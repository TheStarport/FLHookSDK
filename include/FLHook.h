#ifndef _FLHOOK_
#define _FLHOOK_

#pragma warning(disable : 4311 4786)

#include <Windows.h>
#include <cstdio>
#include <string>
#include <set>
#include <list>
#include <ctime>
#include <map>
#include <filesystem>
#include <variant>

#include "Serialization.hpp"
#include "Singleton.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// defines

#define HKHKSUCCESS(a) ((a) == HKE_OK)
#define HKSUCCESS(a) ((hkLastErr = (a)) == HKE_OK)

#define SRV_ADDR(a) ((char*)hModServer + a)
#define DALIB_ADDR(a) ((char*)hModDaLib + a)
#define FLSERVER_ADDR(a) ((char*)hProcFL + a)
#define CONTENT_ADDR(a) ((char*)hModContent + a)

#define IMPORT __declspec(dllimport)
#define EXPORT __declspec(dllexport)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// typedefs
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned __int64 mstime;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// exception logging

#define EXTENDED_EXCEPTION_LOGGING
#ifdef EXTENDED_EXCEPTION_LOGGING
	#pragma warning(disable : 4091)
	#include <dbghelp.h>

struct SEHException
{
	SEHException(uint code, EXCEPTION_POINTERS* ep) : code(code), record(*ep->ExceptionRecord), context(*ep->ContextRecord) {}

	SEHException() = default;

	uint code;
	EXCEPTION_RECORD record;
	CONTEXT context;

	static void Translator(uint code, EXCEPTION_POINTERS* ep) { throw SEHException(code, ep); }
};

IMPORT void WriteMiniDump(SEHException* ex);
IMPORT void AddExceptionInfoLog();
IMPORT void AddExceptionInfoLog(SEHException* ex);
	#define TRY_HOOK \
		try          \
		{            \
			_set_se_translator(SEHException::Translator);
	#define CATCH_HOOK(e)                                                                                                         \
		}                                                                                                                         \
		catch (SEHException & ex)                                                                                                 \
		{                                                                                                                         \
			e;                                                                                                                    \
			AddBothLog(L"ERROR: SEH Exception in %s on line %d; minidump may contain more information.", __FUNCTION__, __LINE__); \
			AddExceptionInfoLog(&ex);                                                                                             \
		}                                                                                                                         \
		catch (std::exception & ex)                                                                                               \
		{                                                                                                                         \
			e;                                                                                                                    \
			AddBothLog(L"ERROR: STL Exception in %s on line %d: %s.", __FUNCTION__, __LINE__, ex.what());                         \
			AddExceptionInfoLog(0);                                                                                               \
		}                                                                                                                         \
		catch (...)                                                                                                               \
		{                                                                                                                         \
			e;                                                                                                                    \
			AddBothLog(L"ERROR: Exception in %s on line %d.", __FUNCTION__, __LINE__);                                            \
			AddExceptionInfoLog(0);                                                                                               \
		}
#else
	#define TRY_HOOK try
	#define CATCH_HOOK(e)                                                            \
		catch (...)                                                                  \
		{                                                                            \
			e;                                                                       \
			AddLog(Normal, LogLevel::Info, L"ERROR: Exception in %s", __FUNCTION__); \
		}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void* (*st6_malloc_t)(size_t);
typedef void (*st6_free_t)(void*);

extern IMPORT st6_malloc_t st6_malloc;
extern IMPORT st6_free_t st6_free;
#define ST6_ALLOCATION_DEFINED

#include "FLCoreCommon.h"
#include "FLCoreServer.h"
#include "FLCoreRemoteClient.h"
#include "FLCoreDALib.h"

#include "plugin.h"

typedef void(__stdcall* _RCSendChatMsg)(uint iId, uint iTo, uint iSize, void* pRDL);
typedef void(__stdcall* _CRCAntiCheat)();
typedef void(__stdcall* _CreateChar)(const wchar_t* wszName);
typedef int(__cdecl* _GetFLName)(char* szBuf, const wchar_t* wszStr);
typedef bool(__cdecl* _GetShipInspect)(uint& iShip, IObjInspectImpl*& inspect, uint& iDunno);

extern IMPORT _GetShipInspect GetShipInspect;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enums

enum class LogLevel : int
{
	Trace,
	Debug,
	Info,
	Warn,
	Err,
	Critical
};

enum LogType
{
	Normal,
	Cheater,
	Kick,
	Connects,
	AdminCmds,
	UserLogCmds,
	SocketCmds,
	PerfTimers,
};

enum HK_ERROR
{
	HKE_OK,
	HKE_PLAYER_NOT_LOGGED_IN,
	HKE_CHAR_DOES_NOT_EXIST,
	HKE_INVALID_CLIENT_ID,
	HKE_COULD_NOT_DECODE_CHARFILE,
	HKE_COULD_NOT_ENCODE_CHARFILE,
	HKE_INVALID_BASENAME,
	HKE_INVALID_ID_STRING,
	HKE_INVALID_SYSTEM,
	HKE_PLAYER_NOT_IN_SPACE,
	HKE_PLAYER_NO_ADMIN,
	HKE_WRONG_XML_SYNTAX,
	HKE_INVALID_GOOD,
	HKE_NO_CHAR_SELECTED,
	HKE_CHARNAME_ALREADY_EXISTS,
	HKE_CHARNAME_TOO_LONG,
	HKE_CHARNAME_TOO_SHORT,
	HKE_AMBIGUOUS_SHORTCUT,
	HKE_NO_MATCHING_PLAYER,
	HKE_INVALID_SHORTCUT_STRING,
	HKE_MPNEWCHARACTERFILE_NOT_FOUND_OR_INVALID,
	HKE_INVALID_REP_GROUP,
	HKE_PLUGIN_UNLOADABLE,
	HKE_PLUGIN_UNPAUSABLE,
	HKE_PLUGIN_NOT_FOUND,
	HKE_UNKNOWN_ERROR,
	HKE_CUSTOM_1,
	HKE_CUSTOM_2,
	HKE_CUSTOM_3,
	HKE_CUSTOM_4,
	HKE_CUSTOM_5,
	HKE_CUSTOM_6,
	HKE_CUSTOM_7,
	HKE_CUSTOM_8,
	HKE_CUSTOM_9,
	HKE_CUSTOM_10,
};

enum DIEMSGTYPE
{
	DIEMSG_ALL = 0,
	DIEMSG_SYSTEM = 1,
	DIEMSG_NONE = 2,
	DIEMSG_SELF = 3,
};

enum CHATSIZE
{
	CS_DEFAULT = 0,
	CS_SMALL = 1,
	CS_BIG = 2,
};

enum CHATSTYLE
{
	CST_DEFAULT = 0,
	CST_BOLD = 1,
	CST_ITALIC = 2,
	CST_UNDERLINE = 3,
};

enum ENGINE_STATE
{
	ES_CRUISE,
	ES_THRUSTER,
	ES_ENGINE,
	ES_KILLED,
	ES_TRADELANE
};

enum EQ_TYPE
{
	ET_GUN,
	ET_TORPEDO,
	ET_CD,
	ET_MISSILE,
	ET_MINE,
	ET_CM,
	ET_SHIELDGEN,
	ET_THRUSTER,
	ET_SHIELDBAT,
	ET_NANOBOT,
	ET_MUNITION,
	ET_ENGINE,
	ET_OTHER,
	ET_SCANNER,
	ET_TRACTOR,
	ET_LIGHT
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structs

struct HOOKENTRY
{
	FARPROC fpProc;
	long dwRemoteAddress;
	FARPROC fpOldProc;
};

struct CARGO_INFO
{
	uint iID;
	int iCount;
	uint iArchID;
	float fStatus;
	bool bMission;
	bool bMounted;
	CacheString hardpoint;
};

// money stuff
struct MONEY_FIX
{
	std::wstring wscCharname;
	int iAmount;

	bool operator==(MONEY_FIX mf1)
	{
		if (!wscCharname.compare(mf1.wscCharname))
			return true;

		return false;
	};
};

// ignore
struct IGNORE_INFO
{
	std::wstring wscCharname;
	std::wstring wscFlags;
};

// resolver
struct RESOLVE_IP
{
	uint iClientID;
	uint iConnects;
	std::wstring wscIP;
	std::wstring wscHostname;
};

struct CLIENT_INFO
{
	// kill msgs
	uint iShip;
	uint iShipOld;
	mstime tmSpawnTime;

	DamageList dmgLast;

	// money cmd
	std::list<MONEY_FIX> lstMoneyFix;

	// anticheat
	uint iTradePartner;

	// change cruise disruptor behaviour
	bool bCruiseActivated;
	bool bThrusterActivated;
	bool bEngineKilled;
	bool bTradelane;

	// idle kicks
	uint iBaseEnterTime;
	uint iCharMenuEnterTime;

	// msg, wait and kick
	mstime tmKickTime;

	// eventmode
	uint iLastExitedBaseID;
	bool bDisconnected;

	// f1 laming
	bool bCharSelected;
	mstime tmF1Time;
	mstime tmF1TimeDisconnect;

	// ignore usercommand
	std::list<IGNORE_INFO> lstIgnore;

	// user settings
	DIEMSGTYPE dieMsg;
	CHATSIZE dieMsgSize;
	CHATSTYLE dieMsgStyle;
	CHATSIZE chatSize;
	CHATSTYLE chatStyle;

	// autobuy
	bool bAutoBuyMissiles;
	bool bAutoBuyMines;
	bool bAutoBuyTorps;
	bool bAutoBuyCD;
	bool bAutoBuyCM;
	bool bAutoBuyReload;

	// MultiKillMessages
	uint iKillsInARow;

	// bans
	uint iConnects; // incremented when player connects

	// other
	std::wstring wscHostname;

	bool bSpawnProtected;
	bool bUseServersideHitDetection; // used by AC Plugin

	// Map of PluginData* to array of 10 potential values
	// PluginData is undefined here, so we need to either forward declare or use a void*.
	std::map<void*, std::array<uchar, 40>> mapPluginData;
};

#define GetPluginClientData(id, info) ((&ClientInfo[(id)])->mapPluginData[(info)].data())

struct INISECTIONVALUE
{
	std::string scKey;
	std::string scValue;
};

struct MULTIKILLMESSAGE
{
	uint iKillsInARow;
	std::wstring wscMessage;
};

// taken from directplay
typedef struct _DPN_CONNECTION_INFO
{
	DWORD dwSize;
	DWORD dwRoundTripLatencyMS;
	DWORD dwThroughputBPS;
	DWORD dwPeakThroughputBPS;
	DWORD dwBytesSentGuaranteed;
	DWORD dwPacketsSentGuaranteed;
	DWORD dwBytesSentNonGuaranteed;
	DWORD dwPacketsSentNonGuaranteed;
	DWORD dwBytesRetried;
	DWORD dwPacketsRetried;
	DWORD dwBytesDropped;
	DWORD dwPacketsDropped;
	DWORD dwMessagesTransmittedHighPriority;
	DWORD dwMessagesTimedOutHighPriority;
	DWORD dwMessagesTransmittedNormalPriority;
	DWORD dwMessagesTimedOutNormalPriority;
	DWORD dwMessagesTransmittedLowPriority;
	DWORD dwMessagesTimedOutLowPriority;
	DWORD dwBytesReceivedGuaranteed;
	DWORD dwPacketsReceivedGuaranteed;
	DWORD dwBytesReceivedNonGuaranteed;
	DWORD dwPacketsReceivedNonGuaranteed;
	DWORD dwMessagesReceived;
} DPN_CONNECTION_INFO, *PDPN_CONNECTION_INFO;

struct HKPLAYERINFO
{
	uint iClientID;
	std::wstring wscCharname;
	std::wstring wscBase;
	std::wstring wscSystem;
	uint iSystem;
	uint iShip;
	DPN_CONNECTION_INFO ci;
	std::wstring wscIP;
	std::wstring wscHostname;
};

// patch stuff
struct PATCH_INFO_ENTRY
{
	ulong pAddress;
	void* pNewValue;
	uint iSize;
	void* pOldValue;
	bool bAlloced;
};

struct PATCH_INFO
{
	char* szBinName;
	ulong pBaseAddress;

	PATCH_INFO_ENTRY piEntries[128];
};

struct DATA_MARKETITEM
{
	uint iArchID;
	float fRep;
};

struct BASE_INFO
{
	uint iBaseID;
	std::string scBasename;
	uint iObjectID;
	bool bDestroyed;
	std::list<DATA_MARKETITEM> lstMarketMisc;
};

struct GROUP_MEMBER
{
	uint iClientID;
	std::wstring wscCharname;
};

struct PLUGIN_HOOKDATA
{
	std::string sName;
	HMODULE hDLL;
	int iPriority;
	bool bPaused;
};

struct PLUGIN_DATA
{
	std::string sName;
	std::string sShortName;
	HMODULE hDLL;
	std::string sDLL;
	bool bMayPause;
	bool bMayUnload;
	bool bPaused;
};

#define LOG_EXCEPTION                                                           \
	{                                                                           \
		AddLog(Normal, LogLevel::Info, L"ERROR Exception in %s", __FUNCTION__); \
		AddExceptionInfoLog();                                                  \
	}

// Almost every plugin will handle user commands in the exact same way.
// Rather than duplicating this code block over and over, lets just macro it.
typedef void (*_UserCmdProc)(uint, const std::wstring&);

struct USERCMD
{
	wchar_t* wszCmd;
	_UserCmdProc proc;
};

// Some plugins already define this, just to stop the compiler from getting angry at us
#ifndef IS_CMD
	#define IS_CMD(a) !wscCmd.compare(L##a)
#endif

#define DefaultUserCommandHandling(clientId, wscCmd, userCmds, returnCode)  \
	std::wstring wscCmdLower = ToLower(wscCmd);                             \
	for (uint i = 0; i < std::size(UserCmds); i++)							\
	{                                                                       \
		if (wscCmdLower.find(ToLower(UserCmds[i].wszCmd)) == 0)             \
		{                                                                   \
			std::wstring wscParam = L"";                                    \
			if ((wscCmd).length() > wcslen(UserCmds[i].wszCmd))             \
			{                                                               \
				if ((wscCmd)[wcslen(UserCmds[i].wszCmd)] != ' ')            \
					continue;                                               \
				wscParam = (wscCmd).substr(wcslen(UserCmds[i].wszCmd) + 1); \
			}                                                               \
			(userCmds)[i].proc(clientId, wscParam);                         \
			(returnCode) = ReturnCode::SkipAll;                             \
			return true;                                                    \
		}                                                                   \
	}                                                                       \
	return false;

// HkFuncTools
IMPORT uint HkGetClientIdFromAccount(CAccount* acc);
IMPORT uint HkGetClientIdFromPD(struct PlayerData* pPD);
IMPORT CAccount* HkGetAccountByCharname(const std::wstring& wscCharname);
IMPORT uint HkGetClientIdFromCharname(const std::wstring& wscCharname);
IMPORT std::wstring HkGetAccountID(CAccount* acc);
IMPORT bool HkIsEncoded(const std::string& scFilename);
IMPORT bool HkIsInCharSelectMenu(std::variant<uint, std::wstring> player);
IMPORT bool HkIsValidClientID(uint iClientID);
IMPORT HK_ERROR HkResolveId(const std::wstring& player, uint& iClientID);
IMPORT HK_ERROR HkResolveShortCut(const std::wstring& wscShortcut, uint& iClientID);
IMPORT uint HkGetClientIDByShip(uint iShip);
IMPORT HK_ERROR HkGetAccountDirName(CAccount* acc, std::wstring& wscDir);
IMPORT HK_ERROR HkGetAccountDirName(std::variant<uint, std::wstring> player, std::wstring& wscDir);
IMPORT HK_ERROR HkGetCharFileName(std::variant<uint, std::wstring> player, std::wstring& wscFilename);
IMPORT std::wstring HkGetBaseNickByID(uint iBaseID);
IMPORT std::wstring HkGetPlayerSystem(uint iClientID);
IMPORT std::wstring HkGetSystemNickByID(uint iSystemID);
IMPORT void HkLockAccountAccess(CAccount* acc, bool bKick);
IMPORT void HkUnlockAccountAccess(CAccount* acc);
IMPORT void HkGetItemsForSale(uint iBaseID, std::list<uint>& lstItems);
IMPORT IObjInspectImpl* HkGetInspect(uint iClientID);
IMPORT ENGINE_STATE HkGetEngineState(uint iClientID);
IMPORT EQ_TYPE HkGetEqType(Archetype::Equipment* eq);
IMPORT HK_ERROR HkGetClientID(bool& bIdString, uint& iClientID, const std::wstring& wscCharname);
IMPORT float HkDistance3D(Vector v1, Vector v2);
IMPORT float HkDistance3DByShip(uint iShip1, uint iShip2);
IMPORT Quaternion HkMatrixToQuaternion(Matrix m);
template<typename Str>
IMPORT Str VectorToSectorCoord(uint iSystemID, Vector vPos);
IMPORT float degrees(float rad);
IMPORT Vector MatrixToEuler(const Matrix& mat);
IMPORT void Rotate180(Matrix& rot);
IMPORT void TranslateY(Vector& pos, Matrix& rot, float y);
IMPORT void TranslateX(Vector& pos, Matrix& rot, float x);
IMPORT void TranslateZ(Vector& pos, Matrix& rot, float z);

// HkFuncMsg
IMPORT HK_ERROR HkMsg(int iClientID, const std::wstring& wscMessage);
IMPORT HK_ERROR HkMsg(std::variant<uint, std::wstring> player, const std::wstring& wscMessage);
IMPORT HK_ERROR HkMsgS(const std::wstring& wscSystemname, const std::wstring& wscMessage);
IMPORT HK_ERROR HkMsgU(const std::wstring& wscMessage);
IMPORT HK_ERROR HkFMsgEncodeXML(const std::wstring& wscXML, char* szBuf, uint iSize, uint& iRet);
IMPORT HK_ERROR HkFMsgSendChat(uint iClientID, char* szBuf, uint iSize);
IMPORT HK_ERROR HkFMsg(uint iClientID, const std::wstring& wscXML);
IMPORT HK_ERROR HkFMsg(std::variant<uint, std::wstring> player, const std::wstring& wscXML);
IMPORT HK_ERROR HkFMsgS(const std::wstring& wscSystemname, const std::wstring& wscXML);
IMPORT HK_ERROR HkFMsgU(const std::wstring& wscXML);
IMPORT std::wstring HkGetWStringFromIDS(uint iIDS);
IMPORT void HkLoadStringDLLs();
IMPORT void HkUnloadStringDLLs();
IMPORT void FormatSendChat(uint iToClientID, const std::wstring& wscSender, const std::wstring& wscText, const std::wstring& wscTextColor);
IMPORT void SendGroupChat(uint iFromClientID, const std::wstring& wscText);
IMPORT void SendLocalSystemChat(uint iFromClientID, const std::wstring& wscText);
IMPORT void SendPrivateChat(uint iFromClientID, uint iToClientID, const std::wstring& wscText);
IMPORT void SendSystemChat(uint iFromClientID, const std::wstring& wscText);

// HkFuncPlayers
IMPORT HK_ERROR HkGetCash(std::variant<uint, std::wstring> player, int& iCash);
IMPORT HK_ERROR HkAddCash(std::variant<uint, std::wstring> player, int iAmount);
IMPORT HK_ERROR HkKick(CAccount* acc);
IMPORT HK_ERROR HkKick(std::variant<uint, std::wstring> player);
IMPORT HK_ERROR HkKickReason(std::variant<uint, std::wstring> player, const std::wstring& wscReason);
IMPORT HK_ERROR HkBan(std::variant<uint, std::wstring> player, bool bBan);
IMPORT HK_ERROR HkBeam(std::variant<uint, std::wstring> player, const std::wstring& wscBasename);
IMPORT HK_ERROR HkSaveChar(std::variant<uint, std::wstring> player);
IMPORT HK_ERROR HkEnumCargo(std::variant<uint, std::wstring> player, std::list<CARGO_INFO>& lstCargo, int& iRemainingHoldSize);
IMPORT HK_ERROR HkRemoveCargo(std::variant<uint, std::wstring> player, uint iID, int iCount);
IMPORT HK_ERROR HkAddCargo(std::variant<uint, std::wstring> player, uint iGoodID, int iCount, bool bMission);
IMPORT HK_ERROR HkAddCargo(std::variant<uint, std::wstring> player, const std::wstring& wscGood, int iCount, bool bMission);
IMPORT HK_ERROR HkRename(std::variant<uint, std::wstring> player, const std::wstring& wscNewCharname, bool bOnlyDelete);
IMPORT HK_ERROR HkMsgAndKick(uint iClientID, const std::wstring& wscReason, uint iIntervall);
IMPORT HK_ERROR HkKill(std::variant<uint, std::wstring> player);
IMPORT HK_ERROR HkGetReservedSlot(std::variant<uint, std::wstring> player, bool& bResult);
IMPORT HK_ERROR HkSetReservedSlot(std::variant<uint, std::wstring> player, bool bReservedSlot);
IMPORT void HkPlayerAutoBuy(uint iClientID, uint iBaseID);
IMPORT HK_ERROR HkResetRep(std::variant<uint, std::wstring> player);
IMPORT HK_ERROR HkGetGroupMembers(std::variant<uint, std::wstring> player, std::list<GROUP_MEMBER>& lstMembers);
IMPORT HK_ERROR HkSetRep(std::variant<uint, std::wstring> player, const std::wstring& wscRepGroup, float fValue);
IMPORT HK_ERROR HkGetRep(std::variant<uint, std::wstring> player, const std::wstring& wscRepGroup, float& fValue);
IMPORT HK_ERROR HkReadCharFile(std::variant<uint, std::wstring> player, std::list<std::wstring>& lstOutput);
IMPORT HK_ERROR HkWriteCharFile(std::variant<uint, std::wstring> player, std::wstring wscData);
IMPORT HK_ERROR HkPlayerRecalculateCRC(uint iClientID);
IMPORT std::string HkGetPlayerSystemS(uint iClientID);
IMPORT bool IsInRange(uint iClientID, float fDistance);
IMPORT std::wstring GetLocation(unsigned int iClientID);
IMPORT HK_ERROR HkAddEquip(std::variant<uint, std::wstring> player, uint iGoodID, const std::string& scHardpoint);
IMPORT HK_ERROR HkAntiCheat(uint iClientID);
IMPORT void HkDelayedKick(uint iClientID, uint secs);
IMPORT HK_ERROR HkDeleteCharacter(CAccount* acc, std::wstring& wscCharname);
IMPORT HK_ERROR HkNewCharacter(CAccount* acc, std::wstring& wscCharname);
IMPORT std::wstring HkGetAccountIDByClientID(uint iClientID);
IMPORT HK_ERROR HkGetOnlineTime(std::variant<uint, std::wstring> player, int& iSecs);
IMPORT HK_ERROR HkGetRank(std::variant<uint, std::wstring> player, int& iRank);
IMPORT HK_ERROR HKGetShipValue(std::variant<uint, std::wstring> player, float& fValue);
IMPORT void HkRelocateClient(uint iClientID, Vector vDestination, Matrix mOrientation);
IMPORT void HkSaveChar(uint iClientID);

// HkFuncLog
#define AddBothLog(s, ...)           \
	{                                \
		AddLog(s, __VA_ARGS__);      \
		AddDebugLog(s, __VA_ARGS__); \
	}
IMPORT void AddLog(enum LogType, LogLevel level, std::wstring wStr, ...);
IMPORT void HkHandleCheater(uint iClientID, bool bBan, std::wstring wscReason, ...);
IMPORT bool HkAddCheaterLog(std::variant<uint, std::wstring> player, const std::wstring& wscReason);
IMPORT bool HkAddKickLog(uint iClientID, std::wstring wscReason, ...);
IMPORT bool HkAddConnectLog(uint iClientID, std::wstring wscReason, ...);

// HkFuncOther
IMPORT void HkGetPlayerIP(uint iClientID, std::wstring& wscIP);
IMPORT HK_ERROR HkGetPlayerInfo(std::variant<uint, std::wstring> player, HKPLAYERINFO& pi, bool bAlsoCharmenu);
IMPORT std::list<HKPLAYERINFO> HkGetPlayers();
IMPORT HK_ERROR HkGetConnectionStats(uint iClientID, DPN_CONNECTION_INFO& ci);
IMPORT HK_ERROR HkSetAdmin(std::variant<uint, std::wstring> player, const std::wstring& wscRights);
IMPORT HK_ERROR HkGetAdmin(std::variant<uint, std::wstring> player, std::wstring& wscRights);
IMPORT HK_ERROR HkDelAdmin(std::variant<uint, std::wstring> player);
IMPORT HK_ERROR HkChangeNPCSpawn(bool bDisable);
IMPORT HK_ERROR HkGetBaseStatus(const std::wstring& wscBasename, float& fHealth, float& fMaxHealth);
IMPORT bool HkLightFuse(IObjRW* ship, uint iFuseID, float fDelay, float fLifetime, float fSkip);
IMPORT bool HkUnLightFuse(IObjRW* ship, uint iFuseID);
IMPORT CEqObj* HkGetEqObjFromObjRW(struct IObjRW* objRW);
IMPORT uint HkGetClientIDFromArg(const std::wstring& wscArg);

// HkFLIni
IMPORT HK_ERROR HkFLIniGet(std::variant<uint, std::wstring> player, const std::wstring& wscKey, std::wstring& wscRet);
IMPORT HK_ERROR HkFLIniWrite(std::variant<uint, std::wstring> player, const std::wstring& wscKey, const std::wstring& wscValue);

IMPORT std::wstring HkErrGetText(HK_ERROR hkErr);

IMPORT void UserCmd_SetDieMsg(uint iClientID, const std::wstring& wscParam);
IMPORT void UserCmd_SetChatFont(uint iClientID, const std::wstring& wscParam);

IMPORT void ProcessEvent(std::wstring wscText, ...);

IMPORT void PrintUserCmdText(uint iClientID, std::wstring wscText, ...);
IMPORT void PrintLocalUserCmdText(uint iClientID, const std::wstring& wscMsg, float fDistance);

// Tools
class IMPORT Console
{
  public:
	static void ConPrint(std::wstring wStr, ...);
	static void ConErr(std::wstring wStr, ...);
	static void ConWarn(std::wstring wStr, ...);
	static void ConInfo(std::wstring wStr, ...);
	static void ConDebug(std::wstring wStr, ...);
};

IMPORT void HkSetCharacterIni(uint client, const std::wstring& name, std::wstring value);

IMPORT std::wstring HkGetCharacterIniString(uint client, const std::wstring& name);
IMPORT bool HkGetCharacterIniBool(uint client, const std::wstring& name);
IMPORT int HkGetCharacterIniInt(uint client, const std::wstring& name);
IMPORT uint HkGetCharacterIniUint(uint client, const std::wstring& name);
IMPORT float HkGetCharacterIniFloat(uint client, const std::wstring& name);
IMPORT double HkGetCharacterIniDouble(uint client, const std::wstring& name);
IMPORT int64_t HkGetCharacterIniInt64(uint client, const std::wstring& name);

IMPORT std::wstring stows(const std::string& scText);
IMPORT std::string wstos(const std::wstring& wscText);
IMPORT std::string IniGetS(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::string& scDefault);
IMPORT int IniGetI(const std::string& scFile, const std::string& scApp, const std::string& scKey, int iDefault);
IMPORT bool IniGetB(const std::string& scFile, const std::string& scApp, const std::string& scKey, bool bDefault);
IMPORT void IniWrite(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::string& scValue);
IMPORT void WriteProcMem(void* pAddress, const void* pMem, int iSize);
IMPORT void ReadProcMem(void* pAddress, void* pMem, int iSize);
IMPORT int ToInt(const std::wstring& wscStr);
IMPORT std::wstring XMLText(const std::wstring& wscText);
IMPORT std::wstring GetParam(const std::wstring& wscLine, wchar_t wcSplitChar, uint iPos);
IMPORT std::string GetParam(std::string scLine, char cSplitChar, uint iPos);
IMPORT std::wstring ReplaceStr(const std::wstring& wscSource, const std::wstring& wscSearchFor, const std::wstring& wscReplaceWith);
IMPORT void IniDelSection(const std::string& scFile, const std::string& scApp);
IMPORT void IniWriteW(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::wstring& wscValue);
IMPORT std::wstring IniGetWS(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::wstring& wscDefault);
IMPORT std::wstring ToMoneyStr(int iCash);
IMPORT float IniGetF(const std::string& scFile, const std::string& scApp, const std::string& scKey, float fDefault);
IMPORT void IniGetSection(const std::string& scFile, const std::string& scApp, std::list<INISECTIONVALUE>& lstValues);
IMPORT float ToFloat(const std::wstring& wscStr);
IMPORT mstime timeInMS();
IMPORT void SwapBytes(void* ptr, uint iLen);
IMPORT FARPROC PatchCallAddr(char* hMod, DWORD dwInstallAddress, char* dwHookFunction);
IMPORT std::wstring ToLower(std::wstring wscStr);
IMPORT std::string ToLower(std::string wscStr);
IMPORT std::wstring GetParamToEnd(const std::wstring& wscLine, wchar_t wcSplitChar, uint iPos);
IMPORT void ini_write_wstring(FILE* file, const std::string& parmname, const std::wstring& in);
IMPORT void ini_get_wstring(INI_Reader& ini, std::wstring& wscValue);
template<typename Str>
IMPORT Str Trim(const Str& scIn);
IMPORT std::wstring GetTimeString(bool bLocalTime);
IMPORT std::string GetUserFilePath(std::variant<uint, std::wstring> player, const std::string& scExtension);
IMPORT mstime GetTimeInMS();

// flcodec
IMPORT bool flc_decode(const char* ifile, const char* ofile);
IMPORT bool flc_encode(const char* ifile, const char* ofile);

// admin commands

// enums
enum CCMDS_RIGHTS
{
	RIGHT_NOTHING = 0,
	RIGHT_SUPERADMIN = 0xFFFFFFFF,
	RIGHT_MSG = (1 << 0),
	RIGHT_KICKBAN = (1 << 1),
	RIGHT_EVENTMODE = (1 << 2),
	RIGHT_CASH = (1 << 3),
	RIGHT_BEAMKILL = (1 << 4),
	RIGHT_REPUTATION = (1 << 5),
	RIGHT_CARGO = (1 << 6),
	RIGHT_CHARACTERS = (1 << 7),
	RIGHT_SETTINGS = (1 << 8),
	RIGHT_PLUGINS = (1 << 9),
	RIGHT_OTHER = (1 << 10),
	RIGHT_SPECIAL1 = (1 << 11),
	RIGHT_SPECIAL2 = (1 << 12),
	RIGHT_SPECIAL3 = (1 << 13),
};

class CTimer
{
  public:
	IMPORT CTimer(std::string sFunction, uint iWarning);
	IMPORT void start();
	IMPORT uint stop();

  private:
	mstime tmStart;
	uint iMax;
	std::string sFunction;
	uint iWarning;
};

// admin stuff
class CCmds
{
	bool bID;
	bool bShortCut;
	bool bSelf;
	bool bTarget;

  public:
	DWORD rights;
	HK_ERROR hkLastErr;

	IMPORT void PrintError();

	// commands
	void CmdGetCash(std::variant<uint, std::wstring> player);
	void CmdSetCash(std::variant<uint, std::wstring> player, int iAmount);
	void CmdSetCashSec(std::variant<uint, std::wstring> player, int iAmountCheck, int iAmount);
	void CmdAddCash(std::variant<uint, std::wstring> player, int iAmount);
	void CmdAddCashSec(std::variant<uint, std::wstring> player, int iAmountCheck, int iAmount);

	void CmdKick(std::variant<uint, std::wstring> player, const std::wstring& wscReason);
	void CmdBan(std::variant<uint, std::wstring> player);
	void CmdUnban(std::variant<uint, std::wstring> player);
	void CmdKickBan(std::variant<uint, std::wstring> player, const std::wstring& wscReason);

	void CmdBeam(std::variant<uint, std::wstring> player, const std::wstring& wscBasename);
	void CmdChase(std::wstring wscAdminName, std::variant<uint, std::wstring> player);
	void CmdPull(std::wstring wscAdminName, std::variant<uint, std::wstring> player);
	void CmdMove(std::wstring wscAdminName, float x, float y, float z);
	void CmdKill(std::variant<uint, std::wstring> player);
	void CmdResetRep(std::variant<uint, std::wstring> player);
	void CmdSetRep(std::variant<uint, std::wstring> player, const std::wstring& wscRepGroup, float fValue);
	void CmdGetRep(std::variant<uint, std::wstring> player, const std::wstring& wscRepGroup);

	void CmdMsg(std::variant<uint, std::wstring> player, const std::wstring& wscText);
	void CmdMsgS(const std::wstring& wscSystemname, const std::wstring& wscText);
	void CmdMsgU(const std::wstring& wscText);
	void CmdFMsg(std::variant<uint, std::wstring> player, const std::wstring& wscXML);
	void CmdFMsgS(const std::wstring& wscSystemname, const std::wstring& wscXML);
	void CmdFMsgU(const std::wstring& wscXML);

	void CmdEnumCargo(std::variant<uint, std::wstring> player);
	void CmdRemoveCargo(std::variant<uint, std::wstring> player, uint iID, uint iCount);
	void CmdAddCargo(std::variant<uint, std::wstring> player, const std::wstring& wscGood, uint iCount, uint iMission);

	void CmdRename(std::variant<uint, std::wstring> player, const std::wstring& wscNewCharname);
	void CmdDeleteChar(std::variant<uint, std::wstring> player);

	void CmdReadCharFile(std::variant<uint, std::wstring> player);
	void CmdWriteCharFile(std::variant<uint, std::wstring> player, const std::wstring& wscData);

	void CmdGetBaseStatus(const std::wstring& wscBasename);
	void CmdGetClientId(std::wstring player);
	void PrintPlayerInfo(HKPLAYERINFO pi);
	void CmdGetPlayerInfo(std::variant<uint, std::wstring> player);
	void CmdGetPlayers();
	void XPrintPlayerInfo(HKPLAYERINFO pi);
	void CmdXGetPlayerInfo(std::variant<uint, std::wstring> player);
	void CmdXGetPlayers();
	void CmdGetPlayerIDs();
	void CmdHelp();
	void CmdGetAccountDirName(std::variant<uint, std::wstring> player);
	void CmdGetCharFileName(std::variant<uint, std::wstring> player);
	void CmdIsOnServer(std::wstring player);
	void CmdIsLoggedIn(std::wstring player);
	void CmdMoneyFixList();
	void CmdServerInfo();
	void CmdGetGroupMembers(std::variant<uint, std::wstring> player);

	void CmdSaveChar(std::variant<uint, std::wstring> player);

	void CmdGetReservedSlot(std::variant<uint, std::wstring> player);
	void CmdSetReservedSlot(std::variant<uint, std::wstring> player, int iReservedSlot);
	void CmdSetAdmin(std::variant<uint, std::wstring> player, const std::wstring& wscRights);
	void CmdGetAdmin(std::variant<uint, std::wstring> player);
	void CmdDelAdmin(std::variant<uint, std::wstring> player);
	void CmdRehash();
	void CmdUnload(const std::wstring& wscParam);

	void CmdLoadPlugins();
	void CmdListPlugins();
	void CmdUnloadPlugin(const std::wstring& wscPlugin);
	void CmdPausePlugin(const std::wstring& wscPlugin);
	void CmdUnpausePlugin(const std::wstring& wscPlugin);

	void CmdTest(int iArg, int iArg2, int iArg3);
	//
	IMPORT std::wstring ArgCharname(uint iArg);
	IMPORT int ArgInt(uint iArg);
	IMPORT uint ArgUInt(uint iArg);
	IMPORT float ArgFloat(uint iArg);
	IMPORT std::wstring ArgStr(uint iArg);
	IMPORT std::wstring ArgStrToEnd(uint iArg);
	void ExecuteCommandString(const std::wstring& wscCmd);

	void SetRightsByString(std::string scRightStr);
	IMPORT void Print(std::wstring wscText, ...);
	virtual void DoPrint(std::wstring wscText) {};
	IMPORT virtual std::wstring GetAdminName() { return L""; };

	std::wstring wscCurCmdString;
};

// namespaces
namespace HkIServerImpl
{
	IMPORT extern bool g_InSubmitChat;
	IMPORT extern uint g_TextLength;
} // namespace HkIServerImpl

// variables
extern IMPORT bool g_bPlugin_nofunctioncall;

extern IMPORT std::map<std::string, std::list<PLUGIN_HOOKDATA>*> mpPluginHooks;
extern IMPORT std::list<PLUGIN_DATA> lstPlugins;

extern IMPORT HkIClientImpl* FakeClient;
extern IMPORT HkIClientImpl* HookClient;
extern IMPORT char* OldClient;

extern IMPORT uint g_DmgTo;
extern IMPORT uint g_DmgToSpaceID;

extern IMPORT bool g_bMsg;
extern IMPORT bool g_bMsgS;
extern IMPORT bool g_bMsgU;

extern IMPORT HANDLE hProcFL;
extern IMPORT HMODULE hModServer;
extern IMPORT HMODULE hModCommon;
extern IMPORT HMODULE hModRemoteClient;
extern IMPORT HMODULE hModDPNet;
extern IMPORT HMODULE hModDaLib;
extern IMPORT HMODULE hModContent;
extern IMPORT FILE* fLog;
extern IMPORT FILE* fLogDebug;
extern IMPORT FARPROC fpOldUpdate;
extern IMPORT std::string sDebugLog;

/** A base class/struct used for denoting that a class can be scanned.
 * Reflectable values are int, uint, bool, float, string, Reflectable, and std::vectors of the previous types.
 * Reflectables are interpreted as headers of the provided name.
 * Circular references are not handled and will crash.
 * Marking a field as reflectable without properly initalizing it will crash upon attempted deserialization.
 * Ensure that the default CTOR initalizes all fields.
 */
struct IMPORT Reflectable
{
	virtual ~Reflectable() = default;
	//! @brief The file name/path of the json file to load. If null, it must be provided in the Serializer::* function
	virtual std::string File() { return {}; }
};

struct IMPORT FLHookConfig final : Reflectable, Singleton<FLHookConfig>
{
	std::string File() override;

	struct General final : Reflectable
	{
		bool autobuy = false;
		uint antiDockKill = 4000;
		uint antiF1 = 0;
		bool changeCruiseDisruptorBehaviour = 0;
		bool debugMode = false;
		bool dieMsg = true;
		bool disableCharfileEncryption = false;
		uint disconnectDelay = 0;
		uint disableNPCSpawns = 0;
		bool dockingMessages = true;
		bool localTime = false;
		uint maxGroupSize = 8;
		bool persistGroup = false;
		uint reservedSlots = 0;
		float torpMissileBaseDamageMultiplier = 1.0f;
		bool logPerformanceTimers = false;

		std::vector<std::wstring> chatSuppressList;
		std::vector<std::string> noPVPSystems;

		std::vector<uint> noPVPSystemsHashed;
		uint antiBaseIdle = 600;
		uint antiCharMenuIdle = 600;
	};

	struct Plugins final : Reflectable
	{
		bool loadAllPlugins = true;
		std::vector<std::string> plugins = {};
	};

	struct MsgStyle final : Reflectable
	{
		std::wstring deathMsgStyle = L"0x19198C01";
		std::wstring deathMsgStyleSys = L"0x1919BD01";
		uint kickMsgPeriod = 5000;
		std::wstring kickMsg = LR"(<TRA data=" 0x0000FF10 " mask=" - 1 "/><TEXT>You will be kicked. Reason: %reason</TEXT>)";
		std::wstring userCmdStyle = L"0x00FF0090";
		std::wstring adminCmdStyle = L"0x00FF0090";
		std::wstring deathMsgTextAdminKill = L"Death: %victim was killed by an admin";
		std::wstring deathMsgTextPlayerKill = L"Death: %victim was killed by %killer (%type)";
		std::wstring deathMsgTextSelfKill = L"Death: %victim killed himself (%type)";
		std::wstring deathMsgTextNPC = L"Death: %victim was killed by an NPC";
		std::wstring deathMsgTextSuicide = L"Death: %victim committed suicide";
	};

	struct Socket final : Reflectable
	{
		bool activated = false;
		int port = 1919;
		int wPort = 1920;
		int ePort = 1921;
		int eWPort = 1922;
		std::string encryptionKey = "SomeRandomKey000";

		void* bfCTX;
		std::map<std::string, std::string> passRightsMap;
	};

	struct UserCommands final : Reflectable
	{
		bool userCmdSetDieMsgSize = true;
		bool userCmdSetDieMsg = true;
		bool userCmdSetChatFont = true;
		bool userCmdIgnore = true;
		bool userCmdHelp = true;
		uint userCmdMaxIgnoreList = true;
		bool defaultLocalChat = false;
	};

	struct MultiKillMessages final : Reflectable
	{
		bool active = false;
		std::wstring multiKillMessageStyle = L"0x1919BD01";
		std::map<std::wstring, int> multiKillMessages = {{L"%player is on a rampage", 5}, {L"%player runs amok", 10}, {L"%player is godlike", 15}};
	};

	struct Bans final : Reflectable
	{
		bool banAccountOnMatch = false;
		std::vector<std::wstring> banWildcardsAndIPs;
	};

	General general;
	Plugins plugins;
	Socket socket;
	MsgStyle msgStyle;
	UserCommands userCommands;
	MultiKillMessages multiKillMessages;
	Bans bans;
};

extern IMPORT std::list<BASE_INFO> lstBases;

extern IMPORT CDPClientProxy** g_cClientProxyArray;
extern IMPORT void* pClient;

extern IMPORT _RCSendChatMsg RCSendChatMsg;
extern IMPORT _CRCAntiCheat CRCAntiCheat;
extern IMPORT _CreateChar CreateChar;

extern IMPORT std::string scAcctPath;

#define MAX_CLIENT_ID 249
extern IMPORT CLIENT_INFO ClientInfo[MAX_CLIENT_ID + 1];
extern IMPORT CDPServer* cdpSrv;
extern IMPORT uint g_iServerLoad;
extern IMPORT uint g_iPlayerCount;
extern IMPORT bool g_bNPCDisabled;
extern IMPORT char* g_FLServerDataPtr;
extern IMPORT bool g_NonGunHitsBase;
extern IMPORT float g_LastHitPts;

// help

typedef bool (*_HelpEntryDisplayed)(uint);
extern IMPORT void HkAddHelpEntry(
    const std::wstring& c, const std::wstring& t, const std::wstring& shelp, const std::wstring& lhelp, _HelpEntryDisplayed check);
extern IMPORT void HkRemoveHelpEntry(const std::wstring& c, const std::wstring& t);
extern IMPORT bool get_bTrue(uint iClientID);

// blowfish

typedef struct
{
	unsigned long P[16 + 2];
	unsigned long S[4][256];
} BLOWFISH_CTX;

IMPORT void Blowfish_Init(BLOWFISH_CTX* ctx, unsigned char* key, int keyLen);
IMPORT char Blowfish_Encrypt(BLOWFISH_CTX* ctx, void* ptr, unsigned long dataLen);
IMPORT char Blowfish_Decrypt(BLOWFISH_CTX* ctx, void* ptr, unsigned long dataLen);

struct SYSTEMINFO
{
	/** The system nickname */
	std::string sysNick;

	/** The system id */
	uint systemId;

	/** The system scale */
	float scale;
};

struct TransformMatrix
{
	float d[4][4];
};

struct ZONE
{
	/** The system nickname */
	std::string sysNick;

	/** The zone nickname */
	std::string zoneNick;

	/** The id of the system for this zone */
	uint systemId;

	/** The zone transformation matrix */
	TransformMatrix transform;

	/** The zone ellipsoid size */
	Vector size;

	/** The zone position */
	Vector pos;

	/** The damage this zone causes per second */
	int damage;

	/** Is this an encounter zone */
	bool encounter;
};

class JUMPPOINT
{
  public:
	/** The system nickname */
	std::string sysNick;

	/** The jump point nickname */
	std::string jumpNick;

	/** The jump point destination system nickname */
	std::string jumpDestSysNick;

	/** The id of the system for this jump point. */
	uint System;

	/** The id of the jump point. */
	uint jumpID;

	/** The jump point destination system id */
	uint jumpDestSysID;
};

struct LOOTABLE_ZONE
{
	/** The zone nickname */
	std::string zoneNick;

	/** The id of the system for this lootable zone */
	uint systemID;

	/** The nickname and arch id of the loot dropped by the asteroids */
	std::string lootNick;
	uint iLootID;

	/** The arch id of the crate the loot is dropped in */
	uint iCrateID;

	/** The minimum number of loot items to drop */
	uint iMinLoot;

	/** The maximum number of loot items to drop */
	uint iMaxLoot;

	/** The drop difficultly */
	uint iLootDifficulty;

	/** The lootable zone ellipsoid size */
	Vector size;

	/** The lootable zone position */
	Vector pos;
};
typedef std::multimap<uint, LOOTABLE_ZONE, std::less<>> zone_map_t;

/** A map of system id to system info */
extern IMPORT std::map<uint, SYSTEMINFO> mapSystems;

/** A map of system id to zones */
extern IMPORT std::multimap<uint, ZONE> zones;

/** A map of system id to jumppoint info */
extern IMPORT std::multimap<uint, JUMPPOINT> jumpPoints;

namespace ZoneUtilities
{
	IMPORT void ReadUniverse(zone_map_t* set_mmapZones);
	IMPORT void ReadLootableZone(zone_map_t& set_mmapZones, const std::string& systemNick, const std::string& defaultZoneNick, const std::string& file);
	IMPORT void ReadSystemLootableZones(zone_map_t& set_mmapZones, const std::string& systemNick, const std::string& file);
	IMPORT void ReadSystemZones(zone_map_t& set_mmapZones, const std::string& systemNick, const std::string& file);
	IMPORT bool InZone(uint systemID, const Vector& pos, ZONE& rlz);
	IMPORT bool InDeathZone(uint systemID, const Vector& pos, ZONE& rlz);
	IMPORT SYSTEMINFO* GetSystemInfo(uint systemID);
	IMPORT void PrintZones();
} // namespace ZoneUtilities

#endif
