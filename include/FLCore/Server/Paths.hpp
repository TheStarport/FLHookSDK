#pragma once

#include "../FLCoreDefs.hpp"

struct PathEntry
{
    Vector pos;
    Id objId;
    SystemId systemId;
};

template <uint count>
struct RequestPath
{
    uint repId;
    uint waypointCount;
    bool noPathFound = false;
    bool funny[3];
    PathEntry pathEntries[count];
};
