#pragma once
#include <FLCore/FLCoreDefs.hpp>

#include "../CProjectile.hpp"

namespace Archetype
{
    struct Munition;
}

struct CBeam : public CProjectile
{
  public:
    IMPORT ~CBeam() override;
    IMPORT Vector get_velocity() const override;
    IMPORT f32 get_mass() const override;
    IMPORT void init_physics(const Vector&, const Vector&) override;
    IMPORT void expire_safe_time() override;

    IMPORT CBeam(const CBeam&);
    IMPORT CBeam(Class);
    IMPORT const char* get_collision_group() const;
    IMPORT const Vector& get_last_pos() const;
    IMPORT void move(f32);
    IMPORT const Archetype::Munition* munitionarch() const;
    IMPORT void set_velocity(const Vector&);

    bool safeTimeExpired;    // 60
    unsigned int beamUnused; // 61
    Vector velocity;         // 62
    Vector initialPosition;  // 65
    Vector lastPosition;     // 68
    bool initialized;        // 69
};
