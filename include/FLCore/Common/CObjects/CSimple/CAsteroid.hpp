#pragma once
#include "../../../FLCoreDefs.hpp"

namespace CmnAsteroid
{
    class CAsteroidField;
}
namespace Archetype
{
    class Asteroid;
}

struct CAsteroid : CSimple
{
    struct IMPORT CreateParms
    {
        CreateParms();
        CreateParms& operator=(const CreateParms&);

        u8 data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CAsteroid();
    IMPORT virtual Vector get_velocity() const;
    IMPORT virtual int update(f32, u32);

    IMPORT const Archetype::Asteroid* asteroidarch() const;
    IMPORT ulong get_asteroid_id();
    IMPORT const CmnAsteroid::CAsteroidField* get_owner_field();
    IMPORT void init(const CreateParms&);
    IMPORT bool is_instant_kill();
    IMPORT bool is_mine();
    IMPORT void set_system(u32);
    IMPORT CAsteroid(const CAsteroid&);
    IMPORT CAsteroid();

    protected:
    IMPORT virtual void init_physics(const Vector&, const Vector&);

    public:
    u8 data[OBJECT_DATA_SIZE];
};