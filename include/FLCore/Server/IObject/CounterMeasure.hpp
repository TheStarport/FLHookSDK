#pragma once

#include "../../FLCoreDefs.hpp"
#include "../../Common/CObjects/CSimple/CProjectile/CCounterMeasure.hpp" #
#include "GameObject.hpp"

struct CounterMeasure : public GameObject
{
        CCounterMeasure* ccountermeasure() { return reinterpret_cast<CCounterMeasure*>(cobject()); };
        static CounterMeasure* Cast(IObjInspectImpl* iobj)
        {
            if (iobj->cobject()->objectClass == CObject::CCOUNTERMEASURE_OBJECT)
            {
                return reinterpret_cast<CounterMeasure*>(iobj);
            }
            return nullptr;
        }
};
