#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct Commodity : Equipment
    {
        IMPORT Commodity(const Commodity&);
        IMPORT Commodity(IClObj*);
        IMPORT ~Commodity() override;
        IMPORT Commodity& operator=(const Commodity&);
        IMPORT ClassType get_class_type() const override;
        IMPORT f32 get_decay_per_second() const;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT Equipment* get_loot_appearance() override;
        IMPORT CargoPod* get_pod_appearance() override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ f32 decayPerSecond;
        /* 29 */ unsigned lootAppearanceId;
        /* 30 */ unsigned podAppearanceId;
    };
}