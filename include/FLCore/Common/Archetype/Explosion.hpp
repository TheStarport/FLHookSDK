#pragma once
#include "../../FLCoreDefs.hpp"

struct IObjInspect;
struct ID_String;
class INI_Reader;

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

        /*  5 */ unsigned processType;
        /*  6 */ float lifetime;
        /*  7 */ float lifetime2;
        /*  8 */ bool hasValidId;
        /*  9 */ Effect* effectPtr;
        /*  10 */ unsigned* dunno2;
        /*  11 */ float childNumPieces;
        /*  12 */ float debrisImpulse;
        /*  13 */ float innardsDebrisStartTime;
        /*  14 */ float innardsDebrisNum;
        /*  15 */ float innardsDebrisRadius;
        /*  16 */ bool hasValidId2;
        /*  17 */ unsigned* dunno4;
        /*  18 */ IObjInspect* innardsDebrisObject;
        /*  19 */ unsigned* dunno5;
        /*  20 */ bool hasValidId3;
        /*  21 */ unsigned* dunno6;
        /*  22 */ unsigned* dunno7;
        /*  23 */ unsigned* dunno8;
    };
}