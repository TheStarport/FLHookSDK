#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct DynamicAsteroid : Root
    {
        IMPORT DynamicAsteroid(const DynamicAsteroid&);
        IMPORT DynamicAsteroid(IClObj*);
        IMPORT ~DynamicAsteroid() override;
        IMPORT DynamicAsteroid& operator=(const DynamicAsteroid&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool read(INI_Reader&) override;

      public:
        // no fields
    };
} // namespace Archetype
