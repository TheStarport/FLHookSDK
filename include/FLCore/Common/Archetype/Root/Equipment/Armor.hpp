#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Armor : Equipment
    {
        IMPORT Armor(const Armor&);
        IMPORT Armor(IClObj*);
        IMPORT ~Armor() override;
        IMPORT Armor& operator=(const Armor&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ float hitPointsScale;
    };
}