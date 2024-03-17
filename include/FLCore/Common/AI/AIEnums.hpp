#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace pub
{
    namespace AI
    {
        enum ScanResponse;
        enum OP_RTYPE;
        enum DirectivePriority;
        struct DirectiveCallback;

        enum OpType
        {
            None = -1,
            NullOp = 0,
            Buzz = 1,
            Dunno = 2,
            Goto = 3,
            Follow = 4,
            Trail = 5,
            Strafe = 6,
            Face = 7,
            Ram = 8,
            Tractor = 9,
            Evade = 10,
            DrasticEvade = 11,
            Delay = 12,
            Dock = 13,
            Launch = 14,
            Tradelane = 15,
            InstanceTradeLane = 16,
            Guide = 17,
            WaitForShip = 18,
            FreeFlight = 19,
            Idle = 20,
            Cancel = 21,
        };
    }
}