#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct AttachedEquipment : Equipment
    {
        IMPORT AttachedEquipment(const AttachedEquipment&);
        IMPORT AttachedEquipment(IClObj*);
        IMPORT ~AttachedEquipment() override;
        IMPORT AttachedEquipment& operator=(const AttachedEquipment&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool is_attached() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ unsigned separationExplosionId;
        /* 29 */ unsigned debrisTypeId;
        /* 30 */ float childImpulse;
        /* 31 */ float parentImpulse;
        /* 32 */ char* hpChild;
        /* 33 */ int toughness;
    };

}