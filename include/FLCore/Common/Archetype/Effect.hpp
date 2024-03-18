#pragma once
#include "../../FLCoreDefs.hpp"

namespace Archetype
{
    struct Effect
    {
        Effect* prevEffect;
        Effect* nextEffect;
        uint archId;
        float lifetime; // -1.0 if skipped in config
    };
}