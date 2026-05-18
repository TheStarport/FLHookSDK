#pragma once

#include "Base.hpp"

#include "../Common/CObjects/CSimple/CProjectile/CMine.hpp"

struct IObjServerMine : ServerGameObject
{
    CMine* cmine() { return reinterpret_cast<CMine*>(cobject()); };
    static IObjServerMine* Cast(IObjInspectImpl* iobj)
    {
        if (iobj->cobject()->objectClass == CObject::CMINE_OBJECT)
        {
            return reinterpret_cast<IObjServerMine*>(iobj);
        }
        return nullptr;
    }

    // TODO: Fields and methods
    //  5 separate vftables, damn.
};
