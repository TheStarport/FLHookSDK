#pragma once

#include "../Equipment.hpp"

namespace Archetype
{
    struct Light : Equipment
    {
        IMPORT Light(const Light&);
        IMPORT Light(IClObj*);
        IMPORT ~Light() override;
        IMPORT Light& operator=(const Light&);
        IMPORT ClassType get_class_type() const override;
        IMPORT bool read(INI_Reader&) override;

        public:
        /* 28 */ bool alwaysOn;
        bool dockingLight;
    };
}