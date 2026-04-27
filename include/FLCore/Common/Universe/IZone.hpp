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
        struct FactionSpawn
        {
            unsigned faction; // Faction Id, obtainable with e.g. pub::Reputation::GetReputationGroup()
            f32 chance; // Spawn chance
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

        void* vtable;
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
        f32 unused2;         // -1
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
}