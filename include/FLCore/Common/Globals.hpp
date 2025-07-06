#pragma once

#include "../FLCoreDefs.hpp"

#include "Archetype/Explosion.hpp"
#include "Archetype/Root/Equipment.hpp"
#include "Reputation.hpp"

#define MACRO_COMMA        ,
#define Ref(type, address) reinterpret_cast<FlMap<uint, type>&>(*(reinterpret_cast<FlMap<uint, type>*>(address)))

namespace GameData
{
    inline static auto& repGroups = Ref(Reputation::RepGroup, 0x64018EC);
    inline static auto& shieldResistMap = Ref(FlMap<uint MACRO_COMMA float>, 0x658A9C0);
    inline static auto& equipment = Ref(Archetype::Equipment*, 0x63FCAD4);
    inline static auto& explosions = Ref(Archetype::Explosion, 0x63FCF3C);
    inline static auto& motorData = Ref(Archetype::MotorData, 0x63FCA70);
    inline static auto& ships = Ref(Archetype::Ship*, 0x63FCAC0);
    inline static auto& asteroids = Ref(Archetype::Asteroid*, 0x63FCA98);
    inline static auto& dynamicAsteroids = Ref(Archetype::DynamicAsteroid*, 0x063FCA84);
    inline static auto& solars = Ref(Archetype::Solar*, 0x63FCAAC);
    inline static auto& allArchetypes = Ref(Archetype::Root*, 0x063FCAE8);

    // clang-format off
    inline static std::array<uint, 9> storyFactions = {
        MakeId("fc_ouk_grp"),
        MakeId("fc_q_grp"),
        MakeId("fc_uk_grp"),
        MakeId("fc_f_grp"),
        MakeId("fc_or_grp"),
        MakeId("fc_rn_grp"),
        MakeId("fc_kn_grp"),
        MakeId("fc_ln_grp"),
        MakeId("fc_n_grp")
    };
    // clang-format on
} // namespace GameData

#undef Ref
#undef MACRO_COMMA
