#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct InternalFXEquip : Equipment
    {
        IMPORT InternalFXEquip(const InternalFXEquip&);
        IMPORT InternalFXEquip(IClObj*);
        IMPORT virtual ~InternalFXEquip();
        IMPORT InternalFXEquip& operator=(const InternalFXEquip&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ char* useAnimation;
    };
}