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

#include "Common.hpp"
#include "Server.hpp"

#pragma warning(disable : 5030)
#pragma comment(lib, "FLCoreServer.lib")

enum class MissionMessageType
{
    Failure,
    Type1, // Dialogue Box
    Type2, // Objective Text
    Success
};

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

enum class ResponseCode
{
    Success = 0,
    Failure = -2,
    InvalidInput = -4
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
        uint userShipId;
        ushort itemId;
        ushort amountUsed;
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
        st6::vector<ushort> hpIds;
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
        ushort subObjId;
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
        ushort slot;
        ushort _padding;
        ushort count;
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

struct RequestBestPathStruct
{
        uint clientId;
        uint dunno0;
        uint dunno1;
        Vector startPos;
        uint dunno2;
        uint startSystem;
        Vector endPos;
        uint dunno3;
        uint endSystem;
};

class IMPORT CAccount
{
    public:
        CAccount(const CAccount&);
        CAccount();
        virtual ~CAccount();
        CAccount& operator=(const CAccount&);
        void AppendCharacterNames(st6::list<st6::wstring&>&);
        void DeleteCharacterFromID(st6::string&);
        void ForceLogout();
        void InitFromFolder(const char*);

    public:
        uint dunno1;
        wchar_t* accId;
        uint dunno2[7];
        CAccountListNode* firstListNode;
        uint numberOfCharacters;
        uint dunno4[32];
};

enum CommResult
{
};

#pragma warning(push)
#pragma warning(disable : 5222)
struct IMPORT [[Hook, ServerCall]] IServerImpl
{
        IServerImpl(const IServerImpl&);
        IServerImpl();
        IServerImpl& operator=(const IServerImpl&);

        // N.B. Do not modify order, vtable ordering is fixed by Server.dll
        [[DisconnectCheck]]
        virtual void FireWeapon(uint client, const XFireWeaponInfo& fwi);
        [[CallInner, DisconnectCheck]]
        virtual void ActivateEquip(uint client, const XActivateEquip& aq);
        [[CallInner, DisconnectCheck]]
        virtual void ActivateCruise(uint client, const XActivateCruise& ac);
        [[CallInner, DisconnectCheck]]
        virtual void ActivateThrusters(uint client, const XActivateThrusters& at);
        virtual void SetTarget(uint client, const XSetTarget& st);
        virtual void TractorObjects(uint client, const XTractorObjects& to);
        [[CallInner, CallCatch]]
        virtual void GoTradelane(uint client, const XGoTradelane& gt);
        [[CallInner]]
        virtual void StopTradelane(uint client, uint shipID, uint tradelaneRing1, uint tradelaneRing2);
        virtual void JettisonCargo(uint client, const XJettisonCargo& jc);
        [[CallInner, CallInnerAfter]]
        virtual bool Startup(const SStartupInfo& si);
        [[CallInnerAfter, NoPluginsAfter]]
        virtual void Shutdown();
        [[CallInner, NoLog]]
        virtual int Update();
        [[NoHook]]
        virtual void ElapseTime(float);
        [[NoHook]]
        virtual void __nullopt1();
        [[NoHook]] virtual bool SwapConnections(EFLConnection, EFLConnection);
        [[NoHook]]
        virtual void __nullopt2();
        [[CallInner]]
        virtual void DisConnect(uint client, EFLConnection conn);
        [[DisconnectCheck, CallInner(true), CallInnerAfter]]
        virtual void OnConnect(uint client);
        [[CallInnerAfter]]
        virtual void Login(const SLoginInfo& li, uint client);
        [[DisconnectCheck, CallInner(true), CallCatch]]
        virtual void CharacterInfoReq(uint client, bool);
        [[DisconnectCheck, CallInner(true), CallInnerAfter]]
        virtual void CharacterSelect(const CHARACTER_ID& cid, uint client);
        [[NoHook]]
        virtual void __nullopt3();
        virtual void CreateNewCharacter(const SCreateCharacterInfo&, uint client);
        virtual void DestroyCharacter(CHARACTER_ID const&, uint client);
        [[NoHook]] virtual void CharacterSkipAutosave(uint);
        virtual void ReqShipArch(uint archID, uint client);
        virtual void ReqHullStatus(float status, uint client);
        virtual void ReqCollisionGroups(const st6::list<CollisionGroupDesc>& collisionGroups, uint client);
        virtual void ReqEquipment(const EquipDescList& edl, uint client);
        [[NoHook]]
        virtual void ReqCargo(const EquipDescList&, uint);
        virtual void ReqAddItem(uint goodID, const char* hardpoint, int count, float status, bool mounted, uint client);
        virtual void ReqRemoveItem(ushort slotID, int count, uint client);
        virtual void ReqModifyItem(ushort slotID, const char* hardpoint, int count, float status, bool mounted, uint client);
        virtual void ReqSetCash(int cash, uint client);
        virtual void ReqChangeCash(int cashAdd, uint client);
        [[DisconnectCheck, CallInner, CallInnerAfter]]
        virtual void BaseEnter(uint baseID, uint client);
        [[DisconnectCheck, CallInner, CallInnerAfter]]
        virtual void BaseExit(uint baseID, uint client);
        virtual void LocationEnter(uint locationID, uint client);
        virtual void LocationExit(uint locationID, uint client);
        virtual void BaseInfoRequest(unsigned int, unsigned int, bool);
        virtual void LocationInfoRequest(unsigned int, unsigned int, bool);
        virtual void GFObjSelect(unsigned int, unsigned int);
        virtual void GFGoodVaporized(const SGFGoodVaporizedInfo& gvi, uint client);
        virtual void MissionResponse(unsigned int, unsigned long, bool, uint client);
        virtual void TradeResponse(const unsigned char*, int, uint client);
        virtual void GFGoodBuy(const SGFGoodBuyInfo&, uint client);
        [[CallInner(true), DisconnectCheck]]
        virtual void GFGoodSell(const SGFGoodSellInfo&, uint client);
        [[CallInnerAfter]]
        virtual void SystemSwitchOutComplete(uint shipID, uint client);
        [[CallInner, CallInnerAfter, DisconnectCheck]]
        virtual void PlayerLaunch(uint shipID, uint client);
        [[CallInner]]
        virtual void LaunchComplete(uint baseID, uint shipID);
        [[CallInnerAfter]]
        virtual void JumpInComplete(uint systemID, uint shipID);
        virtual void Hail(unsigned int, unsigned int, unsigned int);
        [[CallInner(true), NoLog, DisconnectCheck]]
        virtual void SPObjUpdate(const SSPObjUpdateInfo& ui, uint client);
        [[CallInner, DisconnectCheck]]
        virtual void SPMunitionCollision(const SSPMunitionCollisionInfo& mci, uint client);
        [[NoHook]]
        virtual void SPBadLandsObjCollision(const SSPBadLandsObjCollisionInfo&, uint);
        [[DisconnectCheck]]
        virtual void SPObjCollision(const SSPObjCollisionInfo& oci, uint client);
        virtual void SPRequestUseItem(const SSPUseItem& ui, uint client);
        virtual void SPRequestInvincibility(uint shipID, bool enable, InvincibilityReason reason, uint client);
        [[NoHook]]
        virtual void SaveGame(const CHARACTER_ID&, const ushort*, uint);
        [[NoHook]] virtual void MissionSaveB(uint, ulong);
        // eventType: 0 = docking, 1 = formation
        virtual void RequestEvent(int eventType, uint shipID, uint dockTarget, uint, ulong, uint client);
        // eventType: 0 = docking, 1 = formation
        virtual void RequestCancel(int eventType, uint shipID, uint, ulong, uint client);
        virtual void MineAsteroid(uint systemID, const Vector& pos, uint crateID, uint lootID, uint count, uint client);
        [[NoHook]] virtual void CommComplete(uint, uint, uint, CommResult);
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
        [[NoHook]]
        virtual void SetMissionLog(uint, uchar*, int);
        virtual void SetInterfaceState(uint client, uchar*, int);
        virtual void RequestRankLevel(uint client, uchar*, int);
        [[CallInner]]
        virtual void InitiateTrade(uint client1, uint client2);
        [[CallInnerAfter, DisconnectCheck]]
        virtual void TerminateTrade(uint client, int accepted);
        virtual void AcceptTrade(uint client, bool);
        virtual void SetTradeMoney(uint client, ulong);
        virtual void AddTradeEquip(uint client, const EquipDesc& ed);
        virtual void DelTradeEquip(uint client, const EquipDesc& ed);
        virtual void RequestTrade(uint, uint);
        virtual void StopTradeRequest(uint client);
        [[NoHook]]
        virtual void ReqDifficultyScale(float, uint);
        [[NoHook]]
        virtual unsigned int GetServerID();
        [[NoHook]]
        virtual const char* GetServerSig();
        [[NoHook]]
        virtual void DumpPacketStats(const char*);
        [[Disable]]
        virtual void Dock(const uint&, const uint&);

        [[CallInner(true), Semaphore(g_InSubmitChat), Address(-0x08)]]
        virtual void SubmitChat(CHAT_ID cidFrom, ulong size, const void* rdlReader, CHAT_ID cidTo, int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};
#pragma warning(pop)

struct CHARACTER_ID final
{
        CHARACTER_ID();
        CHARACTER_ID const& operator=(CHARACTER_ID const&);
        void invalidate();
        bool is_valid() const;

        char charFilename[512]; // Only first 16 bytes are ever used
};

struct VisitEntry
{
        uint visitValue;
};

template <>
inline void BinarySearchTree<VisitEntry>::Insert(uint key, VisitEntry value)
{
    static DWORD server = DWORD(GetModuleHandleA("server.dll"));
    using sub_6D5C600Type = int(__thiscall*)(BinarySearchTree * ptr, uint * u, uint * state);
    static auto sub_6D5C600 = sub_6D5C600Type(server + 0x7C600);

    uint v166[6];
    uint input[2] = { key, value.visitValue };
    sub_6D5C600(this, v166, input);
}

struct CharacterBaseDataInfo
{
    CharacterBaseDataInfo* left; //0x0
    CharacterBaseDataInfo* root; //0x4
    CharacterBaseDataInfo* right; //0x8
    char filename[0x40]; //0xC
    uint dunno[0x107]; //0x4C
    float baseHealth; // 0x468
    st6::list<EquipDesc> baseEquipList; //0x46C
    st6::list<CollisionGroupDesc> baseColgrps; //0x478
};

struct PlayerData
{
        wchar_t accId[40]; // 0
        void* chararacterCreationPtr; // 0x50
        CharacterBaseDataInfo* accountCharacterDataBegin; // 0x54
        void* accountCharacterDataEnd; // 0x58
        long x05C;
        uint numberOfCharacters; // 0x60
        CHARACTER_ID charFile; // 0x64
        uint shipArchetype; // 0x264
        float relativeHealth; // 0x268
        st6::list<CollisionGroupDesc> collisionGroupDesc; // 0x26C
        EquipDescList equipAndCargo;                      // 0x278
        int rank;                                         // 0x284
        int moneyNeededToNextRank;                        // 0x288
        Costume commCostume;                              // 0x28C
        uint voiceLen;                                    // 0x2C0
        char voice[32];                                   // 0x2C4
        Costume baseCostume;                              // 0x2E4
        uint reputation;                                  // 0x318
        int money;                                        // 0x31C
        int worth;                                        // 0x320
        uint shipArchetypeWhenLanding;                    // 0x324
        // Potentially something related to anti-cheat checking
        EquipDescList shadowEquipDescList;                 // 0x328
        int numKills;                                      // 0x334
        int numMissionSuccesses;                           // 0x338
        int numMissionFailures;                            // 0x33C
        bool skipAutoSave;                                 // 0x340
        uint saveCount;                                    // 0x344
        uint onlineId;                                     // 0x348
        bool cheated;                                      // 0x34C
        Vector position;                                   // 0x350
        Matrix orientation;                                // 0x35C
        st6::string weaponGroups;                          // 0x380
        uint dunno1[2];                                    // 0x390
        int* SPNeuralNetLogUnk;                            // 0x398
        int interfaceState;                                // 0x39C
        BinarySearchTree<VisitEntry> visitEntries;         // 0x3A0
        uint dunno2[4];                                    // 0x3B4
        float difficulty;                                  // 0x3C4
        ushort lastEquipId;                                // 0x3C8
        uint menuItem;                                     // 0x3CC
        uint onlineId2;                                    // 0x3D0
        uint dunno3[2];                                    // 0x3D4
        uint tradeRequestCount;                            // 0x3DC
        uint systemId;                                     // 0x3E0
        uint shipId;                                       // 0x3E4
        uint createdShipId;                                // 0x3E8
        uint baseId;                                       // 0x3EC
        uint lastBaseId;                                   // 0x3F0
        uint enteredBase;                                  // 0x3F4
        uint baseRoomId;                                   // 0x3F8
        uint characterId;                                  // 0x3FC
        CAccount* account;                                 // 0x400
        CPlayerGroup* playerGroup;                         // 0x404
        uint missionId;                                    // 0x408
        uint missionSetBy;                                 // 0x40C
        uint exitedBase;                                   // 0x410
        uint unknownLocId;                                 // 0x414
        uint unknown[20];                                  // 0x418
        float baseHullStatus;                              // 0x468
        EquipDescList baseEquipAndCargo;                   // 0x46C
        st6::list<CollisionGroupDesc> baseCollisionGroups; // 0x478
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
        PlayerDB(const PlayerDB&);
        PlayerDB();
        ~PlayerDB();
        PlayerDB& operator=(const PlayerDB&);
        PlayerData& operator[](const unsigned int&);
        bool BanAccount(st6::wstring&, bool);
        void BuildLocalUserDir();
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
        const unsigned short* GetActiveCharacterName(unsigned int) const;
        bool GetCharactersForAccount(st6::wstring&, st6::list<st6::wstring>&);
        unsigned int GetGroupID(unsigned int);
        st6::wstring& GetMOTD();
        unsigned int GetMaxPlayerCount();
        unsigned int GetServerID();
        const char* GetServerSig();
        void LockAccountAccess(st6::wstring&);
        bool MakeLocalUserPath(char*, const char*);
        void ReadCharacterName(const char*, st6::wstring&);
        void SendGroupID(unsigned int, unsigned int);
        void SendSystemID(unsigned int, unsigned int);
        bool SetAccountAdminRights(st6::wstring&, bool);
        bool SetAccountPassword(st6::wstring&, st6::wstring&);
        void SetMOTD(st6::wstring&);
        void UnlockAccountAccess(st6::wstring&);
        void cleanup(unsigned int);
        bool create_new_character(const SCreateCharacterInfo&, unsigned int);
        bool create_restart_file(const char*);
        void free();
        void init(unsigned int, bool);
        bool is_valid(const unsigned int&);
        bool is_valid_ship_owner(const unsigned int&, const unsigned int&);
        unsigned char login(const SLoginInfo&, unsigned int);
        void logout(unsigned int);
        void logout_all();
        PlayerData* traverse_active(PlayerData*) const;

    private:
        int create_account(const SLoginInfo&);
        unsigned char load_user_data(const SLoginInfo&, unsigned int);
        unsigned int to_index(unsigned int);

    public:
        char* data;
        uint dunno1[12];
        PlayerDbTreeNode* firstNode;
        PlayerDbTreeNode* lastNode;
        uint dunno2;
        uint numAccounts;
};
;

namespace SrvAsteroid
{
    class IMPORT SrvAsteroidSystem
    {
        public:
            SrvAsteroidSystem(const SrvAsteroidSystem&);
            SrvAsteroidSystem();
            ~SrvAsteroidSystem();
            SrvAsteroidSystem& operator=(const SrvAsteroidSystem&);
            int AddRef();
            int Release();
            void load(const char*);
            void map_asteroid_fields();
            void set_cmn_system(CmnAsteroid::CAsteroidSystem*);
            void set_sys_id(unsigned int);
            void update();

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    class MedAsteroid : public GameObject
    {
            virtual void sub_6CEF1C0();
            virtual void sub_6CEE630();
            virtual void sub_6CEE670();
            virtual void sub_6CEE6D0();
            virtual void sub_6D02CB0();
            virtual void sub_6D04C30();
            virtual void sub_6CEE9E0();
            virtual void sub_6CEE6E0();
            virtual void sub_6CEE810();
            virtual void sub_6CEE980();
            virtual void noImpl1(uint dummy1, uint dummy2);
            virtual void noImpl2(uint dummy1, uint dummy2);
            virtual void noImpl3(uint dummy1, uint dummy2);
            virtual void noImpl4(uint dummy);
            virtual void sub_6CE6190();
            virtual void sub_6CEEFA0();
            virtual void sub_6CEF0F0();
            virtual void sub_6CE61A0();
            virtual void sub_6CE61B0();
            virtual void sub_6CE61C0();
            virtual void sub_6CEE9F0();
            virtual void sub_6CEEE20();
            virtual void sub_6CEF1E0();
            virtual void sub_6CEEC90();
            virtual void sub_6CEEF70();
            virtual void sub_6CEF0B0();

            // TODO: Fields
    };

    class MedMine : public GameObject
    {
            virtual void sub_6CEF1C0();
            virtual void sub_6CEE630();
            virtual void sub_6CEE670();
            virtual void sub_6CEE6D0();
            virtual void sub_6D02CB0();
            virtual void sub_6D04C30();
            virtual void sub_6CEE9E0();
            virtual void sub_6CEE6E0();
            virtual void sub_6CEE810();
            virtual void sub_6CEE980();
            virtual void noImpl1(uint dummy1, uint dummy2);
            virtual void noImpl2(uint dummy1, uint dummy2);
            virtual void noImpl3(uint dummy1, uint dummy2);
            virtual void sub_6CEEE70();
            virtual void sub_6CE6190();
            virtual void sub_6CEEFA0();
            virtual void sub_6CEF0F0();
            virtual void sub_6CE61A0();
            virtual void sub_6CE61B0();
            virtual void sub_6CE61C0();
            virtual void sub_6CEE9F0();
            virtual void sub_6CEEE20();
            virtual void sub_6CEF1E0();
            virtual void sub_6CEEC90();
            virtual void sub_6CEEF70();
            virtual void sub_6CEF0B0();
            virtual void noImpl4(uint dummy1, uint dummy2);

            // TODO: Fields
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

template <class T>
class IMPORT OwnerList
{
    public:
        OwnerList();
        virtual ~OwnerList();
        OwnerList& operator=(const OwnerList&);
        void free();

    protected:
        unsigned char data[16];
};

namespace pub
{
    struct CargoEnumerator;

    IMPORT int BuildBaseReader(INI_Reader&, const unsigned int&);
    IMPORT int BuildSystemReader(INI_Reader&, const unsigned int&);
    IMPORT HINSTANCE__* DLL_LoadLibrary(const char*);
    IMPORT void DebugPrint(const char*, int);
    IMPORT int FindHardpoint(const char*, unsigned int, Vector&, Matrix&);
    IMPORT int GetBaseID(unsigned int&, const char*);
    IMPORT unsigned int GetBaseNickname(char*, unsigned int, const unsigned int&);
    IMPORT int GetBaseStridName(unsigned int&, const unsigned int&);
    IMPORT int GetBases(const unsigned int&, unsigned int* const, unsigned int, unsigned int&);
    IMPORT int GetCargoHoldSize(const unsigned int&, unsigned int&);
    IMPORT int GetCostumeID(int&, const char*);
    IMPORT IFileSystem* GetDataPath();
    IMPORT int GetEquipmentID(unsigned int&, const char*);
    IMPORT int GetFullHealth(const unsigned int&, unsigned int&);
    IMPORT int GetGoodID(unsigned int&, const char*);
    IMPORT int GetGoodProperties(const unsigned int&, float&, float&);
    IMPORT int GetLoadout(EquipDescVector&, const unsigned int&);
    IMPORT int GetLoadoutID(unsigned int&, const char*);
    IMPORT int GetLoadoutName(const unsigned int&, char*, int);
    IMPORT unsigned int GetLocationNickname(char*, unsigned int, const unsigned int&);
    IMPORT int GetLocations(const unsigned int&, unsigned int* const, unsigned int, unsigned int&);
    IMPORT int GetMaxHitPoints(const unsigned int&, int&);
    IMPORT int GetNavMapScale(unsigned int, float&);
    IMPORT unsigned int GetNicknameId(const char*);
    IMPORT int GetRwTime(double&);
    IMPORT int GetShipArchSTRID(const unsigned int&, unsigned int&);
    IMPORT int GetShipID(unsigned int&, const char*);
    IMPORT int GetSolarType(const unsigned int&, unsigned int&);
    IMPORT int GetSystem(unsigned int&, const unsigned int&);
    IMPORT int GetSystemGateConnection(const unsigned int&, unsigned int&);
    IMPORT int GetSystemID(unsigned int&, const char*);
    IMPORT unsigned int GetSystemNickname(char*, unsigned int, const unsigned int&);
    IMPORT int GetTime(double&);
    IMPORT int GetType(const unsigned int&, unsigned int&);
    IMPORT int GetVoiceID(unsigned int&, const char*);
    IMPORT int IsCommodity(const unsigned int&, bool&);
    IMPORT unsigned short MakeId(const char*);
    IMPORT bool NextBaseID(unsigned int&);
    IMPORT bool NextSystemID(unsigned int&);
    IMPORT int ReportFreeTerminal(unsigned int, int);
    IMPORT int Save(unsigned int, unsigned int);
    // IMPORT int SetTimer(unsigned int const&, Controller::TimerExpired const&, float);
    IMPORT bool SinglePlayer();
    IMPORT int TranslateArchToGood(const unsigned int&, unsigned int&);
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
        IMPORT enum FORMATION_RTYPE update_formation_state(unsigned int, unsigned int, const Vector&);
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
        IMPORT int SetMusic(unsigned int, const Tryptich&);
    }; // namespace Audio

    namespace GF
    {
        enum MVEmptyReason
        {
        };
        IMPORT unsigned long AmbientScriptCreate(const struct AmbientScriptDescription&);
        IMPORT void AmbientScriptDestroy(unsigned long*);
        IMPORT unsigned long CharacterBehaviorCreate(const struct CharacterBehaviorDescription&);
        IMPORT void CharacterBehaviorDestroy(unsigned long*);
        IMPORT unsigned int CharacterCreate(const struct CharacterDescription&);
        IMPORT void CharacterDestroy(unsigned int*);
        IMPORT void CharacterSetBehavior(unsigned int, unsigned long);
        IMPORT void EnumerateCharacterPlacementIni(unsigned int, void (*)(int, INI_Reader*, void*), void*);
        IMPORT unsigned int FindBase(const char*);
        IMPORT unsigned int FindLocation(unsigned int, const char*);
        IMPORT const char* FormCharacterPlacementName(const SetpointProperties*);
        IMPORT int GetAccessory(const char*);
        IMPORT int GetBasePosition(const unsigned int&, const unsigned int&, Vector&);
        IMPORT int GetBodyPart(const char*, int);
        IMPORT unsigned int GetCharacterOnPlacement(unsigned int, unsigned int, int);
        IMPORT int GetCharacterPlacementByName(unsigned int, const char*, int&);
        IMPORT const char* GetCharacterPlacementName(unsigned int, int);
        IMPORT unsigned long GetCharacterPlacementOccupancy(unsigned int, int);
        IMPORT int GetCharacterPlacementPosture(unsigned int, int, unsigned long&);
        IMPORT bool GetCharacterPlacementProperties(unsigned int, int, SetpointProperties*);
        IMPORT void GetCostumeByID(int, Costume&);
        IMPORT int GetCostumeSkeletonGender(const Costume&, int&);
        IMPORT int GetMissionVendorOfferCount(unsigned int, unsigned int);
        IMPORT int GetNumCharacterPlacements(unsigned int);
        IMPORT float GetRtcPerformanceSlider();
        IMPORT unsigned int GetSpaceflightLocation();
        IMPORT bool IsCharacterPlacementNormal(unsigned int, int);
        IMPORT bool IsCharacterPlacementSpecial(unsigned int, int);
        IMPORT void MissionVendorAcceptance(unsigned long, bool, const FmtStr&, unsigned int);
        IMPORT unsigned long MissionVendorOfferCreate(const struct MissionVendorOfferDescription&);
        IMPORT void MissionVendorOfferDestroy(unsigned long*);
        IMPORT unsigned long NewsBroadcastCreate(const struct NewsBroadcastDescription&);
        IMPORT void NewsBroadcastDestroy(unsigned long*);
        IMPORT int ReportWhyMissionVendorEmpty(unsigned int, MVEmptyReason);
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
        IMPORT int Attach(const unsigned int&, void*);
        IMPORT int Create(unsigned int, const Vector&, const Vector&, const Matrix&, unsigned int, void*&);
        IMPORT int Create(unsigned int, float, const Vector&, unsigned int, void*&);
        IMPORT int Destroy(void*);
        IMPORT int Detach(void*);
        IMPORT int SetActive(void*, bool);
    }; // namespace Phantom

    namespace Player
    {
        IMPORT int AddCargo(const unsigned int&, const unsigned int&, unsigned int, float, bool);
        IMPORT int AdjustCash(const unsigned int&, int);
        IMPORT int CfgInterfaceNotification(unsigned int, unsigned int, bool, int);
        IMPORT int DisplayMissionMessage(const unsigned int&, const FmtStr&, MissionMessageType, bool);
        IMPORT int EnumerateCargo(const unsigned int&, pub::CargoEnumerator&);
        IMPORT int ForceLand(unsigned int, unsigned int);
        IMPORT int GetAssetValue(const unsigned int&, float&);
        IMPORT int GetBase(const unsigned int&, unsigned int&);
        IMPORT int GetBody(const unsigned int&, unsigned int&);
        IMPORT int GetCharacter(const unsigned int&, unsigned int&);
        IMPORT int GetGender(const unsigned int&, int&);
        IMPORT int GetGroupMembers(unsigned int, st6::vector<unsigned int>&);
        IMPORT int GetGroupSize(unsigned int, unsigned int&);
        IMPORT int GetLocation(const unsigned int&, unsigned int&);
        IMPORT int GetMoneyNeededToNextRank(const unsigned int&, int&);
        IMPORT int GetMsnID(unsigned int, unsigned int&);
        IMPORT int GetName(unsigned int, st6::wstring&);
        IMPORT int GetNumKills(const unsigned int&, int&);
        IMPORT int GetNumMissionFailures(const unsigned int&, int&);
        IMPORT int GetNumMissionSuccesses(const unsigned int&, int&);
        IMPORT int GetRank(const unsigned int&, int&);
        IMPORT int GetRelativeHealth(const unsigned int&, float&);
        IMPORT int GetRemainingHoldSize(const unsigned int&, float&);
        IMPORT int GetRep(const unsigned int&, int&);
        IMPORT int GetShip(const unsigned int&, unsigned int&);
        IMPORT int GetShipID(const unsigned int&, unsigned int&);
        IMPORT int GetSystem(const unsigned int&, unsigned int&);
        IMPORT int InspectCash(const unsigned int&, int&);
        IMPORT int IsGroupMember(unsigned int, unsigned int, bool&);
        IMPORT int LoadHint(unsigned int, BaseHint*);
        IMPORT int MarkObj(unsigned int, unsigned int, int);
        IMPORT int PopUpDialog(unsigned int, const FmtStr&, const FmtStr&, unsigned int);
        IMPORT int RemoveCargo(const unsigned int&, unsigned short, unsigned int);
        IMPORT int RemoveFromGroup(unsigned int);
        IMPORT int ReplaceMissionObjective(const unsigned int&, const unsigned int&, unsigned int, const struct MissionObjective&);
        IMPORT int ReturnBestPath(unsigned int, unsigned char*, int);
        IMPORT int ReturnPlayerStats(unsigned int, unsigned char*, int);
        IMPORT int RevertCamera(unsigned int);
        IMPORT int RewardGroup(unsigned int, int);
        IMPORT int SendNNMessage(unsigned int, unsigned int);
        IMPORT int SetCamera(unsigned int, const Transform&, float, float);
        IMPORT int SetCostume(const unsigned int&, int);
        IMPORT int SetInitialOrnt(const unsigned int&, const Matrix&);
        IMPORT int SetInitialPos(const unsigned int&, const Vector&);
        IMPORT int SetMissionObjectiveState(const unsigned int&, const unsigned int&, int, unsigned int);
        IMPORT int SetMissionObjectives(const unsigned int&, const unsigned int&, const MissionObjective*, unsigned int, const FmtStr&, unsigned char,
                                        const FmtStr&);
        IMPORT int SetMoneyNeededToNextRank(unsigned int, int);
        IMPORT int SetMonkey(unsigned int);
        IMPORT int SetMsnID(unsigned int, unsigned int, unsigned int, bool, unsigned int);
        IMPORT int SetNumKills(const unsigned int&, int);
        IMPORT int SetNumMissionFailures(const unsigned int&, int);
        IMPORT int SetNumMissionSuccesses(const unsigned int&, int);
        IMPORT int SetRank(unsigned int, int);
        IMPORT int SetRobot(unsigned int);
        IMPORT int SetShipAndLoadout(const unsigned int&, unsigned int, const EquipDescVector&);
        IMPORT int SetStoryCue(const unsigned int&, unsigned int);
        IMPORT int SetTrent(unsigned int);
    }; // namespace Player

    namespace Reputation
    {
        IMPORT int Alloc(int&, const FmtStr&, const FmtStr&);
        IMPORT int EnumerateGroups(struct Enumerator&);
        IMPORT int Free(const int&);
        IMPORT int GetAffiliation(const int&, unsigned int&);
        IMPORT int GetAttitude(const int&, const int&, float&);
        IMPORT int GetGroupFeelingsTowards(const int&, const unsigned int&, float&);
        IMPORT int GetGroupName(const unsigned int&, unsigned int&);
        IMPORT int GetName(const int&, FmtStr&, FmtStr&);
        IMPORT int GetRank(const int&, float&);
        IMPORT int GetReputation(int&, const ID_String&);
        IMPORT int GetReputation(int&, const char*);
        IMPORT int GetReputation(const int&, const unsigned int&, float&);
        IMPORT int GetReputation(const unsigned int&, const unsigned int&, float&);
        IMPORT int GetReputationGroup(unsigned int&, const char*);
        IMPORT int GetShortGroupName(const unsigned int&, unsigned int&);
        IMPORT int SetAffiliation(const int&, const unsigned int&);
        IMPORT int SetAttitude(const int&, const int&, float);
        IMPORT int SetRank(const int&, float);
        IMPORT int SetReputation(const int&, const unsigned int&, float);
        IMPORT int SetReputation(const unsigned int&, const unsigned int&, float);
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

        struct EquipItem
        {
                EquipItem* next;
                uint i2;
                ushort s1;
                ushort id;
                uint goodId;
                CacheString hardpoint;
                bool mounted;
                char unk[3];
                float status;
                uint count;
                bool mission;
        };

        struct ShipInfo
        {
                uint flag = 0;
                uint system = 0;
                uint shipArchetype = 0;
                Vector pos = { 0, 0, 0 };
                Vector unk1 = { 0, 0, 0 }; // all 0
                Vector unk2 = { 0, 0, 0 }; // all 0
                Matrix orientation;
                uint unk3 = 0; // 0
                uint loadout;
                OwnerList<pub::SpaceObj::CargoDesc> cargoDesc;
                uint look1 = 0;
                uint look2 = 0;
                uint unk4 = 0; // 0
                uint unk6 = 0; // 0
                uint comm = 0;
                float unk7 = 0;
                float unk8 = 0;
                float unk9 = 0;
                float unk10 = 0;
                float unk11 = 0;
                float unk12 = 0;
                float unk13 = 0;
                uint unk14 = 0;

                int rep = 0; // increases for each NPC spawned, starts at 0 or 1
                uint pilotVoice = 0;
                uint unk15 = 0;   // 0
                uint health = -1; // -1 = max health
                uint unk16 = 0;   // 0
                uint unk17 = 0;   // 0
                uint level = 1;
        };

        struct SolarInfo
        {
                int flag; // 0x290; ShipInfo has this too, no clue whether actually a flag
                uint archId;
                uint systemId;
                Vector pos;
                Matrix orientation;
                uint loadoutId;
                Costume costume;
                int rep;
                uint voiceId;
                uint dockWith;
                bool missionBool;
                int hitPointsLeft;
                char nickName[64]; // Has to be unique
                uint unk11;        // 0 unused?
                uint mission = 0;  // 1 = flagged as mission solar, 0 = normal
        };

        struct LootInfo
        {
                uint dunno; // "Flag" like the others?
                uint archId;
        };

        struct TerminalInfo
        {
                char hardPoint[0x20];
                DockType type; // 1=berth 4=moor? 7=jump?
        };

        enum class EQUIPMENT_RTYPE
        {
        };
        enum class PosSelectionType
        {
        };

        IMPORT int Activate(const unsigned int&, bool, int);
        IMPORT EQUIPMENT_RTYPE ActivateEquipment(const unsigned int&, struct EQInfo*);
        IMPORT int AddImpulse(const unsigned int&, const Vector&, const Vector&);
        IMPORT int Create(unsigned int&, const ShipInfo&);
        IMPORT int CreateLoot(unsigned int&, const LootInfo&);
        IMPORT int CreateSolar(unsigned int&, const SolarInfo&);
        IMPORT int Destroy(unsigned int, DestroyType);
        IMPORT int Dock(const unsigned int&, const unsigned int&, int, DOCK_HOST_RESPONSE);
        IMPORT int DockRequest(const unsigned int&, const unsigned int&);
        IMPORT int DrainShields(unsigned int);
        IMPORT int EnumerateCargo(const unsigned int&, pub::CargoEnumerator&);
        IMPORT int ExistsAndAlive(unsigned int);
        IMPORT int FormationResponse(const unsigned int&, FORMATION_RTYPE);
        IMPORT int GetArchetypeID(const unsigned int&, unsigned int&);
        IMPORT int GetAtmosphereRange(const unsigned int&, float&);
        IMPORT int GetBurnRadius(const unsigned int&, float&, Vector&);
        IMPORT int GetCargoSpaceOccupied(const unsigned int&, unsigned int&);
        IMPORT int GetCenterOMass(const unsigned int&, Vector&);
        IMPORT int GetDockingTarget(const unsigned int&, unsigned int&);
        IMPORT int GetEmptyPos(const unsigned int&, const Transform&, const float&, const float&, const PosSelectionType&, Vector&);
        IMPORT int GetGoodID(const unsigned int&, unsigned int&);
        IMPORT int GetHardpoint(const unsigned int&, const char*, Vector*, Matrix*);
        IMPORT int GetHealth(const unsigned int& SpaceObj, float& CurrentHealth, float& MaxHealth);
        IMPORT int GetInvincible(unsigned int, bool&, bool&, float&);
        IMPORT int GetJumpTarget(const unsigned int&, unsigned int&, unsigned int&);
        IMPORT int GetLocation(unsigned int, Vector&, Matrix&);
        IMPORT int GetMass(const unsigned int&, float&);
        IMPORT int GetMotion(unsigned int, Vector&, Vector&);
        IMPORT int GetRadius(const unsigned int&, float&, Vector&);
        IMPORT int GetRelativeHealth(const unsigned int&, float&);
        IMPORT int GetRep(unsigned int, int&);
        IMPORT int GetScannerRange(unsigned int, int&, int&);
        IMPORT int GetShieldHealth(const unsigned int& spaceObj, float& currentShields, float& maxShields, bool& shieldsUp);
        IMPORT int GetSolarArchetypeID(unsigned int, unsigned int&);
        IMPORT int GetSolarArchetypeNickname(char*, int, unsigned int);
        IMPORT int GetSolarParent(const unsigned int&, unsigned int&);
        IMPORT int GetSolarRep(unsigned int, int&);
        IMPORT int GetSystem(unsigned int, unsigned int&);
        IMPORT int GetTarget(const unsigned int&, unsigned int&);
        IMPORT int GetTerminalInfo(const unsigned int&, int terminalIndex, TerminalInfo&);
        IMPORT int GetTradelaneNextAndPrev(const unsigned int&, unsigned int&, unsigned int&);
        IMPORT int GetType(unsigned int, unsigned int&);
        IMPORT int GetVoiceID(const unsigned int&, unsigned int&);
        IMPORT int InstantDock(const unsigned int&, const unsigned int&, int);
        IMPORT int IsPosEmpty(const unsigned int&, const Vector&, const float&, bool&);
        IMPORT int JettisonEquipment(const unsigned int&, const unsigned short&, const int&);
        IMPORT int JumpIn(const unsigned int&, const unsigned int&);
        IMPORT int LaneResponse(const unsigned int&, int);
        IMPORT int Launch(const unsigned int&, const unsigned int&, int);
        IMPORT int LightFuse(const unsigned int&, const char*, float);
        IMPORT int Relocate(const unsigned int&, const unsigned int&, const Vector&, const Matrix&);
        IMPORT int RequestSpaceScript(const unsigned int&, const Vector&, const int&, unsigned int, const char*);
        IMPORT int SendComm(unsigned int, unsigned int, unsigned int, const Costume*, unsigned int, unsigned int*, int, unsigned int, float, bool);
        IMPORT int SetInvincible2(unsigned int, bool, bool, float);
        IMPORT int SetInvincible(unsigned int, bool, bool, float);
        IMPORT int SetRelativeHealth(const unsigned int&, float);
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

        IMPORT int EnumerateConnections(const unsigned int&, pub::System::ConnectionEnumerator&, ConnectionType);
        IMPORT int EnumerateObjects(const unsigned int&, SysObjEnumerator&);
        IMPORT int EnumerateZones(const unsigned int&, struct ZoneEnumerator&);
        IMPORT int Find(const unsigned int&, const char*, unsigned int&);
        IMPORT int GetName(unsigned int, unsigned int&);
        IMPORT int GetNestedProperties(const unsigned int&, const Vector&, unsigned long&);
        IMPORT int InZones(unsigned int, const Transform&, float, float, float, unsigned int* const, unsigned int, unsigned int&);
        IMPORT int InZones(unsigned int, const Vector&, float, unsigned int* const, unsigned int, unsigned int&);
        IMPORT int LoadSystem(const unsigned int&);
        IMPORT int ScanObjects(const unsigned int&, unsigned int* const, unsigned int, const Vector&, float, unsigned int, unsigned int&);
    }; // namespace System

    namespace Zone
    {
        enum ZoneShape
        {
        };
        IMPORT float ClassifyPoint(unsigned int, const Vector&);
        IMPORT float GetDistance(unsigned int, const Vector&);
        IMPORT unsigned int GetId(unsigned int, const char*);
        IMPORT int GetLootableInfo(unsigned int, ID_String&, ID_String&, int&, int&, int&);
        IMPORT int GetName(unsigned int, unsigned int&);
        IMPORT int GetOrientation(const unsigned int&, Matrix&);
        // IMPORT  int GetPopulation(unsigned int,class weighted_vector<unsigned int> const * &);
        IMPORT Vector GetPos(unsigned int);
        IMPORT int GetProperties(unsigned int, unsigned long&);
        IMPORT float GetRadius(unsigned int);
        IMPORT int GetShape(unsigned int, ZoneShape&);
        IMPORT int GetSize(unsigned int, Vector&);
        IMPORT unsigned int GetSystem(unsigned int);
        IMPORT bool InZone(unsigned int, const Vector&, float);
        IMPORT bool Intersect(unsigned int, const Vector&, const Vector&, Vector&);
        IMPORT bool VerifyId(unsigned int);
    }; // namespace Zone

    namespace Controller
    {
        struct CreateParms
        {
                void* freeFunc;
                uint client;
        };

        enum PRIORITY
        {
        };

        IMPORT unsigned int Create(const char*, const char*, const CreateParms*, PRIORITY);
        IMPORT void Destroy(unsigned int);
        IMPORT int SetHeartbeatInterval(const unsigned int&, float);
        IMPORT int _SendMessage(const unsigned int&, int, const void*);
    } // namespace Controller

}; // namespace pub

IMPORT void (*g_pPrivateChatHook)(unsigned short*, int);
IMPORT void (*g_pSystemChatHook)(unsigned short*, int);
IMPORT void (*g_pUniverseChatHook)(unsigned short*, int);

IMPORT PlayerDB Players;
extern "C" IMPORT IServerImpl Server;

#endif // _FLCORESERVER_H_
