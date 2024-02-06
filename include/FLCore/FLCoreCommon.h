//////////////////////////////////////////////////////////////////////
//	Project FLCoreSDK v1.1, modified for use in FLHook Plugin version
//--------------------------
//
//	File:			FLCoreCommon.h
//	Module:			FLCoreCommon.lib
//	Description:	Interface to Common.dll
//
//	Web: www.skif.be/flcoresdk.php
//
//
//////////////////////////////////////////////////////////////////////
#ifndef _FLCORECOMMON_H_
#define _FLCORECOMMON_H_

#include "FLCoreDefs.h"

#pragma comment(lib, "FLCoreCommon.lib")

class TRANode;
class RDLReNode;

// space object types
enum class ObjectType
{
    None = 0,
    Moon = 1 << 0,
    Planet = 1 << 1,
    Sun = 1 << 2,
    BlackHole = 1 << 3,
    Satellite = 1 << 4,
    DockingRing = 1 << 5,
    JumpGate = 1 << 6,
    TradelaneRing = 1 << 7,
    Station = 1 << 8,
    WayPoint = 1 << 9,
    AirlockGate = 1 << 10,
    JumpHole = 1 << 11,
    WeaponPlatform = 1 << 12,
    DestructibleDepot = 1 << 13,
    NonTargetable = 1 << 14,
    MissionSatellite = 1 << 15,
    Fighter = 1 << 16,
    Freighter = 1 << 17,
    Gunboat = 1 << 18,
    Cruiser = 1 << 19,
    Transport = 1 << 20,
    Capital = 1 << 21,
    Mining = 1 << 22,
    Guided = 1 << 24,
    Bullet = 1 << 25,
    Mine = 1 << 26,
    Loot = 1 << 28,
    Asteroid = 1 << 29,
};

enum EquipmentClass : uint
{
    All = -1,
    None = 0,
    LightEquip = 1 << 0,
    AttachedFx = 1 << 1, // contrails
    Mine = 1 << 5,
    CM = 1 << 6,
    Gun = 1 << 7,
    Shield = 1 << 8,
    ShieldGenerator = 1 << 9,
    Thruster = 1 << 10,
    CargoPod = 1 << 11,
    CloakingDevice = 1 << 12,
    Cargo = 1 << 16, // commodities, ammo
    Engine = 1 << 17,
    Power = 1 << 18,
    Scanner = 1 << 19,
    TractorBeam = 1 << 20,
    RepairDroid = 1 << 21,
    InternalFX = 1 << 22,
    TradeLaneEquip = 1 << 23,
    Armor = 1 << 24,
};

struct IMPORT CacheString
{
        void clear();

    public:
        char* value;
};

struct IMPORT ID_String
{
        bool IsEmpty() const;
        void clear();
        const char* get_string() const;

    public:
        uint id;
        unsigned char data[128];
};

struct IObjInspect
{
    struct CargoEnumerator {};
    struct SubtargetEnumerator {};
    IObjInspectImpl* iObjInspectImpl;
};

struct IMPORT ActionDB
{
        ActionDB();
        ~ActionDB();
        ActionDB& operator=(const ActionDB&);
        void add(struct IAction*);
        IAction* find(const char*) const;
        void free();
        int get_action_count() const;
        bool remove(IAction*);
        void update(float);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT AmbientScriptInfo
{
        AmbientScriptInfo();
        ~AmbientScriptInfo();
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT AmbientScriptProperties
{
    public:
        AmbientScriptProperties();
        ~AmbientScriptProperties();
        AmbientScriptProperties& operator=(const AmbientScriptProperties&);
        void clear();
        void destroy();
        unsigned long get_key() const;
        void init(const struct AmbientScriptDescription&);
        void marshal(class MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT INI_Reader
{
    public:
        INI_Reader(const INI_Reader&);
        INI_Reader();
        ~INI_Reader();
        INI_Reader& operator=(const INI_Reader&);
        void close();
        bool find_header(const char*);
        bool get_bool(unsigned int);
        const char* get_file_name() const;
        const char* get_header_ptr();
        const char* get_indexed_value(unsigned int);
        int get_line_num() const;
        const char* get_line_ptr();
        const char* get_name() const;
        const char* get_name_ptr();
        unsigned int get_num_parameters() const;
        void get_state(struct State&) const;
        bool get_value_bool(unsigned int);
        float get_value_float(unsigned int);
        int get_value_int(unsigned int);
        const char* get_value_ptr();
        const char* get_value_string(unsigned int);
        const char* get_value_string();
        const unsigned short* get_value_wstring();
        Vector get_vector();
        bool is_end() const;
        bool is_header(const char*);
        bool is_number(const char*) const;
        bool is_value(const char*);
        bool is_value_empty(unsigned int);
        void log_link(const char*) const;
        bool open(const char*, bool);
        bool open_memory(const char*, unsigned int);
        bool read_header();
        bool read_value();
        void reset();
        void seek(unsigned int);
        void set_state(const State&);
        unsigned int tell() const;
        double value_num(unsigned int);

    public:
        unsigned char data[5480];
};

namespace AnimDB
{
    IMPORT void Add(int);
    IMPORT void Add(struct VChannel*);
    IMPORT unsigned int Count();
    IMPORT void Rem(int);
    IMPORT void Rem(const VChannel*);
    IMPORT void Shutdown();
    IMPORT void Update(float);
}; // namespace AnimDB

namespace PhyArch
{
    struct IMPORT Part
    {
            Part(const Part&);
            Part();
            ~Part();
            Part& operator=(const Part&);
            void clear();

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT const Part* GetDefaultPart();
    IMPORT bool LoadSurfaces(const char*, st6::map<unsigned int, Part, st6::less<unsigned int>, st6::allocator<Part>>&);
}; // namespace PhyArch

enum HpAttachmentType
{
    WEAPON = 3,
    Pointer = 4,
    hp_countermeasure_dropper = 9,
    hp_mine_dropper = 12,
    hp_gun_special_1 = 15,
    hp_gun_special_2 = 16,
    hp_gun_special_3 = 17,
    hp_gun_special_4 = 18,
    hp_gun_special_5 = 19,
    hp_gun_special_6 = 20,
    hp_gun_special_7 = 21,
    hp_gun_special_8 = 22,
    hp_gun_special_9 = 23,
    hp_turret_special_1 = 24,
    hp_turret_special_2 = 25,
    hp_turret_special_3 = 26,
    hp_turret_special_4 = 27,
    hp_turret_special_5 = 28,
    hp_turret_special_6 = 29,
    hp_turret_special_7 = 30,
    hp_turret_special_8 = 31,
    hp_turret_special_9 = 32,
    hp_turret_special_10 = 33,
    hp_thruster = 34,
    hp_torpedo_special_2 = 35,
    hp_fighter_shield_special_1 = 36,
    hp_fighter_shield_special_2 = 37,
    hp_fighter_shield_special_3 = 38,
    hp_fighter_shield_special_4 = 39,
    hp_fighter_shield_special_5 = 40,
    hp_fighter_shield_special_6 = 41,
    hp_fighter_shield_special_7 = 42,
    hp_fighter_shield_special_8 = 43,
    hp_fighter_shield_special_9 = 44,
    hp_fighter_shield_special_10 = 45,
    hp_elite_shield_special_1 = 46,
    hp_elite_shield_special_2 = 47,
    hp_elite_shield_special_3 = 48,
    hp_elite_shield_special_4 = 49,
    hp_elite_shield_special_5 = 50,
    hp_elite_shield_special_6 = 51,
    hp_elite_shield_special_7 = 52,
    hp_elite_shield_special_8 = 53,
    hp_elite_shield_special_9 = 54,
    hp_elite_shield_special_10 = 55,
    hp_freighter_shield_special_1 = 56,
    hp_freighter_shield_special_2 = 57,
    hp_freighter_shield_special_3 = 58,
    hp_freighter_shield_special_4 = 59,
    hp_freighter_shield_special_5 = 60,
    hp_freighter_shield_special_6 = 61,
    hp_freighter_shield_special_7 = 62,
    hp_freighter_shield_special_8 = 63,
    hp_freighter_shield_special_9 = 64,
    hp_freighter_shield_special_10 = 65,
    hp_torpedo_special_1 = 66,
};

struct IEngineInstance;

enum class StrafeDir
{
    None = 0,
    Left = 1,
    Right = 2,
    Up = 3,
    Down = 4,
};

struct IMPORT CollisionGroupDesc
{
        CollisionGroupDesc& operator=(const CollisionGroupDesc&);
        bool operator==(const CollisionGroupDesc&) const;
        bool operator!=(const CollisionGroupDesc&) const;
        bool operator<(const CollisionGroupDesc&) const;
        bool operator>(const CollisionGroupDesc&) const;

    public:
        unsigned short id;
        unsigned short unk;
        float health;
};

namespace Archetype
{
    class IMPORT FuseIgnitionList
    {
        public:
            uint dunno[4];
    };

    enum class ClassType
    {
        Root = 0,
        EqObj = 1,
        Solar = 2,
        Ship = 3,
        Asteroid = 4,
        DynamicAsteroid = 5,
        Equipment = 6,
        AttachedEquipment = 7,
        LootCrate = 8,
        CargoPod = 9,
        Commodity = 10,
        Power = 11,
        Engine = 12,
        Shield = 13,
        ShieldGenerator = 14,
        Thruster = 15,
        Launcher = 16,
        Gun = 17,
        MineDropper = 18,
        CounterMeasureDropper = 19,
        Scanner = 20,
        Light = 21,
        Tractor = 22,
        AttachedFxEquip = 23,
        InternalFxEquip = 24,
        RepairDroid = 25,
        RepairKit = 26,
        ShieldBattery = 27,
        CloakingDevice = 28,
        TradeLaneEquip = 29,
        Projectile = 30,
        Munition = 31,
        Mine = 32,
        CounterMeasure = 33,
        Armor = 34,
    };

    struct IMPORT Root
    {
            Root(const Root&);
            Root(struct IClObj*);
            virtual ~Root();
            const Root& operator=(const Root&);
            void AddRef();
            int GetRef() const;
            int Release();
            long create_instance(IEngineInstance*) const;
            long get_engine_index() const;
            unsigned int get_id() const;
            const PhyArch::Part* get_phy_part(unsigned int) const;
            int get_script_index() const;
            bool is_loaded() const;

            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);
            virtual bool load();
            virtual ClassType get_class_type() const;

        protected:
            void free_physical_representation();
            virtual void free_resources();
            bool init_physical_representation();

        public:
            /*  1 */ uint vtable;
            /*  2 */ uint archId;
            /*  3 */ char* name;
            /*  4 */ uint archType;
            /*  5 */ uint idsName;
            /*  6 */ uint idsInfo;
            /*  7 */ float hitPoints;
            /*  8 */ float mass;
            /*  9 */ uint explosionArchId;
            /* 10 */ float explosionResistance;
            /* 11x4 */ Vector rotationInertia;
            /* 14 */ bool hasRotationInertia;
            bool phantomPhysics;
            /* 15 */ uint dunno1;
            /* 16 */ uint dunno2;
            /* 17 */ void* anim;
            /* 18 */ uint array[5]; // not sure about this.
    };

    struct IMPORT Equipment : public Root
    {
            Equipment(const Equipment&);
            Equipment(IClObj*);
            virtual ~Equipment();
            Equipment& operator=(const Equipment&);

            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);
            virtual bool load();
            virtual ClassType get_class_type() const;
            virtual void free_resources();
            virtual HpAttachmentType get_hp_type() const;
            virtual Equipment* get_loot_appearance();
            virtual struct CargoPod* get_pod_appearance();
            virtual bool is_attached() const;

        public:
            /* 23 */ float volume;
            /* 24 */ uint useCount;
            /* 25 */ uint unitsPerContainer;
            /* 26 */ uint tractoredExplosionId;
            /* 27 */ uint lootable;
    };

    struct IMPORT EqObj : Root
    {
            EqObj(const EqObj&);
            EqObj(IClObj*);
            virtual ~EqObj();
            const EqObj& operator=(const EqObj&);
            bool dock_terminal_valid(int) const;
            virtual ClassType get_class_type() const;
            const struct CollisionGroup* get_group_by_id(unsigned short) const;
            const CollisionGroup* get_group_by_name(const CacheString&) const;
            bool get_undamaged_collision_group_list(st6::list<CollisionGroupDesc>&) const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);
            bool traverse_groups(const CollisionGroup*&) const;

        public:
            /* 23 */ CollisionGroup* collisionGroup;
            /* 24 */ ushort equipmentIdCounter;
            /* 25 */ uint dunno2;
            /* 26 */ uint dunno3;
            /* 27 */ uint dunno4; // something to do with shield link
            /* 28 */ uint dunno5;
            /* 29 */ uint dunno6;
            /* 30 */ uint dunno7;
            /* 31 */ uint dunno9;
            /* 32 */ bool isNomad;
            bool dockingCamera;
            /* 33 */ uint dunno10;
            /* 34 */ uint dunno11;
            /* 35 */ uint dunno12; // something to do with docking sphere
    };

    struct IMPORT AttachedEquipment : public Equipment
    {
            AttachedEquipment(const AttachedEquipment&);
            AttachedEquipment(IClObj*);
            virtual ~AttachedEquipment();
            AttachedEquipment& operator=(const AttachedEquipment&);
            virtual ClassType get_class_type() const;
            virtual bool is_attached() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ uint separationExplosionId;
            /* 29 */ uint debrisTypeId;
            /* 30 */ float childImpulse;
            /* 31 */ float parentImpulse;
            /* 32 */ char* hpChild;
            /* 33 */ int toughness;
    };

    struct IMPORT Armor : Equipment
    {
            Armor(const Armor&);
            Armor(IClObj*);
            virtual ~Armor();
            Armor& operator=(const Armor&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float hitPointsScale;
    };

    struct IMPORT Asteroid : Root
    {
            Asteroid(const Asteroid&);
            Asteroid(IClObj*);
            virtual ~Asteroid();
            Asteroid& operator=(const Asteroid&);
            virtual ClassType get_class_type() const;
            float get_detect_radius() const;
            float get_offset_dist() const;
            float get_recharge_time() const;
            virtual bool read(INI_Reader&);

        public:
            /* 23 */ float detectRadius;
            /* 24 */ float explosionOffset;
            /* 25 */ float rechargeTime;
    };

    struct IMPORT AttachedFXEquip : Equipment
    {
            AttachedFXEquip(const AttachedFXEquip&);
            AttachedFXEquip(IClObj*);
            virtual ~AttachedFXEquip();
            AttachedFXEquip& operator=(const AttachedFXEquip&);
            virtual ClassType get_class_type() const;

        public:
            // no fields here
    };

    struct IMPORT CargoPod : AttachedEquipment
    {
            CargoPod(const CargoPod&);
            CargoPod(IClObj*);
            virtual ~CargoPod();
            CargoPod& operator=(const CargoPod&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;

        public:
            // no fields here
    };

    struct IMPORT CloakingDevice : AttachedEquipment
    {
            CloakingDevice(const CloakingDevice&);
            CloakingDevice(IClObj*);
            virtual ~CloakingDevice();
            CloakingDevice& operator=(const CloakingDevice&);
            virtual ClassType get_class_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 34 */ float powerUsage;
            /* 35 */ float cloakInTime;
            /* 36 */ float cloakOutTime;
            /* 37 */ uint cloakInFxId;
            /* 38 */ uint cloakOutFxId;
    };


    struct IMPORT DamageObjInfo
    {
        DamageObjInfo(const DamageObjInfo&);
        DamageObjInfo();
        DamageObjInfo& operator=(const DamageObjInfo&);
        bool operator==(const DamageObjInfo&) const;
        bool operator!=(const DamageObjInfo&) const;
        bool operator<(const DamageObjInfo&) const;
        bool operator>(const DamageObjInfo&) const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT DamageObjInfoList
    {
    public:
        DamageObjInfoList(const DamageObjInfoList&);
        DamageObjInfoList();
        ~DamageObjInfoList();
        DamageObjInfoList& operator=(const DamageObjInfoList&);
        bool IsValid();

    public:
        bool dunno1;
        void* dunnoPtr; // 16 byte size
        uint dunno2;
    };

    struct IMPORT CollisionGroup
    {
            CollisionGroup(const CollisionGroup&);
            CollisionGroup();
            ~CollisionGroup();
            CollisionGroup& operator=(const CollisionGroup&);

        public:
            CollisionGroup* next;
            ushort id;
            CacheString name;
            uint type;
            uint hitPts;
            bool separable;
            bool destroyParent;
            bool rootHealthProxy;
            float parentImpulse;
            float mass;
            bool hasRotationInertia;
            Vector rotationInertia;
            uint separationExplosionArch;
            uint debrisTypeArch;
            float explosionResistance;
            DamageObjInfoList parentDmgObjInfoList;
            DamageObjInfoList groupDmgObjsInfoList;
            FuseIgnitionList FuseIgnitionList;
            EquipmentClass linkedEquipType;
            float linkedEquipDamage;
    };

    struct IMPORT Commodity : Equipment
    {
            Commodity(const Commodity&);
            Commodity(IClObj*);
            virtual ~Commodity();
            Commodity& operator=(const Commodity&);
            virtual ClassType get_class_type() const;
            float get_decay_per_second() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual Equipment* get_loot_appearance();
            virtual CargoPod* get_pod_appearance();
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float decayPerSecond;
            /* 29 */ uint lootAppearanceId;
            /* 30 */ uint podAppearanceId;
    };


    struct IMPORT DynamicAsteroid : Root
    {
            DynamicAsteroid(const DynamicAsteroid&);
            DynamicAsteroid(IClObj*);
            virtual ~DynamicAsteroid();
            DynamicAsteroid& operator=(const DynamicAsteroid&);
            virtual ClassType get_class_type() const;
            virtual bool read(INI_Reader&);

        public:
            // no fields
    };

    struct IMPORT Engine : Equipment
    {
            Engine(const Engine&);
            Engine(IClObj*);
            virtual ~Engine();
            Engine& operator=(const Engine&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float maxForce;
            /* 29 */ float linearDrag;
            /* 30 */ float powerUsage;
            /* 31 */ float cruisePowerUsage;
            /* 32 */ float cruiseChargeTime;
            /* 33 */ bool indestructible;
            /* 34 */ float reverseFraction;
    };

    struct Effect
    {
        Effect* prevEffect;
        Effect* nextEffect;
        uint archId;
        float lifetime; // -1.0 if skipped in config
    };

    struct IMPORT Explosion
    {
            Explosion(const Explosion&);
            Explosion(const ID_String&);
            ~Explosion();
            Explosion& operator=(const Explosion&);
            bool read(INI_Reader&);
            void reset();

        public:
            /*  0 */ uint id;
            /*  1 */ float radius;
            /*  2 */ float impulse;
            /*  3 */ float hullDamage;
            /*  4 */ float energyDamage;

            /*  5 */ uint processType;
            /*  6 */ float lifetime;
            /*  7 */ float lifetime2;
            /*  8 */ bool hasValidId;
            /*  9 */ Effect* effectPtr;
            /*  10 */ uint* dunno2;
            /*  11 */ float childNumPieces;
            /*  12 */ float debrisImpulse;
            /*  13 */ float innardsDebrisStartTime;
            /*  14 */ float innardsDebrisNum;
            /*  15 */ float innardsDebrisRadius;
            /*  16 */ bool hasValidId2;
            /*  17 */ uint* dunno4;
            /*  18 */ IObjInspect* innardsDebrisObject;
            /*  19 */ uint* dunno5;
            /*  20 */ bool hasValidId3;
            /*  21 */ uint* dunno6;
            /*  22 */ uint* dunno7;
            /*  23 */ uint* dunno8;
    };

    struct IMPORT MotorData
    {
            /*  0 */ uint vtable;
            /*  1 */ uint archId;
            /*  2 */ float delay;
            /*  3 */ float acceleration;
            /*  4 */ float lifetime;
    };

    struct IMPORT Launcher : public AttachedEquipment
    {
            Launcher(const Launcher&);
            Launcher(IClObj*);
            virtual ~Launcher();
            Launcher& operator=(const Launcher&);
            virtual ClassType get_class_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 34 */ float damagePerFire;
            /* 35 */ float powerUsage;
            /* 36 */ float refireDelay;
            /* 37 */ float muzzleVelocity;
            /* 38 */ uint projectileArchId;
            /* 39 */ char* useAnimation;
    };

    struct IMPORT Gun : public Launcher
    {
            Gun(const Gun&);
            Gun(IClObj*);
            virtual ~Gun();
            Gun& operator=(const Gun&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            HpAttachmentType get_hp_type_by_index(int) const;
            float get_munition_range() const;
            int get_number_of_hp_types() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 40 */ float dispersionAngle;
            /* 41 */ float turnRate;
            /* 42 */ float gunAzimuth[2];
            /* 44 */ float gunElevation[2];
            /* 46 */ bool useGunAzimuth;
            bool useGunElevation;
            bool autoTurret;
            /* 47 */ uint hpTypes[4]; // st6::vector?
    };

    struct IMPORT InternalFXEquip : Equipment
    {
            InternalFXEquip(const InternalFXEquip&);
            InternalFXEquip(IClObj*);
            virtual ~InternalFXEquip();
            InternalFXEquip& operator=(const InternalFXEquip&);
            virtual ClassType get_class_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ char* useAnimation;
    };

    struct IMPORT Light : Equipment
    {
            Light(const Light&);
            Light(IClObj*);
            virtual ~Light();
            Light& operator=(const Light&);
            virtual ClassType get_class_type() const;
            virtual bool read(INI_Reader&);

        public:
            /* 28 */ bool alwaysOn;
            bool dockingLight;
    };

    struct IMPORT LootCrate : Equipment
    {
            LootCrate(const LootCrate&);
            LootCrate(IClObj*);
            virtual ~LootCrate();
            LootCrate& operator=(const LootCrate&);
            virtual ClassType get_class_type() const;

        public:
            // no fields here
    };

    struct IMPORT MineDropper : Launcher
    {
            MineDropper(const MineDropper&);
            MineDropper(IClObj*);
            virtual ~MineDropper();
            MineDropper& operator=(const MineDropper&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;

        public:
            // no fields here
    };

    struct IMPORT Power : Equipment
    {
            Power(const Power&);
            Power(IClObj*);
            virtual ~Power();
            Power& operator=(const Power&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float capacity;
            /* 29 */ float chargeRate;
            /* 30 */ float thrustCapacity;
            /* 31 */ float thrustChargeRate;
    };

    struct IMPORT Projectile : Equipment
    {
            Projectile(const Projectile&);
            Projectile(IClObj*);
            virtual ~Projectile();
            Projectile& operator=(const Projectile&);
            virtual ClassType get_class_type() const;
            virtual Equipment* get_loot_appearance();
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float lifeTime;
            /* 29 */ float ownerSafeTime;
            /* 30 */ bool requiresAmmo;
            bool forceGunOri;
            /* 31 */ uint lootAppearanceId;
    };

    struct IMPORT CounterMeasure : Projectile
    {
            CounterMeasure(const CounterMeasure&);
            CounterMeasure(IClObj*);
            virtual ~CounterMeasure();
            CounterMeasure& operator=(const CounterMeasure&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 32 */ float linearDrag;
            /* 33 */ float range;
            /* 34 */ float diversionPercentage;
    };

    struct IMPORT CounterMeasureDropper : Launcher
    {
            CounterMeasureDropper(const CounterMeasureDropper&);
            CounterMeasureDropper(IClObj*);
            virtual ~CounterMeasureDropper();
            CounterMeasureDropper& operator=(const CounterMeasureDropper&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 40 */ float range;
    };

    struct Munition final : Projectile
    {
            IMPORT Munition(const Munition&);
            IMPORT Munition(IClObj*);
            IMPORT virtual ~Munition();
            IMPORT Munition& operator=(const Munition&);
            IMPORT static void FreeBeamArchIdx();
            IMPORT static void LoadBeamArchIdx();
            IMPORT virtual HpAttachmentType get_hp_type() const;
            IMPORT bool is_guided() const;
            IMPORT virtual bool load();
            IMPORT virtual bool read(INI_Reader&);
            IMPORT virtual void redefine(const Root&);
            ClassType get_class_type() const override { return ClassType::Munition; }

        protected:
            static long beamArchIndex;
            IMPORT virtual void free_resources();

        public:
            /* 32 */ float hullDamage;
            /* 33 */ float energyDamage;
            /* 34 */ uint weaponTypeId;
            /* 35 */ uint motorId;
            /* 36 */ uint seeker; // 2 = lock, dumb = 1, ? = 0
            /* 37 */ float timeToLock;
            /* 38 */ float seekerRange;
            /* 39 */ float seekerFovDeg;
            /* 40 */ float maxAngularVelocity;
            /* 41 */ float detonationDist;
            /* 42 */ uint hpType;
            /* 43 */ bool cruiseDisruptor;
    };

    struct IMPORT Mine : Projectile
    {
            Mine(const Mine&);
            Mine(IClObj*);
            virtual ~Mine();
            Mine& operator=(const Mine&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 32 */ float linearDrag;
            /* 33 */ float detonationDist;
            /* 34 */ float seekerDist;
            /* 35 */ float acceleration;
            /* 36 */ float topSpeed;
    };

    struct IMPORT RepairDroid : Equipment
    {
            RepairDroid(const RepairDroid&);
            RepairDroid(IClObj*);
            virtual ~RepairDroid();
            RepairDroid& operator=(const RepairDroid&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float repairRate;
    };

    struct IMPORT Scanner final : Equipment
    {
            Scanner(const Scanner&);
            Scanner(IClObj*);
            virtual ~Scanner();
            Scanner& operator=(const Scanner&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float powerUsage;
            /* 29 */ float range;
            /* 30 */ float cargoScanRange;
    };

    struct IMPORT Shield final : Equipment
    {
            Shield(const Shield&);
            Shield(IClObj*);
            virtual ~Shield();
            Shield& operator=(const Shield&);
            virtual ClassType get_class_type() const;

        public:
            /* 28 */ char* dunno1;
            /* 29 */ char* dunno2;
            /* 30 */ uint dunno3;
            /* 31 */ uint dunno4;
            /* 32 */ char* dunno5;
            /* 33 */ uint dunno6;
    };

    struct IMPORT ShieldBattery : Equipment
    {
            ShieldBattery(const ShieldBattery&);
            ShieldBattery(IClObj*);
            virtual ~ShieldBattery();
            ShieldBattery& operator=(const ShieldBattery&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual Equipment* get_loot_appearance();
            virtual bool read(INI_Reader&);

        public:
            /* 28 */ uint lootAppearanceId;
    };

    struct IMPORT RepairKit final : ShieldBattery
    {
            RepairKit(const RepairKit&);
            RepairKit(IClObj*);
            virtual ~RepairKit();
            RepairKit& operator=(const RepairKit&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual Equipment* get_loot_appearance();
            virtual bool read(INI_Reader&);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    struct ShieldGenerator final : public AttachedEquipment
    {
            IMPORT ShieldGenerator(const ShieldGenerator&);
            IMPORT ShieldGenerator(IClObj*);
            IMPORT virtual ~ShieldGenerator();
            IMPORT ShieldGenerator& operator=(const ShieldGenerator&);
            IMPORT virtual HpAttachmentType get_hp_type() const;
            IMPORT HpAttachmentType get_hp_type_by_index(int) const;
            IMPORT int get_number_of_hp_types() const;
            IMPORT virtual bool read(INI_Reader&);
            IMPORT virtual void redefine(const Root&);
            ClassType get_class_type() const override { return ClassType::ShieldGenerator; }

        public:
            /* 34 */ uint hpType;
            /* 35 */ uint shieldTypeId;
            /* 36 */ float regenerationRate;
            /* 37 */ float maxCapacity;
            /* 38 */ float constantPowerDraw;
            /* 39 */ float rebuildPowerDraw;
            /* 40 */ float offlineThreshold;
            float offlineRebuildTime;
            /* 41 */ uint hpShieldType[4]; // std6::vector?
    };

    struct IMPORT ShieldLink final
    {
            ShieldLink(const ShieldLink&);
            ShieldLink();
            ~ShieldLink();
            ShieldLink& operator=(const ShieldLink&);

        public:
            unsigned char data[0x18];
    };

    struct IMPORT Ship : EqObj
    {
            Ship(const Ship&);
            Ship(IClObj*);
            virtual ~Ship();
            Ship& operator=(const Ship&);
            static const int MAX_EXHAUST_NOZZLES;
            virtual ClassType get_class_type() const;
            const st6::vector<CacheString>* get_legal_hps(HpAttachmentType) const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 36 */ uint dunno12[19];
            /* 55 */ char* bayDoorAnim;
            /* 56 */ char* hpBaySurface;
            /* 57 */ char* hpBayExternal;
            /* 58 */ char* hpTractorSource;
            /* 59 */ uint idsInfo1;
            /* 60 */ uint idsInfo2;
            /* 61 */ uint idsInfo3;
            /* 62 */ uint shipClass;
            /* 63 */ uint numExhaustNozzles;
            /* 64 */ float holdSize;
            /* 65 */ float linearDrag;
            /* 66 */ Vector angularDrag;
            /* 69 */ Vector steeringTorque;
            /* 72 */ float nudgeForce;
            /* 73 */ float strafeForce;
            /* 74 */ float strafePowerUsage;
            /* 75 */ float maxBankAngle;
            uint dunno6[4]; // something about hptypes
            /* 80 */ uint maxNanobots;
            /* 81 */ uint maxShieldBats;
    };

    struct IMPORT Solar : public EqObj
    {
            Solar(const Solar&);
            Solar(IClObj*);
            virtual ~Solar();
            Solar& operator=(const Solar&);
            virtual ClassType get_class_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 37 */ bool destrutible;
            /* 38 */ float solarRadius;
            /* 39 */ uint toughness;
            /* 40 */ char* openAnim;
            /* 41 */ char* jumpOutHp;
            /* 42 */ uint loadoutId;
    };

    struct IMPORT Thruster : public AttachedEquipment
    {
            Thruster(const Thruster&);
            Thruster(IClObj*);
            virtual ~Thruster();
            Thruster& operator=(const Thruster&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 34 */ float powerUsage;
            /* 35 */ float maxForce;
    };

    struct IMPORT Tractor : public Equipment
    {
            Tractor(const Tractor&);
            Tractor(IClObj*);
            virtual ~Tractor();
            Tractor& operator=(const Tractor&);
            virtual ClassType get_class_type() const;
            virtual HpAttachmentType get_hp_type() const;
            virtual bool read(INI_Reader&);
            virtual void redefine(const Root&);

        public:
            /* 28 */ float maxLength;
            /* 29 */ float reachSpeed;
    };

    struct IMPORT TradeLaneEquip : public Equipment
    {
            TradeLaneEquip(const TradeLaneEquip&);
            TradeLaneEquip(IClObj*);
            virtual ~TradeLaneEquip();
            TradeLaneEquip& operator=(const TradeLaneEquip&);
            virtual ClassType get_class_type() const;

        public:
            // no new fields
    };

    IMPORT void EnumAsteroids(struct ArchEnumerator*);
    IMPORT void EnumDynamicAsteroids(ArchEnumerator*);
    IMPORT void EnumEquipment(ArchEnumerator*);
    IMPORT void EnumShips(ArchEnumerator*);
    IMPORT void EnumSimples(ArchEnumerator*);
    IMPORT void EnumSolars(ArchEnumerator*);
    IMPORT void Free();
    IMPORT void FreeExplosions();
    IMPORT int GetArchMaxHitPts(unsigned int);
    IMPORT Asteroid* GetAsteroid(unsigned int);
    IMPORT Asteroid* GetAsteroidByName(const ID_String&);
    IMPORT unsigned int GetAsteroidID(const ID_String&);
    IMPORT DynamicAsteroid* GetDynamicAsteroid(unsigned int);
    IMPORT DynamicAsteroid* GetDynamicAsteroidByName(const ID_String&);
    IMPORT unsigned int GetDynamicAsteroidID(const ID_String&);
    IMPORT Equipment* GetEquipment(unsigned int);
    IMPORT Equipment* GetEquipmentByName(const ID_String&);
    IMPORT unsigned int GetEquipmentID(const ID_String&);
    IMPORT Explosion* GetExplosion(const ID_String&);
    IMPORT unsigned int GetId(ClassType, unsigned int);
    IMPORT unsigned int GetIdCount(ClassType);
    IMPORT const struct MotorData* GetMotor(unsigned int);
    IMPORT Ship* GetShip(unsigned int);
    IMPORT Ship* GetShipByName(const ID_String&);
    IMPORT unsigned int GetShipID(const ID_String&);
    IMPORT Root* GetSimple(unsigned int);
    IMPORT Root* GetSimpleByName(const ID_String&);
    IMPORT unsigned int GetSimpleID(const ID_String&);
    IMPORT Solar* GetSolar(unsigned int);
    IMPORT Solar* GetSolarByName(const ID_String&);
    IMPORT unsigned int GetSolarID(const ID_String&);
    IMPORT unsigned short LargeIDToSmallID(unsigned int);
    IMPORT bool Load(struct IFileSystem*, long*, int*);
    IMPORT bool Load(const char*, long*, int*);
    IMPORT int LoadAsteroids(const char*, struct IClObjFactory*);
    IMPORT int LoadEquipment(const char*, bool, IClObjFactory*);
    IMPORT bool LoadExplosion(INI_Reader&, bool);
    IMPORT int LoadShips(const char*, bool, IClObjFactory*);
    IMPORT int LoadSimples(const char*, bool, IClObjFactory*);
    IMPORT int LoadSolar(const char*, bool, IClObjFactory*);
    IMPORT unsigned int SmallIdToLargeID(unsigned short);

}; // namespace Archetype

namespace Async
{
    struct IMPORT Action
    {
            Action(const Action&);
            Action(bool);
            virtual ~Action();

            static void* operator new(unsigned int);
            static void operator delete(void*);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT bool AddWork(Action*);
    IMPORT void DumpWorkQueue();
    IMPORT void Shutdown();
    IMPORT void Startup();
    IMPORT int WorkQueueSize();
}; // namespace Async

class IMPORT AttribStackNode
{
    public:
        AttribStackNode(const AttribStackNode&);
        AttribStackNode(enum Op);
        AttribStackNode();
        virtual ~AttribStackNode();
        AttribStackNode& operator=(const AttribStackNode&);
        virtual class RDLNode* Clone() const;
        virtual void Execute(class TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, struct VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        Op get_operation();
        void set_operation(Op);

        virtual operator AttribStackNode*();
        virtual operator const AttribStackNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT BaseData
{
    public:
        BaseData(const BaseData&);
        BaseData();
        ~BaseData();
        BaseData& operator=(const BaseData&);
        unsigned int get_base_id() const;
        const st6::list<class RoomData*>* get_const_room_data_list() const;
        const st6::map<unsigned int, struct MarketGoodInfo, st6::less<unsigned int>, st6::allocator<MarketGoodInfo>>* get_market() const;
        float get_price_variance() const;
        st6::list<RoomData*>* get_room_data_list();
        float get_ship_repair_cost() const;
        unsigned int get_start_location() const;
        void read_from_ini(const char*, unsigned int);
        void set_market_good(unsigned int, int, int, enum TransactionType, float, float, float);

    private:
        void read_Base_block(class INI_Reader*);
        void read_Room_block(INI_Reader*);

    public:
        uint dunno;
        float startRoom;
        float priceVariance;
        float shipRepairCost;
        st6::map<uint, MarketGoodInfo> marketMap;
};

class IMPORT BaseDataList
{
    public:
        BaseDataList(const BaseDataList&);
        BaseDataList();
        ~BaseDataList();
        BaseDataList& operator=(const BaseDataList&);
        BaseData* get_base_data(unsigned int) const;
        st6::list<BaseData*>* get_base_data_list();
        const st6::list<BaseData*>* get_const_base_data_list() const;
        RoomData* get_room_data(unsigned int) const;
        RoomData* get_unloaded_room_data(unsigned int) const;
        void load();
        void load_market_data(const char*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT BaseHint
{
        BaseHint(const BaseHint&);
        BaseHint();
        virtual ~BaseHint();
        BaseHint& operator=(const BaseHint&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

// Basically this forms a linked list between BaseWatchers all pointing to the same Watchable object.
// The Watchable object points to the last BaseWatcher which added it
struct IMPORT BaseWatcher
{
        BaseWatcher();
        ~BaseWatcher();
        BaseWatcher& operator=(const BaseWatcher&);
        void set(const struct Watchable*);

    protected:
        void set_pointer(const Watchable*);

    public:
        Watchable* watchable;
        BaseWatcher* nextBaseWatcher;
};

// The newestBaseWatcher pointer seems sometimes to be used with the address it points to -8 bytes to get the object
// This indicates it is probably some compiler construct
struct IMPORT Watchable
{
    Watchable();
    ~Watchable();
    Watchable& operator=(const Watchable&);
    unsigned int unwatch();

public:
    BaseWatcher* newestBaseWatcher; // The last basewatcher set to watch this
};

namespace BehaviorTypes
{
    IMPORT int get_behavior_id(const char*);
    IMPORT const char* get_behavior_name(int);
}; // namespace BehaviorTypes

class IMPORT BinaryRDLReader
{
        char Buf[1024];

    public:
        BinaryRDLReader(const BinaryRDLReader&);
        BinaryRDLReader();
        BinaryRDLReader& operator=(const BinaryRDLReader&);
        virtual bool extract_text_from_buffer(unsigned short*, unsigned int, unsigned int&, const char*, unsigned int);
        virtual bool read_buffer(class RenderDisplayList&, const char*, unsigned int);
        virtual bool read_file(RenderDisplayList&, const char*);
};

class IMPORT BinaryRDLWriter
{
        char Buf[1024];

    public:
        BinaryRDLWriter(const BinaryRDLWriter&);
        BinaryRDLWriter();
        BinaryRDLWriter& operator=(const BinaryRDLWriter&);
        virtual bool write_buffer(const RenderDisplayList&, char*, unsigned int, unsigned int&);
        virtual bool write_file(const RenderDisplayList&, const char*);
};

struct IMPORT DamageEntry
{
        enum class SubObjFate
        {
            Alive = 0,
            Damaged = 1,
            Destroyed = 2,
        };

        DamageEntry();
        DamageEntry& operator=(const DamageEntry&);
        bool operator==(const DamageEntry&) const;
        bool operator!=(const DamageEntry&) const;
        bool operator<(const DamageEntry&) const;
        bool operator>(const DamageEntry&) const;
        static const char* FateToString(SubObjFate);

    public:
        ushort subObj;
        float health;
        SubObjFate fate;
};

enum class DamageCause
{
    Unknown = 0x0,
    Collision = 0x1,
    Gun = 0x2,
    MissileTorpedo = 0x5,
    CruiseDisrupter = 0x6,
    Mine = 0x7,
    Suicide = 0x8,
    DummyDisrupter = 0xC0,
    UnkDisrupter = 0x15,
    Admin = 0x18
};

struct ExplosionDamageEvent
{
    uint victimId;
    uint attackerId;
    DamageCause dmgCause;
    Vector explosionPosition;
    Archetype::Explosion* explosionArchetype;
};

struct IMPORT DamageList
{
        DamageList(const DamageList&);
        DamageList();
        ~DamageList();
        DamageList& operator=(const DamageList&);
        static const char* DmgCauseToString(DamageCause);
        void add_damage_entry(unsigned short, float, DamageEntry::SubObjFate);
        DamageCause get_cause() const;
        float get_hit_pts_left(unsigned short) const;
        unsigned int get_inflictor_id() const;
        unsigned int get_inflictor_owner_player() const;
        bool is_destroyed() const;
        bool is_inflictor_a_player() const;
        void set_cause(DamageCause);
        void set_destroyed(bool);
        void set_inflictor_id(unsigned int);
        void set_inflictor_owner_player(unsigned int);

    public:
        st6::list<DamageEntry> damageEntries;
        bool isDestroyed;
        DamageCause damageCause;
        uint inflictorId;
        uint inflictorPlayerId;
};

class IMPORT CArchGroup
{
    public:
        CArchGroup(const Archetype::CollisionGroup&, struct CEqObj* const);
        ~CArchGroup();
        const ID_String& DebrisTypeName() const;
        bool DestroysParent() const;
        float ExplosionGroupImpulse() const;
        float ExplosionParentImpulse() const;
        float ExplosionResistance() const;
        const ID_String& ExplosionTypeName() const;
        const Archetype::FuseIgnitionList& FuseIgnitions() const;
        bool GetCenterOMass(Vector&) const;
        void GetCollisionGroupDesc(struct CollisionGroupDesc&) const;
        unsigned int GetCollisionGroupType() const;
        DamageEntry::SubObjFate GetFate() const;
        float GetHitPoints() const;
        unsigned short GetID() const;
        float GetMaxHitPoints() const;
        bool GetRadius(float&) const;
        float GetRelativeHealth() const;
        long GetRootIndex() const;
        bool GetVelocity(Vector&) const;
        const Archetype::DamageObjInfoList& GroupDamageObjs() const;
        int InstDepthInGroup(long) const;
        bool IsDead() const;
        bool IsDestroyed() const;
        bool IsInstInGroup(long) const;
        bool IsRootHealthProxy() const;
        void Kill(DamageEntry::SubObjFate);
        float LinkedEquipmentDamage() const;
        unsigned int LinkedEquipmentType() const;
        const CacheString& Name() const;
        const Archetype::DamageObjInfoList& ParentDamageObjs() const;
        struct CObject* RetreiveDestroyedObj();
        bool Separable() const;
        void SetHitPoints(float);
        void SetRelativeHealth(float);

    protected:
        void AttachDamageObjs(CObject*, const Archetype::DamageObjInfoList&) const;
        void Destroy();
        void FreeDamageObjs();
        void GetBoundingSphere(float&, Vector&) const;
        void LoadDamageObjs();

    public:
        /* 0  */ CEqObj* owner;
        /* 1  */ Archetype::CollisionGroup* colGrp;
        /* 2  */ int rootIndex;
        /* 3  */ float hitPts;
        /* 4  */ uint dunno;
        /* 5  */ uint state;
        /* 6  */ DamageEntry::SubObjFate fate;
        /* 7  */ CObject* destroyedObj;
        /* 8  */ bool boundingSphereInitialized;
        /* 9  */ float boundingSphereRadius;
        /* 10 */ Vector boundingSphere;
};

class IMPORT CArchGroupManager
{
    public:
        CArchGroupManager(const CArchGroupManager&);
        CArchGroupManager();
        ~CArchGroupManager();
        CArchGroupManager& operator=(const CArchGroupManager&);
        bool AddNewArchGroup(CArchGroup*);
        int Clear();
        bool DeleteArchGroup(unsigned short);
        bool DestroyDeadGroups();
        bool DestroyGroups(const DamageList&, bool);
        CArchGroup* FindByID(unsigned short);
        const CArchGroup* FindByID(unsigned short) const;
        CArchGroup* FindByName(const CacheString&);
        const CArchGroup* FindByName(const CacheString&) const;
        bool Init(CEqObj*);
        unsigned short InstToSubObjID(long) const;
        bool IsOnMap(unsigned short, bool) const;
        int NumLiving() const;
        int Size() const;
        CArchGroup* Traverse(class CArchGrpTraverser&);
        const CArchGroup* Traverse(CArchGrpTraverser&) const;

    protected:
        void DestroyDeadGroup(CArchGroup&);
        void DestroyLowerGroups(const CArchGroup&);
        static const int MAX_GROUP_DEPTH;

    public:
        uint dunno0; // 0
        bool dunno4; // 4
        uint dunno8; // 8
        uint dunno12; // 12
        uint dunno16; // 16
        char size; // 20
        bool dunno21; // 21
};

class IMPORT CArchGrpTraverser
{
    public:
        CArchGrpTraverser();
        CArchGrpTraverser& operator=(const CArchGrpTraverser&);
        void Restart();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct ISpatialPartition;

namespace CmnAsteroid
{
    struct LootableZone;
}

namespace Universe
{
    struct IBase
    {
            uint dunno1;
            uint baseId;
            uint dunno2;
            uint baseIdS;
            uint dunno3;
            uint systemId;
            uint dunno4[4];
            ulong spaceObjId;
            uint dunno5[10];
    };
    struct IMPORT ISystem
    {
            void* pvtable;
            void* pvftable;           // CommReferrable
            size_t msgIdPrefixLength; // TString<64>
            char msgIdPrefixStr[64];

            uint id;              // Id_String
            const char* nickname; // CacheString
            st6::vector<ISystem*> connections;
            uchar visit;
            uint idsName;
            uint idsInfo;
            const char* file; // CacheString
            Vector navMapPos;
            st6::list<struct IZone*> zones; // st6::list
            ISpatialPartition* spatial;
            float navMapScale;
            uint spaceMusicHash;
    };
    struct IMPORT IZone
    {
            struct FactionSpawn
            {
                    uint faction; // Faction Id, obtainable with e.g. pub::Reputation::GetReputationGroup()
                    float chance; // Spawn chance
            };

            void* vtable;
            long mesh;
            float edgeFraction;
            long unused1; // -1
            float dragModifier;
            float damage;
            float interference;
            float unused2;         // -1
            ID_String music;       // ID_String
            CacheString spaceDust; // CacheString
            int spaceDustMaxParticles;
            float fogColor[3]; // an RGB type
            uint startFaction;
            bool pathLabel;
            uint countMaxFaction;
            st6::list<FactionSpawn> factionSpawns; // st6::weighted_vector<FactionSpawn> factionSpawns;

            BYTE visit;
            uint idsName;
            uint idsInfo;
            uint iDunno5[2];
    };

    IMPORT ISystem* GetFirstSystem();
    IMPORT IBase* GetNextBase();
    IMPORT ISystem* GetNextSystem();
    IMPORT void Shutdown();
    IMPORT bool Startup(const char*);
    IMPORT const IZone* first_zone(unsigned int);
    IMPORT IBase* __cdecl GetFirstBase();
    IMPORT IBase* __cdecl GetNextBase();
    IMPORT unsigned int __cdecl get_base_id(const char*);
    IMPORT IBase* get_base(unsigned int);
    IMPORT unsigned int get_base_id(const char*);
    IMPORT void get_filename(char*, const char*);
    IMPORT unsigned int get_gate_system(unsigned int);
    IMPORT IZone* get_non_const_zone(unsigned int, unsigned int);
    IMPORT IZone* get_non_const_zone(unsigned int, const char*);
    IMPORT const ISystem* get_system(unsigned int);
    IMPORT unsigned int get_system_id(const char*);
    IMPORT const IZone* get_zone(unsigned int);
    IMPORT const IZone* get_zone(unsigned int, const char*);
    IMPORT const IZone* next_zone(const IZone*);
    IMPORT unsigned int num_bases();
    IMPORT unsigned int num_systems();

}; // namespace Universe

namespace Exclusion
{
    struct IMPORT AsteroidExclusionZone
    {
            AsteroidExclusionZone();
            ~AsteroidExclusionZone();
            AsteroidExclusionZone& operator=(const AsteroidExclusionZone&);
            const Universe::IZone* get_zone();
            bool set_zone(const Universe::IZone*, const Universe::IZone*);
            void update_dist(const Vector&);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT AsteroidExclusionZoneMgr
    {
        public:
            AsteroidExclusionZoneMgr(const AsteroidExclusionZoneMgr&);
            AsteroidExclusionZoneMgr();
            ~AsteroidExclusionZoneMgr();
            AsteroidExclusionZoneMgr& operator=(const AsteroidExclusionZoneMgr&);
            AsteroidExclusionZone* back();
            int get_max_billboard_count();
            virtual bool is_excluded(const Vector&, enum ExcludeObjectType, void*);
            void normalize_billboard_density(int);
            virtual void push_back(const Universe::IZone*, const Universe::IZone*);
            void set_max_cliasteroid_exclusion_distance(float);
            void set_max_dynamicasteroid_exclusion_distance(float);
            virtual void sort(void*);

        private:
            bool is_billboard_excluded(const Vector&, float*);
            bool is_cliasteroid_excluded(const Vector&, float*);
            bool is_cmnasteroid_excluded(const Vector&, float*);
            bool is_dynamic_asteroid_excluded(const Vector&);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    struct IMPORT NebulaExclusionZone
    {
            NebulaExclusionZone();
            ~NebulaExclusionZone();
            NebulaExclusionZone& operator=(const NebulaExclusionZone&);
            float get_fog_far();
            const Universe::IZone* get_zone();
            ID_String get_zone_shell_name();
            void set_fog_far(float);
            bool set_zone(const Universe::IZone*, const Universe::IZone*);
            void set_zone_shell_name(const char*);
            void update_dist(const Vector&);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT NebulaExclusionZoneMgr
    {
        public:
            NebulaExclusionZoneMgr(const NebulaExclusionZoneMgr&);
            NebulaExclusionZoneMgr();
            ~NebulaExclusionZoneMgr();
            NebulaExclusionZoneMgr& operator=(const NebulaExclusionZoneMgr&);
            NebulaExclusionZone* back();
            virtual bool is_excluded(const Vector&, ExcludeObjectType, void*);
            bool is_in_exclusion_zone(const Vector&, NebulaExclusionZone**, float*, bool);
            virtual void push_back(const Universe::IZone*, const Universe::IZone*);
            void set_max_distance(float);
            virtual void sort(void*);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

}; // namespace Exclusion

namespace CmnAsteroid
{
    struct LootableZone
    {
            ulong asteroidLootContainer; // not used
            ulong dynamicLootContainer;
            ulong asteroidLootCommodity; // not used
            ulong dynamicLootCommodity;
            ulong asteroidLootCount1; // not used
            ulong asteroidLootCount2; // not used
            ulong dynamicLootCount1;  // min 1
            ulong dynamicLootCount2;
            ulong asteroidLootDifficulty; // not used
            ulong dynamicLootDifficulty;  // default 1, maximum 100
    };

    class IMPORT CAsteroidCube
    {
        public:
            CAsteroidCube(const CAsteroidCube&);
            CAsteroidCube(class CAsteroidField*);
            ~CAsteroidCube();
            CAsteroidCube& operator=(const CAsteroidCube&);
            struct asteroid_marker* get_changes();
            unsigned long get_id();
            Matrix get_orient();
            Vector get_pos();
            enum CubeState get_state();
            void init(const Vector&, unsigned long, struct AsteroidCubeArch*, const struct AxisRotations&, float);
            void set_size(int);
            void set_state(CubeState);
            void set_system(unsigned int);

        private:
            bool compute_asteroid_id(const Vector&, unsigned long&);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT CAsteroidField
    {
        public:
            CAsteroidField(const CAsteroidField&);
            CAsteroidField();
            ~CAsteroidField();
            CAsteroidField& operator=(const CAsteroidField&);
            int AddRef();
            int Release();
            Vector closest_cube_pos(const Vector&);
            unsigned long create_cube_id(const Vector&);
            CAsteroidCube* find_cube(unsigned long);
            void flush_changes();
            AxisRotations& get_axis_rotations();
            asteroid_marker* get_changes();
            int get_cube_size();
            Exclusion::AsteroidExclusionZoneMgr* get_exclusion_mgr();
            float get_immersion(const Vector&);
            const Universe::IZone* get_lootable_zone(const Vector&) const;
            void load(INI_Reader&, int);
            bool near_field(const Vector&);
            float near_field_fraction(const Vector&, float);
            void populate_asteroids(const Vector&, const Vector&);
            void set_cube_size(int);
            void set_empty_freq(float);
            void set_fill_dist(int);
            void set_system(unsigned int);
            void set_zone(const Universe::IZone*);

        private:
            void populate_asteroids_internal(const Vector&, const Vector&, float);
            void update(float);

        public:
            uint dunno[10];
            /* 10 */ Universe::IZone* zone;
            /* 11 */ uint dunno4;
            /* 12 */ Exclusion::AsteroidExclusionZoneMgr* exclusionZoneMgr;
            /* 13 */ uint dunno1;
            /* 14 */ uint dunno2;
            /* 15 */ uint dunno3;
            /* 16 */ uint systemId;
            /* 17 */ int cubeSize;
            /* 18 */ int fillDist;
            /* 19 */ float emptyFreq;
            // This is probably a Matrix? // TODO: Test the type @Nen
            /* 20 */ float rotX[4];
            /* 24 */ float rotY[4];
            /* 28 */ float rotZ[4];
    };

    class IMPORT CAsteroidSystem
    {
        public:
            CAsteroidSystem(const CAsteroidSystem&);
            CAsteroidSystem();
            ~CAsteroidSystem();
            CAsteroidSystem& operator=(const CAsteroidSystem&);
            int AddRef();
            CAsteroidField* FindFirst();
            CAsteroidField* FindNext();
            int Release();
            CAsteroidField* create_field();
            unsigned int get_sys_id();
            void set_sys_id(unsigned int);
            void update(struct IObjDB*, float);

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT CAsteroidField* CreateAsteroidField(unsigned int);
    IMPORT CAsteroidSystem* Find(unsigned int);
    IMPORT int Load(unsigned int);
    IMPORT int Unload(unsigned int);
    IMPORT void Update(struct IObjDB*, float);
    IMPORT int closest_cube_coord(int, int, int);
    IMPORT unsigned long compute_cube_id(const Vector&);
    IMPORT bool compute_cube_orientation(unsigned long, Matrix*, const struct AxisRotations&, float);
}; // namespace CmnAsteroid

struct INotify
{
        enum Event;
};

class IMPORT IVP_Core;

class IMPORT IVP_Event_Sim;

template <class T>
class IMPORT IVP_U_Vector;

enum IVP_CONTROLLER_PRIORITY;

struct CObject;

namespace PhySys
{
    struct CreateParms;

    struct CollisionEvent
    {
            CObject* a;
            CObject* b;
            uint dunno1[2];
            Vector position;
            Vector normal;
            Vector velocity;
    };

    struct IMPORT RayHit
    {
            CObject* collision_object;
            Vector collision_position;
            Vector collision_velocity;
    };

    struct IMPORT Controller
    {
        public:
            virtual ~Controller();

            static void Register(Controller*, CObject*);
            static void UnRegister(Controller*);

            Controller(const Controller&);
            Controller();
            Controller& operator=(const Controller&);
            void push(const Vector&, float);
            void rotate(const Vector&, float);
            void wakeup();

        protected:
            virtual void core_is_going_to_be_deleted_event(IVP_Core*);
            // virtual float dunno_retn_1f(); //??
            virtual IVP_U_Vector<IVP_Core>* get_associated_controlled_cores();
            // virtual void create_instance(long); //??
            virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);
            virtual IVP_CONTROLLER_PRIORITY get_controller_priority();
    };

    class IMPORT PhyCollisionStateManager
    {
        public:
            PhyCollisionStateManager(const PhyCollisionStateManager&);
            PhyCollisionStateManager(CObject*);
            ~PhyCollisionStateManager();
            PhyCollisionStateManager& operator=(const PhyCollisionStateManager&);
            void enable_collisions(bool, bool);
            bool get_actual_collision_state() const;
            bool get_desired_collision_state() const;
            //@@@ int get_intruding_cobjs(bool,struct CheapSet<struct CObject *,struct st6::less<struct CObject *>> &);
            virtual void mindist_entered_volume(class IVP_Controller_Phantom*, class IVP_Mindist_Base*);
            virtual void mindist_left_volume(IVP_Controller_Phantom*, IVP_Mindist_Base*);
            virtual void phantom_is_going_to_be_deleted_event(IVP_Controller_Phantom*);
            void update(float);

        protected:
            class IVP_Real_Object* get_other_object(IVP_Mindist_Base*);
            CObject* mindist_to_cobject(IVP_Mindist_Base*);

        public:
            CObject* cobject;
            unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT float ANOM_LIMITS_MAX_ANGULAR_VELOCITY_PER_PSI;
    IMPORT float ANOM_LIMITS_MAX_VELOCITY;
    IMPORT void AddImpulseAtPoint(CObject*, const Vector&, const Vector&);
    IMPORT void AddToAngularVelocityOS(CObject*, const Vector&);
    IMPORT void AddToVelocity(CObject*, const Vector&);
    IMPORT void AngularImpulse(CObject*, const Vector&, float);
    IMPORT void AngularImpulseOS(CObject*, const Vector&, float);
    IMPORT bool AnyActive();
    IMPORT void Attach(CObject*, CObject*);
    IMPORT int AttachPhantom(CObject*, void*);
    IMPORT float BULLET_LENGTH_FUDGE;
    IMPORT void BeamR(CObject*, const Vector&, const Matrix&, bool);
    IMPORT void BuildIVP_Real(CObject*, const CreateParms&);
    IMPORT void BuildIVP_Sphere(CObject*, float, const CreateParms&);
    IMPORT int CreatePhantom(const struct PhantomParms&, const PhyArch::Part&, void*&);
    IMPORT int CreatePhantom(const PhantomParms&, const Vector&, void*&);
    IMPORT int CreatePhantom(const PhantomParms&, float, void*&);
    IMPORT Vector DEFAULT_ANGULAR_DAMPING;
    IMPORT float DEFAULT_LINEAR_DAMPING;
    IMPORT void DeactivatePhysics(CObject*);
    IMPORT void DeactivatePhysicsR(CObject*);
    IMPORT void DestroyPhantom(void*);
    IMPORT void Detach(CObject*, const struct DetachParms&);
    IMPORT int DetachPhantom(void*);
    IMPORT int FindRayCollisions(unsigned int system, const Vector& origin, const Vector& end, RayHit* rh, int rh_count);
    IMPORT int FindRayIntersect(CObject*, const Vector&, const Vector&, RayHit*, int);
    IMPORT int FindSphereCollisions(unsigned int, const Vector&, float, CObject**, int);
    IMPORT float GOLEM_ANGULAR_DAMP_FACTOR;
    IMPORT Vector GOLEM_CHILD_ANGULAR_DAMP;
    IMPORT float GOLEM_CHILD_LINEAR_DAMP;
    IMPORT float GOLEM_CHILD_MASS;
    IMPORT float GOLEM_DAMP_FACTOR;
    IMPORT float GOLEM_DELTA_ORIENTATION;
    IMPORT float GOLEM_FORCE_FACTOR;
    IMPORT float GOLEM_MAX_DELTA_POSITION;
    IMPORT float GOLEM_MAX_TORQUE;
    IMPORT Vector GOLEM_MAX_TRANSLATION_FORCE;
    IMPORT float GOLEM_TORQUE_FACTOR;
    IMPORT void GenerateCollisions(struct CBeam*);
    IMPORT Vector GetAngularVelocityOS(const CObject*);
    IMPORT Vector GetCenterOMass(const CObject*);
    IMPORT bool GetClosestPhantomIntruderPos(void*, unsigned int, unsigned int, struct CSimple*&, Vector&);
    IMPORT const char* GetCollisionGroup(const CObject*);
    IMPORT bool GetCollisionState(const CObject*);
    IMPORT bool GetCollisionStatePhantom(void* const);
    IMPORT void GetCollisions(unsigned int, const CollisionEvent*&, const CollisionEvent*&);
    IMPORT class IVP_Time GetCurrentTime(unsigned int);
    IMPORT void GetDamping(const CObject*, float&, Vector&);
    IMPORT float GetMass(const CObject*);
    IMPORT Vector GetMomentOInertia(const CObject*);
    IMPORT float GetRadiusR(const CObject*, bool, Vector&);
    IMPORT Vector GetVelocity(const CObject*);
    IMPORT void LinearImpulse(CObject*, const Vector&, float);
    IMPORT double MATERIAL_ELASTICITY;
    IMPORT double MATERIAL_FRICTION;
    IMPORT int MAX_SPAWNED_MINDIST_COUNT;
    IMPORT double MIN_TIME_BETWEEN_COLLISIONS;
    IMPORT unsigned int MovingObjectCount(unsigned int);
    IMPORT float PHYSICAL_SIM_RATE;
    IMPORT void RCBegin(CSimple*, const Vector&, const Vector&, const Quaternion&, const Vector&);
    IMPORT void RCEnd(CSimple*);
    IMPORT void RCSet(CSimple*, const Vector&, const Quaternion&, double);
    IMPORT float RC_MAX_DELTA_ORIENTATION;
    IMPORT float RC_MAX_DELTA_POSITION;
    IMPORT float RMGR_LOOK_AHEAD_MAX_DISTANCE_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MAX_DISTANCE_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_MAX_RADIUS_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MAX_RADIUS_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_MIN_DISTANCE_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MIN_DISTANCE_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_MIN_SECONDS_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_MIN_SECONDS_WORLD;
    IMPORT float RMGR_LOOK_AHEAD_TIME_INTRA;
    IMPORT float RMGR_LOOK_AHEAD_TIME_WORLD;
    IMPORT void ReMakePhysicalR(CObject*, const CreateParms&, float);
    IMPORT void SetCollisionGroup(CObject*, const char* const);
    IMPORT void SetCollisionState(CObject*, bool);
    IMPORT void SetCollisionStatePhantom(void*, bool);
    IMPORT void SetDamping(CObject*, float, const Vector&);
    IMPORT void SetMass(CObject*, float);
    IMPORT void SetMomentOInertia(CObject*, const Vector&);
    IMPORT void Shutdown(unsigned int);
    IMPORT void Startup(unsigned int);
    IMPORT void UnMakePhysicalR(CObject*);
    IMPORT void Update(unsigned int, float);
    IMPORT void Wakeup(CObject*);
    IMPORT enum IVP_BOOL (*m_pCollisionFilter)(class IVP_Real_Object*, class IVP_Real_Object*);
}; // namespace PhySys

struct IMPORT EngineObject
{
    public:
        virtual void __stdcall initialize_instance(long);                       //0
        virtual void __stdcall create_instance(long);                           //4
        virtual void __stdcall destroy_instance(long);                          //8
        virtual void __stdcall set_position(long, const Vector&);               //12
        virtual const Vector& __stdcall get_position(long) const;               //16
        virtual void __stdcall set_orientation(long, const Matrix&);            //20
        virtual const Matrix& __stdcall get_orientation(long) const;            //24
        virtual void __stdcall set_transform(long, const class Transform&);     //28
        virtual const Transform& __stdcall get_transform(long) const;           //32
        virtual void __stdcall get_centered_radius(long, float*, Vector*) const;//36
        virtual void __stdcall set_centered_radius(long, float, const Vector&); //40
        virtual void __stdcall set_instance_flags(long, unsigned long);         //44
        virtual unsigned long __stdcall get_instance_flags(long) const;         //48
        virtual bool __stdcall joint_changed(long);                             //52
        virtual ~EngineObject();                                                //56
        virtual const Vector& __stdcall get_velocity(long) const;               //60
        virtual void __stdcall set_velocity(long, const Vector&);               //64
        virtual const Vector& __stdcall get_angular_velocity(long) const;       //68
        virtual void __stdcall set_angular_velocity(long, const Vector&);       //72

        EngineObject(const EngineObject&);
        EngineObject();
        EngineObject& operator=(const EngineObject&);
        const Matrix& get_orientation() const;
        const Vector& get_position() const;
        const float get_radius() const;
        const Transform& get_transform() const;
        void set_centered_radius(float, const Vector&);
        void set_orientation(const Matrix&);
        void set_position(const Vector&);
        void set_transform(const Transform&);
        void update_tree() const;

        void* index;         // 1 fetched in CBase::get_index()
        Matrix orientation;  // 2
        Vector position;     // 11
        float radius;        // 14
        Vector centerOfMass; // 15
        uint instanceFlags;  // 18
};

class IMPORT CSteering : public PhySys::Controller
{
    public:
        CSteering(const CSteering&);
        CSteering();
        virtual ~CSteering();
        CSteering& operator=(const CSteering&);
        bool Activate(bool);
        virtual bool EnableController();
        float GetAxisSteeringTorque(unsigned int, float) const;
        const Vector& GetAxisThrottle() const;
        bool IsActive() const;
        void SetAxisThrottle(const Vector&);
        void SetOwner(struct CShip*);

    protected:
        static const float AXIS_CHANGE_THRESHOLD;
        virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CStrafeEngine : public PhySys::Controller
{
    public:
        CStrafeEngine(const CStrafeEngine&);
        CStrafeEngine();
        virtual ~CStrafeEngine();
        CStrafeEngine& operator=(const CStrafeEngine&);
        virtual bool EnableController();
        StrafeDir GetStrafe() const;
        void SetOwner(CShip*);
        void SetStrafe(StrafeDir);

    protected:
        //@@@ virtual void do_simulation_controller(class IVP_Event_Sim *,class IVP_U_Vector<class IVP_Core> *);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CPhysControllerEquip : public PhySys::Controller
{
    public:
        virtual ~CPhysControllerEquip();
        virtual bool EnableController();
        virtual bool DisableController();
        virtual bool IsControllerEnabled() const;
        virtual bool ControlObject(CObject*);

        CPhysControllerEquip(const CPhysControllerEquip&);
        CPhysControllerEquip();
        CPhysControllerEquip& operator=(const CPhysControllerEquip&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CAttachmentObj
{
    public:
        virtual ~CAttachmentObj();

        CAttachmentObj(const CAttachmentObj&);
        CAttachmentObj();
        CAttachmentObj& operator=(const CAttachmentObj&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CBase
{
        virtual ~CBase();

        CBase(const CBase&);
        CBase();
        CBase& operator=(const CBase&);
        void advise(bool);
        void cobject(CObject*);
        CObject* cobject() const;
        long get_index() const;
        void notify_of_destruction(void*);

    public:
        CObject* cobj;
};

struct IMPORT CObject : public EngineObject
{
    public:
        virtual void __stdcall destroy_instance(long);                  //8
        virtual ~CObject();                                             //56
        virtual void open(Archetype::Root*);                            //76
        virtual int update(float, unsigned int);                        //80
        virtual Vector get_velocity() const;                            //84
        virtual Vector get_angular_velocity() const;                    //88
        virtual void disable_controllers();                             //92
        virtual void enable_controllers();                              //96
        virtual float get_physical_radius_r(Vector&) const;             //100
        virtual Vector get_center_of_mass() const;                      //104
        virtual float get_mass() const;                                 //108
        virtual bool get_surface_extents(Vector&, Vector&) const;       //112
        virtual void unmake_physical();                                 //116
        virtual void remake_physical(const PhySys::CreateParms&, float);//120
        virtual void beam_object(const Vector&, const Matrix&, bool);   //124

        enum Class
        {
            COBJECT_MASK = 0x1,
            CSIMPLE_MASK = 0x2 | COBJECT_MASK,
            CPROJECTILE_MASK = 0x4 | CSIMPLE_MASK,
            CEQOBJ_MASK = 0x100 | CSIMPLE_MASK,

            // CObject children
            CEQUIPMENT_OBJECT = 0x2000 | COBJECT_MASK,
            CDYNAMICASTEROID_OBJECT = 0x4000 | COBJECT_MASK,

            // CSimple children
            CLOOT_OBJECT = 0x800 | CSIMPLE_MASK,
            CASTEROID_OBJECT = 0x1000 | CSIMPLE_MASK,

            // CProjectile children
            CMINE_OBJECT = 0x8 | CPROJECTILE_MASK,
            CCOUNTERMEASURE_OBJECT = 0x10 | CPROJECTILE_MASK,
            CBEAM_OBJECT = 0x60 | CPROJECTILE_MASK,
            CGUIDED_OBJECT = 0xA0 | CPROJECTILE_MASK,

            // CEqObj children
            CSOLAR_OBJECT = 0x200 | CEQOBJ_MASK,
            CSHIP_OBJECT = 0x400 | CEQOBJ_MASK,
        };

        static CObject* Alloc(Class);
        static CObject* Find(const unsigned int&, Class);
        static CObject* Find(long, Class);
        static CObject* FindFirst(Class);
        static CObject* FindNext();
        static int Count(Class);
        static void ReleaseAll();
        static const unsigned int NoActions;
        static const unsigned int NoBehavior;
        static const unsigned int NoCountermeasureAi;
        static const unsigned int NoDynamics;
        static const unsigned int NoScanner;
        static const unsigned int UpdateDefault;
        static const unsigned int UpdateDumb;

        static void* operator new(unsigned int);
        static void operator delete(void*);

        CObject(const CObject&);
        CObject(Class);
        unsigned int AddRef();
        unsigned int Release();
        void add_impulse(const Vector&, const Vector&);
        void add_impulse(const Vector&);
        void advise(CBase*, bool);
        void enable_collisions_r(bool);
        bool flag_part_as_shield(unsigned int);
        Archetype::Root* get_archetype() const;
        Vector get_moment_of_inertia() const;
        float hierarchy_radius(Vector&) const;
        float hierarchy_radius() const;
        unsigned int inst_to_part(long) const;
        bool is_shield_part(unsigned int) const;
        long part_to_inst(unsigned int) const;

        Class objectClass; // 19
        uint system;       // 20
        uint dunnoCObject; // 21, relates to all PhySys calls, PhySys calls only occur if this value is nonzero
        struct SurfaceExtents
        {
                uint dunno[2];
                Vector min, max;
        };
        SurfaceExtents* surf; // 22

        uint dunnoCObject2; // 23 Parts related
        uint dunnoCObject3; // 24
        bool dunnoCObject4; // 25
        uint dunnoCObjectShield1; // 26 maybe just Parts related
        uint dunnoCObjectShield2; // 27
        uint dunnoCObject5; // 28
        uint dunnoCObject6; // 29
        bool dunnoCObject7; // 30
        void* unkListCObj; // 31 twodirectional list containing a single value
        uint unkListSize;  // 32
        PhySys::PhyCollisionStateManager* colStateManager; // 33
        Archetype::Root* archetype; // 34
        uint dunnoCObject8; // 35
        void* unkListCObj2; // 36 used in CObject::advise
        uint unkList2Size;  // 37
        uint referenceCounter; // 38
};

struct IMPORT CSimple : public CObject
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        virtual ~CSimple();                                             //56
        virtual void open(Archetype::Root*);                            //76
        virtual float get_physical_radius_r(Vector&) const;             //100
        virtual void unmake_physical();                                 //116
        virtual void beam_object(const Vector&, const Matrix&, bool);   //124
        virtual void init(const CreateParms&);                          //128
        virtual void cache_physical_props();                            //132
        virtual unsigned int get_name() const;                          //136
        virtual bool is_targetable() const;                             //140
        virtual void connect(struct IObjDB*);                           //144
        virtual void disconnect(struct IObjDB*);                        //148
        virtual void set_hit_pts(float);                                //152
        virtual void init_physics(const Vector&, const Vector&);        //156

        CSimple(const CSimple&);
        CSimple(Class);
        unsigned int GetOwnerPlayer() const;
        void SetOwnerPlayer(unsigned int);
        float get_hit_pts() const;
        const unsigned int& get_id() const;
        float get_max_hit_pts() const;
        struct IObjDB* get_object_database() const;
        float get_relative_health() const;
        float get_scanner_interference() const;
        unsigned int get_type() const;
        void update_zones(float, unsigned int);

        uint dunnoCSimple;    // 39
        uint dunnoTargetable; // 40
        uint dunnoScanner;    // 41
        uint dunnoCSimple3;   // 42
        struct IObjDB* objDB; // 43
        uint id;              // 44
        uint ownerPlayer;     // 45
        float hitPoints;      // 46
        uint dunnoCSimple4[0x5]; // 47
        Vector radiusCenter;  // 52
        float radiusCentered; // 55
        ObjectType type;      // 56
};

struct IMPORT CAsteroid : public CSimple
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        CAsteroid(const CAsteroid&);
        CAsteroid();
        virtual ~CAsteroid();
        const Archetype::Asteroid* asteroidarch() const;
        unsigned long get_asteroid_id();
        const CmnAsteroid::CAsteroidField* get_owner_field();
        virtual Vector get_velocity() const;
        void init(const CreateParms&);
        bool is_instant_kill();
        bool is_mine();
        void set_system(unsigned int);
        virtual int update(float, unsigned int);

    protected:
        virtual void init_physics(const Vector&, const Vector&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CProjectile : public CSimple
{
    public:
        struct IMPORT CreateParms
        {
                // CreateParms();
                CreateParms& operator=(const CreateParms&);

                uint hash;
                Archetype::Projectile* archetype;
                float dunno2;
                float startHealth; // -1 = max health
                Vector position;
                Matrix orientation;
                Vector velocity;
                float dunno3[4]; // always 0
                uint owner;
        };

        virtual ~CProjectile();                 //56
        virtual int update(float, unsigned int);//80
        virtual void init(const CreateParms&);  //160
        virtual void set_dead();                //164
        virtual void expire_safe_time();        //168

        CProjectile(const CProjectile&);
        CProjectile(Class);
        const unsigned int& get_owner() const;
        bool is_alive() const;
        bool is_owner_safe() const;
        const Archetype::Projectile* projarch() const;

        uint ownerId;                  //57
        float remainingLifetime;        //58
        float remainingOwnerSafeTime;   //59
};

class IMPORT CEquip
{
    public:
        virtual ~CEquip();                                      //0
        virtual bool IsActive() const;                          //4
        virtual bool IsDestroyed() const;                       //8
        virtual bool IsFunctioning() const;                     //12
        virtual bool IsDisabled() const;                        //16
        virtual bool IsTemporary() const;                       //20
        virtual bool CanDelete() const;                         //24
        virtual void NotifyArchGroupDestroyed(unsigned short);  //28
        virtual bool IsLootable() const;                        //32
        virtual bool Update(float, unsigned int);               //36
        virtual bool GetEquipDesc(struct EquipDesc&) const;     //40
        virtual void GetStatus(struct EquipStatus&) const;      //44
        virtual bool Activate(bool);                            //48
        virtual void Destroy();                                 //52
        virtual float GetMaxHitPoints() const;                  //56
        virtual float GetHitPoints() const;                     //60
        virtual void SetHitPoints(float);                       //64
        virtual float GetRelativeHealth() const;                //68
        virtual bool GetConnectionPosition(Vector*, Matrix*) const; //72
        virtual bool IsControllerEnabled();                     //76
        virtual bool EnableController();                        //80
        virtual bool DisableController();                       //84

        static void* operator new(unsigned int);
        static void operator delete(void*);

        CEquip();
        CEquip(const CEquip&);
        CEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);

        void ConnectClientEquip(INotify*);
        void ConnectServerEquip(INotify*);
        const Archetype::Equipment* EquipArch() const;
        unsigned short GetID() const;
        CEqObj* GetOwner() const;
        unsigned int GetType() const;
        const char* IdentifyEquipment() const;
        void Notify(INotify::Event, void*);
        void NotifyDisconnecting(INotify*);

        /* 1 */ CEqObj* owner;
        /* 2 */ ushort SubObjId;
        /* 3 */ Archetype::Equipment* archetype;
        /* 4 */ bool isActive;
                bool isDestroyed;
                bool isTemporary;
        /* 5 */ EquipmentClass CEquipType;
        /* 6 */ void* customWrapperClass2;
        /* 7 */ char* dunno;
};

class IMPORT CInternalEquip : public CEquip
{
    public:
        virtual ~CInternalEquip();
        virtual bool GetEquipDesc(EquipDesc&) const;

        static CInternalEquip* cast(CEquip*);
        static const CInternalEquip* cast(const CEquip*);

        CInternalEquip(const CInternalEquip&);
        CInternalEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);
};

class IMPORT CExternalEquip : public CEquip
{
    public:
        virtual ~CExternalEquip();
        virtual bool IsDestroyed() const;
        virtual bool Update(float, unsigned int);
        virtual bool GetEquipDesc(EquipDesc&) const;
        virtual void Destroy();
        virtual bool GetConnectionPosition(Vector*, Matrix*) const;
        virtual bool IsConnected() const;                               //88
        virtual bool Connect(const char*);                              //92
        virtual CacheString GetParentHPName() const;                    //96
        virtual long GetParentConnector(bool) const;                    //100
        virtual bool GetHardPointInfo(struct HardpointInfo&) const;     //104
        virtual bool GetVelocity(Vector&) const;                        //108
        virtual bool GetCenterOMass(Vector&) const;                     //112
        virtual void Disconnect();                                      //116

        static CExternalEquip* cast(CEquip*);
        static const CExternalEquip* cast(const CEquip*);

        CExternalEquip(const CExternalEquip&);
        CExternalEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);

        /* 8 */ char* mountedHardpoint;
        /* 9 */ long parentConnector;
};

class IMPORT CAttachedEquip : public CExternalEquip
{
    public:
        virtual ~CAttachedEquip();
        virtual bool Update(float, unsigned int);
        virtual float GetHitPoints() const;
        virtual void SetHitPoints(float);
        virtual bool IsConnected() const;
        virtual bool Connect(const char*);
        virtual bool GetVelocity(Vector&) const;
        virtual bool GetCenterOMass(Vector&) const;
        virtual void Disconnect();
        virtual int GetToughness() const;                               //120
        virtual bool GetRadius(float&) const;                           //124
        virtual bool IsInstOnEquip(long) const;                         //128
        virtual long GetRootIndex() const;                              //132
        virtual void SetFate(DamageEntry::SubObjFate);                  //136
        virtual void ComputeBoundingSphere(float&, Vector&) const;      //140

        static CAttachedEquip* cast(CEquip*);
        static const CAttachedEquip* cast(const CEquip*);

        CAttachedEquip(const CAttachedEquip&);
        CAttachedEquip(unsigned int, CEqObj*, unsigned short, const Archetype::Equipment*, bool);
        const Archetype::AttachedEquipment* AttachedEquipArch() const;
        CObject* GetPhysicsOwner() const;
        CObject* RetrieveDebrisObject();

    public:
        /* 10 */ void* physicsPtr; // either CPhysAttachment::`vftable' or CNonPhysAttachment::`vftable'
        /* 11 */ CObject debrisObject;
        /* 12 */ float hitPts;
        /* 13 */ DamageEntry::SubObjFate fate;
        /* 14 */ bool isBoundingSphereInitialized;
        /* 15 */ float boundingSphereRadius;
        /* 16-19 */ Vector boundingSphere;
};

enum class FireResult
{
    ObjectIsDestroyed = 0,
    ObjectIsDisabled = 1,
    RefireDelayNotElapsed = 2,
    AmmoRequirementsNotMet = 3,
    PowerRequirementsNotMet = 4,

    // Not sure what kind of failure
    Failure = 5,

    // Something to do with this? Not sure the exact reason
    FailureCruiseActive = 6,

    // Seems to be related to being in a tradelane, uncertain.
    FailureTradelane = 7,

    Dunno1 = 8,
    Success = 9,
};

class IMPORT CELauncher : public CAttachedEquip
{
    public:
        int dunno[28];
        float OfflineThreshold;
        float OfflineRebuildTime;
        float MaxCapacity;

        virtual ~CELauncher();
        virtual bool IsDisabled() const;
        virtual bool Update(float, unsigned int);
        virtual void GetStatus(EquipStatus&) const;
        virtual bool Connect(const char*);
        virtual void Disconnect();
        virtual FireResult Fire(const Vector&);
        virtual void ConsumeFireResources();
        virtual void ComputeLaunchInfo(st6::vector<struct ProjLaunchInfo>&, const Vector&) const;
        virtual float GetPowerDrawPerFire() const;
        virtual int GetAmmoCount() const;
        virtual bool AmmoNeedsMet() const;
        virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;
        virtual FireResult CanFire(const Vector&) const;
        virtual bool PowerNeedsMet() const;
        virtual void DrawPower(int);
        virtual void DrawAmmoFromCargo(int);
        virtual bool RefireDelayElapsed() const;

        CELauncher(const CELauncher&);
        CELauncher(unsigned int, CEqObj*, unsigned short, const Archetype::Launcher*, bool);
        void ComputeProjectilePosAndVelocity_OneBarrel(Vector&, Vector&, int, const Vector&) const;
        Vector GetAvgBarrelDirWS() const;
        Vector GetAvgBarrelPosWS() const;
        Vector GetBarrelDirWS(unsigned int) const;
        const struct Barrel* GetBarrelInfo(unsigned int) const;
        Vector GetBarrelPosWS(unsigned int) const;
        unsigned int GetProjectilesPerFire() const;
        const Archetype::Launcher* LauncherArch() const;
        const Archetype::Projectile* ProjectileArch() const;
        static CELauncher* cast(CEquip*);
        static const CELauncher* cast(const CEquip*);
};

struct IMPORT CBeam : public CProjectile
{
    public:
        virtual ~CBeam();
        virtual Vector get_velocity() const;
        virtual float get_mass() const;
        virtual void init_physics(const Vector&, const Vector&);
        virtual void expire_safe_time();

        CBeam(const CBeam&);
        CBeam(Class);
        const char* get_collision_group() const;
        const Vector& get_last_pos() const;
        void move(float);
        const Archetype::Munition* munitionarch() const;
        void set_velocity(const Vector&);
};

struct IMPORT CCounterMeasure : public CProjectile
{
    public:
        virtual ~CCounterMeasure();
        virtual int update(float, unsigned int);
        virtual void init_physics(const Vector&, const Vector&);
        virtual void expire_safe_time();

        CCounterMeasure(const CCounterMeasure&);
        CCounterMeasure(Class);
        const Archetype::CounterMeasure* countermeasure_arch();
};

class IMPORT CDeadReckonedVector
{
    public:
        CDeadReckonedVector(const CDeadReckonedVector&);
        CDeadReckonedVector();
        virtual ~CDeadReckonedVector();
        CDeadReckonedVector& operator=(const CDeadReckonedVector&);
        void AddSample(const Vector&, double);
        double CalcError(const Vector&);
        double ConvergeTime();
        void Doit(double);
        const Vector& GetProjectedPosition();
        const Vector& GetSample(int);
        void NormalizeProjectedPosition();
        void NormalizeTrackedPosition();
        Vector ProjectVelocity(double);
        void Reset();
        void SetMaxCorrectiveConvergeTime(double);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CDynamicAsteroid : public CObject
{
    public:
        virtual ~CDynamicAsteroid();
        virtual int update(float, unsigned int);
        virtual void init_physics(const Vector&, const Vector&, unsigned int);

        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        CDynamicAsteroid(const CDynamicAsteroid&);
        CDynamicAsteroid();
        const Archetype::DynamicAsteroid* dynamicAsteroidArch() const;
        void init(const CreateParms&);
};

class IMPORT CEArmor : public CInternalEquip
{
    public:
        virtual ~CEArmor();

        static CEArmor* cast(CEquip*);
        static const CEArmor* cast(const CEquip*);

        CEArmor(const CEArmor&);
        CEArmor(CEqObj*, unsigned short, const Archetype::Armor*, bool);
        const Archetype::Armor* ArmorArch() const;
};

class IMPORT CEAttachedFX : public CExternalEquip
{
    public:
        virtual ~CEAttachedFX();
        virtual void NotifyArchGroupDestroyed(unsigned short);

        static CEAttachedFX* cast(CEquip*);
        static const CEAttachedFX* cast(const CEquip*);

        CEAttachedFX(const CEAttachedFX&);
        CEAttachedFX(CEqObj*, unsigned short, const Archetype::AttachedFXEquip*, bool);
        const Archetype::AttachedFXEquip* FXArch() const;
};

class IMPORT CECargo : public CInternalEquip
{
    public:
        virtual ~CECargo();
        virtual bool IsDestroyed() const;
        virtual bool GetEquipDesc(EquipDesc&) const;
        virtual void Destroy();
        virtual float GetHitPoints() const;
        virtual void SetHitPoints(float);
        virtual unsigned int GetType() const;                       //88
        virtual void Init(float, unsigned int, const CacheString&); //92

        static CECargo* cast(CEquip*);
        static const CECargo* cast(const CEquip*);

        CECargo(const CECargo&);
        CECargo(CEqObj*, unsigned short, const Archetype::Equipment*, bool);
        void AddToStack(unsigned int, float);
        const class CECargoPod* GetContainer() const;
        unsigned int GetCount() const;
        float GetDecayDamagePerSecond() const;
        void RemoveFromStack(unsigned int);
        void SetCount(unsigned int);
};

class IMPORT CECargoPod : public CAttachedEquip
{
    public:
        virtual ~CECargoPod();
        virtual bool IsLootable() const;
        virtual void Destroy();

        static CECargoPod* cast(CEquip*);
        static const CECargoPod* cast(const CEquip*);

        CECargoPod(const CECargoPod&);
        CECargoPod(CEqObj*, unsigned short, const Archetype::CargoPod*, bool);
        void EmptyPod();
        void FillPod(CECargo*);
        const CECargo* GetContents() const;
};

class IMPORT CECloakingDevice : public CExternalEquip
{
    public:
        virtual ~CECloakingDevice();
        virtual bool Update(float, unsigned int);
        virtual bool Activate(bool);

        static CECloakingDevice* cast(CEquip*);
        static const CECloakingDevice* cast(const CEquip*);

        CECloakingDevice(const CECloakingDevice&);
        CECloakingDevice(CEqObj*, unsigned short, const Archetype::CloakingDevice*, bool);
        const Archetype::CloakingDevice* CloakArch() const;
        float cloak_percent() const;
};

class IMPORT CECounterMeasureDropper : public CELauncher
{
    public:
        virtual ~CECounterMeasureDropper();
        virtual bool Update(float, unsigned int);

        static CECounterMeasureDropper* cast(CEquip*);
        static const CECounterMeasureDropper* cast(const CEquip*);

        CECounterMeasureDropper(const CECounterMeasureDropper&);
        CECounterMeasureDropper(CEqObj*, unsigned short, const Archetype::CounterMeasureDropper*, bool);
        const Archetype::CounterMeasure* CounterMeasureArch();
        const Archetype::CounterMeasureDropper* CounterMeasureDropperArch();
};

class IMPORT CEEngine : public CInternalEquip, public CPhysControllerEquip
{
    public:
        virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

        virtual ~CEEngine();

        virtual bool EnableController();
        virtual bool DisableController();
        virtual bool IsControllerEnabled() const;

        virtual bool IsFunctioning() const;
        virtual void NotifyArchGroupDestroyed(unsigned short);
        virtual bool Update(float, unsigned int);
        virtual bool Activate(bool);

        static void BuildNozzleHPName(int, CacheString&);
        static CEEngine* cast(CEquip*);
        static const CEEngine* cast(const CEquip*);

        CEEngine(const CEEngine&);
        CEEngine(CShip*, unsigned short, const Archetype::Engine*, bool);
        bool EngageCruise(bool, bool);
        const Archetype::Engine* EngineArch() const;
        const st6::vector<struct ExhaustNozzleInfo>& NozzleInfos() const;
        float GetCruiseChargeTime() const;
        float GetCruiseChargeTimeElapsed() const;
        float GetCruiseDrag() const;
        float GetCruisePowerDraw() const;
        float GetCruiseThrust(float) const;
        float GetLinearDrag() const;
        float GetPowerDraw(float) const;
        float GetThrust(float) const;
        bool IsCruiseEngaged() const;
};

class IMPORT CEGun : public CELauncher
{
    public:
        virtual ~CEGun();
        virtual bool Update(float, unsigned int);
        virtual bool Activate(bool);
        virtual bool Connect(const char*);
        virtual void Disconnect();
        virtual FireResult Fire(const Vector&);
        virtual void ConsumeFireResources();
        virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, const Vector&) const;
        virtual FireResult CanFire(const Vector&) const;

        static const float TARGET_POINT_VALID_TIME;
        static CEGun* cast(CEquip*);
        static const CEGun* cast(const CEquip*);
        static bool ComputeTimeToTgt(const Vector&, const Vector&, float, float&);

        CEGun(const CEGun&);
        CEGun(CEqObj*, unsigned short, const Archetype::Gun*, bool);
        const Archetype::Gun* GunArch() const;
        const Archetype::Munition* MunitionArch() const;
        bool CanPointAt(const Vector&, float) const;
        bool CanSeeTargetObject(float) const;
        bool CanSeeTargetPoint(const Vector&, float) const;
        bool ComputeTgtLeadPosition(Vector&) const;
        float GetMunitionRange() const;
        float GetSecondsTillLock() const;
        void GetTarget(CSimple*&, unsigned short&) const;
        Vector GetTurretOrigin() const;
        bool IsJointInMotion() const;
        bool SetTarget(CSimple*, unsigned short);
        void SetTargetPoint(const Vector&);
        bool is_guided() const;
        void ComputeTurretFrame();
        void DecomposeJointMotion(const Vector&, float&, float&) const;
        bool IsMovable() const;
        void LocateJoints();
        void LoseJoints();

    protected:
        bool GetTargetObjectPos(Vector&) const;
};

class IMPORT CEInternalFX : public CEquip
{
    public:
        virtual ~CEInternalFX();
        virtual void Destroy();

        static CEInternalFX* cast(CEquip*);
        static const CEInternalFX* cast(const CEquip*);

        CEInternalFX(const CEInternalFX&);
        CEInternalFX(CEqObj*, unsigned short, const Archetype::InternalFXEquip*, bool);
        const Archetype::InternalFXEquip* InternalFXArch() const;
};

class IMPORT CELightEquip : CEquip
{
    public:
        virtual ~CELightEquip();
        virtual void NotifyArchGroupDestroyed(unsigned short);

        static CELightEquip* cast(CEquip*);
        static const CELightEquip* cast(const CEquip*);

        CELightEquip(const CELightEquip&);
        CELightEquip(CEqObj*, unsigned short, const Archetype::Light*, bool);
        const Archetype::Light* LightArch() const;
};

class IMPORT CEMineDropper : public CELauncher
{
    public:
        virtual ~CEMineDropper();
        virtual FireResult CanFire(const Vector&) const;

        static CEMineDropper* cast(CEquip*);
        static const CEMineDropper* cast(const CEquip*);

        CEMineDropper(const CEMineDropper&);
        CEMineDropper(CEqObj*, unsigned short, const Archetype::MineDropper*, bool);
        const Archetype::Mine* MineArch();
        const Archetype::MineDropper* MineDropperArch();
};

class IMPORT CEPower : public CEquip
{
    public:
        virtual ~CEPower();
        virtual bool Update(float, unsigned int);

        static CEPower* cast(CEquip*);
        static const CEPower* cast(const CEquip*);

        CEPower(const CEPower&);
        CEPower(CEqObj*, unsigned short, const Archetype::Power*, bool);

        float GetCapacity() const;
        float GetChargeRate() const;
        float GetThrustCapacity() const;
        float GetThrustChargeRate() const;
};

class IMPORT CERepairDroid : public CEquip
{
    public:
        virtual ~CERepairDroid();
        virtual float GetHitPoints() const;
        virtual void SetHitPoints(float);

        static CERepairDroid* cast(CEquip*);
        static const CERepairDroid* cast(const CEquip*);

        CERepairDroid(const CERepairDroid&);
        CERepairDroid(CEqObj*, unsigned short, const Archetype::RepairDroid*, bool);
        const Archetype::RepairDroid* RepairDroidArch() const;

    public:
        Archetype::RepairDroid* archetype;
};

class IMPORT CEScanner : public CInternalEquip
{
    public:
        virtual ~CEScanner();
        // virtual bool add_obj(struct IObjRW*);
        virtual bool Update(float, unsigned int);

        static CEScanner* cast(CEquip*);
        static const CEScanner* cast(const CEquip*);

        CEScanner(const CEScanner&);
        CEScanner(CEqObj*, unsigned short, const Archetype::Scanner*, bool);
        float GetCargoScanRange() const;
        float GetRadarRange() const;
        enum ScanResult ScanCargo(CEqObj*);
        const Archetype::Scanner* ScannerArch() const;
        void clear_cache();
        void scan_for_types(unsigned int);
};

class IMPORT CEShield : public CAttachedEquip
{
    public:
        virtual ~CEShield();
        virtual bool IsFunctioning() const;
        virtual bool Update(float, unsigned int);
        virtual bool GetEquipDesc(EquipDesc&) const;
        virtual bool Activate(bool);
        virtual void Destroy();
        virtual float GetMaxHitPoints() const;
        virtual float GetHitPoints() const;
        virtual void SetHitPoints(float);
        virtual bool Connect(const char*);
        virtual void Disconnect();

        static CEShield* cast(CEquip*);
        static const CEShield* cast(const CEquip*);

        CEShield(const CEShield&);
        CEShield(CEqObj*, unsigned short, const Archetype::Shield*, bool);
        const Archetype::ShieldGenerator* ShieldGenArch() const;
        const Archetype::Shield* ShieldArch() const;
        void AttachIntruderChecker();
        void DestroyIntruderChecker();
        float GetOfflineRebuildTime() const;
        float GetOfflineThreshold() const;
        float GetWeaponModifier(const ID_String&) const;
        void ShieldBatteryBoost(float);
        bool Activate_Internal(bool);
        void AddGen(class CEShieldGenerator*);
        bool CanActivate() const;
        void RemGen(CEShieldGenerator*);
};

class IMPORT CEShieldGenerator : public CAttachedEquip
{
    public:
        virtual ~CEShieldGenerator();
        virtual bool IsFunctioning() const;
        virtual bool Update(float, unsigned int);
        virtual void Destroy();

        static CEShieldGenerator* cast(CEquip*);
        static const CEShieldGenerator* cast(const CEquip*);

        CEShieldGenerator(const CEShieldGenerator&);
        CEShieldGenerator(CEqObj*, unsigned short, const Archetype::ShieldGenerator*, bool);
        const Archetype::ShieldGenerator* ShieldGenArch() const;
        bool IsLinked() const;
        void LinkShield(CEShield*);
        void UnLinkShield();
};

class IMPORT CEThruster : public CAttachedEquip, public CPhysControllerEquip
{
    public:
        virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

        virtual ~CEThruster();

        virtual bool EnableController();
        virtual bool DisableController();
        virtual bool IsControllerEnabled() const;

        virtual bool Activate(bool);

        static CEThruster* cast(CEquip*);
        static const CEThruster* cast(const CEquip*);

        CEThruster(const CEThruster&);
        CEThruster(CEqObj*, unsigned short, const Archetype::Thruster*, bool);
        const Archetype::Thruster* ThrusterArch() const;
        bool CouldThrust() const;
        float GetPowerDraw() const;
        float GetThrust() const;
};

class IMPORT CETractor : public CInternalEquip
{
    public:
        virtual ~CETractor();
        virtual bool Update(float, unsigned int);

        static CETractor* cast(CEquip*);
        static const CETractor* cast(const CEquip*);

        CETractor(const CETractor&);
        CETractor(CShip*, unsigned short, const Archetype::Tractor*, bool);
        const Archetype::Tractor* TractorArch() const;
        enum TractorFailureCode AddTarget(struct CLoot*);
        int CountActiveArms() const;
        float GetRange() const;
        Vector GetSourcePos() const;
        const class TractorArm* GetTractorArm(unsigned int) const;
        const st6::vector<TractorArm>& GetTractorArms() const;
        void RemoveTarget(unsigned int);
        TractorFailureCode VerifyTarget(const CLoot*) const;
        bool CanSeeTarget(const CLoot*) const;
};

class IMPORT CETradeLaneEquip : public CInternalEquip
{
    public:
        virtual ~CETradeLaneEquip();

        static CETradeLaneEquip* cast(CEquip*);
        static const CETradeLaneEquip* cast(const CEquip*);

        CETradeLaneEquip(const CETradeLaneEquip&);
        CETradeLaneEquip(CEqObj*, unsigned short, const Archetype::TradeLaneEquip*, bool);
        const Archetype::TradeLaneEquip* TradeLaneArch() const;

        Archetype::TradeLaneEquip* archType;
};

class IMPORT CEquipManager
{
    public:
        CEquipManager(const CEquipManager&);
        CEquipManager();
        ~CEquipManager();
        CEquipManager& operator=(const CEquipManager&);
        bool AddNewEquipment(CEquip*);
        int CleanUp();
        void Clear();
        CExternalEquip* FindByHardpoint(const CacheString&);
        const CExternalEquip* FindByHardpoint(const CacheString&) const;
        CEquip* FindByID(unsigned short);
        const CEquip* FindByID(unsigned short) const;
        CEquip* FindFirst(unsigned int);
        const CEquip* FindFirst(unsigned int) const;
        bool HasDecayingCargo() const;
        bool Init(CEqObj*);
        unsigned short InstToSubObjID(long) const;
        CEquip* ReverseTraverse(class CEquipTraverser&);
        const CEquip* ReverseTraverse(CEquipTraverser&) const;
        int Size() const;
        CEquip* Traverse(CEquipTraverser&);
        const CEquip* Traverse(CEquipTraverser&) const;
        bool VerifyListSync(const class EquipDescList&) const;

    private:
        int CleanUp(st6::list<CEquip*, st6::allocator<CEquip*>>&);
        static void Clear(st6::list<CEquip*, st6::allocator<CEquip*>>&);

    public:
        uint iDunno0;
        bool bDunno4;
        uint* iDunnoPtr8;
        int iDunnoC;
        bool bDunno10;
        uint iDunno14;
        int iDunno18;
        uint decayingCargo;
};

class IMPORT CEquipTraverser
{
    public:
        CEquipTraverser(int);
        CEquipTraverser(int, bool);
        CEquipTraverser();
        CEquipTraverser& operator=(const CEquipTraverser&);
        void Restart();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct Costume
{
        uint head = 0;
        uint body = 0;
        uint leftHand = 0;
        uint rightHand = 0;
        UINT accessory[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
        int accessories = 0;
};

struct IMPORT CEqObj : public CSimple
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        virtual ~CEqObj();                                                          //56
        virtual int update(float, unsigned int);                                    //80
        virtual void disable_controllers();                                         //92
        virtual void enable_controllers();                                          //96
        virtual void unmake_physical();                                             //116
        virtual void remake_physical(const PhySys::CreateParms&, float);            //120
        virtual unsigned int get_name() const;                                      //136
        virtual bool is_targetable() const;                                         //140
        virtual void connect(struct IObjDB*);                                       //144
        virtual void disconnect(struct IObjDB*);                                    //148
        virtual void init(const CreateParms&);                                      //160
        virtual void load_equip_and_cargo(const struct EquipDescVector&, bool);     //164
        virtual void clear_equip_and_cargo();                                       //168
        virtual void get_equip_desc_list(EquipDescVector&) const;                   //172
        virtual bool add_item(const EquipDesc&);                                    //176
        virtual enum ObjActivateResult activate(bool, unsigned int);                //180
        virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&);  //184
        virtual void disconnect(INotify*);                                          //188
        virtual void disconnect(struct IObjRW*);                                    //192
        virtual void connect(INotify*);                                             //196
        virtual void notify(INotify::Event, void*);                                 //200
        virtual void flush_animations();                                            //204
        virtual float get_total_hit_pts() const;                                    //208
        virtual float get_total_max_hit_pts() const;                                //212
        virtual float get_total_relative_health() const;                            //216
        virtual bool get_sub_obj_velocity(unsigned short, Vector&) const;           //220
        virtual bool get_sub_obj_center_of_mass(unsigned short, Vector&) const;     //224
        virtual bool get_sub_obj_hit_pts(unsigned short, float&) const;             //228
        virtual bool set_sub_obj_hit_pts(unsigned short, float);                    //232
        virtual bool get_sub_obj_max_hit_pts(unsigned short, float&) const;         //236
        virtual bool get_sub_obj_relative_health(unsigned short, float&) const;     //240
        virtual unsigned short inst_to_subobj_id(long) const;                       //244
        virtual long sub_obj_id_to_inst(unsigned short) const;                      //248
        virtual void destroy_sub_objs(const DamageList&, bool);                     //252
        virtual int enumerate_sub_objs() const;                                     //256
        virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);   //260
        virtual void link_shields();                                                //264

        struct IMPORT DockAnimInfo
        {
                DockAnimInfo();
                DockAnimInfo& operator=(const DockAnimInfo&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        CEqObj(const CEqObj&);
        CEqObj(Class);
        void attaching_damaged_obj(const CacheString&);
        float attitude_towards(const CEqObj*) const;
        void attitude_towards_symmetrical(float&, const CEqObj*, float&) const;
        void clear_arch_groups();
        class IBehaviorManager* create_behavior_interface(IObjRW*, int);
        Archetype::EqObj* eqobjarch() const;
        unsigned int get_base() const;
        unsigned int get_base_name() const;
        IBehaviorManager* get_behavior_interface();
        float get_cloak_percentage() const;
        void get_collision_group_description(st6::list<CollisionGroupDesc>&) const;
        const unsigned int& get_dock_target() const;
        bool get_explosion_dmg_bounding_sphere(float&, Vector&) const;
        float get_max_power() const;
        float get_power() const;
        float get_power_ratio() const;
        int get_vibe() const;
        bool is_base() const;
        int is_cloaked() const;
        bool is_control_excluded(unsigned int) const;
        bool is_damaged_obj_attached(const CacheString&) const;
        bool is_dock() const;
        bool launch_pos(Vector&, Matrix&, int) const;
        void load_arch_groups(const st6::list<CollisionGroupDesc>&);
        void set_control_exclusion(unsigned int);
        void set_power(float);
        bool sync_cargo(const EquipDescList&);
        bool add_cargo_item(const EquipDesc&);
        bool add_equipped_item(const EquipDesc&);
        void compute_explosion_dmg_bounding_sphere(float&, Vector&) const;
        void init_docking_points(unsigned int);
        void update_docking_animations(float);

        CEquipManager equip_manager; // 57
        uint repVibe; // 65
        Costume commCostume; // 66
        uint voiceId; // 79
        float cloakPercentage; // 80
        CArchGroupManager archGroupManager; // 81
        bool isCELauncher; // 87 sub_6CEA4A0 casts eq to CELauncher only if this is true
        uint dockTargetId; // 88
        IObjInspectImpl* dockTargetIObj; // 89
        uint iDunnoEqObj23; // 90
        bool boundingExplosionBool; // 91 bounding explosion?
        float boundingExplosionFloat; // 92 bounding explosion
        Vector boundingExplosionVector; // 93 bounding explosion stuff
        st6::vector<CEqObj::DockAnimInfo> dockingAnimationsVector; // 96 could be st6::vector<IAnimation2>
        uint controlExcludedDunno; // 100
        IBehaviorManager* behaviorManager; // 101
        float power; //102
        float maxPower; //103
        uint iDunnoEqObj; //104 0xffffffff for all solars except those docking on lands you on a base, then it's 6?

    private:
        void destroy_equipment(const DamageList&, bool);
};

class IMPORT CEquipmentObj : public CObject
{
    public:
        virtual ~CEquipmentObj();

        CEquipmentObj(const CEquipmentObj&);
        CEquipmentObj(Class);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CFLIDMaker
{
    public:
        CFLIDMaker& operator=(const CFLIDMaker&);
        unsigned int AllocateObjectID();
        unsigned int CreateStaticID(const char*);
        static CFLIDMaker* GetInstance();
        int Initialize();
        static void Shutdown();
        static CFLIDMaker* m_pTheMaker;

    protected:
        CFLIDMaker();
        ~CFLIDMaker();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CGuided : public CProjectile
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        virtual ~CGuided();
        virtual int update(float, unsigned int);
        virtual void init_physics(const Vector&, const Vector&);
        virtual void expire_safe_time();

        static bool seeker_can_see(const Vector&, const Vector&, const Vector&, const Archetype::Munition*);

        CGuided(const CGuided&);
        CGuided(Class);
        const Archetype::MotorData* get_motor_arch() const;
        unsigned short get_sub_target() const;
        IObjRW* get_target() const;
        void init(const CreateParms&);
        bool motor_on() const;
        bool seeker_can_see(const Vector&) const;
        void set_sub_target(unsigned short);
        void set_target(IObjRW*);

        BaseWatcher targetBaseWatcher; //60
        ushort targetSId; //62
        Archetype::MotorData* mototData; //63
        float lifetime; // 64
};

struct IMPORT CLoot : public CSimple
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        virtual ~CLoot();
        virtual int update(float, unsigned int);
        virtual unsigned int get_name() const;
        virtual void set_hit_pts(float);
        virtual void init_physics(const Vector&, const Vector&);
        virtual void init(const CreateParms&);

        Archetype::Equipment* container_arch() const;
        Archetype::Equipment* contents_arch() const;

        CLoot(const CLoot&);
        CLoot(Class);
        bool can_ai_tractor() const;
        float get_contents_hit_pts() const;
        unsigned int get_owner() const;
        unsigned int get_units() const;
        float get_volume() const;
        bool is_loot_temporary() const;
        void set_contents_hit_pts(float);
        void set_units(unsigned int);

        uint ownerId; // 57
        uint name; //58 data type unknown, fetched with get_name()
        Archetype::Equipment* contentsArch; //59
        uint unitCount; // 60
        float contentsHitPts; //61
        float lootOwnerSafeTime; //62
        bool canAITractor; //63
        bool isTemporary;
        uint dunnoCLoot;// 64 doesn't seem to be actually used
};

struct IMPORT CMine : public CProjectile
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        virtual ~CMine();
        virtual int update(float, unsigned int);
        virtual unsigned int get_name() const;
        virtual void init_physics(const Vector&, const Vector&);
        virtual void init(const CreateParms&);
        virtual void expire_safe_time();

        CMine(const CMine&);
        CMine(Class);
        const Archetype::Mine* minearch();
};

struct IMPORT CMunition : public CProjectile
{
    public:
        virtual ~CMunition();

        CMunition(const CMunition&);
        CMunition(Class);
        const Archetype::Munition* munitionarch() const;
};

class IMPORT CNonPhysAttachment
{
    public:
        virtual ~CNonPhysAttachment();
        virtual long GetRootIndex() const;
        virtual CObject* GetPhysicsOwner() const;
        virtual void EnableCollisions(bool);
        virtual bool Connect(CAttachedEquip*);
        virtual CObject* Disconnect(CAttachedEquip*, bool);

        CNonPhysAttachment(const CNonPhysAttachment&);
        CNonPhysAttachment();
        CNonPhysAttachment& operator=(const CNonPhysAttachment&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CNudgeEngine : public CPhysControllerEquip
{
    public:
        virtual ~CNudgeEngine();
        virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);
        virtual bool EnableController();

        CNudgeEngine(const CNudgeEngine&);
        CNudgeEngine();
        CNudgeEngine& operator=(const CNudgeEngine&);
        bool Activate(bool);
        Vector GetNudgeVec() const;
        bool IsActive() const;
        void SetNudgeVec(const Vector&);
        void SetOwner(CShip*);

    protected:
        static const float NUDGE_CHANGE_THRESHOLD;
        //@@@

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CPhysAttachment
{
    public:
        virtual ~CPhysAttachment();
        virtual long GetRootIndex() const;
        virtual CObject* GetPhysicsOwner() const;
        virtual void EnableCollisions(bool);
        virtual bool Connect(CAttachedEquip*);
        virtual CObject* Disconnect(CAttachedEquip*, bool);

        CPhysAttachment(const CPhysAttachment&);
        CPhysAttachment();
        CPhysAttachment& operator=(const CPhysAttachment&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CPlayerAccount
{
    public:
        CPlayerAccount(const CPlayerAccount&);
        CPlayerAccount();
        virtual ~CPlayerAccount();
        CPlayerAccount& operator=(const CPlayerAccount&);
        void GenerateAccount(const char*);
        static bool GenerateTextKey(char*);
        st6::wstring GetAccountName();
        const char* GetAccountNameChar();
        st6::wstring GetAccountNameSig();
        const char* GetAccountNameSigChar();
        st6::wstring GetServerSignature(const char*);
        static bool GetTextKey(char*);
        bool LoadAccount();
        bool LoadAccountFromStrings(const char*, const char*);
        static void SetAcctIndex(unsigned long);
        static bool SetTextKey(char*);
        bool VerifyAccount();

    protected:
        void TossHashes();
        static unsigned long AccountIndex;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CPlayerTradeOffer
{
    public:
        CPlayerTradeOffer(const CPlayerTradeOffer&);
        CPlayerTradeOffer();
        virtual ~CPlayerTradeOffer();
        CPlayerTradeOffer& operator=(const CPlayerTradeOffer&);
        bool GetAccepted();
        EquipDescList& GetList();
        unsigned long GetMoneyOffered();
        unsigned int GetSourcePlayerID();
        CPlayerTradeOffer* GetTargetOffer();
        unsigned int GetTargetPlayerID();
        void SetAccepted(bool);
        void SetMoneyOffered(unsigned long);
        void SetSourcePlayerID(unsigned int);
        void SetTargetOffer(CPlayerTradeOffer*);
        void SetTargetPlayerID(unsigned int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CRemotePhysicsSimulation
{
    public:
        CRemotePhysicsSimulation(const CRemotePhysicsSimulation&);
        CRemotePhysicsSimulation();
        virtual ~CRemotePhysicsSimulation();
        CRemotePhysicsSimulation& operator=(const CRemotePhysicsSimulation&);
        double CalcPositionError(const Vector&);
        bool CheckForSync(const Vector&, const Vector&, const Quaternion&);
        void Doit(double);
        Vector GetLatestUpdate();
        Vector GetSample(int);
        unsigned long GetSampleCount();
        double GetSimulationTime();
        virtual void RemoteUpdate(const Vector&, const Quaternion&, double);
        void Reset();
        void SetLogging(bool);
        void tracef(const char*, ...);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IObject
{
        enum ThrustEquipType
        {
            ThrustEquipType_Normal = 1,
            ThrustEquipType_Thruster = 2,
            ThrustEquipType_Nudge = 3,
            ThrustEquipType_Cruise = 4
        };
};

enum class BayState
{
    Closed,
    Closing,
    Open,
    Opening
};

namespace BaseGroupMessage
{
    enum Type;
};

class IMPORT CPlayerGroup
{
    public:
        CPlayerGroup(const CPlayerGroup&);
        CPlayerGroup(void);
        virtual ~CPlayerGroup(void);
        CPlayerGroup& operator=(const CPlayerGroup&);
        bool AddInvite(unsigned int);
        bool AddMember(unsigned int);
        bool DelInvite(unsigned int);
        bool DelMember(unsigned int);
        void DeliverChat(unsigned long, const void*);
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
        void SendChat(int, const unsigned short*, ...);
        void SendGroup(BaseGroupMessage::Type, unsigned int);
        void SetMissionID(unsigned int, unsigned int);
        void SetMissionMessage(struct CSetMissionMessage&);
        void SetMissionObjectives(struct CMissionObjectives&);
        void StoreMemberList(st6::vector<unsigned int>&);

    protected:
        static st6::map<const unsigned int, CPlayerGroup*, st6::less<const unsigned int>, st6::allocator<CPlayerGroup*>> groupIdToGroupPtrMap;
        static unsigned int groupId;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CShip : public CEqObj, public PhySys::Controller
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        static const float JETTISON_CLEARANCE_TIME;

        virtual ~CShip();

        virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

        virtual int update(float, unsigned int);
        virtual void disable_controllers();
        virtual void enable_controllers();
        virtual unsigned int get_name() const;
        virtual void init_physics(const Vector&, const Vector&);
        virtual void flush_animations();
        virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);
        virtual void init(const CreateParms&);                                          //268

        CShip(const CShip&);
        CShip();
        const Archetype::Ship* shiparch() const;
        void VerifyTarget();
        enum FORMATION_RTYPE add_follow_follower(IObjRW*);
        FORMATION_RTYPE add_formation_follower(IObjRW*);
        void airlock_in(const Vector&, const Matrix&);
        bool any_thrusters_on() const;
        bool check_formation_follower_status(float);
        float close_bay();
        bool generate_follow_offset(const IObjInspect*, Transform&) const;
        int get_ammo_capacity_remaining(unsigned int) const;
        int get_ammo_capacity_remaining(const Archetype::Equipment*) const;
        float get_angular_distance_travelled(float, float, float) const;
        float get_angular_distance_travelled(float, float, float, float) const;
        Vector get_angular_drag() const;
        float get_angular_speed_XY(float, float) const;
        float get_angular_speed_Z(float) const;
        const Vector& get_axis_throttle() const;
        BayState get_bay_state() const;
        float get_cargo_hold_remaining() const;
        float get_distance_travelled(float, float, float, IObject::ThrustEquipType) const;
        bool get_farthest_active_gun_range(float&) const;
        IObjRW* get_follow_leader();
        const Vector& get_follow_offset();
        int get_formation_follower_count();
        int get_formation_followers(IObjRW** const, unsigned int);
        unsigned int get_group_name() const;
        const struct ShipGunStats& get_gun_stats() const;
        float get_initial_speed_to_coast_distance(float, bool) const;
        float get_linear_drag() const;
        float get_max_bank_angle() const;
        float get_max_thrust_power() const;
        Vector get_nudge_vec() const;
        const unsigned short* get_pilot_name() const;
        float get_projected_axis_throttle_XY(float) const;
        float get_projected_axis_throttle_Z(float) const;
        float get_projected_throttle(float, IObject::ThrustEquipType) const;
        long get_renderable_subtarget() const;
        int get_repair_kit_capacity_remaining() const;
        int get_shield_battery_capacity_remaining() const;
        int get_space_for_cargo_type(const Archetype::Equipment*) const;
        float get_speed(float, IObject::ThrustEquipType) const;
        int get_status(char*, int) const;
        StrafeDir get_strafe_dir() const;
        unsigned short get_sub_target() const;
        IObjRW* get_target() const;
        int get_targeted_enemy_count();
        bool get_tgt_lead_fire_pos(Vector&) const;
        bool get_tgt_lead_fire_pos(const IObjInspect*, Vector&) const;
        float get_throttle() const;
        float get_thrust_power() const;
        float get_thrust_power_ratio() const;
        float get_time_to_accelerate(float, float, float, IObject::ThrustEquipType) const;
        float get_time_to_accelerate_angularly(float, float, float) const;
        float get_time_to_accelerate_angularly(float, float, float, float) const;
        unsigned int get_tradelane_entrance_ring();
        unsigned int get_tradelane_exit_ring();
        float get_tradelane_speed();
        int go_tradelane(const IObjInspect*, const IObjInspect*, IObjRW*, bool, float);
        bool is_cruise_active() const;
        bool is_enemy(IObjInspect*);
        bool is_jumping() const;
        bool is_launching() const;
        bool is_player() const;
        bool is_using_tradelane() const;
        void jump_in(IObjRW*, const Vector&, const Matrix&, float);
        void launch(IObjRW*, CEqObj*, int);
        bool leaving_system_update(unsigned int&);
        IObjRW* next_enemy();
        IObjRW* next_target(bool);
        void notify_set_target(CShip*, bool);
        float open_bay();
        IObjRW* previous_enemy();
        FORMATION_RTYPE remove_follow_follower(IObjRW*);
        FORMATION_RTYPE remove_formation_follower(IObjRW*);
        void request_exit_tradelane();
        void set_angular_drag_factor(float);
        void set_axis_throttle(const Vector&);
        void set_follow_leader(IObjRW*);
        void set_follow_offset(const Vector&);
        void set_gun_stats_dirty();
        void set_nudge_vec(const Vector&);
        void set_strafe_dir(StrafeDir);
        void set_sub_target(unsigned short);
        void set_target(IObjRW*);
        void set_throttle(float);
        void set_thrust_power(float);
        void set_tradelane_speed(float);
        void stop_tradelane();
        void use_tradelane(bool);
        void collect_angular_force_components(unsigned int, float, float&, float&) const;
        void collect_force_components(float, IObject::ThrustEquipType, float&, float&) const;
        float get_distance_travelled(float, float, float, float, float) const;
        float get_initial_speed_to_coast_distance(float, float, float) const;
        float get_time_to_accelerate(float, float, float, float, float) const;
        void recalculate_formation_speed();

        DWORD dunno5[2];           // 106
        uint physicsPtr;             // 108
        CPlayerGroup* playerGroup; // 109
        DWORD dunno6; // 110
        IObjRW* followLeader2; //111
        uint dunno16; // 112
        Vector followOffset2; // 113
        st6::vector<IObjRW*> followerVector; //116
        IObjRW* followLeader; // 120
        DWORD followLeaderID_unk; // 121
        Vector followOffset; // 122
        DWORD dunno8[3]; // 125
        st6::vector<IObjRW*> targetedEnemyVector; // 128
        DWORD dunno11[3]; // 132
        uint groupId; // 135
        IObjRW* target; // 136
        DWORD targetId_unk; // 137
        ushort subTargetId; // 138
        DWORD BayAnim; // 139
        CSteering* cSteering; // 140
        DWORD dunno13[6]; // 141
        Vector axisThrottle; // 147
        CNudgeEngine* nudgeEngine; // 150
        DWORD dunno10[6]; // 151
        Vector nudgeVector; // 157
        CStrafeEngine* strafeEngine; // 160
        DWORD dunno12[5]; // 161
        StrafeDir strafeDir; // 166
        float throttle; // 167
        float thrustPower; // 168
        float maxThrustPower; // 169
        uint dunno14; // 170
        BayState bayState; // 171
        ActionDB* ActionDB; //172
        uint dunnoCShip1; // 173
        float tradeLaneSpeed; // 174
        bool inTradeLane; // 175
        bool gunRelatedBool; // has active guns?
        float angularDragFactor; // 176
        uint gunStatsDirty; //177
        uint activeGunCount1; //178
        float rectHeight; //179 no clue
        float maxActiveGunRange1; //180
        uint activeGunCount2; //181
        float maxActiveGunRange2; //182 1-missiles 2-guns?
};

struct IMPORT CSolar : public CEqObj
{
    public:
        struct IMPORT CreateParms
        {
                CreateParms();
                CreateParms& operator=(const CreateParms&);

            public:
                uint hash;
                float dunno[3]; // (~0, 0, -1) in float consistently
                Vector pos;
                Matrix orientation;
                int dunno1[3];
                Vector spin;
                int dunno2;

                uint base;
                uint hash2; // rep group? (otherwise it's the hash)
                Costume costume;
                int voiceId;
                int dunnoLoadout[4];
                // class st6::list<struct CollisionGroupDesc> collision;
                int dunno3[3];
                uint idString;
                uint visit;
                uint parent;
                uint destructible;
                // 1, 2, 3 = related to loadouts
                // 4 = class st6::list<struct CollisionGroupDesc> &
                // 7 = ID_String of solar (same as Hash)
                // 8 = visit (only last byte used)
                // 9 = id of parent
                // 10 = destructible (only last byte used)
                uint destSystem;
                uint destGate;
                uint prevRing;
                uint nextRing;
                uint tradelaneSpaceName;
                float atmosphereRange;
                uint dockWith;

                int dunnoAnim[3];
                // 1, 2 = something to do with animations
        };

        virtual ~CSolar();
        virtual void __stdcall set_velocity(long, const Vector&);
        virtual void __stdcall set_angular_velocity(long, const Vector&);
        virtual int update(float, unsigned int);
        virtual Vector get_velocity() const;
        virtual Vector get_angular_velocity() const;
        virtual float get_mass() const;
        virtual void cache_physical_props();
        virtual void init_physics(const Vector&, const Vector&);
        virtual ObjActivateResult activate(bool, unsigned int);
        virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&);
        virtual void flush_animations();
        virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);

        CSolar(const CSolar&);
        CSolar(Class);
        const Archetype::Solar* solararch() const;
        const ID_String& GetParentNickname() const;
        unsigned char GetVisitValue() const;
        static bool ReadObj(INI_Reader&, Archetype::Solar*&, CreateParms&);
        void SetVisitValue(unsigned char);
        float get_atmosphere_immersion(const Vector&) const;
        float get_atmosphere_range() const;
        const ID_String& get_dest_gate() const;
        unsigned int get_dest_system() const;
        const ID_String& get_loadout() const;
        unsigned int get_next_trade_ring() const;
        unsigned int get_prev_trade_ring() const;
        unsigned int get_tradelane_space_name() const;
        void init(const CreateParms&);
        bool is_destructible() const;
        bool is_dynamic() const;
        bool is_lane_ring() const;
        bool is_planetary() const;
        bool is_system_gate() const;
        bool is_waypoint() const;
        void configure_system_gate(const char*);
        void init_continual_anim(const char*);
        void update_system_gate(float);

        uint duplicatedSpaceID;           // 105
        bool isDestructible;              // 106
        bool isDynamic;
        float atmosphereRange;            // 107
        uint solarLoadout_possiblyUnused; // 108
        uint jumpDestSystem;              // 109
        uint jumpDestObj;                 // 110
        bool animationBool;               // 111
        uint animationId;                 // 112
        uint animationStateEnum;          // 113
        float animDuration;               // 114
        CObject::Class CSolarClass;       // 115
        void* dunnoListPtr;               // 116 Pointer to two-directional list, individual size 0xC, so only 1 value being kept aside from the prev and next pointers
        uint dunnoListLength;             // 117 length of 116
        uint prevTradeLaneRing;           // 118
        uint nextTradeLaneRing;           // 119
        uint tradeLaneSpaceName_unused;   // 120
        uint visitValue;                  // 121
        uint parentNickname;              // 122
};

struct IMPORT CharPlaceInfo
{
        CharPlaceInfo();
        ~CharPlaceInfo();
        void clear();
        void destroy();
        bool is_named(const char*) const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CharacterProperties
{
    public:
        CharacterProperties();
        ~CharacterProperties();
        CharacterProperties& operator=(const CharacterProperties&);
        void destroy();
        unsigned long get_key() const;
        void init(const struct CharacterDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT ClipNode
{
    public:
        ClipNode(const tagRECT&);
        ClipNode(const ClipNode&);
        ClipNode();
        virtual ~ClipNode();
        ClipNode& operator=(const ClipNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const tagRECT& get_rect();
        void set_rect(const tagRECT&);

        virtual operator ClipNode*();
        virtual operator const ClipNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace Collision
{
    IMPORT float CalcCollisionDamage(unsigned int, const Vector&, const Vector&);
    IMPORT float CalcCollisionDamage(float, float, float);
    IMPORT void Free();
    IMPORT float GetImpactDamageFromType(unsigned int);
    IMPORT bool Load(INI_Reader&);
}; // namespace Collision

struct IMPORT CommReferrable
{
        CommReferrable(const CommReferrable&);
        CommReferrable();
        CommReferrable& operator=(const CommReferrable&);
        virtual const TString<64>& GetMsgIdPrefix() const;
        virtual bool HasVoiceInfo() const;
        virtual bool read_comm_ini_data(INI_Reader&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CostumeDescriptions
{
    public:
        CostumeDescriptions(const CostumeDescriptions&);
        CostumeDescriptions();
        ~CostumeDescriptions();
        CostumeDescriptions& operator=(const CostumeDescriptions&);
        const struct accessory* find_accessory(unsigned long) const;
        const accessory* find_accessory(const char*) const;
        unsigned long find_accessory_id(const char*) const;
        const struct bodypart* find_bodypart(int, unsigned long) const;
        const bodypart* find_bodypart(int, const char*) const;
        const struct costume* find_costume(unsigned long) const;
        const costume* find_costume(const char*) const;
        unsigned long find_costume_id(const char*) const;
        unsigned long find_part_id(int, const char*) const;
        void get_costume(int, struct Costume&) const;
        void get_costume(const char*, Costume&) const;
        int get_costume_gender(const Costume&) const;
        int get_costume_gender(unsigned long) const;
        const char* get_part_mesh(int, unsigned long) const;
        const char* get_part_name(int, unsigned long) const;
        void load_bodyparts(const char*);
        void load_costumes(const char*);

    private:
        void load_accessory(INI_Reader*);
        void load_bodypart(int, int, class DetailSwitchTable*, INI_Reader*);
        void warn(INI_Reader*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CostumeHint
{
        CostumeHint(const CostumeHint&);
        CostumeHint();
        virtual ~CostumeHint();
        CostumeHint& operator=(const CostumeHint&);
        virtual void CleanUp(unsigned char*);
        // virtual unsigned int Serialize(unsigned char**);
        virtual void UnSerialize(unsigned char*, unsigned int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT Csys
{
    public:
        Csys();
        Csys& operator=(const Csys&);
        Csys get_inverse() const;
        Transform get_transform() const;
        void init(const Vector&, const Matrix&);
        void set_identity();
        void set_transform(const Transform&);
        Csys trans_from_frame(const Csys&) const;
        Matrix trans_from_frame(const Matrix&) const;
        Vector trans_from_frame(const Vector&) const;
        Csys trans_to_frame(const Csys&) const;
        Matrix trans_to_frame(const Matrix&) const;
        Vector trans_to_frame(const Vector&) const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

Csys operator*(const Csys&, const Csys&);

namespace DataConfig
{
    IMPORT void shutdown();
    IMPORT int startup(const char*, Archetype::IClObjFactory*, struct ProgressCB*);
}; // namespace DataConfig

class IMPORT DetailSwitchTable
{
    public:
        DetailSwitchTable(const DetailSwitchTable&);
        DetailSwitchTable();
        ~DetailSwitchTable();
        DetailSwitchTable& operator=(const DetailSwitchTable&);
        float adjust_distance(float, float, float) const;
        float get_switch_distance(float) const;
        void read_from_ini(INI_Reader*);

    private:
        void add_table_entry(float, float);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT TextRenderContext
{
    public:
        class Image;
        struct FontDesc;

        TextRenderContext(const TextRenderContext&);
        TextRenderContext();
        virtual ~TextRenderContext();
        TextRenderContext& operator=(const TextRenderContext&);
        void clear_default_attributes();
        const struct TextRenderAttributes& get_current_attributes();
        const TextRenderAttributes& get_default_attributes();
        int get_origin_h();
        int get_origin_v();
        int get_pos_h();
        int get_pos_v();
        void pop_default_attributes();
        void pop_state();
        void push_default_attributes();
        void push_state();
        void reset_to_default();
        void set_current_attributes(const TextRenderAttributes&);
        void set_default_attributes(const TextRenderAttributes&);
        void set_origin(int, int);
        void set_origin_h(int);
        void set_origin_v(int);
        void set_pos(int, int);
        void set_pos_h(int);
        void set_pos_v(int);

    private:
        void get_state(struct State&);
        void set_state(const State&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT DeviceTRC
{
    public:
        DeviceTRC(const DeviceTRC&);
        DeviceTRC(HDC__*);
        DeviceTRC();
        virtual ~DeviceTRC();
        DeviceTRC& operator=(const DeviceTRC&);
        void bind_to_dc(HDC__*);
        virtual TextRenderContext::Image* create_image(const char* const);
        virtual void destroy_image(TextRenderContext::Image*);
        virtual void execute_image(const TextRenderContext::Image*, bool);
        virtual void execute_text(const unsigned short*, bool, int);
        virtual int get_cell_height() const;
        virtual int get_cell_width() const;
        virtual void get_clip_rect(tagRECT&);
        virtual void get_font_metrics(int&, int&) const;
        virtual void get_text_fit(const unsigned short*, int, int&, int*, VisualSize&, int) const;
        virtual void get_text_visual_size(const unsigned short*, VisualSize&, int) const;
        static void release_font(int);
        virtual void set_clip_rect(const tagRECT&);
        static void set_drop_shadow_offset(int, int);
        static void set_image_root(const char*);
        static void static_set_font(int, const TextRenderContext::FontDesc&, float);

    private:
        static int dropShadowX;
        static int dropShadowY;
        static class WinFont* font;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace EngineEquipConsts
{
    IMPORT float CRUISE_ACCEL_TIME;
    IMPORT float CRUISE_ATTEN_MOD_RANGE;
    IMPORT float CRUISE_DISRUPT_TIME;
    IMPORT float CRUISE_DRAG;
    IMPORT float CRUISE_STEADY_TIME;
    IMPORT float CRUISING_SPEED;
    IMPORT float DELTA_CRUISE_ATTEN_MOD_STEADY;
    IMPORT float DELTA_THROTTLE_ATTEN_MOD_CHANGING;
    IMPORT float DELTA_THROTTLE_ATTEN_MOD_STEADY;
    IMPORT float MAX_DELTA_FX_THROTTLE;
    IMPORT float MAX_ENGINE_FX_THROTTLE;
    IMPORT float THROTTLE_ATTEN_MOD_RANGE;
    IMPORT float THROTTLE_STEADY_TIME;
}; // namespace EngineEquipConsts

#pragma pack(push, 1)
struct SetEquipmentItem
{
        int count;
        float health;
        int archId;
        ushort id;
        byte mounted;
        byte mission;
        ushort hardPointLen;
};
#pragma pack(pop)

struct FlPacketSetEquipment
{
        ushort count;
        byte items[1];
};

struct IMPORT EquipDesc
{
        EquipDesc(const EquipDesc&);
        EquipDesc();
        EquipDesc& operator=(const EquipDesc&);
        bool operator==(const EquipDesc&) const;
        bool operator!=(const EquipDesc&) const;
        bool operator<(const EquipDesc&) const;
        bool operator>(const EquipDesc&) const;

        static const CacheString CARGO_BAY_HP_NAME;
        unsigned int get_arch_id() const;
        float get_cargo_space_occupied() const;
        int get_count() const;
        const CacheString& get_hardpoint() const;
        unsigned short get_id() const;
        int get_owner() const;
        float get_status() const;
        bool get_temporary() const;
        bool is_equipped() const;
        bool is_internal() const;
        void make_internal();
        void set_arch_id(unsigned int);
        void set_count(int);
        void set_equipped(bool);
        void set_hardpoint(const CacheString&);
        void set_id(unsigned short);
        void set_owner(int);
        void set_status(float);
        void set_temporary(bool);

    public:
        ushort dunno;
        ushort id;
        uint archId;
        CacheString hardPoint;
        bool mounted;
        float health;
        uint count;
        bool mission;
        uint owner;
};

class IMPORT EquipDescList
{
    public:
        EquipDescList(const EquipDescVector&);
        EquipDescList(const EquipDescList&);
        EquipDescList();
        ~EquipDescList();
        EquipDescList& operator=(const EquipDescList&);
        int add_equipment_item(const EquipDesc&, bool);
        void append(const EquipDescList&);
        EquipDesc* find_equipment_item(const CacheString&);
        EquipDesc* find_equipment_item(unsigned short);
        const EquipDesc* find_equipment_item(const CacheString&) const;
        const EquipDesc* find_equipment_item(unsigned short) const;
        const EquipDesc* find_matching_cargo(unsigned int, int, float) const;
        float get_cargo_space_occupied() const;
        int remove_equipment_item(unsigned short, int);
        EquipDesc* traverse_equipment_type(unsigned int, const EquipDesc*);
        const EquipDesc* traverse_equipment_type(unsigned int, const EquipDesc*) const;

    public:
        st6::list<EquipDesc> equip;
};

struct IMPORT EquipDescVector
{
        EquipDescVector(const EquipDescVector&);
        EquipDescVector(const EquipDescList&);
        EquipDescVector();
        ~EquipDescVector();
        EquipDescVector& operator=(const EquipDescVector&);
        int add_equipment_item(const EquipDesc&, bool);
        void append(const EquipDescVector&);
        EquipDesc* traverse_equipment_type(unsigned int, const EquipDesc*);

    public:
        st6::vector<EquipDesc> equip;
};

namespace ErrorHandler
{
    IMPORT void activate(const char*, int (*)(const char*, const char*, bool));
    IMPORT void deactivate();
    IMPORT bool is_log_enabled(int);
    IMPORT void log_comment(int, const char*, ...);
    IMPORT void log_disable(int);
    IMPORT void log_enable(int);
    IMPORT void log_last_error(const char*, int, enum SeverityLevel, char*, unsigned long);
    IMPORT void* new_log(const char*, int, int, bool, bool);
}; // namespace ErrorHandler

struct IMPORT ExhaustNozzleInfo
{
        ExhaustNozzleInfo();
        ExhaustNozzleInfo& operator=(const ExhaustNozzleInfo&);
        bool GetHardpointOffset_NS(Transform&) const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT File
{
    public:
        File();
        ~File();
        File& operator=(const File&);
        void close();
        int eof();
        void get_info();
        int get_length();
        const char* get_name() const;
        bool is_open();
        bool open(const char*);
        int read(void*, int);
        int read(void*, int, int);
        int read_line(char*, int);
        int seek(int);
        void set_name(const char*);
        int set_offset(int);
        int tell() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT FileMap
{
        FileMap(const FileMap&);
        FileMap();
        ~FileMap();
        FileMap& operator=(const FileMap&);
        void close();
        bool eof() const;
        unsigned int get_file_length() const;
        const char* get_file_name() const;
        void handoff_to(FileMap&);
        bool open(const char*);
        bool open_memory(const void*, unsigned int);
        unsigned int read(void*, unsigned int);
        bool read_ptr(struct BINI_Block*&);
        bool read_ptr(struct BINI_Header*&);
        bool read_ptr(struct BINI_Value*&);
        void* request_pointer(unsigned int&);
        void seek(unsigned int);
        unsigned int tell() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT FlashLightSetInfo
{
        FlashLightSetInfo();
        ~FlashLightSetInfo();
        FlashLightSetInfo& operator=(const FlashLightSetInfo&);
        void clear();
        void destroy();
        void fixup(long, const class HardpointSummary*, const RoomData*);
        void unfixup();

    private:
        void add_light_csys(const Csys&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct FmtStr
{
        struct IMPORT Val
        {
                Val(const Val&);
                Val(unsigned short, void*, unsigned char);
                Val(const void*);
                Val(const void*, int&);
                ~Val();
                const Val& operator=(const Val&);
                bool operator==(const Val&) const;
                unsigned int flatten(void*, unsigned int) const;
                unsigned int get_flattened_size() const;

                static void* operator new(unsigned int);
                static void operator delete(void*);

            private:
                int InitFromVoid(const void*);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        FmtStr() : FmtStr(0, nullptr) {}
        IMPORT FmtStr(const FmtStr&);
        IMPORT FmtStr(unsigned int, const Val*);
        IMPORT ~FmtStr();
        IMPORT const FmtStr& operator=(const FmtStr&);
        IMPORT bool operator==(const FmtStr&) const;
        IMPORT void append(Val*);
        IMPORT void append_base(const unsigned int&);
        IMPORT void append_fmt_str(const FmtStr&);
        IMPORT void append_good(const unsigned int&);
        IMPORT void append_installation(int);
        IMPORT void append_int(unsigned int);
        IMPORT void append_loot(int);
        IMPORT void append_nav_marker(const struct NavMarker&);
        IMPORT void append_rep_group(const unsigned int&);
        IMPORT void append_rep_instance(const int&);
        IMPORT void append_spaceobj_id(const unsigned int&);
        IMPORT void append_string(unsigned int);
        IMPORT void append_system(const unsigned int&);
        IMPORT int append_void(void*);
        IMPORT void append_zone_id(const unsigned int&);
        IMPORT void begin_mad_lib(unsigned int);
        IMPORT void destroy();
        IMPORT void end_mad_lib();
        IMPORT int flatten(void*, unsigned int) const;
        IMPORT int unflatten(void*, unsigned int);

    public:
        uint something;
        uint strid;       // resource containing text
        BYTE tnav_marker; // counters for each type
        BYTE tsystem;
        BYTE tbase;
        BYTE tstring;
        BYTE tgood;
        BYTE tunused;
        BYTE tint;
        BYTE trep_instance;
        BYTE trep_group;
        BYTE tzone_id;
        BYTE tspace_obj_id;
        BYTE tfmt_str;
        BYTE tinstallation;
        BYTE tloot;
};

class IMPORT Fuse
{
    public:
        Fuse(const ID_String&, float);
        Fuse(const Fuse&);
        virtual ~Fuse();
        Fuse& operator=(const Fuse&);
        int ActionCount() const;
        void Burn(float);
        virtual void FreeActions();
        bool IgniteAt(unsigned int, unsigned short, float);
        bool IsBurning() const;
        bool IsDeathFuse() const;
        bool IsSpent() const;
        bool IsSpentAt(float) const;
        float Lifetime() const;
        void Load() const;
        const ID_String& Name() const;
        bool OverrideLifetime(float);
        void RandomizeActions();
        bool UnBurn(unsigned short, float);
        void UnLoad() const;

    protected:
        bool ReadFuseValues(INI_Reader&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT FuseAction
{
    public:
        FuseAction(const FuseAction&);
        FuseAction();
        virtual ~FuseAction();
        FuseAction& operator=(const FuseAction&);
        float GetTriggerTime() const;
        virtual bool IsTriggered(unsigned short) const;
        virtual bool IsTriggered() const;
        virtual int Load();
        virtual float Randomize();
        virtual bool ShouldRandomize() const;
        virtual void Trigger(unsigned int, unsigned short);
        virtual int UnLoad();
        virtual void UnTrigger(unsigned short);

    protected:
        virtual void CopyArchProperties(const FuseAction&);
        bool ReadFuseActionValue(INI_Reader&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT FuseDB
{
    public:
        FuseDB& operator=(const FuseDB&);
        static void AddFuseINIFile(const char*);
        static void Shutdown();

    protected:
        typedef TString<260> TString260;
        static st6::list<TString260> m_FuseINIFiles;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT GoodDesc
{
        GoodDesc();
        GoodDesc& operator=(const GoodDesc&);

        static void* operator new(unsigned int);
        static void operator delete(void*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT GoodDescList
{
        GoodDescList(const GoodDescList&);
        GoodDescList();
        virtual ~GoodDescList();
        const GoodDescList& operator=(const GoodDescList&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct GoodInfo
{
    public:
        enum class Type
        {
            Commodity,
            Equipment,
            Hull,
            Ship
        };

        uint i1;
        uint len;
        uint dunno1[16];
        /* 72 */ uint goodId;
        /* 76 */ Type type; // 0=commodity, 2=hull, 3=ship
        /* 80 */ uint equipmentId;
        /* 84 */ uint shipGoodId; // if type = GOODINFO_TYPE_HULL
        /* 88 */ float price;
        /* 92 */ float goodSellPrice;
        /* 96 */ float badBuyPrice;
        /* 100 */ float badSellPrice;
        /* 104 */ float goodBuyPrice;
        /* 108 */ uint jumpDist;
        /* 112 */ bool multiCount; // TODO: Verify
        /* 116 */ float dunno3;
        /* 120 */ float dunno4;
        /* 124 */ float dunno5;
        /* 128 */ float dunno6;
        /* 132 */ float dunno7;
        /* 136 */ uint idsName;
        /* 140 */ uint idsInfo;
        /* 144 */ uint hullGoodId; // if type = GOODINFO_TYPE_SHIP
        /* 148 */ EquipDescList edl;
        /* 160 */ EquipDescList edl2;
        /* 172 */ EquipDescList edl3;
        /* 184 */ uint freeAmmoArchId;
        /* 188 */ uint freeAmmoCount;
};

class IMPORT GoodInfoList
{
    public:
        GoodInfoList(const GoodInfoList&);
        GoodInfoList();
        ~GoodInfoList();
        GoodInfoList& operator=(const GoodInfoList&);
        void destroy();
        const GoodInfo* find_by_archetype(unsigned int) const;
        const GoodInfo* find_by_id(unsigned int) const;
        const GoodInfo* find_by_name(const char*) const;
        const GoodInfo* find_by_ship_arch(unsigned int) const;
        const st6::list<GoodInfo*, st6::allocator<GoodInfo*>>* get_list() const;
        void load(const char*);

    private:
        void read_Good_block(INI_Reader*, GoodInfo*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace GoodList
{
    IMPORT const GoodInfo* find_by_archetype(unsigned int);
    IMPORT const GoodInfo* find_by_id(unsigned int);
    IMPORT const GoodInfo* find_by_nickname(const char*);
}; // namespace GoodList

class IMPORT HardpointSummary
{
    public:
        HardpointSummary(const HardpointSummary&);
        HardpointSummary();
        virtual ~HardpointSummary();
        HardpointSummary& operator=(const HardpointSummary&);
        int analyze_instance(long);
        void clear();
        void destroy();
        void expire_instance();
        int find_name(const char*) const;
        long find_name_instance(const char*) const;
        int get_count() const;
        const HardpointInfo& get_info(int) const;
        const HardpointInfo* get_info_by_name(const char*) const;
        long get_instance(int) const;
        const char* get_name(int) const;

    private:
        void count_hardpoints(long);
        static void count_hardpoints_callback(long, void*);
        void fill_hardpoints(long);
        static void fill_hardpoints_callback(long, void*);
        static void hardpoint_callback1(const char*, void*);
        static void hardpoint_callback2(const char*, void*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT Heap
{
        Heap(unsigned int, int);
        void Free(void*);
        void* Malloc();
        void Shrink();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace Hierarchy
{
    IMPORT int GetDepth(long, long);
};

struct IMPORT IAction
{
        IAction(const IAction&);
        IAction();
        virtual ~IAction();
        IAction& operator=(const IAction&);
        virtual const char* get_id() const;

        static void* operator new(unsigned int);
        static void operator delete(void*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IStateGraph;

namespace pub
{
    namespace AI
    {
        enum ScanResponse;
        enum OP_RTYPE;
        enum DirectivePriority;
        struct DirectiveCallback;

        enum OpType
        {
            None = -1,
            NullOp = 0,
            Buzz = 1,
            Dunno = 2,
            Goto = 3,
            Follow = 4,
            Trail = 5,
            Strafe = 6,
            Face = 7,
            Ram = 8,
            Tractor = 9,
            Evade = 10,
            DrasticEvade = 11,
            Delay = 12,
            Dock = 13,
            Launch = 14,
            Tradelane = 15,
            InstanceTradeLane = 16,
            Guide = 17,
            WaitForShip = 18,
            FreeFlight = 19,
            Idle = 20,
            Cancel = 21,
        };

        class IMPORT Personality
        {
            public:
                struct IMPORT EvadeDodgeUseStruct
                {
                        EvadeDodgeUseStruct();
                        EvadeDodgeUseStruct& operator=(const EvadeDodgeUseStruct&);

                        float evade_activate_range;                       // 500
                        float evade_dodge_style_weight[4];                // WAGGLE, WAGGLE_RANDOM, SLIDE, CORKSCREW, all 0
                        float evade_dodge_cone_angle;                     // 45
                        float evade_dodge_cone_angle_variance_percent;    // 0
                        float evade_dodge_waggle_axis_cone_angle;         // 0
                        float evade_dodge_roll_angle;                     // 0
                        float evade_dodge_interval_time;                  // 1
                        float evade_dodge_interval_time_variance_percent; // 0
                        float evade_dodge_distance;                       // 100
                        float evade_dodge_time;                           // 10
                        float evade_dodge_slide_throttle;                 // 0.6
                        float evade_dodge_turn_throttle;                  // 0.6
                        float evade_dodge_corkscrew_turn_throttle;        // 0.15
                        float evade_dodge_corkscrew_roll_throttle;        // 1
                        bool evade_dodge_corkscrew_roll_flip_direction;   // false
                        float evade_dodge_direction_weight[4];            // LEFT, RIGHT, UP, DOWN, all 0
                };

                struct IMPORT EvadeBreakUseStruct
                {
                        EvadeBreakUseStruct();
                        EvadeBreakUseStruct& operator=(const EvadeBreakUseStruct&);

                        float evade_break_time;                               // 3
                        float evade_break_interval_time;                      // 100000
                        float evade_break_afterburner_delay;                  // 0
                        float evade_break_afterburner_delay_variance_percent; // 0
                        float evade_break_direction_weight[4];                // LEFT, RIGHT, UP, DOWN, all 0
                        float evade_break_roll_throttle;                      // 0
                        float evade_break_turn_throttle;                      // 1
                        float evade_break_style_weight[3];                    // SIDEWAYS, OUTRUN, REVERSE, all 0
                        float evade_break_attempt_reverse_time;               // 4
                        float evade_break_reverse_distance;                   // 150
                };

                struct IMPORT BuzzHeadTowardUseStruct
                {
                        BuzzHeadTowardUseStruct();
                        BuzzHeadTowardUseStruct& operator=(const BuzzHeadTowardUseStruct&);

                        float buzz_max_time_to_head_away;                        // 4
                        float buzz_head_toward_style_weight[3];                  // STRAIGHT_TO, SLIDE, WAGGLE, all 0
                        float buzz_min_distance_to_head_toward;                  // 400
                        float buzz_min_distance_to_head_toward_variance_percent; // 1
                        float buzz_head_toward_engine_throttle;                  // 1
                        float buzz_head_toward_turn_throttle;                    // 1
                        float buzz_head_toward_roll_throttle;                    // 0
                        bool buzz_head_toward_roll_flip_direction;               // false
                        float buzz_dodge_direction_weight[4];                    // LEFT, RIGHT, UP, DOWN, all 0
                        float buzz_dodge_turn_throttle;                          // 1
                        float buzz_dodge_cone_angle;                             // 45
                        float buzz_dodge_cone_angle_variance_percent;            // 0
                        float buzz_dodge_waggle_axis_cone_angle;                 // 0
                        float buzz_dodge_roll_angle;                             // 0
                        float buzz_dodge_interval_time;                          // 2
                        float buzz_dodge_interval_time_variance_percent;         // 0
                        float buzz_slide_throttle;                               // 1
                        float buzz_slide_interval_time;                          // 2
                        float buzz_slide_interval_time_variance_percent;         // 0.4
                };

                struct IMPORT BuzzPassByUseStruct
                {
                        BuzzPassByUseStruct();
                        BuzzPassByUseStruct& operator=(const BuzzPassByUseStruct&);

                        float buzz_pass_by_style_weight[3];    // STRAIGHT_BY, BREAK_AWAY, ENGINE_KILL, all 0
                        float buzz_distance_to_pass_by;        // 100
                        float buzz_pass_by_time;               // 3
                        bool buzz_drop_bomb_on_pass_by;        // false
                        float buzz_break_direction_weight[4];  // LEFT, RIGHT, UP, DOWN, all 0
                        float buzz_break_direction_cone_angle; // 0
                        float buzz_break_turn_throttle;        // 1
                        float buzz_pass_by_roll_throttle;      // 0
                };

                struct IMPORT TrailUseStruct
                {
                        TrailUseStruct();
                        TrailUseStruct& operator=(const TrailUseStruct&);

                        float trail_lock_cone_angle;     // 30
                        float trail_break_time;          // 2.5
                        float trail_min_no_lock_time;    // 4
                        float trail_break_roll_throttle; // 0
                        bool trail_break_afterburner;    // false
                        float trail_max_turn_throttle;   // 1
                        float trail_distance;            // 150
                };

                struct IMPORT StrafeUseStruct
                {
                        StrafeUseStruct();
                        StrafeUseStruct& operator=(const StrafeUseStruct&);

                        float strafe_run_away_distance; // 300
                        float strafe_attack_throttle;   // 1
                        float strafe_turn_throttle;     // 1
                };

                struct IMPORT EngineKillUseStruct
                {
                        EngineKillUseStruct();
                        EngineKillUseStruct& operator=(const EngineKillUseStruct&);

                        float engine_kill_search_time;         // 6
                        float engine_kill_face_time;           // 3
                        float engine_kill_use_afterburner;     // 0
                        float engine_kill_afterburner_time;    // 0.5
                        float engine_kill_max_target_distance; // 700
                };

                struct IMPORT RepairUseStruct
                {
                        RepairUseStruct();
                        RepairUseStruct& operator=(const RepairUseStruct&);

                        float use_shield_repair_pre_delay;         // 2
                        float use_shield_repair_at_damage_percent; // 0.5
                        float use_shield_repair_post_delay;        // 3
                        float use_hull_repair_pre_delay;           // 1
                        float use_hull_repair_at_damage_percent;   // 0.5
                        float use_hull_repair_post_delay;          // 1
                };

                struct IMPORT GunUseStruct
                {
                        GunUseStruct();
                        GunUseStruct& operator=(const GunUseStruct&);

                        int fire_style;                                    // MULTIPLE = 0 (default), SINGLE = 1
                        float gun_fire_interval_time;                      // 0
                        float gun_fire_interval_variance_percent;          // 0.5
                        float gun_fire_burst_interval_time;                // 1.5
                        float gun_fire_burst_interval_variance_percent;    // 0.1
                        float gun_fire_no_burst_interval_time;             // 0.1
                        float gun_fire_accuracy_cone_angle;                // 0
                        float gun_fire_accuracy_power;                     // 1
                        float gun_fire_accuracy_power_npc;                 // 6
                        float gun_range_threshold;                         // 1
                        float gun_range_threshold_variance_percent;        // 0.2
                        float gun_target_point_switch_time;                // 1.5
                        float auto_turret_interval_time;                   // 0
                        float auto_turret_burst_interval_time;             // 1
                        float auto_turret_no_burst_interval_time;          // 0
                        float auto_turret_burst_interval_variance_percent; // 0.1
                };

                struct IMPORT MineUseStruct
                {
                        MineUseStruct();
                        MineUseStruct& operator=(const MineUseStruct&);

                        float mine_launch_interval;   // 0
                        float mine_launch_cone_angle; // 22.5
                        float mine_launch_range;      // 400
                };

                struct IMPORT MissileUseStruct
                {
                        MissileUseStruct();
                        MissileUseStruct& operator=(const MissileUseStruct&);

                        float missile_launch_range;                     // -1
                        bool missile_launch_allow_out_of_range;         // false
                        float missile_launch_interval_time;             // 5
                        float missile_launch_interval_variance_percent; // 0.4
                        float missile_launch_cone_angle;                // 22.5
                        float anti_cruise_missile_min_distance;         // 300
                        float anti_cruise_missile_max_distance;         // 2500
                        float anti_cruise_missile_pre_fire_delay;       // 2
                        float anti_cruise_missile_interval_time;        // 5
                };

                struct IMPORT DamageReactionStruct
                {
                        DamageReactionStruct();
                        DamageReactionStruct& operator=(const DamageReactionStruct&);

                        float evade_break_damage_trigger_percent;      // 1
                        float evade_dodge_more_damage_trigger_percent; // 0.2
                        float drop_mines_damage_trigger_percent;       // 1
                        float drop_mines_damage_trigger_time;          // 1
                        float engine_kill_face_damage_trigger_percent; // 1
                        float engine_kill_face_damage_trigger_time;    // 2
                        float roll_damage_trigger_percent;             // 1
                        float roll_damage_trigger_time;                // 1
                        float afterburner_damage_trigger_percent;      // 1
                        float afterburner_damage_trigger_time;         // 1.5
                        float brake_reverse_damage_trigger_percent;    // 1
                        float fire_missiles_damage_trigger_percent;    // 1
                        float fire_missiles_damage_trigger_time;       // 0.5
                        float fire_guns_damage_trigger_percent;        // 1
                        float fire_guns_damage_trigger_time;           // 1
                        int _03C;                                      // not initialised
                        int _040;                                      // not initialised
                };

                struct IMPORT MissileReactionStruct
                {
                        MissileReactionStruct();
                        MissileReactionStruct& operator=(const MissileReactionStruct&);

                        float evade_break_missile_reaction_time;     // 0
                        float evade_slide_missile_reaction_time;     // 0
                        float evade_afterburn_missile_reaction_time; // 0
                        float evade_missile_distance;                // 250
                };

                struct IMPORT CountermeasureUseStruct
                {
                        CountermeasureUseStruct();
                        CountermeasureUseStruct& operator=(const CountermeasureUseStruct&);

                        float countermeasure_active_time;   // 1
                        float countermeasure_unactive_time; // 0
                };

                struct IMPORT FormationUseStruct
                {
                        FormationUseStruct();
                        FormationUseStruct& operator=(const FormationUseStruct&);

                        float force_attack_formation_active_time;           // 1
                        float force_attack_formation_unactive_time;         // 0
                        float break_formation_damage_trigger_percent;       // 1
                        float break_formation_damage_trigger_time;          // 4
                        float break_apart_formation_damage_trigger_percent; // 1
                        float break_apart_formation_damage_trigger_time;    // 4
                        float break_formation_missile_reaction_time;        // 0
                        float break_apart_formation_missile_reaction_time;  // 4
                        bool break_apart_formation_on_buzz_head_toward;     // false
                        float break_formation_on_buzz_head_toward_time;     // 4
                        bool regroup_formation_on_buzz_head_toward;         // false
                        bool break_apart_formation_on_buzz_pass_by;         // false
                        float break_formation_on_buzz_pass_by_time;         // 4
                        bool regroup_formation_on_buzz_pass_by;             // false
                        bool break_apart_formation_on_evade_dodge;          // false
                        float break_formation_on_evade_dodge_time;          // 4
                        bool regroup_formation_on_evade_dodge;              // false
                        bool break_apart_formation_on_evade_break;          // false
                        float break_formation_on_evade_break_time;          // 4
                        bool regroup_formation_on_evade_break;              // false
                        int formation_exit_mode;
                        // 0 = BREAK_AWAY_FROM_CENTER
                        // 1 = BREAK_AWAY_FROM_CENTER_AFTERBURNER
                        // 2 = BRAKE_REVERSE
                        // 3 = OUTRUN
                        // 5 = NOTHING (default)
                        float formation_exit_top_turn_break_away_throttle; // 1
                        float formation_exit_roll_outrun_throttle;         // 0
                        float formation_exit_max_time;                     // 0
                        bool leader_makes_me_tougher;                      // false
                };

                struct IMPORT JobStruct
                {
                        JobStruct();
                        JobStruct& operator=(const JobStruct&);

                        int _000;                        // 0
                        int scene_toughness_threshold;   // 2
                                                         // 0 = EASIEST
                                                         // 1 = EASY
                                                         // 2 = EQUAL
                                                         // 3 = HARD
                                                         // 4 = HARDEST
                        int target_toughness_preference; // 2
                                                         // 0 = EASIEST
                                                         // 1 = EASY
                                                         // 2 = EQUAL
                                                         // 3 = HARD
                                                         // 4 = HARDEST
                        float combat_drift_distance;     // ? 10000 (ignored)
                        struct Tattack_order
                        {
                                int type;                     // 11
                                float distance;               // 5000
                                int flag;                     // 15
                        } attack_order[13];                   // attack_preference
                                                              // index 0 = FIGHTER
                                                              //		 1 = FREIGHTER
                                                              //		 2 = TRANSPORT
                                                              //		 3 = GUNBOAT
                                                              //		 4 = CRUISER
                                                              //		 5 = CAPITAL
                                                              //		 6 = TRADELANE
                                                              //		 7 = JUMPGATE
                                                              //		 8 = WEAPONS_PLATFORM
                                                              //		 9 = DESTROYABLE_DEPOT
                                                              //		10 = SOLAR
                                                              //		11 = ANYTHING
                                                              //		12 = end of list
                                                              // flag  1 = GUNS
                                                              //		 2 = GUIDED
                                                              //		 4 = UNGUIDED	// bug - also matches GUIDED
                                                              //		 8 = TORPEDO
                        int attack_subtarget_order[8];        // 6
                                                              // 0 = GUNS
                                                              // 1 = TURRETS
                                                              // 2 = LAUNCHERS
                                                              // 3 = TOWERS
                                                              // 4 = ENGINES
                                                              // 5 = HULL
                                                              // 6 = ANYTHING
                                                              // 7 = end of list
                        bool wait_for_leader_target;          // not initialised
                        float maximum_leader_target_distance; // 5000
                        int field_targeting;                  // 3
                                                              // 0 = NEVER
                                                              // 1 = LOW_DENSITY
                                                              // 2 = HIGH_DENSITY
                                                              // 3 = ALWAYS
                        int loot_preference;                  // 0
                                                              // 0 = LT_NONE
                                                              // 1 = LT_COMMODITIES
                                                              // 2 = LT_EQUIPMENT
                                                              // 4 = LT_POTIONS
                                                              // 7 = LT_ALL (bitmask)
                        int loot_flee_threshold;              // 2
                                                              // 0 = EASIEST
                                                              // 1 = EASY
                                                              // 2 = EQUAL
                                                              // 3 = HARD
                                                              // 4 = HARDEST
                        int _0E0;                             // 0
                        int _0E4_120[16];                     // not initialised
                        int flee_scene_threat_style;          // 3
                                                              // 0 = EASIEST
                                                              // 1 = EASY
                                                              // 2 = EQUAL
                                                              // 3 = HARD
                                                              // 4 = HARDEST
                        float flee_when_hull_damaged_percent; // 0
                        bool flee_when_leader_flees_style;    // true
                        bool flee_no_weapons_style;           // true
                        bool allow_player_targeting;          // true
                        float _130;                           // -1
                        bool force_attack_formation;          // false
                        bool force_attack_formation_used;     // false (true when above is set)
                };

                Personality();
                Personality& operator=(const Personality&);
                static const float SCAN_CHANCE_DEFAULT;
                float get_range_threshold_value();
                float get_toughness_ratio(enum TOUGHNESS_TYPE);

            public:
                EvadeDodgeUseStruct EvadeDodgeUse;
                EvadeBreakUseStruct EvadeBreakUse;
                BuzzHeadTowardUseStruct BuzzHeadTowardUse;
                BuzzPassByUseStruct BuzzPassByUse;
                TrailUseStruct TrailUse;
                StrafeUseStruct StrafeUse;
                EngineKillUseStruct EngineKillUse;
                RepairUseStruct RepairUse;
                GunUseStruct GunUse;
                MineUseStruct MineUse;
                MissileUseStruct MissileUse;
                DamageReactionStruct DamageReaction;
                MissileReactionStruct MissileReaction;
                CountermeasureUseStruct CountermeasureUse;
                FormationUseStruct FormationUse;
                JobStruct Job;
        };

        struct IMPORT ContentCallback
        {
                virtual void combat_drift_event();
                virtual void combat_state_notification(enum CSNType, unsigned int, unsigned int);
                virtual void follow_event(unsigned int, unsigned int, enum FollowStatusType, float);
                virtual enum CreationType get_creation_type();
                virtual bool information_request(enum InformationType, int, char*);
                virtual void lead_object_event(unsigned int, unsigned int, enum LeadProgressType, float, const Vector&);
                virtual bool request_flee_destination(unsigned int, enum FleeReason, enum FleeDestinationType&, Vector&, unsigned int&, float&);
                virtual void scan_state_change(bool);
                virtual void ship_in_sights_event(unsigned int);
                virtual void tether_object_event(unsigned int, unsigned int, enum TetherStatusType, const Vector&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT BaseOp
        {
            public:
                BaseOp(OpType);
                BaseOp(const BaseOp&);

                virtual bool validate();

                OpType op_type;
                int fireWeapons; // Probably a bool, anything non-zero turns it on
        };

        class IMPORT DirectiveCancelOp : public BaseOp
        {
            public:
                DirectiveCancelOp(const DirectiveCancelOp&);
                DirectiveCancelOp();
                virtual bool validate();
        };

        class IMPORT DirectiveDelayOp : public BaseOp
        {
            public:
                DirectiveDelayOp(const DirectiveDelayOp&);
                DirectiveDelayOp();
                virtual bool validate();

                float DelayTime;
        };

        class IMPORT DirectiveDockOp : public BaseOp
        {
            public:
                DirectiveDockOp(const DirectiveDockOp&);
                DirectiveDockOp();
                virtual bool validate();

                uint DockSpaceObj;
                uint x10;   // 0
                ushort x12; // 0
                ushort x14; // 0xbb, 0x83 ??
                int x18;    // -1
                uint x1C;   // 0
                float x20;  // 200
                float x24;  // 500
                uint x28;   // 0
        };

        class IMPORT DirectiveDrasticEvadeOp : public BaseOp
        {
            public:
                DirectiveDrasticEvadeOp(const DirectiveDrasticEvadeOp&);
                DirectiveDrasticEvadeOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveEvadeOp : public BaseOp
        {
            public:
                DirectiveEvadeOp(const DirectiveEvadeOp&);
                DirectiveEvadeOp();
                virtual bool validate();

                uint EvadeSpaceObj;
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveFaceOp : public BaseOp
        {
            public:
                DirectiveFaceOp(const DirectiveFaceOp&);
                DirectiveFaceOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveFollowOp : public BaseOp
        {
            public:
                DirectiveFollowOp(const DirectiveFollowOp&);
                DirectiveFollowOp();
                virtual bool validate();

                uint followSpaceObj;
                float maxDistance;
                Vector offset;
                float dunno2; // 400
        };

        class IMPORT DirectiveFormationOp : public BaseOp
        {
            public:
                DirectiveFormationOp(const DirectiveFormationOp&);
                DirectiveFormationOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveGotoOp : public BaseOp
        {
            public:
                DirectiveGotoOp(const DirectiveGotoOp&);
                DirectiveGotoOp();
                virtual bool validate();

                int gotoType; // 1 = Vec, 0 = Ship, 2 = spline, 3 = undefined
                // The target position if GotoType is 1.
                Vector pos;
                // If GotoType is 0 then move to this spaceobj. Do not set a pos if you
                // set this.
                uint targetId;
                // The 4 points to fly to if GotoType is 2
                Vector spline[4];
                // This specifies how close the NPC will attempt to get to the position
                float range;
                // This specifies the thrust in the range from 0-100. Use -1 for maximum.
                float thrust;
                // This specifies if the ship should move (*not* always set to true)
                bool shipMoves;
                // This specifies if the ship should move (always set to true)
                bool shipMoves2;
                // Set the follow to control if the ship will cruise or not. Do not set
                // both to true.
                bool goToCruise;
                bool goToNoCruise;
                int x5C;
                float x60; // 200
                float x64; // 500
                int x68;
                float x6C;
        };

        class IMPORT DirectiveGuideOp : public BaseOp
        {
            public:
                DirectiveGuideOp(const DirectiveGuideOp&);
                DirectiveGuideOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveIdleOp : public BaseOp
        {
            public:
                DirectiveIdleOp(const DirectiveIdleOp&);
                DirectiveIdleOp();
                virtual bool validate();
        };

        class IMPORT DirectiveInstantTradelaneOp : public BaseOp
        {
            public:
                DirectiveInstantTradelaneOp(const DirectiveInstantTradelaneOp&);
                DirectiveInstantTradelaneOp();
                virtual bool validate();

                uint tradelaneRingFrom;
                uint tradelaneRingTo;
                float dunno; // 3750
        };

        class IMPORT DirectiveLaunchOp : public BaseOp
        {
            public:
                DirectiveLaunchOp(const DirectiveLaunchOp&);
                DirectiveLaunchOp();
                virtual bool validate();

                uint launchFromObject;
                uint x10; // 2, cannot be -1, defaults to -1
                uint x14; // 1, cannot be 0, defaults to 0
        };

        class IMPORT DirectiveRamOp : public BaseOp
        {
            public:
                DirectiveRamOp(const DirectiveRamOp&);
                DirectiveRamOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveStrafeOp : public BaseOp
        {
            public:
                DirectiveStrafeOp(const DirectiveStrafeOp&);
                DirectiveStrafeOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveTractorBeamOp : public BaseOp
        {
            public:
                DirectiveTractorBeamOp(const DirectiveTractorBeamOp&);
                DirectiveTractorBeamOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveTrailOp : public BaseOp
        {
            public:
                DirectiveTrailOp(const DirectiveTrailOp&);
                DirectiveTrailOp();
                virtual bool validate();

                uint x0C;  // 10
                float x10; // 500
                uint x14;  // 0
                uint x18;  // 0
        };

        class IMPORT DirectiveWaitForPlayerManeuverOp : public BaseOp
        {
            public:
                DirectiveWaitForPlayerManeuverOp(const DirectiveWaitForPlayerManeuverOp&);
                DirectiveWaitForPlayerManeuverOp();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        class IMPORT DirectiveWaitForShip
        {
            public:
                DirectiveWaitForShip(const DirectiveWaitForShip&);
                DirectiveWaitForShip();
                virtual bool validate();

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        struct IMPORT GSplinePath
        {
                GSplinePath();
                GSplinePath& operator=(const GSplinePath&);

            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

        struct IMPORT SetFlagParams
        {
                SetFlagParams(const SetFlagParams&);
                SetFlagParams();
                virtual bool validate();

                uint x0C;  // 0
                float x10; // ??
                float x14; // ??
        };

        struct IMPORT SetPersonalityParams : public BaseOp
        {
                SetPersonalityParams();
                SetPersonalityParams(const SetPersonalityParams&);

                virtual bool validate();

                int stateGraph;
                ContentCallback* contentCallback;
                DirectiveCallback* directiveCallback;
                bool stateId; // true - state_graph_id, false - state_graph
                Personality personality;
        };

		// Note: op_type of SetZoneBehaviorParams is 1, indicating that the enum has a different meaning for pub::AI::SubmitState
		// Hex numbers behind dunno variables or in a comment indicate hex offset
		struct IMPORT SetZoneBehaviorParams : public BaseOp
		{
			SetZoneBehaviorParams(struct SetZoneBehaviorParams const &);
			SetZoneBehaviorParams(void);
			virtual bool validate(void);

			uint iZoneType;     // 0 = position, 1 = cuboid 2 = spaceobj
			uint iDunno_0x10;   // 0=?? 1=?? 2=delete user zone
			Vector vPosition;   // only used for iZoneType 0
			uint iSpaceObj;     // only used for iZoneType 2
			Vector vBoxCorner1; // only used for iZoneType 1
			Vector vBoxCorner2; // only used for iZoneType 1
			float fRadius;      // not used for iZoneType 1
		};

    }; // namespace AI

    namespace StateGraph
    {
        enum Type
        {
            TYPE_STANDARD = 0
        };

        IMPORT int get_state_graph(int, Type);
        IMPORT int get_state_graph(const char*, Type);
        IMPORT const IStateGraph* get_state_graph_internal(int);
        IMPORT void refresh_state_graph();
    }; // namespace StateGraph

}; // namespace pub

struct IMPORT IDirectiveInfo
{
        bool init; // ? seems to be 1 after first time auto pilot takes over
        void* vUnknown1;
        pub::AI::OpType op;
};

// Size: 460 bytes
// Constructor e.g. sub_62D2220
// Hex numbers behind dunno variables or in a comment indicate hex offset
class IMPORT IBehaviorManager
{
    public:
        enum IBehaviorCameraMode
        {
            A,
            B,
            C,
            D,
            E
        };

        bool allow_head_tracking();
        bool cancel_behavior(enum CancelRequestType);
        bool enable_all_maneuvers();
        bool enable_maneuver(int, bool);
        enum EvaluateResult external_player_evaluate(int);
        bool get_camera_level_status();
        float get_closest_trailing_ship() const;
        const struct IDirectiveInfo* get_current_directive();
        const IObjRW* get_debugger_target() const;
        bool get_docking_port(const IObjRW*&, int&);
        unsigned int get_parent_id();
        void get_personality(pub::AI::Personality&);
        pub::AI::ScanResponse get_scan_response(unsigned int);
        const Vector get_ship_up_direction();
        const IStateGraph* get_state_graph();
        class SystemManager* get_sys();
        bool get_user_turning_input_state();
        bool lock_maneuvers(bool);
        void refresh_state_graph();
        void reset_current_behavior_direction();
        void set_camera_mode(IBehaviorCameraMode);
        void set_content_callback(pub::AI::ContentCallback*);
        bool set_current_directive(const IDirectiveInfo&, const pub::AI::BaseOp*);
        void set_directive_callback(pub::AI::DirectiveCallback*);
        pub::AI::OP_RTYPE set_directive_priority(pub::AI::DirectivePriority);
        void set_personality(const pub::AI::Personality&);
        void set_ship_up_direction(const Vector&);
        void set_state_graph(int, bool);
        void set_turn_sensitivity(float);
        void set_user_turning_input_state(bool);
        void submit_camera_up(const Vector&);
        void update_current_behavior_afterburner(bool);
        void update_current_behavior_auto_avoidance(bool);
        void update_current_behavior_auto_level(bool);
        void update_current_behavior_brake_reverse(bool);
        void update_current_behavior_cruise(bool);
        void update_current_behavior_direction(const Vector&);
        void update_current_behavior_engage_engine(bool);
        void update_current_behavior_slide_strafe_burst(StrafeDir);
        void update_current_behavior_throttle(float);
        void update_level_camera(bool);

    public:
        int* vft;                        // 0x00
        IStateGraph* stateGraphInternal; // 0x04
        void* pDunno_0x08;
        struct PathfindManager* pathfindManager; // 0x0C
        int iDunnos_0x10[42];
        int iEnabledManeuversFlag;     // 0xB8 - 0 = all enabled
        bool bLockManeuvers;           // 0xBC
        int iCurrentBehaviourIndex;    // 0xC0 - -1 when no behaviour, otherwise index of behaviourArray
        IDirectiveInfo* directiveInfo; // 0xC4
        int iDirectivePriority;        // 0xC8
        int iDunno_0xCC;
        float fDunno_0xD0;
        float fDunno_0xD4;
        byte bDunno54_0xD8;
        float fDunno55_0xDC;
        float fDunno56_0xE0;
        float fDunno57_0xE4;
        int iDunnos58_0xE8[2];
        BaseWatcher baseWatcher; // 0xF0
        byte bDunno62_0xF8;
        bool bCameraLevelStatusFlag;                       // 0xF9
        pub::AI::DirectiveCallback* directiveCallbacks[5]; // 0xFC
        pub::AI::ContentCallback* contentCallback;         // 0x110
        int iDunnos_0x114[7];
        bool bDunno_0x130;
        Vector shipUpDirection;   // 0x134
        Vector cameraUpDirection; // 0x140
        int iDunno_0x14C;
        bool bUserTurningInputState;    // 0x150
        IBehaviorCameraMode cameraMode; // 0x154
        byte bDunno_0x158;
        void* pDunno_0x15C;
        int iDunnos_0x160;
        float fTurnSensitivity; // 0x164
        byte bDunno_0x168;
        byte bDunno_0x169;
        int iDunno_0x16C;
        byte bDunno_0x170;
        struct Behavior* behaviourArray[21]; // 0x174 - index 7 seems to be docking
        byte bDunno_0x1C8;
};

struct IMPORT ICRSplineSegment
{
        ICRSplineSegment();
        ICRSplineSegment& operator=(const ICRSplineSegment&);
        void calculate_arclength();
        Vector calculate_spline_tangent(float);
        Vector calculate_spline_vector(float);
        float get_spline_length();
        float get_t_from_point(const Vector&, float, float);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT IObjInspectImpl
{
        virtual const Vector& get_position() const;
        virtual Vector get_velocity() const;
        virtual Vector get_angular_velocity() const;
        virtual const Matrix& get_orientation() const;
        virtual const Transform& get_transform() const;
        virtual Vector get_center_of_mass() const;
        virtual int get_sub_obj_center_of_mass(unsigned short, Vector&) const;
        virtual long get_index() const;
        virtual const unsigned int get_id() const;
        virtual int get_good_id(unsigned int&) const;
        virtual int get_archetype_extents(Vector&, Vector&) const;
        virtual int get_physical_radius(float&, Vector&) const;
        virtual float get_mass() const;
        virtual bool is_targetable() const;
        virtual bool is_dying() const;
        virtual int get_status(float&) const;
        virtual int get_status(float&, float&) const;
        virtual int get_shield_status(float&, bool&) const; // why in different order ?! msvc i hate you!
        virtual int get_shield_status(float&, float&, bool&) const;
        virtual int get_throttle(float&) const;
        virtual int get_axis_throttle(Vector&) const;
        virtual int get_nudge_vec(Vector&) const;
        virtual int get_strafe_dir(StrafeDir&) const;
        virtual int is_cruise_active(bool&) const; // why in different order ?! msvc i hate you! both is_cruise_active dont work properly for players(always
                                                   // return false when engine kill was used during cruise)
        virtual int is_cruise_active(bool&, bool&) const;
        virtual int are_thrusters_active(bool&) const;
        virtual int get_attitude_towards(float&, const IObjInspect*) const;
        virtual int get_attitude_towards_symmetrical(float&, const IObjInspect*, float&) const;
        virtual int get_reputation(float&, const unsigned int&) const;
        virtual int get_target(IObjRW*&) const;
        virtual int get_subtarget(unsigned short&) const;
        virtual int get_subtarget_center_of_mass(Vector&) const;
        virtual int get_rank(unsigned int&) const;
        virtual int get_affiliation(unsigned int&) const;
        virtual int get_type(unsigned int&) const;
        virtual int get_base(unsigned int&) const;
        virtual int get_dock_target(unsigned int&) const;
        virtual int get_power(float&) const;
        virtual int get_zone_props(unsigned long&) const;
        virtual float get_scanner_interference() const;
        virtual int get_hold_left(float&) const;
        virtual int enumerate_cargo(IObjInspect::CargoEnumerator*) const;
        virtual int get_data(const void*&) const;
        virtual int get_formation_offset(Vector&) const;
        virtual int get_formation_leader(IObjRW*&) const;
        virtual int get_follow_offset(Vector&) const;
        virtual int get_follow_leader(IObjRW*&) const;
        virtual bool is_player() const;
        virtual int get_hardpoint(const char*, Vector*, Matrix*) const;
        virtual bool has_dock_hardpoints() const;
        virtual int get_dock_hardpoints(int, enum TERMINAL_TYPE*, Transform*, Transform*, Transform*, float*) const;
        virtual float get_time_to_accelerate(float, float, float, IObject::ThrustEquipType) const;
        virtual float get_distance_travelled(float, float, float, IObject::ThrustEquipType) const;
        virtual float get_projected_throttle(float, IObject::ThrustEquipType) const;
        virtual float get_speed(float, IObject::ThrustEquipType) const;
        virtual float get_initial_speed_to_coast_distance(float, bool) const;
        virtual float get_time_to_accelerate_angularly(float, float, float) const;
        virtual float get_time_to_accelerate_angularly(float, float, float, float) const;
        virtual float get_angular_distance_travelled(float, float, float) const;
        virtual float get_angular_distance_travelled(float, float, float, float) const;
        virtual float get_angular_speed_XY(float, float) const;
        virtual float get_angular_speed_Z(float) const;
        virtual float get_projected_axis_throttle_XY(float) const;
        virtual float get_projected_axis_throttle_Z(float) const;
        virtual float get_max_bank_angle() const;
        virtual int get_scanlist(const struct ScanList*&, unsigned int, bool) const;
        virtual int get_tgt_lead_fire_pos(const unsigned short&, Vector&) const;
        virtual int is_pointing_at(bool&, const unsigned short&, float) const;
        virtual int can_point_at(bool&, const unsigned short&, const Vector&, float) const;
        virtual int find_equipment(unsigned short* const, unsigned int, unsigned int) const;
        virtual int get_equipment_status(EquipStatus&, const unsigned short&) const;
        virtual int get_equipment_val(struct EquipmentVal&, const unsigned short&, enum EquipmentValType, float) const;
        virtual int scan_cargo(IObjRW*, EquipDescVector&) const;
        virtual int enumerate_subtargets(IObjInspect::SubtargetEnumerator*) const;
        virtual int get_lane_direction(const Transform&, bool*) const;
        virtual int get_ring_side(const Transform&, bool*) const;
        virtual int traverse_rings(unsigned int&, bool) const;
        virtual int is_using_tradelane(bool*) const;
        virtual int get_lane_start(const IObjInspect*, const IObjInspect*&, Vector&, Vector&) const;
        virtual bool generate_follow_offset(const IObjInspect*, Transform&) const;
        virtual int get_atmosphere_range(float&) const;
        virtual int get_toughness() const;
        virtual int get_behavior_id() const;
        virtual int get_formation_followers(IObjRW** const, unsigned int) const;
        virtual const CObject* cobject() const;

    public:
        CObject* cobj;
};

struct IObjRWAbstract
{
    virtual const Vector& get_position() const;                                                                     //0
    virtual Vector get_velocity() const;                                                                            //4
    virtual Vector get_angular_velocity() const;                                                                    //8
    virtual const Matrix& get_orientation() const;                                                                  //12
    virtual const Transform& get_transform() const;                                                                 //16
    virtual Vector get_center_of_mass() const;                                                                      //20
    virtual int get_sub_obj_center_of_mass(unsigned short, Vector&) const;                                          //24
    virtual long get_index() const;                                                                                 //28
    virtual const unsigned int get_id() const;                                                                      //32
    virtual int get_good_id(unsigned int&) const;                                                                   //36
    virtual int get_archetype_extents(Vector&, Vector&) const;                                                      //40
    virtual int get_physical_radius(float&, Vector&) const;                                                         //44
    virtual float get_mass() const;                                                                                 //48
    virtual bool is_targetable() const;                                                                             //52
    virtual bool is_dying() const;                                                                                  //56
    virtual int get_status(float&) const;                                                                           //60
    virtual int get_status(float&, float&) const;                                                                   //64
    virtual int get_shield_status(float&, bool&) const;                                                             //68
    virtual int get_shield_status(float&, float&, bool&) const;                                                     //72
    virtual int get_throttle(float&) const;                                                                         //76
    virtual int get_axis_throttle(Vector&) const;                                                                   //80
    virtual int get_nudge_vec(Vector&) const;                                                                       //84
    virtual int get_strafe_dir(StrafeDir&) const;                                                                   //88
    virtual int is_cruise_active(bool&) const;                                                                      //92
    virtual int is_cruise_active(bool&, bool&) const;                                                               //96
    virtual int are_thrusters_active(bool&) const;                                                                  //100
    virtual int get_attitude_towards(float&, const IObjInspect*) const;                                             //104
    virtual int get_attitude_towards_symmetrical(float&, const IObjInspect*, float&) const;                         //108
    virtual int get_reputation(float&, const unsigned int&) const;                                                  //112
    virtual int get_target(IObjRW*&) const;                                                                         //116
    virtual int get_subtarget(unsigned short&) const;                                                               //120
    virtual int get_subtarget_center_of_mass(Vector&) const;                                                        //124
    virtual int get_rank(unsigned int&) const;                                                                      //128
    virtual int get_affiliation(unsigned int&) const;                                                               //132
    virtual int get_type(unsigned int&) const;                                                                      //136
    virtual int get_base(unsigned int&) const;                                                                      //140
    virtual int get_dock_target(unsigned int&) const;                                                               //144
    virtual int get_power(float&) const;                                                                            //148
    virtual int get_zone_props(unsigned long&) const;                                                               //152
    virtual float get_scanner_interference() const;                                                                 //156
    virtual int get_hold_left(float&) const;                                                                        //160
    virtual int enumerate_cargo(IObjInspect::CargoEnumerator*) const;                                               //164
    virtual int get_data(const void*&) const;                                                                       //168
    virtual int get_formation_offset(Vector&) const;                                                                //172
    virtual int get_formation_leader(IObjRW*&) const;                                                               //176
    virtual int get_follow_offset(Vector&) const;                                                                   //180
    virtual int get_follow_leader(IObjRW*&) const;                                                                  //184
    virtual bool is_player() const;                                                                                 //188
    virtual int get_hardpoint(const char*, Vector*, Matrix*) const;                                                 //192
    virtual bool has_dock_hardpoints() const;                                                                       //196
    virtual int get_dock_hardpoints(int, enum TERMINAL_TYPE*, Transform*, Transform*, Transform*, float*) const;    //200
    virtual float get_time_to_accelerate(float, float, float, IObject::ThrustEquipType) const;                      //204
    virtual float get_distance_travelled(float, float, float, IObject::ThrustEquipType) const;                      //208
    virtual float get_projected_throttle(float, IObject::ThrustEquipType) const;                                    //212
    virtual float get_speed(float, IObject::ThrustEquipType) const;                                                 //216
    virtual float get_initial_speed_to_coast_distance(float, bool) const;                                           //220
    virtual float get_time_to_accelerate_angularly(float, float, float) const;                                      //224
    virtual float get_time_to_accelerate_angularly(float, float, float, float) const;                               //228
    virtual float get_angular_distance_travelled(float, float, float) const;                                        //232
    virtual float get_angular_distance_travelled(float, float, float, float) const;                                 //236
    virtual float get_angular_speed_XY(float, float) const;                                                         //240
    virtual float get_angular_speed_Z(float) const;                                                                 //244
    virtual float get_projected_axis_throttle_XY(float) const;                                                      //248
    virtual float get_projected_axis_throttle_Z(float) const;                                                       //252
    virtual float get_max_bank_angle() const;                                                                       //256
    virtual int get_scanlist(const struct ScanList*&, unsigned int, bool) const;                                    //260
    virtual int get_tgt_lead_fire_pos(const unsigned short&, Vector&) const;                                        //264
    virtual int is_pointing_at(bool&, const unsigned short&, float) const;                                          //268
    virtual int can_point_at(bool&, const unsigned short&, const Vector&, float) const;                             //272
    virtual int find_equipment(unsigned short* const, unsigned int, unsigned int) const;                            //276
    virtual int get_equipment_status(struct EquipStatus&, const unsigned short&) const;                             //280
    virtual int get_equipment_val(struct EquipmentVal&, const unsigned short&, enum EquipmentValType, float) const; //284
    virtual int scan_cargo(IObjRW*, EquipDescVector&) const;                                                        //288
    virtual int enumerate_subtargets(IObjInspect::SubtargetEnumerator*) const;                                      //292
    virtual int get_lane_direction(const Transform&, bool*) const;                                                  //296
    virtual int get_ring_side(const Transform&, bool*) const;                                                       //300
    virtual int traverse_rings(unsigned int&, bool) const;                                                          //304
    virtual int is_using_tradelane(bool*) const;                                                                    //308
    virtual int get_lane_start(const IObjInspect*, const IObjInspect*&, Vector&, Vector&) const;                    //312
    virtual bool generate_follow_offset(const IObjInspect*, Transform&) const;                                      //316
    virtual int get_atmosphere_range(float&) const;                                                                 //320
    virtual int get_toughness() const;                                                                              //324
    virtual int get_behavior_id() const;                                                                            //328
    virtual int get_formation_followers(IObjRW** const, unsigned int) const;                                        //332
    virtual const CObject* cobject() const;                                                                         //336
    virtual ObjectType get_object_type() const;                                                                     //340
    
    virtual bool ShipDestroyed(bool isKill, uint dunno); // NakedShipDestroyed                                      //344 sub_6CE8080
    virtual int Disconnect();                                                                                       //348 sub_6CE7C80
    virtual bool get_dunno_0x40();                                                                                  //352 sub_6CEE6D0
    virtual int instantiate_cship(Archetype::Root* archPtr);                                                        //356 sub_6D01040
    virtual bool set_cship(uint shipId);                                                                            //360 sub_6D010A0
    virtual void sub_6D01450();                                                                                     //364
    virtual void sub_6D01A60();                                                                                     //368
    virtual int  sub_6CEE810(void* PhySys_unk); // physics collsion handling?                                       //372
    virtual void sub_6CEE980(int dunno); // Behavior interface update?                                              //376
    virtual void sub_6CE9250(void* unk, DamageList*);                                                               //380
    virtual void sub_6CE9350(void* unk, DamageList*);                                                               //384
    virtual void process_all_explosion_damage(ExplosionDamageEvent*, DamageList*); // calls methods 508-520         //388
    virtual void sub_6D01A10();                                                                                     //392
    virtual bool get_dunno_0x41();                                                                                  //396
    virtual void sub_6CEEFA0();                                                                                     //400
    virtual void sub_6CEF0F0();                                                                                     //404
    virtual bool is_player_vulnerable();                                                                            //408 sub_6CE61A0
    virtual bool is_invulnerable();                                                                                 //412 sub_6CE61B0
    virtual float get_dunno_0x3C(); //hitpoint % related?                                                           //416 sub_6CE61C0
    virtual bool process_collision_unk(void*); // unknown data type, an object containing a IObjRW as 2nd element?? //420 sub_6CEE9F0
    virtual CArchGroup* sethp_unk(DamageList*, float); // set relative hp to all eq and colgrps to provided float?  //424 sub_6CEB210
    virtual int set_relative_health(float newHp);                                                                   //428
    virtual bool damage_hull(float, DamageList*); // NakedDamageHit                                                 //432 sub_6CEA3A0
    virtual void apply_damage_entry(DamageEntry*);                                                                  //436 sub_6CEEF70
    virtual bool can_deal_damage(DamageList*); // invokes get_dunno_0x39 and 0x38                                   //440 sub_6CEF0B0
    virtual void sub_6CE7D00(); // collision groups, sets off fuses?                                                //444
    virtual void sub_6CE8C50(); // damage dealing method, sets off death animation?                                 //448
    virtual void sub_6CE8D40(); // same as above, but for collision groups                                          //452
    virtual void sub_6CE8CD0(); // collision group related                                                          //456
    virtual void sub_6CE8E90(); // hardpoint eq related                                                             //460
    virtual void sub_6CE8E10(); // hardpoint eq related                                                             //464
    virtual bool sub_6CE8F50(char const*, DamageList*); // iterate over cargo, dunno                                //468
    virtual bool hit_shield_bubble(DamageList*);                                                                    //472
    virtual void sub_6CE88D0(); // iterate over all equipped equipment and run an update?                           //476
    virtual void sub_6CE8930(); // processes values under 0x74 and 0x78 pointers                                    //480
    virtual bool light_fuse(uint dunno, ID_String fuse, ushort sId, float radius, float fuseLifetime);              //484 sub_6D01A90
    virtual bool unlight_fuse_unk(uint fuseId, ushort sid, float lifeTime);                                         //488 sub_6CEC7F0
    virtual bool fuse_expiration_check();                                                                           //492 sub_6CEC8D0
    virtual void death_explosion();                                                                                 //496 sub_6CE8400
    virtual void sub_6D01C90();                                                                                     //500
    virtual void sub_6CE8760();                                                                                     //504
    virtual void process_explosion_damage_hull(ExplosionDamageEvent* explosion, DamageList* dmgList);               //508 sub_6CE9550
    virtual const CArchGroup* process_explosion_damage_external_equip_and_col_grps(ExplosionDamageEvent* explosion, DamageList* dmgList);//512 sub_6CE9690
    virtual bool process_explosion_damage_shield_bubble(ExplosionDamageEvent* explosion, DamageList* dmgList); // NakedGuidedHit   //516 sub_6CE9A90
    virtual void process_explosion_damage_energy(ExplosionDamageEvent* explosion, DamageList* dmgList);             //520 sub_6CE9940
    virtual void damage_shield(CEShield* shield, Archetype::Munition* munition, DamageList* dmgList);               //524 sub_6CE94B0
    virtual bool damage_ext_eq(CEquip* eq, float dmgDealt, DamageList* dmgList);                                    //528 sub_6CEA4A0
    virtual bool damage_general(IObjInspectImpl* target, float dmg, DamageList* dmgList); // NakedDamageHit2        //532 sub_6CEA740
    virtual bool damage_col_grp(CArchGroup*, float, DamageList*);                                                   //536 sub_6CEAA80
    virtual bool damage_energy(float energyDamage, DamageList* dmgList); // deal energy damage                      //540 sub_6CEAFC0
    virtual void col_grp_death(CArchGroup*, DamageEntry::SubObjFate, DamageList*);                                  //544 sub_6CEA9F0
    virtual void cequip_death(CEquip* eq, DamageEntry::SubObjFate fate, DamageList* dmgList);                       //548 sub_6CE9F70
    virtual void unk_death(void* dunno1, DamageEntry::SubObjFate fate, DamageList* dmgList);                        //552 sub_6CE9C50
    virtual EquipmentClass deal_colgrp_linked_damage(CArchGroup* colGrp, DamageList* dmgList);                      //556 sub_6CEADC0
    virtual const CArchGroup* sub_6CEAEA0_unk(CArchGroup* colGrp, DamageList* dmgList); // colgrp update method checking for lost equipment? idk. //560 sub_6CEAEA0
    virtual void AI_react_to_hull_dmg(DamageList*, DamageEntry*);                                                   //564 sub_6CEB550
    virtual void AI_react_to_equip_dmg(DamageList*, DamageEntry*);                                                  //568 sub_6CEB7B0
    virtual void AI_react_to_energy_dmg(DamageList*, DamageEntry*);                                                 //572 sub_6CEBD40
    virtual void AI_react_to_colgrp_dmg(DamageList*, DamageEntry*);                                                 //576 sub_6CEBA40
    virtual void sub_6CEBE80();                                                                                     //580 sub_6CEBE80
    virtual bool sub_6CEC260(CAttachedEquip* attachedEq); // equipment related, always returns true, can't trigger  //584 sub_6CEC260
    virtual void process_perishable_cargo(float deltaTime);                                                         //588 sub_6CEC910 

};

struct CShipAbstract
{
    virtual void set_throttle(float);                           //0
    virtual void set_axis_throttle(const Vector&);              //4
    virtual void set_nudge_vec(const Vector&);                  //8
    virtual int set_strafe_dir(StrafeDir);                      //12
    virtual void sub_6D029C0();                                 //16
    virtual void sub_6D02940();                                 //20
    virtual FORMATION_RTYPE add_formation_follower(IObjRW*);    //24
    virtual FORMATION_RTYPE remove_formation_follower(IObjRW*); //28
    virtual int get_formation_follower_count();                 //32
    virtual void set_follow_leader(IObjRW*);                    //36
    virtual void set_follow_offset(const Vector&);              //40
    virtual FORMATION_RTYPE add_follow_follower(IObjRW*);       //44
    virtual FORMATION_RTYPE remove_follow_follower(IObjRW*);    //48
    virtual void sub_6CE68A0();                                 //52
    virtual void sub_6D020D0();                                 //56
    virtual void sub_6CE6D80();                                 //60
    virtual void sub_6CE6BA0();                                 //64
    virtual void sub_6CE6F60();                                 //68
    virtual void sub_6D02340();                                 //72
    virtual void sub_6CE70B0();                                 //76
    virtual void sub_6D02410();                                 //80
    virtual void sub_6D02500();                                 //84
    virtual void sub_6CE7210();                                 //88
    virtual void sub_6D02670();                                 //92
    virtual void sub_6D027A0();                                 //96
    virtual void sub_6D028C0();                                 //100
    virtual void sub_6D02880();                                 //104
    virtual void sub_6CEF350();                                 //108
    virtual void sub_6D02000();                                 //112
    virtual void sub_6D02070();                                 //116
    virtual void abstractMethod() = 0;
};

// Constructor seems to be e.g. sub_6D02B70
// Size: 144 bytes
// Hex numbers behind dunno variables or in a comment indicate hex offset
struct IObjRW : public IObjRWAbstract, public CShipAbstract
{
    Watchable watchable;
    IObjInspectImpl iObjInspectImpl;
    byte bDunno_0x14;
    void* pDunno_0x18; // struct size: 12 bytes
    int iDunnos_0x1C; // length of 0x1C
    double timer;
    int iDunnos_0x28;// last element has something to do with fuses
    byte bDunno_0x2C;
    void* pDunno_0x30; // struct size: 20 bytes
    int iDunno_0x34; // length of 0x30
    byte isInvulnerable; // not entirely sure on those two
    byte isPlayerVulnerable;
    float fDunno_0x3C; // hitpoint related?
    byte bDunno_0x40;
    byte bDunno_041;
    byte bAlign_0x42; // probably not used
    byte bAlign_0x43; // probably not used
    byte bDunno_0x44;
    void* pDunno_0x48; // struct size: 20 bytes
    int iDunno_0x4C; // size of 0x48
    byte bDunno_0x50;
    int iDunnos_0x54[3];
    byte bDunno_0x60;
    void* pDunno_0x64; // struct size: 16 bytes
    int iDunnos_0x68; // 0x64 size
    float fdunno_0x6C;
    byte bDunno_0x70;
    void* pDunno_0x74; // struct size: 12 bytes onedirectional list that loops
    int iDunno_0x78; // length of 0x74 chain
    byte bDunno_0x7C;
    void* pDunno_0x80; // struct size: 68 bytes list of fuses?
    int iDunno_0x84; // 0x80 length
    byte bDunno_0x88; // flagged on ShipDestroyed
    int iDunno_0x8C;
};

class IMPORT ImageNode
{
    public:
        ImageNode(const ImageNode&);
        ImageNode(const TextRenderContext::Image*);
        ImageNode();
        virtual ~ImageNode();
        ImageNode& operator=(const ImageNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const TextRenderContext::Image* get_image();
        void set_image(const TextRenderContext::Image*);

        virtual operator ImageNode*();
        virtual operator const ImageNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace LaunchActionVars
{
    //@@@TODO	IMPORT  float const  launch_coast_time;
    //@@@TODO	IMPORT  float const  launch_decel_time;
};

struct IMPORT LineParser32
{
        LineParser32();
        LineParser32& operator=(const LineParser32&);
        void clear();
        unsigned int fetch_string(char*, unsigned int);
        int find_char(char) const;
        char get_char() const;
        unsigned int read_string(char*, const char*);
        unsigned int read_terminator2(char*, char, char);
        unsigned int read_terminator(char*, char);
        void set(const char*, unsigned int);
        bool skip_char(char);
        void skip_white();
        bool terminate_line(char);
        bool whitespace(char) const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace Loadout
{
    struct IMPORT Map
    {
            Map(const Map&);
            Map();
            ~Map();
            Map& operator=(const Map&);

        public:
            uint id;
            char cdunno; // -1
            EquipDesc* first;
            EquipDesc* last;
            EquipDesc* end;
    };

    IMPORT void Free();
    IMPORT const Map* Get(unsigned int);
    IMPORT unsigned int GetID(const char*);
    IMPORT int Load(const char*, bool);
    IMPORT bool ReadCargoLine(INI_Reader&, EquipDesc&);
    IMPORT bool ReadEquipLine(INI_Reader&, EquipDesc&);
}; // namespace Loadout

//
// Defined in FLCoreDALib.h
//-------------------------
// class IMPORT MD5Hash
//{
// public:
//	MD5Hash(class MD5Hash const &);
//	class MD5Hash & operator=(class MD5Hash const &);
//	unsigned char * GetStatePtr();

// public:
//	unsigned char data[OBJECT_DATA_SIZE];
// };

struct IMPORT MPCritSec
{
        MPCritSec();
        ~MPCritSec();
        MPCritSec& operator=(const MPCritSec&);
        void lock();
        void unlock();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

enum TransactionType
{
    TransactionType_Sell = 0,
    TransactionType_Buy = 1
};

struct IMPORT MarketGoodInfo
{
        MarketGoodInfo();
        MarketGoodInfo& operator=(const MarketGoodInfo&);

    public:
        uint goodId;
        float price;
        int min;
        int stock;
        TransactionType transType;
        float rank;
        float rep;
        int quantity;
        float scale;
};

class IMPORT MarshalBuffer
{
    public:
        MarshalBuffer();
        MarshalBuffer& operator=(const MarshalBuffer&);
        void clear();
        Costume get_Costume();
        EquipDescList get_EquipDescList();
        unsigned int get_FL_ID();
        FmtStr get_FmtStr();
        GoodDescList get_GoodDescList();
        unsigned short get_U16();
        unsigned long get_U32();
        unsigned char get_U8();
        bool get_bool();
        const unsigned char* get_buffer() const;
        int get_buffer_size() const;
        float get_float();
        void get_image(unsigned char*);
        void get_image(unsigned short*);
        void get_image(int*);
        void get_image(unsigned long*);
        void get_image(float*);
        int get_int();
        int get_num_written() const;
        char* get_string();
        void get_string_to_buffer(char*, int);
        void get_void(void*, int);
        unsigned short* get_wstring();
        bool is_empty() const;
        void put_Costume(const Costume&);
        void put_EquipDescList(const EquipDescList&);
        void put_FL_ID(unsigned int);
        void put_FmtStr(const FmtStr&);
        void put_GoodDescList(const GoodDescList&);
        void put_U16(unsigned short);
        void put_U32(unsigned long);
        void put_U8(unsigned char);
        void put_bool(bool);
        void put_float(float);
        void put_image(const unsigned char&);
        void put_image(const unsigned short&);
        void put_image(const int&);
        void put_image(const unsigned long&);
        void put_image(const float&);
        void put_int(int);
        void put_string(const char*);
        void put_void(const void*, int);
        void put_wstring(const unsigned short*);
        void skip_over(int);
        void use_default();
        void use_read_buffer(const unsigned char*, int);
        void use_write_buffer(unsigned char*, int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

/* struct IMPORT MessageHandler
{
    MessageHandler(class IMessageRouter *);
    virtual ~MessageHandler();
    unsigned int get_id()const ;

protected:
    virtual void send_delayed_message(class StateMachineMessage *,float,unsigned int);
    virtual void send_delayed_message_to_me(class StateMachineMessage *,float,int);
    virtual void send_immediate_message(class StateMachineMessage *,unsigned int);

public:
    unsigned char data[OBJECT_DATA_SIZE];
};*/

class IMPORT MissionVendorAcceptance
{
    public:
        MissionVendorAcceptance(const MissionVendorAcceptance&);
        MissionVendorAcceptance();
        ~MissionVendorAcceptance();
        MissionVendorAcceptance& operator=(const MissionVendorAcceptance&);
        void clear();
        void destroy();
        unsigned long get_key() const;
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT MissionVendorProperties
{
    public:
        MissionVendorProperties(const MissionVendorProperties&);
        MissionVendorProperties();
        ~MissionVendorProperties();
        MissionVendorProperties& operator=(const MissionVendorProperties&);
        void clear();
        void destroy();
        const char* get_icon_texture() const;
        unsigned long get_key() const;
        void init(const struct MissionVendorOfferDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace NewChar
{
    struct Pilot
    {
            uint nickname;
            st6::string body;
            st6::vector<st6::string> bodyAnims;
            st6::string comm;
            st6::vector<st6::string> commAnims;
            st6::string voice;
    };

    struct Package
    {
            uint nickname;
            int idsName;
            int idsDescription;
            st6::string ship;
            st6::string loadout;
            int money;
    };

    struct Faction
    {
            uint nickname;
            st6::string repGroup;
    };

    struct Base
    {
            uint nickname;
            st6::string nicknameStr;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class IDatabase // NOLINT
    {
        public:
            virtual Faction* FindFaction(uint faction);
            virtual Package* FindPackage(uint package);
            virtual Pilot* FindPilot(uint pilot);
            virtual Base* FindBase(uint base);
            virtual void UnknownMethod16(DWORD arg1);
            virtual void UnknownMethod20(DWORD arg1);
            virtual void UnknownMethod24(DWORD arg1);
            virtual void UnknownMethod28(DWORD arg1);
            virtual void UnknownMethod32(DWORD arg1);
            virtual void UnknownMethod36(DWORD arg1);
            virtual void UnknownMethod40(DWORD arg1);
            virtual void UnknownMethod44(DWORD arg1);
            virtual void UnknownMethod48(DWORD arg1);
            virtual void LoadNewCharacterIni(const char* fileBuffer);
    };

    IMPORT IDatabase* TheDB;
}; // namespace NewChar

class IMPORT NewsBroadcastProperties
{
    public:
        NewsBroadcastProperties(const NewsBroadcastProperties&);
        NewsBroadcastProperties();
        ~NewsBroadcastProperties();
        NewsBroadcastProperties& operator=(const NewsBroadcastProperties&);
        void clear();
        void destroy();
        unsigned long get_key() const;
        const char* get_logo_texture() const;
        void init(const struct NewsBroadcastDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

// Size: 1408 bytes
// Constructor e.g. sub_62DB3B0
// Hex numbers behind dunno variables or in a comment indicate hex offset
struct IMPORT PathfindManager
{
        void clear_user_zone();
        bool get_user_zone(struct UserZone&);
        void submit_user_zone(const UserZone&);

    public:
        // size: 64 bytes
        struct UserZone
        {
            int iZoneType;                // 0 = position, 1 = cuboid 2 = spaceobj
            int iDunno_0x04;              // same as iDunno_0x10 from SetZoneBehaviorParams if iDunno_0x10 was 0 or 1
            Vector vPosition;             // only used for iZoneType 0
            float fRadius;                // not used for iZoneType 1
            Matrix mDunno_0x18;           // pub::AI::SubmitState sets this to identiy when SetZoneBehaviorParams is used and iZoneType is 1
            Vector vCuboidCenter;         // only used for iZoneType 1
            Vector vCuboidHalfEdgeLength; // only used for iZoneType 1
            int iSpaceObjId;              // only used for iZoneType 2
        };
        int iDunno_0x00;
        int iDunno_0x04;
        bool bHasUserZone; // 0x08
        UserZone userZone; // 0x0C
        int iDunnos_0x64[2];
        int iDunnoStruct_0x6C[8]; // struct size 32 bytes
        File* fileDunno_0x8C;
        int iDunnos_0x90[62];
        File* fileDunno_0x188;
        int iDunnos_0x188[7];
        float fDunno_0x1A8;
        int iDunno_0x1AC;
        byte bDunno_0x1B0;
        int iDunnos_0x1B4[3];
        IBehaviorManager* behaviorManager; // 0x1C0 - usually the one this one belongs to
        int iDunno_0x1C4;
        BaseWatcher baseWatcher_0x1C8;
        int iDunnos_0x1D0[4];
        float fDunno_0x1E0;
        float fDunno_0x1E4;
        float fDunno_0x1E8;
        float fdunno_0x1EC;
        int iDunno_0x1F0;
        float fDunno_0x1F4;
        float fDunno_0x1F8;
        float fDunno_0x1FC;
        int iDunnos_0x1F8[3];
        float fDunno_0x20C;
        float fDunno_0x210;
        int iDunno_0x214;
        BaseWatcher baseWatcher_0x218;
        int iDunnos_0x220[6];
        byte bDunno_0x238;
        float fDunno_0x23C;
        int iDunno_0x240;
        byte bDunno_0x244;
        byte bDunno_0x245;
        int iDunno_0x248;
        byte bDunno_0x24C;
        int iDunno_0x250;
        byte bDunno_0x254;
        int iDunno_0x258[3];
        byte bDunno_0x260;
        int iDunnos_0x264[198];
};

class IMPORT PetalInterfaceDatabase
{
    public:
        PetalInterfaceDatabase(const PetalInterfaceDatabase&);
        PetalInterfaceDatabase();
        ~PetalInterfaceDatabase();
        PetalInterfaceDatabase& operator=(const PetalInterfaceDatabase&);
        void destroy();
        const struct petal_record* find_record(int, unsigned long) const;
        static int get_category(const char*);
        void load_from_ini(const char*);

    private:
        void add_record(int, const char*, const char*, char**, int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

/*class IMPORT TextNode
{
    char Buf[1024];
public:
    TextNode(unsigned short const *,int);
    TextNode();
};*/

/*class IMPORT StyleNode
{
public:
    StyleNode(unsigned short);

public:
    unsigned char data[1024];
};*/

/*class IMPORT ParagraphNode
{
public:
    ParagraphNode();
};*/

/*class IMPORT RDLReNode
{
public:
    RDLReNode(class RDLReNode const &);

public:
    unsigned char data[1024];
};*/

/*class IMPORT JustifyNode
{
public:
    JustifyNode(enum TextJustify);

public:
    unsigned char data[1024];
};*/

class IMPORT NullNode
{
    public:
        NullNode(const NullNode&);
        NullNode();
        virtual ~NullNode();
        NullNode& operator=(const NullNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);

        virtual operator NullNode*();
        virtual operator const NullNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StyleNode
{
    public:
        StyleNode(const StyleNode&);
        StyleNode(unsigned short);
        StyleNode();
        /*virtual ~StyleNode();
        class StyleNode & operator=(class StyleNode const &);
        virtual class RDLNode * Clone()const ;
        virtual void Execute(class TextRenderContext &,bool);
        virtual void GetElementPos(int,class TextRenderContext &,int &)const ;
        virtual void GetElementSize(int &)const ;
        virtual void GetVisualSize(class TextRenderContext const &,struct VisualSize &)const ;
        virtual bool SplitAtSize(class TextRenderContext const &,int,unsigned int,class RDLNode * &,class RDLNode * &)const ;
        virtual void Update(float);
        unsigned short get_style_id();
        void set_style_id(unsigned short);

        virtual operator class StyleNode *();
        virtual operator class StyleNode const *()const ;*/

    public:
        unsigned char data[1024];
};

class IMPORT ParagraphNode
{
    public:
        ParagraphNode(const ParagraphNode&);
        ParagraphNode();
        /*virtual ~ParagraphNode();
        class ParagraphNode & operator=(class ParagraphNode const &);
        virtual class RDLNode * Clone()const ;
        virtual void Execute(class TextRenderContext &,bool);
        virtual void GetElementPos(int,class TextRenderContext &,int &)const ;
        virtual void GetElementSize(int &)const ;
        virtual void GetVisualSize(class TextRenderContext const &,struct VisualSize &)const ;
        virtual bool SplitAtSize(class TextRenderContext const &,int,unsigned int,class RDLNode * &,class RDLNode * &)const ;
        virtual void Update(float);

        virtual operator class ParagraphNode *();
        virtual operator class ParagraphNode const *()const ;*/
};

class IMPORT TextNode
{
        char Buf[1024];

    public:
        TextNode(const TextNode&);
        TextNode(const st6::wstring&, int);
        TextNode(const unsigned short*, int);
        TextNode();
        /*virtual ~TextNode();
        class TextNode & operator=(class TextNode const &);
        virtual class RDLNode * Clone()const ;
        virtual void Execute(class TextRenderContext &,bool);
        virtual void GetElementPos(int,class TextRenderContext &,int &)const ;
        virtual void GetElementSize(int &)const ;
        virtual void GetVisualSize(class TextRenderContext const &,struct VisualSize &)const ;
        virtual bool SplitAtSize(class TextRenderContext const &,int,unsigned int,class RDLNode * &,class RDLNode * &)const ;
        virtual void Update(float);
        void append_text(st6::wstring const &,int);
        void append_text(unsigned short const *,int);
        st6::wstring const & get_text()const ;
        void set_text(st6::wstring const &,int);
        void set_text(unsigned short const *,int);

        virtual operator class TextNode *();
        virtual operator class TextNode const *()const ;*/
};

class IMPORT TextPtrNode
{
    public:
        TextPtrNode(const TextPtrNode&);
        TextPtrNode(const unsigned short*, int);
        TextPtrNode();
        virtual ~TextPtrNode();
        TextPtrNode& operator=(const TextPtrNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const unsigned short* get_text() const;
        int get_text_length() const;
        void set_text(const unsigned short*, int);

        virtual operator TextPtrNode*();
        virtual operator const TextPtrNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT JustifyNode
{
    public:
        JustifyNode(const JustifyNode&);
        JustifyNode(enum TextJustify);
        virtual ~JustifyNode();
        JustifyNode& operator=(const JustifyNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        TextJustify get_justify();
        void set_justify(TextJustify);

        virtual operator JustifyNode*();
        virtual operator const JustifyNode*() const;

    public:
        unsigned char data[1024];
};

class IMPORT PositionNode
{
    public:
        PositionNode(const PositionNode&);
        PositionNode();
        virtual ~PositionNode();
        PositionNode& operator=(const PositionNode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        float get_pos_h();
        float get_pos_v();
        bool is_rel_h();
        bool is_rel_v();
        void set_pos(float, float);
        void set_pos_h(float);
        void set_pos_v(float);
        void set_rel_h(bool);
        void set_rel_v(bool);

        virtual operator PositionNode*();
        virtual operator const PositionNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RDLNode
{
    public:
        RDLNode(const RDLNode&);
        RDLNode();
        virtual ~RDLNode();
        RDLNode& operator=(const RDLNode&);

        virtual operator AttribStackNode*();
        virtual operator ClipNode*();
        virtual operator ImageNode*();
        virtual operator JustifyNode*();
        virtual operator NullNode*();
        virtual operator ParagraphNode*();
        virtual operator PositionNode*();
        virtual operator RDLReNode*();
        virtual operator StyleNode*();
        virtual operator TRANode*();
        virtual operator TextNode*();
        virtual operator TextPtrNode*();
        virtual operator const AttribStackNode*() const;
        virtual operator const ClipNode*() const;
        virtual operator const ImageNode*() const;
        virtual operator const JustifyNode*() const;
        virtual operator const NullNode*() const;
        virtual operator const ParagraphNode*() const;
        virtual operator const PositionNode*() const;
        virtual operator const RDLReNode*() const;
        virtual operator const StyleNode*() const;
        virtual operator const TRANode*() const;
        virtual operator const TextNode*() const;
        virtual operator const TextPtrNode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RDLReNode
{
    public:
        RDLReNode(RenderDisplayList&);
        RDLReNode(const RDLReNode&);
        virtual ~RDLReNode();
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const RenderDisplayList& get_list();

        virtual operator RDLReNode*();
        virtual operator const RDLReNode*() const;

    public:
        unsigned char data[1024];
};

struct IMPORT Rect
{
        Rect(int, int, int, int);
        Rect();
        Rect& operator=(const Rect&);
        int area() const;
        int bottommost() const;
        void clear();
        void get_center(int*, int*) const;
        int height() const;
        void init(int, int, int, int);
        void init_from_ltrb(int, int, int, int);
        int leftmost() const;
        bool nonnull() const;
        bool null() const;
        bool point_is_inside(int, int) const;
        int rightmost() const;
        int topmost() const;
        int width() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RenderDisplayList
{
    public:
        RenderDisplayList(const RenderDisplayList&);
        RenderDisplayList();
        ~RenderDisplayList();
        RenderDisplayList& operator=(const RenderDisplayList&);
        void execute(TextRenderContext&, bool);
        void get_dimensions(TextRenderContext&, float&, float&, float&);
        int get_element_count() const;
        bool get_element_pos(TextRenderContext&, int, float&, float&, float&);
        void optimize();
        void update(float);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace Reputation
{
    struct Relation
    {
            uint hash;
            float reptuation;
    };

    namespace Vibe
    {
        IMPORT int AdjustAttitude(const int&, const int&, float);
        IMPORT int Alloc(const int&);
        IMPORT int AttitudeTowards(const int&, const int&, float&);
        IMPORT int AttitudeTowardsSymmetrical(const int&, const int&, float&, float&);
        IMPORT unsigned int Count();
        IMPORT int EnsureExists(const int&);
        IMPORT int Free(const int&);
        IMPORT void FreeDynamic();
        IMPORT int Get(const int& repId, unsigned int& affiliation, unsigned int& rank, unsigned char& relationCount, Relation* const relations, FmtStr&,
                       FmtStr&, const unsigned short*& name);
        IMPORT int GetAffiliation(const int&, unsigned int&, bool);
        IMPORT unsigned int GetClientID(int);
        IMPORT int GetGroupFeelingsTowards(const int&, const unsigned int&, float&);
        IMPORT int GetInfocard(const int&, unsigned int&);
        IMPORT int GetName(const int&, FmtStr&, FmtStr&, const unsigned short*&);
        IMPORT int GetRank(const int&, unsigned int&);
        IMPORT int Set(const int&, unsigned int, unsigned int, unsigned char, const Relation* const, const FmtStr&, const FmtStr&, const unsigned short*);
        IMPORT int SetAffiliation(const int&, unsigned int, bool);
        IMPORT int SetAttitudeTowardsPlayer(int, float);
        IMPORT int SetClientID(int, unsigned int);
        IMPORT int SetGroupFeelingsTowards(const int&, const unsigned int&, float);
        IMPORT int SetInfocard(const int&, unsigned int);
        IMPORT int SetName(const int&, const FmtStr&, const FmtStr&, const unsigned short*);
        IMPORT int SetRank(const int&, unsigned int);
        IMPORT bool Verify(int);
    }; // namespace Vibe

    IMPORT void FreeFeelings();
    IMPORT st6::map<unsigned int, unsigned int, st6::less<unsigned int>, st6::allocator<unsigned int>>* GetChangedAffiliationClientMap();
    IMPORT bool IsStoryFaction(unsigned int);
    IMPORT void LoadFeelings(INI_Reader&);
    IMPORT void Save(struct ISave*);
    IMPORT void Shutdown();
    IMPORT bool Startup(const char*);
    IMPORT int affect_relation(const unsigned int&, const unsigned int&, float);
    IMPORT void enumerate(struct RepGroupCB*);
    IMPORT int get_feelings_towards(unsigned int, unsigned int, float&);
    IMPORT unsigned int get_id(const TString<16>&);
    IMPORT unsigned int get_info_card(unsigned int);
    IMPORT unsigned int get_name(unsigned int);
    IMPORT int get_nickname(TString<16>&, const unsigned int&);
    IMPORT unsigned int get_short_name(unsigned int);
    IMPORT unsigned int group_count();
    IMPORT void set(const TString<16>&, Relation* const, unsigned int);
}; // namespace Reputation

struct IMPORT RoomButtonInfo
{
        RoomButtonInfo();
        ~RoomButtonInfo();
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomCameraInfo
{
        RoomCameraInfo();
        ~RoomCameraInfo();
        RoomCameraInfo& operator=(const RoomCameraInfo&);
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct Camera
{
        char* vtable; // vftable
        Matrix rotation;
        Vector pos;
        bool bRenderNewCam; // 14
        Matrix rotation2;
        Vector pos2;
        float halfRes[2];
        float halfRes2[2];
        float fovXHud;
        float fovYHud;
        float cosFovX;
        float alwaysZeroFovX;
        float sinFovX;
        float alwaysZeroFovY;
        float cosFovY;
        float sinFovY;
        float fovX;
        float fovY;
        float aspect;
        float zNear;
        float zFar;
        uint screenExtents[4];
        uint dunno;
        Watchable* watchable; // 49
        uint dunno1[6];
        Vector dunno2;
        uint dunno3[6];
        Vector cameraOffset;
};

class IMPORT RoomData
{
    public:
        RoomData(const RoomData&);
        RoomData();
        ~RoomData();
        RoomData& operator=(const RoomData&);
        void clear();
        void destroy();
        void enumerate_CharacterPlacement_ini(void (*)(int, INI_Reader*, void*), void*) const;
        const RoomCameraInfo* find_camera(const char*, const char*) const;
        const RoomCameraInfo* find_camera_generic(const char*, const char*) const;
        const struct SetpointInfo* find_setpoint(const char*, const char*) const;
        const SetpointInfo* find_setpoint_generic(const char*, const char*) const;
        void fixup(long);
        const RoomCameraInfo* get_camera_info() const;
        void init(unsigned int, unsigned int, const char*, const char*);
        void load();
        void unfixup();
        void unload();

    private:
        void add_set_script_Camera(unsigned long, const Csys&, const char*, const struct ThornCameraProperties*);
        void add_set_script_Prop(const char*, const char*, int, const Csys&, bool, bool, bool, bool, unsigned char, signed char, unsigned long, const char*,
                                 unsigned long, bool);
        void add_set_script_Setpoint(unsigned long, const Csys&, const char*, const struct ThornEntity*);
        void add_set_script_light(unsigned long, const Csys&, const struct ThornLightProperties*, unsigned char);
        const SetpointInfo* apply_setpoint(const char*, char**, Csys*, const char*);
        CharPlaceInfo* find_CharacterPlacement(const char*);
        void fixup_FlashLight_list(long, const HardpointSummary*);
        static void make_setpoint_name_generic(const char*, char*);
        void read_Camera_block(INI_Reader*);
        void read_CharacterPlacement_block(INI_Reader*);
        void read_FlashLightLine_block(INI_Reader*);
        void read_FlashLightSet_block(INI_Reader*);
        void read_ForSaleShipPlacement_block(INI_Reader*);
        void read_Hotspot_block(INI_Reader*);
        void read_PlayerShipPlacement_block(INI_Reader*);
        void read_RoomInfo_block(INI_Reader*);
        void read_Sound_block(INI_Reader*);
        void read_ambient_script(INI_Reader*);
        void read_from_ini(const char*);
        void read_set_script(const char*);
        void setup_Camera();
        void unfixup_FlashLight_list();
        void unsetup_Camera();
        void warn(INI_Reader*, bool);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomLightInfo
{
        RoomLightInfo();
        ~RoomLightInfo();
        RoomLightInfo& operator=(const RoomLightInfo&);
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomPropInfo
{
        RoomPropInfo();
        ~RoomPropInfo();
        RoomPropInfo& operator=(const RoomPropInfo&);
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace RtcSlider
{
    IMPORT float get_default_fps_cap();
    IMPORT float get_fps_cap();
    IMPORT float get_slider();
    IMPORT bool is_enabled(unsigned long);
    IMPORT bool is_enabled(const char*);
    IMPORT void load(const char*);
    IMPORT void set_slider(float);
    IMPORT bool validate_setting(const char*, const char*);
}; // namespace RtcSlider

struct IMPORT SMControllerEvent
{
        SMControllerEvent(int, const void*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SMEventData
{
        SMEventData(enum STATE_MACHINE_EVENT_TYPE);
        virtual STATE_MACHINE_EVENT_TYPE get_event_type() const;
        bool is_sm_event() const;
        bool is_user_event() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SMMChangeState
{
        SMMChangeState(int);
        virtual class StateMachineMessage* clone() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SMMessage
{
        SMMessage(StateMachineMessage*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT ScanList
{
    public:
        ScanList(const ScanList&);
        ScanList();
        ~ScanList();
        ScanList& operator=(const ScanList&);
        bool add(IObjRW*);
        int add_in_range(const Vector&, float, struct IObjDB*, unsigned int, struct Filter*);
        void remove(IObjRW*);
        void reset();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT ScriptBehavior
{
    public:
        ScriptBehavior(const ScriptBehavior&);
        ScriptBehavior();
        ~ScriptBehavior();
        ScriptBehavior& operator=(const ScriptBehavior&);
        void clear();
        void destroy();
        unsigned long get_key() const;
        void init(const struct CharacterBehaviorDescription&);
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SetpointInfo
{
        SetpointInfo(const SetpointInfo&);
        SetpointInfo();
        ~SetpointInfo();
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SetpointProperties
{
        SetpointProperties(const SetpointProperties&);
        SetpointProperties();
        ~SetpointProperties();
        SetpointProperties& operator=(const SetpointProperties&);
        void clear();
        const char* combine_to_name() const;
        void destroy();
        void extract_from_name(const char*);
        void set_segment(const char*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace ShieldEquipConsts
{
    IMPORT float HULL_DAMAGE_FACTOR;
};

struct IMPORT ShipGunStats
{
        ShipGunStats();
        ShipGunStats& operator=(const ShipGunStats&);
        void clear();

    public:
        uint activeGunCount;
        float avgGunSpeed;
        float maxGunRange;
        uint dunno1;
        uint dunno2;
};

struct IMPORT ShipPlaceInfo
{
        ShipPlaceInfo();
        ~ShipPlaceInfo();
        void clear();
        void destroy();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace SolarReps
{
    IMPORT int FindSolarRep(const ID_String&);
};

class IMPORT SphereIntruderChecker
{
    public:
        SphereIntruderChecker(const SphereIntruderChecker&);
        SphereIntruderChecker();
        ~SphereIntruderChecker();
        SphereIntruderChecker& operator=(const SphereIntruderChecker&);
        void check_sphere(unsigned int, const Vector&, float, st6::list<CObject*, st6::allocator<CObject*>>&);

    protected:
        virtual void added(CObject*);
        virtual void deleted(CObject*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT StateMachine
{
        StateMachine();
        virtual ~StateMachine();
        int get_state() const;
        virtual void process(const SMEventData*);
        void reset();
        void start();

    protected:
        virtual void handle_state_change();
        void set_state(int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineGroup
{
    public:
        StateMachineGroup(class IMessageRouter*);
        virtual ~StateMachineGroup();
        virtual void add_state_machine(class StateMachineMessageHandler*);
        virtual void remove_state_machine(unsigned int);
        virtual void remove_state_machine(const StateMachineMessageHandler*);

    protected:
        virtual void process(const SMEventData*);
        void remove_dying_machines();

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineMessage
{
    public:
        StateMachineMessage(const StateMachineMessage&);
        StateMachineMessage(unsigned int);
        StateMachineMessage(float, unsigned int, unsigned int, unsigned int, int);
        StateMachineMessage();
        virtual ~StateMachineMessage();
        static unsigned int GenerateUniqueMessageType();
        virtual StateMachineMessage* clone() const;
        int get_delivery_state() const;
        float get_delivery_time() const;
        unsigned int get_message_type() const;
        unsigned int get_receiver() const;
        unsigned int get_sender() const;
        bool is_delivered() const;
        void set_delivered(bool);
        void set_delivery_options(float, unsigned int, unsigned int, int);
        void set_delivery_state(int);
        void set_delivery_time(float);
        void set_message_type(unsigned int);
        void set_receiver(unsigned int);
        void set_sender(unsigned int);

        static void* operator new(unsigned int);
        static void operator delete(void*);

    private:
        static unsigned int s_unique_message_type_generator;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineMessageHandler
{
    public:
        StateMachineMessageHandler(IMessageRouter*);
        virtual void receive_message(StateMachineMessage*);

    protected:
        void send_delayed_message_to_me(StateMachineMessage*, float, enum SM_MESSAGE_SCOPE, int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StyleCollection
{
        class Style
        {
            public:
                unsigned char data[OBJECT_DATA_SIZE];
        };

    public:
        StyleCollection& operator=(const StyleCollection&);
        static RenderDisplayList& get_style(unsigned short);
        static void remove_style(unsigned short);
        static void set_style(unsigned short, const TextRenderAttributes&);
        static void set_style(unsigned short, const RenderDisplayList&);

    protected:
        static st6::map<unsigned short, Style, st6::less<unsigned short>, st6::allocator<Style>> mStyles;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace SubObjectID
{
    class IMPORT CollGroupIdMaker
    {
        public:
            CollGroupIdMaker();
            CollGroupIdMaker& operator=(const CollGroupIdMaker&);
            unsigned short CreateGroupID();
            void Reset();

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT EquipIdMaker
    {
        public:
            EquipIdMaker();
            EquipIdMaker& operator=(const EquipIdMaker&);
            unsigned short CreateEquipID();
            void Reset();

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    class IMPORT ShieldIdMaker
    {
        public:
            ShieldIdMaker();
            ShieldIdMaker& operator=(const ShieldIdMaker&);
            unsigned short CreateShieldID();
            void Reset();

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT bool IsArchGroupID(unsigned short);
    IMPORT bool IsEquipID(unsigned short);
    IMPORT bool IsShieldEquipID(unsigned short);
}; // namespace SubObjectID

class IMPORT TRANode
{
    public:
        TRANode(const TextRenderAttributes&, unsigned int, unsigned int);
        TRANode(const TRANode&);
        TRANode();
        virtual ~TRANode();
        TRANode& operator=(const TRANode&);
        virtual RDLNode* Clone() const;
        virtual void Execute(TextRenderContext&, bool);
        virtual void GetElementPos(int, TextRenderContext&, int&) const;
        virtual void GetElementSize(int&) const;
        virtual void GetVisualSize(const TextRenderContext&, VisualSize&) const;
        virtual bool SplitAtSize(const TextRenderContext&, int, unsigned int, RDLNode*&, RDLNode*&) const;
        virtual void Update(float);
        const TextRenderAttributes& get_attributes();
        unsigned int get_default_mask();
        unsigned int get_mask();
        void set_attributes(const TextRenderAttributes&, unsigned int);
        void set_default_mask(unsigned int);
        void set_mask(unsigned int);

        virtual operator TRANode*();
        virtual operator const TRANode*() const;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT TargetManager
{
        int remove_forced_target(unsigned int);
        void set_player_enemy_clamp(int, int);
        int submit_forced_target(unsigned int);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT TextFile32
{
        TextFile32(const TextFile32&);
        TextFile32();
        ~TextFile32();
        TextFile32& operator=(const TextFile32&);
        unsigned int get_line_num() const;
        bool read_line(LineParser32&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT ThrustManager
{
        void engage_cruise(bool);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace ThrusterEquipConsts
{
    IMPORT ID_String EXTERIOR_SOUND_NAME;
    IMPORT float INSIDE_CONE_ANGLE;
    IMPORT ID_String INTERIOR_SOUND_NAME;
    IMPORT float MAX_VOLUME_FORCE;
    IMPORT float MIN_VOLUME_FORCE;
    IMPORT float OUTSIDE_CONE_ANGLE;
    IMPORT float OUTSIDE_CONE_ATTENUATION;
}; // namespace ThrusterEquipConsts

namespace Timing
{
    struct IMPORT Delta
    {
            Delta();
            Delta& operator=(const Delta&);
            double calc_dt();
            void init();
            double read_dt();
            void start();
            void stop();
            void swap();

        public:
            unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT double GetGlobalTime();
    IMPORT int GetMachineSpeed();
    IMPORT void UpdateGlobalTime(double);
    IMPORT void init();
    IMPORT double read();
    IMPORT int64 read_ticks();
    IMPORT double seconds(const int64&);
}; // namespace Timing

class IMPORT TractorArm
{
    public:
        TractorArm(const TractorArm&);
        TractorArm(CETractor*);
        ~TractorArm();
        TractorArm& operator=(const TractorArm&);
        TractorFailureCode GetErrorCode() const;
        enum Mode GetMode() const;
        CLoot* GetTarget() const;
        Vector GetTipPos() const;
        bool IsOn() const;
        void SetTarget(CLoot*);
        void TurnOff();
        void Update(float);

    protected:
        static const float AcquireDelay;
        static const float GrabToleranceSquared;

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT TradeResponseInfo
{
    public:
        TradeResponseInfo(const TradeResponseInfo&);
        TradeResponseInfo();
        ~TradeResponseInfo();
        TradeResponseInfo& operator=(const TradeResponseInfo&);
        void clear();
        void destroy();
        void marshal(MarshalBuffer*) const;
        void unmarshal(MarshalBuffer*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace TurnHelper
{
    IMPORT Vector get_angular_throttle(const Matrix&, const Matrix&, float*);
};

class IMPORT XMLReader
{
    public:
        XMLReader(const XMLReader&);
        XMLReader();
        XMLReader& operator=(const XMLReader&);
        virtual bool extract_text_from_buffer(unsigned short*, unsigned int, unsigned int&, const char*, unsigned int);
        virtual bool read_buffer(RenderDisplayList&, const char*, unsigned int);
        virtual bool read_file(RenderDisplayList&, const char*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT XMLWriter
{
    public:
        XMLWriter(const XMLWriter&);
        XMLWriter();
        XMLWriter& operator=(const XMLWriter&);
        virtual bool write_buffer(const RenderDisplayList&, char*, unsigned int, unsigned int&);
        virtual bool write_file(const RenderDisplayList&, const char*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT accessory
{
        accessory(const accessory&);
        accessory();
        ~accessory();
        accessory& operator=(const accessory&);
        const char* get_accessory_hardpoint() const;
        const char* get_character_hardpoint() const;
        const st6::list<st6::string>& get_materials() const;
        const char* get_mesh() const;
        const char* get_name() const;
        unsigned long get_name_crc() const;
        void init(const char*, const char*, const char*, const char*, const st6::list<st6::string>&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT bodypart
{
        bodypart(const bodypart&);
        bodypart();
        ~bodypart();
        bodypart& operator=(const bodypart&);
        int get_gender() const;
        const char* get_mesh() const;
        const char* get_name() const;
        unsigned long get_name_crc() const;
        st6::list<st6::string>* get_petal_anims() const;
        DetailSwitchTable* get_switch_table() const;
        void init(const char*, const char*, int, st6::list<st6::string>*, DetailSwitchTable*);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT option_spec
{
        option_spec& operator=(const option_spec&);

    public:
        unsigned char data[OBJECT_DATA_SIZE];
};

namespace Geometry
{
    struct Frustum;
    struct Sphere;
}; // namespace Geometry

IMPORT bool  operator!=(struct CHARACTER_ID const &,struct CHARACTER_ID const &);
IMPORT bool  operator!=(struct Rect const &,struct Rect const &);
IMPORT bool  operator<(struct CHARACTER_ID const &,struct CHARACTER_ID const &);

IMPORT void AppendMissionLogData(const FmtStr*, unsigned char*&, int&, int);
IMPORT unsigned int Arch2Good(unsigned int);
IMPORT void BaseDataList_destroy();
IMPORT BaseDataList* BaseDataList_get();
IMPORT void BaseDataList_load();
IMPORT void BaseDataList_load_market_data(const char*);
IMPORT void BuildDirectory(const char*);
IMPORT float CHATTER_MAX_DIST;
IMPORT float CHATTER_MAX_DIST_ATTEN;
IMPORT float CHATTER_START_ATTEN;
IMPORT float COLLISION_DAMAGE_FACTOR;
IMPORT int COMM_CONFLICT_PRIORITY_CUTOFF;
IMPORT float COMM_PLAYER_FAR_DIST;
IMPORT float COMM_PLAYER_FAR_DIST_ATTEN;
IMPORT class Behavior* CREATE_BEHAVIOR(int);
IMPORT void CleanUpDatabases();
IMPORT void CompoundInstanceAnalyze(long, void (*)(long, void*), void*);
IMPORT int CompoundInstanceCount(long);
IMPORT long CompoundInstanceFindFirstName(long, const char*);
IMPORT void CompoundInstanceList(long, int*, long**);
IMPORT void ComputeExplosiveImpulses(long, Vector&, Vector&, Vector&);
IMPORT bool CostumeGenderAdjust(int*, int);
IMPORT bool Costume_is_equal(const struct Costume&, const struct Costume&);
IMPORT unsigned int CreateID(const char*);

IMPORT float Csys_error(const Csys&, const Csys&);
IMPORT Csys Csys_identity();
IMPORT Csys Csys_init(const Vector&, const Matrix&);
IMPORT Csys Csys_interpolate(Csys, Csys, float);

IMPORT void DAEngine_create_filesystem(const char*, struct IFileSystem**, const char*);
IMPORT void DAEngine_release_filesystem(IFileSystem**);
IMPORT Csys DALib_Engine_get_csys(long);
IMPORT void DALib_Engine_set_csys(long, const Csys&);

IMPORT ID_String DEATH_COMM_FUSE;
IMPORT double DaysPerSecond;
IMPORT void DebugPrint(const char*, ...);
IMPORT unsigned int DecodeType(const char*);
IMPORT Matrix EulerMatrix(const Vector&);
IMPORT void ExtractMissionLogData(FmtStr*, unsigned char*&, int&);
IMPORT float FIRE_FAILED_DELAY;
IMPORT ID_String FIRE_FAILED_SOUND;

struct HardpointInfo;
IMPORT long FindChild(long, const char*);
IMPORT bool FindHardpoint(long, const char*, long&);
IMPORT bool FindHardpoint_OS(long, const char*, long&, HardpointInfo&);
IMPORT bool FindHardpoint_PS(long, const char*, long&, HardpointInfo&);
IMPORT void FreeCostumeDescriptions();
IMPORT void FreeSpatial(ISpatialPartition*);
IMPORT bool FrustumCull(const Geometry::Frustum&, const Universe::IZone*);
IMPORT IBehaviorManager* GetBehaviorManager(IObjRW*);
IMPORT const CostumeDescriptions* GetCostumeDescriptions();
IMPORT Matrix GetDirectionMatrix(const Transform&, const Vector&);
IMPORT void GetFileSysPath(char*, const char*, IFileSystem*);
IMPORT const char* GetFullFilename(const char*);
IMPORT long GetRoot(long);
IMPORT CObject* GetRoot(const CObject*);
IMPORT bool GetScreenShotPath(char* const);
IMPORT float GetSphereIntersectVol(float, float, float);
IMPORT bool GetUserDataPath(char* const);
IMPORT bool GetUserLocalDataPath(char* const);
IMPORT void GiveClientRunPermission();
IMPORT void GiveServerRunPermission();
IMPORT unsigned int Good2Arch(unsigned int);
IMPORT void GoodList_destroy();
IMPORT GoodInfoList* GoodList_get();
IMPORT void GoodList_load(const char*);
IMPORT bool HardpointPosition(long, const char*, Vector*, Matrix*);
IMPORT bool HardpointPositionA(long, const char*, Vector*, Matrix*);
IMPORT void HardpointToObject(long, HardpointInfo&);
IMPORT void HardpointToWorld(long, HardpointInfo&);
IMPORT void HexToWide(const char*, unsigned short*);
IMPORT bool InitializeRichText(int);
IMPORT bool IsDescendant(long, long);
IMPORT bool IsMPServer();
IMPORT float JETTISONED_CARGO_VELOCITY;
IMPORT bool JointEnumCallback(long, long, const struct JointInfo*, void*);
IMPORT float LOOT_OWNER_SAFE_TIME;
IMPORT float LOOT_UNSEEN_LIFE_TIME;
IMPORT float LOOT_UNSEEN_RADIUS;
IMPORT bool LayoutRichText(TextRenderContext&, const RenderDisplayList&, int, RenderDisplayList&, int, int, bool, int*, bool);
IMPORT void LoadBodypartDescriptions(const char*);
IMPORT void LoadCostumeDescriptions(const char*);
IMPORT Matrix LookMatrix(const Vector&);
IMPORT Matrix LookMatrixYup(const Vector&);
IMPORT int MAX_PLAYER_AMMO;
IMPORT float MUSIC_CROSS_FADE_DELAY;
IMPORT float MUZZLE_CONE_ANGLE;
IMPORT unsigned short MakeId(const char*);
IMPORT unsigned int MakeLocationID(unsigned int, const char*);
IMPORT ISpatialPartition* NewSpatial(const char*);
IMPORT int NumHardpoints(long, bool);
IMPORT float PLAYER_ATTACHED_EQUIP_HIT_PTS_SCALE;
IMPORT float PLAYER_COLLISION_GROUP_HIT_PTS_SCALE;
IMPORT int PackMissionLogData(int, const FmtStr*, unsigned char*, int);
IMPORT _GUID* ParseGUID(const char*, _GUID*);
IMPORT double ParseNumber(const char*);
IMPORT void PetalDB_destroy();
IMPORT const PetalInterfaceDatabase* PetalDB_get();
IMPORT void PetalDB_load(const char*);
IMPORT bool PlayerTrailAvailable;
IMPORT Rect RECT_to_Rect(const tagRECT&);
IMPORT Vector RandomVector(float);
IMPORT Vector random_inside_box(float, float, float);
IMPORT Vector random_inside_cylinder(float, float);
IMPORT Vector random_inside_ellipsoid(float, float, float);
IMPORT Vector random_inside_ring(float, float, float);
IMPORT Vector random_inside_sphere(float);
IMPORT Vector random_on_unit_sphere();
IMPORT Vector random_sphere_constrained(const Vector&, float);
IMPORT Vector random_sphere_constrained_2(const Vector&, float, float);
IMPORT bool ReadConstants(const char*);
IMPORT tagRECT Rect_to_RECT(const Rect&);
IMPORT struct ViewRect Rect_to_ViewRect(const Rect&);
IMPORT void RefreshLoadingProgress();
IMPORT void RegisterLoadingScreen(class ILoadingScreen*);
IMPORT void ReinitializeRichTextFonts();
IMPORT Matrix RotateMatrix(const Vector&);
//@@@TODO IMPORT unsigned int const  SMM_CHANGE_STATE;
//@@@TODO IMPORT unsigned int const  SMM_TIMEOUT;
IMPORT ID_String SND_CARGO_JETTISONED;
//@@@TODO IMPORT unsigned short const  SUBOBJ_ID_NONE;
//@@@TODO IMPORT unsigned short const  SUBOBJ_ID_POWER;
//@@@TODO IMPORT unsigned short const  SUBOBJ_ID_ROOT;
IMPORT unsigned long SafeWaitForSingleObject(void*, unsigned long);
IMPORT void SetIsMPServer(bool);
IMPORT void SetMultPlayer(bool);
IMPORT void SetStandardFont(int, const TextRenderContext::FontDesc&);
IMPORT void ShutdownRichText();
IMPORT bool SinglePlayer();
IMPORT ID_String SpaceflightLocationID;
IMPORT bool SphereCull(const Geometry::Sphere&, const Universe::IZone*);
IMPORT char* StringAlloc(const char*, bool);
IMPORT const char* StringIndex(const char*, unsigned int);
IMPORT void StringShutdown();
IMPORT unsigned long ThornGetRenderType(const struct ThornEntity*, const char*);
IMPORT bool ThornGetUserFloat(struct IScriptEngine*, int, const char*, float*);
IMPORT bool ThornGetUserInt(IScriptEngine*, int, const char*, int*);
IMPORT const char* ThornGetUserString(IScriptEngine*, int, const char*);
IMPORT void ThornScriptDestroy(IScriptEngine**);
IMPORT Csys ThornScriptGetCsys(IScriptEngine*, const char*);
IMPORT IScriptEngine* ThornScriptLoad(const char*);
IMPORT void ToggleIceCap(bool);
IMPORT double ValueNum(const char*, unsigned int);
IMPORT Rect ViewRect_to_Rect(const ViewRect&);
IMPORT float WALLA_MAX_DIST;
IMPORT float WALLA_MAX_DIST_ATTEN;
IMPORT int WALLA_PRIORITY_CUTOFF;
IMPORT float WALLA_START_ATTEN;
IMPORT void WaitForClientRunPermission();
IMPORT void WaitForServerRunPermission();
IMPORT void WideToHex(const unsigned short*, char*);

IMPORT int add_good_item(unsigned int, int, float, float, bool, GoodDescList*);
IMPORT bool arch_is_combinable(unsigned int);
IMPORT const unsigned short* filetime_to_wstring(_FILETIME const&);
//@@@ IMPORT struct GoodDesc *  find_good_item(struct GoodDescList *,unsigned int,class MetaNode<struct GoodDesc> * *);
IMPORT long get_projected_bounding_box(struct ICamera*, const Vector&, float, ViewRect*, float&);
IMPORT long get_projected_bounding_sphere(ICamera*, const Vector&, float, float&, float&, float&, float&);
IMPORT int lex_compare(const RenderDisplayList&, const RenderDisplayList&, bool);
IMPORT const char* malloc_strcpy(char**, const char*);
IMPORT void malloc_strfree(char**);
IMPORT const unsigned short* malloc_wstrcpy(unsigned short**, const unsigned short*);
IMPORT void malloc_wstrfree(unsigned short**);
IMPORT Rect rect_intersect(const Rect&, const Rect&);
IMPORT Rect rect_union(const Rect&, const Rect&);
IMPORT int remove_good_item(unsigned int, int, GoodDescList*);
IMPORT char* safe_strcat(char*, int, const char*);
IMPORT char* safe_strcpy(char*, int, const char*);
IMPORT unsigned short* safe_wcscpy(unsigned short*, int, const unsigned short*);
IMPORT unsigned long select_option_from_string(char*, const option_spec* const, int, const char*);
IMPORT bool strequal(const char*, const char*);

#endif //_FLCORECOMMON_H_
