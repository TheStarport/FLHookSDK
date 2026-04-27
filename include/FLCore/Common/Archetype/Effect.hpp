#pragma once
#include "../../FLCoreDefs.hpp"

namespace Archetype
{
    struct Effect
    {
        Effect* prevEffect;
        Effect* nextEffect;
        unsigned archId;
        f32 lifetime; // -1.0 if skipped in config
    };
}