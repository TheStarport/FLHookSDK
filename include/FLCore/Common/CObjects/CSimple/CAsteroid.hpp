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

        unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CAsteroid();
    IMPORT virtual Vector get_velocity() const;
    IMPORT virtual int update(float, unsigned int);

    IMPORT const Archetype::Asteroid* asteroidarch() const;
    IMPORT unsigned long get_asteroid_id();
    IMPORT const CmnAsteroid::CAsteroidField* get_owner_field();
    IMPORT void init(const CreateParms&);
    IMPORT bool is_instant_kill();
    IMPORT bool is_mine();
    IMPORT void set_system(unsigned int);
    IMPORT CAsteroid(const CAsteroid&);
    IMPORT CAsteroid();

    protected:
    IMPORT virtual void init_physics(const Vector&, const Vector&);

    public:
    unsigned char data[OBJECT_DATA_SIZE];
};