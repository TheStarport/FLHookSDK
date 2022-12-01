#pragma once

#include "plugin.h"

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
	std::wstring character;
	int iAmount;

	bool operator==(MONEY_FIX mf1) const
	{
		if (!character.compare(mf1.character))
			return true;

		return false;
	};
};

// ignore
struct IGNORE_INFO
{
	std::wstring character;
	std::wstring wscFlags;
};

// resolver
struct RESOLVE_IP
{
	uint clientId;
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

struct PLAYERINFO
{
	uint clientId;
	std::wstring character;
	std::wstring wscBase;
	std::wstring wscSystem;
	uint iSystem;
	uint iShip;
	DPN_CONNECTION_INFO connectionInfo;
	std::wstring wscIP;
	std::wstring wscHostname;
};

struct BaseHealth
{
	float currentHealth;
	float maxHealth;
};

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
	uint baseId;
	std::string scBasename;
	uint iObjectID;
	bool bDestroyed;
	std::list<DATA_MARKETITEM> lstMarketMisc;
};

struct GROUP_MEMBER
{
	uint clientId;
	std::wstring character;
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