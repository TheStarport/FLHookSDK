#ifndef _FLHOOK_
#define _FLHOOK_

#pragma warning(disable: 4311 4786)

#include <windows.h>
#include <stdio.h>
#include <string>
#include <set>
#include <list>
#include <time.h>
#include <map>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// defines

#define HKHKSUCCESS(a) ((a) == HKE_OK)
#define HKSUCCESS(a) ((hkLastErr = (a)) == HKE_OK)

#define SRV_ADDR(a) ((char*)hModServer + a)
#define DALIB_ADDR(a) ((char*)hModDaLib + a)
#define FLSERVER_ADDR(a) ((char*)hProcFL + a)
#define CONTENT_ADDR(a) ((char*)hModContent + a)
#define ARG_CLIENTID(a) (std::wstring(L"id ") + stows(itos(a)))

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
	SEHException(uint code, EXCEPTION_POINTERS* ep)
		: code(code), record(*ep->ExceptionRecord), context(*ep->ContextRecord)
	{ }

	uint code;
	EXCEPTION_RECORD record;
	CONTEXT context;

	static void Translator(uint code, EXCEPTION_POINTERS* ep)
	{
		throw SEHException(code, ep);
	}
};

EXPORT extern void WriteMiniDump(SEHException* ex);
EXPORT extern void AddExceptionInfoLog(SEHException* ex);
#define TRY_HOOK try { _set_se_translator(SEHException::Translator);
#define CATCH_HOOK(e) } \
catch(SEHException& ex) { e; AddBothLog("ERROR: SEH Exception in %s on line %d; minidump may contain more information.", __FUNCTION__, __LINE__); AddExceptionInfoLog(&ex); } \
catch(std::exception& ex) { e; AddBothLog("ERROR: STL Exception in %s on line %d: %s.", __FUNCTION__, __LINE__, ex.what()); AddExceptionInfoLog(0); } \
catch (...) { e; AddBothLog("ERROR: Exception in %s on line %d.", __FUNCTION__, __LINE__); AddExceptionInfoLog(0); }
#else
#define TRY_HOOK try
#define CATCH_HOOK(e) catch(...) { e; AddLog("ERROR: Exception in %s", __FUNCTION__); }
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef void*(*st6_malloc_t)(size_t);
typedef void(*st6_free_t)(void*);

extern IMPORT st6_malloc_t st6_malloc;
extern IMPORT st6_free_t st6_free;
#define ST6_ALLOCATION_DEFINED

#include "FLCoreCommon.h"
#include "FLCoreServer.h"
#include "FLCoreRemoteClient.h"
#include "FLCoreDALib.h"

#include "plugin.h"

typedef void (__stdcall *_RCSendChatMsg)(uint iId, uint iTo, uint iSize, void *pRDL);
typedef void (__stdcall *_CRCAntiCheat)();
typedef void (__stdcall *_CreateChar)(const wchar_t *wszName);
typedef int (__cdecl *_GetFLName)(char *szBuf, const wchar_t *wszStr);
typedef bool (__cdecl *_GetShipInspect)(uint &iShip, IObjInspectImpl* &inspect, uint &iDunno);

extern IMPORT _GetShipInspect GetShipInspect;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// enums

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
	long	dwRemoteAddress;
	FARPROC fpOldProc;
};

struct CARGO_INFO
{
	uint		iID;
	int			iCount;
	uint		iArchID;
	float		fStatus;
	bool		bMission;
	bool		bMounted;
	CacheString	hardpoint;
};


// money stuff
struct MONEY_FIX
{
	std::wstring		wscCharname;
	int			iAmount;

	bool operator==(MONEY_FIX mf1)
	{
		if(!wscCharname.compare(mf1.wscCharname))
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
	uint		iShip;
	uint		iShipOld;
	mstime		tmSpawnTime;

	DamageList	dmgLast;

// money cmd
	std::list<MONEY_FIX> lstMoneyFix;

// anticheat
	uint		iTradePartner;

// change cruise disruptor behaviour
	bool		bCruiseActivated;
	bool		bThrusterActivated;
	bool		bEngineKilled;
	bool		bTradelane;

// idle kicks
	uint		iBaseEnterTime;
	uint		iCharMenuEnterTime;

// msg, wait and kick
	mstime		tmKickTime;

// eventmode
	uint		iLastExitedBaseID;
	bool		bDisconnected;

// f1 laming
	bool		bCharSelected;
	mstime		tmF1Time;
	mstime		tmF1TimeDisconnect;

// ignore usercommand
	std::list<IGNORE_INFO> lstIgnore;

// user settings
	DIEMSGTYPE	dieMsg;
	CHATSIZE	dieMsgSize;
	CHATSTYLE	dieMsgStyle;
	CHATSIZE	chatSize;
	CHATSTYLE	chatStyle;

// autobuy
	bool		bAutoBuyMissiles;
	bool		bAutoBuyMines;
	bool		bAutoBuyTorps;
	bool		bAutoBuyCD;
	bool		bAutoBuyCM;
	bool		bAutoBuyReload;

// MultiKillMessages
	uint		iKillsInARow;

// bans
	uint		iConnects; // incremented when player connects

// other
	std::wstring		wscHostname;

	bool		bSpawnProtected;
	bool		bUseServersideHitDetection; //used by AC Plugin
	uchar		unused_data[127];
};

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
typedef struct _DPN_CONNECTION_INFO{
    DWORD   dwSize;
    DWORD   dwRoundTripLatencyMS;
    DWORD   dwThroughputBPS;
    DWORD   dwPeakThroughputBPS;
    DWORD   dwBytesSentGuaranteed;
    DWORD   dwPacketsSentGuaranteed;
    DWORD   dwBytesSentNonGuaranteed;
    DWORD   dwPacketsSentNonGuaranteed;
    DWORD   dwBytesRetried;
    DWORD   dwPacketsRetried;
    DWORD   dwBytesDropped;   
    DWORD   dwPacketsDropped; 
    DWORD   dwMessagesTransmittedHighPriority;
    DWORD   dwMessagesTimedOutHighPriority;
    DWORD   dwMessagesTransmittedNormalPriority;
    DWORD   dwMessagesTimedOutNormalPriority;
    DWORD   dwMessagesTransmittedLowPriority;
    DWORD   dwMessagesTimedOutLowPriority;
    DWORD   dwBytesReceivedGuaranteed;
    DWORD   dwPacketsReceivedGuaranteed;
    DWORD   dwBytesReceivedNonGuaranteed;
    DWORD   dwPacketsReceivedNonGuaranteed;
    DWORD   dwMessagesReceived;
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
	void *pNewValue;
	uint iSize;
	void *pOldValue;
	bool bAlloced;
};

struct PATCH_INFO
{
	char	*szBinName;
	ulong	pBaseAddress;

	PATCH_INFO_ENTRY piEntries[128];
};

struct DATA_MARKETITEM
{
	uint iArchID;
	float fRep;
};

struct BASE_INFO
{
	uint	iBaseID;
	std::string	scBasename;
	uint	iObjectID;
	bool	bDestroyed;
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

// plugin
IMPORT void Plugin_Communication(PLUGIN_MESSAGE msgtype, void* msg);

// HkFuncTools
IMPORT uint HkGetClientIdFromAccount(CAccount *acc);
IMPORT uint HkGetClientIdFromPD(struct PlayerData *pPD);
IMPORT CAccount* HkGetAccountByCharname(const std::wstring &wscCharname);
IMPORT uint HkGetClientIdFromCharname(const std::wstring &wscCharname);
IMPORT std::wstring HkGetAccountID(CAccount *acc);
IMPORT bool HkIsEncoded(const std::string &scFilename);
IMPORT bool HkIsInCharSelectMenu(const std::wstring &wscCharname);
IMPORT bool HkIsInCharSelectMenu(uint iClientID);
IMPORT bool HkIsValidClientID(uint iClientID);
IMPORT HK_ERROR HkResolveId(const std::wstring &wscCharname, uint &iClientID);
IMPORT HK_ERROR HkResolveShortCut(const std::wstring &wscShortcut, uint &iClientID);
IMPORT uint HkGetClientIDByShip(uint iShip);
IMPORT HK_ERROR HkGetAccountDirName(CAccount *acc, std::wstring &wscDir);
IMPORT HK_ERROR HkGetAccountDirName(const std::wstring &wscCharname, std::wstring &wscDir);
IMPORT HK_ERROR HkGetCharFileName(const std::wstring &wscCharname, std::wstring &wscFilename);
IMPORT std::wstring HkGetBaseNickByID(uint iBaseID);
IMPORT std::wstring HkGetPlayerSystem(uint iClientID);
IMPORT std::wstring HkGetSystemNickByID(uint iSystemID);
IMPORT void HkLockAccountAccess(CAccount *acc, bool bKick);
IMPORT void HkUnlockAccountAccess(CAccount *acc);
IMPORT void HkGetItemsForSale(uint iBaseID, std::list<uint> &lstItems);
IMPORT IObjInspectImpl* HkGetInspect(uint iClientID);
IMPORT ENGINE_STATE HkGetEngineState(uint iClientID);
IMPORT EQ_TYPE HkGetEqType(Archetype::Equipment *eq);
IMPORT HK_ERROR HkGetClientID(bool& bIdString, uint& iClientID, const std::wstring &wscCharname);

#define HK_GET_CLIENTID(a, b) \
	bool bIdString = false; uint a = uint(-1); \
    if(auto err = HkGetClientID(bIdString, a, b); err != HKE_OK) return err;

// HkFuncMsg
IMPORT HK_ERROR HkMsg(int iClientID, const std::wstring &wscMessage);
IMPORT HK_ERROR HkMsg(const std::wstring &wscCharname, const std::wstring &wscMessage);
IMPORT HK_ERROR HkMsgS(const std::wstring &wscSystemname, const std::wstring &wscMessage);
IMPORT HK_ERROR HkMsgU(const std::wstring &wscMessage);
IMPORT HK_ERROR HkFMsgEncodeXML(const std::wstring &wscXML, char *szBuf, uint iSize, uint &iRet);
IMPORT HK_ERROR HkFMsgSendChat(uint iClientID, char *szBuf, uint iSize);
IMPORT HK_ERROR HkFMsg(uint iClientID, const std::wstring &wscXML);
IMPORT HK_ERROR HkFMsg(const std::wstring &wscCharname, const std::wstring &wscXML);
IMPORT HK_ERROR HkFMsgS(const std::wstring &wscSystemname, const std::wstring &wscXML);
IMPORT HK_ERROR HkFMsgU(const std::wstring &wscXML);

// HkFuncPlayers
IMPORT HK_ERROR HkGetCash(const std::wstring &wscCharname, int &iCash);
IMPORT HK_ERROR HkAddCash(const std::wstring &wscCharname, int iAmount);
IMPORT HK_ERROR HkKick(CAccount *acc);
IMPORT HK_ERROR HkKick(const std::wstring &wscCharname);
IMPORT HK_ERROR HkKickReason(const std::wstring &wscCharname, const std::wstring &wscReason);
IMPORT HK_ERROR HkBan(const std::wstring &wscCharname, bool bBan);
IMPORT HK_ERROR HkBeam(const std::wstring &wscCharname, const std::wstring &wscBasename);
IMPORT HK_ERROR HkSaveChar(const std::wstring &wscCharname);
IMPORT HK_ERROR HkEnumCargo(const std::wstring &wscCharname, std::list<CARGO_INFO> &lstCargo, int &iRemainingHoldSize);
IMPORT HK_ERROR HkRemoveCargo(const std::wstring &wscCharname, uint iID, int iCount);
IMPORT HK_ERROR HkAddCargo(const std::wstring &wscCharname, uint iGoodID, int iCount, bool bMission);
IMPORT HK_ERROR HkAddCargo(const std::wstring &wscCharname, const std::wstring &wscGood, int iCount, bool bMission);
IMPORT HK_ERROR HkRename(const std::wstring &wscCharname, const std::wstring &wscNewCharname, bool bOnlyDelete);
IMPORT HK_ERROR HkMsgAndKick(uint iClientID, const std::wstring &wscReason, uint iIntervall);
IMPORT HK_ERROR HkKill(const std::wstring &wscCharname);
IMPORT HK_ERROR HkGetReservedSlot(const std::wstring &wscCharname, bool &bResult);
IMPORT HK_ERROR HkSetReservedSlot(const std::wstring &wscCharname, bool bReservedSlot);
IMPORT void HkPlayerAutoBuy(uint iClientID, uint iBaseID);
IMPORT HK_ERROR HkResetRep(const std::wstring &wscCharname);
IMPORT HK_ERROR HkGetGroupMembers(const std::wstring &wscCharname, std::list<GROUP_MEMBER> &lstMembers);
IMPORT HK_ERROR HkSetRep(const std::wstring &wscCharname, const std::wstring &wscRepGroup, float fValue);
IMPORT HK_ERROR HkGetRep(const std::wstring &wscCharname, const std::wstring &wscRepGroup, float &fValue);
IMPORT HK_ERROR HkReadCharFile(const std::wstring &wscCharname, std::list<std::wstring> &lstOutput);
IMPORT HK_ERROR HkWriteCharFile(const std::wstring &wscCharname, std::wstring wscData);
IMPORT HK_ERROR HkPlayerRecalculateCRC(uint iClientID);

// HkFuncLog
#define AddBothLog(s, ...) { AddLog(s, __VA_ARGS__); AddDebugLog(s, __VA_ARGS__);  }
IMPORT void AddDebugLog(const char *szString, ...);
IMPORT void AddLog(const char *szString, ...);
IMPORT void HkHandleCheater(uint iClientID, bool bBan, std::wstring wscReason, ...);
IMPORT bool HkAddCheaterLog(const std::wstring &wscCharname, const std::wstring &wscReason);
IMPORT bool HkAddCheaterLog(const uint &iClientID, const std::wstring &wscReason);
IMPORT bool HkAddKickLog(uint iClientID, std::wstring wscReason, ...);
IMPORT bool HkAddConnectLog(uint iClientID, std::wstring wscReason, ...);
IMPORT void HkAddAdminCmdLog(const char *szString, ...);
IMPORT void HkAddUserCmdLog(const char *szString, ...);
IMPORT void HkAddPerfTimerLog(const char *szString, ...);

// HkFuncOther
IMPORT void HkGetPlayerIP(uint iClientID, std::wstring &wscIP);
IMPORT HK_ERROR HkGetPlayerInfo(const std::wstring &wscCharname, HKPLAYERINFO &pi, bool bAlsoCharmenu);
IMPORT std::list<HKPLAYERINFO> HkGetPlayers();
IMPORT HK_ERROR HkGetConnectionStats(uint iClientID, DPN_CONNECTION_INFO &ci);
IMPORT HK_ERROR HkSetAdmin(const std::wstring &wscCharname, const std::wstring &wscRights);
IMPORT HK_ERROR HkGetAdmin(const std::wstring &wscCharname, std::wstring &wscRights);
IMPORT HK_ERROR HkDelAdmin(const std::wstring &wscCharname);
IMPORT HK_ERROR HkChangeNPCSpawn(bool bDisable);
IMPORT HK_ERROR HkGetBaseStatus(const std::wstring &wscBasename, float &fHealth, float &fMaxHealth);

// HkFLIni
IMPORT HK_ERROR HkFLIniGet(const std::wstring &wscCharname, const std::wstring &wscKey, std::wstring &wscRet);
IMPORT HK_ERROR HkFLIniWrite(const std::wstring &wscCharname, const std::wstring &wscKey, const std::wstring &wscValue);

IMPORT std::wstring HkErrGetText(HK_ERROR hkErr);

IMPORT void UserCmd_SetDieMsg(uint iClientID, const std::wstring &wscParam);
IMPORT void UserCmd_SetChatFont(uint iClientID, const std::wstring &wscParam);

IMPORT void ProcessEvent(std::wstring wscText, ...);

IMPORT void PrintUserCmdText(uint iClientID, std::wstring wscText, ...);

// tools
IMPORT std::wstring stows(const std::string &scText);
IMPORT std::string wstos(const std::wstring &wscText);
IMPORT std::string itos(int i);
IMPORT std::string IniGetS(const std::string &scFile, const std::string &scApp, const std::string &scKey, const std::string &scDefault);
IMPORT int IniGetI(const std::string &scFile, const std::string &scApp, const std::string &scKey, int iDefault);
IMPORT bool IniGetB(const std::string &scFile, const std::string &scApp, const std::string &scKey, bool bDefault);
IMPORT void IniWrite(const std::string &scFile, const std::string &scApp, const std::string &scKey, const std::string &scValue);
IMPORT void WriteProcMem(void *pAddress, void *pMem, int iSize);
IMPORT void ReadProcMem(void *pAddress, void *pMem, int iSize);
IMPORT std::wstring ToLower(const std::wstring &wscStr);
IMPORT std::string ToLower(const std::string &scStr);
IMPORT int ToInt(const std::wstring &wscStr);
IMPORT void ConPrint(std::wstring wscText, ...);
IMPORT std::wstring XMLText(const std::wstring &wscText);
IMPORT std::wstring GetParam(const std::wstring &wscLine, wchar_t wcSplitChar, uint iPos);
IMPORT std::wstring ReplaceStr(const std::wstring &wscSource, const std::wstring &wscSearchFor, const std::wstring &wscReplaceWith);
IMPORT void IniDelSection(const std::string &scFile, const std::string &scApp);
IMPORT void IniWriteW(const std::string &scFile, const std::string &scApp, const std::string &scKey, const std::wstring &wscValue);
IMPORT std::wstring IniGetWS(const std::string &scFile, const std::string &scApp, const std::string &scKey, const std::wstring &wscDefault);
IMPORT std::wstring ToMoneyStr(int iCash);
IMPORT float IniGetF(const std::string &scFile, const std::string &scApp, const std::string &scKey, float fDefault);
IMPORT void IniGetSection(const std::string &scFile, const std::string &scApp, std::list<INISECTIONVALUE> &lstValues);
IMPORT float ToFloat(const std::wstring &wscStr);
IMPORT mstime timeInMS();
IMPORT void SwapBytes(void *ptr, uint iLen);
IMPORT FARPROC PatchCallAddr(char *hMod, DWORD dwInstallAddress, char *dwHookFunction);

// flcodec
IMPORT bool flc_decode(const char *ifile, const char *ofile);
IMPORT bool flc_encode(const char *ifile, const char *ofile);

// admin commands

// enums
enum CCMDS_RIGHTS
{
	RIGHT_NOTHING		= 0,
	RIGHT_SUPERADMIN	= 0xFFFFFFFF,
	RIGHT_MSG			= (1 << 0),
	RIGHT_KICKBAN		= (1 << 1),
	RIGHT_EVENTMODE		= (1 << 2),
	RIGHT_CASH			= (1 << 3),
	RIGHT_BEAMKILL		= (1 << 4),
	RIGHT_REPUTATION	= (1 << 5),
	RIGHT_CARGO			= (1 << 6),
	RIGHT_CHARACTERS	= (1 << 7),
	RIGHT_SETTINGS		= (1 << 8),
	RIGHT_PLUGINS		= (1 << 9),
	RIGHT_OTHER			= (1 << 10),
	RIGHT_SPECIAL1		= (1 << 11),
	RIGHT_SPECIAL2		= (1 << 12),
	RIGHT_SPECIAL3		= (1 << 13),
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
	void CmdGetCash(const std::wstring &wscCharname);
	void CmdSetCash(const std::wstring &wscCharname, int iAmount);
	void CmdSetCashSec(const std::wstring &wscCharname, int iAmountCheck, int iAmount);
	void CmdAddCash(const std::wstring &wscCharname, int iAmount);
	void CmdAddCashSec(const std::wstring &wscCharname, int iAmountCheck, int iAmount);

	void CmdKick(const std::wstring &wscCharname, const std::wstring &wscReason);
	void CmdBan(const std::wstring &wscCharname);
	void CmdUnban(const std::wstring &wscCharname);
	void CmdKickBan(const std::wstring &wscCharname, const std::wstring &wscReason);

	void CmdBeam(const std::wstring &wscCharname, const std::wstring &wscBasename);
	void CmdKill(const std::wstring &wscCharname);
	void CmdResetRep(const std::wstring &wscCharname);
	void CmdSetRep(const std::wstring &wscCharname, const std::wstring &wscRepGroup, float fValue);
	void CmdGetRep(const std::wstring &wscCharname, const std::wstring &wscRepGroup);

	void CmdMsg(const std::wstring &wscCharname, const std::wstring &wscText);
	void CmdMsgS(const std::wstring &wscSystemname, const std::wstring &wscText);
	void CmdMsgU(const std::wstring &wscText);
	void CmdFMsg(const std::wstring &wscCharname, const std::wstring &wscXML);
	void CmdFMsgS(const std::wstring &wscSystemname, const std::wstring &wscXML);
	void CmdFMsgU(const std::wstring &wscXML);

	void CmdEnumCargo(const std::wstring &wscCharname);
	void CmdRemoveCargo(const std::wstring &wscCharname, uint iID, uint iCount);
	void CmdAddCargo(const std::wstring &wscCharname, const std::wstring &wscGood, uint iCount, uint iMission);

	void CmdRename(const std::wstring &wscCharname, const std::wstring &wscNewCharname);
	void CmdDeleteChar(const std::wstring &wscCharname);

	void CmdReadCharFile(const std::wstring &wscCharname);
	void CmdWriteCharFile(const std::wstring &wscCharname, const std::wstring &wscData);

	void CmdGetBaseStatus(const std::wstring &wscBasename);
	void CmdGetClientId(const std::wstring &wscCharname);
	void PrintPlayerInfo(HKPLAYERINFO pi);
	void CmdGetPlayerInfo(const std::wstring &wscCharname);
	void CmdGetPlayers();
	void XPrintPlayerInfo(HKPLAYERINFO pi);
	void CmdXGetPlayerInfo(const std::wstring &wscCharname);
	void CmdXGetPlayers();
	void CmdGetPlayerIDs();
	void CmdHelp();
	void CmdGetAccountDirName(const std::wstring &wscCharname);
	void CmdGetCharFileName(const std::wstring &wscCharname);
	void CmdIsOnServer(const std::wstring &wscCharname);
	void CmdIsLoggedIn(const std::wstring &wscCharname);
	void CmdMoneyFixList();
	void CmdServerInfo();
	void CmdGetGroupMembers(const std::wstring &wscCharname);

	void CmdSaveChar(const std::wstring &wscCharname);

	void CmdGetReservedSlot(const std::wstring &wscCharname);
	void CmdSetReservedSlot(const std::wstring &wscCharname, int iReservedSlot);
	void CmdSetAdmin(const std::wstring &wscCharname, std::wstring wscRights);
	void CmdGetAdmin(const std::wstring &wscCharname);
	void CmdDelAdmin(const std::wstring &wscCharname);
	void CmdRehash();
	void CmdUnload(const std::wstring &wscParam);

	void CmdLoadPlugins();
	void CmdListPlugins();
	void CmdUnloadPlugin(const std::wstring &wscPlugin);
	void CmdPausePlugin(const std::wstring &wscPlugin);
	void CmdUnpausePlugin(const std::wstring &wscPlugin);

	void CmdTest(int iArg, int iArg2, int iArg3);
//
	IMPORT std::wstring ArgCharname(uint iArg);
	IMPORT int ArgInt(uint iArg);
	IMPORT uint ArgUInt(uint iArg);
	IMPORT float ArgFloat(uint iArg);
	IMPORT std::wstring ArgStr(uint iArg);
	IMPORT std::wstring ArgStrToEnd(uint iArg);
	void ExecuteCommandString(const std::wstring &wscCmd);

	void SetRightsByString(std::string scRightStr);
	IMPORT void Print(std::wstring wscText, ...);
	virtual void DoPrint(std::wstring wscText) {};
	IMPORT virtual std::wstring GetAdminName() { return L""; };

	std::wstring wscCurCmdString;
};


// namespaces
namespace HkIServerImpl 
{
	IMPORT extern bool g_bInSubmitChat;
	IMPORT extern uint g_iTextLen;
}
namespace PluginManager {
	IMPORT void LoadPlugins(bool, CCmds*);
	IMPORT void LoadPlugin(const std::string &sFileName, CCmds*);
	IMPORT HK_ERROR PausePlugin(const std::string &sShortName, bool bPause);
	IMPORT HK_ERROR UnloadPlugin(const std::string &sShortName);
	IMPORT void UnloadPlugins();
}

// variables
extern IMPORT bool g_bPlugin_nofunctioncall;

extern IMPORT std::map<std::string, std::list<PLUGIN_HOOKDATA>*> mpPluginHooks;
extern IMPORT std::list<PLUGIN_DATA> lstPlugins;

extern IMPORT HkIClientImpl* FakeClient;
extern IMPORT HkIClientImpl* HookClient;
extern IMPORT char* OldClient;

extern IMPORT uint	iDmgTo;
extern IMPORT uint iDmgToSpaceID;

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
extern IMPORT FILE *fLog;
extern IMPORT FILE *fLogDebug;
extern IMPORT FARPROC fpOldUpdate;
extern IMPORT std::string sDebugLog;

// setting variables
extern IMPORT bool set_bLoadedSettings;
extern IMPORT std::string set_scCfgFile;
extern IMPORT uint set_iAntiDockKill;
extern IMPORT std::set<uint> set_setNoPVPSystems;
extern IMPORT std::set<std::wstring> set_setChatSuppress;
extern IMPORT bool set_bSocketActivated;
extern IMPORT bool set_bDebug;
extern IMPORT bool set_bLogConnects;
extern IMPORT std::wstring set_wscDeathMsgStyle;
extern IMPORT std::wstring set_wscDeathMsgStyleSys;
extern IMPORT bool	set_bDieMsg;
extern IMPORT bool	set_bDisableCharfileEncryption;
extern IMPORT uint	set_iAntiBaseIdle;
extern IMPORT uint	set_iAntiCharMenuIdle;
extern IMPORT bool set_bChangeCruiseDisruptorBehaviour;
extern IMPORT bool	set_bUserCmdSetDieMsg;
extern IMPORT bool	set_bUserCmdSetChatFont;
extern IMPORT bool	set_bUserCmdIgnore;
extern IMPORT bool	set_bUserCmdHelp;
extern IMPORT uint	set_iDisableNPCSpawns;
extern IMPORT int	set_iPort;
extern IMPORT int	set_iWPort;
extern IMPORT std::wstring set_wscKickMsg;
extern IMPORT std::wstring set_wscUserCmdStyle;
extern IMPORT std::wstring set_wscAdminCmdStyle;
extern IMPORT uint	set_iKickMsgPeriod;
extern IMPORT std::wstring set_wscDeathMsgTextPlayerKill;
extern IMPORT std::wstring set_wscDeathMsgTextSelfKill;
extern IMPORT std::wstring set_wscDeathMsgTextNPC;
extern IMPORT std::wstring set_wscDeathMsgTextSuicide;
extern IMPORT uint	set_iAntiF1;
extern IMPORT std::wstring set_wscDeathMsgTextAdminKill;
extern IMPORT uint	set_iUserCmdMaxIgnoreList;
extern IMPORT uint	set_iReservedSlots;
extern IMPORT uint	set_iDisconnectDelay;
extern IMPORT bool	set_bAutoBuy;
extern IMPORT float set_fTorpMissileBaseDamageMultiplier;
extern IMPORT bool set_MKM_bActivated;
extern IMPORT std::wstring set_MKM_wscStyle;
extern IMPORT std::list<MULTIKILLMESSAGE> set_MKM_lstMessages;
extern IMPORT bool	set_bUserCmdSetDieMsgSize;
extern IMPORT uint	set_iMaxGroupSize;
extern IMPORT std::set<std::wstring> set_setBans;
extern IMPORT bool	set_bBanAccountOnMatch;
extern IMPORT uint set_iTimerThreshold;
extern IMPORT uint set_iTimerDebugThreshold;
extern IMPORT uint set_iDebugMaxSize;
extern IMPORT bool	set_bLogAdminCmds;
extern IMPORT bool	set_bLogSocketCmds;
extern IMPORT bool	set_bLogLocalSocketCmds;
extern IMPORT bool	set_bLogUserCmds;
extern IMPORT bool	set_bPerfTimer;


extern IMPORT std::list<BASE_INFO> lstBases;

extern IMPORT CDPClientProxy **g_cClientProxyArray;
extern IMPORT void *pClient;

extern IMPORT _RCSendChatMsg RCSendChatMsg;
extern IMPORT _CRCAntiCheat CRCAntiCheat;
extern IMPORT _CreateChar CreateChar;

extern IMPORT std::string scAcctPath;

#define MAX_CLIENT_ID 249
extern IMPORT CLIENT_INFO ClientInfo[MAX_CLIENT_ID+1];
extern IMPORT CDPServer *cdpSrv;
extern IMPORT uint g_iServerLoad;
extern IMPORT uint g_iPlayerCount;
extern IMPORT bool g_bNPCDisabled;
extern IMPORT char *g_FLServerDataPtr;
extern IMPORT bool g_gNonGunHitsBase;
extern IMPORT float g_LastHitPts;

// help

typedef bool (*_HelpEntryDisplayed)(uint);
extern IMPORT void HkAddHelpEntry(const std::wstring &c, const std::wstring &t, const std::wstring &shelp, const std::wstring &lhelp, _HelpEntryDisplayed check);
extern IMPORT void HkRemoveHelpEntry(const std::wstring &c, const std::wstring &t);
extern IMPORT bool get_bTrue(uint iClientID);

//blowfish

typedef struct {
  unsigned long P[16 + 2];
  unsigned long S[4][256];
} BLOWFISH_CTX;

IMPORT void Blowfish_Init(BLOWFISH_CTX *ctx, unsigned char *key, int keyLen);
IMPORT char Blowfish_Encrypt(BLOWFISH_CTX *ctx, void *ptr, unsigned long dataLen);
IMPORT char Blowfish_Decrypt(BLOWFISH_CTX *ctx, void *ptr, unsigned long dataLen);


#endif