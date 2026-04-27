#pragma once

#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct Launcher : public AttachedEquipment
    {
        IMPORT Launcher(const Launcher&);
        IMPORT Launcher(IClObj*);
        IMPORT ~Launcher() override;
        IMPORT Launcher& operator=(const Launcher&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 34 */ f32 damagePerFire;
        /* 35 */ f32 powerUsage;
        /* 36 */ f32 refireDelay;
        /* 37 */ f32 muzzleVelocity;
        /* 38 */ Id projectileArchId;
        /* 39 */ char* useAnimation;
    };
}