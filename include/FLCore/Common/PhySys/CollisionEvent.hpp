#pragma once

#include "../../FLCoreDefs.hpp"

namespace PhySys
{
    struct CollisionEvent
    {
        CObject* a;
        CObject* b;
        uint dunno1[2];
        Vector position;
        Vector normal;
        Vector velocity;
    };
}