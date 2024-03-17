#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct RepairDroid : Equipment
    {
        IMPORT RepairDroid(const RepairDroid&);
        IMPORT RepairDroid(IClObj*);
        IMPORT virtual ~RepairDroid();
        IMPORT RepairDroid& operator=(const RepairDroid&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float repairRate;
    };
}

struct ShieldBattery : Equipment
{
    IMPORT ShieldBattery(const ShieldBattery&);
    IMPORT ShieldBattery(IClObj*);
    IMPORT virtual ~ShieldBattery();
    IMPORT ShieldBattery& operator=(const ShieldBattery&);
    IMPORT virtual ClassType get_class_type() const;
    IMPORT virtual HpAttachmentType get_hp_type() const;
    IMPORT virtual Equipment* get_loot_appearance();
    IMPORT virtual bool read(INI_Reader&);

    public:
    /* 28 */ uint lootAppearanceId;
};

struct IMPORT RepairKit final : ShieldBattery
{
    RepairKit(const RepairKit&);
    RepairKit(IClObj*);
    virtual ~RepairKit();
    RepairKit& operator=(const RepairKit&);
    virtual ClassType get_class_type() const;
    virtual HpAttachmentType get_hp_type() const;
    virtual Equipment* get_loot_appearance();
    virtual bool read(INI_Reader&);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};