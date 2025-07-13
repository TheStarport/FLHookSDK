#pragma once

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
        Id projectileArchId;
        DWORD dunno;
        DWORD targetObjId;
        ushort s1;
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
        Id ship;
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
        Id archId;
        int count;
};

struct SGFGoodBuyInfo
{
        BaseId baseId;
        ulong null;
        Id goodId;
        int count;
};

struct XFireWeaponInfo
{
        Id object;
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
        Id shipFrom;
        Id shipTo;
        uint flag;
};

struct XSetTarget
{
        Id ship;
        uint slot;
        Id spaceId;
        ushort subObjId;
};

struct SSPObjUpdateInfoSimple
{
        Id objId;
        Quaternion dir;
        Vector pos;
        float timestamp;
        float throttle;
        char state;
};

struct SSPObjUpdateInfo
{
        Id objId;
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
        Id ship;
        ushort slot;
        ushort _padding;
        ushort count;
};

struct XGoTradelane
{
        Id ship;
        Id tradelaneSpaceObj1;
        Id tradelaneSpaceObj2;
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
        uint dunno4;
        uint clientId;
        uint dunno5[30];
};

enum CommResult
{
};
