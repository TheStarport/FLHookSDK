#pragma once

#include "FLCore/Common/Archetype/Root.hpp"

namespace Archetype
{

    struct AttachedEquipment : Equipment
    {
        IMPORT AttachedEquipment(const AttachedEquipment&);
        IMPORT AttachedEquipment(IClObj*);
        IMPORT virtual ~AttachedEquipment();
        IMPORT AttachedEquipment& operator=(const AttachedEquipment&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool is_attached() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ uint separationExplosionId;
        /* 29 */ uint debrisTypeId;
        /* 30 */ float childImpulse;
        /* 31 */ float parentImpulse;
        /* 32 */ char* hpChild;
        /* 33 */ int toughness;
    };

}