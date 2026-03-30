#pragma once

#include "../FLCoreDefs.hpp"

struct PathEntry
{
    Vector pos;
    Id objId;
    SystemId systemId;
};

template <unsigned count>
struct RequestPath
{
    unsigned repId;
    unsigned waypointCount;
    bool noPathFound = false;
    bool funny[3];
    PathEntry pathEntries[count];
};
