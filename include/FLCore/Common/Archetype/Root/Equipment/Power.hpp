#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Power : Equipment
    {
        IMPORT Power(const Power&);
        IMPORT Power(IClObj*);
        IMPORT ~Power() override;
        IMPORT Power& operator=(const Power&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ float capacity;
        /* 29 */ float chargeRate;
        /* 30 */ float thrustCapacity;
        /* 31 */ float thrustChargeRate;
    };
}