#pragma once
#include <FLCore/FLCoreDefs.hpp>

struct CBeam : public CProjectile
{
    public:
    IMPORT virtual ~CBeam();
    IMPORT virtual Vector get_velocity() const;
    IMPORT virtual f32 get_mass() const;
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void expire_safe_time();

    IMPORT CBeam(const CBeam&);
    IMPORT CBeam(Class);
    IMPORT const char* get_collision_group() const;
    IMPORT const Vector& get_last_pos() const;
    IMPORT void move(f32);
    IMPORT const Archetype::Munition* munitionarch() const;
    IMPORT void set_velocity(const Vector&);
};