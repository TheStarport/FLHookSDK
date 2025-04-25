#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct LootCrate : Equipment
    {
        IMPORT LootCrate(const LootCrate&);
        IMPORT LootCrate(IClObj*);
        IMPORT virtual ~LootCrate();
        IMPORT LootCrate& operator=(const LootCrate&);
        IMPORT virtual ClassType get_class_type() const;

        public:
        // no fields here
    };
}