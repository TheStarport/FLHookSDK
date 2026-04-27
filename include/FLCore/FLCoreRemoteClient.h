#pragma once

#include "Common.hpp"
#include "FLCoreDefs.hpp"

#pragma warning(disable : 5030)

struct SSPObjUpdateInfo;
struct XJettisonCargo;
struct XGoTradelane;
struct XSetTarget;
struct XActivateEquip;
struct XActivateThrusters;
struct XActivateCruise;
struct XFireWeaponInfo;
struct XCollision;

class IMPORT IClient
{
    public:
        IClient(const IClient&);
        IClient();
        IClient& operator=(const IClient&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class CDPServer;

///////////////////////////////
///// FL PACKET STRUCTS ///////
///////////////////////////////

struct FLPACKET_UNKNOWN
{
        u32 dunno[20];
};

struct FLPACKET_SYSTEM_SWITCH_OUT
{
        u32 shipId;
        u32 jumpObjectId;
};

struct FLPACKET_SYSTEM_SWITCH_IN
{
        u32 shipId;
        u32 objType;
        Vector pos;
        Quaternion quat;
};

struct FLPACKET_CREATEGUIDED
{
        u32 projectileObjId;
        Vector pos;
        Quaternion ori;
        u32 targetId;
        u32 iDunno;
        u32 munitionArchId;
        u32 iDunno2; // zero (initial speed?)
        u32 ownerId;
};

struct FLPACKET_SETREPUTATION
{
        u32 spaceId;
        f32 rep;
        u32 repGroup; // not sure
                       // there is more (FMTStr? - object name?)
};

struct FLPACKET_LAUNCH
{
        u32 ship;
        u32 base;
        u32 state;
        Quaternion rotate;
        Vector pos;
};

struct FLPACKET_BURNFUSE
{
        u32 shipAttacker;
        u32 ship;
        u32 fuseId;
        u32 dunno1;
        u32 dunno2;
        f32 dunno3;
        bool active;
};

struct FLPACKET_DESTROYOBJECT
{
        u32 spaceId;
        DestroyType destroyType;
};

struct FLPACKET_CREATESHIP
{
        char* address; // pointer to CShipCreate vtable
        Id spaceId;
        Id solarArch;
        Id dockBaseId;
        u32 rep;
        Costume costume;
        Id voiceId;
        Vector pos;
        Quaternion orientation;
        u64 health;
        EquipDescVector equip;
        st6::list<CollisionGroupDesc> colGrps;
        DamageList dmgList; // only holds shield state, which is ignored by receiving client.
        u32 clientId;
        u32 groupId;
        u32 rank;
        Vector linearVelocity;  // ignored by receiving client.
        Vector angularVelocity; // ignored by receiving client.
        f32 throttle;
        u32 dunno;
        u32 playerGroup; // pointer to CPlayerGroup? Possibly ignored.
        bool inTradeLane;
};

struct FLPACKET_CREATESOLAR
{
        char* address; // pointer to CSolarCreate vtable
        u32 spaceId;
        u32 shipArch;
        u32 baseDockId;
        u32 rep;
        Costume costume;
        u32 voiceId;
        Vector pos;
        Quaternion orientation;
        u64 health;
        EquipDescVector equip;
        st6::list<CollisionGroupDesc> colGrps;
        DamageList dmg; // only holds shield state, which is ignored by receiving client.
        bool isDynamic;
        bool isDestructible;
};

struct FLPACKET_LAND
{
        u32 ship;
        u32 landSpaceID;
        u32 targetBase;
};

struct SObjectCargoUpdate
{
        u32 client;
        Vector position;
        u32 dunno[24];
};

struct IClientImpl
{
    public:
        void* unknown[2];
        CDPServer* cdpServer;

        // N.B. Do not modify order, vtable ordering is fixed by RemoteClient.dll
        virtual bool Send_FLPACKET_COMMON_FIREWEAPON(u32 client, XFireWeaponInfo& fwi);
        virtual bool Send_FLPACKET_COMMON_ACTIVATEEQUIP(u32 client, XActivateEquip& aq);
        virtual bool Send_FLPACKET_COMMON_ACTIVATECRUISE(u32 client, XActivateCruise& aq);
        virtual bool Send_FLPACKET_COMMON_ACTIVATETHRUSTERS(u32 client, XActivateThrusters& aq);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SETTARGET(u32 client, XSetTarget& st);
        [[NoPlugins]]
        virtual void unknown_6(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_GOTRADELANE(u32 client, XGoTradelane& tl);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_STOPTRADELANE(u32 client, u32 shipID, u32 archTradelane1, u32 archTradelane2);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_JETTISONCARGO(u32 client, XJettisonCargo& jc);
        [[NoPlugins, NoLog]]
        virtual bool SendPacket(u32 client, void*);
        [[CallInner, NoLog, NoPlugins]] virtual bool Startup(u32, u32);
        [[NoPlugins]] virtual void nullsub(u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_LOGINRESPONSE(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_CHARACTERINFO(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_CHARSELECTVERIFIED(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins, NoLog]]
        virtual void Shutdown();
        [[NoHook]]
        virtual bool DispatchMsgs();
        [[NoPlugins]]
        virtual bool CDPClientProxyDisconnect(u32 client);
        [[NoPlugins]]
        virtual u32 CDPClientProxyGetSendQSize(u32 client);
        [[NoPlugins]]
        virtual u32 CDPClientProxyGetSendQBytes(u32 client);
        virtual double CDPClientProxyGetLinkSaturation(u32 client);
        virtual bool Send_FLPACKET_SERVER_SETSHIPARCH(u32 client, u32 shipArch);
        virtual bool Send_FLPACKET_SERVER_SETHULLSTATUS(u32 client, f32 status);
        virtual bool Send_FLPACKET_SERVER_SETCOLLISIONGROUPS(u32 client, st6::list<CollisionGroupDesc>&);
        virtual bool Send_FLPACKET_SERVER_SETEQUIPMENT(u32 client, st6::vector<EquipDesc>&);
        [[NoPlugins]]
        virtual void unknown_26(u32 client, u32);
        virtual bool Send_FLPACKET_SERVER_SETADDITEM(u32 client, FLPACKET_UNKNOWN*, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_28(u32 client, u32, u32, u32);
        virtual bool Send_FLPACKET_SERVER_SETSTARTROOM(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFDESTROYCHARACTER(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFUPDATECHAR(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETECHARLIST(u32 client, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFSCRIPTBEHAVIOR(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFDESTROYSCRIPTBEHAVIOR(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETESCRIPTBEHAVIORLIST(u32 client, u32);
        [[NoPlugins]]
        virtual void unknown_36(u32 client, u32, u32);
        [[NoPlugins]]
        virtual void unknown_37(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETEAMBIENTSCRIPTLIST(u32 client, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFDESTROYMISSIONCOMPUTER(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFUPDATEMISSIONCOMPUTER(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETEMISSIONCOMPUTERLIST(u32 client, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFMISSIONVENDORACCEPTANCE(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFMISSIONVENDORWHYEMPTY(u32 client, u32 reason);
        [[NoPlugins]]
        virtual void unknown_44(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFUPDATENEWSBROADCAST(u32 client, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETENEWSBROADCASTLIST(u32 client, u32);
        virtual bool Send_FLPACKET_SERVER_CREATESOLAR(u32 client, FLPACKET_CREATESOLAR& solar);
        virtual bool Send_FLPACKET_SERVER_CREATESHIP(u32 client, FLPACKET_CREATESHIP& ship);
        virtual bool Send_FLPACKET_SERVER_CREATELOOT(u32 client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_CREATEMINE(u32 client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_CREATEGUIDED(u32& client, FLPACKET_CREATEGUIDED&);
        virtual bool Send_FLPACKET_SERVER_CREATECOUNTER(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_53(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_54(u32 client, u32, u32, u32);
        [[NoLog]]
        virtual bool Send_FLPACKET_COMMON_UPDATEOBJECT(u32 client, SSPObjUpdateInfo& update);
        virtual bool Send_FLPACKET_SERVER_DESTROYOBJECT(u32 client, FLPACKET_DESTROYOBJECT& destroy);
        virtual bool Send_FLPACKET_SERVER_ACTIVATEOBJECT(u32 client, XActivateEquip& aq);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_SYSTEM_SWITCH_OUT(u32 client, FLPACKET_SYSTEM_SWITCH_OUT&);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_SYSTEM_SWITCH_IN(u32 client, FLPACKET_SYSTEM_SWITCH_IN&);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_LAND(u32 client, FLPACKET_LAND& land);
        virtual bool Send_FLPACKET_SERVER_LAUNCH(u32 client, FLPACKET_LAUNCH& launch);
        virtual bool Send_FLPACKET_SERVER_REQUESTCREATESHIPRESP(u32 client, bool response, u32 shipID);
        [[NoPlugins]]
        virtual void unknown_63(u32 client, FLPACKET_UNKNOWN*);
        [[NoLog, NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_DAMAGEOBJECT(u32 client, u32 objID, DamageList& dmgList);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_ITEMTRACTORED(u32 client, u32);
        virtual bool Send_FLPACKET_SERVER_USE_ITEM(u32 client, u32);
        virtual bool Send_FLPACKET_SERVER_SETREPUTATION(u32 client, FLPACKET_SETREPUTATION& rep);
        [[NoPlugins]]
        virtual void unknown_68(u32 client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_SENDCOMM(u32 client, u32 senderObjId, u32 receiverObjId, u32 voice, u32 head, u32 body, u32 leftHand,
                                                   u32 rightHand, u32 accessory1, u32 accessory2, u32 accessory3, u32 accessory4, u32 accessory5,
                                                   u32 accessory6, u32 accessory7, u32 accessory8, u32 accessories, u32 name, u32* lines, u32 lineCount,
                                                   u32 commType, f32 radioSilenceAfter, bool global);
        [[NoPlugins]]
        virtual void unknown_70(u32 client, u32);
        virtual bool Send_FLPACKET_SERVER_SET_MISSION_MESSAGE(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_72(u32 client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_SETMISSIONOBJECTIVES(u32 client, u32);
        [[NoPlugins]]
        virtual void unknown_74(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_75(u32 client, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_MARKOBJ(u32 client, u32, u32);
        [[NoPlugins]]
        virtual void unknown_77(u32 client, u32);
        virtual bool Send_FLPACKET_SERVER_SETCASH(u32 client, u32 cash);
        [[NoPlugins]]
        virtual void unknown_79(u32 client, u32);
        [[NoPlugins]]
        virtual void unknown_80(u32 client, u32);
        [[NoPlugins]]
        virtual void unknown_81(u32 client, u32);
        [[NoPlugins]]
        virtual void unknown_82(u32 client, u32);
        [[NoPlugins]]
        virtual void unknown_83(u32 client, char*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_REQUEST_RETURNED(u32& client, u32 shipID, u32 flag, u32, u32);
        [[NoPlugins]]
        virtual void unknown_85(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_86(u32 client, u32, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_OBJECTCARGOUPDATE(SObjectCargoUpdate& cargoUpdate, u32 dunno1, u32 dunno2);
        virtual bool Send_FLPACKET_SERVER_BURNFUSE(u32 client, FLPACKET_BURNFUSE& burnFuse);
        [[NoPlugins]]
        virtual void unknown_89(u32 client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_90(u32 client);
        [[NoPlugins]]
        virtual void unknown_91(u32 client, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_WEAPON_GROUP(u32 client, u32, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_VISITED_STATE(u32 client, u32 objHash, int state);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_REQUEST_BEST_PATH(u32 client, u32 objHash, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_REQUEST_PLAYER_STATS(u32 client, u32, int);
        [[NoPlugins]]
        virtual void unknown_96(u32 client, u32, u32, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_REQUEST_GROUP_POSITIONS(u32 client, u32, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_MISSION_LOG(u32 client, u32, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_INTERFACE_STATE(u32 client, u32, int);
        [[NoPlugins]]
        virtual void unknown_100(u32 client, u32, u32);
        [[NoPlugins]]
        virtual void unknown_101(u32& client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void PlayerInitiateTrade(u32 client, u32 targetShip);
        [[NoPlugins]]
        virtual void PlayerTradeTarget(u32 client, u32 targetShip);
        [[NoPlugins]]
        virtual void PlayerAcceptTrade(u32 client, u32 targetShip, u32 doAccept);
        [[NoPlugins]]
        virtual void PlayerSetTradeMoney(u32 client, u32 targetShipId, u32 totalMoney);
        [[NoPlugins]]
        virtual void PlayerAddTradeEquip(u32 client, u32 targetShip, EquipDesc* item);
        [[NoPlugins]]
        virtual void PlayerRemoveTradeEquip(u32 client, u32 targetShip, EquipDesc* item);
        [[NoPlugins]]
        virtual bool PlayerRequestTrade(u32 client, u32 targetShip);
        [[NoPlugins]]
        virtual void PlayerStopTradeRequest(u32 client, u32 targetShip);
        virtual bool Send_FLPACKET_SERVER_SCANNOTIFY(u32 client, u32, u32);
        virtual bool Send_FLPACKET_SERVER_PLAYERLIST(u32 client, wchar_t*, u32, char);
        [[NoPlugins]]
        virtual void PlayerIsLeavingServer(u32 onlineClient, u32 leavingClient);
        virtual bool Send_FLPACKET_SERVER_PLAYERLIST_2(u32 client);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_6(u32 client, u32, u32);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_7(u32 client, u32, u32);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE(u32 client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_2(u32 client, u32, u32);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_3(u32 client, u32 targetID, u32 rank);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_4(u32 client, u32, u32);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_5(u32 client, u32, u32);
        [[NoPlugins]]
        virtual void unknown_121(u32 client, u32);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_FORMATION_UPDATE(u32 client, u32 shipID, Vector& formationOffset);
        [[NoPlugins]]
        virtual void unknown_123(u32 client, u32, u32, u32, u32, u32, u32);
        [[NoPlugins]]
        virtual void unknown_124(u32 client);
        [[NoPlugins]]
        virtual void unknown_125(u32 client, u32);
        [[NoPlugins]]
        virtual int unknown_126(char*);
};

IMPORT void ForceClientLogout(unsigned int);
IMPORT int GetClientStats(struct client_stats_t*, int*);
IMPORT int GetNumClients();
IMPORT void GetRemoteClientPort(st6::vector<unsigned long>&);
IMPORT void SetRemoteClientPassword(const unsigned short*);
IMPORT void SetRemoteClientResponseData(bool, bool, int, const unsigned short*, unsigned int, const char*);
IMPORT void SetRemoteClientSessionName(const unsigned short*);
IMPORT void SetServerLogFunction(int (*)(struct ErrorCode, const char*, ...));

// TODO: Explain that this is just an packet-sending interface, not an actual Client
extern "C" IMPORT IClientImpl Client;
extern "C" IMPORT IClientImpl* GetClientInterface();