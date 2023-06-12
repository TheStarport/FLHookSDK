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
	char const* get_string() const;

  public:
	uint id;
	unsigned char data[128];
};

struct IMPORT ActionDB
{
	ActionDB();
	~ActionDB();
	ActionDB& operator=(ActionDB const&);
	void add(struct IAction*);
	IAction* find(char const*) const;
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
	AmbientScriptProperties& operator=(AmbientScriptProperties const&);
	void clear();
	void destroy();
	unsigned long get_key() const;
	void init(struct AmbientScriptDescription const&);
	void marshal(class MarshalBuffer*) const;
	void unmarshal(MarshalBuffer*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT INI_Reader
{
  public:
	INI_Reader(INI_Reader const&);
	INI_Reader();
	~INI_Reader();
	INI_Reader& operator=(INI_Reader const&);
	void close();
	bool find_header(char const*);
	bool get_bool(unsigned int);
	char const* get_file_name() const;
	char const* get_header_ptr();
	char const* get_indexed_value(unsigned int);
	int get_line_num() const;
	char const* get_line_ptr();
	char const* get_name() const;
	char const* get_name_ptr();
	unsigned int get_num_parameters() const;
	void get_state(struct State&) const;
	bool get_value_bool(unsigned int);
	float get_value_float(unsigned int);
	int get_value_int(unsigned int);
	char const* get_value_ptr();
	char const* get_value_string(unsigned int);
	char const* get_value_string();
	unsigned short const* get_value_wstring();
	Vector get_vector();
	bool is_end() const;
	bool is_header(char const*);
	bool is_number(char const*) const;
	bool is_value(char const*);
	bool is_value_empty(unsigned int);
	void log_link(char const*) const;
	bool open(char const*, bool);
	bool open_memory(char const*, unsigned int);
	bool read_header();
	bool read_value();
	void reset();
	void seek(unsigned int);
	void set_state(State const&);
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
	IMPORT void Rem(VChannel const*);
	IMPORT void Shutdown();
	IMPORT void Update(float);
}; // namespace AnimDB

namespace PhyArch
{
	struct IMPORT Part
	{
		Part(Part const&);
		Part();
		~Part();
		Part& operator=(Part const&);
		void clear();

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	IMPORT Part const* GetDefaultPart();
	IMPORT bool LoadSurfaces(char const*, st6::map<unsigned int, Part, st6::less<unsigned int>, st6::allocator<Part>>&);
}; // namespace PhyArch

enum HpAttachmentType
{
	WEAPON = 3,
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
	hp_fighter_shield_special_1 = 34,
	hp_thruster = 35,
	hp_torpedo_special_2 = 36,
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

namespace Archetype
{
	class IMPORT FuseIgnitionList
	{
	  public:
		unsigned char data[OBJECT_DATA_SIZE];
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
		Root(Root const&);
		Root(struct IClObj*);
		virtual ~Root();
		Root const& operator=(Root const&);
		void AddRef();
		int GetRef() const;
		int Release();
		long create_instance(IEngineInstance*) const;
		long get_engine_index() const;
		unsigned int get_id() const;
		PhyArch::Part const* get_phy_part(unsigned int) const;
		int get_script_index() const;
		bool is_loaded() const;

		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);
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
		/*  9 */ int explosionArchId;
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
		Equipment(Equipment const&);
		Equipment(IClObj*);
		virtual ~Equipment();
		Equipment& operator=(Equipment const&);

		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);
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
		EqObj(EqObj const&);
		EqObj(IClObj*);
		virtual ~EqObj();
		EqObj const& operator=(EqObj const&);
		bool dock_terminal_valid(int) const;
		virtual ClassType get_class_type() const;
		struct CollisionGroup const* get_group_by_id(unsigned short) const;
		CollisionGroup const* get_group_by_name(CacheString const&) const;
		bool get_undamaged_collision_group_list(st6::list<struct CollisionGroupDesc>&) const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);
		bool traverse_groups(CollisionGroup const*&) const;

	  public:
		/* 23 */ CollisionGroup* collisionGroup;
		/* 24 */ uint dunno1;
		/* 25 */ uint dunno2;
		/* 26 */ uint dunno3;
		/* 27 */ uint dunno4;
		/* 28 */ uint dunno5;
		/* 29 */ uint dunno6;
		/* 30 */ uint dunno7;
		/* 31 */ uint dunno9;
		/* 32 */ bool b128;
		bool dockingCamera;
		/* 33 */ uint dunno10;
		/* 34 */ uint dunno11;
		/* 35 */ uint dunno12;
	};

	struct IMPORT AttachedEquipment : public Equipment
	{
		AttachedEquipment(AttachedEquipment const&);
		AttachedEquipment(IClObj*);
		virtual ~AttachedEquipment();
		AttachedEquipment& operator=(AttachedEquipment const&);
		virtual ClassType get_class_type() const;
		virtual bool is_attached() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

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
		Armor(Armor const&);
		Armor(IClObj*);
		virtual ~Armor();
		Armor& operator=(Armor const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float hitPointsScale;
	};

	struct IMPORT Asteroid : Root
	{
		Asteroid(Asteroid const&);
		Asteroid(IClObj*);
		virtual ~Asteroid();
		Asteroid& operator=(Asteroid const&);
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
		AttachedFXEquip(AttachedFXEquip const&);
		AttachedFXEquip(IClObj*);
		virtual ~AttachedFXEquip();
		AttachedFXEquip& operator=(AttachedFXEquip const&);
		virtual ClassType get_class_type() const;

	  public:
		// no fields here
	};

	struct IMPORT CargoPod : AttachedEquipment
	{
		CargoPod(CargoPod const&);
		CargoPod(IClObj*);
		virtual ~CargoPod();
		CargoPod& operator=(CargoPod const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;

	  public:
		// no fields here
	};

	struct IMPORT CloakingDevice : AttachedEquipment
	{
		CloakingDevice(CloakingDevice const&);
		CloakingDevice(IClObj*);
		virtual ~CloakingDevice();
		CloakingDevice& operator=(CloakingDevice const&);
		virtual ClassType get_class_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 34 */ float powerUsage;
		/* 35 */ float cloakInTime;
		/* 36 */ float cloakOutTime;
		/* 37 */ uint cloakInFxId;
		/* 38 */ uint cloakOutFxId;
	};

	struct IMPORT CollisionGroup
	{
		CollisionGroup(CollisionGroup const&);
		CollisionGroup();
		~CollisionGroup();
		CollisionGroup& operator=(CollisionGroup const&);

	  public:
		CollisionGroup* next;
		ushort id;
		CacheString name;
	};

	struct IMPORT Commodity : Equipment
	{
		Commodity(Commodity const&);
		Commodity(IClObj*);
		virtual ~Commodity();
		Commodity& operator=(Commodity const&);
		virtual ClassType get_class_type() const;
		float get_decay_per_second() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual Equipment* get_loot_appearance();
		virtual CargoPod* get_pod_appearance();
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float decayPerSecond;
		/* 29 */ uint lootAppearanceId;
		/* 30 */ uint podAppearanceId;
	};

	struct IMPORT DamageObjInfo
	{
		DamageObjInfo(DamageObjInfo const&);
		DamageObjInfo();
		DamageObjInfo& operator=(DamageObjInfo const&);
		bool operator==(DamageObjInfo const&) const;
		bool operator!=(DamageObjInfo const&) const;
		bool operator<(DamageObjInfo const&) const;
		bool operator>(DamageObjInfo const&) const;

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	class IMPORT DamageObjInfoList
	{
	  public:
		DamageObjInfoList(DamageObjInfoList const&);
		DamageObjInfoList();
		~DamageObjInfoList();
		DamageObjInfoList& operator=(DamageObjInfoList const&);
		bool IsValid();

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	struct IMPORT DynamicAsteroid : Root
	{
		DynamicAsteroid(DynamicAsteroid const&);
		DynamicAsteroid(IClObj*);
		virtual ~DynamicAsteroid();
		DynamicAsteroid& operator=(DynamicAsteroid const&);
		virtual ClassType get_class_type() const;
		virtual bool read(INI_Reader&);

	  public:
		// no fields
	};

	struct IMPORT Engine : Equipment
	{
		Engine(Engine const&);
		Engine(IClObj*);
		virtual ~Engine();
		Engine& operator=(Engine const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float maxForce;
		/* 29 */ float linearDrag;
		/* 30 */ float powerUsage;
		/* 31 */ float cruisePowerUsage;
		/* 32 */ float cruiseChargeTime;
		/* 33 */ bool indestructible;
		/* 34 */ float reverseFraction;
	};

	struct IMPORT Explosion
	{
		Explosion(Explosion const&);
		Explosion(ID_String const&);
		~Explosion();
		Explosion& operator=(Explosion const&);
		bool read(INI_Reader&);
		void reset();

	  public:
		/*  0 */ uint id;
		/*  1 */ float radius;
		/*  2 */ float impulse;
		/*  3 */ float hullDamage;
		/*  4 */ float energyDamage;
		// and some other stuff
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
		Launcher(Launcher const&);
		Launcher(IClObj*);
		virtual ~Launcher();
		Launcher& operator=(Launcher const&);
		virtual ClassType get_class_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

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
		Gun(Gun const&);
		Gun(IClObj*);
		virtual ~Gun();
		Gun& operator=(Gun const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		HpAttachmentType get_hp_type_by_index(int) const;
		float get_munition_range() const;
		int get_number_of_hp_types() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

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
		InternalFXEquip(InternalFXEquip const&);
		InternalFXEquip(IClObj*);
		virtual ~InternalFXEquip();
		InternalFXEquip& operator=(InternalFXEquip const&);
		virtual ClassType get_class_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ char* useAnimation;
	};

	struct IMPORT Light : Equipment
	{
		Light(Light const&);
		Light(IClObj*);
		virtual ~Light();
		Light& operator=(Light const&);
		virtual ClassType get_class_type() const;
		virtual bool read(INI_Reader&);

	  public:
		/* 28 */ bool alwaysOn;
		bool dockingLight;
	};

	struct IMPORT LootCrate : Equipment
	{
		LootCrate(LootCrate const&);
		LootCrate(IClObj*);
		virtual ~LootCrate();
		LootCrate& operator=(LootCrate const&);
		virtual ClassType get_class_type() const;

	  public:
		// no fields here
	};

	struct IMPORT MineDropper : Launcher
	{
		MineDropper(MineDropper const&);
		MineDropper(IClObj*);
		virtual ~MineDropper();
		MineDropper& operator=(MineDropper const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;

	  public:
		// no fields here
	};

	struct IMPORT Power : Equipment
	{
		Power(Power const&);
		Power(IClObj*);
		virtual ~Power();
		Power& operator=(Power const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float capacity;
		/* 29 */ float chargeRate;
		/* 30 */ float thrustCapacity;
		/* 31 */ float thrustChargeRate;
	};

	struct IMPORT Projectile : Equipment
	{
		Projectile(Projectile const&);
		Projectile(IClObj*);
		virtual ~Projectile();
		Projectile& operator=(Projectile const&);
		virtual ClassType get_class_type() const;
		virtual Equipment* get_loot_appearance();
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float lifeTime;
		/* 29 */ float ownerSafeTime;
		/* 30 */ bool requiresAmmo;
		bool forceGunOri;
		/* 31 */ uint lootAppearanceId;
	};

	struct IMPORT CounterMeasure : Projectile
	{
		CounterMeasure(CounterMeasure const&);
		CounterMeasure(IClObj*);
		virtual ~CounterMeasure();
		CounterMeasure& operator=(CounterMeasure const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 32 */ float linearDrag;
		/* 33 */ float range;
		/* 34 */ int diversionPercentage;
	};

	struct IMPORT CounterMeasureDropper : Launcher
	{
		CounterMeasureDropper(CounterMeasureDropper const&);
		CounterMeasureDropper(IClObj*);
		virtual ~CounterMeasureDropper();
		CounterMeasureDropper& operator=(CounterMeasureDropper const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 40 */ float range;
	};

	struct IMPORT Munition final : Projectile
	{
		Munition(Munition const&);
		Munition(IClObj*);
		virtual ~Munition();
		Munition& operator=(Munition const&);
		static void FreeBeamArchIdx();
		static void LoadBeamArchIdx();
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		bool is_guided() const;
		virtual bool load();
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  protected:
		static long beamArchIndex;
		virtual void free_resources();

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
		Mine(Mine const&);
		Mine(IClObj*);
		virtual ~Mine();
		Mine& operator=(Mine const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 32 */ float linearDrag;
		/* 33 */ float detonationDist;
		/* 34 */ float seekerDist;
		/* 35 */ float acceleration;
		/* 36 */ float topSpeed;
	};

	struct IMPORT RepairDroid : Equipment
	{
		RepairDroid(RepairDroid const&);
		RepairDroid(IClObj*);
		virtual ~RepairDroid();
		RepairDroid& operator=(RepairDroid const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float repairRate;
	};

	struct IMPORT Scanner final : Equipment
	{
		Scanner(Scanner const&);
		Scanner(IClObj*);
		virtual ~Scanner();
		Scanner& operator=(Scanner const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float powerUsage;
		/* 29 */ float range;
		/* 30 */ float cargoScanRange;
	};

	struct IMPORT Shield final : Equipment
	{
		Shield(Shield const&);
		Shield(IClObj*);
		virtual ~Shield();
		Shield& operator=(Shield const&);
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
		ShieldBattery(ShieldBattery const&);
		ShieldBattery(IClObj*);
		virtual ~ShieldBattery();
		ShieldBattery& operator=(ShieldBattery const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual Equipment* get_loot_appearance();
		virtual bool read(INI_Reader&);

	  public:
		/* 28 */ uint lootAppearanceId;
	};

	struct IMPORT RepairKit final : ShieldBattery
	{
		RepairKit(RepairKit const&);
		RepairKit(IClObj*);
		virtual ~RepairKit();
		RepairKit& operator=(RepairKit const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual Equipment* get_loot_appearance();
		virtual bool read(INI_Reader&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	struct IMPORT ShieldGenerator final : public AttachedEquipment
	{
		ShieldGenerator(ShieldGenerator const&);
		ShieldGenerator(IClObj*);
		virtual ~ShieldGenerator();
		ShieldGenerator& operator=(ShieldGenerator const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		HpAttachmentType get_hp_type_by_index(int) const;
		int get_number_of_hp_types() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

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
		ShieldLink(ShieldLink const&);
		ShieldLink();
		~ShieldLink();
		ShieldLink& operator=(ShieldLink const&);

	  public:
		unsigned char data[0x18];
	};

	struct IMPORT Ship : EqObj
	{
		Ship(Ship const&);
		Ship(IClObj*);
		virtual ~Ship();
		Ship& operator=(Ship const&);
		static int const MAX_EXHAUST_NOZZLES;
		virtual ClassType get_class_type() const;
		st6::vector<CacheString> const* get_legal_hps(HpAttachmentType) const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

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
		Solar(Solar const&);
		Solar(IClObj*);
		virtual ~Solar();
		Solar& operator=(Solar const&);
		virtual ClassType get_class_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

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
		Thruster(Thruster const&);
		Thruster(IClObj*);
		virtual ~Thruster();
		Thruster& operator=(Thruster const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 34 */ float powerUsage;
		/* 35 */ float maxForce;
	};

	struct IMPORT Tractor : public Equipment
	{
		Tractor(Tractor const&);
		Tractor(IClObj*);
		virtual ~Tractor();
		Tractor& operator=(Tractor const&);
		virtual ClassType get_class_type() const;
		virtual HpAttachmentType get_hp_type() const;
		virtual bool read(INI_Reader&);
		virtual void redefine(Root const&);

	  public:
		/* 28 */ float maxLength;
		/* 29 */ float reachSpeed;
	};

	struct IMPORT TradeLaneEquip : public Equipment
	{
		TradeLaneEquip(TradeLaneEquip const&);
		TradeLaneEquip(IClObj*);
		virtual ~TradeLaneEquip();
		TradeLaneEquip& operator=(TradeLaneEquip const&);
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
	IMPORT Asteroid* GetAsteroidByName(ID_String const&);
	IMPORT unsigned int GetAsteroidID(ID_String const&);
	IMPORT DynamicAsteroid* GetDynamicAsteroid(unsigned int);
	IMPORT DynamicAsteroid* GetDynamicAsteroidByName(ID_String const&);
	IMPORT unsigned int GetDynamicAsteroidID(ID_String const&);
	IMPORT Equipment* GetEquipment(unsigned int);
	IMPORT Equipment* GetEquipmentByName(ID_String const&);
	IMPORT unsigned int GetEquipmentID(ID_String const&);
	IMPORT Explosion* GetExplosion(ID_String const&);
	IMPORT unsigned int GetId(ClassType, unsigned int);
	IMPORT unsigned int GetIdCount(ClassType);
	IMPORT struct MotorData const* GetMotor(unsigned int);
	IMPORT Ship* GetShip(unsigned int);
	IMPORT Ship* GetShipByName(ID_String const&);
	IMPORT unsigned int GetShipID(ID_String const&);
	IMPORT Root* GetSimple(unsigned int);
	IMPORT Root* GetSimpleByName(ID_String const&);
	IMPORT unsigned int GetSimpleID(ID_String const&);
	IMPORT Solar* GetSolar(unsigned int);
	IMPORT Solar* GetSolarByName(ID_String const&);
	IMPORT unsigned int GetSolarID(ID_String const&);
	IMPORT unsigned short LargeIDToSmallID(unsigned int);
	IMPORT bool Load(struct IFileSystem*, long*, int*);
	IMPORT bool Load(char const*, long*, int*);
	IMPORT int LoadAsteroids(char const*, struct IClObjFactory*);
	IMPORT int LoadEquipment(char const*, bool, IClObjFactory*);
	IMPORT bool LoadExplosion(INI_Reader&, bool);
	IMPORT int LoadShips(char const*, bool, IClObjFactory*);
	IMPORT int LoadSimples(char const*, bool, IClObjFactory*);
	IMPORT int LoadSolar(char const*, bool, IClObjFactory*);
	IMPORT unsigned int SmallIdToLargeID(unsigned short);

}; // namespace Archetype

namespace Async
{
	struct IMPORT Action
	{
		Action(Action const&);
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
	AttribStackNode(AttribStackNode const&);
	AttribStackNode(enum Op);
	AttribStackNode();
	virtual ~AttribStackNode();
	AttribStackNode& operator=(AttribStackNode const&);
	virtual class RDLNode* Clone() const;
	virtual void Execute(class TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, struct VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	Op get_operation();
	void set_operation(Op);

	virtual operator AttribStackNode*();
	virtual operator AttribStackNode const*() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT BaseData
{
  public:
	BaseData(BaseData const&);
	BaseData();
	~BaseData();
	BaseData& operator=(BaseData const&);
	unsigned int get_base_id() const;
	st6::list<class RoomData*> const* get_const_room_data_list() const;
	st6::map<unsigned int, struct MarketGoodInfo, st6::less<unsigned int>, st6::allocator<MarketGoodInfo>> const* get_market() const;
	float get_price_variance() const;
	st6::list<RoomData*>* get_room_data_list();
	float get_ship_repair_cost() const;
	unsigned int get_start_location() const;
	void read_from_ini(char const*, unsigned int);
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
	BaseDataList(BaseDataList const&);
	BaseDataList();
	~BaseDataList();
	BaseDataList& operator=(BaseDataList const&);
	BaseData* get_base_data(unsigned int) const;
	st6::list<BaseData*>* get_base_data_list();
	st6::list<BaseData*> const* get_const_base_data_list() const;
	RoomData* get_room_data(unsigned int) const;
	RoomData* get_unloaded_room_data(unsigned int) const;
	void load();
	void load_market_data(char const*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT BaseHint
{
	BaseHint(BaseHint const&);
	BaseHint();
	virtual ~BaseHint();
	BaseHint& operator=(BaseHint const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT BaseWatcher
{
	BaseWatcher();
	~BaseWatcher();
	BaseWatcher& operator=(BaseWatcher const&);
	void set(struct Watchable const*);

  protected:
	void set_pointer(Watchable const*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace BehaviorTypes
{
	IMPORT int get_behavior_id(char const*);
	IMPORT char const* get_behavior_name(int);
}; // namespace BehaviorTypes

class IMPORT BinaryRDLReader
{
	char Buf[1024];

  public:
	BinaryRDLReader(BinaryRDLReader const&);
	BinaryRDLReader();
	BinaryRDLReader& operator=(BinaryRDLReader const&);
	virtual bool extract_text_from_buffer(unsigned short*, unsigned int, unsigned int&, char const*, unsigned int);
	virtual bool read_buffer(class RenderDisplayList&, char const*, unsigned int);
	virtual bool read_file(RenderDisplayList&, char const*);
};

class IMPORT BinaryRDLWriter
{
	char Buf[1024];

  public:
	BinaryRDLWriter(BinaryRDLWriter const&);
	BinaryRDLWriter();
	BinaryRDLWriter& operator=(BinaryRDLWriter const&);
	virtual bool write_buffer(RenderDisplayList const&, char*, unsigned int, unsigned int&);
	virtual bool write_file(RenderDisplayList const&, char const*);
};

struct IMPORT DamageEntry
{
	enum SubObjFate;

	DamageEntry();
	DamageEntry& operator=(DamageEntry const&);
	bool operator==(DamageEntry const&) const;
	bool operator!=(DamageEntry const&) const;
	bool operator<(DamageEntry const&) const;
	bool operator>(DamageEntry const&) const;
	static char const* FateToString(SubObjFate);

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

struct IMPORT DamageList
{
	DamageList(DamageList const&);
	DamageList();
	~DamageList();
	DamageList& operator=(DamageList const&);
	static char const* DmgCauseToString(DamageCause);
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
	CArchGroup(Archetype::CollisionGroup const&, struct CEqObj* const);
	~CArchGroup();
	ID_String const& DebrisTypeName() const;
	bool DestroysParent() const;
	float ExplosionGroupImpulse() const;
	float ExplosionParentImpulse() const;
	float ExplosionResistance() const;
	ID_String const& ExplosionTypeName() const;
	Archetype::FuseIgnitionList const& FuseIgnitions() const;
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
	Archetype::DamageObjInfoList const& GroupDamageObjs() const;
	int InstDepthInGroup(long) const;
	bool IsDead() const;
	bool IsDestroyed() const;
	bool IsInstInGroup(long) const;
	bool IsRootHealthProxy() const;
	void Kill(DamageEntry::SubObjFate);
	float LinkedEquipmentDamage() const;
	unsigned int LinkedEquipmentType() const;
	CacheString const& Name() const;
	Archetype::DamageObjInfoList const& ParentDamageObjs() const;
	struct CObject* RetreiveDestroyedObj();
	bool Separable() const;
	void SetHitPoints(float);
	void SetRelativeHealth(float);

  protected:
	void AttachDamageObjs(CObject*, Archetype::DamageObjInfoList const&) const;
	void Destroy();
	void FreeDamageObjs();
	void GetBoundingSphere(float&, Vector&) const;
	void LoadDamageObjs();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CArchGroupManager
{
  public:
	CArchGroupManager(CArchGroupManager const&);
	CArchGroupManager();
	~CArchGroupManager();
	CArchGroupManager& operator=(CArchGroupManager const&);
	bool AddNewArchGroup(CArchGroup*);
	int Clear();
	bool DeleteArchGroup(unsigned short);
	bool DestroyDeadGroups();
	bool DestroyGroups(DamageList const&, bool);
	CArchGroup* FindByID(unsigned short);
	CArchGroup const* FindByID(unsigned short) const;
	CArchGroup* FindByName(CacheString const&);
	CArchGroup const* FindByName(CacheString const&) const;
	bool Init(CEqObj*);
	unsigned short InstToSubObjID(long) const;
	bool IsOnMap(unsigned short, bool) const;
	int NumLiving() const;
	int Size() const;
	CArchGroup* Traverse(class CArchGrpTraverser&);
	CArchGroup const* Traverse(CArchGrpTraverser&) const;

  protected:
	void DestroyDeadGroup(CArchGroup&);
	void DestroyLowerGroups(CArchGroup const&);
	static int const MAX_GROUP_DEPTH;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CArchGrpTraverser
{
  public:
	CArchGrpTraverser();
	CArchGrpTraverser& operator=(CArchGrpTraverser const&);
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

		uint dunno1[1];
		uint zoneId;
		uint systemId;
		Matrix rot;
		Vector pos;
		uint shapeType; // 1 = sphere, 5 = ring
		uint propertyFlags;
		Vector size;
		uint dunno4[13];
		CmnAsteroid::LootableZone* lootableZone;
		uint startFaction;    // & 0xFF, always zero
		uint countMaxFaction; // & 0xFF, appears related to the max number of factions in a given encounter line
		st6::list<FactionSpawn> factionSpawns;
		uint dunno5;
		uint idsName;
		uint idsInfo;
		uint iDunno6[2];
	};

	IMPORT ISystem* GetFirstSystem();
	IMPORT IBase* GetNextBase();
	IMPORT ISystem* GetNextSystem();
	IMPORT void Shutdown();
	IMPORT bool Startup(char const*);
	IMPORT IZone const* first_zone(unsigned int);
	IMPORT IBase* __cdecl GetFirstBase();
	IMPORT IBase* __cdecl GetNextBase();
	IMPORT unsigned int __cdecl get_base_id(char const*);
	IMPORT IBase* get_base(unsigned int);
	IMPORT unsigned int get_base_id(char const*);
	IMPORT void get_filename(char*, char const*);
	IMPORT unsigned int get_gate_system(unsigned int);
	IMPORT IZone* get_non_const_zone(unsigned int, unsigned int);
	IMPORT IZone* get_non_const_zone(unsigned int, char const*);
	IMPORT ISystem const* get_system(unsigned int);
	IMPORT unsigned int get_system_id(char const*);
	IMPORT IZone const* get_zone(unsigned int);
	IMPORT IZone const* get_zone(unsigned int, char const*);
	IMPORT IZone const* next_zone(IZone const*);
	IMPORT unsigned int num_bases();
	IMPORT unsigned int num_systems();

}; // namespace Universe

namespace Exclusion
{
	struct IMPORT AsteroidExclusionZone
	{
		AsteroidExclusionZone();
		~AsteroidExclusionZone();
		AsteroidExclusionZone& operator=(AsteroidExclusionZone const&);
		Universe::IZone const* get_zone();
		bool set_zone(Universe::IZone const*, Universe::IZone const*);
		void update_dist(Vector const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	class IMPORT AsteroidExclusionZoneMgr
	{
	  public:
		AsteroidExclusionZoneMgr(AsteroidExclusionZoneMgr const&);
		AsteroidExclusionZoneMgr();
		~AsteroidExclusionZoneMgr();
		AsteroidExclusionZoneMgr& operator=(AsteroidExclusionZoneMgr const&);
		AsteroidExclusionZone* back();
		int get_max_billboard_count();
		virtual bool is_excluded(Vector const&, enum ExcludeObjectType, void*);
		void normalize_billboard_density(int);
		virtual void push_back(Universe::IZone const*, Universe::IZone const*);
		void set_max_cliasteroid_exclusion_distance(float);
		void set_max_dynamicasteroid_exclusion_distance(float);
		virtual void sort(void*);

	  private:
		bool is_billboard_excluded(Vector const&, float*);
		bool is_cliasteroid_excluded(Vector const&, float*);
		bool is_cmnasteroid_excluded(Vector const&, float*);
		bool is_dynamic_asteroid_excluded(Vector const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	struct IMPORT NebulaExclusionZone
	{
		NebulaExclusionZone();
		~NebulaExclusionZone();
		NebulaExclusionZone& operator=(NebulaExclusionZone const&);
		float get_fog_far();
		Universe::IZone const* get_zone();
		ID_String get_zone_shell_name();
		void set_fog_far(float);
		bool set_zone(Universe::IZone const*, Universe::IZone const*);
		void set_zone_shell_name(char const*);
		void update_dist(Vector const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	class IMPORT NebulaExclusionZoneMgr
	{
	  public:
		NebulaExclusionZoneMgr(NebulaExclusionZoneMgr const&);
		NebulaExclusionZoneMgr();
		~NebulaExclusionZoneMgr();
		NebulaExclusionZoneMgr& operator=(NebulaExclusionZoneMgr const&);
		NebulaExclusionZone* back();
		virtual bool is_excluded(Vector const&, ExcludeObjectType, void*);
		bool is_in_exclusion_zone(Vector const&, NebulaExclusionZone**, float*, bool);
		virtual void push_back(Universe::IZone const*, Universe::IZone const*);
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
		CAsteroidCube(CAsteroidCube const&);
		CAsteroidCube(class CAsteroidField*);
		~CAsteroidCube();
		CAsteroidCube& operator=(CAsteroidCube const&);
		struct asteroid_marker* get_changes();
		unsigned long get_id();
		Matrix get_orient();
		Vector get_pos();
		enum CubeState get_state();
		void init(Vector const&, unsigned long, struct AsteroidCubeArch*, struct AxisRotations const&, float);
		void set_size(int);
		void set_state(CubeState);
		void set_system(unsigned int);

	  private:
		bool compute_asteroid_id(Vector const&, unsigned long&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	class IMPORT CAsteroidField
	{
	  public:
		CAsteroidField(CAsteroidField const&);
		CAsteroidField();
		~CAsteroidField();
		CAsteroidField& operator=(CAsteroidField const&);
		int AddRef();
		int Release();
		Vector closest_cube_pos(Vector const&);
		unsigned long create_cube_id(Vector const&);
		CAsteroidCube* find_cube(unsigned long);
		void flush_changes();
		AxisRotations& get_axis_rotations();
		asteroid_marker* get_changes();
		int get_cube_size();
		Exclusion::AsteroidExclusionZoneMgr* get_exclusion_mgr();
		float get_immersion(Vector const&);
		Universe::IZone const* get_lootable_zone(Vector const&) const;
		void load(INI_Reader&, int);
		bool near_field(Vector const&);
		float near_field_fraction(Vector const&, float);
		void populate_asteroids(Vector const&, Vector const&);
		void set_cube_size(int);
		void set_empty_freq(float);
		void set_fill_dist(int);
		void set_system(unsigned int);
		void set_zone(Universe::IZone const*);

	  private:
		void populate_asteroids_internal(Vector const&, Vector const&, float);
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
		CAsteroidSystem(CAsteroidSystem const&);
		CAsteroidSystem();
		~CAsteroidSystem();
		CAsteroidSystem& operator=(CAsteroidSystem const&);
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
	IMPORT unsigned long compute_cube_id(Vector const&);
	IMPORT bool compute_cube_orientation(unsigned long, Matrix*, struct AxisRotations const&, float);
}; // namespace CmnAsteroid

struct INotify
{
	enum Event;
};

class IMPORT IVP_Core;

class IMPORT IVP_Event_Sim;

template<class T>
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

		Controller(Controller const&);
		Controller();
		Controller& operator=(Controller const&);
		void push(Vector const&, float);
		void rotate(Vector const&, float);
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
		PhyCollisionStateManager(PhyCollisionStateManager const&);
		PhyCollisionStateManager(CObject*);
		~PhyCollisionStateManager();
		PhyCollisionStateManager& operator=(PhyCollisionStateManager const&);
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
	IMPORT void AddImpulseAtPoint(CObject*, Vector const&, Vector const&);
	IMPORT void AddToAngularVelocityOS(CObject*, Vector const&);
	IMPORT void AddToVelocity(CObject*, Vector const&);
	IMPORT void AngularImpulse(CObject*, Vector const&, float);
	IMPORT void AngularImpulseOS(CObject*, Vector const&, float);
	IMPORT bool AnyActive();
	IMPORT void Attach(CObject*, CObject*);
	IMPORT int AttachPhantom(CObject*, void*);
	IMPORT float BULLET_LENGTH_FUDGE;
	IMPORT void BeamR(CObject*, Vector const&, Matrix const&, bool);
	IMPORT void BuildIVP_Real(CObject*, CreateParms const&);
	IMPORT void BuildIVP_Sphere(CObject*, float, CreateParms const&);
	IMPORT int CreatePhantom(struct PhantomParms const&, PhyArch::Part const&, void*&);
	IMPORT int CreatePhantom(PhantomParms const&, Vector const&, void*&);
	IMPORT int CreatePhantom(PhantomParms const&, float, void*&);
	IMPORT Vector DEFAULT_ANGULAR_DAMPING;
	IMPORT float DEFAULT_LINEAR_DAMPING;
	IMPORT void DeactivatePhysics(CObject*);
	IMPORT void DeactivatePhysicsR(CObject*);
	IMPORT void DestroyPhantom(void*);
	IMPORT void Detach(CObject*, struct DetachParms const&);
	IMPORT int DetachPhantom(void*);
	IMPORT int FindRayCollisions(unsigned int system, Vector const& origin, Vector const& end, RayHit* rh, int rh_count);
	IMPORT int FindRayIntersect(CObject*, Vector const&, Vector const&, RayHit*, int);
	IMPORT int FindSphereCollisions(unsigned int, Vector const&, float, CObject**, int);
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
	IMPORT Vector GetAngularVelocityOS(CObject const*);
	IMPORT Vector GetCenterOMass(CObject const*);
	IMPORT bool GetClosestPhantomIntruderPos(void*, unsigned int, unsigned int, struct CSimple*&, Vector&);
	IMPORT char const* GetCollisionGroup(CObject const*);
	IMPORT bool GetCollisionState(CObject const*);
	IMPORT bool GetCollisionStatePhantom(void* const);
	IMPORT void GetCollisions(unsigned int, CollisionEvent const*&, CollisionEvent const*&);
	IMPORT class IVP_Time GetCurrentTime(unsigned int);
	IMPORT void GetDamping(CObject const*, float&, Vector&);
	IMPORT float GetMass(CObject const*);
	IMPORT Vector GetMomentOInertia(CObject const*);
	IMPORT float GetRadiusR(CObject const*, bool, Vector&);
	IMPORT Vector GetVelocity(CObject const*);
	IMPORT void LinearImpulse(CObject*, Vector const&, float);
	IMPORT double MATERIAL_ELASTICITY;
	IMPORT double MATERIAL_FRICTION;
	IMPORT int MAX_SPAWNED_MINDIST_COUNT;
	IMPORT double MIN_TIME_BETWEEN_COLLISIONS;
	IMPORT unsigned int MovingObjectCount(unsigned int);
	IMPORT float PHYSICAL_SIM_RATE;
	IMPORT void RCBegin(CSimple*, Vector const&, Vector const&, Quaternion const&, Vector const&);
	IMPORT void RCEnd(CSimple*);
	IMPORT void RCSet(CSimple*, Vector const&, Quaternion const&, double);
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
	IMPORT void ReMakePhysicalR(CObject*, CreateParms const&, float);
	IMPORT void SetCollisionGroup(CObject*, char const* const);
	IMPORT void SetCollisionState(CObject*, bool);
	IMPORT void SetCollisionStatePhantom(void*, bool);
	IMPORT void SetDamping(CObject*, float, Vector const&);
	IMPORT void SetMass(CObject*, float);
	IMPORT void SetMomentOInertia(CObject*, Vector const&);
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
	virtual void __stdcall initialize_instance(long);
	virtual void __stdcall create_instance(long);
	virtual void __stdcall destroy_instance(long);
	virtual void __stdcall set_position(long, Vector const&);
	virtual Vector const& __stdcall get_position(long) const;
	virtual void __stdcall set_orientation(long, Matrix const&);
	virtual Matrix const& __stdcall get_orientation(long) const;
	virtual void __stdcall set_transform(long, class Transform const&);
	virtual Transform const& __stdcall get_transform(long) const;
	virtual void __stdcall get_centered_radius(long, float*, Vector*) const;
	virtual void __stdcall set_centered_radius(long, float, Vector const&);
	virtual void __stdcall set_instance_flags(long, unsigned long);
	virtual unsigned long __stdcall get_instance_flags(long) const;
	virtual bool __stdcall joint_changed(long);
	virtual ~EngineObject();
	virtual Vector const& __stdcall get_velocity(long) const;
	virtual void __stdcall set_velocity(long, Vector const&);
	virtual Vector const& __stdcall get_angular_velocity(long) const;
	virtual void __stdcall set_angular_velocity(long, Vector const&);

	EngineObject(EngineObject const&);
	EngineObject();
	EngineObject& operator=(EngineObject const&);
	Matrix const& get_orientation() const;
	Vector const& get_position() const;
	float const get_radius() const;
	Transform const& get_transform() const;
	void set_centered_radius(float, Vector const&);
	void set_orientation(Matrix const&);
	void set_position(Vector const&);
	void set_transform(Transform const&);
	void update_tree() const;

	uint dunnoEngineObject1;
	Matrix orientation;  // 0x8
	Vector position;     // 0x2C
	float radius;        // 0x38
	Vector centerOfMass; // 0x3C
	uint instanceFlags;  // 0x48
};

class IMPORT CSteering : public PhySys::Controller
{
  public:
	CSteering(CSteering const&);
	CSteering();
	virtual ~CSteering();
	CSteering& operator=(CSteering const&);
	bool Activate(bool);
	virtual bool EnableController();
	float GetAxisSteeringTorque(unsigned int, float) const;
	Vector const& GetAxisThrottle() const;
	bool IsActive() const;
	void SetAxisThrottle(Vector const&);
	void SetOwner(struct CShip*);

  protected:
	static float const AXIS_CHANGE_THRESHOLD;
	virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CStrafeEngine : public PhySys::Controller
{
  public:
	CStrafeEngine(CStrafeEngine const&);
	CStrafeEngine();
	virtual ~CStrafeEngine();
	CStrafeEngine& operator=(CStrafeEngine const&);
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

	CPhysControllerEquip(CPhysControllerEquip const&);
	CPhysControllerEquip();
	CPhysControllerEquip& operator=(CPhysControllerEquip const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CAttachmentObj
{
  public:
	virtual ~CAttachmentObj();

	CAttachmentObj(CAttachmentObj const&);
	CAttachmentObj();
	CAttachmentObj& operator=(CAttachmentObj const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CBase
{
	virtual ~CBase();

	CBase(CBase const&);
	CBase();
	CBase& operator=(CBase const&);
	void advise(bool);
	void cobject(CObject*);
	CObject* cobject() const;
	long get_index() const;
	void notify_of_destruction(void*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CObject : public EngineObject
{
  public:
	virtual void __stdcall destroy_instance(long);
	virtual ~CObject();
	virtual void open(Archetype::Root*);
	virtual int update(float, unsigned int);
	virtual Vector get_velocity() const;
	virtual Vector get_angular_velocity() const;
	virtual void disable_controllers();
	virtual void enable_controllers();
	virtual float get_physical_radius_r(Vector&) const;
	virtual Vector get_center_of_mass() const;
	virtual float get_mass() const;
	virtual bool get_surface_extents(Vector&, Vector&) const;
	virtual void unmake_physical();
	virtual void remake_physical(PhySys::CreateParms const&, float);
	virtual void beam_object(Vector const&, Matrix const&, bool);

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
	static CObject* Find(unsigned int const&, Class);
	static CObject* Find(long, Class);
	static CObject* FindFirst(Class);
	static CObject* FindNext();
	static int Count(Class);
	static void ReleaseAll();
	static unsigned int const NoActions;
	static unsigned int const NoBehavior;
	static unsigned int const NoCountermeasureAi;
	static unsigned int const NoDynamics;
	static unsigned int const NoScanner;
	static unsigned int const UpdateDefault;
	static unsigned int const UpdateDumb;

	static void* operator new(unsigned int);
	static void operator delete(void*);

	CObject(CObject const&);
	CObject(Class);
	unsigned int AddRef();
	unsigned int Release();
	void add_impulse(Vector const&, Vector const&);
	void add_impulse(Vector const&);
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

	Class objectClass; // 0x4C
	uint system;       // 0x50
	uint dunnoCObject; // 0x54, relates to all PhySys calls
	struct SurfaceExtents
	{
		uint dunno[2];
		Vector min, max;
	};
	SurfaceExtents* surf; // 0x58
};

inline CObject::Class get_class(const CObject* c)
{
	return *(CObject::Class*)(((char*)c) + 0x4C);
}

struct IMPORT CSimple : public CObject
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	virtual ~CSimple();
	virtual void open(Archetype::Root*);
	virtual float get_physical_radius_r(Vector&) const;
	virtual void unmake_physical();
	virtual void beam_object(Vector const&, Matrix const&, bool);
	virtual void init(CreateParms const&);
	virtual void cache_physical_props();
	virtual unsigned int get_name() const;
	virtual bool is_targetable() const;
	virtual void connect(struct IObjDB*);
	virtual void disconnect(struct IObjDB*);
	virtual void set_hit_pts(float);
	virtual void init_physics(Vector const&, Vector const&);

	CSimple(CSimple const&);
	CSimple(Class);
	unsigned int GetOwnerPlayer() const;
	void SetOwnerPlayer(unsigned int);
	float get_hit_pts() const;
	unsigned int const& get_id() const;
	float get_max_hit_pts() const;
	struct IObjDB* get_object_database() const;
	float get_relative_health() const;
	float get_scanner_interference() const;
	unsigned int get_type() const;
	void update_zones(float, unsigned int);

	uint dunnoCSimple1[0xB];
	Archetype::Root* archetype; // 0x88
	uint dunnoCSimple2[0x5];
	uint dunnoTargetable; // 0xA0
	uint dunnoScanner;    // 0xA4
	uint dunnoCSimple3;   // 0xA8
	struct IObjDB* objDB;        // 0xAC
	uint id;              // 0xB0
	uint ownerPlayer;     // 0xB4
	float hitPoints;      // 0xB8
	uint dunnoCSimple4[0x5];
	Vector radiusCenter;  // 0xD0
	float radiusCentered; // 0xDC
	uint type;            // 0xE0
};

struct IMPORT CAsteroid : public CSimple
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	CAsteroid(CAsteroid const&);
	CAsteroid();
	virtual ~CAsteroid();
	Archetype::Asteroid const* asteroidarch() const;
	unsigned long get_asteroid_id();
	CmnAsteroid::CAsteroidField const* get_owner_field();
	virtual Vector get_velocity() const;
	void init(CreateParms const&);
	bool is_instant_kill();
	bool is_mine();
	void set_system(unsigned int);
	virtual int update(float, unsigned int);

  protected:
	virtual void init_physics(Vector const&, Vector const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CProjectile : public CSimple
{
  public:
	struct IMPORT CreateParms
	{
		// CreateParms();
		CreateParms& operator=(CreateParms const&);

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

	virtual ~CProjectile();
	virtual int update(float, unsigned int);
	virtual void init(CreateParms const&);
	virtual void set_dead();
	virtual void expire_safe_time();

	CProjectile(CProjectile const&);
	CProjectile(Class);
	unsigned int const& get_owner() const;
	bool is_alive() const;
	bool is_owner_safe() const;
	Archetype::Projectile const* projarch() const;

#ifdef _USE_DEPRECATED_COBJECT_VARIABLES_
	Archetype::Projectile* archetype;
#endif // _USE_DEPRECATED_COBJECT_VARIABLES_
};

class IMPORT CEquip
{
  public:
	virtual ~CEquip();
	virtual bool IsActive() const;
	virtual bool IsDestroyed() const;
	virtual bool IsFunctioning() const;
	virtual bool IsDisabled() const;
	virtual bool IsTemporary() const;
	virtual bool CanDelete() const;
	virtual void NotifyArchGroupDestroyed(unsigned short);
	virtual bool IsLootable() const;
	virtual bool Update(float, unsigned int);
	virtual bool GetEquipDesc(struct EquipDesc&) const;
	virtual void GetStatus(struct EquipStatus&) const;
	virtual bool Activate(bool);
	virtual void Destroy();
	virtual float GetMaxHitPoints() const;
	virtual float GetHitPoints() const;
	virtual void SetHitPoints(float);
	virtual float GetRelativeHealth() const;
	virtual bool GetConnectionPosition(Vector*, Matrix*) const;
	virtual bool IsControllerEnabled();
	virtual bool EnableController();
	virtual bool DisableController();

	static void* operator new(unsigned int);
	static void operator delete(void*);

	CEquip();
	CEquip(CEquip const&);
	CEquip(unsigned int, CEqObj*, unsigned short, Archetype::Equipment const*, bool);

	void ConnectClientEquip(INotify*);
	void ConnectServerEquip(INotify*);
	Archetype::Equipment const* EquipArch() const;
	unsigned short GetID() const;
	CEqObj* GetOwner() const;
	unsigned int GetType() const;
	char const* IdentifyEquipment() const;
	void Notify(INotify::Event, void*);
	void NotifyDisconnecting(INotify*);

	CEqObj* owner;
	unsigned int SubObjId;
	Archetype::Equipment* archetype;
	void* data2[2]; // 0x10 - 0x14
	void* customWrapperClass;
	void* customWrapperClass2;
	char* mountedHardpoint;
};

class IMPORT CInternalEquip : public CEquip
{
  public:
	virtual ~CInternalEquip();
	virtual bool GetEquipDesc(EquipDesc&) const;

	static CInternalEquip* cast(CEquip*);
	static CInternalEquip const* cast(CEquip const*);

	CInternalEquip(CInternalEquip const&);
	CInternalEquip(unsigned int, CEqObj*, unsigned short, Archetype::Equipment const*, bool);
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
	virtual bool IsConnected() const;
	virtual bool Connect(char const*);
	virtual CacheString GetParentHPName() const;
	virtual long GetParentConnector(bool) const;
	virtual bool GetHardPointInfo(struct HardpointInfo&) const;
	virtual bool GetVelocity(Vector&) const;
	virtual bool GetCenterOMass(Vector&) const;
	virtual void Disconnect();

	static CExternalEquip* cast(CEquip*);
	static CExternalEquip const* cast(CEquip const*);

	CExternalEquip(CExternalEquip const&);
	CExternalEquip(unsigned int, CEqObj*, unsigned short, Archetype::Equipment const*, bool);
};

class IMPORT CAttachedEquip : public CExternalEquip
{
  public:
	virtual ~CAttachedEquip();
	virtual bool Update(float, unsigned int);
	virtual float GetHitPoints() const;
	virtual void SetHitPoints(float);
	virtual bool IsConnected() const;
	virtual bool Connect(char const*);
	virtual bool GetVelocity(Vector&) const;
	virtual bool GetCenterOMass(Vector&) const;
	virtual void Disconnect();
	virtual int GetToughness() const;
	virtual bool GetRadius(float&) const;
	virtual bool IsInstOnEquip(long) const;
	virtual long GetRootIndex() const;
	virtual void SetFate(DamageEntry::SubObjFate);
	virtual void ComputeBoundingSphere(float&, Vector&) const;

	static CAttachedEquip* cast(CEquip*);
	static CAttachedEquip const* cast(CEquip const*);

	CAttachedEquip(CAttachedEquip const&);
	CAttachedEquip(unsigned int, CEqObj*, unsigned short, Archetype::Equipment const*, bool);
	Archetype::AttachedEquipment const* AttachedEquipArch() const;
	CObject* GetPhysicsOwner() const;
	CObject* RetrieveDebrisObject();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
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
	virtual bool Connect(char const*);
	virtual void Disconnect();
	virtual FireResult Fire(Vector const&);
	virtual void ConsumeFireResources();
	virtual void ComputeLaunchInfo(st6::vector<struct ProjLaunchInfo>&, Vector const&) const;
	virtual float GetPowerDrawPerFire() const;
	virtual int GetAmmoCount() const;
	virtual bool AmmoNeedsMet() const;
	virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, Vector const&) const;
	virtual FireResult CanFire(Vector const&) const;
	virtual bool PowerNeedsMet() const;
	virtual void DrawPower(int);
	virtual void DrawAmmoFromCargo(int);
	virtual bool RefireDelayElapsed() const;

	CELauncher(CELauncher const&);
	CELauncher(unsigned int, CEqObj*, unsigned short, Archetype::Launcher const*, bool);
	void ComputeProjectilePosAndVelocity_OneBarrel(Vector&, Vector&, int, Vector const&) const;
	Vector GetAvgBarrelDirWS() const;
	Vector GetAvgBarrelPosWS() const;
	Vector GetBarrelDirWS(unsigned int) const;
	struct Barrel const* GetBarrelInfo(unsigned int) const;
	Vector GetBarrelPosWS(unsigned int) const;
	unsigned int GetProjectilesPerFire() const;
	Archetype::Launcher const* LauncherArch() const;
	Archetype::Projectile const* ProjectileArch() const;
	static CELauncher* cast(CEquip*);
	static CELauncher const* cast(CEquip const*);
};

struct IMPORT CBeam : public CProjectile
{
  public:
	virtual ~CBeam();
	virtual Vector get_velocity() const;
	virtual float get_mass() const;
	virtual void init_physics(Vector const&, Vector const&);
	virtual void expire_safe_time();

	CBeam(CBeam const&);
	CBeam(Class);
	char const* get_collision_group() const;
	Vector const& get_last_pos() const;
	void move(float);
	Archetype::Munition const* munitionarch() const;
	void set_velocity(Vector const&);
};

struct IMPORT CCounterMeasure : public CProjectile
{
  public:
	virtual ~CCounterMeasure();
	virtual int update(float, unsigned int);
	virtual void init_physics(Vector const&, Vector const&);
	virtual void expire_safe_time();

	CCounterMeasure(CCounterMeasure const&);
	CCounterMeasure(Class);
	Archetype::CounterMeasure const* countermeasure_arch();
};

class IMPORT CDeadReckonedVector
{
  public:
	CDeadReckonedVector(CDeadReckonedVector const&);
	CDeadReckonedVector();
	virtual ~CDeadReckonedVector();
	CDeadReckonedVector& operator=(CDeadReckonedVector const&);
	void AddSample(Vector const&, double);
	double CalcError(Vector const&);
	double ConvergeTime();
	void Doit(double);
	Vector const& GetProjectedPosition();
	Vector const& GetSample(int);
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
	virtual void init_physics(Vector const&, Vector const&, unsigned int);

	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	CDynamicAsteroid(CDynamicAsteroid const&);
	CDynamicAsteroid();
	Archetype::DynamicAsteroid const* dynamicAsteroidArch() const;
	void init(CreateParms const&);
};

class IMPORT CEArmor : public CInternalEquip
{
  public:
	virtual ~CEArmor();

	static CEArmor* cast(CEquip*);
	static CEArmor const* cast(CEquip const*);

	CEArmor(CEArmor const&);
	CEArmor(CEqObj*, unsigned short, Archetype::Armor const*, bool);
	Archetype::Armor const* ArmorArch() const;
};

class IMPORT CEAttachedFX : public CExternalEquip
{
  public:
	virtual ~CEAttachedFX();
	virtual void NotifyArchGroupDestroyed(unsigned short);

	static CEAttachedFX* cast(CEquip*);
	static CEAttachedFX const* cast(CEquip const*);

	CEAttachedFX(CEAttachedFX const&);
	CEAttachedFX(CEqObj*, unsigned short, Archetype::AttachedFXEquip const*, bool);
	Archetype::AttachedFXEquip const* FXArch() const;
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
	virtual unsigned int GetType() const;
	virtual void Init(float, unsigned int, CacheString const&);

	static CECargo* cast(CEquip*);
	static CECargo const* cast(CEquip const*);

	CECargo(CECargo const&);
	CECargo(CEqObj*, unsigned short, Archetype::Equipment const*, bool);
	void AddToStack(unsigned int, float);
	class CECargoPod const* GetContainer() const;
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
	static CECargoPod const* cast(CEquip const*);

	CECargoPod(CECargoPod const&);
	CECargoPod(CEqObj*, unsigned short, Archetype::CargoPod const*, bool);
	void EmptyPod();
	void FillPod(CECargo*);
	CECargo const* GetContents() const;
};

class IMPORT CECloakingDevice : public CExternalEquip
{
  public:
	virtual ~CECloakingDevice();
	virtual bool Update(float, unsigned int);
	virtual bool Activate(bool);

	static CECloakingDevice* cast(CEquip*);
	static CECloakingDevice const* cast(CEquip const*);

	CECloakingDevice(CECloakingDevice const&);
	CECloakingDevice(CEqObj*, unsigned short, Archetype::CloakingDevice const*, bool);
	Archetype::CloakingDevice const* CloakArch() const;
	float cloak_percent() const;
};

class IMPORT CECounterMeasureDropper : public CELauncher
{
  public:
	virtual ~CECounterMeasureDropper();
	virtual bool Update(float, unsigned int);

	static CECounterMeasureDropper* cast(CEquip*);
	static CECounterMeasureDropper const* cast(CEquip const*);

	CECounterMeasureDropper(CECounterMeasureDropper const&);
	CECounterMeasureDropper(CEqObj*, unsigned short, Archetype::CounterMeasureDropper const*, bool);
	Archetype::CounterMeasure const* CounterMeasureArch();
	Archetype::CounterMeasureDropper const* CounterMeasureDropperArch();
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
	static CEEngine const* cast(CEquip const*);

	CEEngine(CEEngine const&);
	CEEngine(CShip*, unsigned short, Archetype::Engine const*, bool);
	bool EngageCruise(bool, bool);
	Archetype::Engine const* EngineArch() const;
	st6::vector<struct ExhaustNozzleInfo> const& NozzleInfos() const;
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
	virtual bool Connect(char const*);
	virtual void Disconnect();
	virtual FireResult Fire(Vector const&);
	virtual void ConsumeFireResources();
	virtual void ComputeLaunchInfo_OneBarrel(ProjLaunchInfo&, int, Vector const&) const;
	virtual FireResult CanFire(Vector const&) const;

	static float const TARGET_POINT_VALID_TIME;
	static CEGun* cast(CEquip*);
	static CEGun const* cast(CEquip const*);
	static bool ComputeTimeToTgt(Vector const&, Vector const&, float, float&);

	CEGun(CEGun const&);
	CEGun(CEqObj*, unsigned short, Archetype::Gun const*, bool);
	Archetype::Gun const* GunArch() const;
	Archetype::Munition const* MunitionArch() const;
	bool CanPointAt(Vector const&, float) const;
	bool CanSeeTargetObject(float) const;
	bool CanSeeTargetPoint(Vector const&, float) const;
	bool ComputeTgtLeadPosition(Vector&) const;
	float GetMunitionRange() const;
	float GetSecondsTillLock() const;
	void GetTarget(CSimple*&, unsigned short&) const;
	Vector GetTurretOrigin() const;
	bool IsJointInMotion() const;
	bool SetTarget(CSimple*, unsigned short);
	void SetTargetPoint(Vector const&);
	bool is_guided() const;
	void ComputeTurretFrame();
	void DecomposeJointMotion(Vector const&, float&, float&) const;
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
	static CEInternalFX const* cast(CEquip const*);

	CEInternalFX(CEInternalFX const&);
	CEInternalFX(CEqObj*, unsigned short, Archetype::InternalFXEquip const*, bool);
	Archetype::InternalFXEquip const* InternalFXArch() const;
};

class IMPORT CELightEquip : CEquip
{
  public:
	virtual ~CELightEquip();
	virtual void NotifyArchGroupDestroyed(unsigned short);

	static CELightEquip* cast(CEquip*);
	static CELightEquip const* cast(CEquip const*);

	CELightEquip(CELightEquip const&);
	CELightEquip(CEqObj*, unsigned short, Archetype::Light const*, bool);
	Archetype::Light const* LightArch() const;
};

class IMPORT CEMineDropper : public CELauncher
{
  public:
	virtual ~CEMineDropper();
	virtual FireResult CanFire(Vector const&) const;

	static CEMineDropper* cast(CEquip*);
	static CEMineDropper const* cast(CEquip const*);

	CEMineDropper(CEMineDropper const&);
	CEMineDropper(CEqObj*, unsigned short, Archetype::MineDropper const*, bool);
	Archetype::Mine const* MineArch();
	Archetype::MineDropper const* MineDropperArch();
};

class IMPORT CEPower : public CEquip
{
  public:
	virtual ~CEPower();
	virtual bool Update(float, unsigned int);

	static CEPower* cast(CEquip*);
	static CEPower const* cast(CEquip const*);

	CEPower(CEPower const&);
	CEPower(CEqObj*, unsigned short, Archetype::Power const*, bool);

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
	static CERepairDroid const* cast(CEquip const*);

	CERepairDroid(CERepairDroid const&);
	CERepairDroid(CEqObj*, unsigned short, Archetype::RepairDroid const*, bool);
	Archetype::RepairDroid const* RepairDroidArch() const;

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
	static CEScanner const* cast(CEquip const*);

	CEScanner(CEScanner const&);
	CEScanner(CEqObj*, unsigned short, Archetype::Scanner const*, bool);
	float GetCargoScanRange() const;
	float GetRadarRange() const;
	enum ScanResult ScanCargo(CEqObj*);
	Archetype::Scanner const* ScannerArch() const;
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
	virtual bool Connect(char const*);
	virtual void Disconnect();

	static CEShield* cast(CEquip*);
	static CEShield const* cast(CEquip const*);

	CEShield(CEShield const&);
	CEShield(CEqObj*, unsigned short, Archetype::Shield const*, bool);
	Archetype::ShieldGenerator const* ShieldGenArch() const;
	Archetype::Shield const* ShieldArch() const;
	void AttachIntruderChecker();
	void DestroyIntruderChecker();
	float GetOfflineRebuildTime() const;
	float GetOfflineThreshold() const;
	float GetWeaponModifier(ID_String const&) const;
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
	static CEShieldGenerator const* cast(CEquip const*);

	CEShieldGenerator(CEShieldGenerator const&);
	CEShieldGenerator(CEqObj*, unsigned short, Archetype::ShieldGenerator const*, bool);
	Archetype::ShieldGenerator const* ShieldGenArch() const;
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
	static CEThruster const* cast(CEquip const*);

	CEThruster(CEThruster const&);
	CEThruster(CEqObj*, unsigned short, Archetype::Thruster const*, bool);
	Archetype::Thruster const* ThrusterArch() const;
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
	static CETractor const* cast(CEquip const*);

	CETractor(CETractor const&);
	CETractor(CShip*, unsigned short, Archetype::Tractor const*, bool);
	Archetype::Tractor const* TractorArch() const;
	enum TractorFailureCode AddTarget(struct CLoot*);
	int CountActiveArms() const;
	float GetRange() const;
	Vector GetSourcePos() const;
	class TractorArm const* GetTractorArm(unsigned int) const;
	st6::vector<TractorArm> const& GetTractorArms() const;
	void RemoveTarget(unsigned int);
	TractorFailureCode VerifyTarget(CLoot const*) const;
	bool CanSeeTarget(CLoot const*) const;
};

class IMPORT CETradeLaneEquip : public CInternalEquip
{
  public:
	virtual ~CETradeLaneEquip();

	static CETradeLaneEquip* cast(CEquip*);
	static CETradeLaneEquip const* cast(CEquip const*);

	CETradeLaneEquip(CETradeLaneEquip const&);
	CETradeLaneEquip(CEqObj*, unsigned short, Archetype::TradeLaneEquip const*, bool);
	Archetype::TradeLaneEquip const* TradeLaneArch() const;

	Archetype::TradeLaneEquip* archType;
};

class IMPORT CEquipManager
{
  public:
	CEquipManager(CEquipManager const&);
	CEquipManager();
	~CEquipManager();
	CEquipManager& operator=(CEquipManager const&);
	bool AddNewEquipment(CEquip*);
	int CleanUp();
	void Clear();
	CExternalEquip* FindByHardpoint(CacheString const&);
	CExternalEquip const* FindByHardpoint(CacheString const&) const;
	CEquip* FindByID(unsigned short);
	CEquip const* FindByID(unsigned short) const;
	CEquip* FindFirst(unsigned int);
	CEquip const* FindFirst(unsigned int) const;
	bool HasDecayingCargo() const;
	bool Init(CEqObj*);
	unsigned short InstToSubObjID(long) const;
	CEquip* ReverseTraverse(class CEquipTraverser&);
	CEquip const* ReverseTraverse(CEquipTraverser&) const;
	int Size() const;
	CEquip* Traverse(CEquipTraverser&);
	CEquip const* Traverse(CEquipTraverser&) const;
	bool VerifyListSync(class EquipDescList const&) const;

  private:
	int CleanUp(st6::list<CEquip*, st6::allocator<CEquip*>>&);
	static void Clear(st6::list<CEquip*, st6::allocator<CEquip*>>&);

  public:
	unsigned char data[180];
};

class IMPORT CEquipTraverser
{
  public:
	CEquipTraverser(int);
	CEquipTraverser(int, bool);
	CEquipTraverser();
	CEquipTraverser& operator=(CEquipTraverser const&);
	void Restart();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CEqObj : public CSimple
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	virtual ~CEqObj();
	virtual int update(float, unsigned int);
	virtual void disable_controllers();
	virtual void enable_controllers();
	virtual void unmake_physical();
	virtual void remake_physical(PhySys::CreateParms const&, float);
	virtual unsigned int get_name() const;
	virtual bool is_targetable() const;
	virtual void init(CreateParms const&);
	virtual void load_equip_and_cargo(struct EquipDescVector const&, bool);
	virtual void clear_equip_and_cargo();
	virtual void get_equip_desc_list(EquipDescVector&) const;
	virtual bool add_item(EquipDesc const&);
	virtual enum ObjActivateResult activate(bool, unsigned int);
	virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&);
	virtual void disconnect(struct IObjDB*);
	virtual void disconnect(INotify*);
	virtual void disconnect(struct IObjRW*);
	virtual void connect(struct IObjDB*);
	virtual void connect(INotify*);
	virtual void notify(INotify::Event, void*);
	virtual void flush_animations();
	virtual float get_total_hit_pts() const;
	virtual float get_total_max_hit_pts() const;
	virtual float get_total_relative_health() const;
	virtual bool get_sub_obj_velocity(unsigned short, Vector&) const;
	virtual bool get_sub_obj_center_of_mass(unsigned short, Vector&) const;
	virtual bool get_sub_obj_hit_pts(unsigned short, float&) const;
	virtual bool set_sub_obj_hit_pts(unsigned short, float);
	virtual bool get_sub_obj_max_hit_pts(unsigned short, float&) const;
	virtual bool get_sub_obj_relative_health(unsigned short, float&) const;
	virtual unsigned short inst_to_subobj_id(long) const;
	virtual long sub_obj_id_to_inst(unsigned short) const;
	virtual void destroy_sub_objs(DamageList const&, bool);
	virtual int enumerate_sub_objs() const;
	virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);
	virtual void link_shields();

	struct IMPORT DockAnimInfo
	{
		DockAnimInfo();
		DockAnimInfo& operator=(DockAnimInfo const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	CEqObj(CEqObj const&);
	CEqObj(Class);
	void attaching_damaged_obj(CacheString const&);
	float attitude_towards(CEqObj const*) const;
	void attitude_towards_symmetrical(float&, CEqObj const*, float&) const;
	void clear_arch_groups();
	class IBehaviorManager* create_behavior_interface(IObjRW*, int);
	Archetype::EqObj* eqobjarch() const;
	unsigned int get_base() const;
	unsigned int get_base_name() const;
	IBehaviorManager* get_behavior_interface();
	float get_cloak_percentage() const;
	void get_collision_group_description(st6::list<CollisionGroupDesc>&) const;
	unsigned int const& get_dock_target() const;
	bool get_explosion_dmg_bounding_sphere(float&, Vector&) const;
	float get_max_power() const;
	float get_power() const;
	float get_power_ratio() const;
	int get_vibe() const;
	bool is_base() const;
	int is_cloaked() const;
	bool is_control_excluded(unsigned int) const;
	bool is_damaged_obj_attached(CacheString const&) const;
	bool is_dock() const;
	bool launch_pos(Vector&, Matrix&, int) const;
	void load_arch_groups(st6::list<CollisionGroupDesc> const&);
	void set_control_exclusion(unsigned int);
	void set_power(float);
	bool sync_cargo(EquipDescList const&);
	bool add_cargo_item(EquipDesc const&);
	bool add_equipped_item(EquipDesc const&);
	void compute_explosion_dmg_bounding_sphere(float&, Vector&) const;
	void init_docking_points(unsigned int);
	void update_docking_animations(float);

#ifdef _USE_DEPRECATED_COBJECT_VARIABLES_
	/* 0x088 */ Archetype::Ship* ship_arch;
	/* 0x08c */ uint dunno3[0x16];
	/* 0x0e0 */ CEquipManager equip_manager; // 180 bytes
	/* 0x194 */ float Power;
	/* 0x198 */ float MaxPower;
#endif // _USE_DEPRECATED_COBJECT_VARIABLES_

  private:
	void destroy_equipment(DamageList const&, bool);
};

inline CEquipManager* GetEquipManager(CEqObj* ceq)
{
	return (CEquipManager*)((char*)ceq + 0xE4);
}

class IMPORT CEquipmentObj : public CObject
{
  public:
	virtual ~CEquipmentObj();

	CEquipmentObj(CEquipmentObj const&);
	CEquipmentObj(Class);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CFLIDMaker
{
  public:
	CFLIDMaker& operator=(CFLIDMaker const&);
	unsigned int AllocateObjectID();
	unsigned int CreateStaticID(char const*);
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
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	virtual ~CGuided();
	virtual int update(float, unsigned int);
	virtual void init_physics(Vector const&, Vector const&);
	virtual void expire_safe_time();

	static bool seeker_can_see(Vector const&, Vector const&, Vector const&, Archetype::Munition const*);

	CGuided(CGuided const&);
	CGuided(Class);
	Archetype::MotorData const* get_motor_arch() const;
	unsigned short get_sub_target() const;
	IObjRW* get_target() const;
	void init(CreateParms const&);
	bool motor_on() const;
	bool seeker_can_see(Vector const&) const;
	void set_sub_target(unsigned short);
	void set_target(IObjRW*);
};

struct IMPORT CLoot : public CSimple
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	virtual ~CLoot();
	virtual int update(float, unsigned int);
	virtual unsigned int get_name() const;
	virtual void set_hit_pts(float);
	virtual void init_physics(Vector const&, Vector const&);
	virtual void init(CreateParms const&);

	Archetype::Equipment* container_arch() const;
	Archetype::Equipment* contents_arch() const;

	CLoot(CLoot const&);
	CLoot(Class);
	bool can_ai_tractor() const;
	float get_contents_hit_pts() const;
	unsigned int get_owner() const;
	unsigned int get_units() const;
	float get_volume() const;
	bool is_loot_temporary() const;
	void set_contents_hit_pts(float);
	void set_units(unsigned int);
};

struct IMPORT CMine : public CProjectile
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	virtual ~CMine();
	virtual int update(float, unsigned int);
	virtual unsigned int get_name() const;
	virtual void init_physics(Vector const&, Vector const&);
	virtual void init(CreateParms const&);
	virtual void expire_safe_time();

	CMine(CMine const&);
	CMine(Class);
	Archetype::Mine const* minearch();
};

struct IMPORT CMunition : public CProjectile
{
  public:
	virtual ~CMunition();

	CMunition(CMunition const&);
	CMunition(Class);
	Archetype::Munition const* munitionarch() const;
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

	CNonPhysAttachment(CNonPhysAttachment const&);
	CNonPhysAttachment();
	CNonPhysAttachment& operator=(CNonPhysAttachment const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CNudgeEngine : public CPhysControllerEquip
{
  public:
	virtual ~CNudgeEngine();
	virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);
	virtual bool EnableController();

	CNudgeEngine(CNudgeEngine const&);
	CNudgeEngine();
	CNudgeEngine& operator=(CNudgeEngine const&);
	bool Activate(bool);
	Vector GetNudgeVec() const;
	bool IsActive() const;
	void SetNudgeVec(Vector const&);
	void SetOwner(CShip*);

  protected:
	static float const NUDGE_CHANGE_THRESHOLD;
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

	CPhysAttachment(CPhysAttachment const&);
	CPhysAttachment();
	CPhysAttachment& operator=(CPhysAttachment const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CPlayerAccount
{
  public:
	CPlayerAccount(CPlayerAccount const&);
	CPlayerAccount();
	virtual ~CPlayerAccount();
	CPlayerAccount& operator=(CPlayerAccount const&);
	void GenerateAccount(char const*);
	static bool GenerateTextKey(char*);
	st6::wstring GetAccountName();
	char const* GetAccountNameChar();
	st6::wstring GetAccountNameSig();
	char const* GetAccountNameSigChar();
	st6::wstring GetServerSignature(char const*);
	static bool GetTextKey(char*);
	bool LoadAccount();
	bool LoadAccountFromStrings(char const*, char const*);
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
	CPlayerTradeOffer(CPlayerTradeOffer const&);
	CPlayerTradeOffer();
	virtual ~CPlayerTradeOffer();
	CPlayerTradeOffer& operator=(CPlayerTradeOffer const&);
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
	CRemotePhysicsSimulation(CRemotePhysicsSimulation const&);
	CRemotePhysicsSimulation();
	virtual ~CRemotePhysicsSimulation();
	CRemotePhysicsSimulation& operator=(CRemotePhysicsSimulation const&);
	double CalcPositionError(Vector const&);
	bool CheckForSync(Vector const&, Vector const&, Quaternion const&);
	void Doit(double);
	Vector GetLatestUpdate();
	Vector GetSample(int);
	unsigned long GetSampleCount();
	double GetSimulationTime();
	virtual void RemoteUpdate(Vector const&, Quaternion const&, double);
	void Reset();
	void SetLogging(bool);
	void tracef(char const*, ...);

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

struct IObjInspect
{
	struct CargoEnumerator;
	struct SubtargetEnumerator;
};

struct IMPORT CShip : public CEqObj, public PhySys::Controller
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	static float const JETTISON_CLEARANCE_TIME;

	virtual ~CShip();

	virtual void do_simulation_controller(IVP_Event_Sim*, IVP_U_Vector<IVP_Core>*);

	virtual int update(float, unsigned int);
	virtual void disable_controllers();
	virtual void enable_controllers();
	virtual unsigned int get_name() const;
	virtual void init_physics(Vector const&, Vector const&);
	virtual void flush_animations();
	virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);
	virtual void init(CreateParms const&);

	CShip(CShip const&);
	CShip();
	Archetype::Ship const* shiparch() const;
	void VerifyTarget();
	enum FORMATION_RTYPE add_follow_follower(IObjRW*);
	FORMATION_RTYPE add_formation_follower(IObjRW*);
	void airlock_in(Vector const&, Matrix const&);
	bool any_thrusters_on() const;
	bool check_formation_follower_status(float);
	float close_bay();
	bool generate_follow_offset(IObjInspect const*, Transform&) const;
	int get_ammo_capacity_remaining(unsigned int) const;
	int get_ammo_capacity_remaining(Archetype::Equipment const*) const;
	float get_angular_distance_travelled(float, float, float) const;
	float get_angular_distance_travelled(float, float, float, float) const;
	Vector get_angular_drag() const;
	float get_angular_speed_XY(float, float) const;
	float get_angular_speed_Z(float) const;
	Vector const& get_axis_throttle() const;
	enum BayState get_bay_state() const;
	float get_cargo_hold_remaining() const;
	float get_distance_travelled(float, float, float, IObject::ThrustEquipType) const;
	bool get_farthest_active_gun_range(float&) const;
	IObjRW* get_follow_leader();
	Vector const& get_follow_offset();
	int get_formation_follower_count();
	int get_formation_followers(IObjRW** const, unsigned int);
	unsigned int get_group_name() const;
	struct ShipGunStats const& get_gun_stats() const;
	float get_initial_speed_to_coast_distance(float, bool) const;
	float get_linear_drag() const;
	float get_max_bank_angle() const;
	float get_max_thrust_power() const;
	Vector get_nudge_vec() const;
	unsigned short const* get_pilot_name() const;
	float get_projected_axis_throttle_XY(float) const;
	float get_projected_axis_throttle_Z(float) const;
	float get_projected_throttle(float, IObject::ThrustEquipType) const;
	long get_renderable_subtarget() const;
	int get_repair_kit_capacity_remaining() const;
	int get_shield_battery_capacity_remaining() const;
	int get_space_for_cargo_type(Archetype::Equipment const*) const;
	float get_speed(float, IObject::ThrustEquipType) const;
	int get_status(char*, int) const;
	StrafeDir get_strafe_dir() const;
	unsigned short get_sub_target() const;
	IObjRW* get_target() const;
	int get_targeted_enemy_count();
	bool get_tgt_lead_fire_pos(Vector&) const;
	bool get_tgt_lead_fire_pos(IObjInspect const*, Vector&) const;
	float get_throttle() const;
	float get_thrust_power() const;
	float get_thrust_power_ratio() const;
	float get_time_to_accelerate(float, float, float, IObject::ThrustEquipType) const;
	float get_time_to_accelerate_angularly(float, float, float) const;
	float get_time_to_accelerate_angularly(float, float, float, float) const;
	unsigned int get_tradelane_entrance_ring();
	unsigned int get_tradelane_exit_ring();
	float get_tradelane_speed();
	int go_tradelane(IObjInspect const*, IObjInspect const*, IObjRW*, bool, float);
	bool is_cruise_active() const;
	bool is_enemy(IObjInspect*);
	bool is_jumping() const;
	bool is_launching() const;
	bool is_player() const;
	bool is_using_tradelane() const;
	void jump_in(IObjRW*, Vector const&, Matrix const&, float);
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
	void set_axis_throttle(Vector const&);
	void set_follow_leader(IObjRW*);
	void set_follow_offset(Vector const&);
	void set_gun_stats_dirty();
	void set_nudge_vec(Vector const&);
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

#ifdef _USE_DEPRECATED_COBJECT_VARIABLES_
	/* 105 */ DWORD vtable;
	DWORD dunno5[34];
	/* 139 */ DWORD BayAnim;
	DWORD dunno6[31];
	/* 170 */ DWORD BayState;
	/* 174 */ DWORD BayState2;
#endif // _USE_DEPRECATED_COBJECT_VARIABLES_
};

struct IMPORT CSolar : public CEqObj
{
  public:
	struct IMPORT CreateParms
	{
		CreateParms();
		CreateParms& operator=(CreateParms const&);

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
		// TODO: We have duplicated this struct in like 4 places, lets have one source of truth not 4. Merge them all into one.
		struct structCostume
		{
			uint head;
			uint body;
			uint leftHand;
			uint rightHand;
			uint accessory[8];
			int accessories;
		};
		structCostume costume;
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
	virtual void __stdcall set_velocity(long, Vector const&);
	virtual void __stdcall set_angular_velocity(long, Vector const&);
	virtual int update(float, unsigned int);
	virtual Vector get_velocity() const;
	virtual Vector get_angular_velocity() const;
	virtual float get_mass() const;
	virtual void cache_physical_props();
	virtual void init_physics(Vector const&, Vector const&);
	virtual ObjActivateResult activate(bool, unsigned int);
	virtual bool get_activate_state(st6::vector<bool, st6::allocator<bool>>&);
	virtual void flush_animations();
	virtual CEquip* alloc_equip(unsigned short, Archetype::Equipment*, bool);

	CSolar(CSolar const&);
	CSolar(Class);
	Archetype::Solar const* solararch() const;
	ID_String const& GetParentNickname() const;
	unsigned char GetVisitValue() const;
	static bool ReadObj(INI_Reader&, Archetype::Solar*&, CreateParms&);
	void SetVisitValue(unsigned char);
	float get_atmosphere_immersion(Vector const&) const;
	float get_atmosphere_range() const;
	ID_String const& get_dest_gate() const;
	unsigned int get_dest_system() const;
	ID_String const& get_loadout() const;
	unsigned int get_next_trade_ring() const;
	unsigned int get_prev_trade_ring() const;
	unsigned int get_tradelane_space_name() const;
	void init(CreateParms const&);
	bool is_destructible() const;
	bool is_dynamic() const;
	bool is_lane_ring() const;
	bool is_planetary() const;
	bool is_system_gate() const;
	bool is_waypoint() const;
	void configure_system_gate(char const*);
	void init_continual_anim(char const*);
	void update_system_gate(float);
};

struct IMPORT CharPlaceInfo
{
	CharPlaceInfo();
	~CharPlaceInfo();
	void clear();
	void destroy();
	bool is_named(char const*) const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CharacterProperties
{
  public:
	CharacterProperties();
	~CharacterProperties();
	CharacterProperties& operator=(CharacterProperties const&);
	void destroy();
	unsigned long get_key() const;
	void init(struct CharacterDescription const&);
	void marshal(MarshalBuffer*) const;
	void unmarshal(MarshalBuffer*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT ClipNode
{
  public:
	ClipNode(tagRECT const&);
	ClipNode(ClipNode const&);
	ClipNode();
	virtual ~ClipNode();
	ClipNode& operator=(ClipNode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	tagRECT const& get_rect();
	void set_rect(tagRECT const&);

	virtual operator ClipNode*();
	virtual operator ClipNode const*() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace Collision
{
	IMPORT float CalcCollisionDamage(unsigned int, Vector const&, Vector const&);
	IMPORT float CalcCollisionDamage(float, float, float);
	IMPORT void Free();
	IMPORT float GetImpactDamageFromType(unsigned int);
	IMPORT bool Load(INI_Reader&);
}; // namespace Collision

struct IMPORT CollisionGroupDesc
{
	CollisionGroupDesc& operator=(CollisionGroupDesc const&);
	bool operator==(CollisionGroupDesc const&) const;
	bool operator!=(CollisionGroupDesc const&) const;
	bool operator<(CollisionGroupDesc const&) const;
	bool operator>(CollisionGroupDesc const&) const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CommReferrable
{
	CommReferrable(CommReferrable const&);
	CommReferrable();
	CommReferrable& operator=(CommReferrable const&);
	virtual TString<64> const& GetMsgIdPrefix() const;
	virtual bool HasVoiceInfo() const;
	virtual bool read_comm_ini_data(INI_Reader&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT CostumeDescriptions
{
  public:
	CostumeDescriptions(CostumeDescriptions const&);
	CostumeDescriptions();
	~CostumeDescriptions();
	CostumeDescriptions& operator=(CostumeDescriptions const&);
	struct accessory const* find_accessory(unsigned long) const;
	accessory const* find_accessory(char const*) const;
	unsigned long find_accessory_id(char const*) const;
	struct bodypart const* find_bodypart(int, unsigned long) const;
	bodypart const* find_bodypart(int, char const*) const;
	struct costume const* find_costume(unsigned long) const;
	costume const* find_costume(char const*) const;
	unsigned long find_costume_id(char const*) const;
	unsigned long find_part_id(int, char const*) const;
	void get_costume(int, struct Costume&) const;
	void get_costume(char const*, Costume&) const;
	int get_costume_gender(Costume const&) const;
	int get_costume_gender(unsigned long) const;
	char const* get_part_mesh(int, unsigned long) const;
	char const* get_part_name(int, unsigned long) const;
	void load_bodyparts(char const*);
	void load_costumes(char const*);

  private:
	void load_accessory(INI_Reader*);
	void load_bodypart(int, int, class DetailSwitchTable*, INI_Reader*);
	void warn(INI_Reader*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT CostumeHint
{
	CostumeHint(CostumeHint const&);
	CostumeHint();
	virtual ~CostumeHint();
	CostumeHint& operator=(CostumeHint const&);
	virtual void CleanUp(unsigned char*);
	virtual unsigned int Serialize(unsigned char**);
	virtual void UnSerialize(unsigned char*, unsigned int);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT Csys
{
  public:
	Csys();
	Csys& operator=(Csys const&);
	Csys get_inverse() const;
	Transform get_transform() const;
	void init(Vector const&, Matrix const&);
	void set_identity();
	void set_transform(Transform const&);
	Csys trans_from_frame(Csys const&) const;
	Matrix trans_from_frame(Matrix const&) const;
	Vector trans_from_frame(Vector const&) const;
	Csys trans_to_frame(Csys const&) const;
	Matrix trans_to_frame(Matrix const&) const;
	Vector trans_to_frame(Vector const&) const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

Csys operator*(Csys const&, Csys const&);

namespace DataConfig
{
	IMPORT void shutdown();
	IMPORT int startup(char const*, Archetype::IClObjFactory*, struct ProgressCB*);
}; // namespace DataConfig

class IMPORT DetailSwitchTable
{
  public:
	DetailSwitchTable(DetailSwitchTable const&);
	DetailSwitchTable();
	~DetailSwitchTable();
	DetailSwitchTable& operator=(DetailSwitchTable const&);
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

	TextRenderContext(TextRenderContext const&);
	TextRenderContext();
	virtual ~TextRenderContext();
	TextRenderContext& operator=(TextRenderContext const&);
	void clear_default_attributes();
	struct TextRenderAttributes const& get_current_attributes();
	TextRenderAttributes const& get_default_attributes();
	int get_origin_h();
	int get_origin_v();
	int get_pos_h();
	int get_pos_v();
	void pop_default_attributes();
	void pop_state();
	void push_default_attributes();
	void push_state();
	void reset_to_default();
	void set_current_attributes(TextRenderAttributes const&);
	void set_default_attributes(TextRenderAttributes const&);
	void set_origin(int, int);
	void set_origin_h(int);
	void set_origin_v(int);
	void set_pos(int, int);
	void set_pos_h(int);
	void set_pos_v(int);

  private:
	void get_state(struct State&);
	void set_state(State const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT DeviceTRC
{
  public:
	DeviceTRC(DeviceTRC const&);
	DeviceTRC(HDC__*);
	DeviceTRC();
	virtual ~DeviceTRC();
	DeviceTRC& operator=(DeviceTRC const&);
	void bind_to_dc(HDC__*);
	virtual TextRenderContext::Image* create_image(char const* const);
	virtual void destroy_image(TextRenderContext::Image*);
	virtual void execute_image(TextRenderContext::Image const*, bool);
	virtual void execute_text(unsigned short const*, bool, int);
	virtual int get_cell_height() const;
	virtual int get_cell_width() const;
	virtual void get_clip_rect(tagRECT&);
	virtual void get_font_metrics(int&, int&) const;
	virtual void get_text_fit(unsigned short const*, int, int&, int*, VisualSize&, int) const;
	virtual void get_text_visual_size(unsigned short const*, VisualSize&, int) const;
	static void release_font(int);
	virtual void set_clip_rect(tagRECT const&);
	static void set_drop_shadow_offset(int, int);
	static void set_image_root(char const*);
	static void static_set_font(int, TextRenderContext::FontDesc const&, float);

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
	EquipDesc(EquipDesc const&);
	EquipDesc();
	EquipDesc& operator=(EquipDesc const&);
	bool operator==(EquipDesc const&) const;
	bool operator!=(EquipDesc const&) const;
	bool operator<(EquipDesc const&) const;
	bool operator>(EquipDesc const&) const;

	static CacheString const CARGO_BAY_HP_NAME;
	unsigned int get_arch_id() const;
	float get_cargo_space_occupied() const;
	int get_count() const;
	CacheString const& get_hardpoint() const;
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
	void set_hardpoint(CacheString const&);
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
	EquipDescList(EquipDescVector const&);
	EquipDescList(EquipDescList const&);
	EquipDescList();
	~EquipDescList();
	EquipDescList& operator=(EquipDescList const&);
	int add_equipment_item(EquipDesc const&, bool);
	void append(EquipDescList const&);
	EquipDesc* find_equipment_item(CacheString const&);
	EquipDesc* find_equipment_item(unsigned short);
	EquipDesc const* find_equipment_item(CacheString const&) const;
	EquipDesc const* find_equipment_item(unsigned short) const;
	EquipDesc const* find_matching_cargo(unsigned int, int, float) const;
	float get_cargo_space_occupied() const;
	int remove_equipment_item(unsigned short, int);
	EquipDesc* traverse_equipment_type(unsigned int, EquipDesc const*);
	EquipDesc const* traverse_equipment_type(unsigned int, EquipDesc const*) const;

  public:
	st6::list<EquipDesc> equip;
};

struct IMPORT EquipDescVector
{
	EquipDescVector(EquipDescVector const&);
	EquipDescVector(EquipDescList const&);
	EquipDescVector();
	~EquipDescVector();
	EquipDescVector& operator=(EquipDescVector const&);
	int add_equipment_item(EquipDesc const&, bool);
	void append(EquipDescVector const&);
	EquipDesc* traverse_equipment_type(unsigned int, EquipDesc const*);

  public:
	st6::vector<EquipDesc> equip;
};

namespace ErrorHandler
{
	IMPORT void activate(char const*, int (*)(char const*, char const*, bool));
	IMPORT void deactivate();
	IMPORT bool is_log_enabled(int);
	IMPORT void log_comment(int, char const*, ...);
	IMPORT void log_disable(int);
	IMPORT void log_enable(int);
	IMPORT void log_last_error(char const*, int, enum SeverityLevel, char*, unsigned long);
	IMPORT void* new_log(char const*, int, int, bool, bool);
}; // namespace ErrorHandler

struct IMPORT ExhaustNozzleInfo
{
	ExhaustNozzleInfo();
	ExhaustNozzleInfo& operator=(ExhaustNozzleInfo const&);
	bool GetHardpointOffset_NS(Transform&) const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT File
{
  public:
	File();
	~File();
	File& operator=(File const&);
	void close();
	int eof();
	void get_info();
	int get_length();
	char const* get_name() const;
	bool is_open();
	bool open(char const*);
	int read(void*, int);
	int read(void*, int, int);
	int read_line(char*, int);
	int seek(int);
	void set_name(char const*);
	int set_offset(int);
	int tell() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT FileMap
{
	FileMap(FileMap const&);
	FileMap();
	~FileMap();
	FileMap& operator=(FileMap const&);
	void close();
	bool eof() const;
	unsigned int get_file_length() const;
	char const* get_file_name() const;
	void handoff_to(FileMap&);
	bool open(char const*);
	bool open_memory(void const*, unsigned int);
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
	FlashLightSetInfo& operator=(FlashLightSetInfo const&);
	void clear();
	void destroy();
	void fixup(long, class HardpointSummary const*, RoomData const*);
	void unfixup();

  private:
	void add_light_csys(Csys const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT FmtStr
{
	struct IMPORT Val
	{
		Val(Val const&);
		Val(unsigned short, void*, unsigned char);
		Val(void const*);
		Val(void const*, int&);
		~Val();
		Val const& operator=(Val const&);
		bool operator==(Val const&) const;
		unsigned int flatten(void*, unsigned int) const;
		unsigned int get_flattened_size() const;

		static void* operator new(unsigned int);
		static void operator delete(void*);

	  private:
		int InitFromVoid(void const*);

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	FmtStr(FmtStr const&);
	FmtStr(unsigned int, Val const*);
	~FmtStr();
	FmtStr const& operator=(FmtStr const&);
	bool operator==(FmtStr const&) const;
	void append(Val*);
	void append_base(unsigned int const&);
	void append_fmt_str(FmtStr const&);
	void append_good(unsigned int const&);
	void append_installation(int);
	void append_int(unsigned int);
	void append_loot(int);
	void append_nav_marker(struct NavMarker const&);
	void append_rep_group(unsigned int const&);
	void append_rep_instance(int const&);
	void append_spaceobj_id(unsigned int const&);
	void append_string(unsigned int);
	void append_system(unsigned int const&);
	int append_void(void*);
	void append_zone_id(unsigned int const&);
	void begin_mad_lib(unsigned int);
	void destroy();
	void end_mad_lib();
	int flatten(void*, unsigned int) const;
	int unflatten(void*, unsigned int);

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
	Fuse(ID_String const&, float);
	Fuse(Fuse const&);
	virtual ~Fuse();
	Fuse& operator=(Fuse const&);
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
	ID_String const& Name() const;
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
	FuseAction(FuseAction const&);
	FuseAction();
	virtual ~FuseAction();
	FuseAction& operator=(FuseAction const&);
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
	virtual void CopyArchProperties(FuseAction const&);
	bool ReadFuseActionValue(INI_Reader&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT FuseDB
{
  public:
	FuseDB& operator=(FuseDB const&);
	static void AddFuseINIFile(char const*);
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
	GoodDesc& operator=(GoodDesc const&);

	static void* operator new(unsigned int);
	static void operator delete(void*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT GoodDescList
{
	GoodDescList(GoodDescList const&);
	GoodDescList();
	virtual ~GoodDescList();
	GoodDescList const& operator=(GoodDescList const&);

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
	/* 72 */ uint archId;
	/* 76 */ Type type; // 0=commodity, 2=hull, 3=ship
	/* 80 */ uint i3;
	/* 84 */ uint shipGoodId; // if type = GOODINFO_TYPE_HULL
	/* 88 */ float price;
	/* 92 */ float goodSellPrice;
	/* 96 */ float badBuyPrice;
	/* 100 */ float badSellPrice;
	/* 104 */ float goodBuyPrice;
	/* 108 */ uint jumpDist;
	/* 112 */ float dunno2;
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
	GoodInfoList(GoodInfoList const&);
	GoodInfoList();
	~GoodInfoList();
	GoodInfoList& operator=(GoodInfoList const&);
	void destroy();
	GoodInfo const* find_by_archetype(unsigned int) const;
	GoodInfo const* find_by_id(unsigned int) const;
	GoodInfo const* find_by_name(char const*) const;
	GoodInfo const* find_by_ship_arch(unsigned int) const;
	st6::list<GoodInfo*, st6::allocator<GoodInfo*>> const* get_list() const;
	void load(char const*);

  private:
	void read_Good_block(INI_Reader*, GoodInfo*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace GoodList
{
	IMPORT GoodInfo const* find_by_archetype(unsigned int);
	IMPORT GoodInfo const* find_by_id(unsigned int);
	IMPORT GoodInfo const* find_by_nickname(char const*);
}; // namespace GoodList

class IMPORT HardpointSummary
{
  public:
	HardpointSummary(HardpointSummary const&);
	HardpointSummary();
	virtual ~HardpointSummary();
	HardpointSummary& operator=(HardpointSummary const&);
	int analyze_instance(long);
	void clear();
	void destroy();
	void expire_instance();
	int find_name(char const*) const;
	long find_name_instance(char const*) const;
	int get_count() const;
	HardpointInfo const& get_info(int) const;
	HardpointInfo const* get_info_by_name(char const*) const;
	long get_instance(int) const;
	char const* get_name(int) const;

  private:
	void count_hardpoints(long);
	static void count_hardpoints_callback(long, void*);
	void fill_hardpoints(long);
	static void fill_hardpoints_callback(long, void*);
	static void hardpoint_callback1(char const*, void*);
	static void hardpoint_callback2(char const*, void*);

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
	IAction(IAction const&);
	IAction();
	virtual ~IAction();
	IAction& operator=(IAction const&);
	virtual char const* get_id() const;

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
					int type;                         // 11
					float distance;                   // 5000
					int flag;                         // 15
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
			static float const SCAN_CHANCE_DEFAULT;
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
			virtual void lead_object_event(unsigned int, unsigned int, enum LeadProgressType, float, Vector const&);
			virtual bool request_flee_destination(unsigned int, enum FleeReason, enum FleeDestinationType&, Vector&, unsigned int&, float&);
			virtual void scan_state_change(bool);
			virtual void ship_in_sights_event(unsigned int);
			virtual void tether_object_event(unsigned int, unsigned int, enum TetherStatusType, Vector const&);

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
			DirectiveCancelOp(DirectiveCancelOp const&);
			DirectiveCancelOp();
			virtual bool validate();
		};

		class IMPORT DirectiveDelayOp : public BaseOp
		{
		  public:
			DirectiveDelayOp(DirectiveDelayOp const&);
			DirectiveDelayOp();
			virtual bool validate();

			float DelayTime;
		};

		class IMPORT DirectiveDockOp : public BaseOp
		{
		  public:
			DirectiveDockOp(DirectiveDockOp const&);
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
			DirectiveDrasticEvadeOp(DirectiveDrasticEvadeOp const&);
			DirectiveDrasticEvadeOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveEvadeOp : public BaseOp
		{
		  public:
			DirectiveEvadeOp(DirectiveEvadeOp const&);
			DirectiveEvadeOp();
			virtual bool validate();

			uint EvadeSpaceObj;
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveFaceOp : public BaseOp
		{
		  public:
			DirectiveFaceOp(DirectiveFaceOp const&);
			DirectiveFaceOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveFollowOp : public BaseOp
		{
		  public:
			DirectiveFollowOp(DirectiveFollowOp const&);
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
			DirectiveFormationOp(DirectiveFormationOp const&);
			DirectiveFormationOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveGotoOp : public BaseOp
		{
		  public:
			DirectiveGotoOp(DirectiveGotoOp const&);
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
			DirectiveGuideOp(DirectiveGuideOp const&);
			DirectiveGuideOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveIdleOp : public BaseOp
		{
		  public:
			DirectiveIdleOp(DirectiveIdleOp const&);
			DirectiveIdleOp();
			virtual bool validate();
		};

		class IMPORT DirectiveInstantTradelaneOp : public BaseOp
		{
		  public:
			DirectiveInstantTradelaneOp(DirectiveInstantTradelaneOp const&);
			DirectiveInstantTradelaneOp();
			virtual bool validate();

			uint tradelaneRingFrom;
			uint tradelaneRingTo;
			float dunno; // 3750
		};

		class IMPORT DirectiveLaunchOp : public BaseOp
		{
		  public:
			DirectiveLaunchOp(DirectiveLaunchOp const&);
			DirectiveLaunchOp();
			virtual bool validate();

			uint launchFromObject;
			uint x10; // 2, cannot be -1, defaults to -1
			uint x14; // 1, cannot be 0, defaults to 0
		};

		class IMPORT DirectiveRamOp : public BaseOp
		{
		  public:
			DirectiveRamOp(DirectiveRamOp const&);
			DirectiveRamOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveStrafeOp : public BaseOp
		{
		  public:
			DirectiveStrafeOp(DirectiveStrafeOp const&);
			DirectiveStrafeOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveTractorBeamOp : public BaseOp
		{
		  public:
			DirectiveTractorBeamOp(DirectiveTractorBeamOp const&);
			DirectiveTractorBeamOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveTrailOp : public BaseOp
		{
		  public:
			DirectiveTrailOp(DirectiveTrailOp const&);
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
			DirectiveWaitForPlayerManeuverOp(DirectiveWaitForPlayerManeuverOp const&);
			DirectiveWaitForPlayerManeuverOp();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		class IMPORT DirectiveWaitForShip
		{
		  public:
			DirectiveWaitForShip(DirectiveWaitForShip const&);
			DirectiveWaitForShip();
			virtual bool validate();

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		struct IMPORT GSplinePath
		{
			GSplinePath();
			GSplinePath& operator=(GSplinePath const&);

		  public:
			unsigned char data[OBJECT_DATA_SIZE];
		};

		struct IMPORT SetFlagParams
		{
			SetFlagParams(SetFlagParams const&);
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

		struct IMPORT SetZoneBehaviorParams : public BaseOp
		{
			SetZoneBehaviorParams(SetZoneBehaviorParams const&);
			SetZoneBehaviorParams();
			virtual bool validate();

			uint zoneType; // 0 = position, 2 = spaceobj
			uint x10;      // 0
			Vector vPosition;
			uint spaceObj;
			uint x24; // ??
			uint x28; // ??
			uint x2C; // ??
			uint x30; // ??
			uint x34; // ??
			uint x38; // ??
			float range;
		};

	}; // namespace AI

	namespace StateGraph
	{
		enum Type
		{
			TYPE_STANDARD = 0
		};

		IMPORT int get_state_graph(int, Type);
		IMPORT int get_state_graph(char const*, Type);
		IMPORT IStateGraph const* get_state_graph_internal(int);
		IMPORT void refresh_state_graph();
	}; // namespace StateGraph

}; // namespace pub

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
	struct IDirectiveInfo const* get_current_directive();
	IObjRW const* get_debugger_target() const;
	bool get_docking_port(IObjRW const*&, int&);
	unsigned int get_parent_id();
	void get_personality(pub::AI::Personality&);
	pub::AI::ScanResponse get_scan_response(unsigned int);
	Vector const get_ship_up_direction();
	IStateGraph const* get_state_graph();
	class SystemManager* get_sys();
	bool get_user_turning_input_state();
	bool lock_maneuvers(bool);
	void refresh_state_graph();
	void reset_current_behavior_direction();
	void set_camera_mode(IBehaviorCameraMode);
	void set_content_callback(pub::AI::ContentCallback*);
	bool set_current_directive(IDirectiveInfo const&, pub::AI::BaseOp const*);
	void set_directive_callback(pub::AI::DirectiveCallback*);
	pub::AI::OP_RTYPE set_directive_priority(pub::AI::DirectivePriority);
	void set_personality(pub::AI::Personality const&);
	void set_ship_up_direction(Vector const&);
	void set_state_graph(int, bool);
	void set_turn_sensitivity(float);
	void set_user_turning_input_state(bool);
	void submit_camera_up(Vector const&);
	void update_current_behavior_afterburner(bool);
	void update_current_behavior_auto_avoidance(bool);
	void update_current_behavior_auto_level(bool);
	void update_current_behavior_brake_reverse(bool);
	void update_current_behavior_cruise(bool);
	void update_current_behavior_direction(Vector const&);
	void update_current_behavior_engage_engine(bool);
	void update_current_behavior_slide_strafe_burst(StrafeDir);
	void update_current_behavior_throttle(float);
	void update_level_camera(bool);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT ICRSplineSegment
{
	ICRSplineSegment();
	ICRSplineSegment& operator=(ICRSplineSegment const&);
	void calculate_arclength();
	Vector calculate_spline_tangent(float);
	Vector calculate_spline_vector(float);
	float get_spline_length();
	float get_t_from_point(Vector const&, float, float);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT IObjInspectImpl
{
	virtual Vector const& get_position() const;
	virtual Vector get_velocity() const;
	virtual Vector get_angular_velocity() const;
	virtual Matrix const& get_orientation() const;
	virtual Transform const& get_transform() const;
	virtual Vector get_center_of_mass() const;
	virtual int get_sub_obj_center_of_mass(unsigned short, Vector&) const;
	virtual long get_index() const;
	virtual unsigned int const get_id() const;
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
	virtual int is_cruise_active(bool&) const; // why in different order ?! msvc i hate you! both is_cruise_active dont work properly for players(always return
	                                           // false when engine kill was used during cruise)
	virtual int is_cruise_active(bool&, bool&) const;
	virtual int are_thrusters_active(bool&) const;
	virtual int get_attitude_towards(float&, IObjInspect const*) const;
	virtual int get_attitude_towards_symmetrical(float&, IObjInspect const*, float&) const;
	virtual int get_reputation(float&, unsigned int const&) const;
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
	virtual int get_data(void const*&) const;
	virtual int get_formation_offset(Vector&) const;
	virtual int get_formation_leader(IObjRW*&) const;
	virtual int get_follow_offset(Vector&) const;
	virtual int get_follow_leader(IObjRW*&) const;
	virtual bool is_player() const;
	virtual int get_hardpoint(char const*, Vector*, Matrix*) const;
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
	virtual int get_scanlist(struct ScanList const*&, unsigned int, bool) const;
	virtual int get_tgt_lead_fire_pos(unsigned short const&, Vector&) const;
	virtual int is_pointing_at(bool&, unsigned short const&, float) const;
	virtual int can_point_at(bool&, unsigned short const&, Vector const&, float) const;
	virtual int find_equipment(unsigned short* const, unsigned int, unsigned int) const;
	virtual int get_equipment_status(EquipStatus&, unsigned short const&) const;
	virtual int get_equipment_val(struct EquipmentVal&, unsigned short const&, enum EquipmentValType, float) const;
	virtual int scan_cargo(IObjRW*, EquipDescVector&) const;
	virtual int enumerate_subtargets(IObjInspect::SubtargetEnumerator*) const;
	virtual int get_lane_direction(Transform const&, bool*) const;
	virtual int get_ring_side(Transform const&, bool*) const;
	virtual int traverse_rings(unsigned int&, bool) const;
	virtual int is_using_tradelane(bool*) const;
	virtual int get_lane_start(IObjInspect const*, IObjInspect const*&, Vector&, Vector&) const;
	virtual bool generate_follow_offset(IObjInspect const*, Transform&) const;
	virtual int get_atmosphere_range(float&) const;
	virtual int get_toughness() const;
	virtual int get_behavior_id() const;
	virtual int get_formation_followers(IObjRW** const, unsigned int) const;
	virtual CObject const* cobject() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IObjRW // : public IObjInspectImpl
{
	IObjInspectImpl* ship;
};

class IMPORT ImageNode
{
  public:
	ImageNode(ImageNode const&);
	ImageNode(TextRenderContext::Image const*);
	ImageNode();
	virtual ~ImageNode();
	ImageNode& operator=(ImageNode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	TextRenderContext::Image const* get_image();
	void set_image(TextRenderContext::Image const*);

	virtual operator ImageNode*();
	virtual operator ImageNode const*() const;

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
	LineParser32& operator=(LineParser32 const&);
	void clear();
	unsigned int fetch_string(char*, unsigned int);
	int find_char(char) const;
	char get_char() const;
	unsigned int read_string(char*, char const*);
	unsigned int read_terminator2(char*, char, char);
	unsigned int read_terminator(char*, char);
	void set(char const*, unsigned int);
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
		Map(Map const&);
		Map();
		~Map();
		Map& operator=(Map const&);

	  public:
		uint id;
		char cdunno; // -1
		EquipDesc* first;
		EquipDesc* last;
		EquipDesc* end;
	};

	IMPORT void Free();
	IMPORT Map const* Get(unsigned int);
	IMPORT unsigned int GetID(char const*);
	IMPORT int Load(char const*, bool);
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
	MPCritSec& operator=(MPCritSec const&);
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
	MarketGoodInfo& operator=(MarketGoodInfo const&);

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
	MarshalBuffer& operator=(MarshalBuffer const&);
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
	unsigned char const* get_buffer() const;
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
	void put_Costume(Costume const&);
	void put_EquipDescList(EquipDescList const&);
	void put_FL_ID(unsigned int);
	void put_FmtStr(FmtStr const&);
	void put_GoodDescList(GoodDescList const&);
	void put_U16(unsigned short);
	void put_U32(unsigned long);
	void put_U8(unsigned char);
	void put_bool(bool);
	void put_float(float);
	void put_image(unsigned char const&);
	void put_image(unsigned short const&);
	void put_image(int const&);
	void put_image(unsigned long const&);
	void put_image(float const&);
	void put_int(int);
	void put_string(char const*);
	void put_void(void const*, int);
	void put_wstring(unsigned short const*);
	void skip_over(int);
	void use_default();
	void use_read_buffer(unsigned char const*, int);
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
	MissionVendorAcceptance(MissionVendorAcceptance const&);
	MissionVendorAcceptance();
	~MissionVendorAcceptance();
	MissionVendorAcceptance& operator=(MissionVendorAcceptance const&);
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
	MissionVendorProperties(MissionVendorProperties const&);
	MissionVendorProperties();
	~MissionVendorProperties();
	MissionVendorProperties& operator=(MissionVendorProperties const&);
	void clear();
	void destroy();
	char const* get_icon_texture() const;
	unsigned long get_key() const;
	void init(struct MissionVendorOfferDescription const&);
	void marshal(MarshalBuffer*) const;
	void unmarshal(MarshalBuffer*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace NewChar
{
	IMPORT class IDatabase* TheDB;
};

class IMPORT NewsBroadcastProperties
{
  public:
	NewsBroadcastProperties(NewsBroadcastProperties const&);
	NewsBroadcastProperties();
	~NewsBroadcastProperties();
	NewsBroadcastProperties& operator=(NewsBroadcastProperties const&);
	void clear();
	void destroy();
	unsigned long get_key() const;
	char const* get_logo_texture() const;
	void init(struct NewsBroadcastDescription const&);
	void marshal(MarshalBuffer*) const;
	void unmarshal(MarshalBuffer*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT PathfindManager
{
	void clear_user_zone();
	bool get_user_zone(struct UserZone&);
	void submit_user_zone(UserZone const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT PetalInterfaceDatabase
{
  public:
	PetalInterfaceDatabase(PetalInterfaceDatabase const&);
	PetalInterfaceDatabase();
	~PetalInterfaceDatabase();
	PetalInterfaceDatabase& operator=(PetalInterfaceDatabase const&);
	void destroy();
	struct petal_record const* find_record(int, unsigned long) const;
	static int get_category(char const*);
	void load_from_ini(char const*);

  private:
	void add_record(int, char const*, char const*, char**, int);

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
	NullNode(NullNode const&);
	NullNode();
	virtual ~NullNode();
	NullNode& operator=(NullNode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);

	virtual operator NullNode*();
	virtual operator NullNode const*() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StyleNode
{
  public:
	StyleNode(StyleNode const&);
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
	ParagraphNode(ParagraphNode const&);
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
	TextNode(TextNode const&);
	TextNode(st6::wstring const&, int);
	TextNode(unsigned short const*, int);
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
	TextPtrNode(TextPtrNode const&);
	TextPtrNode(unsigned short const*, int);
	TextPtrNode();
	virtual ~TextPtrNode();
	TextPtrNode& operator=(TextPtrNode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	unsigned short const* get_text() const;
	int get_text_length() const;
	void set_text(unsigned short const*, int);

	virtual operator TextPtrNode*();
	virtual operator TextPtrNode const*() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT JustifyNode
{
  public:
	JustifyNode(JustifyNode const&);
	JustifyNode(enum TextJustify);
	virtual ~JustifyNode();
	JustifyNode& operator=(JustifyNode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	TextJustify get_justify();
	void set_justify(TextJustify);

	virtual operator JustifyNode*();
	virtual operator JustifyNode const*() const;

  public:
	unsigned char data[1024];
};

class IMPORT PositionNode
{
  public:
	PositionNode(PositionNode const&);
	PositionNode();
	virtual ~PositionNode();
	PositionNode& operator=(PositionNode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
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
	virtual operator PositionNode const*() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RDLNode
{
  public:
	RDLNode(RDLNode const&);
	RDLNode();
	virtual ~RDLNode();
	RDLNode& operator=(RDLNode const&);

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
	virtual operator AttribStackNode const*() const;
	virtual operator ClipNode const*() const;
	virtual operator ImageNode const*() const;
	virtual operator JustifyNode const*() const;
	virtual operator NullNode const*() const;
	virtual operator ParagraphNode const*() const;
	virtual operator PositionNode const*() const;
	virtual operator RDLReNode const*() const;
	virtual operator StyleNode const*() const;
	virtual operator TRANode const*() const;
	virtual operator TextNode const*() const;
	virtual operator TextPtrNode const*() const;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RDLReNode
{
  public:
	RDLReNode(RenderDisplayList&);
	RDLReNode(RDLReNode const&);
	virtual ~RDLReNode();
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	RenderDisplayList const& get_list();

	virtual operator RDLReNode*();
	virtual operator RDLReNode const*() const;

  public:
	unsigned char data[1024];
};

struct IMPORT Rect
{
	Rect(int, int, int, int);
	Rect();
	Rect& operator=(Rect const&);
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
	RenderDisplayList(RenderDisplayList const&);
	RenderDisplayList();
	~RenderDisplayList();
	RenderDisplayList& operator=(RenderDisplayList const&);
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
	struct Relation;

	namespace Vibe
	{
		IMPORT int AdjustAttitude(int const&, int const&, float);
		IMPORT int Alloc(int const&);
		IMPORT int AttitudeTowards(int const&, int const&, float&);
		IMPORT int AttitudeTowardsSymmetrical(int const&, int const&, float&, float&);
		IMPORT unsigned int Count();
		IMPORT int EnsureExists(int const&);
		IMPORT int Free(int const&);
		IMPORT void FreeDynamic();
		IMPORT int Get(int const&, unsigned int&, unsigned int&, unsigned char&, Relation* const, FmtStr&, FmtStr&, unsigned short const*&);
		IMPORT int GetAffiliation(int const&, unsigned int&, bool);
		IMPORT unsigned int GetClientID(int);
		IMPORT int GetGroupFeelingsTowards(int const&, unsigned int const&, float&);
		IMPORT int GetInfocard(int const&, unsigned int&);
		IMPORT int GetName(int const&, FmtStr&, FmtStr&, unsigned short const*&);
		IMPORT int GetRank(int const&, unsigned int&);
		IMPORT int Set(int const&, unsigned int, unsigned int, unsigned char, Relation const* const, FmtStr const&, FmtStr const&, unsigned short const*);
		IMPORT int SetAffiliation(int const&, unsigned int, bool);
		IMPORT int SetAttitudeTowardsPlayer(int, float);
		IMPORT int SetClientID(int, unsigned int);
		IMPORT int SetGroupFeelingsTowards(int const&, unsigned int const&, float);
		IMPORT int SetInfocard(int const&, unsigned int);
		IMPORT int SetName(int const&, FmtStr const&, FmtStr const&, unsigned short const*);
		IMPORT int SetRank(int const&, unsigned int);
		IMPORT bool Verify(int);
	}; // namespace Vibe

	IMPORT void FreeFeelings();
	IMPORT st6::map<unsigned int, unsigned int, st6::less<unsigned int>, st6::allocator<unsigned int>>* GetChangedAffiliationClientMap();
	IMPORT bool IsStoryFaction(unsigned int);
	IMPORT void LoadFeelings(INI_Reader&);
	IMPORT void Save(struct ISave*);
	IMPORT void Shutdown();
	IMPORT bool Startup(char const*);
	IMPORT int affect_relation(unsigned int const&, unsigned int const&, float);
	IMPORT void enumerate(struct RepGroupCB*);
	IMPORT int get_feelings_towards(unsigned int, unsigned int, float&);
	IMPORT unsigned int get_id(TString<16> const&);
	IMPORT unsigned int get_info_card(unsigned int);
	IMPORT unsigned int get_name(unsigned int);
	IMPORT int get_nickname(TString<16>&, unsigned int const&);
	IMPORT unsigned int get_short_name(unsigned int);
	IMPORT unsigned int group_count();
	IMPORT void set(TString<16> const&, Relation* const, unsigned int);
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
	RoomCameraInfo& operator=(RoomCameraInfo const&);
	void clear();
	void destroy();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT RoomData
{
  public:
	RoomData(RoomData const&);
	RoomData();
	~RoomData();
	RoomData& operator=(RoomData const&);
	void clear();
	void destroy();
	void enumerate_CharacterPlacement_ini(void (*)(int, INI_Reader*, void*), void*) const;
	RoomCameraInfo const* find_camera(char const*, char const*) const;
	RoomCameraInfo const* find_camera_generic(char const*, char const*) const;
	struct SetpointInfo const* find_setpoint(char const*, char const*) const;
	SetpointInfo const* find_setpoint_generic(char const*, char const*) const;
	void fixup(long);
	RoomCameraInfo const* get_camera_info() const;
	void init(unsigned int, unsigned int, char const*, char const*);
	void load();
	void unfixup();
	void unload();

  private:
	void add_set_script_Camera(unsigned long, Csys const&, char const*, struct ThornCameraProperties const*);
	void add_set_script_Prop(
	    char const*, char const*, int, Csys const&, bool, bool, bool, bool, unsigned char, signed char, unsigned long, char const*, unsigned long, bool);
	void add_set_script_Setpoint(unsigned long, Csys const&, char const*, struct ThornEntity const*);
	void add_set_script_light(unsigned long, Csys const&, struct ThornLightProperties const*, unsigned char);
	SetpointInfo const* apply_setpoint(char const*, char**, Csys*, char const*);
	CharPlaceInfo* find_CharacterPlacement(char const*);
	void fixup_FlashLight_list(long, HardpointSummary const*);
	static void make_setpoint_name_generic(char const*, char*);
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
	void read_from_ini(char const*);
	void read_set_script(char const*);
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
	RoomLightInfo& operator=(RoomLightInfo const&);
	void clear();
	void destroy();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT RoomPropInfo
{
	RoomPropInfo();
	~RoomPropInfo();
	RoomPropInfo& operator=(RoomPropInfo const&);
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
	IMPORT bool is_enabled(char const*);
	IMPORT void load(char const*);
	IMPORT void set_slider(float);
	IMPORT bool validate_setting(char const*, char const*);
}; // namespace RtcSlider

struct IMPORT SMControllerEvent
{
	SMControllerEvent(int, void const*);

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
	ScanList(ScanList const&);
	ScanList();
	~ScanList();
	ScanList& operator=(ScanList const&);
	bool add(IObjRW*);
	int add_in_range(Vector const&, float, struct IObjDB*, unsigned int, struct Filter*);
	void remove(IObjRW*);
	void reset();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT ScriptBehavior
{
  public:
	ScriptBehavior(ScriptBehavior const&);
	ScriptBehavior();
	~ScriptBehavior();
	ScriptBehavior& operator=(ScriptBehavior const&);
	void clear();
	void destroy();
	unsigned long get_key() const;
	void init(struct CharacterBehaviorDescription const&);
	void marshal(MarshalBuffer*) const;
	void unmarshal(MarshalBuffer*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SetpointInfo
{
	SetpointInfo(SetpointInfo const&);
	SetpointInfo();
	~SetpointInfo();
	void clear();
	void destroy();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT SetpointProperties
{
	SetpointProperties(SetpointProperties const&);
	SetpointProperties();
	~SetpointProperties();
	SetpointProperties& operator=(SetpointProperties const&);
	void clear();
	char const* combine_to_name() const;
	void destroy();
	void extract_from_name(char const*);
	void set_segment(char const*);

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
	ShipGunStats& operator=(ShipGunStats const&);
	void clear();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
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
	IMPORT int FindSolarRep(ID_String const&);
};

class IMPORT SphereIntruderChecker
{
  public:
	SphereIntruderChecker(SphereIntruderChecker const&);
	SphereIntruderChecker();
	~SphereIntruderChecker();
	SphereIntruderChecker& operator=(SphereIntruderChecker const&);
	void check_sphere(unsigned int, Vector const&, float, st6::list<CObject*, st6::allocator<CObject*>>&);

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
	virtual void process(SMEventData const*);
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
	virtual void remove_state_machine(StateMachineMessageHandler const*);

  protected:
	virtual void process(SMEventData const*);
	void remove_dying_machines();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT StateMachineMessage
{
  public:
	StateMachineMessage(StateMachineMessage const&);
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
	StyleCollection& operator=(StyleCollection const&);
	static RenderDisplayList& get_style(unsigned short);
	static void remove_style(unsigned short);
	static void set_style(unsigned short, TextRenderAttributes const&);
	static void set_style(unsigned short, RenderDisplayList const&);

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
		CollGroupIdMaker& operator=(CollGroupIdMaker const&);
		unsigned short CreateGroupID();
		void Reset();

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	class IMPORT EquipIdMaker
	{
	  public:
		EquipIdMaker();
		EquipIdMaker& operator=(EquipIdMaker const&);
		unsigned short CreateEquipID();
		void Reset();

	  public:
		unsigned char data[OBJECT_DATA_SIZE];
	};

	class IMPORT ShieldIdMaker
	{
	  public:
		ShieldIdMaker();
		ShieldIdMaker& operator=(ShieldIdMaker const&);
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
	TRANode(TextRenderAttributes const&, unsigned int, unsigned int);
	TRANode(TRANode const&);
	TRANode();
	virtual ~TRANode();
	TRANode& operator=(TRANode const&);
	virtual RDLNode* Clone() const;
	virtual void Execute(TextRenderContext&, bool);
	virtual void GetElementPos(int, TextRenderContext&, int&) const;
	virtual void GetElementSize(int&) const;
	virtual void GetVisualSize(TextRenderContext const&, VisualSize&) const;
	virtual bool SplitAtSize(TextRenderContext const&, int, unsigned int, RDLNode*&, RDLNode*&) const;
	virtual void Update(float);
	TextRenderAttributes const& get_attributes();
	unsigned int get_default_mask();
	unsigned int get_mask();
	void set_attributes(TextRenderAttributes const&, unsigned int);
	void set_default_mask(unsigned int);
	void set_mask(unsigned int);

	virtual operator TRANode*();
	virtual operator TRANode const*() const;

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
	TextFile32(TextFile32 const&);
	TextFile32();
	~TextFile32();
	TextFile32& operator=(TextFile32 const&);
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
		Delta& operator=(Delta const&);
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
	IMPORT double seconds(int64 const&);
}; // namespace Timing

class IMPORT TractorArm
{
  public:
	TractorArm(TractorArm const&);
	TractorArm(CETractor*);
	~TractorArm();
	TractorArm& operator=(TractorArm const&);
	TractorFailureCode GetErrorCode() const;
	enum Mode GetMode() const;
	CLoot* GetTarget() const;
	Vector GetTipPos() const;
	bool IsOn() const;
	void SetTarget(CLoot*);
	void TurnOff();
	void Update(float);

  protected:
	static float const AcquireDelay;
	static float const GrabToleranceSquared;

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT TradeResponseInfo
{
  public:
	TradeResponseInfo(TradeResponseInfo const&);
	TradeResponseInfo();
	~TradeResponseInfo();
	TradeResponseInfo& operator=(TradeResponseInfo const&);
	void clear();
	void destroy();
	void marshal(MarshalBuffer*) const;
	void unmarshal(MarshalBuffer*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace TurnHelper
{
	IMPORT Vector get_angular_throttle(Matrix const&, Matrix const&, float*);
};

struct IMPORT Watchable
{
	Watchable();
	~Watchable();
	Watchable& operator=(Watchable const&);
	unsigned int unwatch();

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT XMLReader
{
  public:
	XMLReader(XMLReader const&);
	XMLReader();
	XMLReader& operator=(XMLReader const&);
	virtual bool extract_text_from_buffer(unsigned short*, unsigned int, unsigned int&, char const*, unsigned int);
	virtual bool read_buffer(RenderDisplayList&, char const*, unsigned int);
	virtual bool read_file(RenderDisplayList&, char const*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

class IMPORT XMLWriter
{
  public:
	XMLWriter(XMLWriter const&);
	XMLWriter();
	XMLWriter& operator=(XMLWriter const&);
	virtual bool write_buffer(RenderDisplayList const&, char*, unsigned int, unsigned int&);
	virtual bool write_file(RenderDisplayList const&, char const*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT accessory
{
	accessory(accessory const&);
	accessory();
	~accessory();
	accessory& operator=(accessory const&);
	char const* get_accessory_hardpoint() const;
	char const* get_character_hardpoint() const;
	st6::list<st6::string> const& get_materials() const;
	char const* get_mesh() const;
	char const* get_name() const;
	unsigned long get_name_crc() const;
	void init(char const*, char const*, char const*, char const*, st6::list<st6::string> const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT bodypart
{
	bodypart(bodypart const&);
	bodypart();
	~bodypart();
	bodypart& operator=(bodypart const&);
	int get_gender() const;
	char const* get_mesh() const;
	char const* get_name() const;
	unsigned long get_name_crc() const;
	st6::list<st6::string>* get_petal_anims() const;
	DetailSwitchTable* get_switch_table() const;
	void init(char const*, char const*, int, st6::list<st6::string>*, DetailSwitchTable*);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

struct IMPORT option_spec
{
	option_spec& operator=(option_spec const&);

  public:
	unsigned char data[OBJECT_DATA_SIZE];
};

namespace Geometry
{
	struct Frustum;
	struct Sphere;
}; // namespace Geometry

IMPORT bool operator!=(struct CHARACTER_ID const&, CHARACTER_ID const&);
IMPORT bool operator!=(Rect const&, Rect const&);
IMPORT bool operator<(CHARACTER_ID const&, CHARACTER_ID const&);

IMPORT void AppendMissionLogData(FmtStr const*, unsigned char*&, int&, int);
IMPORT unsigned int Arch2Good(unsigned int);
IMPORT void BaseDataList_destroy();
IMPORT BaseDataList* BaseDataList_get();
IMPORT void BaseDataList_load();
IMPORT void BaseDataList_load_market_data(char const*);
IMPORT void BuildDirectory(char const*);
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
IMPORT long CompoundInstanceFindFirstName(long, char const*);
IMPORT void CompoundInstanceList(long, int*, long**);
IMPORT void ComputeExplosiveImpulses(long, Vector&, Vector&, Vector&);
IMPORT bool CostumeGenderAdjust(int*, int);
IMPORT bool Costume_is_equal(struct Costume const&, struct Costume const&);
IMPORT unsigned int CreateID(char const*);

IMPORT float Csys_error(Csys const&, Csys const&);
IMPORT Csys Csys_identity();
IMPORT Csys Csys_init(Vector const&, Matrix const&);
IMPORT Csys Csys_interpolate(Csys, Csys, float);

IMPORT void DAEngine_create_filesystem(char const*, struct IFileSystem**, char const*);
IMPORT void DAEngine_release_filesystem(IFileSystem**);
IMPORT Csys DALib_Engine_get_csys(long);
IMPORT void DALib_Engine_set_csys(long, Csys const&);

IMPORT ID_String DEATH_COMM_FUSE;
IMPORT double DaysPerSecond;
IMPORT void DebugPrint(char const*, ...);
IMPORT unsigned int DecodeType(char const*);
IMPORT Matrix EulerMatrix(Vector const&);
IMPORT void ExtractMissionLogData(FmtStr*, unsigned char*&, int&);
IMPORT float FIRE_FAILED_DELAY;
IMPORT ID_String FIRE_FAILED_SOUND;

struct HardpointInfo;
IMPORT long FindChild(long, char const*);
IMPORT bool FindHardpoint(long, char const*, long&);
IMPORT bool FindHardpoint_OS(long, char const*, long&, HardpointInfo&);
IMPORT bool FindHardpoint_PS(long, char const*, long&, HardpointInfo&);
IMPORT void FreeCostumeDescriptions();
IMPORT void FreeSpatial(ISpatialPartition*);
IMPORT bool FrustumCull(Geometry::Frustum const&, Universe::IZone const*);
IMPORT IBehaviorManager* GetBehaviorManager(IObjRW*);
IMPORT CostumeDescriptions const* GetCostumeDescriptions();
IMPORT Matrix GetDirectionMatrix(Transform const&, Vector const&);
IMPORT void GetFileSysPath(char*, char const*, IFileSystem*);
IMPORT char const* GetFullFilename(char const*);
IMPORT long GetRoot(long);
IMPORT CObject* GetRoot(CObject const*);
IMPORT bool GetScreenShotPath(char* const);
IMPORT float GetSphereIntersectVol(float, float, float);
IMPORT bool GetUserDataPath(char* const);
IMPORT bool GetUserLocalDataPath(char* const);
IMPORT void GiveClientRunPermission();
IMPORT void GiveServerRunPermission();
IMPORT unsigned int Good2Arch(unsigned int);
IMPORT void GoodList_destroy();
IMPORT GoodInfoList* GoodList_get();
IMPORT void GoodList_load(char const*);
IMPORT bool HardpointPosition(long, char const*, Vector*, Matrix*);
IMPORT bool HardpointPositionA(long, char const*, Vector*, Matrix*);
IMPORT void HardpointToObject(long, HardpointInfo&);
IMPORT void HardpointToWorld(long, HardpointInfo&);
IMPORT void HexToWide(char const*, unsigned short*);
IMPORT bool InitializeRichText(int);
IMPORT bool IsDescendant(long, long);
IMPORT bool IsMPServer();
IMPORT float JETTISONED_CARGO_VELOCITY;
IMPORT bool JointEnumCallback(long, long, struct JointInfo const*, void*);
IMPORT float LOOT_OWNER_SAFE_TIME;
IMPORT float LOOT_UNSEEN_LIFE_TIME;
IMPORT float LOOT_UNSEEN_RADIUS;
IMPORT bool LayoutRichText(TextRenderContext&, RenderDisplayList const&, int, RenderDisplayList&, int, int, bool, int*, bool);
IMPORT void LoadBodypartDescriptions(char const*);
IMPORT void LoadCostumeDescriptions(char const*);
IMPORT Matrix LookMatrix(Vector const&);
IMPORT Matrix LookMatrixYup(Vector const&);
IMPORT int MAX_PLAYER_AMMO;
IMPORT float MUSIC_CROSS_FADE_DELAY;
IMPORT float MUZZLE_CONE_ANGLE;
IMPORT unsigned short MakeId(char const*);
IMPORT unsigned int MakeLocationID(unsigned int, char const*);
IMPORT ISpatialPartition* NewSpatial(char const*);
IMPORT int NumHardpoints(long, bool);
IMPORT float PLAYER_ATTACHED_EQUIP_HIT_PTS_SCALE;
IMPORT float PLAYER_COLLISION_GROUP_HIT_PTS_SCALE;
IMPORT int PackMissionLogData(int, FmtStr const*, unsigned char*, int);
IMPORT _GUID* ParseGUID(char const*, _GUID*);
IMPORT double ParseNumber(char const*);
IMPORT void PetalDB_destroy();
IMPORT PetalInterfaceDatabase const* PetalDB_get();
IMPORT void PetalDB_load(char const*);
IMPORT bool PlayerTrailAvailable;
IMPORT Rect RECT_to_Rect(tagRECT const&);
IMPORT Vector RandomVector(float);
IMPORT Vector random_inside_box(float, float, float);
IMPORT Vector random_inside_cylinder(float, float);
IMPORT Vector random_inside_ellipsoid(float, float, float);
IMPORT Vector random_inside_ring(float, float, float);
IMPORT Vector random_inside_sphere(float);
IMPORT Vector random_on_unit_sphere();
IMPORT Vector random_sphere_constrained(Vector const&, float);
IMPORT Vector random_sphere_constrained_2(Vector const&, float, float);
IMPORT bool ReadConstants(char const*);
IMPORT tagRECT Rect_to_RECT(Rect const&);
IMPORT struct ViewRect Rect_to_ViewRect(Rect const&);
IMPORT void RefreshLoadingProgress();
IMPORT void RegisterLoadingScreen(class ILoadingScreen*);
IMPORT void ReinitializeRichTextFonts();
IMPORT Matrix RotateMatrix(Vector const&);
//@@@TODO IMPORT unsigned int const  SMM_CHANGE_STATE;
//@@@TODO IMPORT unsigned int const  SMM_TIMEOUT;
IMPORT ID_String SND_CARGO_JETTISONED;
//@@@TODO IMPORT unsigned short const  SUBOBJ_ID_NONE;
//@@@TODO IMPORT unsigned short const  SUBOBJ_ID_POWER;
//@@@TODO IMPORT unsigned short const  SUBOBJ_ID_ROOT;
IMPORT unsigned long SafeWaitForSingleObject(void*, unsigned long);
IMPORT void SetIsMPServer(bool);
IMPORT void SetMultPlayer(bool);
IMPORT void SetStandardFont(int, TextRenderContext::FontDesc const&);
IMPORT void ShutdownRichText();
IMPORT bool SinglePlayer();
IMPORT ID_String SpaceflightLocationID;
IMPORT bool SphereCull(Geometry::Sphere const&, Universe::IZone const*);
IMPORT char* StringAlloc(char const*, bool);
IMPORT char const* StringIndex(char const*, unsigned int);
IMPORT void StringShutdown();
IMPORT unsigned long ThornGetRenderType(struct ThornEntity const*, char const*);
IMPORT bool ThornGetUserFloat(struct IScriptEngine*, int, char const*, float*);
IMPORT bool ThornGetUserInt(IScriptEngine*, int, char const*, int*);
IMPORT char const* ThornGetUserString(IScriptEngine*, int, char const*);
IMPORT void ThornScriptDestroy(IScriptEngine**);
IMPORT Csys ThornScriptGetCsys(IScriptEngine*, char const*);
IMPORT IScriptEngine* ThornScriptLoad(char const*);
IMPORT void ToggleIceCap(bool);
IMPORT double ValueNum(char const*, unsigned int);
IMPORT Rect ViewRect_to_Rect(ViewRect const&);
IMPORT float WALLA_MAX_DIST;
IMPORT float WALLA_MAX_DIST_ATTEN;
IMPORT int WALLA_PRIORITY_CUTOFF;
IMPORT float WALLA_START_ATTEN;
IMPORT void WaitForClientRunPermission();
IMPORT void WaitForServerRunPermission();
IMPORT void WideToHex(unsigned short const*, char*);

IMPORT int add_good_item(unsigned int, int, float, float, bool, GoodDescList*);
IMPORT bool arch_is_combinable(unsigned int);
IMPORT unsigned short const* filetime_to_wstring(_FILETIME const&);
//@@@ IMPORT struct GoodDesc *  find_good_item(struct GoodDescList *,unsigned int,class MetaNode<struct GoodDesc> * *);
IMPORT long get_projected_bounding_box(struct ICamera*, Vector const&, float, ViewRect*, float&);
IMPORT long get_projected_bounding_sphere(ICamera*, Vector const&, float, float&, float&, float&, float&);
IMPORT int lex_compare(RenderDisplayList const&, RenderDisplayList const&, bool);
IMPORT char const* malloc_strcpy(char**, char const*);
IMPORT void malloc_strfree(char**);
IMPORT unsigned short const* malloc_wstrcpy(unsigned short**, unsigned short const*);
IMPORT void malloc_wstrfree(unsigned short**);
IMPORT Rect rect_intersect(Rect const&, Rect const&);
IMPORT Rect rect_union(Rect const&, Rect const&);
IMPORT int remove_good_item(unsigned int, int, GoodDescList*);
IMPORT char* safe_strcat(char*, int, char const*);
IMPORT char* safe_strcpy(char*, int, char const*);
IMPORT unsigned short* safe_wcscpy(unsigned short*, int, unsigned short const*);
IMPORT unsigned long select_option_from_string(char*, option_spec const* const, int, char const*);
IMPORT bool strequal(char const*, char const*);

#endif //_FLCORECOMMON_H_
