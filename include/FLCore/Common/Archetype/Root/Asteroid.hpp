#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct Asteroid : Root
    {
        IMPORT Asteroid(const Asteroid&);
        IMPORT Asteroid(IClObj*);
        IMPORT ~Asteroid() override;
        IMPORT Asteroid& operator=(const Asteroid&);
        IMPORT ClassType get_class_type() const override;
        IMPORT f32 get_detect_radius() const;
        IMPORT f32 get_offset_dist() const;
        IMPORT f32 get_recharge_time() const;
        IMPORT bool read(INI_Reader&) override;

      public:
        /* 23 */ f32 detectRadius;
        /* 24 */ f32 explosionOffset;
        /* 25 */ f32 rechargeTime;
    };
} // namespace Archetype
