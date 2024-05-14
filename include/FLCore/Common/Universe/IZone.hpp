#pragma once
#include "../../FLCoreDefs.hpp"
#include "../Strings.hpp"

namespace Universe
{
    struct IZone
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
}