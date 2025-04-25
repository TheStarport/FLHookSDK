#pragma once
#include "FLCore/FLCoreDefs.hpp"

#include "FLCore/Common/Archetype/Root/Equipment/AttachedEquipment.hpp"

namespace Archetype
{
    struct ShieldGenerator final : public AttachedEquipment
    {
        struct IMPORT ShieldLink final
        {
            ShieldLink(const ShieldLink&);
            ShieldLink();
            ~ShieldLink();
            ShieldLink& operator=(const ShieldLink&);

            public:
            unsigned char data[0x18];
        };

        IMPORT ShieldGenerator(const ShieldGenerator&);
        IMPORT ShieldGenerator(IClObj*);
        IMPORT virtual ~ShieldGenerator();
        IMPORT ShieldGenerator& operator=(const ShieldGenerator&);
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT HpAttachmentType get_hp_type_by_index(int) const;
        IMPORT int get_number_of_hp_types() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);
        ClassType get_class_type() const override { return ClassType::ShieldGenerator; }

        public:
        /* 34 */ uint hpType;
        /* 35 */ uint shieldTypeId;
        /* 36 */ float regenerationRate;
        /* 37 */ float maxCapacity;
        /* 38 */ float constantPowerDraw;
        /* 39 */ float rebuildPowerDraw;
        /* 40 */ float offlineThreshold;
        float offlineRebuildTime;
        /* 41 */ uint hpShieldType[4]; // std6::vector?
    };
}