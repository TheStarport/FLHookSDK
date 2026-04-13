#pragma once
#include "FLCore/FLCoreDefs.hpp"
#include "../Projectile.hpp"
namespace Archetype
{
    struct Mine : Projectile
    {
            IMPORT Mine(const Mine&);
            IMPORT Mine(IClObj*);
            IMPORT ~Mine() override;
            IMPORT Mine& operator=(const Mine&);
            IMPORT ClassType get_class_type() const override;
            IMPORT HpAttachmentType get_hp_type() const override;
            IMPORT bool read(INI_Reader&) override;
            IMPORT void redefine(const Root&) override;

        public:
            /* 32 */ float linearDrag;
            /* 33 */ float detonationDist;
            /* 34 */ float seekerDist;
            /* 35 */ float acceleration;
            /* 36 */ float topSpeed;
    };
} // namespace Archetype
