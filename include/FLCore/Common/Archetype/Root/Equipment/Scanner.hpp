#pragma once
#include <FLCore/FLCoreDefs.hpp>

namespace Archetype
{
    struct Scanner final : Equipment
    {
        IMPORT Scanner(const Scanner&);
        IMPORT Scanner(IClObj*);
        IMPORT ~Scanner() override;
        IMPORT Scanner& operator=(const Scanner&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;
        IMPORT bool read(INI_Reader&) override;
        IMPORT void redefine(const Root&) override;

        public:
        /* 28 */ f32 powerUsage;
        /* 29 */ f32 range;
        /* 30 */ f32 cargoScanRange;
    };
}