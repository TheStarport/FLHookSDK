#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct CounterMeasureDropper : Launcher
    {
        IMPORT CounterMeasureDropper(const CounterMeasureDropper&);
        IMPORT CounterMeasureDropper(IClObj*);
        IMPORT ~CounterMeasureDropper() override;
        IMPORT CounterMeasureDropper& operator=(const CounterMeasureDropper&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 40 */ f32 range;
    };
}