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

    IMPORT ~CAsteroid() override;
    IMPORT Vector get_velocity() const override;
    IMPORT int update(f32, u32) override;

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
    IMPORT void init_physics(const Vector&, const Vector&) override;

  public:
    u8 data[OBJECT_DATA_SIZE];
};
