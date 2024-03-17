#pragma once
#include "FLCore/FLCoreDefs.hpp"

struct CGuided : public CProjectile
{
    public:
    struct IMPORT CreateParms
    {
        CreateParms();
        CreateParms& operator=(const CreateParms&);

        public:
        unsigned char data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CGuided();
    IMPORT virtual int update(float, unsigned int);
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void expire_safe_time();

    IMPORT static bool seeker_can_see(const Vector&, const Vector&, const Vector&, const Archetype::Munition*);

    IMPORT CGuided(const CGuided&);
    IMPORT CGuided(Class);
    IMPORT const Archetype::MotorData* get_motor_arch() const;
    IMPORT unsigned short get_sub_target() const;
    IMPORT IObjRW* get_target() const;
    IMPORT void init(const CreateParms&);
    IMPORT bool motor_on() const;
    IMPORT bool seeker_can_see(const Vector&) const;
    IMPORT void set_sub_target(unsigned short);
    IMPORT void set_target(IObjRW*);

    BaseWatcher targetBaseWatcher;   // 60
    ushort targetSId;                // 62
    Archetype::MotorData* mototData; // 63
    float lifetime;                  // 64
};