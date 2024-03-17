#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct AttachedFXEquip : Root
    {
        IMPORT AttachedFXEquip(const AttachedFXEquip&);
        IMPORT AttachedFXEquip(IClObj*);
        IMPORT virtual ~AttachedFXEquip();
        IMPORT AttachedFXEquip& operator=(const AttachedFXEquip&);
        IMPORT virtual ClassType get_class_type() const;

        public:
        // no fields here
    };
}