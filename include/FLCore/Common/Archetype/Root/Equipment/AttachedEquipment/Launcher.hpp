#pragma once

#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct Launcher : public AttachedEquipment
    {
        IMPORT Launcher(const Launcher&);
        IMPORT Launcher(IClObj*);
        IMPORT virtual ~Launcher();
        IMPORT Launcher& operator=(const Launcher&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 34 */ float damagePerFire;
        /* 35 */ float powerUsage;
        /* 36 */ float refireDelay;
        /* 37 */ float muzzleVelocity;
        /* 38 */ Id projectileArchId;
        /* 39 */ char* useAnimation;
    };
}