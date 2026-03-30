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
            float chance; // Spawn chance
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
        float edgeFraction;
        long unused1; // -1
        float dragModifier;
        float damage;
        float interference;
        float unused2;         // -1
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