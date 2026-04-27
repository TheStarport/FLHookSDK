#pragma once
#include <FLCore/FLCoreDefs.hpp>
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
            /* 32 */ f32 linearDrag;
            /* 33 */ f32 detonationDist;
            /* 34 */ f32 seekerDist;
            /* 35 */ f32 acceleration;
            /* 36 */ f32 topSpeed;
    };
} // namespace Archetype
