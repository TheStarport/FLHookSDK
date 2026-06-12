#pragma once

#include "../EqObj.hpp"

enum HpAttachmentType;
namespace Archetype
{
    struct Ship : EqObj
    {
        IMPORT Ship(const Ship&);
        IMPORT Ship(IClObj*);
        IMPORT ~Ship() override;
        IMPORT Ship& operator=(const Ship&);
        IMPORT static const int MAX_EXHAUST_NOZZLES;
        IMPORT ClassType get_class_type() const override;
        IMPORT const st6::vector<CacheString>* get_legal_hps(HpAttachmentType) const;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

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
        /* 64 */ f32 holdSize;
        /* 65 */ f32 linearDrag;
        /* 66 */ Vector angularDrag;
        /* 69 */ Vector steeringTorque;
        /* 72 */ f32 nudgeForce;
        /* 73 */ f32 strafeForce;
        /* 74 */ f32 strafePowerUsage;
        /* 75 */ f32 maxBankAngle;
        st6::vector<HpType> hardpoints;
        /* 80 */ unsigned maxNanobots;
        /* 81 */ unsigned maxShieldBats;
    };
} // namespace Archetype
