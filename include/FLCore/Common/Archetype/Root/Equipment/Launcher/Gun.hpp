#pragma once

#include "../AttachedEquipment/Launcher.hpp"

namespace Archetype
{
    struct Gun : Launcher
    {
        IMPORT Gun(const Gun&);
        IMPORT Gun(IClObj*);
        IMPORT ~Gun() override;
        IMPORT Gun& operator=(const Gun&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT HpAttachmentType get_hp_type_by_index(int) const;
        IMPORT float get_munition_range() const;
        IMPORT int get_number_of_hp_types() const;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 40 */ float dispersionAngle;
        /* 41 */ float turnRate;
        /* 42 */ float gunAzimuth[2];
        /* 44 */ float gunElevation[2];
        /* 46 */ bool useGunAzimuth;
        bool useGunElevation;
        bool autoTurret;
        /* 47 */ unsigned hpTypes[4]; // st6::vector?
    };
}