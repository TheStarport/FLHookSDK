#pragma once
#include "FLCore/FLCoreDefs.hpp"

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

        /* 37 */ uint dunno12[18];
        /* 55 */ char* bayDoorAnim;
        /* 56 */ char* hpBaySurface;
        /* 57 */ char* hpBayExternal;
        /* 58 */ char* hpTractorSource;
        /* 59 */ uint idsInfo1;
        /* 60 */ uint idsInfo2;
        /* 61 */ uint idsInfo3;
        /* 62 */ uint shipClass;
        /* 63 */ uint numExhaustNozzles;
        /* 64 */ float holdSize;
        /* 65 */ float linearDrag;
        /* 66 */ Vector angularDrag;
        /* 69 */ Vector steeringTorque;
        /* 72 */ float nudgeForce;
        /* 73 */ float strafeForce;
        /* 74 */ float strafePowerUsage;
        /* 75 */ float maxBankAngle;
        st6::vector<HpType> hardpoints;
        /* 80 */ uint maxNanobots;
        /* 81 */ uint maxShieldBats;
    };
}