#pragma once
#include "../CProjectile.hpp"

namespace Archetype
{
    struct CounterMeasure;
}
struct CCounterMeasure : CProjectile
{
    IMPORT ~CCounterMeasure() override;
    IMPORT int update(f32, u32) override;
    IMPORT void init_physics(const Vector&, const Vector&) override;
    IMPORT void expire_safe_time() override;

    IMPORT CCounterMeasure(const CCounterMeasure&);
    IMPORT CCounterMeasure(Class);
    IMPORT const Archetype::CounterMeasure* countermeasure_arch();
};
