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
#pragma comment( lib, "FLCoreServer.lib" )

#define POPUPDIALOG_BUTTONS_LEFT_YES 1
#define POPUPDIALOG_BUTTONS_CENTER_NO 2
#define POPUPDIALOG_BUTTONS_RIGHT_LATER 4
#define POPUPDIALOG_BUTTONS_CENTER_OK 8


struct CHAT_ID
{
	uint iID;
};

enum DOCK_HOST_RESPONSE
{
	ACCESS_DENIED = 1,
	DOCK_DENIED = 2,
	DOCK_IN_USE = 3,
	PROCEED_DOCK = 4,
	DOCK = 5,
};

enum DestroyType
{
	VANISH = 0,
	FUSE = 1,
};

struct SGFGoodVaporizedInfo
{
    uint iDunno[128];
};

struct SSPMunitionCollisionInfo
{
	uint iProjectileArchID;
	DWORD dw2;
	DWORD dwTargetShip;
	ushort s1;

};

struct SSPBadLandsObjCollisionInfo
{
    uint iDunno[128];
};

struct SSPObjCollisionInfo
{
	uint iColliderObjectID;
	uint iColliderSubObjID;
	uint iDamagedObjectID;
	uint iDamagedSubObjID;
	float fDamage;
};

struct SSPUseItem
{
    uint iDunno[128];
};

struct XActivateEquip
{
	uint	iSpaceID;
	ushort	sID;
	bool	bActivate;
};

struct XActivateCruise
{
	uint	iShip;
	bool	bActivate;
};

struct XActivateThrusters
{
	uint	iShip;
	bool	bActivate;
};

struct XTractorObjects
{
	int iDunno[3];
	// This points to the start of the array of space IDs
	int *pArraySpaceID;
	// This points to the end of the array of space IDs
	int *pArraySpaceIDEnd;
};

struct SGFGoodSellInfo
{
	long	l1;
	uint	iArchID;
	int		iCount;
};

struct SGFGoodBuyInfo
{
	uint baseId;
	ulong lNull;
	uint iGoodID;
	int iCount;
};

struct XFireWeaponInfo
{
	uint iObject;
	Vector vTarget;
	uint iDunno;
	st6::list<ushort> hpIds;
};

struct XSetManeuver
{
	uint iShipFrom;
	uint IShipTo;
	uint iFlag;
};

struct XSetTarget
{
	uint iShip;
	uint iSlot;
	uint iSpaceID;
	uint iSubObjID;
};

struct SSPObjUpdateInfo
{
	uint iShip;
	Quaternion vDir;
	Vector vPos;
	float fTimestamp;
	float fThrottle;
	union
	{
		float fStateValue;
		uint iStateValue;
	};
	char cState;
};

struct XJettisonCargo
{
	uint iShip;
	uint iSlot;
	uint iCount;
};

struct XGoTradelane
{
	uint iShip;
	uint iTradelaneSpaceObj1;
	uint iTradelaneSpaceObj2;
};

struct CAccountListNode
{
	CAccountListNode *next;
	CAccountListNode *prev;
	uint iDunno1;
	wchar_t *wszCharname;
	uint iDunno2[32];
};

enum ConnectionType
{
	JUMPHOLE
};

enum EFLConnection {
    
};

enum InvincibilityReason {
    
};

struct CollisionGroupDescList
{
	st6::list<CollisionGroupDesc> data;
};

struct SCreateCharacterInfo
{
	wchar_t wszCharname[24];
	uint iNickName; // From [Faction] section of newcharacter.ini
	uint iBase;     // From [Faction] section of newcharacter.ini
	uint iPackage;  // From [Faction] section of newcharacter.ini
	uint iPilot;    // From [Faction] section of newcharacter.ini
	uint iDunno[96];
};

struct SStartupInfo
{
	uint iDunno[130];
	int iMaxPlayers;
};

struct SLoginInfo
{
	wchar_t wszAccount[36];
};

struct FLString
{
	st6::string value;
	UINT iDunno2[12];
};

class IMPORT CAccount
{
public:
	 CAccount(class CAccount const &);
	 CAccount(void);
	 virtual ~CAccount(void);
	 class CAccount & operator=(class CAccount const &);
	 void AppendCharacterNames(st6::list<st6::wstring &> &);
	 void DeleteCharacterFromID(st6::string &);
	 void ForceLogout(void);
	 void InitFromFolder(char const *);

public:
	uint iDunno1;
	wchar_t *wszAccID;
	uint iDunno2[7];
	CAccountListNode *pFirstListNode;
	uint iNumberOfCharacters;
	uint iDunno4[32];
};

namespace BaseGroupMessage
{
	enum Type;
};

class IMPORT CPlayerGroup
{
public:
	 CPlayerGroup(class CPlayerGroup const &);
	 CPlayerGroup(void);
	 virtual ~CPlayerGroup(void);
	 class CPlayerGroup & operator=(class CPlayerGroup const &);
	 bool AddInvite(unsigned int);
	 bool AddMember(unsigned int);
	 bool DelInvite(unsigned int);
	 bool DelMember(unsigned int);
	 void DeliverChat(unsigned long,void const *);
	 static class CPlayerGroup * FromGroupID(unsigned int);
	 unsigned int GetID(void);
	 unsigned int GetInviteCount(void);
	 unsigned int GetMember(int)const ;
	 unsigned int GetMemberCount(void);
	 unsigned int GetMissionID(void);
	 unsigned int GetMissionSetBy(void);
	 void HandleClientLogout(unsigned int);
	 bool IsFull(void);
	 bool IsInvited(unsigned int);
	 bool IsMember(unsigned int);
	 void RewardMembers(int);
	 void SendChat(int,unsigned short const *,...);
	 void SendGroup(enum BaseGroupMessage::Type,unsigned int);
	 void SetMissionID(unsigned int,unsigned int);
	 void SetMissionMessage(struct CSetMissionMessage &);
	 void SetMissionObjectives(struct CMissionObjectives &);
	 void StoreMemberList(st6::vector<unsigned int> &);

protected:
	 static class st6::map<unsigned int const, class CPlayerGroup *, struct st6::less<unsigned int const>, class st6::allocator<class CPlayerGroup *>>  s_GroupIDToGroupPtrMap;
	 static unsigned int  s_uiGroupID;

public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT [[Hook, ServerCall]] IServerImpl
{
	IServerImpl(const IServerImpl&);
	IServerImpl();
	IServerImpl& operator=(const IServerImpl&);

	// N.B. Do not modify order, vtable ordering is fixed by Server.dll
	[[DisconnectCheck]] virtual void FireWeapon(uint clientId, const XFireWeaponInfo& fwi);
	[[CallInner, DisconnectCheck]] virtual void ActivateEquip(uint clientId, const XActivateEquip& aq);
	[[CallInner, DisconnectCheck]] virtual void ActivateCruise(uint clientId, const XActivateCruise& ac);
	[[CallInner, DisconnectCheck]] virtual void ActivateThrusters(uint clientId, const XActivateThrusters& at);
	virtual void SetTarget(uint clientId, const XSetTarget& st);
	virtual void TractorObjects(uint clientId, const XTractorObjects& to);
	[[CallInner, CallCatch]] virtual void GoTradelane(uint clientId, const XGoTradelane& gt);
	[[CallInner]] virtual void StopTradelane(uint clientId, uint shipID, uint tradelaneRing1, uint tradelaneRing2);
	virtual void JettisonCargo(uint clientId, const XJettisonCargo& jc);
	[[CallInner, CallInnerAfter]] virtual bool Startup(const SStartupInfo& si);
	[[CallInnerAfter, NoPluginsAfter]] virtual void Shutdown();
	[[CallInner, NoLog]] virtual int Update();
	[[NoHook]] virtual void ElapseTime(float);
	[[NoHook]] virtual void __nullopt1();
	[[NoHook]] virtual bool SwapConnections(EFLConnection, EFLConnection);
	[[NoHook]] virtual void __nullopt2();
	[[CallInner]] virtual void DisConnect(uint clientId, EFLConnection conn);
	[[DisconnectCheck, CallInner(true), CallInnerAfter]]
    virtual void OnConnect(uint clientId);
	[[CallInnerAfter]] virtual void Login(const SLoginInfo& li, uint clientId);
	[[DisconnectCheck, CallInner(true), CallCatch]]
    virtual void CharacterInfoReq(uint clientId, bool);
	[[DisconnectCheck, CallInner(true), CallInnerAfter]]
	virtual void CharacterSelect(const CHARACTER_ID& cid, uint clientId);
	[[NoHook]] virtual void __nullopt3();
	virtual void CreateNewCharacter(const SCreateCharacterInfo&, uint clientId);
	virtual void DestroyCharacter(struct CHARACTER_ID const &, uint clientId);
	[[NoHook]] virtual void CharacterSkipAutosave(uint);
	virtual void ReqShipArch(uint archID, uint clientId);
	virtual void ReqHullStatus(float status, uint clientId);
	virtual void ReqCollisionGroups(const st6::list<CollisionGroupDesc>& collisionGroups, uint clientId);
	virtual void ReqEquipment(const EquipDescList& edl, uint clientId);
	[[NoHook]] virtual void ReqCargo(const EquipDescList&, uint);
	virtual void ReqAddItem(uint goodID, const char* hardpoint, int count, float status, bool mounted, uint clientId);
	virtual void ReqRemoveItem(ushort slotID, int count, uint clientId);
	virtual void ReqModifyItem(ushort slotID, const char* hardpoint, int count, float status, bool mounted, uint clientId);
	virtual void ReqSetCash(int cash, uint clientId);
	virtual void ReqChangeCash(int cashAdd, uint clientId);
	[[DisconnectCheck, CallInner, CallInnerAfter]]
	virtual void BaseEnter(uint baseID, uint clientId);
	[[DisconnectCheck, CallInner, CallInnerAfter]]
	virtual void BaseExit(uint baseID, uint clientId);
	virtual void LocationEnter(uint locationID, uint clientId);
	virtual void LocationExit(uint locationID, uint clientId);
	virtual void BaseInfoRequest(unsigned int,unsigned int,bool);
	virtual void LocationInfoRequest(unsigned int,unsigned int,bool);
	virtual void GFObjSelect(unsigned int,unsigned int);
	virtual void GFGoodVaporized(const SGFGoodVaporizedInfo& gvi, uint clientId);
	virtual void MissionResponse(unsigned int,unsigned long,bool, uint clientId);
	virtual void TradeResponse(unsigned char const *,int, uint clientId);
	virtual void GFGoodBuy(const SGFGoodBuyInfo&, uint clientId);
	[[CallInner(true), DisconnectCheck]] virtual void GFGoodSell(const SGFGoodSellInfo&, uint clientId);
	[[CallInnerAfter]] virtual void SystemSwitchOutComplete(uint shipID, uint clientId);
	[[CallInner, CallInnerAfter, DisconnectCheck]]
	virtual void PlayerLaunch(uint shipID, uint clientId);
	[[CallInner]] virtual void LaunchComplete(uint baseID, uint shipID);
	[[CallInnerAfter]] virtual void JumpInComplete(uint systemID, uint shipID);
	virtual void Hail(unsigned int,unsigned int,unsigned int);
	[[CallInner(true), NoLog, DisconnectCheck]]
	virtual void SPObjUpdate(const SSPObjUpdateInfo& ui, uint clientId);
	[[CallInner, DisconnectCheck]]
	virtual void SPMunitionCollision(const SSPMunitionCollisionInfo& mci, uint clientId);
	[[NoHook]] virtual void SPBadLandsObjCollision(const SSPBadLandsObjCollisionInfo&, uint);
	[[DisconnectCheck]] virtual void SPObjCollision(const SSPObjCollisionInfo& oci, uint clientId);
	virtual void SPRequestUseItem(const SSPUseItem& ui, uint clientId);
	virtual void SPRequestInvincibility(uint shipID, bool enable, InvincibilityReason reason, uint clientId);
	[[NoHook]] virtual void SaveGame(const CHARACTER_ID&, const ushort*, uint);
	[[NoHook]] virtual void MissionSaveB(uint, ulong);
	// eventType: 0 = docking, 1 = formation
	virtual void RequestEvent(int eventType, uint shipID, uint dockTarget, uint, ulong, uint clientId);
	// eventType: 0 = docking, 1 = formation
	virtual void RequestCancel(int eventType, uint shipID, uint, ulong, uint clientId);
	virtual void MineAsteroid(uint systemID, const Vector& pos, uint crateID, uint lootID, uint count, uint clientId);
	[[NoHook]] virtual void CommComplete(uint, uint, uint, enum CommResult);
	virtual void RequestCreateShip(uint clientId);
	virtual void SPScanCargo(const uint&, const uint&, uint);
	virtual void SetManeuver(uint clientId, const XSetManeuver& sm);
	virtual void InterfaceItemUsed(uint, uint);
	virtual void AbortMission(uint clientId, uint);
	[[NoHook]] virtual void RTCDone(uint, uint);
	virtual void SetWeaponGroup(uint clientId, uchar*, int);
	virtual void SetVisitedState(uint clientId, uchar*, int);
	virtual void RequestBestPath(uint clientId, uchar*, int);
	virtual void RequestPlayerStats(uint clientId, uchar*, int);
	[[NoHook]] virtual void PopUpDialog(uint, uint);
	virtual void RequestGroupPositions(uint clientId, uchar*, int);
	[[NoHook]] virtual void SetMissionLog(uint, uchar*, int);
	virtual void SetInterfaceState(uint clientId, uchar*, int);
	virtual void RequestRankLevel(uint clientId, uchar*, int);
	[[CallInner]] virtual void InitiateTrade(uint clientId1, uint clientId2);
	[[CallInnerAfter, DisconnectCheck]] virtual void TerminateTrade(uint clientId, int accepted);
	virtual void AcceptTrade(uint clientId, bool);
	virtual void SetTradeMoney(uint clientId, ulong);
	virtual void AddTradeEquip(uint clientId, const EquipDesc& ed);
	virtual void DelTradeEquip(uint clientId, const EquipDesc& ed);
	virtual void RequestTrade(uint, uint);
	virtual void StopTradeRequest(uint clientId);
	[[NoHook]] virtual void ReqDifficultyScale(float, uint);
	[[NoHook]] virtual unsigned int GetServerID();
	[[NoHook]] virtual char const * GetServerSig();
	[[NoHook]] virtual void DumpPacketStats(const char*);
	[[Disable]] virtual void Dock(const uint&, const uint&);

	[[CallInner(true), Semaphore(g_InSubmitChat), Address(-0x08)]]
	virtual void SubmitChat(CHAT_ID cidFrom, ulong size, const void* rdlReader, CHAT_ID cidTo, int);

public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct CHARACTER_ID
{
	CHARACTER_ID(void);
	struct CHARACTER_ID const & operator=(struct CHARACTER_ID const &);
	void invalidate(void);
	bool is_valid(void)const;

	char szCharFilename[512]; // Only first 16 bytes are ever used
};

struct PlayerData
{
	wchar_t wszAccID[40];
	long x050, x054, x058, x05C;
	uint iNumberOfCharacters;
	CHARACTER_ID charFile;
	uint iShipArchetype;
	float fRelativeHealth;
	CollisionGroupDescList collisionGroupDesc;
	EquipDescList equipDescList;
	int iRank;
	int iMoneyNeededToNextRank;
	struct structCostume
	{
		UINT iHead;
		UINT iBody;
		UINT iLefthand;
		UINT iRighthand;
		UINT iAccessory[8];
		int  iAccessories;
	};
	structCostume costume1;
	long x2C0, x2C4, x2C8, x2CC, x2D0, x2D4, x2D8, x2DC, x2E0;
	structCostume costume2;
	uint iReputation;
	int iInspectCash;
	int iWorth;
	uint iShipArchetypeWhenLanding;
	EquipDescList lShadowEquipDescList;
	int iNumKills;
	int iNumMissionSuccesses;
	int iNumMissionFailures;
	bool bSkipAutosave;
	char __padding0[3];
	uint iSaveCount;
	uint iOnlineID;
	bool bCheated;
	char __padding1[3];
	Vector vPosition;
	Matrix mOrientation;
	FLString weaponGroup; // 0x10 bytes
	uint iSetToZero;
	float fDifficulty;
	ushort sLastEquipID;
	char __padding2[2];
	uint aMenuItem;
	uint iOnlineID2;
	long x3D4, x3D8;
	uint iTradeRequestCount;
	uint systemId;
	uint iShipID;
	uint iCreatedShipID;
	uint baseId;
	uint iLastBaseID;
	uint iEnteredBase;
	uint iBaseRoomID;
	uint iCharacterID;
	class CAccount* Account;
	class CPlayerGroup* PlayerGroup;
	uint iMissionID;
	uint iMissionSetBy;
	uint iExitedBase;
	uint iUnknownLocID;
};

struct PlayerDBTreeNode
{
	PlayerDBTreeNode *pLeft;
	PlayerDBTreeNode *pParent;
	PlayerDBTreeNode *pRight;
	ulong l1;
	// File name of character
	char *szFLName;
	// Length of file name
	uint iLength;
	// Always seems to be 0x1F. Possibly max length of szFLName
	uint iDunno;
	// Account for this player
	CAccount *acc;
};

class IMPORT PlayerDB
{
public:
	 PlayerDB(class PlayerDB const &);
	 PlayerDB(void);
	 ~PlayerDB(void);
	 class PlayerDB & operator=(class PlayerDB const &);
	 struct PlayerData & operator[](unsigned int const &);
	 bool BanAccount(st6::wstring &,bool);
	 void BuildLocalUserDir(void);
	 unsigned int CountPlayersInSystem(int);
	 bool CreateAccount(st6::wstring &);
	 void DeleteAccount(st6::wstring &);
	 void DeleteCharacterFromID(st6::wstring &);
	 bool DeleteCharacterFromName(st6::wstring &);
	 class CAccount * FindAccountFromCharacterID(st6::string &);
	 class CAccount * FindAccountFromCharacterName(st6::wstring &);
	 class CAccount * FindAccountFromClientID(unsigned int);
	 class CAccount * FindAccountFromName(st6::wstring &);
	 bool GetAccountAdminRights(st6::wstring &);
	 bool GetAccountBanned(st6::wstring &);
	 unsigned short const * GetActiveCharacterName(unsigned int)const ;
	 bool GetCharactersForAccount(st6::wstring &,class st6::list<st6::wstring> &);
	 unsigned int GetGroupID(unsigned int);
	 st6::wstring & GetMOTD(void);
	 unsigned int GetMaxPlayerCount(void);
	 unsigned int GetServerID(void);
	 char const * GetServerSig(void);
	 void LockAccountAccess(st6::wstring &);
	 bool MakeLocalUserPath(char *,char const *);
	 void ReadCharacterName(char const *,st6::wstring &);
	 void SendGroupID(unsigned int,unsigned int);
	 void SendSystemID(unsigned int,unsigned int);
	 bool SetAccountAdminRights(st6::wstring &,bool);
	 bool SetAccountPassword(st6::wstring &,st6::wstring &);
	 void SetMOTD(st6::wstring &);
	 void UnlockAccountAccess(st6::wstring &);
	 void cleanup(unsigned int);
	 bool create_new_character(struct SCreateCharacterInfo const &,unsigned int);
	 bool create_restart_file(char const *);
	 void free(void);
	 void init(unsigned int,bool);
	 bool is_valid(unsigned int const &);
	 bool is_valid_ship_owner(unsigned int const &,unsigned int const &);
	 unsigned char login(struct SLoginInfo const &,unsigned int);
	 void logout(unsigned int);
	 void logout_all(void);
	 struct PlayerData * traverse_active(struct PlayerData *)const ;

private:
	 int create_account(struct SLoginInfo const &);
	 unsigned char load_user_data(struct SLoginInfo const &,unsigned int);
	 unsigned int to_index(unsigned int);

public:
	uint iDunno1[13];
	PlayerDBTreeNode *pFirstNode;
	PlayerDBTreeNode *pLastNode;
	uint iDunno2;
	uint iNumAccounts;
};


namespace CmnAsteroid  // from FLCoreCommon.h
{
	class CAsteroidSystem;
}; 

namespace SrvAsteroid
{
	class IMPORT SrvAsteroidSystem
	{
	public:
		 SrvAsteroidSystem(SrvAsteroidSystem const &);
		 SrvAsteroidSystem(void);
		 ~SrvAsteroidSystem(void);
		 SrvAsteroidSystem & operator=(SrvAsteroidSystem const &);
		 int AddRef(void);
		 int Release(void);
		 void load(char const *);
		 void map_asteroid_fields(void);
		 void set_cmn_system(class CmnAsteroid::CAsteroidSystem *);
		 void set_sys_id(unsigned int);
		 void update(void);

	public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

};

struct IMPORT StarSystem
{
	 unsigned int count_players(unsigned int)const ;

public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace SysDB
{
	IMPORT  st6::map<unsigned int, class StarSystem, st6::less<unsigned int>, st6::allocator<std::pair<const unsigned int, class StarSystem>>> SysMap;
};

namespace Controller
{
	struct TimerExpired;
}

template <class T> class IMPORT OwnerList
{
public:
	OwnerList<T>();
	virtual ~OwnerList<T>();
	class OwnerList<T> & operator=(class OwnerList<T> const &);
	void free();
protected:
	unsigned char data[16];
};

namespace pub
{
	struct CargoEnumerator;
	
	IMPORT  int BuildBaseReader(class INI_Reader &,unsigned int const &);
	IMPORT  int BuildSystemReader(class INI_Reader &,unsigned int const &);
	IMPORT  struct HINSTANCE__ * DLL_LoadLibrary(char const *);
	IMPORT  void DebugPrint(char const *,int);
	IMPORT  int FindHardpoint(char const *,unsigned int,class Vector &,class Matrix &);
	IMPORT  int GetBaseID(unsigned int &,char const *);
	IMPORT  unsigned int GetBaseNickname(char *,unsigned int,unsigned int const &);
	IMPORT  int GetBaseStridName(unsigned int &,unsigned int const &);
	IMPORT  int GetBases(unsigned int const &,unsigned int * const,unsigned int,unsigned int &);
	IMPORT  int GetCargoHoldSize(unsigned int const &,unsigned int &);
	IMPORT  int GetCostumeID(int &,char const *);
	IMPORT  struct IFileSystem * GetDataPath(void);
	IMPORT  int GetEquipmentID(unsigned int &,char const *);
	IMPORT  int GetFullHealth(unsigned int const &,unsigned int &);
	IMPORT  int GetGoodID(unsigned int &,char const *);
	IMPORT  int GetGoodProperties(unsigned int const &,float &,float &);
	IMPORT  int GetLoadout(struct EquipDescVector &,unsigned int const &);
	IMPORT  int GetLoadoutID(unsigned int &,char const *);
	IMPORT  int GetLoadoutName(unsigned int const &,char *,int);
	IMPORT  unsigned int GetLocationNickname(char *,unsigned int,unsigned int const &);
	IMPORT  int GetLocations(unsigned int const &,unsigned int * const,unsigned int,unsigned int &);
	IMPORT  int GetMaxHitPoints(unsigned int const &,int &);
	IMPORT  int GetNavMapScale(unsigned int,float &);
	IMPORT  unsigned int GetNicknameId(char const *);
	IMPORT  int GetRwTime(double &);
	IMPORT  int GetShipArchSTRID(unsigned int const &,unsigned int &);
	IMPORT  int GetShipID(unsigned int &,char const *);
	IMPORT  int GetSolarType(unsigned int const &,unsigned int &);
	IMPORT  int GetSystem(unsigned int &,unsigned int const &);
	IMPORT  int GetSystemGateConnection(unsigned int const &,unsigned int &);
	IMPORT  int GetSystemID(unsigned int &,char const *);
	IMPORT  unsigned int GetSystemNickname(char *,unsigned int,unsigned int const &);
	IMPORT  int GetTime(double &);
	IMPORT  int GetType(unsigned int const &,unsigned int &);
	IMPORT  int GetVoiceID(unsigned int &,char const *);
	IMPORT  int IsCommodity(unsigned int const &,bool &);
	IMPORT  unsigned short MakeId(char const *);
	IMPORT  bool NextBaseID(unsigned int &);
	IMPORT  bool NextSystemID(unsigned int &);
	IMPORT  int ReportFreeTerminal(unsigned int,int);
	IMPORT  int Save(unsigned int,unsigned int);
	IMPORT  int SetTimer(unsigned int const &,struct Controller::TimerExpired const &,float);
	IMPORT  bool SinglePlayer(void);
	IMPORT  int TranslateArchToGood(unsigned int const &,unsigned int &);
	IMPORT  int TranslateGoodToMsgIdPrefix(unsigned int,struct TString<64> &);
	IMPORT  int TranslateShipToMsgIdPrefix(unsigned int,struct TString<64> &);
	IMPORT  int TranslateSystemToMsgIdPrefix(unsigned int,struct TString<64> &);

	namespace AI
	{
		class Personality;

		IMPORT  enum OP_RTYPE  SubmitDirective(unsigned int,class BaseOp *);
		IMPORT  enum OP_RTYPE  SubmitState(unsigned int,class BaseOp *);
		IMPORT  bool enable_all_maneuvers(unsigned int);
		IMPORT  bool enable_maneuver(unsigned int,int,bool);
		IMPORT  int get_behavior_id(unsigned int);
		IMPORT  bool get_personality(unsigned int,class Personality &);
		IMPORT  enum ScanResponse  get_scan_response(unsigned int,unsigned int,unsigned int);
		IMPORT  int get_state_graph_id(unsigned int);
		IMPORT  bool lock_maneuvers(unsigned int,bool);
		IMPORT  void refresh_state_graph(unsigned int);
		IMPORT  int remove_forced_target(unsigned int,unsigned int);
		IMPORT  enum OP_RTYPE  set_directive_priority(unsigned int,enum DirectivePriority);
		IMPORT  bool set_player_enemy_clamp(unsigned int,int,int);
		IMPORT  int submit_forced_target(unsigned int,unsigned int);
		IMPORT  enum FORMATION_RTYPE  update_formation_state(unsigned int,unsigned int,class Vector const &);
	};

	namespace Audio
	{
		struct Tryptich {
			uint iDunno;
			uint iDunno2;
			uint iDunno3;
			uint iMusicID;
		};

		IMPORT  int CancelMusic(unsigned int);
		IMPORT  int PlaySoundEffect(unsigned int,unsigned int);
		IMPORT  int SetMusic(unsigned int,struct Tryptich const &);
	};

	namespace Controller
	{
		struct CreateParms
		{
			void* pFreeFunc;
			uint clientId;
		};

		enum PRIORITY;

		IMPORT  unsigned int Create(char const *,char const *,struct CreateParms const *,enum PRIORITY);
		IMPORT  void Destroy(unsigned int);
		IMPORT  int SetHeartbeatInterval(unsigned int const &,float);
		IMPORT  int _SendMessage(unsigned int const &,int,void const *);
	};

	namespace GF
	{
		IMPORT  unsigned long AmbientScriptCreate(struct AmbientScriptDescription const &);
		IMPORT  void AmbientScriptDestroy(unsigned long *);
		IMPORT  unsigned long CharacterBehaviorCreate(struct CharacterBehaviorDescription const &);
		IMPORT  void CharacterBehaviorDestroy(unsigned long *);
		IMPORT  unsigned int CharacterCreate(struct CharacterDescription const &);
		IMPORT  void CharacterDestroy(unsigned int *);
		IMPORT  void CharacterSetBehavior(unsigned int,unsigned long);
		IMPORT  void EnumerateCharacterPlacementIni(unsigned int,void (*)(int,class INI_Reader *,void *),void *);
		IMPORT  unsigned int FindBase(char const *);
		IMPORT  unsigned int FindLocation(unsigned int,char const *);
		IMPORT  char const * FormCharacterPlacementName(struct SetpointProperties const *);
		IMPORT  int GetAccessory(char const *);
		IMPORT  int GetBasePosition(unsigned int const &,unsigned int const &,class Vector &);
		IMPORT  int GetBodyPart(char const *,int);
		IMPORT  unsigned int GetCharacterOnPlacement(unsigned int,unsigned int,int);
		IMPORT  int GetCharacterPlacementByName(unsigned int,char const *,int &);
		IMPORT  char const * GetCharacterPlacementName(unsigned int,int);
		IMPORT  unsigned long GetCharacterPlacementOccupancy(unsigned int,int);
		IMPORT  int GetCharacterPlacementPosture(unsigned int,int,unsigned long &);
		IMPORT  bool GetCharacterPlacementProperties(unsigned int,int,struct SetpointProperties *);
		IMPORT  void GetCostumeByID(int,struct Costume &);
		IMPORT  int GetCostumeSkeletonGender(struct Costume const &,int &);
		IMPORT  int GetMissionVendorOfferCount(unsigned int,unsigned int);
		IMPORT  int GetNumCharacterPlacements(unsigned int);
		IMPORT  float GetRtcPerformanceSlider(void);
		IMPORT  unsigned int GetSpaceflightLocation(void);
		IMPORT  bool IsCharacterPlacementNormal(unsigned int,int);
		IMPORT  bool IsCharacterPlacementSpecial(unsigned int,int);
		IMPORT  void MissionVendorAcceptance(unsigned long,bool,struct FmtStr const &,unsigned int);
		IMPORT  unsigned long MissionVendorOfferCreate(struct MissionVendorOfferDescription const &);
		IMPORT  void MissionVendorOfferDestroy(unsigned long *);
		IMPORT  unsigned long NewsBroadcastCreate(struct NewsBroadcastDescription const &);
		IMPORT  void NewsBroadcastDestroy(unsigned long *);
		IMPORT  int ReportWhyMissionVendorEmpty(unsigned int,enum MVEmptyReason);
	};

	namespace Market
	{
		IMPORT  int GetCommoditiesForSale(unsigned int,unsigned int * const,int *);
		IMPORT  int GetCommoditiesInDemand(unsigned int,unsigned int * const,int *);
		IMPORT  int GetGoodJumpDist(unsigned int,unsigned int &);
		IMPORT  int GetMinInventory(unsigned int,unsigned int,int &);
		IMPORT  int GetNominalPrice(unsigned int,float &);
		IMPORT  int GetNumCommoditiesForSale(unsigned int,int *);
		IMPORT  int GetNumCommoditiesInDemand(unsigned int,int *);
		IMPORT  int GetPrice(unsigned int,unsigned int,float &);
		IMPORT  int IsGoodInDemand(unsigned int,unsigned int,bool &);
	};

	namespace Phantom
	{
		IMPORT  int Attach(unsigned int const &,void *);
		IMPORT  int Create(unsigned int,class Vector const &,class Vector const &,class Matrix const &,unsigned int,void * &);
		IMPORT  int Create(unsigned int,float,class Vector const &,unsigned int,void * &);
		IMPORT  int Destroy(void *);
		IMPORT  int Detach(void *);
		IMPORT  int SetActive(void *,bool);
	};

	namespace Player
	{
		IMPORT  int AddCargo(unsigned int const &,unsigned int const &,unsigned int,float,bool);
		IMPORT  int AdjustCash(unsigned int const &,int);
		IMPORT  int CfgInterfaceNotification(unsigned int,unsigned int,bool,int);
		IMPORT  int DisplayMissionMessage(unsigned int const &,struct FmtStr const &,enum MissionMessageType,bool);
		IMPORT  int EnumerateCargo(unsigned int const &,struct pub::CargoEnumerator &);
		IMPORT  int ForceLand(unsigned int,unsigned int);
		IMPORT  int GetAssetValue(unsigned int const &,float &);
		IMPORT  int GetBase(unsigned int const &,unsigned int &);
		IMPORT  int GetBody(unsigned int const &,unsigned int &);
		IMPORT  int GetCharacter(unsigned int const &,unsigned int &);
		IMPORT  int GetGender(unsigned int const &,int &);
		IMPORT  int GetGroupMembers(unsigned int,st6::vector<unsigned int> &);
		IMPORT  int GetGroupSize(unsigned int,unsigned int &);
		IMPORT  int GetLocation(unsigned int const &,unsigned int &);
		IMPORT  int GetMoneyNeededToNextRank(unsigned int const &,int &);
		IMPORT  int GetMsnID(unsigned int,unsigned int &);
		IMPORT  int GetName(unsigned int,st6::wstring &);
		IMPORT  int GetNumKills(unsigned int const &,int &);
		IMPORT  int GetNumMissionFailures(unsigned int const &,int &);
		IMPORT  int GetNumMissionSuccesses(unsigned int const &,int &);
		IMPORT  int GetRank(unsigned int const &,int &);
		IMPORT  int GetRelativeHealth(unsigned int const &,float &);
		IMPORT  int GetRemainingHoldSize(unsigned int const &,float &);
		IMPORT  int GetRep(unsigned int const &,int &);
		IMPORT  int GetShip(unsigned int const &,unsigned int &);
		IMPORT  int GetShipID(unsigned int const &,unsigned int &);
		IMPORT  int GetSystem(unsigned int const &,unsigned int &);
		IMPORT  int InspectCash(unsigned int const &,int &);
		IMPORT  int IsGroupMember(unsigned int,unsigned int,bool &);
		IMPORT  int LoadHint(unsigned int,struct BaseHint *);
		IMPORT  int MarkObj(unsigned int,unsigned int,int);
		IMPORT  int PopUpDialog(unsigned int,struct FmtStr const &,struct FmtStr const &,unsigned int);
		IMPORT  int RemoveCargo(unsigned int const &,unsigned short,unsigned int);
		IMPORT  int RemoveFromGroup(unsigned int);
		IMPORT  int ReplaceMissionObjective(unsigned int const &,unsigned int const &,unsigned int,struct MissionObjective const &);
		IMPORT  int ReturnBestPath(unsigned int,unsigned char *,int);
		IMPORT  int ReturnPlayerStats(unsigned int,unsigned char *,int);
		IMPORT  int RevertCamera(unsigned int);
		IMPORT  int RewardGroup(unsigned int,int);
		IMPORT  int SendNNMessage(unsigned int,unsigned int);
		IMPORT  int SetCamera(unsigned int,class Transform const &,float,float);
		IMPORT  int SetCostume(unsigned int const &,int);
		IMPORT  int SetInitialOrnt(unsigned int const &,class Matrix const &);
		IMPORT  int SetInitialPos(unsigned int const &,class Vector const &);
		IMPORT  int SetMissionObjectiveState(unsigned int const &,unsigned int const &,int,unsigned int);
		IMPORT  int SetMissionObjectives(unsigned int const &,unsigned int const &,struct MissionObjective const *,unsigned int,struct FmtStr const &,unsigned char,struct FmtStr const &);
		IMPORT  int SetMoneyNeededToNextRank(unsigned int,int);
		IMPORT  int SetMonkey(unsigned int);
		IMPORT  int SetMsnID(unsigned int,unsigned int,unsigned int,bool,unsigned int);
		IMPORT  int SetNumKills(unsigned int const &,int);
		IMPORT  int SetNumMissionFailures(unsigned int const &,int);
		IMPORT  int SetNumMissionSuccesses(unsigned int const &,int);
		IMPORT  int SetRank(unsigned int,int);
		IMPORT  int SetRobot(unsigned int);
		IMPORT  int SetShipAndLoadout(unsigned int const &,unsigned int,struct EquipDescVector const &);
		IMPORT  int SetStoryCue(unsigned int const &,unsigned int);
		IMPORT  int SetTrent(unsigned int);
	};

	namespace Reputation
	{
		IMPORT  int Alloc(int &,struct FmtStr const &,struct FmtStr const &);
		IMPORT  int EnumerateGroups(struct Enumerator &);
		IMPORT  int Free(int const &);
		IMPORT  int GetAffiliation(int const &,unsigned int &);
		IMPORT  int GetAttitude(int const &,int const &,float &);
		IMPORT  int GetGroupFeelingsTowards(int const &,unsigned int const &,float &);
		IMPORT  int GetGroupName(unsigned int const &,unsigned int &);
		IMPORT  int GetName(int const &,struct FmtStr &,struct FmtStr &);
		IMPORT  int GetRank(int const &,float &);
		IMPORT  int GetReputation(int &,struct ID_String const &);
		IMPORT  int GetReputation(int &,char const *);
		IMPORT  int GetReputation(int const &,unsigned int const &,float &);
		IMPORT  int GetReputation(unsigned int const &,unsigned int const &,float &);
		IMPORT  int GetReputationGroup(unsigned int &,char const *);
		IMPORT  int GetShortGroupName(unsigned int const &,unsigned int &);
		IMPORT  int SetAffiliation(int const &,unsigned int const &);
		IMPORT  int SetAttitude(int const &,int const &,float);
		IMPORT  int SetRank(int const &,float);
		IMPORT  int SetReputation(int const &,unsigned int const &,float);
		IMPORT  int SetReputation(unsigned int const &,unsigned int const &,float);
	};

	namespace SpaceObj
	{
		struct CargoDesc
		{
			int vTbl;
			int iUnk1;
			int iUnk2;
			int iUnk3;
			int iUnk4;
		};

		struct ShipInfo
		{
			uint iFlag;
			uint iSystem;
			uint iShipArchetype;
			Vector vPos;
			Vector vUnk1; // all 0
			Vector vUnk2; // all 0
			Matrix mOrientation;
			uint iUnk1; // 0
			uint iLoadout;
			OwnerList<pub::SpaceObj::CargoDesc> cargoDesc;
			uint iLook1;
			uint iLook2;
			uint unk4; // 0
			uint unk5; // 0
			uint iComm;
			float fUnk2;
			float fUnk3;
			float fUnk4;
			float fUnk5;
			float fUnk6;
			float fUnk7;
			float fUnk8;
			uint iUnk2;
			
			int iRep; // increases for each NPC spawned, starts at 0 or 1
			uint iPilotVoice;
			uint unk6; // 0
			uint iHealth; // -1 = max health
			uint unk7; // 0
			uint unk8; // 0
			uint iLevel;
		};

		struct SolarInfo{
			int iFlag; //0x290; ShipInfo has this too, no clue whether actually a flag
			uint iArchID;
			uint systemId;
			Vector vPos;
			Matrix mOrientation;
			uint iLoadoutID;
			struct structCostume
			{
			  UINT head;
			  UINT body;
			  UINT lefthand;
			  UINT righthand;
			  UINT accessory[8];
			  int  accessories;
			};
			structCostume Costume;
			int iRep;
			int iVoiceID;
			uint iUnk8; //0
			uint iUnk9; //Boolean, only last byte is used
			int iHitPointsLeft;
			char cNickName[64]; //Has to be unique
			uint iUnk11; //0 unused?
			uint iUnk12; // 1 = flagged as mission solar, 0 = normal
		};

		struct LootInfo {
			uint iDunno; // "Flag" like the others?
			uint iArchID;
		};

		struct TerminalInfo {
			char szHardPoint[0x20];
			uint iType; // 1=berth 4=moor? 7=jump?
		};

		IMPORT  int Activate(unsigned int const &,bool,int);
		IMPORT  enum EQUIPMENT_RTYPE  ActivateEquipment(unsigned int const &,struct EQInfo *);
		IMPORT  int AddImpulse(unsigned int const &,class Vector const &,class Vector const &);
		IMPORT  int Create(unsigned int &,struct ShipInfo const &);
		IMPORT  int CreateLoot(unsigned int &,struct LootInfo const &);
		IMPORT  int CreateSolar(unsigned int &,struct SolarInfo const &);
		IMPORT  int Destroy(unsigned int,enum DestroyType);
		IMPORT  int Dock(unsigned int const &,unsigned int const &,int,enum DOCK_HOST_RESPONSE);
		IMPORT  int DockRequest(unsigned int const &,unsigned int const &);
		IMPORT  int DrainShields(unsigned int);
		IMPORT  int EnumerateCargo(unsigned int const &,struct pub::CargoEnumerator &);
		IMPORT  int ExistsAndAlive(unsigned int);
		IMPORT  int FormationResponse(unsigned int const &,enum FORMATION_RTYPE);
		IMPORT  int GetArchetypeID(unsigned int const &,unsigned int &);
		IMPORT  int GetAtmosphereRange(unsigned int const &,float &);
		IMPORT  int GetBurnRadius(unsigned int const &,float &,class Vector &);
		IMPORT  int GetCargoSpaceOccupied(unsigned int const &,unsigned int &);
		IMPORT  int GetCenterOfMass(unsigned int const &,class Vector &);
		IMPORT  int GetDockingTarget(unsigned int const &,unsigned int &);
		IMPORT  int GetEmptyPos(unsigned int const &,class Transform const &,float const &,float const &,enum PosSelectionType const &,class Vector &);
		IMPORT  int GetGoodID(unsigned int const &,unsigned int &);
		IMPORT  int GetHardpoint(unsigned int const &,char const *,class Vector *,class Matrix *);
		IMPORT  int GetHealth(unsigned int const &iSpaceObj,float &fCurrentHealth,float &fMaxHealth);
		IMPORT  int GetInvincible(unsigned int,bool &,bool &,float &);
		IMPORT  int GetJumpTarget(unsigned int const &,unsigned int &,unsigned int &);
		IMPORT  int GetLocation(unsigned int,class Vector &,class Matrix &);
		IMPORT  int GetMass(unsigned int const &,float &);
		IMPORT  int GetMotion(unsigned int,class Vector &,class Vector &);
		IMPORT  int GetRadius(unsigned int const &,float &,class Vector &);
		IMPORT  int GetRelativeHealth(unsigned int const &,float &);
		IMPORT  int GetRep(unsigned int,int &);
		IMPORT  int GetScannerRange(unsigned int,int &,int &);
		IMPORT  int GetShieldHealth(unsigned int const &iSpaceObj,float &fCurrentShields,float &fMaxShields,bool &bShieldsUp);
		IMPORT  int GetSolarArchetypeID(unsigned int,unsigned int &);
		IMPORT  int GetSolarArchetypeNickname(char *,int,unsigned int);
		IMPORT  int GetSolarParent(unsigned int const &,unsigned int &);
		IMPORT  int GetSolarRep(unsigned int,int &);
		IMPORT  int GetSystem(unsigned int,unsigned int &);
		IMPORT  int GetTarget(unsigned int const &,unsigned int &);
		IMPORT  int GetTerminalInfo(unsigned int const &,int,struct TerminalInfo &);
		IMPORT  int GetTradelaneNextAndPrev(unsigned int const &,unsigned int &,unsigned int &);
		IMPORT  int GetType(unsigned int,unsigned int &);
		IMPORT  int GetVoiceID(unsigned int const &,unsigned int &);
		IMPORT  int InstantDock(unsigned int const &,unsigned int const &,int);
		IMPORT  int IsPosEmpty(unsigned int const &,class Vector const &,float const &,bool &);
		IMPORT  int JettisonEquipment(unsigned int const &,unsigned short const &,int const &);
		IMPORT  int JumpIn(unsigned int const &,unsigned int const &);
		IMPORT  int LaneResponse(unsigned int const &,int);
		IMPORT  int Launch(unsigned int const &,unsigned int const &,int);
		IMPORT  int LightFuse(unsigned int const &,char const *,float);
		IMPORT  int Relocate(unsigned int const &,unsigned int const &,class Vector const &,class Matrix const &);
		IMPORT  int RequestSpaceScript(unsigned int const &,class Vector const &,int const &,unsigned int,char const *);
		IMPORT  int SendComm(unsigned int,unsigned int,unsigned int,struct Costume const *,unsigned int,unsigned int *,int,unsigned int,float,bool);
		IMPORT  int SetInvincible2(unsigned int,bool,bool,float);
		IMPORT  int SetInvincible(unsigned int,bool,bool,float);
		IMPORT  int SetRelativeHealth(unsigned int const &,float);
	};

	namespace System
	{
		struct SysObj
		{
			char   nick[32];		// NOT NUL-terminated if longer
			Vector pos;
			UINT   archid;
			UINT   ids_name;
			UINT   ids_info;
			char   reputation[32];
			UINT   dock_with;
			UINT   goto_system;
			UINT   system;
			// -------------------
			// Some nicknames are longer than 32 characters, so take advantage of the
			// fact that where it gets the nickname from immediately follows.
			size_t len;		// TString<64>
			char   nickname[64];
		};
	
		struct SysObjEnumerator
		{
			virtual bool operator()( const SysObj& ) = 0;
		};
		
		struct Connection
		{
			UINT   stuff[10];
		};
		
		struct ConnectionEnumerator
		{
			virtual bool operator()( const Connection& ) = 0;
		};
	
		IMPORT  int EnumerateConnections(unsigned int const &,struct pub::System::ConnectionEnumerator &,enum ConnectionType);
		IMPORT  int EnumerateObjects(unsigned int const &,struct SysObjEnumerator &);
		IMPORT  int EnumerateZones(unsigned int const &,struct ZoneEnumerator &);
		IMPORT  int Find(unsigned int const &,char const *,unsigned int &);
		IMPORT  int GetName(unsigned int,unsigned int &);
		IMPORT  int GetNestedProperties(unsigned int const &,class Vector const &,unsigned long &);
		IMPORT  int InZones(unsigned int,class Transform const &,float,float,float,unsigned int * const,unsigned int,unsigned int &);
		IMPORT  int InZones(unsigned int,class Vector const &,float,unsigned int * const,unsigned int,unsigned int &);
		IMPORT  int LoadSystem(unsigned int const &);
		IMPORT  int ScanObjects(unsigned int const &,unsigned int * const,unsigned int,class Vector const &,float,unsigned int,unsigned int &);
	};

	namespace Zone
	{
		IMPORT  float ClassifyPoint(unsigned int,class Vector const &);
		IMPORT  float GetDistance(unsigned int,class Vector const &);
		IMPORT  unsigned int GetId(unsigned int,char const *);
		IMPORT  int GetLootableInfo(unsigned int,struct ID_String &,struct ID_String &,int &,int &,int &);
		IMPORT  int GetName(unsigned int,unsigned int &);
		IMPORT  int GetOrientation(unsigned int const &,class Matrix &);
		//IMPORT  int GetPopulation(unsigned int,class weighted_vector<unsigned int> const * &);
		IMPORT  class Vector  GetPos(unsigned int);
		IMPORT  int GetProperties(unsigned int,unsigned long &);
		IMPORT  float GetRadius(unsigned int);
		IMPORT  int GetShape(unsigned int,enum ZoneShape &);
		IMPORT  int GetSize(unsigned int,class Vector &);
		IMPORT  unsigned int GetSystem(unsigned int);
		IMPORT  bool InZone(unsigned int,class Vector const &,float);
		IMPORT  bool Intersect(unsigned int,class Vector const &,class Vector const &,class Vector &);
		IMPORT  bool VerifyId(unsigned int);
	};

};

IMPORT  void (* g_pPrivateChatHook)(unsigned short *,int);
IMPORT  void (* g_pSystemChatHook)(unsigned short *,int);
IMPORT  void (* g_pUniverseChatHook)(unsigned short *,int);

IMPORT  PlayerDB  Players;
extern "C" IMPORT IServerImpl Server;

#endif // _FLCORESERVER_H_
