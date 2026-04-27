#pragma once
#include "../../FLCoreDefs.hpp"

namespace Archetype
{
    struct MotorData
    {
        /*  0 */ unsigned vtable;
        /*  1 */ unsigned archId;
        /*  2 */ f32 delay;
        /*  3 */ f32 acceleration;
        /*  4 */ f32 lifetime;
    };
}