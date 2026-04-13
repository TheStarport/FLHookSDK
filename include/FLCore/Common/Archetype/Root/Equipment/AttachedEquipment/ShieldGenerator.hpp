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
        IMPORT ~ShieldGenerator() override;
        IMPORT ShieldGenerator& operator=(const ShieldGenerator&);
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT HpAttachmentType get_hp_type_by_index(int) const;
        IMPORT int get_number_of_hp_types() const;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;
        ClassType get_class_type() const override { return ClassType::ShieldGenerator; }

        public:
        /* 34 */ unsigned hpType;
        /* 35 */ unsigned shieldTypeId;
        /* 36 */ float regenerationRate;
        /* 37 */ float maxCapacity;
        /* 38 */ float constantPowerDraw;
        /* 39 */ float rebuildPowerDraw;
        /* 40 */ float offlineThreshold;
        float offlineRebuildTime;
        /* 41 */ unsigned hpShieldType[4]; // std6::vector?
    };
}