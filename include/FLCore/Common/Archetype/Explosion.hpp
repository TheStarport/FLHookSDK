#pragma once
#include "../../FLCoreDefs.hpp"

class IObjInspect;
namespace Archetype
{
    struct Effect;
    struct Explosion
    {
        IMPORT Explosion(const Explosion&);
        IMPORT Explosion(const ID_String&);
        IMPORT ~Explosion();
        IMPORT Explosion& operator=(const Explosion&);
        IMPORT bool read(INI_Reader&);
        IMPORT void reset();

        public:
        /*  0 */ Id id;
        /*  1 */ float radius;
        /*  2 */ float impulse;
        /*  3 */ float hullDamage;
        /*  4 */ float energyDamage;

        /*  5 */ uint processType;
        /*  6 */ float lifetime;
        /*  7 */ float lifetime2;
        /*  8 */ bool hasValidId;
        /*  9 */ Effect* effectPtr;
        /*  10 */ uint* dunno2;
        /*  11 */ float childNumPieces;
        /*  12 */ float debrisImpulse;
        /*  13 */ float innardsDebrisStartTime;
        /*  14 */ float innardsDebrisNum;
        /*  15 */ float innardsDebrisRadius;
        /*  16 */ bool hasValidId2;
        /*  17 */ uint* dunno4;
        /*  18 */ IObjInspect* innardsDebrisObject;
        /*  19 */ uint* dunno5;
        /*  20 */ bool hasValidId3;
        /*  21 */ uint* dunno6;
        /*  22 */ uint* dunno7;
        /*  23 */ uint* dunno8;
    };
}