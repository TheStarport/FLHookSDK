#pragma once

struct CollisionGroupDesc;
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
        unsigned id;
};

enum class DOCK_HOST_RESPONSE
{
    AccessDenied = 1,
    DockDenied = 2,
    DockInUse = 3,
    ProceedDock = 4,
    Dock = 5,
};

enum class EventRequestType
{
    StationJumpDock = 0,
    TradeLaneDock = 1,
    FormationJoin = 2,
};

enum class ResponseCode
{
    Success = 0,
    Failure = -2,
    InvalidInput = -4
};

struct SGFGoodVaporizedInfo
{
        unsigned dunno[128];
};

struct SSPMunitionCollisionInfo
{
        Id projectileArchId;
        ObjectId attackerId;
        ObjectId targetObjId;
        unsigned short subObjId;
        Vector impactPosition;
};

struct SSPBadLandsObjCollisionInfo
{
        unsigned dunno[128];
};

struct SSPObjCollisionInfo
{
        unsigned colliderObjectId;
        unsigned colliderSubObjId;
        unsigned damagedObjectId;
        unsigned damagedSubObjId;
        float damage;
};

struct SSPUseItem
{
        Id userShipId;
        unsigned short itemId;
        unsigned short amountUsed;
};

struct XActivateEquip
{
        Id spaceId;
        unsigned short id;
        bool activate;
};

struct XActivateCruise
{
        Id ship;
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
        st6::vector<unsigned short> hpIds;
};

struct XCollision
{
        unsigned short componentId;
        float componentHp;
};

struct XSetManeuver
{
        Id shipFrom;
        Id shipTo;
        unsigned flag;
};

struct XSetTarget
{
        Id ship;
        unsigned slot;
        Id spaceId;
        unsigned short subObjId;
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
        unsigned stateValue;
        // Enum of some kind
        char state;
};

struct XJettisonCargo
{
        Id ship;
        unsigned short slot;
        unsigned count;
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
        unsigned dunno1;
        wchar_t* charname;
        unsigned dunno2[32];
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
        unsigned nickName; // From [Faction] section of newcharacter.ini
        unsigned base;     // From [Faction] section of newcharacter.ini
        unsigned package;  // From [Faction] section of newcharacter.ini
        unsigned pilot;    // From [Faction] section of newcharacter.ini
        unsigned dunno[96];
};

struct SStartupInfo
{
        unsigned dunno[130];
        int maxPlayers;
};

struct SLoginInfo
{
        wchar_t account[36];
};

struct RequestBestPathStruct
{
        unsigned clientId;
        unsigned dunno0;
        unsigned dunno1;
        Vector startPos;
        unsigned dunno2;
        unsigned startSystem;
        Vector endPos;
        unsigned dunno3;
        unsigned endSystem;
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
        unsigned dunno1;
        wchar_t* accId;
        unsigned dunno2[7];
        CAccountListNode* firstListNode;
        unsigned numberOfCharacters;
        unsigned dunno4;
        unsigned clientId;
        unsigned dunno5[30];
};

enum CommResult
{
};
