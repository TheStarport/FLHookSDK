#pragma once

#include "../../FLCoreDefs.hpp"

namespace PhySys
{
    struct CollisionEvent
    {
        CObject* a;
        CObject* b;
        unsigned dunno1[2];
        Vector position;
        Vector normal;
        Vector velocity;
    };
}