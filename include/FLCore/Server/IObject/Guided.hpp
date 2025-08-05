#pragma once

#include "../../FLCoreDefs.hpp"
#include "../../Common/CObjects/CSimple/CProjectile/CGuided.hpp"
#include "GameObject.hpp"

struct Guided : public GameObject
{
    public:
        CGuided* cguided() { return reinterpret_cast<CGuided*>(cobject()); };
        static Guided* Cast(IObjInspectImpl* iobj)
        {
            if (iobj->cobject()->objectClass == CObject::CGUIDED_OBJECT)
            {
                return reinterpret_cast<Guided*>(iobj);
            }
            return nullptr;
        }
        // TODO: Fields and methods
};
