#pragma once

#include "Enums.hpp"
#include "../FLCoreDefs.hpp"

namespace Archetype
{
    struct Explosion;
}

struct DamageEntry
{
    enum class SubObjFate
    {
        Alive = 0,
        Destroyed = 1,
        Debris = 2,
        Disappear = 3,
        Loot = 4
    };

    IMPORT DamageEntry();
    IMPORT DamageEntry& operator=(const DamageEntry&);
    IMPORT bool operator==(const DamageEntry&) const;
    IMPORT bool operator!=(const DamageEntry&) const;
    IMPORT bool operator<(const DamageEntry&) const;
    IMPORT bool operator>(const DamageEntry&) const;
    IMPORT static const char* FateToString(SubObjFate);

    public:
    ushort subObj;
    float health;
    SubObjFate fate;
};

struct MunitionImpactData
{
        uint attackerId;
        Archetype::Munition* munitionArch;
        ushort subObjId;
};

struct ExplosionDamageEvent
{
    uint projectileId;
    uint attackerId;
    DamageCause dmgCause;
    Vector explosionPosition;
    Archetype::Explosion* explosionArchetype;
    uint dunno;
};

struct DamageList
{
    IMPORT DamageList(const DamageList&);
    IMPORT DamageList();
    IMPORT ~DamageList();
    IMPORT DamageList& operator=(const DamageList&);
    IMPORT static const char* DmgCauseToString(DamageCause);
    IMPORT void add_damage_entry(unsigned short, float, DamageEntry::SubObjFate);
    IMPORT DamageCause get_cause() const;
    IMPORT float get_hit_pts_left(unsigned short) const;
    IMPORT unsigned int get_inflictor_id() const;
    IMPORT unsigned int get_inflictor_owner_player() const;
    IMPORT bool is_destroyed() const;
    IMPORT bool is_inflictor_a_player() const;
    IMPORT void set_cause(DamageCause);
    IMPORT void set_destroyed(bool);
    IMPORT void set_inflictor_id(unsigned int);
    IMPORT void set_inflictor_owner_player(unsigned int);

    public:
    st6::list<DamageEntry> damageEntries;
    bool isDestroyed;
    DamageCause damageCause;
    Id inflictorId;
    uint inflictorPlayerId;
    bool dunno;
};