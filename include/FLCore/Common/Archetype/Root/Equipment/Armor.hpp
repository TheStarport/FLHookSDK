#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Armor : Equipment
    {
        IMPORT Armor(const Armor&);
        IMPORT Armor(IClObj*);
        IMPORT virtual ~Armor();
        IMPORT Armor& operator=(const Armor&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float hitPointsScale;
    };
}