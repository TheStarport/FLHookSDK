#pragma once
#include "FLCore/FLCoreDefs.hpp"
#include "../Projectile.hpp"
namespace Archetype
{
    struct Munition : Projectile
    {
            IMPORT Munition(const Munition&);
            IMPORT Munition(IClObj*);
            IMPORT ~Munition() override;
            IMPORT Munition& operator=(const Munition&);
            IMPORT static void FreeBeamArchIdx();
            IMPORT static void LoadBeamArchIdx();
            IMPORT HpAttachmentType get_hp_type() const override;
            IMPORT bool is_guided() const;
            IMPORT bool load() override;
            IMPORT bool read(INI_Reader&) override;
            IMPORT void redefine(const Root&) override;
            ClassType get_class_type() const override { return ClassType::Munition; }

        protected:
            static long beamArchIndex;
            IMPORT void free_resources() override;

        public:
            /* 32 */ float hullDamage;
            /* 33 */ float energyDamage;
            /* 34 */ unsigned weaponTypeId;
            /* 35 */ unsigned motorId;
            /* 36 */ unsigned seeker; // 2 = lock, dumb = 1, ? = 0
            /* 37 */ float timeToLock;
            /* 38 */ float seekerRange;
            /* 39 */ float seekerFovDeg;
            /* 40 */ float maxAngularVelocity;
            /* 41 */ float detonationDist;
            /* 42 */ unsigned hpType;
            /* 43 */ bool cruiseDisruptor;
    };
} // namespace Archetype
