#pragma once

#include "../CProjectile.hpp"
#include "../../../Watchable.hpp"

namespace Archetype
{
    struct Munition;
    struct MotorData;
}

struct IObjRW;
struct CGuided : public CProjectile
{
    public:
    struct IMPORT CreateParms
    {
        CreateParms();
        CreateParms& operator=(const CreateParms&);

        public:
        u8 data[OBJECT_DATA_SIZE];
    };

    IMPORT virtual ~CGuided();
    IMPORT virtual int update(f32, u32);
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void expire_safe_time();

    IMPORT static bool seeker_can_see(const Vector&, const Vector&, const Vector&, const Archetype::Munition*);

    IMPORT CGuided(const CGuided&);
    IMPORT CGuided(Class);
    IMPORT const Archetype::MotorData* get_motor_arch() const;
    IMPORT u16 get_sub_target() const;
    IMPORT IObjRW* get_target() const;
    IMPORT void init(const CreateParms&);
    IMPORT bool motor_on() const;
    IMPORT bool seeker_can_see(const Vector&) const;
    IMPORT void set_sub_target(u16);
    IMPORT void set_target(IObjRW*);

    BaseWatcher targetBaseWatcher;   // 60
    u16 targetSId;                // 62
    Archetype::MotorData* motorData; // 63
    f32 lifetime;                  // 64
};