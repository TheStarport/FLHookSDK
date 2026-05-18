#pragma once

#include "Base.hpp"

#include "../Common/CObjects/CSimple/CProjectile/CCounterMeasure.hpp"

struct IObjServerCounterMeasure : ServerGameObject
{
    CCounterMeasure* ccountermeasure() { return reinterpret_cast<CCounterMeasure*>(cobject()); }

    static IObjServerCounterMeasure* Cast(IObjInspectImpl* iobj)
    {
        if (iobj->cobject()->objectClass == CObject::CCOUNTERMEASURE_OBJECT)
        {
            return reinterpret_cast<IObjServerCounterMeasure*>(iobj);
        }

        return nullptr;
    }
};
