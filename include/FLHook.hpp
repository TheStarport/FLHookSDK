#pragma once

#define _WINSOCKAPI_
#include <Windows.h>
#include <cstdio>
#include <string>
#include <set>
#include <list>
#include <ctime>
#include <map>
#include <filesystem>
#include <variant>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "WinSock2.h"

#include "Typedefs.hpp"
#include "Macros.hpp"
#include "Enums.hpp"
#include "Constexpr.hpp"

// Libs
#include "Singleton.h"
#include "Wildcard.hpp"
#include "magic_enum.hpp"

// Magic Enum Extensions
using namespace magic_enum::bitwise_operators;  // NOLINT
using namespace magic_enum::flags; // NOLINT
using namespace magic_enum::ostream_operators; // NOLINT

// ST6
extern DLL st6_malloc_t st6_malloc;
extern DLL st6_free_t st6_free;
#define ST6_ALLOCATION_DEFINED

#include "FLCoreCommon.h"
#include "FLCoreServer.h"
#include "FLCoreRemoteClient.h"
#include "FLCoreDALib.h"
#include "plugin.h"

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

DLL void ProcessEvent(std::wstring wscText, ...);

// Tools
class DLL Console
{
	static void Log(std::wstring& wStr, va_list args, void* addr);

	// Might use more later?
	enum class ConsoleColor
	{
		BLUE = 0x0001,
		GREEN = 0x0002,
		CYAN = BLUE | GREEN,
		RED = 0x0004,
		PURPLE = RED | BLUE,
		YELLOW = RED | GREEN,
		WHITE = RED | BLUE | GREEN,

		STRONG_BLUE = 0x0008 | BLUE,
		STRONG_GREEN = 0x0008 | GREEN,
		STRONG_CYAN = 0x0008 | CYAN,
		STRONG_RED = 0x0008 | RED,
		STRONG_PURPLE = 0x0008 | PURPLE,
		STRONG_YELLOW = 0x0008 | YELLOW,
		STRONG_WHITE = 0x0008 | WHITE,
	};

  public:
	// String
	static void ConPrint(std::string str, ...);
	static void ConErr(std::string str, ...);
	static void ConWarn(std::string str, ...);
	static void ConInfo(std::string str, ...);
	static void ConDebug(std::string str, ...);

	// Wide-string
	static void ConPrint(std::wstring wStr, ...);
	static void ConErr(std::wstring wStr, ...);
	static void ConWarn(std::wstring wStr, ...);
	static void ConInfo(std::wstring wStr, ...);
	static void ConDebug(std::wstring wStr, ...);
};

DLL std::wstring stows(const std::string& scText);
DLL std::string wstos(const std::wstring& wscText);
DLL std::string IniGetS(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::string& scDefault);
DLL int IniGetI(const std::string& scFile, const std::string& scApp, const std::string& scKey, int iDefault);
DLL bool IniGetB(const std::string& scFile, const std::string& scApp, const std::string& scKey, bool bDefault);
DLL void IniWrite(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::string& scValue);
DLL void WriteProcMem(void* pAddress, const void* pMem, int iSize);
DLL void ReadProcMem(void* pAddress, void* pMem, int iSize);
DLL int ToInt(const std::wstring& wscStr);
DLL uint ToUInt(const std::wstring& wscStr);
DLL std::wstring XMLText(const std::wstring& wscText);
DLL std::wstring GetParam(const std::wstring& wscLine, wchar_t wcSplitChar, uint iPos);
DLL std::wstring GetParam(const std::wstring_view& wscLine, wchar_t wcSplitChar, uint iPos);
DLL std::string GetParam(std::string scLine, char cSplitChar, uint iPos);
DLL std::wstring ReplaceStr(const std::wstring& wscSource, const std::wstring& wscSearchFor, const std::wstring& wscReplaceWith);
DLL void IniDelSection(const std::string& scFile, const std::string& scApp);
DLL void IniDelete(const std::string& scFile, const std::string& scApp, const std::string& scKey);
DLL void IniWriteW(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::wstring& wscValue);
DLL std::wstring IniGetWS(const std::string& scFile, const std::string& scApp, const std::string& scKey, const std::wstring& wscDefault);
DLL std::wstring ToMoneyStr(int iCash);
DLL float IniGetF(const std::string& scFile, const std::string& scApp, const std::string& scKey, float fDefault);
DLL void IniGetSection(const std::string& scFile, const std::string& scApp, std::list<INISECTIONVALUE>& lstValues);
DLL float ToFloat(const std::wstring& wscStr);
DLL mstime timeInMS();
DLL void SwapBytes(void* ptr, uint iLen);
DLL FARPROC PatchCallAddr(char* hMod, DWORD dwInstallAddress, char* dwHookFunction);
template<typename Str>
Str Trim(const Str& scIn);
template DLL std::string Trim(const std::string& scIn);
template DLL std::wstring Trim(const std::wstring& scIn);
DLL std::wstring ViewToWString(const std::wstring_view&);
DLL std::string ViewToString(const std::string_view&);
DLL BOOL FileExists(LPCTSTR szPath);
DLL std::wstring ToLower(std::wstring wscStr);
DLL std::string ToLower(std::string wscStr);
DLL std::wstring_view GetParamToEnd(const std::wstring_view& wscLine, wchar_t wcSplitChar, uint iPos);
DLL void ini_write_wstring(FILE* file, const std::string& parmname, const std::wstring& in);
DLL void ini_get_wstring(INI_Reader& ini, std::wstring& wscValue);
DLL std::wstring GetTimeString(bool bLocalTime);
DLL std::string GetUserFilePath(std::variant<uint, std::wstring> player, const std::string& scExtension);
DLL mstime GetTimeInMS();
DLL void AddLog(LogType LogType, LogLevel level, std::wstring wStr, ...);

// variables
extern DLL HANDLE hProcFL;
extern DLL HMODULE hModServer;
extern DLL HMODULE hModCommon;
extern DLL HMODULE hModRemoteClient;
extern DLL HMODULE hModDPNet;
extern DLL HMODULE hModDaLib;
extern DLL HMODULE hModContent;
extern DLL FARPROC fpOldUpdate;

// A base class/struct used for denoting that a class can be scanned.
// Reflectable values are int, uint, bool, float, string, Reflectable, and std::vectors of the previous types.
// Reflectables are interepreted as headers of the provided name.
// Circular references are not handled and will crash.
// Marking a field as reflectable without properly initalizing it will crash upon attempted deserialization.
// Ensure that the default CTOR initalizes all fields.
struct DLL Reflectable
{
	virtual ~Reflectable() = default;
	virtual std::string File() { return {}; }
};

#include <Serialization.hpp>

struct DLL FLHookConfig final : Reflectable, Singleton<FLHookConfig>
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
		bool echoCommands = true;
		bool suppressInvalidCommands = true;

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
		std::wstring msgEchoStyle = L"0x00AA0090";
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

		void* bfCTX = nullptr;
		std::map<std::wstring, std::string> passRightsMap = {{L"SuperSecret", "superadmin"}};
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

REFL_AUTO(type(FLHookConfig::General), field(antiDockKill), field(antiF1), field(changeCruiseDisruptorBehaviour), field(debugMode), field(dieMsg),
    field(disableCharfileEncryption), field(disconnectDelay), field(disableNPCSpawns), field(dockingMessages), field(localTime), field(maxGroupSize),
    field(persistGroup), field(reservedSlots), field(torpMissileBaseDamageMultiplier), field(logPerformanceTimers), field(chatSuppressList),
    field(noPVPSystems), field(echoCommands), field(suppressInvalidCommands))
REFL_AUTO(type(FLHookConfig::Plugins), field(loadAllPlugins), field(plugins))
REFL_AUTO(type(FLHookConfig::Socket), field(activated), field(port), field(wPort), field(ePort), field(eWPort), field(encryptionKey), field(passRightsMap))
REFL_AUTO(type(FLHookConfig::MsgStyle), field(msgEchoStyle), field(deathMsgStyle), field(deathMsgStyleSys), field(kickMsgPeriod), field(kickMsg), field(userCmdStyle),
    field(adminCmdStyle), field(deathMsgTextAdminKill), field(deathMsgTextPlayerKill), field(deathMsgTextSelfKill), field(deathMsgTextNPC),
    field(deathMsgTextSuicide))
REFL_AUTO(type(FLHookConfig::UserCommands), field(userCmdSetDieMsg), field(userCmdSetDieMsgSize), field(userCmdSetChatFont), field(userCmdIgnore),
    field(userCmdHelp), field(userCmdMaxIgnoreList), field(defaultLocalChat))
REFL_AUTO(type(FLHookConfig::MultiKillMessages), field(active), field(multiKillMessageStyle), field(multiKillMessages))
REFL_AUTO(type(FLHookConfig::Bans), field(banAccountOnMatch), field(banWildcardsAndIPs))
REFL_AUTO(type(FLHookConfig), field(general), field(plugins), field(socket), field(msgStyle), field(userCommands), field(multiKillMessages), field(bans))

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
extern DLL std::map<uint, SYSTEMINFO> mapSystems;

/** A map of system id to zones */
extern DLL std::multimap<uint, ZONE> zones;

/** A map of system id to jumppoint info */
extern DLL std::multimap<uint, JUMPPOINT> jumpPoints;

namespace ZoneUtilities
{
	DLL void ReadUniverse(zone_map_t* set_mmapZones);
	DLL void ReadLootableZone(zone_map_t& set_mmapZones, const std::string& systemNick, const std::string& defaultZoneNick, const std::string& file);
	DLL void ReadSystemLootableZones(zone_map_t& set_mmapZones, const std::string& systemNick, const std::string& file);
	DLL void ReadSystemZones(zone_map_t& set_mmapZones, const std::string& systemNick, const std::string& file);
	DLL bool InZone(uint systemID, const Vector& pos, ZONE& rlz);
	DLL bool InDeathZone(uint systemID, const Vector& pos, ZONE& rlz);
	DLL SYSTEMINFO* GetSystemInfo(uint systemID);
	DLL void PrintZones();
} // namespace ZoneUtilities

typedef bool (*_HelpEntryDisplayed)(uint);
struct stHelpEntry
{
	std::wstring wszCommand;
	std::wstring wszArguments;
	std::wstring wszShortHelp;
	std::wstring wszLongHelp;
	_HelpEntryDisplayed fnIsDisplayed;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// structs

struct HookEntry
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

	bool operator==(MONEY_FIX mf1) const
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

	// Group
	uint iGroupID;

	// other
	std::wstring wscHostname;

	bool bSpawnProtected;
	bool bUseServersideHitDetection; // used by AC Plugin
	std::map<PluginInfo*, std::array<uchar, 40>> mapPluginData;
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

struct SpecialChatIDs
{
	enum : uint
	{
		CONSOLE = 0,

		PLAYER_MIN = 1,
		PLAYER_MAX = 249,

		SPECIAL_BASE = 0x10000,
		UNIVERSE = SPECIAL_BASE | 0,
		SYSTEM = SPECIAL_BASE | 1,
		LOCAL = SPECIAL_BASE | 2,
		GROUP = SPECIAL_BASE | 3,
		GROUP_EVENT = SPECIAL_BASE | 4
	};
};

class CCmds
{
protected:
	~CCmds() = default;
private:
	bool bID;
	bool bShortCut;
	bool bSelf;
	bool bTarget;

  public:
	DWORD rights;
	HK_ERROR hkLastErr;
#ifdef FLHOOK
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
	void CmdLoadPlugin(const std::wstring& wscPlugin);
	void CmdListPlugins();
	void CmdUnloadPlugin(const std::wstring& wscPlugin);

	void ExecuteCommandString(const std::wstring& wscCmd);
	void SetRightsByString(const std::string& scRightStr);
	std::wstring wscCurCmdString;
	#endif

public:
	virtual void DoPrint(const std::wstring& wscText) = 0;
	DLL void PrintError();
	DLL std::wstring ArgCharname(uint iArg);
	DLL int ArgInt(uint iArg);
	DLL uint ArgUInt(uint iArg);
	DLL float ArgFloat(uint iArg);
	DLL std::wstring ArgStr(uint iArg);
	DLL std::wstring ArgStrToEnd(uint iArg);
	DLL void Print(std::wstring wscText, ...);
	DLL virtual std::wstring GetAdminName() { return L""; };
	DLL virtual bool IsPlayer() { return false; }
};

class CInGame final : public CCmds
{
  public:
	uint iClientID;
	std::wstring wscAdminName;
	DLL void DoPrint(const std::wstring& wscText) override;
	DLL void ReadRights(const std::string& scIniFile);
	DLL std::wstring GetAdminName() override;
	DLL bool IsPlayer() override { return true; }
};

class CSocket final : public CCmds
{
  public:
	SOCKET s;
	BLOWFISH_CTX* bfc;
	bool bAuthed;
	bool bEventMode;
	bool bUnicode;
	bool bEncrypted;
	std::string sIP;
	ushort iPort;

	CSocket()
	{
		bAuthed = false;
		bEventMode = false;
		bUnicode = false;
	}
	DLL void DoPrint(const std::wstring& wscText) override;
	DLL std::wstring GetAdminName() override;
};


// HkFuncTools
DLL uint HkGetClientIdFromAccount(CAccount* acc);
DLL uint HkGetClientIdFromPD(struct PlayerData* pPD);
DLL CAccount* HkGetAccountByCharname(const std::wstring& wscCharname);
DLL uint HkGetClientIdFromCharname(const std::wstring& wscCharname);
DLL std::wstring HkGetAccountID(CAccount* acc);
DLL bool HkIsEncoded(const std::string& scFilename);
DLL bool HkIsInCharSelectMenu(std::variant<uint, std::wstring> player);
DLL bool HkIsValidClientID(uint iClientID);
DLL std::wstring HkGetCharacterNameById(const uint& iClientId);
DLL HK_ERROR HkResolveId(const std::wstring& player, uint& iClientID);
DLL HK_ERROR HkResolveShortCut(const std::wstring& wscShortcut, uint& iClientID);
DLL uint HkGetClientIDByShip(uint iShip);
DLL HK_ERROR HkGetAccountDirName(CAccount* acc, std::wstring& wscDir);
DLL HK_ERROR HkGetAccountDirName(std::variant<uint, std::wstring> player, std::wstring& wscDir);
DLL HK_ERROR HkGetCharFileName(std::variant<uint, std::wstring> player, std::wstring& wscFilename);
DLL std::wstring HkGetBaseNickByID(uint iBaseID);
DLL std::wstring HkGetPlayerSystem(uint iClientID);
DLL std::wstring HkGetSystemNickByID(uint iSystemID);
DLL void HkLockAccountAccess(CAccount* acc, bool bKick);
DLL void HkUnlockAccountAccess(CAccount* acc);
DLL void HkGetItemsForSale(uint iBaseID, std::list<uint>& lstItems);
DLL IObjInspectImpl* HkGetInspect(uint iClientID);
DLL ENGINE_STATE HkGetEngineState(uint iClientID);
DLL EQ_TYPE HkGetEqType(Archetype::Equipment* eq);
DLL float HkDistance3D(Vector v1, Vector v2);
DLL float HkDistance3DByShip(uint iShip1, uint iShip2);
DLL Quaternion HkMatrixToQuaternion(Matrix m);
template<typename Str>
Str VectorToSectorCoord(uint iSystemID, Vector vPos);
template DLL std::string VectorToSectorCoord(uint iSystemID, Vector vPos);
template DLL std::wstring VectorToSectorCoord(uint iSystemID, Vector vPos);
DLL float degrees(float rad);
DLL Vector MatrixToEuler(const Matrix& mat);
DLL void Rotate180(Matrix& rot);
DLL void TranslateY(Vector& pos, Matrix& rot, float y);
DLL void TranslateX(Vector& pos, Matrix& rot, float x);
DLL void TranslateZ(Vector& pos, Matrix& rot, float z);
DLL uint RgbToBgr(uint color);
DLL std::wstring UintToHex(uint number, uint width, bool addPrefix = false);
DLL HK_ERROR HkGetSystemByNickname(std::variant<std::string, std::wstring> nickname, uint& system);
DLL CShip* HkCShipFromShipDestroyed(const DWORD** ecx);

// HkFuncMsg
DLL HK_ERROR HkMsg(uint iClientID, const std::wstring& wscMessage);
DLL HK_ERROR HkMsg(std::variant<uint, std::wstring> player, const std::wstring& wscMessage);
DLL HK_ERROR HkMsgS(const std::wstring& wscSystemname, const std::wstring& wscMessage);
DLL HK_ERROR HkMsgU(const std::wstring& wscMessage);
DLL HK_ERROR HkFMsgEncodeXML(const std::wstring& wscXML, char* szBuf, uint iSize, uint& iRet);
DLL HK_ERROR HkFMsgSendChat(uint iClientID, char* szBuf, uint iSize);
DLL HK_ERROR HkFMsg(uint iClientID, const std::wstring& wscXML);
DLL HK_ERROR HkFMsg(std::variant<uint, std::wstring> player, const std::wstring& wscXML);
DLL HK_ERROR HkFMsgS(const std::wstring& wscSystemname, const std::wstring& wscXML);
DLL HK_ERROR HkFMsgU(const std::wstring& wscXML);
DLL void HkFormatMessage(uint clientId, MessageColor color, MessageFormat format, std::wstring msg, ...);
DLL std::wstring HkGetWStringFromIDS(uint iIDS);
DLL void HkLoadStringDLLs();
DLL void HkUnloadStringDLLs();
DLL void FormatSendChat(uint iToClientID, const std::wstring& wscSender, const std::wstring& wscText, const std::wstring& wscTextColor);
DLL void SendGroupChat(uint iFromClientID, const std::wstring& wscText);
DLL void SendLocalSystemChat(uint iFromClientID, const std::wstring& wscText);
DLL void SendPrivateChat(uint iFromClientID, uint iToClientID, const std::wstring& wscText);
DLL void SendSystemChat(uint iFromClientID, const std::wstring& wscText);

// HkFuncPlayers
DLL HK_ERROR HkAddToGroup(uint iClientID, uint iGroupID);
DLL HK_ERROR HkGetGroupID(uint iClientID, uint& iGroupID);
DLL HK_ERROR HkGetCash(std::variant<uint, std::wstring> player, int& iCash);
DLL HK_ERROR HkAddCash(std::variant<uint, std::wstring> player, int iAmount);
DLL HK_ERROR HkKick(CAccount* acc);
DLL HK_ERROR HkKick(std::variant<uint, std::wstring> player);
DLL HK_ERROR HkKickReason(std::variant<uint, std::wstring> player, const std::wstring& wscReason);
DLL HK_ERROR HkBan(std::variant<uint, std::wstring> player, bool bBan);
DLL HK_ERROR HkBeam(std::variant<uint, std::wstring> player, const std::wstring& wscBasename);
DLL HK_ERROR HkSaveChar(std::variant<uint, std::wstring> player);
DLL HK_ERROR HkEnumCargo(std::variant<uint, std::wstring> player, std::list<CARGO_INFO>& lstCargo, int& iRemainingHoldSize);
DLL HK_ERROR HkRemoveCargo(std::variant<uint, std::wstring> player, uint iID, int iCount);
DLL HK_ERROR HkAddCargo(std::variant<uint, std::wstring> player, uint iGoodID, int iCount, bool bMission);
DLL HK_ERROR HkAddCargo(std::variant<uint, std::wstring> player, const std::wstring& wscGood, int iCount, bool bMission);
DLL HK_ERROR HkRename(std::variant<uint, std::wstring> player, const std::wstring& wscNewCharname, bool bOnlyDelete);
DLL HK_ERROR HkMsgAndKick(uint iClientID, const std::wstring& wscReason, uint iIntervall);
DLL HK_ERROR HkKill(std::variant<uint, std::wstring> player);
DLL HK_ERROR HkGetReservedSlot(std::variant<uint, std::wstring> player, bool& bResult);
DLL HK_ERROR HkSetReservedSlot(std::variant<uint, std::wstring> player, bool bReservedSlot);
DLL void HkPlayerAutoBuy(uint iClientID, uint iBaseID);
DLL HK_ERROR HkResetRep(std::variant<uint, std::wstring> player);
DLL HK_ERROR HkGetGroupMembers(std::variant<uint, std::wstring> player, std::list<GROUP_MEMBER>& lstMembers);
DLL HK_ERROR HkSetRep(std::variant<uint, std::wstring> player, const std::wstring& wscRepGroup, float fValue);
DLL HK_ERROR HkGetRep(std::variant<uint, std::wstring> player, const std::wstring& wscRepGroup, float& fValue);
DLL HK_ERROR HkReadCharFile(std::variant<uint, std::wstring> player, std::list<std::wstring>& lstOutput);
DLL HK_ERROR HkWriteCharFile(std::variant<uint, std::wstring> player, std::wstring wscData);
DLL HK_ERROR HkPlayerRecalculateCRC(uint iClientID);
DLL std::string HkGetPlayerSystemS(uint iClientID);
DLL bool IsInRange(uint iClientID, float fDistance);
DLL std::wstring GetLocation(unsigned int iClientID);
DLL HK_ERROR HkAddEquip(std::variant<uint, std::wstring> player, uint iGoodID, const std::string& scHardpoint);
DLL HK_ERROR HkAntiCheat(uint iClientID);
DLL void HkDelayedKick(uint iClientID, uint secs);
DLL HK_ERROR HkDeleteCharacter(CAccount* acc, std::wstring& wscCharname);
DLL HK_ERROR HkNewCharacter(CAccount* acc, std::wstring& wscCharname);
DLL std::wstring HkGetAccountIDByClientID(uint iClientID);
DLL HK_ERROR HkGetOnlineTime(std::variant<uint, std::wstring> player, int& iSecs);
DLL HK_ERROR HkGetRank(std::variant<uint, std::wstring> player, int& iRank);
DLL HK_ERROR HKGetShipValue(std::variant<uint, std::wstring> player, float& fValue);
DLL void HkRelocateClient(uint iClientID, Vector vDestination, Matrix mOrientation);
DLL void HkSaveChar(uint iClientID);
DLL HK_ERROR HkGetTarget(std::variant<uint, std::wstring> player, uint& target);
DLL HK_ERROR HkGetTargetClientId(std::variant<uint, std::wstring> player, uint& targetClientId);
DLL HK_ERROR HkGetCurrentBase(std::variant<uint, std::wstring> player, uint& base);
DLL HK_ERROR HkGetSystem(std::variant<uint, std::wstring> player, uint& system);
DLL HK_ERROR HkGetShip(std::variant<uint, std::wstring> player, uint& system);

// HkFuncLog

DLL bool InitLogs();

DLL void HkHandleCheater(uint iClientID, bool bBan, std::wstring wscReason, ...);
DLL bool HkAddCheaterLog(std::variant<uint, std::wstring> player, const std::wstring& wscReason);
DLL bool HkAddKickLog(uint iClientID, std::wstring wscReason, ...);
DLL bool HkAddConnectLog(uint iClientID, std::wstring wscReason, ...);

// HkFuncOther
DLL void HkGetPlayerIP(uint iClientID, std::wstring& wscIP);
DLL HK_ERROR HkGetPlayerInfo(std::variant<uint, std::wstring> player, HKPLAYERINFO& pi, bool bAlsoCharmenu);
DLL std::list<HKPLAYERINFO> HkGetPlayers();
DLL HK_ERROR HkGetConnectionStats(uint iClientID, DPN_CONNECTION_INFO& ci);
DLL HK_ERROR HkSetAdmin(std::variant<uint, std::wstring> player, const std::wstring& wscRights);
DLL HK_ERROR HkGetAdmin(std::variant<uint, std::wstring> player, std::wstring& wscRights);
DLL HK_ERROR HkDelAdmin(std::variant<uint, std::wstring> player);
DLL HK_ERROR HkChangeNPCSpawn(bool bDisable);
DLL HK_ERROR HkGetBaseStatus(const std::wstring& wscBasename, float& fHealth, float& fMaxHealth);
DLL Fuse* HkGetFuseFromID(uint iFuseID);
DLL bool HkLightFuse(IObjRW* ship, uint iFuseID, float fDelay, float fLifetime, float fSkip);
DLL bool HkUnLightFuse(IObjRW* ship, uint iFuseID);
DLL CEqObj* HkGetEqObjFromObjRW(struct IObjRW* objRW);
DLL uint HkGetClientIDFromArg(const std::wstring& wscArg);

// HkFLIni
DLL HK_ERROR HkFLIniGet(std::variant<uint, std::wstring> player, const std::wstring& wscKey, std::wstring& wscRet);
DLL HK_ERROR HkFLIniWrite(std::variant<uint, std::wstring> player, const std::wstring& wscKey, std::wstring wscValue);

DLL std::wstring HkErrGetText(HK_ERROR hkErr);

DLL void UserCmd_SetDieMsg(const uint& iClientID, const std::wstring_view& wscParam);
DLL void UserCmd_SetChatFont(const uint& iClientID, const std::wstring_view& wscParam);
DLL void PrintUserCmdText(uint iClientID, std::wstring wscText, ...);
DLL void PrintLocalUserCmdText(uint iClientID, const std::wstring& wscMsg, float fDistance);

DLL void HkSetCharacterIni(uint client, const std::wstring& name, std::wstring value);

DLL std::wstring HkGetCharacterIniString(uint client, const std::wstring& name);
DLL bool HkGetCharacterIniBool(uint client, const std::wstring& name);
DLL int HkGetCharacterIniInt(uint client, const std::wstring& name);
DLL uint HkGetCharacterIniUint(uint client, const std::wstring& name);
DLL float HkGetCharacterIniFloat(uint client, const std::wstring& name);
DLL double HkGetCharacterIniDouble(uint client, const std::wstring& name);
DLL int64_t HkGetCharacterIniInt64(uint client, const std::wstring& name);

// HkPersonalities
DLL pub::AI::Personality HkGetPersonality(const std::string& pilotNickname, HK_ERROR& err);

DLL extern bool g_NonGunHitsBase;
DLL extern float g_LastHitPts;

// namespaces
namespace HkIServerImpl
{
	DLL extern bool g_InSubmitChat;
	DLL extern uint g_TextLength;
} // namespace HkIServerImpl

// variables

extern DLL HkIClientImpl* FakeClient;
extern DLL HkIClientImpl* HookClient;
extern DLL char* OldClient;

extern DLL uint g_DmgTo;
extern DLL uint g_DmgToSpaceID;

extern DLL bool g_bMsg;
extern DLL bool g_bMsgS;
extern DLL bool g_bMsgU;

extern DLL CDPClientProxy** g_cClientProxyArray;
extern DLL void* pClient;

extern DLL _RCSendChatMsg RCSendChatMsg;
extern DLL _CRCAntiCheat CRCAntiCheat;
extern DLL _CreateChar CreateChar;

extern DLL std::string scAcctPath;

extern DLL std::array<CLIENT_INFO, MaxClientId + 1> ClientInfo;
extern DLL CDPServer* cdpSrv;
extern DLL uint g_iServerLoad;
extern DLL uint g_iPlayerCount;
extern DLL bool g_bNPCDisabled;
extern DLL char* g_FLServerDataPtr;

extern DLL bool g_bPlugin_nofunctioncall;

extern DLL bool get_bTrue(uint iClientID);
extern DLL void HkAddHelpEntry(const std::wstring& wscCommand, const std::wstring& wscArguments, const std::wstring& wscShortHelp,
    const std::wstring& wscLongHelp, _HelpEntryDisplayed fnIsDisplayed);
extern DLL void HkRemoveHelpEntry(const std::wstring& wscCommand, const std::wstring& wscArguments);

extern DLL HK_ERROR HkGetClientID(bool& bIdString, uint& iClientID, const std::wstring& wscCharName);

extern DLL _GetShipInspect GetShipInspect;
extern DLL std::list<BASE_INFO> lstBases;
extern DLL bool flhookReady;

DLL bool flc_decode(const char* ifile, const char* ofile);
DLL bool flc_encode(const char* ifile, const char* ofile);

DLL void Blowfish_Init(BLOWFISH_CTX* ctx, unsigned char* key, int keyLen);
DLL char Blowfish_Encrypt(BLOWFISH_CTX* ctx, void* ptr, unsigned long dataLen);
DLL char Blowfish_Decrypt(BLOWFISH_CTX* ctx, void* ptr, unsigned long dataLen);