#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Projectile : Equipment
    {
        IMPORT Projectile(const Projectile&);
        IMPORT Projectile(IClObj*);
        IMPORT virtual ~Projectile();
        IMPORT Projectile& operator=(const Projectile&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual Equipment* get_loot_appearance();
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float lifeTime;
        /* 29 */ float ownerSafeTime;
        /* 30 */ bool requiresAmmo;
        bool forceGunOri;
        /* 31 */ uint lootAppearanceId;
    };
}