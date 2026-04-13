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
        /* 34 */ float damagePerFire;
        /* 35 */ float powerUsage;
        /* 36 */ float refireDelay;
        /* 37 */ float muzzleVelocity;
        /* 38 */ Id projectileArchId;
        /* 39 */ char* useAnimation;
    };
}