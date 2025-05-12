#pragma once

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

enum class DockType
{
    Berth = 1,
    MoorSmall = 3,
    MoorMedium = 4,
    MoorLarge = 5,
    Ring = 6,
    Pad = 6,
    Jump = 7,
    Airlock = 8
};

enum class StrafeDir
{
    None = 0,
    Left = 1,
    Right = 2,
    Up = 3,
    Down = 4,
};

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

enum class EquipmentClass
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
    ExternalEquipment = Mine | CM | Gun | ShieldGenerator | Thruster | CargoPod | CloakingDevice,
    InternalEquipment = Engine | Power | Scanner | TractorBeam | RepairDroid | InternalFX | TradeLaneEquip | Armor,
};

enum HpAttachmentType
{
    WEAPON = 3,
    Pointer = 4,
    hp_countermeasure_dropper = 9,
    hp_mine_dropper = 12,
    hp_gun_special_1 = 15,
    hp_gun_special_2,
    hp_gun_special_3,
    hp_gun_special_4,
    hp_gun_special_5,
    hp_gun_special_6,
    hp_gun_special_7,
    hp_gun_special_8,
    hp_gun_special_9,
    hp_gun_special_10,
    hp_turret_special_1,
    hp_turret_special_2,
    hp_turret_special_3,
    hp_turret_special_4,
    hp_turret_special_5,
    hp_turret_special_6,
    hp_turret_special_7,
    hp_turret_special_8,
    hp_turret_special_9,
    hp_turret_special_10,
    hp_thruster,
    hp_torpedo_special_2,
    hp_fighter_shield_special_1,
    hp_fighter_shield_special_2,
    hp_fighter_shield_special_3,
    hp_fighter_shield_special_4,
    hp_fighter_shield_special_5,
    hp_fighter_shield_special_6,
    hp_fighter_shield_special_7,
    hp_fighter_shield_special_8,
    hp_fighter_shield_special_9,
    hp_fighter_shield_special_10,
    hp_elite_shield_special_1,
    hp_elite_shield_special_2,
    hp_elite_shield_special_3,
    hp_elite_shield_special_4,
    hp_elite_shield_special_5,
    hp_elite_shield_special_6,
    hp_elite_shield_special_7,
    hp_elite_shield_special_8,
    hp_elite_shield_special_9,
    hp_elite_shield_special_10,
    hp_freighter_shield_special_1,
    hp_freighter_shield_special_2,
    hp_freighter_shield_special_3,
    hp_freighter_shield_special_4,
    hp_freighter_shield_special_5,
    hp_freighter_shield_special_6,
    hp_freighter_shield_special_7,
    hp_freighter_shield_special_8,
    hp_freighter_shield_special_9,
    hp_freighter_shield_special_10,
    hp_torpedo_special_1,
};

enum class FireResult
{
    ObjectIsDestroyed = 0,
    ObjectIsDisabled = 1,
    RefireDelayNotElapsed = 2,
    AmmoRequirementsNotMet = 3,
    PowerRequirementsNotMet = 4,
    FailureGunAngle = 5,
    FailureCruiseActive = 6,
    FailureTradelane = 7,
    FailureCloakActive = 8,
    Success = 9,
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

enum class DestroyType
{
    Vanish = 0,
    Fuse = 1,
};
