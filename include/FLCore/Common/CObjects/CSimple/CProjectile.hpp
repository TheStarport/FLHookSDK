#pragma once
#include "../../../FLCoreDefs.hpp"

#include "../CSimple.hpp"

namespace Archetype
{
    struct Projectile;
}
struct CProjectile : CSimple
{
    struct IMPORT CreateParms
    {
        // CreateParms();
        CreateParms& operator=(const CreateParms&);

        unsigned hash;
        Archetype::Projectile* archetype;
        f32 dunno2;
        f32 startHealth; // -1 = max health
        Vector position;
        Matrix orientation;
        Vector velocity;
        f32 dunno3[4]; // always 0
        unsigned owner;
    };

    IMPORT virtual ~CProjectile();                  // 56
    IMPORT virtual int update(f32, u32); // 80
    IMPORT virtual void init(const CreateParms&);   // 160
    IMPORT virtual void set_dead();                 // 164
    IMPORT virtual void expire_safe_time();         // 168

    IMPORT CProjectile(const CProjectile&);
    IMPORT CProjectile(Class);
    IMPORT const u32& get_owner() const;
    IMPORT bool is_alive() const;
    IMPORT bool is_owner_safe() const;
    IMPORT const Archetype::Projectile* projarch() const;

    unsigned ownerId;                 // 57
    f32 remainingLifetime;      // 58
    f32 remainingOwnerSafeTime; // 59
};