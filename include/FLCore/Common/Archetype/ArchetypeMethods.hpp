#pragma once

#include "../../FLCoreDefs.hpp"
#include <FLCore/Common/Strings.hpp>

class INI_Reader;
namespace Archetype
{
    struct Equipment;
    struct Solar;
    struct Root;
    struct Ship;
    struct MotorData;
    struct Explosion;
    struct DynamicAsteroid;
    struct Asteroid;

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

    IMPORT void EnumAsteroids(struct ArchEnumerator*);
    IMPORT void EnumDynamicAsteroids(ArchEnumerator*);
    IMPORT void EnumEquipment(ArchEnumerator*);
    IMPORT void EnumShips(ArchEnumerator*);
    IMPORT void EnumSimples(ArchEnumerator*);
    IMPORT void EnumSolars(ArchEnumerator*);
    IMPORT void Free();
    IMPORT void FreeExplosions();
    IMPORT int GetArchMaxHitPts(u32);
    IMPORT Asteroid* GetAsteroid(u32);
    IMPORT Asteroid* GetAsteroidByName(const ID_String&);
    IMPORT u32 GetAsteroidID(const ID_String&);
    IMPORT DynamicAsteroid* GetDynamicAsteroid(u32);
    IMPORT DynamicAsteroid* GetDynamicAsteroidByName(const ID_String&);
    IMPORT u32 GetDynamicAsteroidID(const ID_String&);
    IMPORT Equipment* GetEquipment(u32);
    IMPORT Equipment* GetEquipmentByName(const ID_String&);
    IMPORT u32 GetEquipmentID(const ID_String&);
    IMPORT Explosion* GetExplosion(const ID_String&);
    IMPORT u32 GetId(ClassType, u32);
    IMPORT u32 GetIdCount(ClassType);
    IMPORT const MotorData* GetMotor(u32);
    IMPORT Ship* GetShip(u32);
    IMPORT Ship* GetShipByName(const ID_String&);
    IMPORT u32 GetShipID(const ID_String&);
    IMPORT Root* GetSimple(u32);
    IMPORT Root* GetSimpleByName(const ID_String&);
    IMPORT u32 GetSimpleID(const ID_String&);
    IMPORT Solar* GetSolar(u32);
    IMPORT Solar* GetSolarByName(const ID_String&);
    IMPORT u32 GetSolarID(const ID_String&);
    IMPORT u16 LargeIDToSmallID(u32);
    IMPORT bool Load(struct IFileSystem*, long*, int*);
    IMPORT bool Load(const char*, long*, int*);
    IMPORT int LoadAsteroids(const char*, struct IClObjFactory*);
    IMPORT int LoadEquipment(const char*, bool, IClObjFactory*);
    IMPORT bool LoadExplosion(INI_Reader&, bool);
    IMPORT int LoadShips(const char*, bool, IClObjFactory*);
    IMPORT int LoadSimples(const char*, bool, IClObjFactory*);
    IMPORT int LoadSolar(const char*, bool, IClObjFactory*);
    IMPORT u32 SmallIdToLargeID(u16);
} // namespace Archetype
