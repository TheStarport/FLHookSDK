#pragma once
#include "../../FLCoreDefs.hpp"

namespace PhySys
{
    struct RayHit
    {
        CObject* collision_object;
        Vector collision_position;
        Vector collision_velocity;
        uint dacomCRC32hash;
    };
}