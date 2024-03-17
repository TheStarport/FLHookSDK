#pragma once
#include "../../../FLCoreDefs.hpp"

struct CCounterMeasure : public CProjectile
{
    public:
    IMPORT virtual ~CCounterMeasure();
    IMPORT virtual int update(float, unsigned int);
    IMPORT virtual void init_physics(const Vector&, const Vector&);
    IMPORT virtual void expire_safe_time();

    IMPORT CCounterMeasure(const CCounterMeasure&);
    IMPORT CCounterMeasure(Class);
    IMPORT const Archetype::CounterMeasure* countermeasure_arch();
};