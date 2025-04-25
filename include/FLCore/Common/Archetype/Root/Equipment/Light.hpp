#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct Light : Equipment
    {
        IMPORT Light(const Light&);
        IMPORT Light(IClObj*);
        IMPORT virtual ~Light();
        IMPORT Light& operator=(const Light&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT bool read(INI_Reader&);

        public:
        /* 28 */ bool alwaysOn;
        bool dockingLight;
    };
}