#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct CounterMeasureDropper : Launcher
    {
        IMPORT CounterMeasureDropper(const CounterMeasureDropper&);
        IMPORT CounterMeasureDropper(IClObj*);
        IMPORT virtual ~CounterMeasureDropper();
        IMPORT CounterMeasureDropper& operator=(const CounterMeasureDropper&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;
        IMPORT virtual bool read(INI_Reader&);
        IMPORT virtual void redefine(const Root&);

        public:
        /* 40 */ float range;
    };
}