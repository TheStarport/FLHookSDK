#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Munition : Projectile
    {
        IMPORT Munition(const Munition&);
        IMPORT Munition(IClObj*);
        IMPORT virtual ~Munition();
        IMPORT Munition& operator=(const Munition&);
        IMPORT static void FreeBeamArchIdx();
        IMPORT static void LoadBeamArchIdx();
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT bool is_guided() const;
        IMPORT virtual bool load();
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);
        ClassType get_class_type() const override { return ClassType::Munition; }

        protected:
        static long beamArchIndex;
        IMPORT virtual void free_resources();

        public:
        /* 32 */ float hullDamage;
        /* 33 */ float energyDamage;
        /* 34 */ uint weaponTypeId;
        /* 35 */ uint motorId;
        /* 36 */ uint seeker; // 2 = lock, dumb = 1, ? = 0
        /* 37 */ float timeToLock;
        /* 38 */ float seekerRange;
        /* 39 */ float seekerFovDeg;
        /* 40 */ float maxAngularVelocity;
        /* 41 */ float detonationDist;
        /* 42 */ uint hpType;
        /* 43 */ bool cruiseDisruptor;
    };
}