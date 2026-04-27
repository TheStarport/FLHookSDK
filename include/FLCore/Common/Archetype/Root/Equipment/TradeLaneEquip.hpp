#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct TradeLaneEquip : public Equipment
    {
        IMPORT TradeLaneEquip(const TradeLaneEquip&);
        IMPORT TradeLaneEquip(IClObj*);
        IMPORT ~TradeLaneEquip() override;
        IMPORT TradeLaneEquip& operator=(const TradeLaneEquip&);
        IMPORT ClassType get_class_type() const override;

        public:
        // no new fields
    };
}