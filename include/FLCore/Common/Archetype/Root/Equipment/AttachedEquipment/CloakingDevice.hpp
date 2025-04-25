#pragma once


#include "../AttachedEquipment.hpp"

namespace Archetype
{
    struct CloakingDevice : AttachedEquipment
    {
        IMPORT CloakingDevice(const CloakingDevice&);
        IMPORT CloakingDevice(IClObj*);
        IMPORT virtual ~CloakingDevice();
        IMPORT CloakingDevice& operator=(const CloakingDevice&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 34 */ float powerUsage;
        /* 35 */ float cloakInTime;
        /* 36 */ float cloakOutTime;
        /* 37 */ uint cloakInFxId;
        /* 38 */ uint cloakOutFxId;
    };
}