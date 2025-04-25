#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct DynamicAsteroid : Root
    {
        IMPORT DynamicAsteroid(const DynamicAsteroid&);
        IMPORT DynamicAsteroid(IClObj*);
        IMPORT virtual ~DynamicAsteroid();
        IMPORT DynamicAsteroid& operator=(const DynamicAsteroid&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT virtual bool read(INI_Reader&);

        public:
        // no fields
    };
}