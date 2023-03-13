//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreServer.h
//	Module:			FLCoreServer.lib
//	Description:	Interface to Server.dll
//
//	Web: www.skif.be/flcoresdk.php
//
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCORESERVER_H_
#define _FLCORESERVER_H_

#include "FLCoreDefs.h"
#include "FLCoreCommon.h"

#pragma warning(disable : 5030)
#pragma comment(lib, "FLCoreServer.lib")

enum class PopupDialog
{
	LeftYes = 1 << 0,
	CenterNo = 1 << 1,
	RightLater = 1 << 2,
	CenterOk = 1 << 3
};

struct CHAT_ID
{
	uint id;
};

enum class DOCK_HOST_RESPONSE
{
	AccessDenied = 1,
	DockDenied = 2,
	DockInUse = 3,
	ProceedDock = 4,
	Dock = 5,
};

enum class DestroyType
{
	Vanish = 0,
	Fuse = 1,
};

struct SGFGoodVaporizedInfo
{
	uint dunno[128];
};

struct SSPMunitionCollisionInfo
{
	uint projectileArchId;
	DWORD dunno;
	DWORD targetShip;
	ushort s1;
};

struct SObjectCargoUpdate
{
	uint client;
	Vector position;
	uint dunno[24];
};

struct SSPBadLandsObjCollisionInfo
{
	uint dunno[128];
};

struct SSPObjCollisionInfo
{
	uint colliderObjectId;
	uint colliderSubObjId;
	uint damagedObjectId;
	uint damagedSubObjId;
	float damage;
};

struct SSPUseItem
{
	uint dunno[128];
};

struct XActivateEquip
{
	uint spaceId;
	ushort id;
	bool activate;
};

struct XActivateCruise
{
	uint ship;
	bool activate;
};

struct XActivateThrusters
{
	uint ship;
	bool activate;
};

struct XTractorObjects
{
	int dunno[3];
	// This points to the start of the array of space Ids
	int* arraySpaceId;
	// This points to the end of the array of space Ids
	int* arraySpaceIdEnd;
};

struct SGFGoodSellInfo
{
	long dunno1;
	uint archId;
	int count;
};

struct SGFGoodBuyInfo
{
	uint baseId;
	ulong null;
	uint goodId;
	int count;
};

struct XFireWeaponInfo
{
	uint object;
	Vector target;
	uint dunno;
	st6::list<ushort> hpIds;
};

struct XCollision
{
	ushort componentId;
	float componentHp;
};

struct XSetManeuver
{
	uint shipFrom;
	uint shipTo;
	uint flag;
};

struct XSetTarget
{
	uint ship;
	uint slot;
	uint spaceId;
	uint subObjId;
};

struct SSPObjUpdateInfo
{
	uint ship;
	Quaternion dir;
	Vector pos;
	float timestamp;
	float throttle;
	uint stateValue;
	// Enum of some kind
	char state;
};

struct XJettisonCargo
{
	uint ship;
	uint Slot;
	uint Count;
};

struct XGoTradelane
{
	uint ship;
	uint tradelaneSpaceObj1;
	uint tradelaneSpaceObj2;
};

struct CAccountListNode
{
	CAccountListNode* next;
	CAccountListNode* prev;
	uint dunno1;
	wchar_t* charname;
	uint dunno2[32];
};

enum class ConnectionType
{
	// TODO: Map out other connection types
	Jumphole
};

enum class EFLConnection
{
	// TODO: Map out connections
};

enum class InvincibilityReason
{
	// TODO Map out reason
};

struct CollisionGroupDescList
{
	st6::list<CollisionGroupDesc> data;
};

struct SCreateCharacterInfo
{
	wchar_t charname[24];
	uint nickName; // From [Faction] section of newcharacter.ini
	uint base;     // From [Faction] section of newcharacter.ini
	uint package;  // From [Faction] section of newcharacter.ini
	uint pilot;    // From [Faction] section of newcharacter.ini
	uint dunno[96];
};

struct SStartupInfo
{
	uint dunno[130];
	int maxPlayers;
};

struct SLoginInfo
{
	wchar_t account[36];
};

struct FLString
{
	st6::string value;
	UINT dunno2[12];
};

class IMPORT CAccount
{
  public:
	CAccount(CAccount const&);
	CAccount(void);
	virtual ~CAccount(void);
	CAccount& operator=(CAccount const&);
	void AppendCharacterNames(st6::list<st6::wstring&>&);
	void DeleteCharacterFromID(st6::string&);
	void ForceLogout(void);
	void InitFromFolder(char const*);

  public:
	uint dunno1;
	wchar_t* accId;
	uint dunno2[7];
	CAccountListNode* firstListNode;
	uint numberOCharacters;
	uint dunno4[32];
};

namespace BaseGroupMessage
{
	enum Type;
};

class IMPORT CPlayerGroup
{
  public:
	CPlayerGroup(CPlayerGroup const&);
	CPlayerGroup(void);
	virtual ~CPlayerGroup(void);
	CPlayerGroup& operator=(CPlayerGroup const&);
	bool AddInvite(unsigned int);
	bool AddMember(unsigned int);
	bool DelInvite(unsigned int);
	bool DelMember(unsigned int);
	void DeliverChat(unsigned long, void const*);
	static CPlayerGroup* FromGroupID(unsigned int);
	unsigned int GetID(void);
	unsigned int GetInviteCount(void);
	unsigned int GetMember(int) const;
	unsigned int GetMemberCount(void);
	unsigned int GetMissionID(void);
	unsigned int GetMissionSetBy(void);
	void HandleClientLogout(unsigned int);
	bool IsFull(void);
	bool IsInvited(unsigned int);
	bool IsMember(unsigned int);
	void RewardMembers(int);
	void SendChat(int, unsigned short const*, ...);
	void SendGroup(BaseGroupMessage::Type, unsigned int);
	void SetMissionID(unsigned int, unsigned int);
	void SetMissionMessage(struct CSetMissionMessage&);
	void SetMissionObjectives(struct CMissionObjectives&);
	void StoreMemberList(st6::vector<unsigned int>&);

  protected:
	static st6::map<unsigned int const, CPlayerGroup*, st6::less<unsigned int const>, st6::allocator<CPlayerGroup*>> groupIdToGroupPtrMap;
	static unsigned int groupId;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT [[Hook, ServerCall]] IServerImpl
{
	IServerImpl(const IServerImpl&);
	IServerImpl();
	IServerImpl& operator=(const IServerImpl&);

	// N.B. Do not modify order, vtable ordering is fixed by Server.dll
	[[DisconnectCheck]] virtual void FireWeapon(uint client, const XFireWeaponInfo& fwi);
	[[CallInner, DisconnectCheck]] virtual void ActivateEquip(uint client, const XActivateEquip& aq);
	[[CallInner, DisconnectCheck]] virtual void ActivateCruise(uint client, const XActivateCruise& ac);
	[[CallInner, DisconnectCheck]] virtual void ActivateThrusters(uint client, const XActivateThrusters& at);
	virtual void SetTarget(uint client, const XSetTarget& st);
	virtual void TractorObjects(uint client, const XTractorObjects& to);
	[[CallInner, CallCatch]] virtual void GoTradelane(uint client, const XGoTradelane& gt);
	[[CallInner]] virtual void StopTradelane(uint client, uint shipID, uint tradelaneRing1, uint tradelaneRing2);
	virtual void JettisonCargo(uint client, const XJettisonCargo& jc);
	[[CallInner, CallInnerAfter]] virtual bool Startup(const SStartupInfo& si);
	[[CallInnerAfter, NoPluginsAfter]] virtual void Shutdown();
	[[CallInner, NoLog]] virtual int Update();
	[[NoHook]] virtual void ElapseTime(float);
	[[NoHook]] virtual void __nullopt1();
	[[NoHook]] virtual bool SwapConnections(EFLConnection, EFLConnection);
	[[NoHook]] virtual void __nullopt2();
	[[CallInner]] virtual void DisConnect(uint client, EFLConnection conn);
	[[DisconnectCheck, CallInner(true), CallInnerAfter]] virtual void OnConnect(uint client);
	[[CallInnerAfter]] virtual void Login(const SLoginInfo& li, uint client);
	[[DisconnectCheck, CallInner(true), CallCatch]] virtual void CharacterInfoReq(uint client, bool);
	[[DisconnectCheck, CallInner(true), CallInnerAfter]] virtual void CharacterSelect(const CHARACTER_ID& cid, uint client);
	[[NoHook]] virtual void __nullopt3();
	virtual void CreateNewCharacter(const SCreateCharacterInfo&, uint client);
	virtual void DestroyCharacter(CHARACTER_ID const&, uint client);
	[[NoHook]] virtual void CharacterSkipAutosave(uint);
	virtual void ReqShipArch(uint archID, uint client);
	virtual void ReqHullStatus(float status, uint client);
	virtual void ReqCollisionGroups(const st6::list<CollisionGroupDesc>& collisionGroups, uint client);
	virtual void ReqEquipment(const EquipDescList& edl, uint client);
	[[NoHook]] virtual void ReqCargo(const EquipDescList&, uint);
	virtual void ReqAddItem(uint goodID, const char* hardpoint, int count, float status, bool mounted, uint client);
	virtual void ReqRemoveItem(ushort slotID, int count, uint client);
	virtual void ReqModifyItem(ushort slotID, const char* hardpoint, int count, float status, bool mounted, uint client);
	virtual void ReqSetCash(int cash, uint client);
	virtual void ReqChangeCash(int cashAdd, uint client);
	[[DisconnectCheck, CallInner, CallInnerAfter]] virtual void BaseEnter(uint baseID, uint client);
	[[DisconnectCheck, CallInner, CallInnerAfter]] virtual void BaseExit(uint baseID, uint client);
	virtual void LocationEnter(uint locationID, uint client);
	virtual void LocationExit(uint locationID, uint client);
	virtual void BaseInfoRequest(unsigned int, unsigned int, bool);
	virtual void LocationInfoRequest(unsigned int, unsigned int, bool);
	virtual void GFObjSelect(unsigned int, unsigned int);
	virtual void GFGoodVaporized(const SGFGoodVaporizedInfo& gvi, uint client);
	virtual void MissionResponse(unsigned int, unsigned long, bool, uint client);
	virtual void TradeResponse(unsigned char const*, int, uint client);
	virtual void GFGoodBuy(const SGFGoodBuyInfo&, uint client);
	[[CallInner(true), DisconnectCheck]] virtual void GFGoodSell(const SGFGoodSellInfo&, uint client);
	[[CallInnerAfter]] virtual void SystemSwitchOutComplete(uint shipID, uint client);
	[[CallInner, CallInnerAfter, DisconnectCheck]] virtual void PlayerLaunch(uint shipID, uint client);
	[[CallInner]] virtual void LaunchComplete(uint baseID, uint shipID);
	[[CallInnerAfter]] virtual void JumpInComplete(uint systemID, uint shipID);
	virtual void Hail(unsigned int, unsigned int, unsigned int);
	[[CallInner(true), NoLog, DisconnectCheck]] virtual void SPObjUpdate(const SSPObjUpdateInfo& ui, uint client);
	[[CallInner, DisconnectCheck]] virtual void SPMunitionCollision(const SSPMunitionCollisionInfo& mci, uint client);
	[[NoHook]] virtual void SPBadLandsObjCollision(const SSPBadLandsObjCollisionInfo&, uint);
	[[DisconnectCheck]] virtual void SPObjCollision(const SSPObjCollisionInfo& oci, uint client);
	virtual void SPRequestUseItem(const SSPUseItem& ui, uint client);
	virtual void SPRequestInvincibility(uint shipID, bool enable, InvincibilityReason reason, uint client);
	[[NoHook]] virtual void SaveGame(const CHARACTER_ID&, const ushort*, uint);
	[[NoHook]] virtual void MissionSaveB(uint, ulong);
	// eventType: 0 = docking, 1 = formation
	virtual void RequestEvent(int eventType, uint shipID, uint dockTarget, uint, ulong, uint client);
	// eventType: 0 = docking, 1 = formation
	virtual void RequestCancel(int eventType, uint shipID, uint, ulong, uint client);
	virtual void MineAsteroid(uint systemID, const Vector& pos, uint crateID, uint lootID, uint count, uint client);
	[[NoHook]] virtual void CommComplete(uint, uint, uint, enum CommResult);
	virtual void RequestCreateShip(uint client);
	virtual void SPScanCargo(const uint&, const uint&, uint);
	virtual void SetManeuver(uint client, const XSetManeuver& sm);
	virtual void InterfaceItemUsed(uint, uint);
	virtual void AbortMission(uint client, uint);
	[[NoHook]] virtual void RTCDone(uint, uint);
	virtual void SetWeaponGroup(uint client, uchar*, int);
	virtual void SetVisitedState(uint client, uchar*, int);
	virtual void RequestBestPath(uint client, uchar*, int);
	virtual void RequestPlayerStats(uint client, uchar*, int);
	[[NoHook]] virtual void PopUpDialog(uint, uint);
	virtual void RequestGroupPositions(uint client, uchar*, int);
	[[NoHook]] virtual void SetMissionLog(uint, uchar*, int);
	virtual void SetInterfaceState(uint client, uchar*, int);
	virtual void RequestRankLevel(uint client, uchar*, int);
	[[CallInner]] virtual void InitiateTrade(uint client1, uint client2);
	[[CallInnerAfter, DisconnectCheck]] virtual void TerminateTrade(uint client, int accepted);
	virtual void AcceptTrade(uint client, bool);
	virtual void SetTradeMoney(uint client, ulong);
	virtual void AddTradeEquip(uint client, const EquipDesc& ed);
	virtual void DelTradeEquip(uint client, const EquipDesc& ed);
	virtual void RequestTrade(uint, uint);
	virtual void StopTradeRequest(uint client);
	[[NoHook]] virtual void ReqDifficultyScale(float, uint);
	[[NoHook]] virtual unsigned int GetServerID();
	[[NoHook]] virtual char const* GetServerSig();
	[[NoHook]] virtual void DumpPacketStats(const char*);
	[[Disable]] virtual void Dock(const uint&, const uint&);

	[[CallInner(true), Semaphore(g_InSubmitChat), Address(-0x08)]] virtual void SubmitChat(
	    CHAT_ID cidFrom, ulong size, const void* rdlReader, CHAT_ID cidTo, int);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct CHARACTER_ID final
{
	CHARACTER_ID(void);
	CHARACTER_ID const& operator=(CHARACTER_ID const&);
	void invalidate(void);
	bool is_valid(void) const;

	char charFilename[512]; // Only first 16 bytes are ever used
};

struct PlayerData
{
	wchar_t accId[40];
	long x050, x054, x058, x05C;
	uint numberOCharacters;
	CHARACTER_ID charFile;
	uint shipArchetype;
	float relativeHealth;
	CollisionGroupDescList collisionGroupDesc;
	EquipDescList equipDescList;
	int rank;
	int moneyNeededToNextRank;
	struct StructCostume
	{
		UINT head;
		UINT body;
		UINT leftHand;
		UINT rightHand;
		UINT accessory[8];
		int accessories;
	};
	StructCostume costume1;
	long x2C0, x2C4, x2C8, x2CC, x2D0, x2D4, x2D8, x2DC, x2E0;
	StructCostume costume2;
	uint reputation;
	int inspectCash;
	int worth;
	uint shipArchetypeWhenLanding;
	EquipDescList lShadowEquipDescList;
	int numKills;
	int numMissionSuccesses;
	int numMissionFailures;
	bool skipAutoSave;
	char padding0[3];
	uint saveCount;
	uint onlineId;
	bool cheated;
	char padding1[3];
	Vector position;
	Matrix orientation;
	FLString weaponGroup; // 0x10 bytes
	uint setToZero;
	float difficulty;
	ushort lastEquipId;
	char padding2[2];
	uint menuItem;
	uint onlineId2;
	long x3D4, x3D8;
	uint tradeRequestCount;
	uint systemId;
	uint shipId;
	uint createdShipId;
	uint baseId;
	uint lastBaseId;
	uint enteredBase;
	uint baseRoomId;
	uint characterId;
	CAccount* account;
	CPlayerGroup* playerGroup;
	uint missionId;
	uint missionSetBy;
	uint exitedBase;
	uint unknownLocId;
};

struct PlayerDbTreeNode
{
	PlayerDbTreeNode* left;
	PlayerDbTreeNode* parent;
	PlayerDbTreeNode* right;
	ulong l1;
	// File name of character
	char* flName;
	// Length of file name
	uint length;
	// Always seems to be 0x1F. Possibly max length of flName
	uint dunno;
	// Account for this player
	CAccount* acc;
};

class IMPORT PlayerDB
{
  public:
	PlayerDB(PlayerDB const&);
	PlayerDB(void);
	~PlayerDB(void);
	PlayerDB& operator=(PlayerDB const&);
	PlayerData& operator[](unsigned int const&);
	bool BanAccount(st6::wstring&, bool);
	void BuildLocalUserDir(void);
	unsigned int CountPlayersInSystem(int);
	bool CreateAccount(st6::wstring&);
	void DeleteAccount(st6::wstring&);
	void DeleteCharacterFromID(st6::wstring&);
	bool DeleteCharacterFromName(st6::wstring&);
	CAccount* FindAccountFromCharacterID(st6::string&);
	CAccount* FindAccountFromCharacterName(st6::wstring&);
	CAccount* FindAccountFromClientID(unsigned int);
	CAccount* FindAccountFromName(st6::wstring&);
	bool GetAccountAdminRights(st6::wstring&);
	bool GetAccountBanned(st6::wstring&);
	unsigned short const* GetActiveCharacterName(unsigned int) const;
	bool GetCharactersForAccount(st6::wstring&, st6::list<st6::wstring>&);
	unsigned int GetGroupID(unsigned int);
	st6::wstring& GetMOTD(void);
	unsigned int GetMaxPlayerCount(void);
	unsigned int GetServerID(void);
	char const* GetServerSig(void);
	void LockAccountAccess(st6::wstring&);
	bool MakeLocalUserPath(char*, char const*);
	void ReadCharacterName(char const*, st6::wstring&);
	void SendGroupID(unsigned int, unsigned int);
	void SendSystemID(unsigned int, unsigned int);
	bool SetAccountAdminRights(st6::wstring&, bool);
	bool SetAccountPassword(st6::wstring&, st6::wstring&);
	void SetMOTD(st6::wstring&);
	void UnlockAccountAccess(st6::wstring&);
	void cleanup(unsigned int);
	bool create_new_character(SCreateCharacterInfo const&, unsigned int);
	bool create_restart_file(char const*);
	void free(void);
	void init(unsigned int, bool);
	bool is_valid(unsigned int const&);
	bool is_valid_ship_owner(unsigned int const&, unsigned int const&);
	unsigned char login(SLoginInfo const&, unsigned int);
	void logout(unsigned int);
	void logout_all(void);
	PlayerData* traverse_active(PlayerData*) const;

  private:
	int create_account(SLoginInfo const&);
	unsigned char load_user_data(SLoginInfo const&, unsigned int);
	unsigned int to_index(unsigned int);

  public:
	uint dunno1[13];
	PlayerDbTreeNode* pFirstNode;
	PlayerDbTreeNode* pLastNode;
	uint dunno2;
	uint numAccounts;
};

namespace CmnAsteroid // from FLCoreCommon.h
{
	class CAsteroidSystem;
};

namespace SrvAsteroid
{
	class IMPORT SrvAsteroidSystem
	{
	  public:
		SrvAsteroidSystem(SrvAsteroidSystem const&);
		SrvAsteroidSystem(void);
		~SrvAsteroidSystem(void);
		SrvAsteroidSystem& operator=(SrvAsteroidSystem const&);
		int AddRef(void);
		int Release(void);
		void load(char const*);
		void map_asteroid_fields(void);
		void set_cmn_system(CmnAsteroid::CAsteroidSystem*);
		void set_sys_id(unsigned int);
		void update(void);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

}; // namespace SrvAsteroid

struct IMPORT StarSystem
{
	unsigned int count_players(unsigned int) const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace SysDB
{
	IMPORT st6::map<unsigned int, StarSystem, st6::less<unsigned int>, st6::allocator<std::pair<const unsigned int, StarSystem>>> SysMap;
};

namespace Controller
{
	struct TimerExpired;
}

template<class T>
class IMPORT OwnerList
{
  public:
	OwnerList<T>();
	virtual ~OwnerList<T>();
	OwnerList<T>& operator=(OwnerList<T> const&);
	void free();

  protected:
	unsigned char data[16];
};

namespace pub
{
	struct CargoEnumerator;

	IMPORT int BuildBaseReader(INI_Reader&, unsigned int const&);
	IMPORT int BuildSystemReader(INI_Reader&, unsigned int const&);
	IMPORT HINSTANCE__* DLL_LoadLibrary(char const*);
	IMPORT void DebugPrint(char const*, int);
	IMPORT int FindHardpoint(char const*, unsigned int, Vector&, Matrix&);
	IMPORT int GetBaseID(unsigned int&, char const*);
	IMPORT unsigned int GetBaseNickname(char*, unsigned int, unsigned int const&);
	IMPORT int GetBaseStridName(unsigned int&, unsigned int const&);
	IMPORT int GetBases(unsigned int const&, unsigned int* const, unsigned int, unsigned int&);
	IMPORT int GetCargoHoldSize(unsigned int const&, unsigned int&);
	IMPORT int GetCostumeID(int&, char const*);
	IMPORT IFileSystem* GetDataPath(void);
	IMPORT int GetEquipmentID(unsigned int&, char const*);
	IMPORT int GetFullHealth(unsigned int const&, unsigned int&);
	IMPORT int GetGoodID(unsigned int&, char const*);
	IMPORT int GetGoodProperties(unsigned int const&, float&, float&);
	IMPORT int GetLoadout(EquipDescVector&, unsigned int const&);
	IMPORT int GetLoadoutID(unsigned int&, char const*);
	IMPORT int GetLoadoutName(unsigned int const&, char*, int);
	IMPORT unsigned int GetLocationNickname(char*, unsigned int, unsigned int const&);
	IMPORT int GetLocations(unsigned int const&, unsigned int* const, unsigned int, unsigned int&);
	IMPORT int GetMaxHitPoints(unsigned int const&, int&);
	IMPORT int GetNavMapScale(unsigned int, float&);
	IMPORT unsigned int GetNicknameId(char const*);
	IMPORT int GetRwTime(double&);
	IMPORT int GetShipArchSTRID(unsigned int const&, unsigned int&);
	IMPORT int GetShipID(unsigned int&, char const*);
	IMPORT int GetSolarType(unsigned int const&, unsigned int&);
	IMPORT int GetSystem(unsigned int&, unsigned int const&);
	IMPORT int GetSystemGateConnection(unsigned int const&, unsigned int&);
	IMPORT int GetSystemID(unsigned int&, char const*);
	IMPORT unsigned int GetSystemNickname(char*, unsigned int, unsigned int const&);
	IMPORT int GetTime(double&);
	IMPORT int GetType(unsigned int const&, unsigned int&);
	IMPORT int GetVoiceID(unsigned int&, char const*);
	IMPORT int IsCommodity(unsigned int const&, bool&);
	IMPORT unsigned short MakeId(char const*);
	IMPORT bool NextBaseID(unsigned int&);
	IMPORT bool NextSystemID(unsigned int&);
	IMPORT int ReportFreeTerminal(unsigned int, int);
	IMPORT int Save(unsigned int, unsigned int);
	//IMPORT int SetTimer(unsigned int const&, Controller::TimerExpired const&, float);
	IMPORT bool SinglePlayer(void);
	IMPORT int TranslateArchToGood(unsigned int const&, unsigned int&);
	IMPORT int TranslateGoodToMsgIdPrefix(unsigned int, TString<64>&);
	IMPORT int TranslateShipToMsgIdPrefix(unsigned int, TString<64>&);
	IMPORT int TranslateSystemToMsgIdPrefix(unsigned int, TString<64>&);

	namespace AI
	{
		class Personality;

		IMPORT OP_RTYPE SubmitDirective(unsigned int, BaseOp*);
		IMPORT OP_RTYPE SubmitState(unsigned int, BaseOp*);
		IMPORT bool enable_all_maneuvers(unsigned int);
		IMPORT bool enable_maneuver(unsigned int, int, bool);
		IMPORT int get_behavior_id(unsigned int);
		IMPORT bool get_personality(unsigned int, Personality&);
		IMPORT ScanResponse get_scan_response(unsigned int, unsigned int, unsigned int);
		IMPORT int get_state_graph_id(unsigned int);
		IMPORT bool lock_maneuvers(unsigned int, bool);
		IMPORT void refresh_state_graph(unsigned int);
		IMPORT int remove_forced_target(unsigned int, unsigned int);
		IMPORT OP_RTYPE set_directive_priority(unsigned int, DirectivePriority);
		IMPORT bool set_player_enemy_clamp(unsigned int, int, int);
		IMPORT int submit_forced_target(unsigned int, unsigned int);
		IMPORT enum FORMATION_RTYPE update_formation_state(unsigned int, unsigned int, Vector const&);
	}; // namespace AI

	namespace Audio
	{
		struct Tryptich
		{
			uint dunno;
			uint dunno2;
			uint dunno3;
			uint musicId;
		};

		IMPORT int CancelMusic(unsigned int);
		IMPORT int PlaySoundEffect(unsigned int, unsigned int);
		IMPORT int SetMusic(unsigned int, Tryptich const&);
	}; // namespace Audio

	namespace GF
	{
		IMPORT unsigned long AmbientScriptCreate(struct AmbientScriptDescription const&);
		IMPORT void AmbientScriptDestroy(unsigned long*);
		IMPORT unsigned long CharacterBehaviorCreate(struct CharacterBehaviorDescription const&);
		IMPORT void CharacterBehaviorDestroy(unsigned long*);
		IMPORT unsigned int CharacterCreate(struct CharacterDescription const&);
		IMPORT void CharacterDestroy(unsigned int*);
		IMPORT void CharacterSetBehavior(unsigned int, unsigned long);
		IMPORT void EnumerateCharacterPlacementIni(unsigned int, void (*)(int, INI_Reader*, void*), void*);
		IMPORT unsigned int FindBase(char const*);
		IMPORT unsigned int FindLocation(unsigned int, char const*);
		IMPORT char const* FormCharacterPlacementName(SetpointProperties const*);
		IMPORT int GetAccessory(char const*);
		IMPORT int GetBasePosition(unsigned int const&, unsigned int const&, Vector&);
		IMPORT int GetBodyPart(char const*, int);
		IMPORT unsigned int GetCharacterOnPlacement(unsigned int, unsigned int, int);
		IMPORT int GetCharacterPlacementByName(unsigned int, char const*, int&);
		IMPORT char const* GetCharacterPlacementName(unsigned int, int);
		IMPORT unsigned long GetCharacterPlacementOccupancy(unsigned int, int);
		IMPORT int GetCharacterPlacementPosture(unsigned int, int, unsigned long&);
		IMPORT bool GetCharacterPlacementProperties(unsigned int, int, SetpointProperties*);
		IMPORT void GetCostumeByID(int, Costume&);
		IMPORT int GetCostumeSkeletonGender(Costume const&, int&);
		IMPORT int GetMissionVendorOfferCount(unsigned int, unsigned int);
		IMPORT int GetNumCharacterPlacements(unsigned int);
		IMPORT float GetRtcPerformanceSlider(void);
		IMPORT unsigned int GetSpaceflightLocation(void);
		IMPORT bool IsCharacterPlacementNormal(unsigned int, int);
		IMPORT bool IsCharacterPlacementSpecial(unsigned int, int);
		IMPORT void MissionVendorAcceptance(unsigned long, bool, FmtStr const&, unsigned int);
		IMPORT unsigned long MissionVendorOfferCreate(struct MissionVendorOfferDescription const&);
		IMPORT void MissionVendorOfferDestroy(unsigned long*);
		IMPORT unsigned long NewsBroadcastCreate(struct NewsBroadcastDescription const&);
		IMPORT void NewsBroadcastDestroy(unsigned long*);
		IMPORT int ReportWhyMissionVendorEmpty(unsigned int, enum MVEmptyReason);
	}; // namespace GF

	namespace Market
	{
		IMPORT int GetCommoditiesForSale(unsigned int, unsigned int* const, int*);
		IMPORT int GetCommoditiesInDemand(unsigned int, unsigned int* const, int*);
		IMPORT int GetGoodJumpDist(unsigned int, unsigned int&);
		IMPORT int GetMinInventory(unsigned int, unsigned int, int&);
		IMPORT int GetNominalPrice(unsigned int, float&);
		IMPORT int GetNumCommoditiesForSale(unsigned int, int*);
		IMPORT int GetNumCommoditiesInDemand(unsigned int, int*);
		IMPORT int GetPrice(unsigned int, unsigned int, float&);
		IMPORT int IsGoodInDemand(unsigned int, unsigned int, bool&);
	}; // namespace Market

	namespace Phantom
	{
		IMPORT int Attach(unsigned int const&, void*);
		IMPORT int Create(unsigned int, Vector const&, Vector const&, Matrix const&, unsigned int, void*&);
		IMPORT int Create(unsigned int, float, Vector const&, unsigned int, void*&);
		IMPORT int Destroy(void*);
		IMPORT int Detach(void*);
		IMPORT int SetActive(void*, bool);
	}; // namespace Phantom

	namespace Player
	{
		IMPORT int AddCargo(unsigned int const&, unsigned int const&, unsigned int, float, bool);
		IMPORT int AdjustCash(unsigned int const&, int);
		IMPORT int CfgInterfaceNotification(unsigned int, unsigned int, bool, int);
		IMPORT int DisplayMissionMessage(unsigned int const&, FmtStr const&, enum MissionMessageType, bool);
		IMPORT int EnumerateCargo(unsigned int const&, pub::CargoEnumerator&);
		IMPORT int ForceLand(unsigned int, unsigned int);
		IMPORT int GetAssetValue(unsigned int const&, float&);
		IMPORT int GetBase(unsigned int const&, unsigned int&);
		IMPORT int GetBody(unsigned int const&, unsigned int&);
		IMPORT int GetCharacter(unsigned int const&, unsigned int&);
		IMPORT int GetGender(unsigned int const&, int&);
		IMPORT int GetGroupMembers(unsigned int, st6::vector<unsigned int>&);
		IMPORT int GetGroupSize(unsigned int, unsigned int&);
		IMPORT int GetLocation(unsigned int const&, unsigned int&);
		IMPORT int GetMoneyNeededToNextRank(unsigned int const&, int&);
		IMPORT int GetMsnID(unsigned int, unsigned int&);
		IMPORT int GetName(unsigned int, st6::wstring&);
		IMPORT int GetNumKills(unsigned int const&, int&);
		IMPORT int GetNumMissionFailures(unsigned int const&, int&);
		IMPORT int GetNumMissionSuccesses(unsigned int const&, int&);
		IMPORT int GetRank(unsigned int const&, int&);
		IMPORT int GetRelativeHealth(unsigned int const&, float&);
		IMPORT int GetRemainingHoldSize(unsigned int const&, float&);
		IMPORT int GetRep(unsigned int const&, int&);
		IMPORT int GetShip(unsigned int const&, unsigned int&);
		IMPORT int GetShipID(unsigned int const&, unsigned int&);
		IMPORT int GetSystem(unsigned int const&, unsigned int&);
		IMPORT int InspectCash(unsigned int const&, int&);
		IMPORT int IsGroupMember(unsigned int, unsigned int, bool&);
		IMPORT int LoadHint(unsigned int, BaseHint*);
		IMPORT int MarkObj(unsigned int, unsigned int, int);
		IMPORT int PopUpDialog(unsigned int, FmtStr const&, FmtStr const&, unsigned int);
		IMPORT int RemoveCargo(unsigned int const&, unsigned short, unsigned int);
		IMPORT int RemoveFromGroup(unsigned int);
		IMPORT int ReplaceMissionObjective(unsigned int const&, unsigned int const&, unsigned int, struct MissionObjective const&);
		IMPORT int ReturnBestPath(unsigned int, unsigned char*, int);
		IMPORT int ReturnPlayerStats(unsigned int, unsigned char*, int);
		IMPORT int RevertCamera(unsigned int);
		IMPORT int RewardGroup(unsigned int, int);
		IMPORT int SendNNMessage(unsigned int, unsigned int);
		IMPORT int SetCamera(unsigned int, Transform const&, float, float);
		IMPORT int SetCostume(unsigned int const&, int);
		IMPORT int SetInitialOrnt(unsigned int const&, Matrix const&);
		IMPORT int SetInitialPos(unsigned int const&, Vector const&);
		IMPORT int SetMissionObjectiveState(unsigned int const&, unsigned int const&, int, unsigned int);
		IMPORT int SetMissionObjectives(
		    unsigned int const&, unsigned int const&, MissionObjective const*, unsigned int, FmtStr const&, unsigned char, FmtStr const&);
		IMPORT int SetMoneyNeededToNextRank(unsigned int, int);
		IMPORT int SetMonkey(unsigned int);
		IMPORT int SetMsnID(unsigned int, unsigned int, unsigned int, bool, unsigned int);
		IMPORT int SetNumKills(unsigned int const&, int);
		IMPORT int SetNumMissionFailures(unsigned int const&, int);
		IMPORT int SetNumMissionSuccesses(unsigned int const&, int);
		IMPORT int SetRank(unsigned int, int);
		IMPORT int SetRobot(unsigned int);
		IMPORT int SetShipAndLoadout(unsigned int const&, unsigned int, EquipDescVector const&);
		IMPORT int SetStoryCue(unsigned int const&, unsigned int);
		IMPORT int SetTrent(unsigned int);
	}; // namespace Player

	namespace Reputation
	{
		IMPORT int Alloc(int&, FmtStr const&, FmtStr const&);
		IMPORT int EnumerateGroups(struct Enumerator&);
		IMPORT int Free(int const&);
		IMPORT int GetAffiliation(int const&, unsigned int&);
		IMPORT int GetAttitude(int const&, int const&, float&);
		IMPORT int GetGroupFeelingsTowards(int const&, unsigned int const&, float&);
		IMPORT int GetGroupName(unsigned int const&, unsigned int&);
		IMPORT int GetName(int const&, FmtStr&, FmtStr&);
		IMPORT int GetRank(int const&, float&);
		IMPORT int GetReputation(int&, ID_String const&);
		IMPORT int GetReputation(int&, char const*);
		IMPORT int GetReputation(int const&, unsigned int const&, float&);
		IMPORT int GetReputation(unsigned int const&, unsigned int const&, float&);
		IMPORT int GetReputationGroup(unsigned int&, char const*);
		IMPORT int GetShortGroupName(unsigned int const&, unsigned int&);
		IMPORT int SetAffiliation(int const&, unsigned int const&);
		IMPORT int SetAttitude(int const&, int const&, float);
		IMPORT int SetRank(int const&, float);
		IMPORT int SetReputation(int const&, unsigned int const&, float);
		IMPORT int SetReputation(unsigned int const&, unsigned int const&, float);
	}; // namespace Reputation

	namespace SpaceObj
	{
		struct CargoDesc
		{
			int vTbl;
			int unk1;
			int unk2;
			int unk3;
			int unk4;
		};

		struct ShipInfo
		{
			uint flag;
			uint system;
			uint shipArchetype;
			Vector pos;
			Vector unk1; // all 0
			Vector unk2; // all 0
			Matrix mOrientation;
			uint unk3; // 0
			uint loadout;
			OwnerList<pub::SpaceObj::CargoDesc> cargoDesc;
			uint look1;
			uint look2;
			uint unk4; // 0
			uint unk6; // 0
			uint comm;
			float unk7;
			float unk8;
			float unk9;
			float unk10;
			float unk11;
			float unk12;
			float unk13;
			uint unk14;

			int rep; // increases for each NPC spawned, starts at 0 or 1
			uint pilotVoice;
			uint unk15;  // 0
			uint health; // -1 = max health
			uint unk16;  // 0
			uint unk17;  // 0
			uint level;
		};

		struct SolarInfo
		{
			int flag; // 0x290; ShipInfo has this too, no clue whether actually a flag
			uint archId;
			uint systemId;
			Vector pos;
			Matrix orientation;
			uint loadoutId;
			struct StructCostume
			{
				UINT head;
				UINT body;
				UINT leftHand;
				UINT rightHand;
				UINT accessory[8];
				int accessories;
			};
			StructCostume costume;
			int rep;
			int voiceId;
			uint unk8; // 0
			uint unk9; // Boolean, only last byte is used
			int hitPointsLeft;
			char nickName[64]; // Has to be unique
			uint unk11;        // 0 unused?
			uint unk12;        // 1 = flagged as mission solar, 0 = normal
		};

		struct LootInfo
		{
			uint dunno; // "Flag" like the others?
			uint archId;
		};

		struct TerminalInfo
		{
			char hardPoint[0x20];
			uint type; // 1=berth 4=moor? 7=jump?
		};

		IMPORT int Activate(unsigned int const&, bool, int);
		IMPORT enum EQUIPMENT_RTYPE ActivateEquipment(unsigned int const&, struct EQInfo*);
		IMPORT int AddImpulse(unsigned int const&, Vector const&, Vector const&);
		IMPORT int Create(unsigned int&, struct ShipInfo const&);
		IMPORT int CreateLoot(unsigned int&, struct LootInfo const&);
		IMPORT int CreateSolar(unsigned int&, struct SolarInfo const&);
		IMPORT int Destroy(unsigned int, DestroyType);
		IMPORT int Dock(unsigned int const&, unsigned int const&, int, DOCK_HOST_RESPONSE);
		IMPORT int DockRequest(unsigned int const&, unsigned int const&);
		IMPORT int DrainShields(unsigned int);
		IMPORT int EnumerateCargo(unsigned int const&, pub::CargoEnumerator&);
		IMPORT int ExistsAndAlive(unsigned int);
		IMPORT int FormationResponse(unsigned int const&, enum FORMATION_RTYPE);
		IMPORT int GetArchetypeID(unsigned int const&, unsigned int&);
		IMPORT int GetAtmosphereRange(unsigned int const&, float&);
		IMPORT int GetBurnRadius(unsigned int const&, float&, Vector&);
		IMPORT int GetCargoSpaceOccupied(unsigned int const&, unsigned int&);
		IMPORT int GetCenterOMass(unsigned int const&, Vector&);
		IMPORT int GetDockingTarget(unsigned int const&, unsigned int&);
		IMPORT int GetEmptyPos(unsigned int const&, Transform const&, float const&, float const&, enum PosSelectionType const&, Vector&);
		IMPORT int GetGoodID(unsigned int const&, unsigned int&);
		IMPORT int GetHardpoint(unsigned int const&, char const*, Vector*, Matrix*);
		IMPORT int GetHealth(unsigned int const& SpaceObj, float& CurrentHealth, float& MaxHealth);
		IMPORT int GetInvincible(unsigned int, bool&, bool&, float&);
		IMPORT int GetJumpTarget(unsigned int const&, unsigned int&, unsigned int&);
		IMPORT int GetLocation(unsigned int, Vector&, Matrix&);
		IMPORT int GetMass(unsigned int const&, float&);
		IMPORT int GetMotion(unsigned int, Vector&, Vector&);
		IMPORT int GetRadius(unsigned int const&, float&, Vector&);
		IMPORT int GetRelativeHealth(unsigned int const&, float&);
		IMPORT int GetRep(unsigned int, int&);
		IMPORT int GetScannerRange(unsigned int, int&, int&);
		IMPORT int GetShieldHealth(unsigned int const& SpaceObj, float& CurrentShields, float& MaxShields, bool& bShieldsUp);
		IMPORT int GetSolarArchetypeID(unsigned int, unsigned int&);
		IMPORT int GetSolarArchetypeNickname(char*, int, unsigned int);
		IMPORT int GetSolarParent(unsigned int const&, unsigned int&);
		IMPORT int GetSolarRep(unsigned int, int&);
		IMPORT int GetSystem(unsigned int, unsigned int&);
		IMPORT int GetTarget(unsigned int const&, unsigned int&);
		IMPORT int GetTerminalInfo(unsigned int const&, int, TerminalInfo&);
		IMPORT int GetTradelaneNextAndPrev(unsigned int const&, unsigned int&, unsigned int&);
		IMPORT int GetType(unsigned int, unsigned int&);
		IMPORT int GetVoiceID(unsigned int const&, unsigned int&);
		IMPORT int InstantDock(unsigned int const&, unsigned int const&, int);
		IMPORT int IsPosEmpty(unsigned int const&, Vector const&, float const&, bool&);
		IMPORT int JettisonEquipment(unsigned int const&, unsigned short const&, int const&);
		IMPORT int JumpIn(unsigned int const&, unsigned int const&);
		IMPORT int LaneResponse(unsigned int const&, int);
		IMPORT int Launch(unsigned int const&, unsigned int const&, int);
		IMPORT int LightFuse(unsigned int const&, char const*, float);
		IMPORT int Relocate(unsigned int const&, unsigned int const&, Vector const&, Matrix const&);
		IMPORT int RequestSpaceScript(unsigned int const&, Vector const&, int const&, unsigned int, char const*);
		IMPORT int SendComm(unsigned int, unsigned int, unsigned int, Costume const*, unsigned int, unsigned int*, int, unsigned int, float, bool);
		IMPORT int SetInvincible2(unsigned int, bool, bool, float);
		IMPORT int SetInvincible(unsigned int, bool, bool, float);
		IMPORT int SetRelativeHealth(unsigned int const&, float);
	}; // namespace SpaceObj

	namespace System
	{
		struct SysObj
		{
			char nick[32]; // NOT NUL-terminated if longer
			Vector pos;
			UINT archId;
			UINT idsName;
			UINT idsInfo;
			char reputation[32];
			UINT dockWith;
			UINT gotoSystem;
			UINT system;
			// -------------------
			// Some nicknames are longer than 32 characters, so take advantage of the
			// fact that where it gets the nickname from immediately follows.
			size_t len; // TString<64>
			char nickname[64];
		};

		struct SysObjEnumerator
		{
			virtual bool operator()(const SysObj&) = 0;
		};

		struct Connection
		{
			UINT stuff[10];
		};

		struct ConnectionEnumerator
		{
			virtual bool operator()(const Connection&) = 0;
		};

		IMPORT int EnumerateConnections(unsigned int const&, pub::System::ConnectionEnumerator&, ConnectionType);
		IMPORT int EnumerateObjects(unsigned int const&, SysObjEnumerator&);
		IMPORT int EnumerateZones(unsigned int const&, struct ZoneEnumerator&);
		IMPORT int Find(unsigned int const&, char const*, unsigned int&);
		IMPORT int GetName(unsigned int, unsigned int&);
		IMPORT int GetNestedProperties(unsigned int const&, Vector const&, unsigned long&);
		IMPORT int InZones(unsigned int, Transform const&, float, float, float, unsigned int* const, unsigned int, unsigned int&);
		IMPORT int InZones(unsigned int, Vector const&, float, unsigned int* const, unsigned int, unsigned int&);
		IMPORT int LoadSystem(unsigned int const&);
		IMPORT int ScanObjects(unsigned int const&, unsigned int* const, unsigned int, Vector const&, float, unsigned int, unsigned int&);
	}; // namespace System

	namespace Zone
	{
		IMPORT float ClassifyPoint(unsigned int, Vector const&);
		IMPORT float GetDistance(unsigned int, Vector const&);
		IMPORT unsigned int GetId(unsigned int, char const*);
		IMPORT int GetLootableInfo(unsigned int, ID_String&, ID_String&, int&, int&, int&);
		IMPORT int GetName(unsigned int, unsigned int&);
		IMPORT int GetOrientation(unsigned int const&, Matrix&);
		// IMPORT  int GetPopulation(unsigned int,class weighted_vector<unsigned int> const * &);
		IMPORT Vector GetPos(unsigned int);
		IMPORT int GetProperties(unsigned int, unsigned long&);
		IMPORT float GetRadius(unsigned int);
		IMPORT int GetShape(unsigned int, enum ZoneShape&);
		IMPORT int GetSize(unsigned int, Vector&);
		IMPORT unsigned int GetSystem(unsigned int);
		IMPORT bool InZone(unsigned int, Vector const&, float);
		IMPORT bool Intersect(unsigned int, Vector const&, Vector const&, Vector&);
		IMPORT bool VerifyId(unsigned int);
	}; // namespace Zone

	namespace Controller
	{
		struct CreateParms
		{
			void* freeFunc;
			uint client;
		};

		enum PRIORITY;

		IMPORT unsigned int Create(char const*, char const*, CreateParms const*, PRIORITY);
		IMPORT void Destroy(unsigned int);
		IMPORT int SetHeartbeatInterval(unsigned int const&, float);
		IMPORT int _SendMessage(unsigned int const&, int, void const*);
	} // namespace Controller

}; // namespace pub

IMPORT void (*g_pPrivateChatHook)(unsigned short*, int);
IMPORT void (*g_pSystemChatHook)(unsigned short*, int);
IMPORT void (*g_pUniverseChatHook)(unsigned short*, int);

IMPORT PlayerDB Players;
extern "C" IMPORT IServerImpl Server;

#endif // _FLCORESERVER_H_