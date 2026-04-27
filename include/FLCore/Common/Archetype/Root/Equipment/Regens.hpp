#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct RepairDroid : Equipment
    {
        IMPORT RepairDroid(const RepairDroid&);
        IMPORT RepairDroid(IClObj*);
        IMPORT ~RepairDroid() override;
        IMPORT RepairDroid& operator=(const RepairDroid&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ f32 repairRate;
    };

    struct ShieldBattery : Equipment
    {
        IMPORT ShieldBattery(const ShieldBattery&);
        IMPORT ShieldBattery(IClObj*);
        IMPORT ~ShieldBattery() override;
        IMPORT ShieldBattery& operator=(const ShieldBattery&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT Equipment* get_loot_appearance() override;
        IMPORT bool read(INI_Reader&) override;

        public:
        /* 28 */ unsigned lootAppearanceId;
    };

    struct IMPORT RepairKit final : ShieldBattery
    {
        RepairKit(const RepairKit&);
        RepairKit(IClObj*);
        ~RepairKit() override;
        RepairKit& operator=(const RepairKit&);
        ClassType get_class_type() const override;
        HpAttachmentType get_hp_type() const override;
        Equipment* get_loot_appearance() override;
        bool read(INI_Reader&) override;

        public:
        u8 data[OBJECT_DATA_SIZE];
    };
}