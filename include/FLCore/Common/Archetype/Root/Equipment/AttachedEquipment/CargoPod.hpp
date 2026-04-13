#pragma once

#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct CargoPod : AttachedEquipment
    {
        IMPORT CargoPod(const CargoPod&);
        IMPORT CargoPod(IClObj*);
        IMPORT ~CargoPod() override;
        IMPORT CargoPod& operator=(const CargoPod&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;

        public:
        // no fields here
    };
}