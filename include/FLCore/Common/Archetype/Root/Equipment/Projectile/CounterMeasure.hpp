#pragma once
#include "FLCore/FLCoreDefs.hpp"
#include "../Projectile.hpp"
namespace Archetype
{
    struct CounterMeasure : Projectile
    {
            IMPORT CounterMeasure(const CounterMeasure&);
            IMPORT CounterMeasure(IClObj*);
            IMPORT ~CounterMeasure() override;
            IMPORT CounterMeasure& operator=(const CounterMeasure&);
            IMPORT ClassType get_class_type() const override;
            IMPORT HpAttachmentType get_hp_type() const override;
            IMPORT bool read(INI_Reader&) override;
            IMPORT void redefine(const Root&) override;

        public:
            /* 32 */ float linearDrag;
            /* 33 */ float range;
            /* 34 */ unsigned diversionPercentage;
    };
} // namespace Archetype
