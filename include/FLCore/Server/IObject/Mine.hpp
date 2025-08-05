#pragma once

#include "../../FLCoreDefs.hpp"
#include "../../Common/CObjects/CSimple/CProjectile/CMine.hpp"
#include "GameObject.hpp"

struct Mine : public GameObject
{
        CMine* cmine() { return reinterpret_cast<CMine*>(cobject()); };
        static Mine* Cast(IObjInspectImpl* iobj)
        {
            if (iobj->cobject()->objectClass == CObject::CMINE_OBJECT)
            {
                return reinterpret_cast<Mine*>(iobj);
            }
            return nullptr;
        }
        // TODO: Fields and methods
        //  5 separate vftables, damn.
};
