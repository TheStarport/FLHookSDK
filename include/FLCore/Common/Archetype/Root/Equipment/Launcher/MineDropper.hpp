#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct MineDropper : Launcher
    {
        IMPORT MineDropper(const MineDropper&);
        IMPORT MineDropper(IClObj*);
        IMPORT virtual ~MineDropper();
        IMPORT MineDropper& operator=(const MineDropper&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual HpAttachmentType get_hp_type() const;

        public:
        // no fields here
    };
}