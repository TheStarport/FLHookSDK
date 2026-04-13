#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Projectile : Equipment
    {
        IMPORT Projectile(const Projectile&);
        IMPORT Projectile(IClObj*);
        IMPORT ~Projectile() override;
        IMPORT Projectile& operator=(const Projectile&);
        IMPORT ClassType get_class_type() const override;
        IMPORT Equipment* get_loot_appearance() override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ float lifeTime;
        /* 29 */ float ownerSafeTime;
        /* 30 */ bool requiresAmmo;
        bool forceGunOri;
        /* 31 */ unsigned lootAppearanceId;
    };
}