#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Power : Equipment
    {
        IMPORT Power(const Power&);
        IMPORT Power(IClObj*);
        IMPORT virtual ~Power();
        IMPORT Power& operator=(const Power&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float capacity;
        /* 29 */ float chargeRate;
        /* 30 */ float thrustCapacity;
        /* 31 */ float thrustChargeRate;
    };
}