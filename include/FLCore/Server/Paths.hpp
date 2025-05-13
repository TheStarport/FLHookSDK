#pragma once

#include "../FLCoreDefs.hpp"

struct PathEntry
{
    Vector pos;
    uint objId = 0;
    uint systemId;
};

template <uint count>
struct RequestPath
{
    int repId;
    uint waypointCount;
    bool noPathFound = false;
    bool funny[3];
    PathEntry pathEntries[count];
};
