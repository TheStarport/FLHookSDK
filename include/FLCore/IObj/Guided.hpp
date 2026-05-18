#pragma once

#include "Base.hpp"

#include "../Common/CObjects/CSimple/CProjectile/CGuided.hpp"

struct IObjServerGuided : ServerGameObject
{
  public:
    CGuided* cguided() { return reinterpret_cast<CGuided*>(cobject()); };
    static IObjServerGuided* Cast(IObjInspectImpl* iobj)
    {
        if (iobj->cobject()->objectClass == CObject::CGUIDED_OBJECT)
        {
            return reinterpret_cast<IObjServerGuided*>(iobj);
        }
        return nullptr;
    }
    // TODO: Fields and methods
};
