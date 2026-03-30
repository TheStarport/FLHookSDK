#pragma once
#include "../../FLCoreDefs.hpp"

namespace Archetype
{
    struct MotorData
    {
        /*  0 */ unsigned vtable;
        /*  1 */ unsigned archId;
        /*  2 */ float delay;
        /*  3 */ float acceleration;
        /*  4 */ float lifetime;
    };
}