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
        /*  1 */ f32 radius;
        /*  2 */ f32 impulse;
        /*  3 */ f32 hullDamage;
        /*  4 */ f32 energyDamage;

        /*  5 */ unsigned processType;
        /*  6 */ f32 lifetime;
        /*  7 */ f32 lifetime2;
        /*  8 */ bool hasValidId;
        /*  9 */ Effect* effectPtr;
        /*  10 */ unsigned* dunno2;
        /*  11 */ f32 childNumPieces;
        /*  12 */ f32 debrisImpulse;
        /*  13 */ f32 innardsDebrisStartTime;
        /*  14 */ f32 innardsDebrisNum;
        /*  15 */ f32 innardsDebrisRadius;
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