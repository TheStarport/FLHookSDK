#ifndef _FLCORESERVER_H_
#define _FLCORESERVER_H_

#include "Common.hpp"
#include "Server.hpp"

#pragma warning(disable : 5030)

#pragma warning(push)
#pragma warning(disable : 5222)
struct IMPORT IServerImpl
{
        IServerImpl(const IServerImpl&);
        IServerImpl();
        IServerImpl& operator=(const IServerImpl&);

        // N.B. Do not modify order, vtable ordering is fixed by Server.dll
        virtual void FireWeapon(uint client, const XFireWeaponInfo& fwi);
        virtual void ActivateEquip(uint client, const XActivateEquip& aq);
        virtual void ActivateCruise(uint client, const XActivateCruise& ac);
        virtual void ActivateThrusters(uint client, const XActivateThrusters& at);
        virtual void SetTarget(uint client, const XSetTarget& st);
        virtual void TractorObjects(uint client, const XTractorObjects& to);
        virtual void GoTradelane(uint client, const XGoTradelane& gt);
        virtual void StopTradelane(uint client, uint shipID, uint tradelaneRing1, uint tradelaneRing2);
        virtual void JettisonCargo(uint client, const XJettisonCargo& jc);
        virtual bool Startup(const SStartupInfo& si);
        virtual void Shutdown();
        virtual int Update();
        virtual void ElapseTime(f32);
        virtual void __nullopt1();
        virtual bool SwapConnections(EFLConnection, EFLConnection);
        virtual void __nullopt2();
        virtual void DisConnect(uint client, EFLConnection conn);
        virtual void OnConnect(uint client);
        virtual void Login(const SLoginInfo& li, uint client);
        virtual void CharacterInfoReq(uint client, bool);
        virtual void CharacterSelect(const CHARACTER_ID& cid, uint client);
        virtual void __nullopt3();
        virtual void CreateNewCharacter(const SCreateCharacterInfo&, uint client);
        virtual void DestroyCharacter(CHARACTER_ID const&, uint client);
        virtual void CharacterSkipAutosave(uint);
        virtual void ReqShipArch(uint archID, uint client);
        virtual void ReqHullStatus(f32 status, uint client);
        virtual void ReqCollisionGroups(const st6::list<CollisionGroupDesc>& collisionGroups, uint client);
        virtual void ReqEquipment(const EquipDescList& edl, uint client);
        virtual void ReqCargo(const EquipDescList&, uint);
        virtual void ReqAddItem(uint goodID, const char* hardpoint, int count, f32 status, bool mounted, uint client);
        virtual void ReqRemoveItem(ushort slotID, int count, uint client);
        virtual void ReqModifyItem(ushort slotID, const char* hardpoint, int count, f32 status, bool mounted, uint client);
        virtual void ReqSetCash(int cash, uint client);
        virtual void ReqChangeCash(int cashAdd, uint client);
        virtual void BaseEnter(uint baseID, uint client);
        virtual void BaseExit(uint baseID, uint client);
        virtual void LocationEnter(uint locationID, uint client);
        virtual void LocationExit(uint locationID, uint client);
        virtual void BaseInfoRequest(u32, u32, bool);
        virtual void LocationInfoRequest(u32, u32, bool);
        virtual void GFObjSelect(u32, u32);
        virtual void GFGoodVaporized(const SGFGoodVaporizedInfo& gvi, uint client);
        virtual void MissionResponse(u32, ulong, bool, uint client);
        virtual void TradeResponse(const u8*, int, uint client);
        virtual void GFGoodBuy(const SGFGoodBuyInfo&, uint client);
        virtual void GFGoodSell(const SGFGoodSellInfo&, uint client);
        virtual void SystemSwitchOutComplete(uint shipID, uint client);
        virtual void PlayerLaunch(uint shipID, uint client);
        virtual void LaunchComplete(uint baseID, uint shipID);
        virtual void JumpInComplete(uint systemID, uint shipID);
        virtual void Hail(u32, u32, u32);
        virtual void SPObjUpdate(const SSPObjUpdateInfo& ui, uint client);
        virtual void SPMunitionCollision(const SSPMunitionCollisionInfo& mci, uint client);
        virtual void SPBadLandsObjCollision(const SSPBadLandsObjCollisionInfo&, uint);
        virtual void SPObjCollision(const SSPObjCollisionInfo& oci, uint client);
        virtual void SPRequestUseItem(const SSPUseItem& ui, uint client);
        virtual void SPRequestInvincibility(uint shipID, bool enable, InvincibilityReason reason, uint client);
        virtual void SaveGame(const CHARACTER_ID&, const ushort*, uint);
        virtual void MissionSaveB(uint, ulong);
        // eventType: 0 = docking, 1 = formation
        virtual void RequestEvent(int eventType, uint shipID, uint dockTarget, uint, ulong, uint client);
        // eventType: 0 = docking, 1 = formation
        virtual void RequestCancel(int eventType, uint shipID, uint, ulong, uint client);
        virtual void MineAsteroid(uint systemID, const Vector& pos, uint crateID, uint lootID, uint count, uint client);
        virtual void CommComplete(uint, uint, uint, CommResult);
        virtual void RequestCreateShip(uint client);
        virtual void SPScanCargo(const uint&, const uint&, uint);
        virtual void SetManeuver(uint client, const XSetManeuver& sm);
        virtual void InterfaceItemUsed(uint, uint);
        virtual void AbortMission(uint client, uint);
        virtual void RTCDone(uint, uint);
        virtual void SetWeaponGroup(uint client, uchar*, int);
        virtual void SetVisitedState(uint client, uchar*, int);
        virtual void RequestBestPath(uint client, uchar*, int);
        virtual void RequestPlayerStats(uint client, uchar*, int);
        virtual void PopUpDialog(uint, uint);
        virtual void RequestGroupPositions(uint client, uchar*, int);
        virtual void SetMissionLog(uint, uchar*, int);
        virtual void SetInterfaceState(uint client, uchar*, int);
        virtual void RequestRankLevel(uint client, uchar*, int);
        virtual void InitiateTrade(uint client1, uint client2);
        virtual void TerminateTrade(uint client, int accepted);
        virtual void AcceptTrade(uint client, bool);
        virtual void SetTradeMoney(uint client, ulong);
        virtual void AddTradeEquip(uint client, const EquipDesc& ed);
        virtual void DelTradeEquip(uint client, const EquipDesc& ed);
        virtual void RequestTrade(uint, uint);
        virtual void StopTradeRequest(uint client);
        virtual void ReqDifficultyScale(f32, uint);
        virtual u32 GetServerID();
        virtual const char* GetServerSig();
        virtual void DumpPacketStats(const char*);
        virtual void Dock(const uint&, const uint&);

        virtual void SubmitChat(CHAT_ID cidFrom, ulong size, const void* rdlReader, CHAT_ID cidTo, int);
};

#pragma warning(pop)

struct CharacterData
{
        CHARACTER_ID characterCode;
        st6::wstring name{};                                    // 512
        st6::wstring description{};                             // 528
        uint descripStrId;                                      // 544
        uint datetimeHigh;                                      // 548
        uint datetimeLow;                                       // 552
        Id shipHash;                                            // 556
        int money;                                              // 560
        int numOfKills;                                         // 564
        int numOfSuccessMissions;                               // 568
        int numOfFailedMissions;                                // 572
        f32 hullStatus;                                       // 576
        st6::list<EquipDesc> currentEquipAndCargo{};            // 580
        st6::list<CollisionGroupDesc> currentCollisionGroups{}; // 592
        f32 baseHullStatus;                                   // 604
        st6::list<EquipDesc> baseEquipAndCargo{};               // 608
        st6::list<CollisionGroupDesc> baseCollisionGroups{};    // 620
        Id currentBase;                                         // 632
        Id lastDockedBase;                                      // 636
        Id currentRoom;                                         // 640
        Id system;                                              // 644
        Vector pos;                                             // 648 - 656
        Matrix rot;                                             // 660 - 692
        Id startingRing;                                        // 696
        int rank;                                               // 700
        st6::vector<Reputation::Relation> repList{};            // 704
        Id affiliation;                                         // 720, see Reputation::get_id();
        Costume commCostume{};                                  // 724 - 772
        uint voiceLen;                                          // 776
        char voice[32] = "trent_voice";                         // 780
        Costume baseCostume;                                    // 812 - 860
        SubObjectID::EquipIdMaker equipIdEnumerator;            // 864
        st6::string prefilledWeaponGroupIni{};                  // 876
        st6::list<uint> logInfo{};                              // 888
        int interfaceState = 3;                                 // 896
        st6::map<uint, char> visits{};                          // 900
};

struct PlayerData
{
        wchar_t accId[40];                                  // 0
        st6::map<CHARACTER_ID, CharacterData> characterMap; // 0x50
        CHARACTER_ID charFile;                              // 0x64
        Id shipArchetype;                                   // 0x264
        f32 relativeHealth;                               // 0x268
        st6::list<CollisionGroupDesc> collisionGroupDesc;   // 0x26C
        EquipDescList equipAndCargo;                        // 0x278
        int rank;                                           // 0x284
        int moneyNeededToNextRank;                          // 0x288
        Costume commCostume;                                // 0x28C
        uint voiceLen;                                      // 0x2C0
        char voice[32];                                     // 0x2C4
        Costume baseCostume;                                // 0x2E4
        int reputation;                                     // 0x318
        int money;                                          // 0x31C
        int worth;                                          // 0x320
        Id shipArchetypeWhenLanding;                        // 0x324
        // Potentially something related to anti-cheat checking
        EquipDescList shadowEquipDescList; // 0x328
        int numKills;                      // 0x334
        int numMissionSuccesses;           // 0x338
        int numMissionFailures;            // 0x33C
        bool skipAutoSave;                 // 0x340
        uint saveCount;                    // 0x344
        uint clientId;                     // 0x348
        bool cheated;                      // 0x34C
        Vector position;                   // 0x350
        Matrix orientation;                // 0x35C
        st6::string weaponGroups;          // 0x380
        st6::list<uint> neuralNetLog;      // 0x390
        int interfaceState;                // 0x39C
        st6::map<uint, char> visitEntries; // 0x3A0
        uint dunno2[4];                    // 0x3B4
        f32 difficulty;                  // 0x3C4
        ushort lastEquipId;                // 0x3C8
        CPlayerTradeOffer* tradeOffer;     // 0x3CC
        uint onlineId2;                    // 0x3D0
        uint dunno3[2];                    // 0x3D4
        uint tradeRequestCount;            // 0x3DC
        SystemId systemId;                 // 0x3E0
        uint shipId;                       // 0x3E4
        uint createdShipId;                // 0x3E8
        BaseId baseId;                     // 0x3EC
        BaseId lastBaseId;                 // 0x3F0
        BaseId enteredBase;                // 0x3F4
        Id baseRoomId;                     // 0x3F8
        uint characterId;                  // 0x3FC
        CAccount* account;                 // 0x400
        CPlayerGroup* playerGroup;         // 0x404
        uint missionId;                    // 0x408
        uint missionSetBy;                 // 0x40C
        BaseId exitedBase;                 // 0x410
        uint unknownLocId;                 // 0x414
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
        PlayerData& operator[](const u32&);
        bool BanAccount(st6::wstring&, bool);
        void BuildLocalUserDir();
        u32 CountPlayersInSystem(int);
        bool CreateAccount(st6::wstring&);
        void DeleteAccount(st6::wstring&);
        void DeleteCharacterFromID(st6::wstring&);
        bool DeleteCharacterFromName(st6::wstring&);
        CAccount* FindAccountFromCharacterID(st6::string&);
        CAccount* FindAccountFromCharacterName(st6::wstring&);
        CAccount* FindAccountFromClientID(u32);
        CAccount* FindAccountFromName(st6::wstring&);
        bool GetAccountAdminRights(st6::wstring&);
        bool GetAccountBanned(st6::wstring&);
        const u16* GetActiveCharacterName(u32) const;
        bool GetCharactersForAccount(st6::wstring&, st6::list<st6::wstring>&);
        u32 GetGroupID(u32);
        st6::wstring& GetMOTD();
        u32 GetMaxPlayerCount();
        u32 GetServerID();
        const char* GetServerSig();
        void LockAccountAccess(st6::wstring&);
        bool MakeLocalUserPath(char*, const char*);
        void ReadCharacterName(const char*, st6::wstring&);
        void SendGroupID(u32, u32);
        void SendSystemID(u32, u32);
        bool SetAccountAdminRights(st6::wstring&, bool);
        bool SetAccountPassword(st6::wstring&, st6::wstring&);
        void SetMOTD(st6::wstring&);
        void UnlockAccountAccess(st6::wstring&);
        void cleanup(u32);
        bool create_new_character(const SCreateCharacterInfo&, u32);
        bool create_restart_file(const char*);
        void free();
        void init(u32, bool);
        bool is_valid(const u32&);
        bool is_valid_ship_owner(const u32&, const u32&);
        u8 login(const SLoginInfo&, u32);
        void logout(u32);
        void logout_all();
        PlayerData* traverse_active(PlayerData*) const;

    private:
        int create_account(const SLoginInfo&);
        u8 load_user_data(const SLoginInfo&, u32);
        u32 to_index(u32);

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
            void set_sys_id(u32);
            void update();

        public:
            u8 data[OBJECT_DATA_SIZE];
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

struct MetaListNode
{
        MetaListNode* next;
        MetaListNode* prev;
        GameObject* value;
};

struct MetaList
{
        uint vtable;
        MetaListNode* start;
        MetaListNode* end;
        uint dunno[2];
};

struct Observer
{
        uint vtable;
        uint dunno[11];
        f64 timestamp;
        uint clientId;
        Vector position;
        uint dunno2[30]; // unknown size
};

class IMPORT StarSystem
{
        u32 count_players(u32 clientIdToIgnore) const;

    public:
        uint vftable;                           // 0
        void* commReferableRelatedPtr;          // 4
        st6::list<Observer> observerList;       // 8
        st6::list<uint> dunnoList;              // 20
        ISpatialPartition* spatialPartitionBSP; // 32
        st6::vector<uint> dunnoVector;          // 36
        MetaList shipList;                      // 52/13
        MetaList lootList;                      // 72/18
        MetaList solarList;                     // 92/23
        MetaList guidedList;                    // 112
        MetaList bulletList;                    // 132
        MetaList mineList;                      // 152
        MetaList counterMeasureList;            // 172
        MetaList asteroidList;                  // 192
        MetaList unkList1;                      // 212 one of those is dynamic asteroids?
        MetaList unkList2;                      // 232
        bool systemLoaded;                      // 252
};

namespace SysDB
{
    // IMPORT std::map<u32, StarSystem, std::less<u32>, std::allocator<StarSystem>> SysMap;
    inline static st6::map<u32, StarSystem>* GetSysMap()
    {
        static auto SysMap = reinterpret_cast<st6::map<u32, StarSystem>*>(u32(GetModuleHandleA("server")) + 0xADA2C);
        return SysMap;
    }
}; // namespace SysDB

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
        u8 data[16];
};

namespace pub
{
    struct CargoEnumerator;

    IMPORT int BuildBaseReader(INI_Reader&, const u32&);
    IMPORT int BuildSystemReader(INI_Reader&, const u32&);
    IMPORT HINSTANCE__* DLL_LoadLibrary(const char*);
    IMPORT void DebugPrint(const char*, int);
    IMPORT int FindHardpoint(const char*, u32, Vector&, Matrix&);
    IMPORT int GetBaseID(u32&, const char*);
    IMPORT u32 GetBaseNickname(char*, u32, const u32&);
    IMPORT int GetBaseStridName(u32&, const u32&);
    IMPORT int GetBases(const u32&, u32* const, u32, u32&);
    IMPORT int GetCargoHoldSize(const u32&, u32&);
    IMPORT int GetCostumeID(int&, const char*);
    IMPORT IFileSystem* GetDataPath();
    IMPORT int GetEquipmentID(u32&, const char*);
    IMPORT int GetFullHealth(const u32&, u32&);
    IMPORT int GetGoodID(u32&, const char*);
    IMPORT int GetGoodProperties(const u32&, f32&, f32&);
    IMPORT int GetLoadout(EquipDescVector&, const u32&);
    IMPORT int GetLoadoutID(u32&, const char*);
    IMPORT int GetLoadoutName(const u32&, char*, int);
    IMPORT u32 GetLocationNickname(char*, u32, const u32&);
    IMPORT int GetLocations(const u32&, u32* const, u32, u32&);
    IMPORT int GetMaxHitPoints(const u32&, int&);
    IMPORT int GetNavMapScale(u32, f32&);
    IMPORT u32 GetNicknameId(const char*);
    IMPORT int GetRwTime(f64&);
    IMPORT int GetShipArchSTRID(const u32&, u32&);
    IMPORT int GetShipID(u32&, const char*);
    IMPORT int GetSolarType(const u32&, u32&);
    IMPORT int GetSystem(u32&, const u32&);
    IMPORT int GetSystemGateConnection(const u32&, u32&);
    IMPORT int GetSystemID(u32&, const char*);
    IMPORT u32 GetSystemNickname(char*, u32, const u32&);
    IMPORT int GetTime(f64&);
    IMPORT int GetType(const u32&, u32&);
    IMPORT int GetVoiceID(u32&, const char*);
    IMPORT int IsCommodity(const u32&, bool&);
    IMPORT u16 MakeId(const char*);
    IMPORT bool NextBaseID(u32&);
    IMPORT bool NextSystemID(u32&);
    IMPORT int ReportFreeTerminal(u32, int);
    IMPORT int Save(u32, u32);
    // IMPORT int SetTimer(u32 const&, Controller::TimerExpired const&, f32);
    IMPORT bool SinglePlayer();
    IMPORT int TranslateArchToGood(const u32&, u32&);
    IMPORT int TranslateGoodToMsgIdPrefix(u32, TString<64>&);
    IMPORT int TranslateShipToMsgIdPrefix(u32, TString<64>&);
    IMPORT int TranslateSystemToMsgIdPrefix(u32, TString<64>&);

    namespace AI
    {
        class Personality;

        IMPORT OP_RTYPE SubmitDirective(u32, BaseOp*);
        IMPORT OP_RTYPE SubmitState(u32, BaseOp*);
        IMPORT bool enable_all_maneuvers(u32);
        IMPORT bool enable_maneuver(u32, int, bool);
        IMPORT int get_behavior_id(u32);
        IMPORT bool get_personality(u32, Personality&);
        IMPORT ScanResponse get_scan_response(u32, u32, u32);
        IMPORT int get_state_graph_id(u32);
        IMPORT bool lock_maneuvers(u32, bool);
        IMPORT void refresh_state_graph(u32);
        IMPORT int remove_forced_target(u32, u32);
        IMPORT OP_RTYPE set_directive_priority(u32, DirectivePriority);
        IMPORT bool set_player_enemy_clamp(u32, int, int);
        IMPORT int submit_forced_target(u32, u32);
        IMPORT enum FORMATION_RTYPE update_formation_state(u32, u32, const Vector&);
    }; // namespace AI

    namespace Audio
    {
        struct Tryptich
        {
                uint spaceMusic = 0;
                uint dangerMusic = 0;
                uint battleMusic = 0;
                uint overrideMusic = 0;
                bool playOnce = false;
                f32 crossFadeDurationInS = 0.0f;
        };

        IMPORT int CancelMusic(u32);
        IMPORT int PlaySoundEffect(u32, u32);
        IMPORT int SetMusic(u32, const Tryptich&);
    }; // namespace Audio

    namespace GF
    {
        enum MVEmptyReason
        {
        };
        IMPORT ulong AmbientScriptCreate(const struct AmbientScriptDescription&);
        IMPORT void AmbientScriptDestroy(ulong*);
        IMPORT ulong CharacterBehaviorCreate(const struct CharacterBehaviorDescription&);
        IMPORT void CharacterBehaviorDestroy(ulong*);
        IMPORT u32 CharacterCreate(const struct CharacterDescription&);
        IMPORT void CharacterDestroy(u32*);
        IMPORT void CharacterSetBehavior(u32, ulong);
        IMPORT void EnumerateCharacterPlacementIni(u32, void (*)(int, INI_Reader*, void*), void*);
        IMPORT u32 FindBase(const char*);
        IMPORT u32 FindLocation(u32, const char*);
        IMPORT const char* FormCharacterPlacementName(const SetpointProperties*);
        IMPORT int GetAccessory(const char*);
        IMPORT int GetBasePosition(const u32&, const u32&, Vector&);
        IMPORT int GetBodyPart(const char*, int);
        IMPORT u32 GetCharacterOnPlacement(u32, u32, int);
        IMPORT int GetCharacterPlacementByName(u32, const char*, int&);
        IMPORT const char* GetCharacterPlacementName(u32, int);
        IMPORT ulong GetCharacterPlacementOccupancy(u32, int);
        IMPORT int GetCharacterPlacementPosture(u32, int, ulong&);
        IMPORT bool GetCharacterPlacementProperties(u32, int, SetpointProperties*);
        IMPORT void GetCostumeByID(int, Costume&);
        IMPORT int GetCostumeSkeletonGender(const Costume&, int&);
        IMPORT int GetMissionVendorOfferCount(u32, u32);
        IMPORT int GetNumCharacterPlacements(u32);
        IMPORT f32 GetRtcPerformanceSlider();
        IMPORT u32 GetSpaceflightLocation();
        IMPORT bool IsCharacterPlacementNormal(u32, int);
        IMPORT bool IsCharacterPlacementSpecial(u32, int);
        IMPORT void MissionVendorAcceptance(ulong, bool, const FmtStr&, u32);
        IMPORT ulong MissionVendorOfferCreate(const struct MissionVendorOfferDescription&);
        IMPORT void MissionVendorOfferDestroy(ulong*);
        IMPORT ulong NewsBroadcastCreate(const struct NewsBroadcastDescription&);
        IMPORT void NewsBroadcastDestroy(ulong*);
        IMPORT int ReportWhyMissionVendorEmpty(u32, MVEmptyReason);
    }; // namespace GF

    namespace Market
    {
        IMPORT int GetCommoditiesForSale(u32, u32* const, int*);
        IMPORT int GetCommoditiesInDemand(u32, u32* const, int*);
        IMPORT int GetGoodJumpDist(u32, u32&);
        IMPORT int GetMinInventory(u32, u32, int&);
        IMPORT int GetNominalPrice(u32, f32&);
        IMPORT int GetNumCommoditiesForSale(u32, int*);
        IMPORT int GetNumCommoditiesInDemand(u32, int*);
        IMPORT int GetPrice(u32, u32, f32&);
        IMPORT int IsGoodInDemand(u32, u32, bool&);
    }; // namespace Market

    namespace Phantom
    {
        IMPORT int Attach(const u32&, void*);
        IMPORT int Create(u32, const Vector&, const Vector&, const Matrix&, u32, void*&);
        IMPORT int Create(u32, f32, const Vector&, u32, void*&);
        IMPORT int Destroy(void*);
        IMPORT int Detach(void*);
        IMPORT int SetActive(void*, bool);
    }; // namespace Phantom

    namespace Player
    {
        IMPORT int AddCargo(const u32&, const u32&, u32, f32, bool);
        IMPORT int AdjustCash(const u32&, int);
        IMPORT int CfgInterfaceNotification(u32, u32, bool, int);
        IMPORT int DisplayMissionMessage(const u32&, const FmtStr&, MissionMessageType, bool);
        IMPORT int EnumerateCargo(const u32&, pub::CargoEnumerator&);
        IMPORT int ForceLand(u32, u32);
        IMPORT int GetAssetValue(const u32&, f32&);
        IMPORT int GetBase(const u32&, u32&);
        IMPORT int GetBody(const u32&, u32&);
        IMPORT int GetCharacter(const u32&, u32&);
        IMPORT int GetGender(const u32&, int&);
        IMPORT int GetGroupMembers(u32, st6::vector<u32>&);
        IMPORT int GetGroupSize(u32, u32&);
        IMPORT int GetLocation(const u32&, u32&);
        IMPORT int GetMoneyNeededToNextRank(const u32&, int&);
        IMPORT int GetMsnID(u32, u32&);
        IMPORT int GetName(u32, st6::wstring&);
        IMPORT int GetNumKills(const u32&, int&);
        IMPORT int GetNumMissionFailures(const u32&, int&);
        IMPORT int GetNumMissionSuccesses(const u32&, int&);
        IMPORT int GetRank(const u32&, int&);
        IMPORT int GetRelativeHealth(const u32&, f32&);
        IMPORT int GetRemainingHoldSize(const u32&, f32&);
        IMPORT int GetRep(const u32&, int&);
        IMPORT int GetShip(const u32&, u32&);
        IMPORT int GetShipID(const u32&, u32&);
        IMPORT int GetSystem(const u32&, u32&);
        IMPORT int InspectCash(const u32&, int&);
        IMPORT int IsGroupMember(u32, u32, bool&);
        IMPORT int LoadHint(u32, BaseHint*);
        IMPORT int MarkObj(u32, u32, int);
        IMPORT int PopUpDialog(u32, const FmtStr&, const FmtStr&, u32);
        IMPORT int RemoveCargo(const u32&, u16, u32);
        IMPORT int RemoveFromGroup(u32);
        IMPORT int ReplaceMissionObjective(const u32&, const u32&, u32, const struct MissionObjective&);
        IMPORT int ReturnBestPath(u32, u8*, int);
        IMPORT int ReturnPlayerStats(u32, u8*, int);
        IMPORT int RevertCamera(u32);
        IMPORT int RewardGroup(u32, int);
        IMPORT int SendNNMessage(u32, u32);
        IMPORT int SetCamera(u32, const Transform&, f32, f32);
        IMPORT int SetCostume(const u32&, int);
        IMPORT int SetInitialOrnt(const u32&, const Matrix&);
        IMPORT int SetInitialPos(const u32&, const Vector&);
        IMPORT int SetMissionObjectiveState(const u32&, const u32&, int, u32);
        IMPORT int SetMissionObjectives(const u32&, const u32&, const MissionObjective*, u32, const FmtStr&,
                                        u8, const FmtStr&);
        IMPORT int SetMoneyNeededToNextRank(u32, int);
        IMPORT int SetMonkey(u32);
        IMPORT int SetMsnID(u32, u32, u32, bool, u32);
        IMPORT int SetNumKills(const u32&, int);
        IMPORT int SetNumMissionFailures(const u32&, int);
        IMPORT int SetNumMissionSuccesses(const u32&, int);
        IMPORT int SetRank(u32, int);
        IMPORT int SetRobot(u32);
        IMPORT int SetShipAndLoadout(const u32&, u32, const EquipDescVector&);
        IMPORT int SetStoryCue(const u32&, u32);
        IMPORT int SetTrent(u32);
    }; // namespace Player

    namespace Reputation
    {
        IMPORT int Alloc(int&, const FmtStr&, const FmtStr&);
        IMPORT int EnumerateGroups(struct Enumerator&);
        IMPORT int Free(const int&);
        IMPORT int GetAffiliation(const int&, u32&);
        IMPORT int GetAttitude(const int&, const int&, f32&);
        IMPORT int GetGroupFeelingsTowards(const int&, const u32&, f32&);
        IMPORT int GetGroupName(const u32&, u32&);
        IMPORT int GetName(const int&, FmtStr&, FmtStr&);
        IMPORT int GetRank(const int&, f32&);
        IMPORT int GetReputation(int&, const ID_String&);
        IMPORT int GetReputation(int&, const char*);
        IMPORT int GetReputation(const int&, const u32&, f32&);
        IMPORT int GetReputation(const u32&, const u32&, f32&);
        IMPORT int GetReputationGroup(u32&, const char*);
        IMPORT int GetShortGroupName(const u32&, u32&);
        IMPORT int SetAffiliation(const int&, const u32&);
        IMPORT int SetAttitude(const int&, const int&, f32);
        IMPORT int SetRank(const int&, f32);
        IMPORT int SetReputation(const int&, const u32&, f32);
        IMPORT int SetReputation(const u32&, const u32&, f32);
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
                f32 status;
                uint count;
                bool mission;
        };

        struct ShipInfo
        {
                uint flag = 0;
                SystemId system;
                Id shipArchetype;
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
                f32 unk7 = 0;
                f32 unk8 = 0;
                f32 unk9 = 0;
                f32 unk10 = 0;
                f32 unk11 = 0;
                f32 unk12 = 0;
                f32 unk13 = 0;
                uint unk14 = 0;

                int rep = 0; // increases for each NPC spawned, starts at 0 or 1
                Id pilotVoice;
                uint unk15 = 0;         // 0
                uint health = UINT_MAX; // -1 = max health
                uint unk16 = 0;         // 0
                uint unk17 = 0;         // 0
                uint level = 1;
        };

        struct SolarInfo
        {
                int flag; // 0x290; ShipInfo has this too, no clue whether actually a flag
                Id archId;
                SystemId systemId;
                Vector pos;
                Matrix orientation;
                Id loadoutId;
                Costume costume;
                int rep;
                Id voiceId;
                BaseId dockWith;
                bool missionBool;
                int hitPointsLeft;
                char nickName[64]; // Has to be unique
                uint unk11;        // 0 unused?
                uint mission = 0;  // 1 = flagged as mission solar, 0 = normal
        };

        struct LootInfo
        {
                SystemId systemId;
                Id equipmentArchId;
                Id infocardOverride;
                uint ownerId;
                Vector linearVelocity;
                Vector pos;
                Matrix rot;
                Vector angularVelocity;
                int itemCount;
                f32 hitPtsPercentage;
                bool canAITractor;
                bool isMissionLoot;
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

        IMPORT int Activate(const u32&, bool, int);
        IMPORT EQUIPMENT_RTYPE ActivateEquipment(const u32&, struct EQInfo*);
        IMPORT int AddImpulse(const u32&, const Vector&, const Vector&);
        IMPORT int Create(u32&, const ShipInfo&);
        IMPORT int CreateLoot(u32&, const LootInfo&);
        IMPORT int CreateSolar(u32&, const SolarInfo&);
        IMPORT int Destroy(u32, DestroyType);
        IMPORT int Dock(const u32&, const u32&, int, DOCK_HOST_RESPONSE);
        IMPORT int DockRequest(const u32&, const u32&);
        IMPORT int DrainShields(u32);
        IMPORT int EnumerateCargo(const u32&, pub::CargoEnumerator&);
        IMPORT int ExistsAndAlive(u32);
        IMPORT int FormationResponse(const u32&, FORMATION_RTYPE);
        IMPORT int GetArchetypeID(const u32&, u32&);
        IMPORT int GetAtmosphereRange(const u32&, f32&);
        IMPORT int GetBurnRadius(const u32&, f32&, Vector&);
        IMPORT int GetCargoSpaceOccupied(const u32&, u32&);
        IMPORT int GetCenterOMass(const u32&, Vector&);
        IMPORT int GetDockingTarget(const u32&, u32&);
        IMPORT int GetEmptyPos(const u32&, const Transform&, const f32&, const f32&, const PosSelectionType&, Vector&);
        IMPORT int GetGoodID(const u32&, u32&);
        IMPORT int GetHardpoint(const u32&, const char*, Vector*, Matrix*);
        IMPORT int GetHealth(const u32& SpaceObj, f32& CurrentHealth, f32& MaxHealth);
        IMPORT int GetInvincible(u32, bool&, bool&, f32&);
        IMPORT int GetJumpTarget(const u32&, u32&, u32&);
        IMPORT int GetLocation(u32, Vector&, Matrix&);
        IMPORT int GetMass(const u32&, f32&);
        IMPORT int GetMotion(u32, Vector&, Vector&);
        IMPORT int GetRadius(const u32&, f32&, Vector&);
        IMPORT int GetRelativeHealth(const u32&, f32&);
        IMPORT int GetRep(u32, int&);
        IMPORT int GetScannerRange(u32, int&, int&);
        IMPORT int GetShieldHealth(const u32& spaceObj, f32& currentShields, f32& maxShields, bool& shieldsUp);
        IMPORT int GetSolarArchetypeID(u32, u32&);
        IMPORT int GetSolarArchetypeNickname(char*, int, u32);
        IMPORT int GetSolarParent(const u32&, u32&);
        IMPORT int GetSolarRep(u32, int&);
        IMPORT int GetSystem(u32, u32&);
        IMPORT int GetTarget(const u32&, u32&);
        IMPORT int GetTerminalInfo(const u32&, int terminalIndex, TerminalInfo&);
        IMPORT int GetTradelaneNextAndPrev(const u32&, u32&, u32&);
        IMPORT int GetType(u32, u32&);
        IMPORT int GetVoiceID(const u32&, u32&);
        IMPORT int InstantDock(const u32&, const u32&, int);
        IMPORT int IsPosEmpty(const u32&, const Vector&, const f32&, bool&);
        IMPORT int JettisonEquipment(const u32&, const u16&, const int&);
        IMPORT int JumpIn(const u32&, const u32&);
        IMPORT int LaneResponse(const u32&, int);
        IMPORT int Launch(const u32&, const u32&, int);
        IMPORT int LightFuse(const u32&, const char*, f32);
        IMPORT int Relocate(const u32&, const u32&, const Vector&, const Matrix&);
        IMPORT int RequestSpaceScript(const u32&, const Vector&, const int&, u32, const char*);
        IMPORT int SendComm(u32, u32, u32, const Costume*, u32, u32*, int, u32, f32,
                            bool);
        IMPORT int SetInvincible2(u32, bool, bool, f32);
        IMPORT int SetInvincible(u32, bool, bool, f32);
        IMPORT int SetRelativeHealth(const u32&, f32);
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

        IMPORT int EnumerateConnections(const u32&, pub::System::ConnectionEnumerator&, ConnectionType);
        IMPORT int EnumerateObjects(const u32&, SysObjEnumerator&);
        IMPORT int EnumerateZones(const u32&, struct ZoneEnumerator&);
        IMPORT int Find(const u32&, const char*, u32&);
        IMPORT int GetName(u32, u32&);
        IMPORT int GetNestedProperties(const u32&, const Vector&, ulong&);
        IMPORT int InZones(u32, const Transform&, f32, f32, f32, u32* const, u32, u32&);
        IMPORT int InZones(u32, const Vector&, f32, u32* const, u32, u32&);
        IMPORT int LoadSystem(const u32&);
        IMPORT int ScanObjects(const u32&, u32* const, u32, const Vector&, f32, u32, u32&);
    }; // namespace System

    namespace Zone
    {
        enum ZoneShape
        {
        };
        IMPORT f32 ClassifyPoint(u32, const Vector&);
        IMPORT f32 GetDistance(u32, const Vector&);
        IMPORT u32 GetId(u32, const char*);
        IMPORT int GetLootableInfo(u32, ID_String&, ID_String&, int&, int&, int&);
        IMPORT int GetName(u32, u32&);
        IMPORT int GetOrientation(const u32&, Matrix&);
        // IMPORT  int GetPopulation(u32,class weighted_vector<u32> const * &);
        IMPORT Vector GetPos(u32);
        IMPORT int GetProperties(u32, ulong&);
        IMPORT f32 GetRadius(u32);
        IMPORT int GetShape(u32, ZoneShape&);
        IMPORT int GetSize(u32, Vector&);
        IMPORT u32 GetSystem(u32);
        IMPORT bool InZone(u32, const Vector&, f32);
        IMPORT bool Intersect(u32, const Vector&, const Vector&, Vector&);
        IMPORT bool VerifyId(u32);
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

        IMPORT u32 Create(const char*, const char*, const CreateParms*, PRIORITY);
        IMPORT void Destroy(u32);
        IMPORT int SetHeartbeatInterval(const u32&, f32);
        IMPORT int _SendMessage(const u32&, int, const void*);
    } // namespace Controller

}; // namespace pub

IMPORT void (*g_pPrivateChatHook)(u16*, int);
IMPORT void (*g_pSystemChatHook)(u16*, int);
IMPORT void (*g_pUniverseChatHook)(u16*, int);

IMPORT PlayerDB Players;
extern "C" IMPORT IServerImpl Server;

#endif // _FLCORESERVER_H_
