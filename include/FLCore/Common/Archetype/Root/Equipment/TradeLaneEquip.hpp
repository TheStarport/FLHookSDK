#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct TradeLaneEquip : public Equipment
    {
        IMPORT TradeLaneEquip(const TradeLaneEquip&);
        IMPORT TradeLaneEquip(IClObj*);
        IMPORT virtual ~TradeLaneEquip();
        IMPORT TradeLaneEquip& operator=(const TradeLaneEquip&);
        IMPORT virtual ClassType get_class_type() const;

        public:
        // no new fields
    };
}