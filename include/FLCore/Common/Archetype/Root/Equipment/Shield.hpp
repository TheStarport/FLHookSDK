#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct Shield final : Equipment
    {
        IMPORT Shield(const Shield&);
        IMPORT Shield(IClObj*);
        IMPORT virtual ~Shield();
        IMPORT Shield& operator=(const Shield&);
        IMPORT virtual ClassType get_class_type() const;

        public:
        /* 28 */ char* dunno1;
        /* 29 */ char* dunno2;
        /* 30 */ uint dunno3;
        /* 31 */ uint dunno4;
        /* 32 */ char* dunno5;
        /* 33 */ uint dunno6;
    };
}