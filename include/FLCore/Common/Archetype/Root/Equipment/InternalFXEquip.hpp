#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct InternalFXEquip : Equipment
    {
        IMPORT InternalFXEquip(const InternalFXEquip&);
        IMPORT InternalFXEquip(IClObj*);
        IMPORT ~InternalFXEquip() override;
        IMPORT InternalFXEquip& operator=(const InternalFXEquip&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ char* useAnimation;
    };
}