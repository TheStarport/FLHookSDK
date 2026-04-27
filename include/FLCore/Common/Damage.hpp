#pragma once

#include "Enums.hpp"
#include "../FLCoreDefs.hpp"

namespace Archetype
{
    struct Munition;
    struct Explosion;
} // namespace Archetype

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
        u16 subObj;
        f32 health;
        SubObjFate fate;
};

struct MunitionImpactData
{
        unsigned attackerId;
        Archetype::Munition* munitionArch;
        u16 subObjId;
        Vector impactPosition;
};

struct ExplosionDamageEvent
{
        unsigned projectileId;
        unsigned attackerId;
        DamageCause dmgCause;
        Vector explosionPosition;
        Archetype::Explosion* explosionArchetype;
        unsigned dunno;
};

struct DamageList
{
        IMPORT DamageList(const DamageList&);
        IMPORT DamageList();
        IMPORT ~DamageList();
        IMPORT DamageList& operator=(const DamageList&);
        IMPORT static const char* DmgCauseToString(DamageCause);
        IMPORT void add_damage_entry(u16, f32, DamageEntry::SubObjFate);
        IMPORT DamageCause get_cause() const;
        IMPORT f32 get_hit_pts_left(u16) const;
        IMPORT u32 get_inflictor_id() const;
        IMPORT u32 get_inflictor_owner_player() const;
        IMPORT bool is_destroyed() const;
        IMPORT bool is_inflictor_a_player() const;
        IMPORT void set_cause(DamageCause);
        IMPORT void set_destroyed(bool);
        IMPORT void set_inflictor_id(u32);
        IMPORT void set_inflictor_owner_player(u32);

    public:
        st6::list<DamageEntry> damageEntries;
        bool isDestroyed;
        DamageCause damageCause;
        Id inflictorId;
        unsigned inflictorPlayerId;
        bool dunno;
};
