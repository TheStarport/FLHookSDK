#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct CounterMeasure : Projectile
    {
        IMPORT CounterMeasure(const CounterMeasure&);
        IMPORT CounterMeasure(IClObj*);
        IMPORT virtual ~CounterMeasure();
        IMPORT CounterMeasure& operator=(const CounterMeasure&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 32 */ float linearDrag;
        /* 33 */ float range;
        /* 34 */ float diversionPercentage;
    };
}