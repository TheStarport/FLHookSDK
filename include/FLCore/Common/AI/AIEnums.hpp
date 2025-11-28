#pragma once

namespace pub
{
    namespace AI
    {
        enum ScanResponse
        {

        };
        enum OP_RTYPE
        {

        };

        enum DirectivePriority
        {

        };

        struct DirectiveCallback;

        enum OpType
        {
            None = -1,
            NullOp = 0,
            Buzz = 1,
            Goto = 2,
            Trail = 3,
            Flee = 4,
            Evade = 5,
            Idle = 6,
            Dock = 7,
            Launch = 8,
            InstantTradeLane = 9,
            Formation = 10,
            LargeShipMove = 11,
            Cruise = 12,
            Strafe = 13,
            Guide = 14,
            Face = 15,
            Loot = 16,
            Follow = 17,
            DrasticEvade = 18,
            FreeFlight = 19,
            Delay = 20,
        };
    }
}