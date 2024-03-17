#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct Gun : Launcher
    {
        IMPORT Gun(const Gun&);
        IMPORT Gun(IClObj*);
        IMPORT virtual ~Gun();
        IMPORT Gun& operator=(const Gun&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT HpAttachmentType get_hp_type_by_index(int) const;
        IMPORT float get_munition_range() const;
        IMPORT int get_number_of_hp_types() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 40 */ float dispersionAngle;
        /* 41 */ float turnRate;
        /* 42 */ float gunAzimuth[2];
        /* 44 */ float gunElevation[2];
        /* 46 */ bool useGunAzimuth;
        bool useGunElevation;
        bool autoTurret;
        /* 47 */ uint hpTypes[4]; // st6::vector?
    };
}