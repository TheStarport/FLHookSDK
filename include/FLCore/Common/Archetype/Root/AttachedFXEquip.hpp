#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct AttachedFXEquip : Root
    {
        IMPORT AttachedFXEquip(const AttachedFXEquip&);
        IMPORT AttachedFXEquip(IClObj*);
        IMPORT ~AttachedFXEquip() override;
        IMPORT AttachedFXEquip& operator=(const AttachedFXEquip&);
        IMPORT ClassType get_class_type() const override;

      public:
        // no fields here
    };
} // namespace Archetype
