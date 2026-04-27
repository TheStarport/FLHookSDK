#pragma once
#include <FLCore/FLCoreDefs.hpp>
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
            /* 32 */ f32 hullDamage;
            /* 33 */ f32 energyDamage;
            /* 34 */ unsigned weaponTypeId;
            /* 35 */ unsigned motorId;
            /* 36 */ unsigned seeker; // 2 = lock, dumb = 1, ? = 0
            /* 37 */ f32 timeToLock;
            /* 38 */ f32 seekerRange;
            /* 39 */ f32 seekerFovDeg;
            /* 40 */ f32 maxAngularVelocity;
            /* 41 */ f32 detonationDist;
            /* 42 */ unsigned hpType;
            /* 43 */ bool cruiseDisruptor;
    };
} // namespace Archetype
