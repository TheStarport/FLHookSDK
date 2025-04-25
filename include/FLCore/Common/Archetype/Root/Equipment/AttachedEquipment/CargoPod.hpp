#pragma once

#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct CargoPod : AttachedEquipment
    {
        IMPORT CargoPod(const CargoPod&);
        IMPORT CargoPod(IClObj*);
        IMPORT virtual ~CargoPod();
        IMPORT CargoPod& operator=(const CargoPod&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;

        public:
        // no fields here
    };
}