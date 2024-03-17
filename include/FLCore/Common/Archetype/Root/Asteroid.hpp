#pragma once
#include "../../../FLCoreDefs.hpp"

namespace Archetype
{
    struct Asteroid : Root
    {
        IMPORT Asteroid(const Asteroid&);
        IMPORT Asteroid(IClObj*);
        IMPORT virtual ~Asteroid();
        IMPORT Asteroid& operator=(const Asteroid&);
        IMPORT virtual ClassType get_class_type() const;
        IMPORT float get_detect_radius() const;
        IMPORT float get_offset_dist() const;
        IMPORT float get_recharge_time() const;
        IMPORT virtual bool read(INI_Reader&);

        public:
        /* 23 */ float detectRadius;
        /* 24 */ float explosionOffset;
        /* 25 */ float rechargeTime;
    };
}