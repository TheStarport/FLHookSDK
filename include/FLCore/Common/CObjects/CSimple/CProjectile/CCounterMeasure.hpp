#pragma once
#include "../CProjectile.hpp"

namespace Archetype
{
    struct CounterMeasure;
}
struct CCounterMeasure : CProjectile
{
    IMPORT virtual ~CCounterMeasure();
    IMPORT virtual int update(float, unsigned int);
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void expire_safe_time();

    IMPORT CCounterMeasure(const CCounterMeasure&);
    IMPORT CCounterMeasure(Class);
    IMPORT const Archetype::CounterMeasure* countermeasure_arch();
};