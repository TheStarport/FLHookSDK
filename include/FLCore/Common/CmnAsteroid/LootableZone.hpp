#pragma once
#include "FLCore/FLCoreDefs.hpp"

namespace CmnAsteroid
{
    struct LootableZone
    {
        ulong asteroidLootContainer; // not used
        ulong dynamicLootContainer;
        ulong asteroidLootCommodity; // not used
        ulong dynamicLootCommodity;
        ulong asteroidLootCount1; // not used
        ulong asteroidLootCount2; // not used
        ulong dynamicLootCount1;  // min 1
        ulong dynamicLootCount2;
        ulong asteroidLootDifficulty; // not used
        ulong dynamicLootDifficulty;  // default 1, maximum 100
    };
}