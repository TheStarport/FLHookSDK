#pragma once

#include "../EqObj.hpp"

namespace Archetype
{
    struct Ship : EqObj
    {
        IMPORT Ship(const Ship&);
        IMPORT Ship(IClObj*);
        IMPORT virtual ~Ship();
        IMPORT Ship& operator=(const Ship&);
        IMPORT static const int MAX_EXHAUST_NOZZLES;
        IMPORT virtual ClassType get_class_type() const;
        IMPORT const st6::vector<CacheString>* get_legal_hps(HpAttachmentType) const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        struct HpType
        {
            HpAttachmentType type;
            st6::vector<CacheString> hp;
        };

        /* 37 */ unsigned dunno12;
        /* 38 */ size_t msgidprefix_len;
        /* 39 */ char msgidprefix_str[64];
        /* 55 */ char* bayDoorAnim;
        /* 56 */ char* hpBaySurface;
        /* 57 */ char* hpBayExternal;
        /* 58 */ char* hpTractorSource;
        /* 59 */ unsigned idsInfo1;
        /* 60 */ unsigned idsInfo2;
        /* 61 */ unsigned idsInfo3;
        /* 62 */ unsigned shipClass;
        /* 63 */ unsigned numExhaustNozzles;
        /* 64 */ float holdSize;
        /* 65 */ float linearDrag;
        /* 66 */ Vector angularDrag;
        /* 69 */ Vector steeringTorque;
        /* 72 */ float nudgeForce;
        /* 73 */ float strafeForce;
        /* 74 */ float strafePowerUsage;
        /* 75 */ float maxBankAngle;
        st6::vector<HpType> hardpoints;
        /* 80 */ unsigned maxNanobots;
        /* 81 */ unsigned maxShieldBats;
    };
}