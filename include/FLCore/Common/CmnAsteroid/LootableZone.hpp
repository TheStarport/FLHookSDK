#pragma once

#include "../../FLCoreDefs.hpp"

namespace CmnAsteroid
{
    struct LootableZone
    {
        Id asteroidLootContainer; // not used
        Id dynamicLootContainer;
        Id asteroidLootCommodity; // not used
        Id dynamicLootCommodity;
        Id asteroidLootCount1; // not used
        Id asteroidLootCount2; // not used
        Id dynamicLootCount1;  // min 1
        Id dynamicLootCount2;
        Id asteroidLootDifficulty; // not used
        Id dynamicLootDifficulty;  // default 1, maximum 100
    };
}