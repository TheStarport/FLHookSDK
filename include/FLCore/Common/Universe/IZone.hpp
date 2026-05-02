#pragma once
#include "../../FLCoreDefs.hpp"
#include "../Strings.hpp"

namespace CmnAsteroid
{
    struct LootableZone;
}

namespace Universe
{
    struct IZone
    {
        virtual void dunno0();
        virtual void dunno4();
        virtual void dunno8();
        virtual void dunnoC();
        virtual void dunno10();
        virtual void dunno14();
        virtual void dunno18();
        virtual void dunno1C();
        virtual void dunno20();
        virtual void dunno24();
        virtual void dunno28();
        virtual void dunno2C();
        virtual void dunno30();
        virtual bool is_within_zone(const Vector& pos, float objRadius) const;
        virtual bool is_within_zone2D(const Vector& pos, float objRadius) const;
        virtual void dunno3C();
        virtual void dunno40();
        virtual void dunno44();
        virtual float get_immersion(const Vector& pos) const;
        virtual void dunno4C();
        virtual void dunno50();
        virtual void dunno54();
        virtual void dunno58();
        virtual void dunno5C();
        virtual void dunno60();
        virtual void dunno64();
        virtual void dunno68();
        virtual void dunno6C();
        virtual void dunno70();
        virtual void dunno74();
        virtual void dunno78();
        virtual void dunno7C();
        virtual void dunno80();
        virtual void dunno84();
        virtual void dunno88();
        virtual void dunno8C();
        virtual void dunno90();

        struct FactionSpawn
        {
            unsigned faction; // Faction Id, obtainable with e.g. pub::Reputation::GetReputationGroup()
            f32 chance;       // Spawn chance
        };

        enum ShapeType
        {
            Sphere = 1,
            Ellipsoid,
            Box,
            Cylinder,
            Ring,
            Mesh
        };

        Id zoneId;
        SystemId systemId;
        Matrix orientation;
        Vector position;
        ShapeType shapeType;
        unsigned propertyFlags;
        Vector size;
        long mesh;
        f32 edgeFraction;
        long unused1; // -1
        f32 dragModifier;
        f32 damage;
        f32 interference;
        f32 unused2;           // -1
        ID_String music;       // ID_String
        CacheString spaceDust; // CacheString
        int spaceDustMaxParticles;
        Vector fogColor; // an RGB type
        CmnAsteroid::LootableZone* lootableZone;
        bool pathLabel;
        unsigned countMaxFaction;
        st6::list<FactionSpawn> factionSpawns; // st6::weighted_vector<FactionSpawn> factionSpawns;

        BYTE visit;
        unsigned idsName;
        unsigned idsInfo;
        unsigned iDunno5[2];
    };
} // namespace Universe
