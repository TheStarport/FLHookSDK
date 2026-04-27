#pragma once


#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct CloakingDevice : AttachedEquipment
    {
        IMPORT CloakingDevice(const CloakingDevice&);
        IMPORT CloakingDevice(IClObj*);
        IMPORT ~CloakingDevice() override;
        IMPORT CloakingDevice& operator=(const CloakingDevice&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 34 */ f32 powerUsage;
        /* 35 */ f32 cloakInTime;
        /* 36 */ f32 cloakOutTime;
        /* 37 */ unsigned cloakInFxId;
        /* 38 */ unsigned cloakOutFxId;
    };
}