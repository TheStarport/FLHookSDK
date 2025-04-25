#pragma once

#include "../../FLCoreDefs.hpp"
#include "GameObject.hpp"

struct Loot : public GameObject
{
    CLoot* cloot(){return reinterpret_cast<CLoot*>(cobject());};

    static Loot* cast(IObjInspectImpl* iobj)
    {
        if(iobj->cobject()->objectClass == CObject::CLOOT_OBJECT)
        {
            return reinterpret_cast<Loot*>(iobj);
        }
        return nullptr;
    }
    //TODO: Fields and methods
};