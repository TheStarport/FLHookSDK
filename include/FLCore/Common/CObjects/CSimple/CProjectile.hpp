#pragma once
#include "../../../FLCoreDefs.hpp"

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

        uint hash;
        Archetype::Projectile* archetype;
        float dunno2;
        float startHealth; // -1 = max health
        Vector position;
        Matrix orientation;
        Vector velocity;
        float dunno3[4]; // always 0
        uint owner;
    };

    IMPORT virtual ~CProjectile();                  // 56
    IMPORT virtual int update(float, unsigned int); // 80
    IMPORT virtual void init(const CreateParms&);   // 160
    IMPORT virtual void set_dead();                 // 164
    IMPORT virtual void expire_safe_time();         // 168

    IMPORT CProjectile(const CProjectile&);
    IMPORT CProjectile(Class);
    IMPORT const unsigned int& get_owner() const;
    IMPORT bool is_alive() const;
    IMPORT bool is_owner_safe() const;
    IMPORT const Archetype::Projectile* projarch() const;

    uint ownerId;                 // 57
    float remainingLifetime;      // 58
    float remainingOwnerSafeTime; // 59
};