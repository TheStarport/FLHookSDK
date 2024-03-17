#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace Archetype
{
    struct MotorData
    {
        /*  0 */ uint vtable;
        /*  1 */ uint archId;
        /*  2 */ float delay;
        /*  3 */ float acceleration;
        /*  4 */ float lifetime;
    };
}