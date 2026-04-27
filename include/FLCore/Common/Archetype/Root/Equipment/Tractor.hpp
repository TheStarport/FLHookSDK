#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct Tractor : public Equipment
    {
        IMPORT Tractor(const Tractor&);
        IMPORT Tractor(IClObj*);
        IMPORT ~Tractor() override;
        IMPORT Tractor& operator=(const Tractor&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ f32 maxLength;
        /* 29 */ f32 reachSpeed;
    };
}