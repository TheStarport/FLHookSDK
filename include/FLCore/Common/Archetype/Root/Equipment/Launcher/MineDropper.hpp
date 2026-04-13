#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct MineDropper : Launcher
    {
        IMPORT MineDropper(const MineDropper&);
        IMPORT MineDropper(IClObj*);
        IMPORT ~MineDropper() override;
        IMPORT MineDropper& operator=(const MineDropper&);
        IMPORT ClassType get_class_type() const override;
        IMPORT HpAttachmentType get_hp_type() const override;

        public:
        // no fields here
    };
}