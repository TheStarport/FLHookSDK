//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreRemoteClient.h
//	Module:			FLCoreRemoteClient.lib
//	Description:	Interface to RemoteClient.dll
//
//	Web: www.skif.be/flcoresdk.php
//
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCOREREMOTECLIENT_H_
#define _FLCOREREMOTECLIENT_H_

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
        uint dunno[20];
};

struct FLPACKET_SYSTEM_SWITCH_OUT
{
        uint shipId;
        uint jumpObjectId;
};

struct FLPACKET_SYSTEM_SWITCH_IN
{
        uint shipId;
        uint objType;
        Vector pos;
        Quaternion quat;
};

struct FLPACKET_CREATEGUIDED
{
        uint projectileObjId;
        Vector pos;
        Quaternion ori;
        uint targetId;
        uint iDunno;
        uint munitionArchId;
        uint iDunno2; // zero (initial speed?)
        uint ownerId;
};

struct FLPACKET_SETREPUTATION
{
        uint spaceId;
        float rep;
        uint repGroup; // not sure
                       // there is more (FMTStr? - object name?)
};

struct FLPACKET_LAUNCH
{
        uint ship;
        uint base;
        uint state;
        Quaternion rotate;
        Vector pos;
};

struct FLPACKET_BURNFUSE
{
        uint shipAttacker;
        uint ship;
        uint fuseId;
        uint dunno1;
        uint dunno2;
        float dunno3;
        bool active;
};

struct FLPACKET_DESTROYOBJECT
{
        uint spaceId;
        DestroyType destroyType;
};

struct FLPACKET_CREATESHIP
{
        char* address; // pointer to CShipCreate vtable
        uint spaceId;
        uint solarArch;
        uint dockBaseId;
        uint rep;
        Costume costume;
        uint voiceId;
        Vector pos;
        Quaternion orientation;
        uint64 health;
        EquipDescVector equip;
        st6::list<CollisionGroupDesc> colGrps;
        DamageList dmgList; // only holds shield state, which is ignored by receiving client.
        uint clientId;
        uint groupId;
        uint rank;
        Vector linearVelocity;  // ignored by receiving client.
        Vector angularVelocity; // ignored by receiving client.
        float throttle;
        uint dunno;
        uint playerGroup; // pointer to CPlayerGroup? Possibly ignored.
        bool inTradeLane;
};

struct FLPACKET_CREATESOLAR
{
        char* address; // pointer to CSolarCreate vtable
        uint spaceId;
        uint shipArch;
        uint baseDockId;
        uint rep;
        Costume costume;
        uint voiceId;
        Vector pos;
        Quaternion orientation;
        uint64 health;
        EquipDescVector equip;
        st6::list<CollisionGroupDesc> colGrps;
        DamageList dmg; // only holds shield state, which is ignored by receiving client.
        bool isDynamic;
        bool isDestructible;
};

struct FLPACKET_LAND
{
        uint ship;
        uint landSpaceID;
        uint targetBase;
};

struct SObjectCargoUpdate
{
        uint client;
        Vector position;
        uint dunno[24];
};

struct IClientImpl
{
    public:
        void* unknown[2];
        CDPServer* cdpServer;

        // N.B. Do not modify order, vtable ordering is fixed by RemoteClient.dll
        virtual bool Send_FLPACKET_COMMON_FIREWEAPON(uint client, XFireWeaponInfo& fwi);
        virtual bool Send_FLPACKET_COMMON_ACTIVATEEQUIP(uint client, XActivateEquip& aq);
        virtual bool Send_FLPACKET_COMMON_ACTIVATECRUISE(uint client, XActivateCruise& aq);
        virtual bool Send_FLPACKET_COMMON_ACTIVATETHRUSTERS(uint client, XActivateThrusters& aq);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SETTARGET(uint client, XSetTarget& st);
        [[NoPlugins]]
        virtual void unknown_6(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_GOTRADELANE(uint client, XGoTradelane& tl);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_STOPTRADELANE(uint client, uint shipID, uint archTradelane1, uint archTradelane2);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_JETTISONCARGO(uint client, XJettisonCargo& jc);
        [[NoPlugins, NoLog]]
        virtual bool SendPacket(uint client, void*);
        [[CallInner, NoLog, NoPlugins]] virtual bool Startup(uint, uint);
        [[NoPlugins]] virtual void nullsub(uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_LOGINRESPONSE(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_CHARACTERINFO(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_CHARSELECTVERIFIED(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins, NoLog]]
        virtual void Shutdown();
        [[NoHook]]
        virtual bool DispatchMsgs();
        [[NoPlugins]]
        virtual bool CDPClientProxyDisconnect(uint client);
        [[NoPlugins]]
        virtual uint CDPClientProxyGetSendQSize(uint client);
        [[NoPlugins]]
        virtual uint CDPClientProxyGetSendQBytes(uint client);
        virtual double CDPClientProxyGetLinkSaturation(uint client);
        virtual bool Send_FLPACKET_SERVER_SETSHIPARCH(uint client, uint shipArch);
        virtual bool Send_FLPACKET_SERVER_SETHULLSTATUS(uint client, float status);
        virtual bool Send_FLPACKET_SERVER_SETCOLLISIONGROUPS(uint client, st6::list<CollisionGroupDesc>&);
        virtual bool Send_FLPACKET_SERVER_SETEQUIPMENT(uint client, st6::vector<EquipDesc>&);
        [[NoPlugins]]
        virtual void unknown_26(uint client, uint);
        virtual bool Send_FLPACKET_SERVER_SETADDITEM(uint client, FLPACKET_UNKNOWN*, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_28(uint client, uint, uint, uint);
        virtual bool Send_FLPACKET_SERVER_SETSTARTROOM(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFDESTROYCHARACTER(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFUPDATECHAR(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETECHARLIST(uint client, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFSCRIPTBEHAVIOR(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFDESTROYSCRIPTBEHAVIOR(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETESCRIPTBEHAVIORLIST(uint client, uint);
        [[NoPlugins]]
        virtual void unknown_36(uint client, uint, uint);
        [[NoPlugins]]
        virtual void unknown_37(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETEAMBIENTSCRIPTLIST(uint client, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFDESTROYMISSIONCOMPUTER(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFUPDATEMISSIONCOMPUTER(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETEMISSIONCOMPUTERLIST(uint client, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFMISSIONVENDORACCEPTANCE(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFMISSIONVENDORWHYEMPTY(uint client, uint reason);
        [[NoPlugins]]
        virtual void unknown_44(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFUPDATENEWSBROADCAST(uint client, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_GFCOMPLETENEWSBROADCASTLIST(uint client, uint);
        virtual bool Send_FLPACKET_SERVER_CREATESOLAR(uint client, FLPACKET_CREATESOLAR& solar);
        virtual bool Send_FLPACKET_SERVER_CREATESHIP(uint client, FLPACKET_CREATESHIP& ship);
        virtual bool Send_FLPACKET_SERVER_CREATELOOT(uint client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_CREATEMINE(uint client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_CREATEGUIDED(uint& client, FLPACKET_CREATEGUIDED&);
        virtual bool Send_FLPACKET_SERVER_CREATECOUNTER(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_53(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_54(uint client, uint, uint, uint);
        [[NoLog]]
        virtual bool Send_FLPACKET_COMMON_UPDATEOBJECT(uint client, SSPObjUpdateInfo& update);
        virtual bool Send_FLPACKET_SERVER_DESTROYOBJECT(uint client, FLPACKET_DESTROYOBJECT& destroy);
        virtual bool Send_FLPACKET_SERVER_ACTIVATEOBJECT(uint client, XActivateEquip& aq);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_SYSTEM_SWITCH_OUT(uint client, FLPACKET_SYSTEM_SWITCH_OUT&);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_SYSTEM_SWITCH_IN(uint client, FLPACKET_SYSTEM_SWITCH_IN&);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_LAND(uint client, FLPACKET_LAND& land);
        virtual bool Send_FLPACKET_SERVER_LAUNCH(uint client, FLPACKET_LAUNCH& launch);
        virtual bool Send_FLPACKET_SERVER_REQUESTCREATESHIPRESP(uint client, bool response, uint shipID);
        [[NoPlugins]]
        virtual void unknown_63(uint client, FLPACKET_UNKNOWN*);
        [[NoLog, NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_DAMAGEOBJECT(uint client, uint objID, DamageList& dmgList);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_ITEMTRACTORED(uint client, uint);
        virtual bool Send_FLPACKET_SERVER_USE_ITEM(uint client, uint);
        virtual bool Send_FLPACKET_SERVER_SETREPUTATION(uint client, FLPACKET_SETREPUTATION& rep);
        [[NoPlugins]]
        virtual void unknown_68(uint client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_SENDCOMM(uint client, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint, uint,
                                                   uint, uint, uint, uint, uint, uint);
        [[NoPlugins]]
        virtual void unknown_70(uint client, uint);
        virtual bool Send_FLPACKET_SERVER_SET_MISSION_MESSAGE(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_72(uint client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_SETMISSIONOBJECTIVES(uint client, uint);
        [[NoPlugins]]
        virtual void unknown_74(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_75(uint client, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_MARKOBJ(uint client, uint, uint);
        [[NoPlugins]]
        virtual void unknown_77(uint client, uint);
        virtual bool Send_FLPACKET_SERVER_SETCASH(uint client, uint cash);
        [[NoPlugins]]
        virtual void unknown_79(uint client, uint);
        [[NoPlugins]]
        virtual void unknown_80(uint client, uint);
        [[NoPlugins]]
        virtual void unknown_81(uint client, uint);
        [[NoPlugins]]
        virtual void unknown_82(uint client, uint);
        [[NoPlugins]]
        virtual void unknown_83(uint client, char*);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_REQUEST_RETURNED(uint& client, uint shipID, uint flag, uint, uint);
        [[NoPlugins]]
        virtual void unknown_85(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_86(uint client, uint, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_OBJECTCARGOUPDATE(SObjectCargoUpdate& cargoUpdate, uint dunno1, uint dunno2);
        virtual bool Send_FLPACKET_SERVER_BURNFUSE(uint client, FLPACKET_BURNFUSE& burnFuse);
        [[NoPlugins]]
        virtual void unknown_89(uint client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void unknown_90(uint client);
        [[NoPlugins]]
        virtual void unknown_91(uint client, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_WEAPON_GROUP(uint client, uint, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_VISITED_STATE(uint client, uint objHash, int state);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_REQUEST_BEST_PATH(uint client, uint objHash, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_REQUEST_PLAYER_STATS(uint client, uint, int);
        [[NoPlugins]]
        virtual void unknown_96(uint client, uint, uint, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_REQUEST_GROUP_POSITIONS(uint client, uint, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_MISSION_LOG(uint client, uint, int);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_COMMON_SET_INTERFACE_STATE(uint client, uint, int);
        [[NoPlugins]]
        virtual void unknown_100(uint client, uint, uint);
        [[NoPlugins]]
        virtual void unknown_101(uint& client, FLPACKET_UNKNOWN*);
        [[NoPlugins]]
        virtual void PlayerInitiateTrade(uint client, uint targetShip);
        [[NoPlugins]]
        virtual void PlayerTradeTarget(uint client, uint targetShip);
        [[NoPlugins]]
        virtual void PlayerAcceptTrade(uint client, uint targetShip, uint doAccept);
        [[NoPlugins]]
        virtual void PlayerSetTradeMoney(uint client, uint targetShipId, uint totalMoney);
        [[NoPlugins]]
        virtual void PlayerAddTradeEquip(uint client, uint targetShip, EquipDesc* item);
        [[NoPlugins]]
        virtual void PlayerRemoveTradeEquip(uint client, uint targetShip, EquipDesc* item);
        [[NoPlugins]]
        virtual bool PlayerRequestTrade(uint client, uint targetShip);
        [[NoPlugins]]
        virtual void PlayerStopTradeRequest(uint client, uint targetShip);
        virtual bool Send_FLPACKET_SERVER_SCANNOTIFY(uint client, uint, uint);
        virtual bool Send_FLPACKET_SERVER_PLAYERLIST(uint client, wchar_t*, uint, char);
        [[NoPlugins]]
        virtual void PlayerIsLeavingServer(uint onlineClient, uint leavingClient);
        virtual bool Send_FLPACKET_SERVER_PLAYERLIST_2(uint client);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_6(uint client, uint, uint);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_7(uint client, uint, uint);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE(uint client, FLPACKET_UNKNOWN*);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_2(uint client, uint, uint);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_3(uint client, uint targetID, uint rank);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_4(uint client, uint, uint);
        virtual bool Send_FLPACKET_SERVER_MISCOBJUPDATE_5(uint client, uint, uint);
        [[NoPlugins]]
        virtual void unknown_121(uint client, uint);
        [[NoPlugins]]
        virtual bool Send_FLPACKET_SERVER_FORMATION_UPDATE(uint client, uint shipID, Vector& formationOffset);
        [[NoPlugins]]
        virtual void unknown_123(uint client, uint, uint, uint, uint, uint, uint);
        [[NoPlugins]]
        virtual void unknown_124(uint client);
        [[NoPlugins]]
        virtual void unknown_125(uint client, uint);
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

#endif // _FLCOREREMOTECLIENT_H_
