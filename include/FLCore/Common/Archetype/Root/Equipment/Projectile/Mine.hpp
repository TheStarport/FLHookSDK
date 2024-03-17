#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Mine : Projectile
    {
        IMPORT Mine(const Mine&);
        IMPORT Mine(IClObj*);
        IMPORT virtual ~Mine();
        IMPORT Mine& operator=(const Mine&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 32 */ float linearDrag;
        /* 33 */ float detonationDist;
        /* 34 */ float seekerDist;
        /* 35 */ float acceleration;
        /* 36 */ float topSpeed;
    };
}