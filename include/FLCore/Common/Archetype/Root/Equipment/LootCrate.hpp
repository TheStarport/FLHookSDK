#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct LootCrate : Equipment
    {
        IMPORT LootCrate(const LootCrate&);
        IMPORT LootCrate(IClObj*);
        IMPORT ~LootCrate() override;
        IMPORT LootCrate& operator=(const LootCrate&);
        IMPORT ClassType get_class_type() const override;

        public:
        // no fields here
    };
}