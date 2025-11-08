#pragma once

#include "../../FLCoreDefs.hpp"
#include "FLCore/Common/Strings.hpp"

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
    IMPORT const MotorData* GetMotor(unsigned int);
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
} // namespace Archetype
