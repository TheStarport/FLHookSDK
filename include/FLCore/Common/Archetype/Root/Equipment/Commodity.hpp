#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct Commodity : Equipment
    {
        IMPORT Commodity(const Commodity&);
        IMPORT Commodity(IClObj*);
        IMPORT virtual ~Commodity();
        IMPORT Commodity& operator=(const Commodity&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT float get_decay_per_second() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual Equipment* get_loot_appearance();
        IMPORT virtual CargoPod* get_pod_appearance();
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 28 */ float decayPerSecond;
        /* 29 */ uint lootAppearanceId;
        /* 30 */ uint podAppearanceId;
    };
}